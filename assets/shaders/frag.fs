#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec2 u_res;
uniform vec2 u_mouse;
uniform float u_time;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(TexCoord.x, -TexCoord.y)), 0.7);
}
