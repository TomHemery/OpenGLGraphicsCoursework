#version 330 core
//fragment shader used by all lit objects 
//outputs a fragment colour 
out vec4 FragColor;

//struct used to represent a material internally
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
//struct used to represent a directional light
struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
//struct to represent a point light
struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
//sadly we have a static number of point lights (currently)
#define MAX_POINT_LIGHTS 32

//take in frag position, normal, and tex coordinates from the vertex shader 
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

//take in this stuff from the program
uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int numPointLights = 0;
uniform Material material;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

//blends texture and lighting together to work out colour
void main()
{    
	//extract the plain text colour
	vec4 texColor = texture(material.diffuse, TexCoords);
	//discard alpha < 0.1 fragments for transparency 
    if(texColor.a < 0.1){
        discard;
	}

	else{
		// properties
		vec3 norm = normalize(Normal);
		vec3 viewDir = normalize(viewPos - FragPos);

		// phase 1: directional lighting
		vec3 result = CalcDirLight(dirLight, norm, viewDir);
		// phase 2: point lights
		for(int i = 0; i < numPointLights && i < MAX_POINT_LIGHTS; i++)
			result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    

		FragColor = vec4(result, 1.0);
	}
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}