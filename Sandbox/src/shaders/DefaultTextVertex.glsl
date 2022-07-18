#version 330 core

layout (location = 0) in vec4 a_Position;
layout (location = 1) in vec2 a_TextureCoord;

out vec2 v_TextureCoord;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * a_Position;
    v_TextureCoord = a_TextureCoord;
}