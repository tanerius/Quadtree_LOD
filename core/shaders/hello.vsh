#version 410

in vec3 position;
out vec3 color;

void main(void)
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);

    color = vec3(position.x + 0.5, 1.0, position.y + 0.5);
}