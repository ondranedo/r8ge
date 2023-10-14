#include "Core.h"

#include <iostream>

#include "utility/StringFormat.h"
#include "fileio/FileIO.h"

namespace r8ge {
    void assertImpl(const char *expr, unsigned long line, const char *fun, const char *msg,
                          const utility::StringFormat::ValidList &list) {
        global::fileIO->writeStderr(
        utility::StringFormat("assertion[{}];line[{}];func[{}];msg[{}]",
                              {expr,line,fun,utility::StringFormat(msg, list).to_string()}).to_string() + "\n");
    }
}
