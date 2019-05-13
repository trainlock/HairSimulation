#include <iostream>

/*******************************************
 ******           INCLUDES             *****
 *******************************************/

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GLM
#include <glm.hpp>
#include <gtx/string_cast.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/constants.hpp>
#include <gtc/type_ptr.hpp>

// Classes
#include "ShaderProgram.hpp"
#include "Camera.h"
#include "MeshObject.h"
#include "Texture.h"

/*******************************************
 ******      VARIABLE DECLARATIONS     *****
 *******************************************/

// Window dimensions
//const GLuint WIDTH = 1920, HEIGHT = 1080;
const GLuint WIDTH = 800, HEIGHT = 600;

// Time variables
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// Camera variables
Camera camera(glm::vec3(10.0f, 0.0f, 7.0f));
//Camera camera(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.f, 1.f, 0.f), 180, 0);

float lastX = WIDTH / 2.0f;
float lastY = HEIGHT / 2.0f;
bool firstMouse = true;

glm::mat4 model;

/*******************************************
 ******      FUNCTION DECLARATIONS     *****
 *******************************************/

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow *window);

/*******************************************
 ******              MAIN              *****
 *******************************************/

// The MAIN function, from here we start the application and run the rendering loop
int main(){
    std::cout << "Starting GLFW context, OpenGL 4.0 or higher" << std::endl;

    // Init GLFW
    if(!glfwInit()) {
        std::cout << "Failed to initialise GLFW" << std::endl;
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "HairSimulation", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    glEnable(GL_DEPTH_TEST);

    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // Show some useful information on the GL context
    std::cout << "GL vendor:       " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "GL renderer:     " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GL version:      " << glGetString(GL_VERSION) << std::endl;

    std::cout << "GLM, GLFW and Window fixed!" << std::endl;

    /************** Callback functions **************/
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /************** Models **************/
    /*
    MeshObject triangle;
    triangle.createTriangle();
     */

    ///*
    MeshObject box;
    box.createBox(2.0, 2.0, 2.0);
    // */

    /*
    MeshObject sphere;
    sphere.createSphere(2.0, 40);
     */

    ///*
    std::cout << "Created model mesh!" << std::endl;

    //Texture mainTexture = Texture("../textures/sky.tga");
    Texture mainTexture = Texture("../textures/wall.tga");
    //*/

    /************** Shaders **************/
    std::cout << "Setting up shader!" << std::endl;

    ///*
    // Build and compile the regular shader
    std::string regularVertFilename = "../shaders/regularShader.vert";
    std::string regularFragFilename = "../shaders/regularShader.frag";
    ShaderProgram regularShader(regularVertFilename, "", "", "", regularFragFilename);
    // */

    /*
    std::string hairVertFilename = "../shaders/hairShader.vert";
    std::string hairFragFilename = "../shaders/hairShader.frag";
    std::string hairGeometryFilename = "../shaders/hairShader.gs";
    ShaderProgram regularShader(hairVertFilename, "", "", hairGeometryFilename, hairFragFilename);
    regularShader();
    // */

    ///*
    // Build and compile the hair shader
    std::string hairVertFilename = "../shaders/hairShader.vert";
    std::string hairFragFilename = "../shaders/hairShader.frag";
    std::string hairGeometryFilename = "../shaders/hairShader.gs";
    ShaderProgram hairShader(hairVertFilename, "", "", hairGeometryFilename, hairFragFilename);
    hairShader();
    // */

    /************** Uniform Variables **************/
    std::cout << "Connecting shaders!" << std::endl;

    /** Regular shader **/
    ///*
    regularShader();
    GLint modelLocRegular = glGetUniformLocation(regularShader, "model");
    GLint viewLocRegular = glGetUniformLocation(regularShader, "view");
    GLint projLocRegular = glGetUniformLocation(regularShader, "projection");

    GLint mainTextureLocPlain = glGetUniformLocation(regularShader, "mainTexture");
    glUniform1i(mainTextureLocPlain, 0);
    // */

    /** Hair shader **/
    ///*
    hairShader();
    GLint modelLocHair = glGetUniformLocation(hairShader, "model");
    GLint viewLocHair = glGetUniformLocation(hairShader, "view");
    GLint projLocHair = glGetUniformLocation(hairShader, "projection");
    // */

    std::cout << "Shaders connected!" << std::endl;

    std::cout << "Entering render loop!" << std::endl;
    /*******************************************
     ******          RENDER LOOP           *****
     *******************************************/
    while (!glfwWindowShouldClose(window)){
        /************** Settings and Transforms **************/
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        // OpenGL settings
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        // Create camera transformation
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);

        /************** RENDERING **************/

        /************** Regular rendering **************/
        ///*
        regularShader();
        glUniformMatrix4fv(modelLocRegular, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLocRegular, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLocRegular, 1, GL_FALSE, glm::value_ptr(projection));
        // */

        //triangle.render(false);
        box.render(false);
        //sphere.render(false);

        ///*
        glActiveTexture(GL_TEXTURE0 + 0); // Texture unit 0
        glBindTexture(GL_TEXTURE_2D, mainTexture.textureID);
        // */

        ///*
        hairShader();
        glUniformMatrix4fv(modelLocHair, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLocHair, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLocHair, 1, GL_FALSE, glm::value_ptr(projection));
        // */

        //triangle.render(true);
        box.render(true);
        //sphere.render(true);

        ///*
        glActiveTexture(GL_TEXTURE0 + 0); // Texture unit 0
        glBindTexture(GL_TEXTURE_2D, mainTexture.textureID);
        // */

        /****************************************************/

        // Swap front and back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    std::cout << "Hello, World!" << std::endl;

    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    return 0;
}


/*******************************************
 ******            FUNCTIONS           *****
 *******************************************/
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glfwGetWindowSize( window, &width, &height );
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    float xOffset = xPos - lastX;
    float yOffset = lastY - yPos; // reversed since y-coordinates go from bottom to top

    lastX = xPos;
    lastY = yPos;

    //camera.ProcessMouseMovement(xoffset, yoffset);
    model = glm::translate(model, glm::vec3(0.f, yOffset*0.01f, -xOffset*0.01f));
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
    camera.ProcessMouseScroll(yOffset);
}

void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }
}