#version 330

out vec4 fragColor;

in vec3 v_color;
in vec3 v_normal;
in vec3 v_vertex;

// STEP 3: get the uv coordinates form the vertex shader

in vec2 v_uv;

uniform sampler2D u_texture;



void main(void)
{
	vec4 texture_color = texture(u_texture, v_uv);
	// STEP 3: use the uv coordinates as colors
    // STEP 8: get the color from the texture
	fragColor = vec4(texture_color.xyz, 1.0);   
}
