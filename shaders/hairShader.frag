#version 410 core

/*** Uniform Variables ***/
uniform sampler2D mainTexture;

/*** Input Variables (from Geometry Shader) ***/
in vec2 gsTexCoord;

/*** Output Variables ***/
out vec4 color;

void main(){
    color = vec4(1.0f);
    //color = vec4(vec3(texture(mainTexture, gsTexCoord)), 1.0);
}