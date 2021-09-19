
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/defs.h>

#include <iostream>
#include <array>
#include <cmath>
#include <algorithm>
#include <variant>

#include "Shader.h"
#include "Mesh.h"
//#include "Binder.h"
#include "Input.h"
#include "InputProcessing.h"
#include "Model.h"
#include "Lighting.h"
#include "Cubes.h"
#include "Quad.h"
#include "Materials.h"
#include "Utilities.h"
#include "Renderable.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* glInitialise(const int width, const int height);

int main()
{
    
    const float screenWidth = 800.0f;
    const float screenHeight = 600.0f;

    GLFWwindow* window = glInitialise(screenWidth, screenHeight);
    if( window == nullptr)
    {
        std::cout << "Failed to initialise GLFW window" << std::endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // capture the mouse
    Input::Mouse mouse{};
    glfwSetCursorPosCallback(window, Input::Mouse::mouse_callback);
    
    using namespace Graphics;
    Graphics::camera cam{};

    double lastFrame{ glfwGetTime() };
    
    std::filesystem::path current_path = std::filesystem::current_path();
    std::cout << current_path << '\n';

    // Cubes in the scene
    Graphics::ShaderProgram lightSourceShaderProgram( "../shaders/cube.vs", "../shaders/uber_phong.fs");
    Graphics::ShaderProgram plainCubeShaderProgram  ( "../shaders/cube.vs", "../shaders/uber_phong.fs");
    Graphics::ShaderProgram scaledCubeShaderProgram ( "../shaders/cube.vs", "../shaders/uber_phong.fs");
    
    // Light source
    Graphics::Lighting bottomLeftPointLight{{-2.0f, -2.0f, 4.0f}, {{0.2f, 0.2f, 0.2f}, {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}};
    Graphics::Lighting topLeftPointLight{{-2.0f, -2.0f, 4.0f}, {{0.2f, 0.2f, 0.2f}, {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}};
    Graphics::Lighting directionalLight{{1.0, 1.0, 1.0}, {glm::vec3{1}, glm::vec3{}, glm::vec3{}}};

    

    Examples::Cubes lightSourceCube{""}, plainCube(""), scaledCube("");

    // Models:
    // Backpack backPackmodel
    glm::mat4 backPackmodel = glm::mat4(1.0f);
    backPackmodel = glm::translate(backPackmodel, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    backPackmodel = glm::scale(backPackmodel, glm::vec3(1));    // it's a bit too big for our scene, so scale it down

    // texturedCube model
    glm::mat4 texturedCubeModel = glm::mat4(1.0f);
    texturedCubeModel = glm::translate(texturedCubeModel, glm::vec3(-1.8f, -1.8f, 3.0f));
    texturedCubeModel = glm::scale(texturedCubeModel, glm::vec3(0.5f));

    // Cube model
    glm::mat4 plainCubeModel = glm::mat4(1.0f);
    plainCubeModel = glm::translate(plainCubeModel, glm::vec3(-2.0f, 1.0f, 2.0f));
    plainCubeModel = glm::scale(plainCubeModel, glm::vec3(0.5f));

    // Scaled Cube model
    glm::mat4 scaledCubeModel = glm::mat4(1.0f);
    scaledCubeModel = glm::translate(scaledCubeModel, glm::vec3(-2.0f, 1.0f, 2.0f));
    scaledCubeModel = glm::scale(scaledCubeModel, glm::vec3(0.52f));

    // Grass
    glm::mat4 grassModel = glm::mat4(1.0f);
    grassModel = glm::translate(grassModel, glm::vec3(-2.0f, -1.0f, 2.5f));

    // Blend window
    glm::mat4 blendWindowModel = glm::mat4(1.0f);
    blendWindowModel = glm::translate(blendWindowModel, glm::vec3(-2.0f, -1.0f, 2.6f));

    // LightSource model
    const glm::vec3 lightSourcePos{bottomLeftPointLight.directionality()};
    glm::mat4 lightSourceModel = glm::mat4(1.0f);
    lightSourceModel = glm::translate(lightSourceModel, lightSourcePos); // translate it down so it's at the center of the scene
    lightSourceModel = glm::scale(lightSourceModel, glm::vec3(0.2f));    // it's a bit too big for our scene, so scale it down

    Material cubeMaterial{{0.3f, 0.7f, 0.3f}, {0.7f, 0.3f, 0.1f}, {0.2f, 0.1f, 0.1f}},
             scaledCubeMaterial{{1, 1, 1}, {},{}},
             lightSourceMaterial{glm::vec3{1.0}, {}, {}, 0};

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);
    
    // These are containers of objects we can render.
    // When we add a renderable, we need to provide the shader program, the model, lighting and material to be used.
    using RenderablesVariant = Renderable<Model, Examples::Cubes, Examples::Quad>;
    std::vector<RenderablesVariant> opaqueRenderables{};
    std::vector<RenderablesVariant> transparentRenderables{};
        
    
    
    opaqueRenderables.emplace_back(
        Model{"../models/backpack/backpack.obj"},
        RenderData{
            {"../shaders/model_loading.vs",  "../shaders/uber_phong.fs"},
            backPackmodel,
            {bottomLeftPointLight, topLeftPointLight},
            MappedMaterial{},
            0
    });
    
    opaqueRenderables.emplace_back(
        Examples::Cubes{"../images/container2.png",
                        "../images/container2_specular.png"},
        RenderData{
            {"../shaders/cube.vs", "../shaders/uber_phong.fs"},
            texturedCubeModel,
            {bottomLeftPointLight, topLeftPointLight},
            MappedMaterial{32},
            0
    });
    
    transparentRenderables.emplace_back(
        Examples::Quad{"../images/grass.png"},
        RenderData{
            {"../shaders/quad.vs", "../shaders/uber_phong.fs"},
            grassModel,
            {bottomLeftPointLight, topLeftPointLight},
            MappedMaterial{},
            0.1f
        });
    
    transparentRenderables.emplace_back(
        Examples::Quad{"../images/blending_transparent_window.png"},
        RenderData{
            {"../shaders/quad.vs", "../shaders/uber_phong.fs"},
            blendWindowModel,
            {bottomLeftPointLight, topLeftPointLight},
            MappedMaterial{},
            0
        });
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    
    glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while(!glfwWindowShouldClose(window))
    {


        const double currentFrame {glfwGetTime()};
        const auto deltaTime{currentFrame - lastFrame};
        lastFrame = currentFrame;
        cam = processInput(window, cam, deltaTime, mouse);

        glStencilMask(0xFF);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glStencilMask(0x00);
        glEnable(GL_DEPTH_TEST);

        const auto view = glm::lookAt(cam.pos, cam.pos + cam.front, cam.up);
        const auto projection = glm::perspective(glm::radians(mouse.zoom()), screenWidth / screenHeight, 0.1f, 100.0f);

        // Light source
        updateUberPhong(lightSourceShaderProgram, view, projection, lightSourceModel, {directionalLight}, lightSourceMaterial, 0.0, cam);
        lightSourceCube.Draw(lightSourceShaderProgram);

        // Rotating:
            // Textured Cube
                //texturedCubeModel = glm::rotate(texturedCubeModel, fmodf(static_cast<float>(glm::radians(10.0f) * deltaTime), static_cast<float>(glm::radians(360.0))), glm::vec3(0.0f, 1.0f, 0.0f));
            // Backpack
                //backPackmodel = glm::rotate(backPackmodel, fmodf(static_cast<float>(glm::radians(10.0f) * deltaTime), static_cast<float>(glm::radians(360.0))), glm::vec3(0.0f, 1.0f, 0.0f));
        
        for(auto& r : opaqueRenderables)
        {
            r.draw(view, projection, cam);
        }
        for(auto& r : transparentRenderables)
        {
            r.draw(view, projection, cam);
        }
        glStencilFunc(GL_ALWAYS, 1, 0xFF); // all fragments should pass the stencil test
        glStencilMask(0xFF); // enable writing to the stencil buffer;

        // Cube
        updateUberPhong(plainCubeShaderProgram, view, projection, plainCubeModel, {bottomLeftPointLight, topLeftPointLight}, cubeMaterial, 0.0, cam);
        plainCube.Draw(plainCubeShaderProgram);

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00); // disable writing to the stencil buffer
        glDisable(GL_DEPTH_TEST);

        // Scaled cube
        updateUberPhong(scaledCubeShaderProgram, view, projection, scaledCubeModel, {bottomLeftPointLight, topLeftPointLight}, scaledCubeMaterial, 0.0, cam);
        scaledCube.Draw(scaledCubeShaderProgram);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;

}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
GLFWwindow* glInitialise(const int width, const int height)
{
    // init lib
    if(!glfwInit())
    {
        std::cout << "Failed to init GLFW" << std::endl;
        return nullptr;
    }
    // ask for 3.2 context on MacOSX
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif //__APPLE__

    // create windowed mode GLFW window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(width, height, "Learn OpenGL", NULL, NULL);
    if(window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // GLAD: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }
    return window;
}
