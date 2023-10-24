#version 330
 
in vec3 a_vertex;
in vec3 a_color;
in vec3 a_normal;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

// STEP 2: add a attribute: a_uv and varying v_uv here

in vec2 a_uv;
out vec2 v_uv;

out vec3 v_color;
out vec3 v_vertex;
out vec3 v_normal;

void main()
{
	gl_Position = u_projection * u_view * u_model * vec4(a_vertex,1.0);

	v_normal = a_normal;
	v_vertex = a_vertex; 

	// pass the colour to the fragment shader
	v_color = a_color;


    // STEP 2: pass the uv coordinates to the fragment shader
	v_uv = a_uv;

}

