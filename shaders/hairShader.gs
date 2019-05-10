#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec2 texCoord[3];
out vec2 texCoordGS;

void main() {
    // Passthrough without altering the vertex positions
    for(int i = 0; i < gl_in.length(); i++){
        gl_Position = gl_in[i].gl_Position;
        texCoordGS = texCoord[i];
        EmitVertex();
    }
    EndPrimitive();
}