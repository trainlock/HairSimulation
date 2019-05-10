#version 330 core

uniform sampler2D mainTexture;

in vec2 texCoord;
out vec4 color;


void main(){
    //color = texture(mainTexture, texCoord);
    color = vec4(vec3(texture(mainTexture, texCoord)), 1.0);
    //fragColor = vec4(1.0f, 0.2f, 0.5f, 1.0f);
}