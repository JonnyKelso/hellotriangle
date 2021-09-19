//
//  stb_image_impl.cpp
//  helloTriangle
//
//  Created by Jonny Kelso on 02/04/2020.
//  Copyright © 2020 Jonny Kelso. All rights reserved.
//
#ifndef STB_IMAGE_H
#define STB_IMAGE_H

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <string>
#include <iostream>

class stb_image_loader
{
public:
    stb_image_loader(){};
    
    unsigned char* LoadImage(const std::string name, int& width, int& height, int& nrChannels )
    {
        unsigned char* data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);
        if(!data)
        {
            std::cout << "Failed to load image" << std::endl;
            return nullptr;
        }
        return data;
    }
    
    void FreeImage(unsigned char* data)
    {
        stbi_image_free(data);
    }
    
};
#endif //STB_IMAGE_H


