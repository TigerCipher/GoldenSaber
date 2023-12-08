#version 430 core

// Input vertex data: position and texture mapping
layout(location = 0) in vec3 aPosition;
//layout(location = 2) in vec2 aTexCoord;

// Output vertex data: texture mapping
//out vec2 vTexCoord;

// main
void main()
{
    // Set the vertex position
    gl_Position = vec4(aPosition, 1.0);

    // Set the texture coordinate
    //vTexCoord = aTexCoord;
}