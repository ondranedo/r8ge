#include "Core.h"

#include <iostream>

#include "utility/StringFormat.h"
#include "fileio/FileIO.h"

namespace r8ge {
    void assertImpl(std::string_view expr, unsigned long line, std::string_view fun, std::string_view msg,
                          const utility::StringFormat::ValidList &list) {
        global::fileIO->writeStderr(
        utility::StringFormat("assertion[{}];line[{}];func[{}];msg[{}]",
                              {expr,line,fun,utility::StringFormat(msg, list).to_string()}).to_string() + "\n");
    }
}
