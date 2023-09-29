#include "../EntryPoint.h"

#ifdef R8GE_LINUX

int main(int argc, char** argv) {
    r8ge::EntryPointData data{};

    for(int i = 1; i < argc; i++)
        data.argv.emplace_back(argv[i]);

   return r8ge::main(data);
}

#else
    #error "Unsuported platform"
#endif