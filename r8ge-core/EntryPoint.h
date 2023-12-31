#ifndef R8GE_ENTRYPOINT_H
#define R8GE_ENTRYPOINT_H

#include "Core.h"

#include <string>
#include <vector>

namespace r8ge {
    struct EntryPointData {
        std::vector<std::string_view> argv;
    };

    // Engine's entry point, called by the platform layer
    int main(const EntryPointData& entry_data);
}

#endif//!R8GE_ENTRYPOINT_H
