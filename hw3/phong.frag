#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

/*Reference: https://learnopengl.com/code_viewer.php?code=lighting/basic_lighting-exercise2*/

vec3 Diffuse(){
	vec3 lightDir = normalize(lightPos - FragPos);
  vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightDir), 0.0);
	return diff * lightColor;
}

vec3 Specular(){
	vec3 lightDir = normalize(lightPos - FragPos);
  vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	return (0.5 * spec * lightColor);
}

void main(){
  vec3 ambient  = (0.1 * lightColor) * objectColor;
	vec3 diffuse  = Diffuse();
	vec3 specular = Specular();
	vec3 rgb = (ambient + diffuse + specular) * objectColor;
	color = vec4(rgb, 1.0);
} 

