//
// Created by Vojta on 04.10.2023.
//

#ifndef R8GE_WINDOWMANAGER_HPP
#define R8GE_WINDOWMANAGER_HPP

#include "../vendor/glfw/include/GLFW/glfw3.h"
#include <memory>
#include <mutex>


namespace r8ge
{

    std::mutex WindowManager_mutex;

    class WindowManager
    {
    public:
        WindowManager(WindowManager const &) = delete;

        WindowManager &operator=(WindowManager const &) = delete;

        ~WindowManager() = default;

        void init()
        {
            if(!glfwInit()){
                printf("Unable to init glfw");
            }
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        }

        void terminate()
        {
            glfwTerminate();
        }

        static WindowManager *get_instance()
        {
            std::lock_guard<std::mutex> lock(WindowManager_mutex);
            if (!instance)
            {
                instance = std::unique_ptr<WindowManager>(new WindowManager());
            }
            return instance.get();
        }

    private:
        inline static std::unique_ptr<WindowManager> instance{nullptr};

        WindowManager() = default;
    };

}

#endif //R8GE_WINDOWMANAGER_HPP
