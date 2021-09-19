//
//  Errors.hpp
//  helloTriangle
//
//  Created by Jonny Kelso on 10/09/2021.
//

#ifndef Errors_hpp
#define Errors_hpp

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


#endif /* Errors_hpp */
