#include "../../EntryPoint.h"

#include <dlfcn.h>

#ifdef R8GE_LINUX

int main(int argc, char** argv) {
    dlopen("lib/libr8ge-core.so", RTLD_LAZY);

    r8ge::EntryPointData data{};

    for(int i = 1; i < argc; i++)
        data.argv.emplace_back(argv[i]);

   return r8ge::main(data);
   //return 0;
}

#endif//!R8GE_LINUX