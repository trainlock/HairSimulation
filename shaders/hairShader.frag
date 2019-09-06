#version 410 core

/*** Uniform Variables ***/
uniform vec3 lightPos;
uniform vec3 lightColour;
uniform sampler2D mainTexture;

/*** Input Variables (from Geometry Shader) ***/
in vec2 gsTexCoord;

/*** Output Variables ***/
out vec4 color;

void main(){
    // TODO: Add light (Phong lighting model)

    //color = vec4(1.0f);
    color = vec4(vec3(texture(mainTexture, gsTexCoord)), 1.0);
}