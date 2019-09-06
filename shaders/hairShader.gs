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
const float GRAVITY = -9.82;

float offsetWidth = (1.0f / (nrHairSegments * 3.0f) ) * 0.5f;
float offsetHeight = (1.0f / nrMasterStrands) * 0.5f;

/*** Function Declerations ***/
vec3 getHairPositionFromTexture(float vertexIndex, int hairIndex);
vec3 interpolateHairSegments(int index, int hairIndex);
void generateHairStrands(int index);

/*** Main ***/
void main() {
    //gsNormal = vec3(teNormal.x, teNormal.y, teNormal.z);

    // Passthrough without altering the vertex positions
    for(int i = 0; i < gl_in.length(); i++){
        generateHairStrands(i);
    }
}

/*** Functions ***/
// Get position of hair from texture
vec3 getHairPositionFromTexture(float vertexIndex, int hairIndex){
    // Find position of the base of the hair strands
    // Change position according to which segment and the number of vertices
    vec2 hairStrandPosition = vec2((hairIndex / nrHairSegments) + offsetWidth, (vertexIndex / nrMasterStrands) + offsetHeight);

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

// Generate the hair strand for the given index, only one hair strand at a time
void generateHairStrands(int index){
    // Variables
    vec3 baseHairPos;
    vec3 currHairPos; // Hair Segment Pos
    vec3 nextHairPos; // Hair Segment Pos
    vec3 velocity;
    float forces = 1.0; // GRAVITY;
    float dt = 0.1; // Time step

    // TODO: Precompute rest-state values (DONE)

    // Generate master strand (base), non-movable
    vec3 prevHairPos = (gl_in[index].gl_Position).xyz;
    vec3 firstHairPos = interpolateHairSegments(index, 0);

    gl_Position = projection * view * vec4(firstHairPos, 1.0f);
    gsTexCoord = teTexCoord[index];
    baseHairPos = prevHairPos;
    prevHairPos = firstHairPos;
    EmitVertex(); // Might not need YET

    // TODO: While simulation running do...
    // Generate hair segments
    for(int hairIndex = 1; hairIndex < MAX_HAIR_INDEX; hairIndex++){
        // TODO: Compute forces such as gravity or wind
        // Pi0 = firstHairSegmentPos

        // hairPos = currentHairPos;
        currHairPos = interpolateHairSegments(index, hairIndex);

        // TODO: Integrate with Verlet integration scheme
        // Skip first position (master position)
        velocity = currHairPos - prevHairPos;
        nextHairPos = currHairPos + velocity + forces * pow(dt, 2);
        prevHairPos = currHairPos;

        // TODO: Apply global shape constraints
        // Pi = Sg(H * Pi0 - Pi)

        // TODO: Apply local shape constraints (while iterating)

        // TODO: Apply edge length constraints
        // TODO: Collision handling


        gl_Position = projection * view * vec4(nextHairPos, 1.0f);
        gsTexCoord = teTexCoord[index];
        EmitVertex();
    }
    EndPrimitive();
}