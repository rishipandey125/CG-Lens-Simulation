#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
 Shader Structure Containing GLSL Source Code and GL Shader Type
 */
struct Shader {
    std::string sourceCode;
    int shaderType;
};


/*
 Load Shader Function.
 */
Shader loadShader(std::string filePath) {
    //set to load just one shader, because sometimes we may only need 1, more efficient
    std::ifstream input(filePath);
    std::string line;
    std::stringstream shaderCode;
    int type = -1;
    bool typeFound = false;
    while (getline(input,line)) {
        if (!typeFound) {
            if (line.find("#ShaderType") != std::string::npos) {
                if(line.find("Vertex") != std::string::npos) {
                   //set to vertex
                    type = GL_VERTEX_SHADER;
                } else if (line.find("Fragment") != std::string::npos) {
                    //set to fragment
                    type = GL_FRAGMENT_SHADER;
                }
            }
            typeFound = true;
        } else {
            shaderCode << line << "\n";
        }
    }
    Shader shaderInfo;
    shaderInfo.sourceCode = shaderCode.str();
    shaderInfo.shaderType = type;
    return shaderInfo;
}

/*
 Compile Shader Function
 */
static unsigned int compileShader(unsigned int shaderType, const std::string &sourceCode) {
    unsigned int shaderID = glCreateShader(shaderType);
    const char* src = sourceCode.c_str();
    glShaderSource(shaderID, 1, &src, nullptr);
    glCompileShader(shaderID);
    int result;
    glGetShaderiv(shaderID,GL_COMPILE_STATUS, &result);
    //did the shader compile?
    if (result == GL_FALSE) {
        //which shader failed to compile?
        int typeResult;
        glGetShaderiv(shaderID,GL_SHADER_TYPE, &typeResult);
        if (typeResult == GL_VERTEX_SHADER) {
            std::cout << "Vertex Shader Failed to Compile" << std::endl;
        } else {
            std::cout << "Fragment Shader Failed to Compile" << std::endl;
        }
        std::cout << src << std:: endl;
        int logResultLength;
        glGetShaderiv(shaderID,GL_INFO_LOG_LENGTH,&logResultLength);
        char* message = (char*)alloca(logResultLength*sizeof(char));
        glGetShaderInfoLog(shaderID,logResultLength,&logResultLength,message);
        std::cout << "SHADER ERROR MESSAGE:" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(shaderID);
        return 0;
    }
    return shaderID;
}

/*
  Create Shader Function
 */
static unsigned int createShader(const std::string &vertexShader, const std::string &fragmentShader) {
    unsigned int program = glCreateProgram(); //creating a program
    unsigned int vShader = compileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fShader = compileShader(GL_FRAGMENT_SHADER,fragmentShader);
    glAttachShader(program,vShader);
    glAttachShader(program,fShader);
    glLinkProgram(program);
    glValidateProgram(program);
    
    //we delete because we linked them to a program, otherwise they are just sitting around
    glDeleteShader(vShader);
    glDeleteShader(fShader);
     
    return program;
}

int main() {
    glewExperimental = true; //Needed for core profile
    
    //initialize GLFW
    if (!glfwInit()) {
        std::cout << "FAILED to Initialize GLFW" << std::endl;
        return -1;
    }
    
    //Setting up OpenGL and Window
    glfwWindowHint(GLFW_SAMPLES, 4); //antialiasing 4x: minimizing distortion
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // We don't want the old OpenGL
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window; //creating a pntr to a window object
    window = glfwCreateWindow(1024, 768, "Triangle", NULL, NULL);
    
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
    //replaced with the two xy position of the viewport, and pass some additional info to calc z
    //use the vertex shader to calc z, pass, xyz
    
    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f,
    };
    
    unsigned int buffer; //buffer reference
    unsigned int index = 0;
    //Buffers just hold data for OpenGL, you have to create one for the positions
    glGenBuffers(1,&buffer); //specifies how many buffers to generate
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions),positions,GL_STATIC_DRAW);
    
    //Stores Vertex Data for OpenGL
    unsigned int vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    glEnableVertexAttribArray(index);
    //sizeof(float)*2 dictates data to vertices
    glVertexAttribPointer(index,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);
    Shader vertexShader = loadShader(
                                           "/Users/rishipandey125/Documents/GitHub/Shader-Programming/CG_Lens_Simulation/CG_Lens_Simulation/initial_vertex.glsl");
    Shader fragmentShader = loadShader(
                                           "/Users/rishipandey125/Documents/GitHub/Shader-Programming/CG_Lens_Simulation/CG_Lens_Simulation/initial_fragment.glsl");

    unsigned int shader = createShader(vertexShader.sourceCode,fragmentShader.sourceCode);
    glUseProgram(shader);
    //how do we get the fragment shader to write to the rgb array? 
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    while(glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 ) {
        //clear screen to avoid flickering
        glClear( GL_COLOR_BUFFER_BIT );

        glDrawArrays(GL_TRIANGLES,0,3); //gl draw points to return given pixel from fragment shader
    

        glEnd();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(shader);

    return 0;
}

