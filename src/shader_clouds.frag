#version 330

out vec4 fragColor;

in vec3 v_color;

// TODO: get the uv coordinates form the vertex shader
in vec2 v_uv;


uniform sampler2D u_texture;


//TODO: get the texture sampler


//TODO: get the alpha value
uniform float u_alpha;

void main(void)
{
    // TODO: Get the color from the texture sampler

	vec4 texture_color = texture(u_texture, v_uv);
	fragColor = vec4(texture_color.xyz, 1.0);

	// TODO: If the color is white then we consider it as the transparent part of the texture and discard the color.
	if ( texture_color.x == 1.0 && texture_color.y == 1.0 && texture_color.z == 1.0)
	 discard;


   // TODO: change to the color of the texture
   // TODO: change the alpha

	fragColor = vec4(1.0,1.0,1.0,1.0); 
	fragColor = vec4(texture_color.xyz, u_alpha);
	
}
