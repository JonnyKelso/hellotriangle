#pragma once

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

namespace Graphics
{

    GLenum glCheckError_(const char *file, int line);
    #define GLCHECKERROR() glCheckError_(__FILE__, __LINE__)
}

