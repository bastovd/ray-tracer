#version 150

//there's no rules about the prefixes but they do help
//keep track of things
uniform mat4 u_modelMatrix;
uniform mat4 u_projMatrix;
uniform vec3 lightPos;
uniform vec3 camV;
uniform vec3 lightCol;

in vec4 vs_normal;
in vec4 vs_position;
in vec3 vs_color;

out vec3 fs_normal;
out vec3 fs_light_vector;
out vec3 fs_color;
out vec3 fs_camera;
out vec3 fs_light_color;

void main() {
// light source is fixed here. Make it an uniform if you want to change it.
//const vec3 lightPos = vec3(-3.0, -20.0, 50.0);
const vec3 camPos = vec3(0.0,5.0,10.0);
const vec3 cenPos = vec3(0.0,0.0,0.0);

// Set the color and normal as just the input from the VBOs,
// they only get interesting after they've been interpolated by the rasterizer
fs_color = vs_color;
fs_normal = (transpose(inverse(u_modelMatrix)) * vs_normal).xyz;

// Set up our vector for the light
fs_light_vector = vec3(lightPos - (u_modelMatrix * vs_position).xyz);
fs_camera = normalize(vec3(cenPos - camPos));

//fs_color = fs_light_vector;

fs_light_color = lightCol; //light color

//built-in things to pass down the pipeline
gl_Position = u_projMatrix * u_modelMatrix * vs_position;
}


