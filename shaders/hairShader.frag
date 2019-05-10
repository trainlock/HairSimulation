#version 330 core

uniform sampler2D mainTexture;

in vec2 texCoordGS;
out vec4 color;


void main(){
    color = vec4(vec3(texture(mainTexture, texCoordGS)), 1.0);
}