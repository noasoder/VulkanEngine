#ifndef ENGINE_CORE
#define ENGINE_CORE

#ifndef OPENGL
//#define OPENGL
#endif // OPENGL
#ifndef VULKAN
#define VULKAN
#endif // VULKAN

#ifndef WINDOWS
#define WINDOWS
#endif // !WINDOWS

#ifndef LINUX
// #define LINUX
#endif // !LINUX


#ifdef OPENGL
#define GLEW_STATIC
#include <GL/glew.h>
#endif // OPENGL

#ifdef VULKAN
#define GLFW_INCLUDE_VULKAN
#endif // VULKAN

#include <GLFW/glfw3.h>

//#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#define STB_IMAGE_IMPLEMENTATION
#define ENABLE_VALIDATION_LAYERS true

#endif // !ENGINE_CORE