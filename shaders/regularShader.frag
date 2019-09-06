#version 410 core

/*** Uniform Variables ***/
uniform vec3 cameraPos;
uniform vec3 lightPos;
uniform vec3 lightColour;
uniform sampler2D mainTexture;

/*** Input Variables ***/
in vec2 texCoord;
in vec3 vNormal;
in vec3 vPosition;

/*** Output Variables ***/
out vec4 color;

/*** Main ***/
void main(){
    // TODO: Add Phong lightning

    /*
    // Add Phong Lighting Model
    vec3 lightDir = lightPos - vPosition;
    vec3 viewDir = cameraPos - vPosition;
    vec3 interpolatedNormal = normalize(vNormal);

    vec3 L = normalize(lightDir);
    vec3 V = normalize(viewDir); //vec3(0.0, 0.0, 1.0);
    vec3 N = interpolatedNormal;
    vec3 R = 2.0 * dot(N,L) * N - L;
    float alpha = 32; // shininess

    vec3 ka = 0.1 + vec3(texture(mainTexture, texCoord)); // vec3(0.3, 0.3, 0.3) + vec3(texture(mainTexture, texCoord));
    vec3 Ia = vec3(0.8, 0.8, 0.8);

    vec3 kd = vec3(texture(mainTexture, texCoord));
    vec3 Id = vec3(0.7, 0.7, 0.7);

    float ks = 0.5; // lightColour; // vec3(1.0, 1.0, 1.0);
    vec3 Is = lightColour; //vec3(1.0, 1.0, 1.0);

    float dotNL = max(dot(N, L), 0.0);
    float dotRV = max(dot(R, V), 0.0);

    if(dotNL == 0.0) dotRV = 0.0;

    vec3 ambient = Ia * ka;
    vec3 diffuse = Id * kd * dotNL;
    vec3 specular = Is * ks * pow(dotRV, alpha);

    // Calculate Phong
    vec3 shadedColour = ambient + diffuse + specular;
    color = vec4(shadedColour, 1.0);
    */

    ///*
    // Add Phong Lightning Model
    // Ambient lightning
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColour; // vec3(texture(mainTexture, texCoord));

    // Diffuse lightning
    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(lightPos - vPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColour; // vec3(texture(mainTexture, texCoord));

    // Specular lightning
    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - vPosition);
    vec3 reflectionDir = reflect(-lightDir, norm);
    int shininess = 32;
    float spec = pow(max(dot(viewDir, reflectionDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColour;

    // Calculate Phong
    vec3 phong = (ambient + diffuse + specular) * vec3(texture(mainTexture, texCoord));
    color = vec4(phong, 1.0);
    //*/
}