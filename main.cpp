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
Camera camera(glm::vec3(1.0f, 1.0f, 1.0f));
//Camera camera(glm::vec3(10.0f, 0.0f, 0.0f), glm::vec3(0.f, 1.f, 0.f), 180, 0);
//GLfloat lastX = 400;
//GLfloat lastY = 300;
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
    std::cout << "Starting GLFW context, OpenGL 3.3 or higher" << std::endl;

    // Init GLFW
    if(!glfwInit()) {
        std::cout << "Failed to initialise GLFW" << std::endl;
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


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

    // Initialize GLEW to setup the OpenGL Function pointers
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    std::cout << "GLM, GLFW and Window fixed!" << std::endl;

    /************** Callback functions **************/
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /************** Models **************/
    //std::cout << "Time to model!" << std::endl;
    /*
    MeshObject triangle;
    triangle.createTriangle();
    std::cout << "Created triangle!" << std::endl;
     */

    //Texture mainTexture = Texture("../textures/sky.tga");
    Texture mainTexture = Texture("../textures/wall.tga");

    /************** Shaders **************/
    std::cout << "Setting up shader!" << std::endl;

    // Build and compile the regular shader
    std::string vertexFilename = "../shaders/vertexShader.vert";
    std::string fragmentFilename = "../shaders/fragmentShader.frag";
    ShaderProgram regularShader(vertexFilename, "", "", "", fragmentFilename);
    regularShader();

    /************** Uniform Variables **************/
    std::cout << "Connecting shaders!" << std::endl;
    /** Plain shader **/

    //regularShader(); // Used when more than one shader is used
    //GLint modelLocRegular = glGetUniformLocation(regularShader, "model");
    GLint viewLocRegular = glGetUniformLocation(regularShader, "view");
    GLint projLocRegular = glGetUniformLocation(regularShader, "projection");

    ///*
    GLint mainTextureLocPlain = glGetUniformLocation(regularShader, "mainTexture");
    glUniform1i(mainTextureLocPlain, 0);
    //*/

    std::cout << "Shaders connected!" << std::endl;

    ///* Uncomment to remove manual triangle
    float vertices[] = {
            -0.5f, -0.5f, 0.0f, // left
             0.5f, -0.5f, 0.0f, // right
             0.0f,  0.5f, 0.0f  // top
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    // */


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
        ///*
        // Create camera transformation
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::perspective(camera.Zoom, (float)WIDTH/(float)HEIGHT, 0.1f, 1000.0f);
        //*/

        /*
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(camera.Zoom, (float)WIDTH/(float)HEIGHT, 0.1f, 1000.0f);
        */

        /************** RENDERING **************/

        /************** Regular rendering **************/
        regularShader();
        glUniformMatrix4fv(viewLocRegular, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLocRegular, 1, GL_FALSE, glm::value_ptr(projection));

        /*
        triangle.render(true);
        */

        glActiveTexture(GL_TEXTURE0 + 0); // Texture unit 0
        glBindTexture(GL_TEXTURE_2D, mainTexture.textureID);

        ///*
        // draw our first triangle
        //glUseProgram(regularShader);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // */

        /****************************************************/

        // Swap front and back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::cout << "Hello, World!" << std::endl;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

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
