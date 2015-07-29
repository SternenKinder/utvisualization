//
// Created by Ulrich Eck on 26/07/2015.
//

#ifndef UBITACK_GLFW_RENDERMANAGER_H
#define UBITACK_GLFW_RENDERMANAGER_H

#include <string>

#ifdef HAVE_GLEW
	#include "GL/glew.h"
#endif
#include <GLFW/glfw3.h>

#include <utVisualization/RenderAPI/utRenderAPI.h>

namespace Ubitrack {
    namespace Visualization {

        class GLFWWindowImpl : public VirtualWindow {

        public:
            GLFWWindowImpl(int _width, int _height, const std::string& _title);
            ~GLFWWindowImpl();

            virtual void pre_render();
            virtual void post_render();

            // Implementation of Public interface
            virtual bool is_valid();
            virtual bool create();
            virtual void initGL(CameraHandle* cam);
            virtual void destroy();

        private:
            GLFWwindow*	m_pWindow;

        };

        // callback implementations for GLFW
        inline static void WindowResizeCallback(
                GLFWwindow *win,
                int w,
                int h) {
            CameraHandle *cam = static_cast<CameraHandle*>(glfwGetWindowUserPointer(win));
            cam->on_window_size(w, h);
        }

        inline static void WindowRefreshCallback(GLFWwindow *win) {
            CameraHandle *cam = static_cast<CameraHandle*>(glfwGetWindowUserPointer(win));
            cam->on_render();
        }

        inline static void WindowCloseCallback(GLFWwindow *win) {
            CameraHandle *cam = static_cast<CameraHandle*>(glfwGetWindowUserPointer(win));
            cam->on_window_close();
        }

        inline static void WindowKeyCallback(GLFWwindow *win,
                                             int key,
                                             int scancode,
                                             int action,
                                             int mods) {
            CameraHandle *cam = static_cast<CameraHandle*>(glfwGetWindowUserPointer(win));
            cam->on_keypress(key, scancode, action, mods);
        }


        inline static void WindowCursorPosCallback(GLFWwindow *win,
                                             double xpos,
                                             double ypos) {
            CameraHandle *cam = static_cast<CameraHandle*>(glfwGetWindowUserPointer(win));
            cam->on_cursorpos(xpos, ypos);
        }

    }
}

#endif //UBITACK_GLFW_RENDERMANAGER_H
