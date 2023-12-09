#version 430 core

// Input vertex data: position and texture mapping
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;


layout(location=0) uniform mat4 uProjView;
layout(location=1) uniform mat4 uModel;

layout(location=0)out vec2 oTexCoord;

void main()
{
    vec4 model = uModel * vec4(aPosition, 1.0);
    gl_Position = uProjView * model;
    oTexCoord = aTexCoord;
}