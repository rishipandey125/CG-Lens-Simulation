#include <iostream>
//path tracing with lens distortion and materials
//virtual photobooth basically
//adding GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//adding GLFW (focused more on windows)
#include <GLFW/glfw3.h>

int main() {
    glewExperimental = true; //Needed for core profile
    
    //initialize GLFW
    if (!glfwInit()) {
        std::cout << "FAILED to Initialize GLFW" << std::endl;
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4); //antialiasing 4x: minimizing distortion
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // We don't want the old OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window; //creating a pntr to a window object
    window = glfwCreateWindow(1024, 768, "Project 1", NULL, NULL);
    
    if( window == NULL ) {
        std::cout << "FAILED to Open GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    
    if (glewInit() != GLEW_OK) {
        std::cout << "FAILED to Initialize GLEW" << std::endl;
        return -1;
    }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 ) {
        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear( GL_COLOR_BUFFER_BIT );
        
        //do ur graphics here
        //load a simple geometry
        //light the scene (inside or outside shader?)
        //write some shaders
        
        //change
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}
