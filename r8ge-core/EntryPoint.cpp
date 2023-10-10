#include "EntryPoint.h"

#include "Logger.h"
#include "Ar8ge.h"

namespace r8ge {
    int main(const EntryPointData& entry_data)
    {
        global::logger = new Logger;
        auto engine = new Ar8ge;

        engine->init();
        engine->run();
        engine->exit();

        delete engine;
        delete global::logger;

        return 0;
    }
}
