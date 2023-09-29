#include "Core.h"

#include <iostream>

#include "utility/StringFormat.h"

namespace r8ge {
    void assertImpl(const char * expr, unsigned long line, const char * fun, const char *msg) {
        //TODO: Add thread safety, fileI/O module
        std::cerr << utility::StringFormat("assertion[{}];line[{}];func[{}];msg[{}]",{expr,line,fun,msg}).to_string() << std::endl;
    }

    void assertImpl(const char * expr, unsigned long line, const char * fun) {
        assertImpl(expr, line, fun, "");
    }
}
