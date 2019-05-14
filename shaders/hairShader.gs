#version 410 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec2 teTexCoord[3]; // 3 => Trianlge
out vec2 gsTexCoord;

void main() {
    // Passthrough without altering the vertex positions
    for(int i = 0; i < gl_in.length(); i++){
        gl_Position = gl_in[i].gl_Position;
        gsTexCoord = teTexCoord[i];
        EmitVertex();
    }
    EndPrimitive();
}