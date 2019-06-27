#version 410 core
//RENDERING FUR USING TESSELLATION: https://interplayoflight.wordpress.com/2014/12/31/rendering-fur-using-tessellation/

/*** Layout ***/
layout (triangles) in;
layout (line_strip, max_vertices = 12) out;

/*** Input Variables (from Tesselation Evaluation Shader) ***/
in vec3 teNormal[3];
in vec2 teTexCoord[3]; // 3 => Triangle
in vec3 teVertexID[3]; // One point for each vertex in the triangle
in vec3 tessCoord[3];

/*** Output Variables (to Fragment Shader) ***/
out vec2 gsTexCoord;

/*** Uniform Variables ***/
uniform mat4 view;
uniform mat4 projection;
//uniform mat4 model;

uniform float nrHairSegments;
uniform float nrMasterStrands;
uniform sampler2D hairDataTexture;

/*** Variables ***/
const float MAGNITUDE = 0.4;
const int MAX_HAIR_INDEX = 4;

float offsetWidth = (1.0f / (nrHairSegments * 3.0f) ) * 0.5f;
float offsetHeight = (1.0f / nrMasterStrands) * 0.5f;

/*** Function Declerations ***/
vec3 getHairPositionFromTexture(float vertexIndex, int hairIndex);
vec3 interpolateHairSegments(int index, int hairIndex);
void generateHairStrands(int index);

/*** Main ***/
void main() {
    // Passthrough without altering the vertex positions
    for(int i = 0; i < gl_in.length(); i++){
        generateHairStrands(i);
    }
}

/*** Functions ***/
// Get position of hair from texture
vec3 getHairPositionFromTexture(float vertexIndex, int hairIndex){
    // Find position of the base of the hair strands
    vec2 hairStrandPosition = vec2(offsetWidth, (vertexIndex / nrMasterStrands) + offsetHeight);

    // Return hair position for current vertex
    return vec3(texture(hairDataTexture, hairStrandPosition));
}

// Get interpolated position of hair segment
vec3 interpolateHairSegments(int index, int hairIndex){
    vec3 hairStrandPos0 = getHairPositionFromTexture(teVertexID[index].x, hairIndex);
    vec3 hairStrandPos1 = getHairPositionFromTexture(teVertexID[index].y, hairIndex);
    vec3 hairStrandPos2 = getHairPositionFromTexture(teVertexID[index].z, hairIndex);

    vec3 hairPos =  tessCoord[index].x * hairStrandPos0 +
                    tessCoord[index].y * hairStrandPos1 +
                    tessCoord[index].z * hairStrandPos2;

    return hairPos;
}

// Generate the hair strand for the given index
void generateHairStrands(int index){
    // Generate master strand (base)
    gl_Position = gl_in[index].gl_Position;
    gsTexCoord = teTexCoord[index];
    EmitVertex();
    vec3 hairPos;

    // Generate hair segments
    for(int hairIndex = 0; hairIndex < MAX_HAIR_INDEX; hairIndex++){
        // Find vertex from tesselation texture
        hairPos = interpolateHairSegments(index, hairIndex);
        gl_Position = projection * view * vec4(hairPos, 1.0f);
        gsTexCoord = teTexCoord[index];
        EmitVertex();
    }
    EndPrimitive();
}