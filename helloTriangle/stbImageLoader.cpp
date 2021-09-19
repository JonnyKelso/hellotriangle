//
//  stbImageLoader.cpp
//  helloTriangle
//
//  Created by Jonny Kelso on 22/10/2020.
//  Copyright © 2020 Jonny Kelso. All rights reserved.
//

#include "stbImageLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


unsigned char* stbImageLoader::LoadImage(const std::string name, int& width, int& height, int& nrChannels )
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(name.c_str(), &width, &height, &nrChannels, 0);
    if(!data)
    {
        std::cout << "Failed to load image" << std::endl;
        return nullptr;
    }
    return data;
}

void stbImageLoader::FreeImage(unsigned char* data)
{
    stbi_image_free(data);
}
