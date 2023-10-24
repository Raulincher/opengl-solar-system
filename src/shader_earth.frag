#version 330

out vec4 fragColor;

in vec3 v_color;
in vec3 v_normal;
in vec3 v_vertex;

// STEP 3: get the uv coordinates form the vertex shader

in vec2 v_uv;

uniform sampler2D u_texture_spec;

uniform sampler2D u_texture_night;

uniform sampler2D u_texture_clouds;

uniform sampler2D u_texture;

uniform vec3 u_light_dir;
uniform vec3 u_cam_pos;
uniform float u_alpha;

uniform vec3 u_ambient;
uniform vec3 u_diffuse;
uniform vec3 u_specular;
uniform float u_shininess;


void main(void)
{
	// STEP 3: use the uv coordinates as colors
	vec3 texture_color = texture(u_texture, v_uv).xyz;   

	vec3 L = normalize(u_light_dir - v_vertex);
	vec3 N = normalize(v_normal);
	
	//phong ambient
	vec3 ambient_color = texture_color * u_ambient;

	//phong diffuse
	float NdotL = max ( dot (N,L) , 0.0 );
	vec3 diffuse_color = texture_color * NdotL;

	//phong specular
	vec3 R = normalize(-reflect(L, N) );
	vec3 E = normalize(u_cam_pos - v_vertex);
	float RdotE = max( dot(R,E) , 0.0 );

	vec3 spec_color = texture_color * pow (RdotE, u_shininess);

	vec3 texture_spec = texture(u_texture_spec, v_uv).xyz;

	vec3 texture_clouds = texture(u_texture_clouds, v_uv).xyz;

	vec3 texture_night = texture(u_texture_night, v_uv).xyz;

		if ( texture_color.x == 1.0 && texture_color.y == 1.0 && texture_color.z == 1.0)
	 discard;

	vec3 final_color = ambient_color + diffuse_color + spec_color * texture_spec * texture_clouds ;

	if (NdotL < 0.001)

		final_color = texture_night;

	fragColor = vec4(final_color, 1.0); 
	
}
