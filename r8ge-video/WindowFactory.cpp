//
// Created by vojta on 03.10.2023.
//

#include "WindowFactory.h"
#include "platform/Win32Window.h"

namespace r8ge
{
    std::shared_ptr<Window> WindowFactory::constructWindow()
    {
        return std::make_shared<Win32Window>();
    }
    //
    //std::shared_ptr<Window> WindowFactory::constructWindow()
    //{
    //    return std::shared_ptr<LinuxWindow>();
}

