#version 410 core
/*** Locations ***/
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 TexCoord;

/*** Uniform Variables ***/
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

/*** Output Variables ***/
out vec2 texCoord;
out vec3 vNormal;
out vec3 vPosition;

/*** Main ***/
void main(){
    gl_Position = projection * view * vec4(position, 1.0);
    //gl_Position = projection * view * model * vec4(position, 1.0);

    texCoord = TexCoord;
    vNormal = normal;
    vPosition = position;
}