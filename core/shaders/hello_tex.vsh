#version 410

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
out vec2 TexCoord;

void main(void)
{
    gl_Position = vec4(position, 1.0f);
    TexCoord = textureCoords;
}
