

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
