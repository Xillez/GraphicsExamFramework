#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 diffuse; 
uniform sampler2D texture_diffuse1;
uniform vec3 color;


void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords) * vec4(color, 1.0);
	FragColor = vec4(texture(texture_diffuse1, TexCoords).rgb * color * diffuse, 1.0);
}