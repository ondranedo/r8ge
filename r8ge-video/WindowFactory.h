//
// Created by vojta on 03.10.2023.
//

#ifndef R8GE_WINDOWFACTORY_H
#define R8GE_WINDOWFACTORY_H

#include <memory>
#include "Window.h"


namespace r8ge
{
    class Window;

    class WindowFactory
    {
    public:
        std::shared_ptr<Window> constructWindow();
    };
}
#endif //R8GE_WINDOWFACTORY_H