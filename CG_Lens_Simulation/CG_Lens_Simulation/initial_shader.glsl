#ShaderType Vertex
#version 330 core
layout(location = 0) in vec4 positions;
void main() {
    gl_Position = positions;
}

#ShaderType Fragment
#version 330 core
layout(location = 0) out vec4 color;
void main()  {
    color = vec4(1.0,0.0,0.0,1.0);
}
