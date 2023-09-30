#include "Core.h"

#include <iostream>

#include "utility/StringFormat.h"

namespace r8ge {
    void assertImpl(const char *expr, unsigned long line, const char *fun, const char *msg,
                          const utility::StringFormat::ValidList &list) {
        //TODO: Add thread safety, fileI/O module
        std::cerr <<
        utility::StringFormat("assertion[{}];line[{}];func[{}];msg[{}]",
                              {expr,line,fun,utility::StringFormat(msg, list).to_string()}).to_string() << std::endl;
    }
}
