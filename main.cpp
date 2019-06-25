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

// Master Strands
float lengthHairSegment = 0.1f; //0.05; //1.0f;
int nrHairSegments = 4;         // How many segments should each strand of hair have?

int nrMasterStrands = 0;

/*******************************************
 ******      FUNCTION DECLARATIONS     *****
 *******************************************/

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow *window);
GLuint createMasterStrands(const MeshObject& meshObject);

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

    // glfw: Capture mouse position and movement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    /************** Models **************/
    ///* Triangle
    MeshObject triangle;
    triangle.createTriangle();
    // */

    /* Box
    MeshObject box;
    box.createBox(2.0, 2.0, 2.0);
     */

    /* Sphere
    MeshObject sphere;
    sphere.createSphere(2.0, 40);
     */

    ///*
    std::cout << "Created model mesh!" << std::endl;

    //Texture mainTexture = Texture("../textures/sky.tga");
    Texture mainTexture = Texture("../textures/wall.tga");
    //*/

    /************** Hair **************/

    GLuint hairDataTextureID = createMasterStrands(triangle);
    //GLuint hairDataTextureID = createMasterStrands(box);
    //GLuint hairDataTextureID = createMasterStrands(sphere);

    /************** Shaders **************/
    std::cout << "Setting up shader!" << std::endl;
    // Build and compile the regular shader
    std::string regularVertFilename = "../shaders/regularShader.vert";
    std::string regularFragFilename = "../shaders/regularShader.frag";
    ShaderProgram regularShader(regularVertFilename, "", "", "", regularFragFilename);

    // Build and compile the hair shader
    std::string hairVertFilename = "../shaders/hairShader.vert";
    std::string hairFragFilename = "../shaders/hairShader.frag";
    std::string hairGeometryFilename = "../shaders/hairShader.gs";
    std::string hairTessCtrlFilename = "../shaders/hairShader.tc";
    std::string hairTessEvalFilename = "../shaders/hairShader.te";
    //ShaderProgram hairShader(hairVertFilename, "", "", hairGeometryFilename, hairFragFilename);
    ShaderProgram hairShader(hairVertFilename, hairTessCtrlFilename, hairTessEvalFilename, hairGeometryFilename, hairFragFilename);
    hairShader();

    /************** Uniform Variables **************/
    std::cout << "Connecting shaders!" << std::endl;

    /** Regular shader **/
    regularShader();
    GLint modelLocRegular = glGetUniformLocation(regularShader, "model");
    GLint viewLocRegular = glGetUniformLocation(regularShader, "view");
    GLint projLocRegular = glGetUniformLocation(regularShader, "projection");

    GLint mainTextureLocPlain = glGetUniformLocation(regularShader, "mainTexture");
    glUniform1i(mainTextureLocPlain, 0);

    /** Hair shader **/
    hairShader();
    GLint modelLocHair = glGetUniformLocation(hairShader, "model");
    GLint viewLocHair = glGetUniformLocation(hairShader, "view");
    GLint projLocHair = glGetUniformLocation(hairShader, "projection");

    GLint hairDataTextureLocPlain = glGetUniformLocation(hairShader, "hairDataTexture");
    glUniform1i(hairDataTextureLocPlain, 1);

    GLint nrHairSegmentsLoc = glGetUniformLocation(hairShader, "nrHairSegments");
    GLint nrMasterStrandVerticesLoc = glGetUniformLocation(hairShader, "nrMasterStrands");
    glUniform1f(nrHairSegmentsLoc, (float)nrHairSegments);
    glUniform1f(nrMasterStrandVerticesLoc, (float)nrMasterStrands);

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
        regularShader();
        glUniformMatrix4fv(modelLocRegular, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLocRegular, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLocRegular, 1, GL_FALSE, glm::value_ptr(projection));

        triangle.render(false);
        //box.render(false);
        //sphere.render(false);

        glActiveTexture(GL_TEXTURE0 + 0); // Texture unit 0
        glBindTexture(GL_TEXTURE_2D, mainTexture.textureID);

        /************** Hair rendering **************/
        hairShader();
        glUniformMatrix4fv(modelLocHair, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLocHair, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLocHair, 1, GL_FALSE, glm::value_ptr(projection));

        ///*
        glActiveTexture(GL_TEXTURE0 + 0); // Texture unit 0
        glBindTexture(GL_TEXTURE_2D, mainTexture.textureID);
        // */

        ///*
        glActiveTexture(GL_TEXTURE0 + 1); // Texture unit 1
        glBindTexture(GL_TEXTURE_2D, hairDataTextureID);
        // */

        triangle.render(true);
        //box.render(true);
        //sphere.render(true);

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
// glfw: Whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glfwGetWindowSize( window, &width, &height );
    glViewport(0, 0, width, height);
}

