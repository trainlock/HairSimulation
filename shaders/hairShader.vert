#version 410 core
/*** Locations ***/
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

/*** Output Variables (to Tesselation Control Shader) ***/
out vec3 vsNormal;
out vec2 vsTexCoord;
out float vsVertexID;

/*** Uniform Variables ***/
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// TODO: Add constrains to the hair

/*** Main ***/
void main(){
    //gl_Position = projection * view * vec4(position, 1.0);
    gl_Position = vec4(position, 1.0);
    vsTexCoord = texCoord;

    // Calculate the normals normals
    //mat3 normalMatrix = mat3(transpose(inverse(view)));
    //vsNormal = normalize(vec3(projection * vec4(normalMatrix * normal, 0.0)));
    vsNormal = normalize(normal);

    // Index of associated vertices
    vsVertexID = gl_VertexID;
}