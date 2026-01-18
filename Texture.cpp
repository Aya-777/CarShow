#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_STATIC
#include<GL/stb_image.h>
#include "Cuboid.h"
#include "Texture.h"
#include <iostream> 
#include <direct.h> // for _getcwd
    // ... inside loadTexture ...

void Texture::Use()
{
    glEnable(GL_TEXTURE_2D);								// Enable texture mapping
    glBindTexture(GL_TEXTURE_2D, textureID);				// Bind the texture as the current one
}
void Texture::loadTexture(const char* filename) {

    stbi_set_flip_vertically_on_load(true);
    int width, height, channels;


    unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);

    if (image) {
        std::cout << "Image loaded successfully: " << width << "x" << height << ", Channels: " << channels << std::endl;


        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
            channels == 4 ? GL_RGBA : GL_RGB,
            GL_UNSIGNED_BYTE, image);

        stbi_image_free(image);
    }
    else {
        char buff[FILENAME_MAX];
        _getcwd(buff, FILENAME_MAX);
        std::cout << "Failed to load texture!" << std::endl;
        std::cout << "Looking for: " << filename << std::endl;
        std::cout << "Current Working Directory: " << buff << std::endl;
        std::cout << "stb error: " << stbi_failure_reason() << std::endl;

    }
}
