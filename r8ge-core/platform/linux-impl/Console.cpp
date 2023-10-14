#include "../Console.h"
#include "../../fileio/FileIO.h"

namespace r8ge{
    void Console::log(const std::string &str) {
        global::fileIO->writeStdout(str);
    }

    void Console::changeColor(int color) {

    }

    void Console::resetColor() {

    }
}
