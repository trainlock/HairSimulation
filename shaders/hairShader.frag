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
    //vec3 lightDir = normalize(lightPos - gl_Position);
    // Ambient light
    float amibientStrength = 0.1;
    vec3 amibient = amibientStrength * lightColour;

    // Diffuse light
    //vec3 normal = normalize(gsNormal);

    //color = vec4(1.0f);
    color = vec4(vec3(texture(mainTexture, gsTexCoord)), 1.0);
}