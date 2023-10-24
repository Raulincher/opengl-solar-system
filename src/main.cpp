/*  by Alun Evans 2016 LaSalle (aevanss@salleurl.edu) */

/*Edited by Raúl Luque Sanmartín & Carlos Dalghi Bellart*/

//include some standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

//include OpenGL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>

//STEP 5: INCLUDE THE imageloader

#include "imageloader.h"

//include some custom code files
#include "glfunctions.h" //include all OpenGL stuff
#include "Shader.h" // class to compile shaders
#include <string>
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

using namespace std;
using namespace glm;

string basepath = "assets/";
string inputfile = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes;    
vector< tinyobj::material_t > materials;

string inputfile2 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes2;
vector< tinyobj::material_t > materials2;

string inputfile3 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes3;
vector< tinyobj::material_t > materials3;

string inputfile4 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes4;
vector< tinyobj::material_t > materials4;

string inputfile5 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes5;
vector< tinyobj::material_t > materials5;

string inputfile6 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes6;
vector< tinyobj::material_t > materials6;

string inputfile7 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes7;
vector< tinyobj::material_t > materials7;

string inputfile8 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes8;
vector< tinyobj::material_t > materials8;

string inputfile9 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes9;
vector< tinyobj::material_t > materials9;

string inputfile10 = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes10;
vector< tinyobj::material_t > materials10;

string inputfile_moon = basepath + "sphere.obj";
vector< tinyobj::shape_t > shapes_moon;
vector< tinyobj::material_t > materials_moon;

string inputfile_star = basepath + "star.obj";
vector< tinyobj::shape_t > shapes_star;
vector< tinyobj::material_t > materials_star;

//global variables to help us do things
int g_ViewportWidth = 512; int g_ViewportHeight = 512; // Default window size, in pixels
double mouse_x, mouse_y; //variables storing mouse position
const vec3 g_backgroundColor(0.2f, 0.2f, 0.2f); // background colour - a GLM 3-component vector

vec3 g_light_dir (10.0, 0, 10.0);
vec3 g_light_dir_venus (5.0, 0, 10.0);

GLuint g_simpleShader_all = 0; //shader identifier
GLuint g_Vao = 0; //vao
GLuint g_NumTriangles = 0; //  Numbre of triangles we are painting.

GLuint g_simpleShader_earth = 0;
GLuint g_simpleShader_sun = 0;

GLuint texture_id_earth;
GLuint texture_id_sun;
GLuint texture_id_milky;
GLuint texture_id_earth_spec;
GLuint texture_id_earth_night;
GLuint texture_id_venus;
GLuint texture_id_mars;
GLuint texture_id_saturn;
GLuint texture_id_mercury;
GLuint texture_id_uranus;
GLuint texture_id_neptune;
GLuint texture_id_jupiter;
GLuint texture_id_moon;


float speed = 0.15f;

vec3 eye = vec3(0.0f, 0.0f, 3.0f);
vec3 center = vec3(0.0f, 0.0f, -1.0f);
vec3 up = vec3(0.0f, 1.0f, 0.0f);

float mouseSpeed = 0.005f;



float Yaw = -90.0f;
float Pitch = 0.0f;
vec3 direction_mouse;
float direction_mouse_x = cos(radians(Yaw)) * cos(radians(Pitch));
float direction_mouse_y = sin(radians(Pitch));
float direction_mouse_z = sin(radians(Yaw)) * cos(radians(Pitch));

float sensibilidad = 0.1f;

int aux = 1;

float lastX = 0.0f;
float lastY = 0.0f;
float offset_x = 0.0f;
float offset_y = 0.0f;

GLuint g_simpleShader_sky = 0; //shader identifier
GLuint g_Vao_sky = 0; //vao
GLuint g_NumTriangles_sky = 0; // Number of triangles we are painting.

GLuint g_simpleShader_clouds = 0; //shader identifier

GLuint g_Vao_sun = 0; //vao
GLuint g_NumTriangles_sun = 0; //  Numbre of triangles we are painting.

GLuint g_Vao_venus = 0; //vao
GLuint g_NumTriangles_venus = 0; //  Numbre of triangles we are painting.

GLuint g_Vao_mars = 0; //vao
GLuint g_NumTriangles_mars = 0; //  Numbre of triangles we are painting.

GLuint g_Vao_saturn = 0; //vao
GLuint g_NumTriangles_saturn = 0; //  Numbre of triangles we are painting.

GLuint g_Vao_mercury = 0; //vao
GLuint g_NumTriangles_mercury = 0; //  Numbre of triangles we are painting.

GLuint g_Vao_uranus = 0; //vao
GLuint g_NumTriangles_uranus = 0; //  Numbre of triangles we are painting.

GLuint g_Vao_neptune = 0; //vao
GLuint g_NumTriangles_neptune = 0; //  Numbre of triangles we are painting.

GLuint g_Vao_jupiter = 0; //vao
GLuint g_NumTriangles_jupiter = 0; //  Numbre of triangles we are painting.

GLuint g_Vao_moon = 0; //vao
GLuint g_NumTriangles_moon = 0; //  Numbre of triangles we are painting.

GLuint g_Vao_star = 0; //vao
GLuint g_NumTriangles_star = 0; //  Numbre of triangles we are painting.

//STEP 6: add a global variable for the texture ID

