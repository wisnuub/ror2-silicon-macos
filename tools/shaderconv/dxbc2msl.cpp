// Translate a DXBC shader to Unity-style Metal Shading Language with HLSLcc,
// emitting the MSL source and the resource bindings HLSLcc assigned.
#include "hlslcc.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

static std::string esc(const std::string& s) {
    std::string o;
    for (char c : s) { if (c == '"' || c == '\\') o += '\\'; o += c; }
    return o;
}

struct Reflect : HLSLccReflection {
    std::ostringstream j;
    bool first = true;
    void item(const std::string& s) { j << (first ? "" : ",\n") << "  " << s; first = false; }
    void OnDiagnostics(const std::string& e, int line, bool isError) override {
        fprintf(stderr, "%s: %s (line %d)\n", isError ? "error" : "warn", e.c_str(), line);
    }
    void OnInputBinding(const std::string& n, int i) override {
        item("{\"kind\":\"input\",\"name\":\"" + esc(n) + "\",\"index\":" + std::to_string(i) + "}");
    }
    bool OnConstantBuffer(const std::string& n, size_t size, size_t count) override {
        item("{\"kind\":\"cbdecl\",\"name\":\"" + esc(n) + "\",\"size\":" + std::to_string(size) + ",\"count\":" + std::to_string(count) + "}");
        return true;
    }
    bool OnConstant(const std::string& n, int bindIndex, SHADER_VARIABLE_TYPE t, int rows, int cols, bool isMatrix, int arraySize, bool isUsed) override {
        item("{\"kind\":\"const\",\"name\":\"" + esc(n) + "\",\"offset\":" + std::to_string(bindIndex) + ",\"type\":" + std::to_string((int)t) +
             ",\"rows\":" + std::to_string(rows) + ",\"cols\":" + std::to_string(cols) + ",\"isMatrix\":" + (isMatrix ? "true" : "false") +
             ",\"arraySize\":" + std::to_string(arraySize) + ",\"used\":" + (isUsed ? "true" : "false") + "}");
        return true;
    }
    void OnConstantBufferBinding(const std::string& n, int i) override {
        item("{\"kind\":\"cbuffer\",\"name\":\"" + esc(n) + "\",\"index\":" + std::to_string(i) + "}");
    }
    void OnTextureBinding(const std::string& n, int i, int s, bool ms, HLSLCC_TEX_DIMENSION d, bool uav) override {
        item("{\"kind\":\"texture\",\"name\":\"" + esc(n) + "\",\"index\":" + std::to_string(i) +
             ",\"sampler\":" + std::to_string(s) + ",\"ms\":" + (ms ? "true" : "false") +
             ",\"dim\":" + std::to_string((int)d) + ",\"uav\":" + (uav ? "true" : "false") + "}");
    }
    void OnBufferBinding(const std::string& n, int i, bool uav) override {
        item("{\"kind\":\"buffer\",\"name\":\"" + esc(n) + "\",\"index\":" + std::to_string(i) + ",\"uav\":" + (uav ? "true" : "false") + "}");
    }
    void OnFragmentOutputDeclaration(int comps, int idx) override {
        item("{\"kind\":\"fragout\",\"index\":" + std::to_string(idx) + ",\"components\":" + std::to_string(comps) + "}");
    }
    void OnVertexProgramOutput(const std::string& n, const std::string& sem, int si) override {
        item("{\"kind\":\"vsout\",\"name\":\"" + esc(n) + "\",\"semantic\":\"" + esc(sem) + "\",\"index\":" + std::to_string(si) + "}");
    }
    void OnBuiltinOutput(SPECIAL_NAME n) override {
        item("{\"kind\":\"builtin\",\"id\":" + std::to_string((int)n) + "}");
    }
};

static const unsigned int kFlags = HLSLCC_FLAG_TRANSLATE_MATRICES | HLSLCC_FLAG_UNIFORM_BUFFER_OBJECT;

static bool translate(const char* in, const char* outMetal, const char* outJson) {
    std::ifstream f(in, std::ios::binary);
    std::string dxbc((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    GlExtensions ext = {};
    GLSLCrossDependencyData deps;
    HLSLccSamplerPrecisionInfo prec;
    Reflect r;
    GLSLShader out;
    if (!TranslateHLSLFromMem(dxbc.data(), kFlags, LANG_METAL, &ext, &deps, prec, r, &out))
        return false;
    std::ofstream(outMetal) << out.sourceCode;
    std::ofstream(outJson) << "[\n" << r.j.str() << "\n]\n";
    return true;
}

// --batch: read "in<TAB>out.metal<TAB>out.json" lines from stdin, print "ok N" / "fail N" per line.
int main(int argc, char** argv) {
    if (argc == 2 && std::string(argv[1]) == "--batch") {
        std::string line;
        for (int n = 0; std::getline(std::cin, line); ++n) {
            size_t a = line.find('\t'), b = line.find('\t', a + 1);
            if (a == std::string::npos || b == std::string::npos) continue;
            bool ok = translate(line.substr(0, a).c_str(), line.substr(a + 1, b - a - 1).c_str(), line.substr(b + 1).c_str());
            printf("%s %d\n", ok ? "ok" : "fail", n);
            fflush(stdout);
        }
        return 0;
    }
    if (argc < 4) {
        fprintf(stderr, "usage: %s <in.dxbc> <out.metal> <out.json> | --batch\n", argv[0]);
        return 2;
    }
    return translate(argv[1], argv[2], argv[3]) ? 0 : 1;
}
