#version 150 

//these are the interpolated values out of the rasterizer, so you can't know
//their specific values without knowing the vertices that contributed to them
in vec3 fs_normal;
in vec3 fs_light_vector;
in vec3 fs_color;
in vec3 fs_camera;
in vec3 fs_light_color;

out vec4 out_Color;

void main() {
    //base colors for materials
    vec4 diffuseColor = vec4(fs_color, 1.0);
    vec4 ambientColor = vec4(0.5,0.2,0.2,1.0);
	vec4 specularColor = vec4(fs_light_color,1.0);
    //calculate diffuse term and clamp to the range [0, 1]
    float diffuseTerm = clamp(dot(normalize(fs_normal), normalize(fs_light_vector)), 0.0, 1.0);
    

	///specular highlight
	vec3 ref_light_vector = clamp(reflect(normalize(-fs_light_vector), normalize(fs_normal)), 0.0, 1.0);
	ref_light_vector = vec3((2 * normalize(fs_normal) * dot(normalize(fs_normal), normalize(fs_light_vector))) - fs_light_vector);

	float specularTerm = pow (max(dot(normalize(ref_light_vector),normalize(fs_camera)),0.0),60.0);

    out_Color = ambientColor + (diffuseColor +  specularColor) * (diffuseTerm + specularTerm);
}