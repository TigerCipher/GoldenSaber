#version 430 core

// Input vertex data: position and texture mapping
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in float aTexIndex;


layout(location=0) uniform mat4 uProjView;

layout(location=0)out vec2 oTexCoord;
layout(location=1)out float oTexIndex;

void main()
{
    gl_Position = uProjView * vec4(aPosition, 1.0);
    oTexCoord = aTexCoord;
    oTexIndex = aTexIndex;
}