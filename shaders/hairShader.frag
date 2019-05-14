#version 410 core

uniform sampler2D mainTexture;

in vec2 gsTexCoord;
out vec4 color;


void main(){
    color = vec4(vec3(texture(mainTexture, gsTexCoord)), 1.0);
}