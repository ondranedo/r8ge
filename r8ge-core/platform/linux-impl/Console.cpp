#include "../Console.h"
#include "../../fileio/FileIO.h"

#include <ranges>

static void ANSISend(const std::vector<std::string>& str);

namespace r8ge {
    void Console::log(const std::string &str) {
        global::fileIO->writeStdout(str);
    }

    void Console::set(const Console::ConsoleParam &param) {
        std::vector<std::string> args;

        if (param.bold)
            args.emplace_back("1");
        if (param.italic)
            args.emplace_back("3");
        if (param.underline == UNDERLINE)
            args.emplace_back("4");
        if (param.underline == DOUBLE_UNDERLINE)
            args.emplace_back("21");
        if (param.blink)
            args.emplace_back("5");

        if(param.useDefaultForegroundColor)
            args.emplace_back("39");
        else
            args.emplace_back("38;2;"+
                              std::to_string(param.foregroundColor.r)+";"+
                              std::to_string(param.foregroundColor.g)+";"+
                              std::to_string(param.foregroundColor.b));

        if(param.useDefaultBackgroundColor)
            args.emplace_back("49");
        else
            args.emplace_back("48;2;"+
                              std::to_string(param.backgroundColor.r)+";"+
                              std::to_string(param.backgroundColor.g)+";"+
                              std::to_string(param.backgroundColor.b));

        ANSISend(args);
    }

    void Console::setDefault() {
        ANSISend({"0"});
    }
}

static void ANSISend(const std::vector<std::string>& str) {
    std::string s;
    for (auto[index, arg] : str | std::views::enumerate) {
        s += arg;
        s += index < str.size()-1?";":"";
    }

    r8ge::global::fileIO->writeStdout("\033[" + s + "m");
}
std::vector<std::string> setBold() {
    return {"1"};
}