// glfw: Whenever the mouse moves, this callback is called
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

    camera.ProcessMouseMovement(xOffset, yOffset);
    model = glm::translate(model, glm::vec3(0.f, yOffset*0.01f, -xOffset*0.01f));
}

// glfw: Whenever the mouse scroll wheel scrolls, this callback is called
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
    camera.ProcessMouseScroll(yOffset);
}

// Handle input from user
void processInput(GLFWwindow *window){
    // Terminate on ESC
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // Camera movement
    GLfloat cameraSpeed = deltaTime * 5.0f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        camera.ProcessKeyboard(FORWARD, cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        camera.ProcessKeyboard(BACKWARD, cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        camera.ProcessKeyboard(LEFT, cameraSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        camera.ProcessKeyboard(RIGHT, cameraSpeed);
    }
}

// Create Master strands of hair. These are used to then map texture to each strand of hair
GLuint createMasterStrands(const MeshObject& meshObject){
    GLfloat* vertexArray = meshObject.getVertexArray(); // VertexArray consists of vertices (3), normals (3) and texture (2)
    nrMasterStrands = meshObject.getNoOfVertices();

    // Size of new array, include all type of data (vertices, normal and texture)
    GLfloat* hairData = new GLfloat[nrMasterStrands * (nrHairSegments * 9)];

    int hairStrandIndex = 0;
    int stride = 8; // Since vertexArray consists of 8 different data types for each triangle on the object

    /*** Loop through the number of vertices and create the master strands ***/
    for(int i = 0; i < nrMasterStrands * stride; i = i + stride){
        glm::vec3 rootPos = glm::vec3(vertexArray[i], vertexArray[i+1], vertexArray[i+2]);      // The vertices
        glm::vec3 rootNormal = glm::vec3(vertexArray[i+3], vertexArray[i+4], vertexArray[i+5]); // The normals

        std::cout << "CMS: RootPos = " << glm::to_string(rootPos) << std::endl;
        //std::cout << "CMS: RootNormal = " << glm::to_string(rootNormal) << std::endl;

        // Add hair vertices
        for(int hairSegment = 1; hairSegment <= nrHairSegments; hairSegment++){
            glm::vec3 newPos = rootPos + lengthHairSegment * hairSegment * rootNormal; // xyz-pos
            //std::cout << "newPos = " << glm::to_string(newPos) << std::endl;

            // Add position to hair data (each coordinate has its own entry)
            hairData[hairStrandIndex++] = newPos.x;
            hairData[hairStrandIndex++] = newPos.y;
            hairData[hairStrandIndex++] = newPos.z;

            // Add normal
            /*
            hairData[hairStrandIndex++] = rootNormal.x;
            hairData[hairStrandIndex++] = rootNormal.y;
            hairData[hairStrandIndex++] = rootNormal.x;
             */
            ///*
            hairData[hairStrandIndex++] = vertexArray[i+3];
            hairData[hairStrandIndex++] = vertexArray[i+4];
            hairData[hairStrandIndex++] = vertexArray[i+5];
            // */

            // Add texture to hair data
            hairData[hairStrandIndex++] = vertexArray[i+6];
            hairData[hairStrandIndex++] = vertexArray[i+7];
            hairData[hairStrandIndex++] = 0.0f;

            std::cout << "CMS: newPos = " << glm::to_string(newPos) << std::endl;
        }
        std::cout << std::endl;
    }

    /*** Bind texture for the strands ***/
    GLuint hairDataTextureID;
    glGenTextures(1, &hairDataTextureID);
    glActiveTexture(GL_TEXTURE0); // Activate the texture unit first before binding texture
    glBindTexture(GL_TEXTURE_2D, hairDataTextureID);

    // Load and create another texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, nrHairSegments * 3, nrMasterStrands, 0, GL_RGB, GL_FLOAT, hairData);

    // Set parameters to determine how the texture is resized
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return hairDataTextureID;
}