// ------------------------------------------------------------------------------------------
// This function manually creates a square geometry (defined in the array vertices[])
// ------------------------------------------------------------------------------------------
void load()
{
	//**********************
	// CODE TO SET GEOMETRY
	//**********************

	string err;
	//load the OBJ file to shapes
	bool  ret = tinyobj::LoadObj(shapes, materials, err, inputfile.c_str(), basepath.c_str());
	ret = tinyobj::LoadObj(shapes2, materials2, err, inputfile2.c_str(), basepath.c_str());
	ret = tinyobj::LoadObj(shapes3, materials3, err, inputfile3.c_str(), basepath.c_str());
	ret = tinyobj::LoadObj(shapes4, materials4, err, inputfile4.c_str(), basepath.c_str());
	ret = tinyobj::LoadObj(shapes5, materials5, err, inputfile5.c_str(), basepath.c_str());
	ret = tinyobj::LoadObj(shapes6, materials6, err, inputfile6.c_str(), basepath.c_str());
	ret = tinyobj::LoadObj(shapes7, materials7, err, inputfile7.c_str(), basepath.c_str());
	ret = tinyobj::LoadObj(shapes8, materials8, err, inputfile8.c_str(), basepath.c_str());
	ret = tinyobj::LoadObj(shapes9, materials9, err, inputfile9.c_str(), basepath.c_str());
	ret = tinyobj::LoadObj(shapes10, materials10, err, inputfile10.c_str(), basepath.c_str());
	ret = tinyobj::LoadObj(shapes_moon, materials_moon, err, inputfile_moon.c_str(), basepath.c_str());
	ret = tinyobj::LoadObj(shapes_star, materials_star, err, inputfile_star.c_str(), basepath.c_str());



	//we assign a colour to each vertex (all of the vertices as assigned WHITE)
	vector<GLfloat> colors(shapes[0].mesh.positions.size(), 1.0);

	//test if OBJ loaded correctly
	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << std::endl;
	}
	else
		//print out number of meshes described in file
		std::cout << "Loaded " << inputfile << " with shapes: " << shapes.size() << std::endl;



	//**********************
	// CODE TO LOAD EVERYTHING INTO MEMORY
	//**********************

	//load the shader
	Shader simpleShader_all("src/shader.vert", "src/shader_all.frag");
	g_simpleShader_all = simpleShader_all.program;

	Shader simpleShader_earth("src/shader.vert", "src/shader_earth.frag");
	g_simpleShader_earth = simpleShader_earth.program;

	Shader simpleShader_sun("src/shader.vert", "src/shader_sun.frag");
	g_simpleShader_sun = simpleShader_sun.program;

	Shader simpleShader_sky("src/shader_sky.vert", "src/shader_sky.frag");
	g_simpleShader_sky = simpleShader_sky.program;

	// Create the VAO where we store all geometry (stored in g_Vao)
	g_Vao = gl_createAndBindVAO();

	// Bind the vectors/arrays to the attributes in the shaders 
	gl_createAndBindAttribute(&(shapes[0].mesh.positions[0]), shapes[0].mesh.positions.size() * sizeof(float), g_simpleShader_earth, "a_vertex", 3);
	gl_createAndBindAttribute(&(colors[0]), colors.size() * sizeof(GLfloat), g_simpleShader_earth, "a_color", 3);
	gl_createIndexBuffer(&(shapes[0].mesh.indices[0]), shapes[0].mesh.indices.size() * sizeof(unsigned int));
	gl_createAndBindAttribute(&(shapes[0].mesh.normals[0]), shapes[0].mesh.normals.size() * sizeof(float), g_simpleShader_earth, "a_normal", 3);
	gl_createAndBindAttribute(&(shapes[0].mesh.texcoords[0]), shapes[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_earth, "a_uv", 2);



	// STEP 1: create a VBO for the texture coordinates

	gl_unbindVAO();

	g_NumTriangles = shapes[0].mesh.indices.size() / 3;

	g_Vao_sky = gl_createAndBindVAO();

	gl_createAndBindAttribute(&(shapes2[0].mesh.positions[0]), shapes2[0].mesh.positions.size() * sizeof(float), g_simpleShader_sky, "a_vertex", 3);

	gl_createIndexBuffer(&(shapes2[0].mesh.indices[0]), shapes2[0].mesh.indices.size() * sizeof(unsigned int));

	gl_createAndBindAttribute(&(shapes2[0].mesh.texcoords[0]), shapes2[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_sky, "a_uv", 2);

	gl_unbindVAO();

	g_NumTriangles_sky = shapes2[0].mesh.indices.size() / 3;


	g_Vao_sun = gl_createAndBindVAO();

	gl_createAndBindAttribute(&(shapes3[0].mesh.positions[0]), shapes3[0].mesh.positions.size() * sizeof(float), g_simpleShader_sun, "a_vertex", 3);

	gl_createIndexBuffer(&(shapes3[0].mesh.indices[0]), shapes3[0].mesh.indices.size() * sizeof(unsigned int));

	gl_createAndBindAttribute(&(shapes3[0].mesh.texcoords[0]), shapes3[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_sun, "a_uv", 2);

	gl_createAndBindAttribute(&(shapes3[0].mesh.normals[0]), shapes3[0].mesh.normals.size() * sizeof(float), g_simpleShader_sun, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_sun = shapes3[0].mesh.indices.size() / 3;


	g_Vao_venus = gl_createAndBindVAO();

	gl_createAndBindAttribute(&(shapes4[0].mesh.positions[0]), shapes4[0].mesh.positions.size() * sizeof(float), g_simpleShader_sun, "a_vertex", 3);

	gl_createIndexBuffer(&(shapes4[0].mesh.indices[0]), shapes4[0].mesh.indices.size() * sizeof(unsigned int));

	gl_createAndBindAttribute(&(shapes4[0].mesh.texcoords[0]), shapes4[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_sun, "a_uv", 2);

	gl_createAndBindAttribute(&(shapes4[0].mesh.normals[0]), shapes4[0].mesh.normals.size() * sizeof(float), g_simpleShader_sun, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_venus = shapes4[0].mesh.indices.size() / 3;


	g_Vao_mars = gl_createAndBindVAO();

	gl_createAndBindAttribute(&(shapes5[0].mesh.positions[0]), shapes5[0].mesh.positions.size() * sizeof(float), g_simpleShader_sun, "a_vertex", 3);

	gl_createIndexBuffer(&(shapes5[0].mesh.indices[0]), shapes5[0].mesh.indices.size() * sizeof(unsigned int));

	gl_createAndBindAttribute(&(shapes5[0].mesh.texcoords[0]), shapes5[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_sun, "a_uv", 2);

	gl_createAndBindAttribute(&(shapes5[0].mesh.normals[0]), shapes5[0].mesh.normals.size() * sizeof(float), g_simpleShader_sun, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_mars = shapes5[0].mesh.indices.size() / 3;


	g_Vao_saturn = gl_createAndBindVAO();

	gl_createAndBindAttribute(&(shapes6[0].mesh.positions[0]), shapes6[0].mesh.positions.size() * sizeof(float), g_simpleShader_sun, "a_vertex", 3);

	gl_createIndexBuffer(&(shapes6[0].mesh.indices[0]), shapes6[0].mesh.indices.size() * sizeof(unsigned int));

	gl_createAndBindAttribute(&(shapes6[0].mesh.texcoords[0]), shapes6[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_sun, "a_uv", 2);

	gl_createAndBindAttribute(&(shapes6[0].mesh.normals[0]), shapes6[0].mesh.normals.size() * sizeof(float), g_simpleShader_sun, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_saturn = shapes6[0].mesh.indices.size() / 3;


	g_Vao_mercury = gl_createAndBindVAO();

	gl_createAndBindAttribute(&(shapes7[0].mesh.positions[0]), shapes7[0].mesh.positions.size() * sizeof(float), g_simpleShader_sun, "a_vertex", 3);

	gl_createIndexBuffer(&(shapes7[0].mesh.indices[0]), shapes7[0].mesh.indices.size() * sizeof(unsigned int));

	gl_createAndBindAttribute(&(shapes7[0].mesh.texcoords[0]), shapes7[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_sun, "a_uv", 2);

	gl_createAndBindAttribute(&(shapes7[0].mesh.normals[0]), shapes7[0].mesh.normals.size() * sizeof(float), g_simpleShader_sun, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_mercury = shapes7[0].mesh.indices.size() / 3;



	g_Vao_uranus = gl_createAndBindVAO();

	gl_createAndBindAttribute(&(shapes8[0].mesh.positions[0]), shapes8[0].mesh.positions.size() * sizeof(float), g_simpleShader_sun, "a_vertex", 3);

	gl_createIndexBuffer(&(shapes8[0].mesh.indices[0]), shapes8[0].mesh.indices.size() * sizeof(unsigned int));

	gl_createAndBindAttribute(&(shapes8[0].mesh.texcoords[0]), shapes8[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_sun, "a_uv", 2);

	gl_createAndBindAttribute(&(shapes8[0].mesh.normals[0]), shapes8[0].mesh.normals.size() * sizeof(float), g_simpleShader_sun, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_uranus = shapes8[0].mesh.indices.size() / 3;


	g_Vao_neptune = gl_createAndBindVAO();

	gl_createAndBindAttribute(&(shapes9[0].mesh.positions[0]), shapes9[0].mesh.positions.size() * sizeof(float), g_simpleShader_sun, "a_vertex", 3);

	gl_createIndexBuffer(&(shapes9[0].mesh.indices[0]), shapes9[0].mesh.indices.size() * sizeof(unsigned int));

	gl_createAndBindAttribute(&(shapes9[0].mesh.texcoords[0]), shapes9[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_sun, "a_uv", 2);

	gl_createAndBindAttribute(&(shapes9[0].mesh.normals[0]), shapes9[0].mesh.normals.size() * sizeof(float), g_simpleShader_sun, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_neptune = shapes9[0].mesh.indices.size() / 3;


	g_Vao_jupiter = gl_createAndBindVAO();

	gl_createAndBindAttribute(&(shapes10[0].mesh.positions[0]), shapes10[0].mesh.positions.size() * sizeof(float), g_simpleShader_sun, "a_vertex", 3);

	gl_createIndexBuffer(&(shapes10[0].mesh.indices[0]), shapes10[0].mesh.indices.size() * sizeof(unsigned int));

	gl_createAndBindAttribute(&(shapes10[0].mesh.texcoords[0]), shapes10[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_sun, "a_uv", 2);

	gl_createAndBindAttribute(&(shapes10[0].mesh.normals[0]), shapes10[0].mesh.normals.size() * sizeof(float), g_simpleShader_sun, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_jupiter = shapes10[0].mesh.indices.size() / 3;


	g_Vao_moon = gl_createAndBindVAO();

	gl_createAndBindAttribute(&(shapes_moon[0].mesh.positions[0]), shapes_moon[0].mesh.positions.size() * sizeof(float), g_simpleShader_sun, "a_vertex", 3);

	gl_createIndexBuffer(&(shapes_moon[0].mesh.indices[0]), shapes_moon[0].mesh.indices.size() * sizeof(unsigned int));

	gl_createAndBindAttribute(&(shapes_moon[0].mesh.texcoords[0]), shapes_moon[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_sun, "a_uv", 2);

	gl_createAndBindAttribute(&(shapes_moon[0].mesh.normals[0]), shapes_moon[0].mesh.normals.size() * sizeof(float), g_simpleShader_sun, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_moon = shapes_moon[0].mesh.indices.size() / 3;



	g_Vao_star = gl_createAndBindVAO();

	gl_createAndBindAttribute(&(shapes_star[0].mesh.positions[0]), shapes_star[0].mesh.positions.size() * sizeof(float), g_simpleShader_sun, "a_vertex", 3);

	gl_createIndexBuffer(&(shapes_star[0].mesh.indices[0]), shapes_star[0].mesh.indices.size() * sizeof(unsigned int));

	gl_createAndBindAttribute(&(shapes_star[0].mesh.texcoords[0]), shapes_star[0].mesh.texcoords.size() * sizeof(GLfloat), g_simpleShader_sun, "a_uv", 2);

	gl_createAndBindAttribute(&(shapes_star[0].mesh.normals[0]), shapes_star[0].mesh.normals.size() * sizeof(float), g_simpleShader_sun, "a_normal", 3);

	gl_unbindVAO();

	g_NumTriangles_star = shapes_star[0].mesh.indices.size() / 3;


	//sun texture
	Image* image_sun = loadBMP("assets/sun.bmp");
	glGenTextures(1, &texture_id_sun);
	glBindTexture(GL_TEXTURE_2D, texture_id_sun);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_sun->width, image_sun->height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image_sun->pixels);


	//venus texture
	Image* image_venus = loadBMP("assets/venus.bmp");
	glGenTextures(1, &texture_id_venus);
	glBindTexture(GL_TEXTURE_2D, texture_id_venus);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_venus->width, image_venus->height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image_venus->pixels);


	//mars texture
	Image* image_mars = loadBMP("assets/mars.bmp");
	glGenTextures(1, &texture_id_mars);
	glBindTexture(GL_TEXTURE_2D, texture_id_mars);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_mars->width, image_mars->height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image_mars->pixels);


	//saturn texture
	Image* image_saturn = loadBMP("assets/saturn.bmp");
	glGenTextures(1, &texture_id_saturn);
	glBindTexture(GL_TEXTURE_2D, texture_id_saturn);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_saturn->width, image_saturn->height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image_saturn->pixels);

	//uranus texture
	Image* image_uranus = loadBMP("assets/uranus.bmp");
	glGenTextures(1, &texture_id_uranus);
	glBindTexture(GL_TEXTURE_2D, texture_id_uranus);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_uranus->width, image_uranus->height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image_uranus->pixels);

	//milkyway texture
	Image* image_milky = loadBMP("assets/milkyway.bmp");
	glGenTextures(1, &texture_id_milky);
	glBindTexture(GL_TEXTURE_2D, texture_id_milky);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_milky->width, image_milky->height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image_milky->pixels);

	//mercury texture
	Image* image_mercury = loadBMP("assets/mercury.bmp");
	glGenTextures(1, &texture_id_mercury);
	glBindTexture(GL_TEXTURE_2D, texture_id_mercury);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_mercury->width, image_mercury->height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image_mercury->pixels);

	//neptune texture
	Image* image_neptune = loadBMP("assets/neptune.bmp");
	glGenTextures(1, &texture_id_neptune);
	glBindTexture(GL_TEXTURE_2D, texture_id_neptune);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_neptune->width, image_neptune->height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image_neptune->pixels);

	//jupiter texture
	Image* image_jupiter = loadBMP("assets/jupiter.bmp");
	glGenTextures(1, &texture_id_jupiter);
	glBindTexture(GL_TEXTURE_2D, texture_id_jupiter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_jupiter->width, image_jupiter->height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image_jupiter->pixels);

	//earth texture
	Image* image = loadBMP("assets/earthmap1k.bmp");
	glGenTextures(1, &texture_id_earth);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

	//earthspec texture
	Image* image_spec = loadBMP("assets/earthspec.bmp");
	glGenTextures(1, &texture_id_earth_spec);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth_spec);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_spec->width, image_spec->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_spec->pixels); 

	//earthnight texture
	Image* image_night = loadBMP("assets/earthnight.bmp");
	glGenTextures(1, &texture_id_earth_night);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth_night);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image_night->width, image_night->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image_night->pixels); 

}

// ------------------------------------------------------------------------------------------
// This function actually draws to screen and called non-stop, in a loop
// ------------------------------------------------------------------------------------------
void draw()
{
	
	//clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	//milky way

	glUseProgram(g_simpleShader_sky);

	gl_bindVAO(g_Vao_sky);
	

	GLuint u_model = glGetUniformLocation(g_simpleShader_sky, "u_model");
	GLuint u_view = glGetUniformLocation(g_simpleShader_sky, "u_view");
	GLuint u_projection = glGetUniformLocation(g_simpleShader_sky, "u_projection");

	mat4 model_matrix2 = translate(mat4(1.0f), eye);
	mat4 view_matrix2 = lookAt(eye, center, vec3(0, 1, 0));
	mat4 projection_matrix2 = glm::perspective(120.0f, (float)(g_ViewportWidth / g_ViewportHeight), 0.1f, 50.0f);


	glUniformMatrix4fv(u_model, 1, GL_FALSE, glm::value_ptr(model_matrix2));

	glUniformMatrix4fv(u_view, 1, GL_FALSE, glm::value_ptr(view_matrix2));

	glUniformMatrix4fv(u_projection, 1, GL_FALSE, glm::value_ptr(projection_matrix2));

	GLuint u_texture_milky = glGetUniformLocation(g_simpleShader_sky, "u_texture");
	glUniform1i(u_texture_milky, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_milky);

	gl_bindVAO(g_Vao_sky);

	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_sky, GL_UNSIGNED_INT, 0);



	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// earth
	glUseProgram(g_simpleShader_earth);

	gl_bindVAO(g_Vao);

	GLuint model_loc = glGetUniformLocation(g_simpleShader_earth, "u_model");

	mat4 model = translate(mat4(1.0f), vec3(15.0f, 0.0f, 0.0f));

	glUniformMatrix4fv(model_loc, 1, GL_FALSE, glm::value_ptr(model));

	GLuint projection_loc = glGetUniformLocation(g_simpleShader_earth, "u_projection");

	mat4 projection_matrix = perspective(
		90.0f,
		1.0f,
		0.1f,
		50.0f
	);

	glUniformMatrix4fv(projection_loc, 1, GL_FALSE, value_ptr(projection_matrix));



	vec3 up = vec3(0.0f, 1.0f, 0.0f);
	mat4 view_matrix = glm::lookAt(
		eye, 		// the position of your camera, in world space
		center,   	// where you want to look at, in world space
		up       	// probably glm::vec3(0,1,0)
	);

	GLuint view_loc = glGetUniformLocation(g_simpleShader_earth, "u_view");
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, value_ptr(view_matrix));

	GLuint u_texture_spec = glGetUniformLocation(g_simpleShader_earth, "u_texture_spec");

	glUniform1i(u_texture_spec, 2);

	glActiveTexture(GL_TEXTURE2);

	glBindTexture(GL_TEXTURE_2D, texture_id_earth_spec);

	GLuint u_texture_night = glGetUniformLocation(g_simpleShader_earth, "u_texture_night");

	glUniform1i(u_texture_night, 3);

	glActiveTexture(GL_TEXTURE3);

	glBindTexture(GL_TEXTURE_2D, texture_id_earth_night);

	GLuint u_texture = glGetUniformLocation(g_simpleShader_earth, "u_texture");

	glUniform1i(u_texture, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_earth);

	GLuint light_loc = glGetUniformLocation(g_simpleShader_earth, "u_light_dir");
	glUniform3f(light_loc, g_light_dir.x, g_light_dir.y, g_light_dir.z);

	GLuint cam_pos_loc = glGetUniformLocation(g_simpleShader_earth, "u_cam_pos");

	glUniform3f(cam_pos_loc, 0.0, 0.0, 0.0);

	GLuint ambient_loc = glGetUniformLocation(g_simpleShader_earth, "u_ambient");
	glUniform3f(ambient_loc, 0.0, 0.0, 0.2);

	GLuint diffuse_loc = glGetUniformLocation(g_simpleShader_earth, "u_diffuse");
	glUniform3f(diffuse_loc, 0.0, 0.0, 1.0); // blue light

	GLuint specular_loc = glGetUniformLocation(g_simpleShader_earth, "u_specular");
	glUniform3f(specular_loc, 1.0, 1.0, 1.0);

	GLuint shininess_loc = glGetUniformLocation(g_simpleShader_earth, "u_shininess");
	glUniform1f(shininess_loc, 80.0);

	gl_bindVAO(g_Vao);

	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles, GL_UNSIGNED_INT, 0);




	//sun
	glUseProgram(g_simpleShader_sun);

	gl_bindVAO(g_Vao_sun);

	GLuint model_loc3= glGetUniformLocation(g_simpleShader_sun, "u_model");

	mat4 model3 = translate(mat4(1.0f), vec3(-5.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(7.0f, 7.0f, 7.0f));;

	glUniformMatrix4fv(model_loc3, 1, GL_FALSE, glm::value_ptr(model3));


	GLuint projection_loc3 = glGetUniformLocation(g_simpleShader_sun, "u_projection");

	mat4 projection_matrix3 = perspective(
		90.0f,
		1.0f,
		0.1f,
		50.0f
	);

	glUniformMatrix4fv(projection_loc3, 1, GL_FALSE, value_ptr(projection_matrix3));

	mat4 view_matrix3 = glm::lookAt(
		eye, 		// the position of your camera, in world space
		center,   	// where you want to look at, in world space
		up      	// probably glm::vec3(0,1,0)
	);
	
	GLuint view_loc3 = glGetUniformLocation(g_simpleShader_sun, "u_view");
	glUniformMatrix4fv(view_loc3, 1, GL_FALSE, value_ptr(view_matrix3));

	GLuint u_texture_sun = glGetUniformLocation(g_simpleShader_sun, "u_texture");

	glUniform1i(u_texture_sun, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_sun);

	gl_bindVAO(g_Vao_sun);

	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_sun, GL_UNSIGNED_INT, 0);



	//venus
	glUseProgram(g_simpleShader_sun);

	gl_bindVAO(g_Vao_venus);

	GLuint model_loc4 = glGetUniformLocation(g_simpleShader_sun, "u_model");

	mat4 model4 = translate(mat4(1.0f), vec3(10.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.8, 0.8, 0.8));

	glUniformMatrix4fv(model_loc4, 1, GL_FALSE, glm::value_ptr(model4));


	GLuint projection_loc4 = glGetUniformLocation(g_simpleShader_sun, "u_projection");

	mat4 projection_matrix4 = perspective(
		90.0f,
		1.0f,
		0.1f,
		50.0f
	);

	glUniformMatrix4fv(projection_loc4, 1, GL_FALSE, value_ptr(projection_matrix4));

	mat4 view_matrix4 = glm::lookAt(
		eye, 		// the position of your camera, in world space
		center,   	// where you want to look at, in world space
		up      	// probably glm::vec3(0,1,0)
	);



	GLuint view_loc4 = glGetUniformLocation(g_simpleShader_sun, "u_view");
	glUniformMatrix4fv(view_loc4, 1, GL_FALSE, value_ptr(view_matrix4));

	GLuint u_texture_venus = glGetUniformLocation(g_simpleShader_sun, "u_texture");

	glUniform1i(u_texture_venus, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_venus);


	GLuint light_loc2 = glGetUniformLocation(g_simpleShader_sun, "u_light_dir");
	glUniform3f(light_loc2, g_light_dir_venus.x, g_light_dir_venus.y, g_light_dir_venus.z);

	GLuint cam_pos_loc2 = glGetUniformLocation(g_simpleShader_sun, "u_cam_pos");

	glUniform3f(cam_pos_loc2, -5.0, 0.0, 0.0);

	GLuint ambient_loc2 = glGetUniformLocation(g_simpleShader_sun, "u_ambient");
	glUniform3f(ambient_loc2, 0.0, 0.0, 0.2);

	GLuint diffuse_loc2 = glGetUniformLocation(g_simpleShader_sun, "u_diffuse");
	glUniform3f(diffuse_loc2, 0.0, 0.0, 0.0); // blue light

	GLuint specular_loc2 = glGetUniformLocation(g_simpleShader_sun, "u_specular");
	glUniform3f(specular_loc2, 1.0, 1.0, 1.0);

	GLuint shininess_loc2 = glGetUniformLocation(g_simpleShader_sun, "u_shininess");
	glUniform1f(shininess_loc2, 20.0);

	gl_bindVAO(g_Vao_venus);

	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_venus, GL_UNSIGNED_INT, 0);




	//mars
	glUseProgram(g_simpleShader_sun);

	gl_bindVAO(g_Vao_mars);

	GLuint model_loc5 = glGetUniformLocation(g_simpleShader_sun, "u_model");

	mat4 model5 = translate(mat4(1.0f), vec3(20.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.5, 0.5, 0.5));

	glUniformMatrix4fv(model_loc5, 1, GL_FALSE, glm::value_ptr(model5));


	GLuint projection_loc5 = glGetUniformLocation(g_simpleShader_sun, "u_projection");

	mat4 projection_matrix5 = perspective(
		90.0f,
		1.0f,
		0.1f,
		50.0f
	);

	glUniformMatrix4fv(projection_loc5, 1, GL_FALSE, value_ptr(projection_matrix5));

	mat4 view_matrix5 = glm::lookAt(
		eye, 		// the position of your camera, in world space
		center,   	// where you want to look at, in world space
		up      	// probably glm::vec3(0,1,0)
	);



	GLuint view_loc5 = glGetUniformLocation(g_simpleShader_sun, "u_view");
	glUniformMatrix4fv(view_loc5, 1, GL_FALSE, value_ptr(view_matrix5));

	GLuint u_texture_mars = glGetUniformLocation(g_simpleShader_sun, "u_texture");

	glUniform1i(u_texture_mars, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_mars);

	gl_bindVAO(g_Vao_mars);

	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_mars, GL_UNSIGNED_INT, 0);



	//saturn
	glUseProgram(g_simpleShader_sun);

	gl_bindVAO(g_Vao_saturn);

	GLuint model_loc6 = glGetUniformLocation(g_simpleShader_sun, "u_model");

	mat4 model6 = translate(mat4(1.0f), vec3(33.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(2.5f, 2.5f, 2.5f));

	glUniformMatrix4fv(model_loc6, 1, GL_FALSE, glm::value_ptr(model6));


	GLuint projection_loc6 = glGetUniformLocation(g_simpleShader_sun, "u_projection");

	mat4 projection_matrix6 = perspective(
		90.0f,
		1.0f,
		0.1f,
		50.0f
	);

	glUniformMatrix4fv(projection_loc6, 1, GL_FALSE, value_ptr(projection_matrix6));


	mat4 view_matrix6 = glm::lookAt(
		eye, 		// the position of your camera, in world space
		center,   	// where you want to look at, in world space
		up      	// probably glm::vec3(0,1,0)
	);



	GLuint view_loc6 = glGetUniformLocation(g_simpleShader_sun, "u_view");
	glUniformMatrix4fv(view_loc6, 1, GL_FALSE, value_ptr(view_matrix6));

	GLuint u_texture_saturn = glGetUniformLocation(g_simpleShader_sun, "u_texture");

	glUniform1i(u_texture_saturn, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_saturn);

	gl_bindVAO(g_Vao_saturn);

	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_saturn, GL_UNSIGNED_INT, 0);




	//mercury
	glUseProgram(g_simpleShader_sun);

	gl_bindVAO(g_Vao_mercury);

	GLuint model_loc7 = glGetUniformLocation(g_simpleShader_sun, "u_model");

	mat4 model7 = translate(mat4(1.0f), vec3(5.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.4, 0.4, 0.4));

	glUniformMatrix4fv(model_loc7, 1, GL_FALSE, glm::value_ptr(model7));


	GLuint projection_loc7 = glGetUniformLocation(g_simpleShader_sun, "u_projection");

	mat4 projection_matrix7 = perspective(
		90.0f,
		1.0f,
		0.1f,
		50.0f
	);

	glUniformMatrix4fv(projection_loc7, 1, GL_FALSE, value_ptr(projection_matrix7));

	mat4 view_matrix7 = glm::lookAt(
		eye, 		// the position of your camera, in world space
		center,   	// where you want to look at, in world space
		up      	// probably glm::vec3(0,1,0)
	);



	GLuint view_loc7 = glGetUniformLocation(g_simpleShader_sun, "u_view");
	glUniformMatrix4fv(view_loc7, 1, GL_FALSE, value_ptr(view_matrix7));

	GLuint u_texture_mercury = glGetUniformLocation(g_simpleShader_sun, "u_texture");

	glUniform1i(u_texture_mercury, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_mercury);

	gl_bindVAO(g_Vao_mercury);

	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_mercury, GL_UNSIGNED_INT, 0);




	//uranus
	glUseProgram(g_simpleShader_sun);

	gl_bindVAO(g_Vao_uranus);

	GLuint model_loc8 = glGetUniformLocation(g_simpleShader_sun, "u_model");

	mat4 model8 = translate(mat4(1.0f), vec3(40.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(1.6, 1.6, 1.6));

	glUniformMatrix4fv(model_loc8, 1, GL_FALSE, glm::value_ptr(model8));


	GLuint projection_loc8 = glGetUniformLocation(g_simpleShader_sun, "u_projection");

	mat4 projection_matrix8 = perspective(
		90.0f,
		1.0f,
		0.1f,
		50.0f
	);

	glUniformMatrix4fv(projection_loc8, 1, GL_FALSE, value_ptr(projection_matrix8));


	mat4 view_matrix8 = glm::lookAt(
		eye, 		// the position of your camera, in world space
		center,   	// where you want to look at, in world space
		up      	// probably glm::vec3(0,1,0)
	);



	GLuint view_loc8 = glGetUniformLocation(g_simpleShader_sun, "u_view");
	glUniformMatrix4fv(view_loc8, 1, GL_FALSE, value_ptr(view_matrix8));

	GLuint u_texture_uranus = glGetUniformLocation(g_simpleShader_sun, "u_texture");

	glUniform1i(u_texture_uranus, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_uranus);

	gl_bindVAO(g_Vao_uranus);

	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_uranus, GL_UNSIGNED_INT, 0);




	//neptune
	glUseProgram(g_simpleShader_sun);

	gl_bindVAO(g_Vao_neptune);

	GLuint model_loc9 = glGetUniformLocation(g_simpleShader_sun, "u_model");

	mat4 model9 = translate(mat4(1.0f), vec3(45.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(1.5, 1.5, 1.5));

	glUniformMatrix4fv(model_loc9, 1, GL_FALSE, glm::value_ptr(model9));


	GLuint projection_loc9 = glGetUniformLocation(g_simpleShader_sun, "u_projection");

	mat4 projection_matrix9 = perspective(
		90.0f,
		1.0f,
		0.1f,
		50.0f
	);

	glUniformMatrix4fv(projection_loc9, 1, GL_FALSE, value_ptr(projection_matrix9));


	mat4 view_matrix9 = glm::lookAt(
		eye, 		// the position of your camera, in world space
		center,   	// where you want to look at, in world space
		up      	// probably glm::vec3(0,1,0)
	);

	GLuint view_loc9 = glGetUniformLocation(g_simpleShader_sun, "u_view");
	glUniformMatrix4fv(view_loc9, 1, GL_FALSE, value_ptr(view_matrix9));

	GLuint u_texture_neptune = glGetUniformLocation(g_simpleShader_sun, "u_texture");

	glUniform1i(u_texture_neptune, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_neptune);

	gl_bindVAO(g_Vao_neptune);

	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_neptune, GL_UNSIGNED_INT, 0);




	//jupiter
	glUseProgram(g_simpleShader_sun);

	gl_bindVAO(g_Vao_jupiter);

	GLuint model_loc10 = glGetUniformLocation(g_simpleShader_sun, "u_model");

	mat4 model10 = translate(mat4(1.0f), vec3(25.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(3, 3, 3));

	glUniformMatrix4fv(model_loc10, 1, GL_FALSE, glm::value_ptr(model10));


	GLuint projection_loc10 = glGetUniformLocation(g_simpleShader_sun, "u_projection");

	mat4 projection_matrix10 = perspective(
		90.0f,
		1.0f,
		0.1f,
		50.0f
	);

	glUniformMatrix4fv(projection_loc10, 1, GL_FALSE, value_ptr(projection_matrix10));

	
	mat4 view_matrix10 = glm::lookAt(
		eye, 		// the position of your camera, in world space
		center,   	// where you want to look at, in world space
		up      	// probably glm::vec3(0,1,0)
	);



	GLuint view_loc10 = glGetUniformLocation(g_simpleShader_sun, "u_view");
	glUniformMatrix4fv(view_loc10, 1, GL_FALSE, value_ptr(view_matrix10));

	GLuint u_texture_jupiter = glGetUniformLocation(g_simpleShader_sun, "u_texture");

	glUniform1i(u_texture_jupiter, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_jupiter);

	gl_bindVAO(g_Vao_jupiter);

	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_jupiter, GL_UNSIGNED_INT, 0);


	//moon
	glUseProgram(g_simpleShader_sun);

	gl_bindVAO(g_Vao_moon);

	GLuint model_loc_moon = glGetUniformLocation(g_simpleShader_sun, "u_model");

	mat4 model_moon = translate(mat4(1.0f), vec3(15.0f, 0.0f, 2.0f)) * scale(mat4(1.0f), vec3(0.3, 0.3, 0.3));

	glUniformMatrix4fv(model_loc_moon, 1, GL_FALSE, glm::value_ptr(model_moon));


	GLuint projection_loc_moon = glGetUniformLocation(g_simpleShader_sun, "u_projection");

	mat4 projection_matrix_moon = perspective(
		90.0f,
		1.0f,
		0.1f,
		50.0f
	);

	glUniformMatrix4fv(projection_loc_moon, 1, GL_FALSE, value_ptr(projection_matrix_moon));


	mat4 view_matrix_moon = glm::lookAt(
		eye, 		// the position of your camera, in world space
		center,   	// where you want to look at, in world space
		up      	// probably glm::vec3(0,1,0)
	);



	GLuint view_loc_moon = glGetUniformLocation(g_simpleShader_sun, "u_view");
	glUniformMatrix4fv(view_loc_moon, 1, GL_FALSE, value_ptr(view_matrix_moon));

	GLuint u_texture_moon = glGetUniformLocation(g_simpleShader_sun, "u_texture");

	glUniform1i(u_texture_moon, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_mercury);

	gl_bindVAO(g_Vao_moon);

	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_moon, GL_UNSIGNED_INT, 0);



	//star
	glUseProgram(g_simpleShader_sun);

	gl_bindVAO(g_Vao_star);

	GLuint model_loc_iron_man = glGetUniformLocation(g_simpleShader_sun, "u_model");

	mat4 model_iron_man = translate(mat4(1.0f), vec3(15.0f, 5.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.05, 0.05, 0.05));

	glUniformMatrix4fv(model_loc_iron_man, 1, GL_FALSE, glm::value_ptr(model_iron_man));


	GLuint projection_loc_iron_man = glGetUniformLocation(g_simpleShader_sun, "u_projection");

	mat4 projection_matrix_iron_man = perspective(
		90.0f,
		1.0f,
		0.1f,
		50.0f
	);

	glUniformMatrix4fv(projection_loc_iron_man, 1, GL_FALSE, value_ptr(projection_matrix_iron_man));


	mat4 view_matrix_iron_man = glm::lookAt(
		eye, 		// the position of your camera, in world space
		center,   	// where you want to look at, in world space
		up      	// probably glm::vec3(0,1,0)
	);



	GLuint view_loc_iron_man = glGetUniformLocation(g_simpleShader_sun, "u_view");
	glUniformMatrix4fv(view_loc_iron_man, 1, GL_FALSE, value_ptr(view_matrix_iron_man));

	GLuint u_texture_iron_man = glGetUniformLocation(g_simpleShader_sun, "u_texture");

	glUniform1i(u_texture_iron_man, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_id_sun);

	gl_bindVAO(g_Vao_star);

	glDrawElements(GL_TRIANGLES, 3 * g_NumTriangles_star, GL_UNSIGNED_INT, 0);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//quit
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);
	//reload

	//Movimiento de cámara//
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
		eye += speed * center;
	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
		eye -= speed * center;
	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
		eye -= normalize(cross(center, up)) * speed;
	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
		eye += normalize(cross(center, up)) * speed;
}

