#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

/*Reference: https://learnopengl.com/code_viewer.php?code=lighting/basic_lighting-exercise2*/
/*https://learnopengl.com/Lighting/Basic-Lighting*/

vec3 Diffuse(){
	vec3 lightDir = normalize(lightPos - FragPos); //
        vec3 norm = normalize(Normal); //normalize to get a unit vector form
	float diff = max(dot(norm, lightDir), 0.0); // impact of the light
	return diff * lightColor; //darker diffuse
}

vec3 Specular(){
	vec3 lightDir = normalize(lightPos - FragPos);
        vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	int shininess = 32; 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	return (0.5 * spec * lightColor);
}

void main(){
        //0.1 is used as a small constant ambient factor
        vec3 ambient  = (0.1 * lightColor) * objectColor;
	vec3 diffuse  = Diffuse();
	vec3 specular = Specular();
	vec3 rgb = (ambient + diffuse + specular) * objectColor;
	color = vec4(rgb, 1.0);
} 

