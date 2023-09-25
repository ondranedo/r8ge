#include "EntryPoint.h"

#include <iostream>
#include <ranges>

#include "Logger.h"

namespace r8ge {
    int main(const EntryPointData& entry_data)
    {
        r8ge::mainLogger = new Logger;

        delete r8ge::mainLogger;
        return 0;
    }
}
