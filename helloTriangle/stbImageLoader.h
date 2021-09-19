//
//  stbImageLoader.hpp
//  helloTriangle
//
//  Created by Jonny Kelso on 22/10/2020.
//  Copyright © 2020 Jonny Kelso. All rights reserved.
//

#ifndef STB_IMAGE_H
#define STB_IMAGE_H


#include <string>
#include <iostream>

class stbImageLoader
{
public:
    stbImageLoader(){};
    //~stbImageLoader();
    
    unsigned char* LoadImage(const std::string name, int& width, int& height, int& nrChannels );
    void FreeImage(unsigned char* data);
    
};
#endif // STB_IMAGE_H