// ------------------------------------------------------------------------------------------
// This function is called every time you click the mouse
// ------------------------------------------------------------------------------------------
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {

	//Input por ratón//

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		cout << "Left mouse down" << endl;

		if (aux == 1) {

			lastX = mouse_x;
			lastY = mouse_y;
			aux = 0;

		}

		offset_x = mouse_x - lastX;
		offset_y = mouse_y - lastY;
		lastX = mouse_x;
		lastY = mouse_y;


		offset_x *= sensibilidad;
		offset_y *= sensibilidad;

		Yaw += offset_x;
		Pitch += offset_y;


		if (Pitch > 89.0) {
			Pitch = 89.0f;
		}
		if (Pitch < -89.0) {
			Pitch = -89.0f;
		}


		vec3 direction_mouse(direction_mouse_x, direction_mouse_y, direction_mouse_z);
		direction_mouse_x = cos(radians(Yaw)) * cos(radians(Pitch));
		direction_mouse_y = sin(radians(Pitch));
		direction_mouse_z = sin(radians(Yaw)) * cos(radians(Pitch));
		center = normalize(direction_mouse);

	}

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		cout << "Left mouse up " << endl;


	}
}


void onMouseMove(GLFWwindow* window, double x, double y) {
	//cout << "Mouse at" << x << ", " << y << endl;





}




int main(void)
{
	//setup window and boring stuff, defined in glfunctions.cpp
	GLFWwindow* window;
	if (!glfwInit())return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(g_ViewportWidth, g_ViewportHeight, "Hello OpenGL!", NULL, NULL);
	if (!window) {glfwTerminate();	return -1;}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	glewInit();

	//input callbacks
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
	glfwSetCursorPosCallback(window, onMouseMove);

	//load all the resources
	load();

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
		draw();
        
        // Swap front and back buffers
        glfwSwapBuffers(window);
        
        // Poll for and process events
        glfwPollEvents();
        
        //mouse position must be tracked constantly (callbacks do not give accurate delta)
        glfwGetCursorPos(window, &mouse_x, &mouse_y);
    }

    //terminate glfw and exit
    glfwTerminate();
    return 0;
}


