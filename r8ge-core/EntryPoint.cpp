#include "EntryPoint.h"

#include <iostream>
#include <ranges>

namespace r8ge {
    int main(const EntryPointData& entry_data)
    {
        for(auto const&[i, sv] : entry_data.argv | std::ranges::views::enumerate)
            std::cout << i << " : " <<  sv << std::endl;

        return 0;
    }
}
