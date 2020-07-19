#include <iostream>

//adding GLEW
#define GLEW_STATIC
#include <GL/glew.h>

//adding GLFW
#include <GLFW/glfw3.h>

static int createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    return 0;
}

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
    //2d vertex positions of triangle
    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };
    
    unsigned int buffer; //buffer reference
    glGenBuffers(1,&buffer); //generates a single buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffer); //
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions),positions,GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0); //sizeof(float)*2 dictates data to vertices
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 ) {
        //clear screen to avoid flickering
        glClear( GL_COLOR_BUFFER_BIT );
        glDrawArrays(GL_TRIANGLES,0,3); 
    
        glEnd();
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    return 0;
}
