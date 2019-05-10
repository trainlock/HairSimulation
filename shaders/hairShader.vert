#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 TexCoord;

uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;

void main(){
    gl_Position = projection * view * vec4(position, 1.0);
    texCoord = TexCoord;
}