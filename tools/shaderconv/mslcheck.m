// Compile MSL files with the runtime Metal compiler (what Unity uses) and report failures.
#import <Foundation/Foundation.h>
#import <Metal/Metal.h>

int main(int argc, const char** argv) {
    @autoreleasepool {
        id<MTLDevice> dev = MTLCreateSystemDefaultDevice();
        MTLCompileOptions* opt = [MTLCompileOptions new];
        opt.fastMathEnabled = YES;
        int fails = 0;
        for (int i = 1; i < argc; i++) {
            @autoreleasepool {
                NSString* src = [NSString stringWithContentsOfFile:@(argv[i]) encoding:NSUTF8StringEncoding error:nil];
                NSError* err = nil;
                id<MTLLibrary> lib = [dev newLibraryWithSource:src options:opt error:&err];
                if (!lib || (![lib newFunctionWithName:@"xlatMtlMain"] && ![lib newFunctionWithName:@"computeMain"])) {
                    fails++;
                    printf("FAIL %s\n%s\n", argv[i], err.localizedDescription.UTF8String ?: "no xlatMtlMain");
                }
            }
        }
        printf("checked %d, failed %d\n", argc - 1, fails);
        return fails ? 1 : 0;
    }
}
