#include "EntryPoint.h"

#include <iostream>
#include <ranges>

#include "Logger.h"

namespace r8ge {
    int main(const EntryPointData& entry_data)
    {
        for(auto const&[i, sv] : entry_data.argv | std::ranges::views::enumerate)
            std::cout << i << " : " <<  sv << std::endl;
        //  R8GE_LOG("");   ->  TRACE
        //  R8GE_LOG_TRACE("");
        //      R8GE_LOG_DEBUG("");
        //  R8GE_LOG_ERROR("");
        //  R8GE_LOG_WARNI("");
        //  R8GE_LOG_FATAL("");



        return 0;
    }
}
