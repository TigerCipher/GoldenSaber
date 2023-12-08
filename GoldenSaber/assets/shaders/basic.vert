#version 430 core

// Input vertex data: position and texture mapping
layout(location = 0) in vec3 aPosition;
//layout(location = 2) in vec2 aTexCoord;

// Output vertex data: texture mapping
//out vec2 vTexCoord;

layout(location=0) uniform mat4 uProjView;

// main
void main()
{
    // Set the vertex position
    // TODO: Get world matrix transformation
    gl_Position = uProjView * vec4(aPosition, 1.0);

    // Set the texture coordinate
    //vTexCoord = aTexCoord;
}