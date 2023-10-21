#ifndef R8GE_GLXCONTEXT_H
#define R8GE_GLXCONTEXT_H

#include "../XContext.h"

#include <GL/glew.h>
#include <GL/glx.h>

namespace r8ge {
    namespace video {
        class GLXContext : public XContext  {
        public:
            GLXContext();
            ~GLXContext();

            void swapBuffers() const override;

            void createContext() override;

            [[nodiscard]] ::XVisualInfo *getVisualInfo() const override;

            void init() override;

            void exit() override;

            void setContextActive() const override;

            void windowIsReady() const override;
        private:
            ::GLXContext m_context;
            ::XVisualInfo *m_visual;
            static size_t s_contextCount;
        };
    }
}

#endif//!R8GE_GLXCONTEXT_H
