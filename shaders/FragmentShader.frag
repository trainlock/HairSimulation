#version 330 core

out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D mainTexture;

void main(){
    fragColor = texture(mainTexture, texCoord);
    //fragColor = vec4(1.0f, 0.2f, 0.5f, 1.0f);
}