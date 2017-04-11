#version 410

in vec2 TexCoord;

out vec4 out_color;

uniform sampler2D textureSampler;

void main(void)
{
    out_color = texture(textureSampler,TexCoord);
}
