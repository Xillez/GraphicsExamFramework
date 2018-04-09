#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in float diffuse; 

uniform vec3 color;
uniform sampler2D texture_diffuse1;

void main()
{    
    FragColor = texture(texture_diffuse1, TexCoords);// * vec4(color,0.0f);
	//FragColor = vec4(texture(texture_diffuse1, TexCoords).rgb * diffuse, 1.0);
}