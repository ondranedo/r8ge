#include "EntryPoint.h"
#include "fileio/FileIO.h"

#include "Logger.h"
#include "Ar8ge.h"

namespace r8ge {
    int main(const EntryPointData& entry_data)
    {
        global::logger = new Logger;
        global::fileIO = new FileIO(256);
        auto engine = new Ar8ge;

        engine->init();
        engine->run();
        engine->exit();

        delete engine;
        delete global::fileIO;
        delete global::logger;

        return 0;
    }
}
