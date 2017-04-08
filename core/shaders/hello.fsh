#version 410 core

in vec3 color;
out vec4 out_color;

void main(void)
{
    out_color = vec4(color, 1.0);
}
