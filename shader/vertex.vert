#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 aPos0;
out vec3 aNormal0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normalMatrix; 

uniform float attenuationA;
uniform float attenuationB;
uniform float attenuationC;

uniform float ambientCoefficient;
uniform int specularExponent;

uniform vec3 lightColor;
uniform vec3 lightSourcePosition;
uniform vec3 CamPos;

out vec3 ambient;
out vec3 diffuse;
out vec3 specular;
out vec2 TexCoords;



// this function specifies spreading of light. 
vec3 diffuseComponent(){
	
    // diffuse
    vec3 normal = normalize(normalMatrix * normalize(aNormal)); // calculate normals in eye space.
    vec3 surfacePos = vec3(model * vec4(aPos0, 1)); // Get the vertex position according model of the world.
    vec3 surfaceToLight = normalize(lightSourcePosition - aPos0);    // distance between surface to lightsource.

    float diffuseCoefficient = max(0.0, dot(normal, surfaceToLight)); // brightness.
    vec3 diff = diffuseCoefficient * vec3(attenuationA, attenuationB, attenuationC); 

    return diff;
}

// this function specifies minimum brightness
vec3 ambientComponent(){
    return ambientCoefficient * vec3(attenuationA, attenuationB, attenuationC);
}

// this function specifies shininess.
vec3 specularComponent(){

    vec3 incidenceVector = normalize(aPos0 - lightSourcePosition);
    vec3 reflectionVector = reflect(incidenceVector, aNormal0);
    vec3 surfaceToCamera = normalize(CamPos - aPos0);
    float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
    float specularCoefficient = pow(cosAngle, specularExponent);

    vec3 specularComponent = specularCoefficient * lightColor * vec3(attenuationA, attenuationB, attenuationC);
    return specularComponent;
}

void main()
{   
    aPos0 = vec3((model * vec4(aPos, 0.0f)));
    aNormal0 = normalize(vec3((model * vec4(aNormal,0.0f))));
    ambient = ambientComponent();
    diffuse = diffuseComponent();
    specular = specularComponent();
	TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}