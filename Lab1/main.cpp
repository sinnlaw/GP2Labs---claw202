<<<<<<< HEAD
//Head file
#include <iostream>
#include <GL\glew.h>
#include <gl\GLU.h>

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <gl/GLU.h>

#include "Vertex.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "Component.h"
#include "FBXLoader.h"

#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;

#include <vector>

std::vector<GameObject*> displayList;
GameObject * mainCamera;


=======
//Head file
#include <iostream>
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include "Vertex.h"
#include "Shader.h"

<<<<<<< HEAD
>>>>>>> parent of 9382281... Lab3 16/10/2014
=======
>>>>>>> parent of 9382281... Lab3 16/10/2014
//maths	headers
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;
#include <glm/gtc/matrix_transform.hpp>
<<<<<<< HEAD
<<<<<<< HEAD
#include <glm/gtc/type_ptr.hpp>

#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "assets";
#else
const std::string ASSET_PATH = "assets";
#endif

const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/texture";
const std::string MODEL_PATH = "/models";
 
//Golbal variables
bool running = true;

//Pointer to our SDL Windows
//SDL_GLContext
SDL_Window * window;
SDL_Event event;
SDL_GLContext glcontext = NULL;

//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

GLuint texture = 0;
GLuint triangleVBO;
GLuint triangleEBO;
GLuint shaderProgram = 0;
GLuint VAO;

//matrices
mat4 viewMatrix;
mat4 projMatrix;
mat4 worldMatrix;

Vertex triangleData[] = {
	{ vec3(-0.5f, 0.5f, 0.5f), vec3(0.25f, 0.25f, 0.5f), vec2(0.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f) },// Top Left
	{ vec3(-0.5f, -0.5f, 0.5f), vec3(0.25f, 0.25f, 0.5f), vec2(0.0f, 1.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) },// Bottom Left
	{ vec3(0.5f, -0.5f, 0.5f), vec3(0.25f, -0.25f, 0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f) }, //Bottom Right
	{ vec3(0.5f, 0.5f, 0.5f), vec3(0.25f, -0.25f, 0.5f), vec2(1.0f, 0.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f) },// Top Right


	//back
	{ vec3(-0.5f, 0.5f, -0.5f), vec3(0.25f, 0.25f, -0.5f), vec2(0.0f, 0.0f), vec4(0.0f, 0.0f, 1.0f, 1.0f) },// Top Left
	{ vec3(-0.5f, -0.5f, -0.5f), vec3(0.25f, 0.25f, -0.5f), vec2(0.0f, 1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f) },// Bottom Left
	{ vec3(0.5f, -0.5f, -0.5f), vec3(0.25f, -0.25f, -0.5f), vec2(1.0f, 1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f) }, //Bottom Right
	{ vec3(0.5f, 0.5f, -0.5f), vec3(0.25f, -0.25f, -0.5f), vec2(1.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 1.0f) }// Top Right
};


GLuint indices[] = {
	//front
	0, 1, 2,
	0, 3, 2,

	//left
	4, 5, 1,
	4, 1, 0,

	//right
	3, 7, 2,
	7, 6, 2,

	//bottom
	1, 5, 2,
	6, 2, 1,

	//top
	5, 0, 7,
	5, 7, 3,

	//back
	4, 5, 6,
	4, 7, 6
};


void initGeometry()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//create buffer
	glGenBuffers(1, &triangleVBO);
	//make the new vbo active
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//copy vertex data to vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);

	//create buffer
	glGenBuffers(1, &triangleEBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
	//Copy Index data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void renderGameObject(GameObject *pObject)
{
	if (!pObject)
	{
		return;

		pObject->render();

		Mesh * currentMesh = pObject->getMesh();
		Transform * currentTransform = pObject->getTransform();
		Material * currentMaterial = pObject->getMaterial();

		if (currentMesh && currentMaterial && currentTransform)
		{
			currentMesh->Bind();
			currentMaterial->bind();

			GLint MVPLocation = currentMaterial->getUniformLocation("MVP");

			Camera * cam = mainCamera->getCamera();
			mat4 MVP = cam->getProjection()*cam->getView()*currentTransform->getModel();
			glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));

			glDrawElements(GL_TRIANGLES, currentMesh->getIndexData(), GL_UNSIGNED_INT, 0);
		}

		for (int i = 0; i < pObject->getChildCount(); i++)
		{
			renderGameObject(pObject->getChild(i));
		}

	}
}

//Function to draw
void render()
{

	//set colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glBindVertexArray(VAO);
	//make the new vbo active. repeat here as a sanity check
	//glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
	//glUseProgram(shaderProgram);
	//GLint texture0Location = glGetUniformLocation(shaderProgram, "texture0");
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture);
	//glUniform1i(texture0Location, 0);
	//GLint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
	//mat4 MVP = projMatrix*viewMatrix*worldMatrix;
	//glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
	//Tell	the	shader	that	0	is	the	position	element
	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), NULL);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void**)sizeof(vec3));
	//glEnableVertexAttribArray(2);
	//glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void**)(sizeof(vec3)+sizeof(vec2)));
	//draw the triangle 
	//glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);
	//require to swap the back and front buffer

	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
	
		renderGameObject((*iter));

	}

	SDL_GL_SwapWindow(window);
}

//Function to update game state
void update()
{

//	projMatrix = glm::perspective(45.0f, (float)WINDOW_WIDTH /(float)WINDOW_HEIGHT, 0.1f, 100.0f);
//	viewMatrix = glm::lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
//	worldMatrix = glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));

	//alternative sytanx
	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		renderGameObject((*iter));
	}

}

void initialise()
{
	mainCamera = new GameObject();
	mainCamera->setName("MainCamera");

	Transform *t = new Transform();
	t->setPosition(0.0f, 0.0f, 10.0f);
	mainCamera->setTransform(t);

	Camera * c = new Camera();
	c->setFOV(45.0f);
	c->setNearClip(0.1f);
	c->setFarClip(1000.0f);

	//set everthing
	mainCamera->setCamera(c);
	displayList.push_back(mainCamera);

	GameObject * cube = new GameObject();
	cube->setName("Cube");
	Transform *transform = new Transform();
	transform->setPosition(0.0f, 0.0f, 0.0f);
	cube->setTransform(transform);

	Material * material = new Material();
	std::string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	std::string fsPath = ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";
	material->loadShader(vsPath, fsPath);
	cube->setMaterial(material);

	Mesh * mesh = new Mesh();
	cube->setMesh(mesh);

	displayList.push_back(cube);
	//for loop initialisation starts
	//for loop initialisation ends

	for (auto iter = displayList.begin(); iter != displayList.end(); iter++)
	{
		(*iter)->init();
	} 

	mesh->copyVertexData(8, sizeof(Vertex), (void**)triangleData);
	mesh->copyIndexData(36, sizeof(int), (void**)indices);

	std::string modelPath = ASSET_PATH + MODEL_PATH + "/armoredrecon.fbx";
	GameObject * go = loadFBXFromFile(modelPath);
	for (int i = 0; i < go->getChildCount(); i++)
	{
		Material * material = new Material();
		material->init();
		std::string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
		std::string fsPath = ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";
		material->loadShader(vsPath, fsPath);
		go->getChild(i)->setMaterial(material);
	}
	displayList.push_back(go);

}

//Clean Up function
void CleanUp(){

	auto iter = displayList.begin();
	while (iter != displayList.end())
	{
		(*iter)->destroy();
		if ((*iter))
		{
			delete (*iter);
			(*iter) = NULL;
			iter = displayList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	//glDeleteTextures(1, &texture);
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteProgram(shaderProgram);
	//glDeleteBuffers(1, &triangleEBO);
	//glDeleteBuffers(1, &triangleVBO);
	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();

}

//Function to initialise OpenGL
void initOpenGL()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);



	//Create OpenGL Context
	glcontext = SDL_GL_CreateContext(window);

	//something went wrong in creating the context, if it is NULL
	if (!glcontext)
	{
		std::cout << "ERROR Creating OpenGL Context" << SDL_GetError() << std::endl;
	}

	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "ERROR" << glewGetErrorString(err) << std::endl;
	}

	//Smooth shading
	glShadeModel(GL_SMOOTH);
	//clear the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Clear the depth buffer to 1.0
	glClearDepth(1.0f);
	//Enable depth testing
	glEnable(GL_DEPTH_TEST);
	//The depth test to use
	glDepthFunc(GL_LEQUAL);
	//Trun on best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//Function to set/reset viewport
void setViewport(int width, int height)
{
	//screen ration
	GLfloat ratio;
	//make sure height is always above 0
	if (height == 0)
	{
		height = 1;
	}
	//calculate screen ration
	ratio = (GLfloat)width / (GLfloat)height;
	//Setup viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	//Setup the Transformation
	//Change to poject matrix mode
	// - glMatrixMode(GL_PROJECTION);
	// - glLoadIdentity();

	//Calculate perspective matrix, using gly library functions
	// - gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	//Swoth to ModelView
	// - glMatrixMode(GL_MODELVIEW);

	//Reset using the Indentity Matrix
	// - glLoadIdentity();


}

//Global function
void InitWindow(int width, int height, bool fullscreen)
{
	//Create a window
	window = SDL_CreateWindow(
		"Lab 1",				//Window name
		SDL_WINDOWPOS_CENTERED, //x position centered
		SDL_WINDOWPOS_CENTERED, //y position centered
		width,					//width in pixel
		height,					//height in pixel
		SDL_WINDOW_OPENGL		//flags
		);
}

//void createShader()
//{
//	GLuint vertexShaderProgram = 0;
//		std::string vsPath = ASSET_PATH + SHADER_PATH + "/textureVS.glsl";
//		vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);/
//
//	GLuint fragmentShaderProgram = 0;
//		std::string fsPath = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";
//		fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);/
//
//	shaderProgram =	glCreateProgram();
//		glAttachShader(shaderProgram, vertexShaderProgram);
//		glAttachShader(shaderProgram, fragmentShaderProgram);
//		glLinkProgram(shaderProgram);
//		checkForLinkErrors(shaderProgram);
//
//	glBindAttribLocation(shaderProgram, 0, "vertexPosition");
//	glBindAttribLocation(shaderProgram, 1, "vertexTexCoords");
//	glBindAttribLocation(shaderProgram, 2, "vertexColour");
//}

void createTexture()
{
	std::string	texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";
	texture = loadTextureFromFile(texturePath);
}

//Main Method - Entry Point
int main(int argc, char* arg[]){

	//if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	//{
	//	std::cout << "ERROR SDL_Init" << SDL_GetError() << std::endl;
	//	return -1;
	//}
	//int	imageInitFlags = IMG_INIT_JPG | IMG_INIT_PNG;
	//int	returnInitFlags = IMG_Init(imageInitFlags);
	//if (((returnInitFlags)&	(imageInitFlags)) != imageInitFlags)	{
	//	std::cout << "ERROR	SDL_Image Init " << IMG_GetError() << std::endl;
	//	handle	error
	//}
	InitWindow(WINDOW_HEIGHT, WINDOW_HEIGHT, false);
	//Call out InitOpenGL Function
	initOpenGL();
	//initGeometry();
	//Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);
	//createShader();
	//createTexture();

	initialise();

	//Game loop
	while (running)
	{
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
		{
			//set out=r bool to false
			running = false;
		}
		while (SDL_PollEvent(&event))
		{

		}
		update();
		render();

	}

	CleanUp();
	return 0;
}

=======

#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "../assets";
#else
const std::string ASSET_PATH = "assets";
#endif
=======

#ifdef _DEBUG && WIN32
const std::string ASSET_PATH = "../assets";
#else
const std::string ASSET_PATH = "assets";
#endif

const std::string SHADER_PAT = "/shaders";

//Golbal variables
bool running = true;

float objectA_X = 0.0;
float yRotation = 30.0f;

//Pointer to our SDL Windows
//SDL_GLContext
SDL_Window * window;
SDL_Event event;
SDL_GLContext glcontext = NULL;

//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

GLuint shaderProgram = 0;
GLuint triangleVBO;
GLuint triangleEBO;

//matrices
mat4	viewMatrix;
mat4	projMatrix;
mat4	worldMatrix;

//3D tranigle Data
Vertex triangleData[] = {
	//Front
	{ -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f }, //Top Left
	{ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f },//Bottom Left
	{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right
	{ 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f },  //Top Right
	{ -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f }, //Top Left
	{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right
	//Back
	{ -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f }, //Top Left
	{ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f },//Bottom Left
	{ 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right
	{ 0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f },  //Top Right
	{ -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f }, //Top Left
	{ 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right
};

GLuint indices[]{
		//font
		0, 1, 2, 0, 3, 2,
		//left
		4, 5, 1, 4, 1, 0,
		//right
		3, 7, 2, 7, 6, 2,
		//bottom
		1, 5, 2, 6, 2, 1,
		//top
		5, 0, 7, 5, 7, 3,
		//back
		4, 5, 6, 5, 7, 6
};

void keyPressed(unsigned char key, int x, int y)
{
	if (key == 'a')
	{
		yRotation += 100;
	}
}
>>>>>>> parent of 9382281... Lab3 16/10/2014

const std::string SHADER_PAT = "/shaders";

//Golbal variables
bool running = true;

float objectA_X = 0.0;
float yRotation = 30.0f;

//Pointer to our SDL Windows
//SDL_GLContext
SDL_Window * window;
SDL_Event event;
SDL_GLContext glcontext = NULL;

//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

GLuint shaderProgram = 0;
GLuint triangleVBO;
GLuint triangleEBO;

//matrices
mat4	viewMatrix;
mat4	projMatrix;
mat4	worldMatrix;

//3D tranigle Data
Vertex triangleData[] = {
	//Front
	{ -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f }, //Top Left
	{ -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 1.0f },//Bottom Left
	{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right
	{ 0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f },  //Top Right
	{ -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 1.0f }, //Top Left
	{ 0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right
	//Back
	{ -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f }, //Top Left
	{ -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f },//Bottom Left
	{ 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right
	{ 0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f },  //Top Right
	{ -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f }, //Top Left
	{ 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f }, //Bottom Right
};

GLuint indices[]{
		//font
		0, 1, 2, 0, 3, 2,
		//left
		4, 5, 1, 4, 1, 0,
		//right
		3, 7, 2, 7, 6, 2,
		//bottom
		1, 5, 2, 6, 2, 1,
		//top
		5, 0, 7, 5, 7, 3,
		//back
		4, 5, 6, 5, 7, 6
};

void keyPressed(unsigned char key, int x, int y)
{
<<<<<<< HEAD
	if (key == 'a')
	{
		yRotation += 100;
	}
}

void initGeometry()
{
=======
>>>>>>> parent of 9382281... Lab3 16/10/2014
	//create buffer
	glGenBuffers(1, &triangleVBO);
	//make the new vbo active
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	//copy vertex data to vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);

	//create buffer
	glGenBuffers(1, &triangleEBO);
	//Make the EBO active
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
	//Copy Index data to the EBO
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

//Function to draw
void render()
{

	//set colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//make the new vbo active. repeat here as a sanity check
	glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleEBO);
	
	glUseProgram(shaderProgram);

	GLint MVPLocation = glGetUniformLocation(shaderProgram, "MVP");
	mat4 MVP = projMatrix*viewMatrix*worldMatrix;
	glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));

	//Tell	the	shader	that	0	is	the	position	element
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	//Establish its 3 coordinates per vertex with zero stride(space between elements)
	//in array and contain floating point numbers
	//-		glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);
	//The last parameter basiclly says that the colours start 3 float into each element of the array
	//-		glColorPointer(4, GL_FLOAT, sizeof(Vertex), (void**)(3 * sizeof(float)));
	//Establish array contains vertices (not normals, colours, texture coords etc)
	//-		glEnableClientState(GL_VERTEX_ARRAY);
	//-		glEnableClientState(GL_COLOR_ARRAY);

	//swith to modelview
	//-	glMatrixMode(GL_MODELVIEW);

	//triangle one

	//reset using the indenity martix	
	//-		glLoadIdentity();
	//3D
	//-		gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0f, 0.0f, 1.0, 0.0);
	//translate
	//-		glTranslatef(0.0f, 0.0f, -6.0f);
	//Rotate
	//-		glRotatef(yRotation, 0.0f, 1.0f, 0.0f);

	//draw the triangle 
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

//Begin drawing triangles
//	glBegin(GL_TRIANGLES);
//		glColor3f(1.0f, 0.0f, 0.0f);	//Colour of the vertices
//		glVertex3f(objectA_X, 0.5f, 0.0f);	//Top
//		glVertex3f(objectA_X - 0.5f, -0.5f, 0.0f);	//Bottom Left
//		glVertex3f(objectA_X + 0.5f, -0.5f, 0.0f);
//		
//		glColor3f(1.0f, 5.0f, 0.0f);	//Colour of the vertices
//		glVertex3f(-0.5f, -0.5f, 0.0f);	//Top
//		glVertex3f(-1.0f, -1.0f, 0.0f);	//Bottom Left
//		glVertex3f(0.0f, -1.0f, 0.0f);//Bottom Right
//	 glEnd();

	//require to swap the back and front buffer
	SDL_GL_SwapWindow(window);
}

//Function to update game state
void update()
{
	projMatrix = glm::perspective(45.0f, (float)WINDOW_WIDTH /(float)WINDOW_HEIGHT, 0.1f, 100.0f);
	viewMatrix = glm::lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	worldMatrix = glm::translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));
}

//Clean Up function
void CleanUp(){
	glDeleteProgram(shaderProgram);
	SDL_DestroyWindow(window);
	glDeleteBuffers(1, &triangleEBO);
	glDeleteBuffers(1, &triangleVBO);
	SDL_GL_DeleteContext(glcontext);
	SDL_Quit();
}

//Function to initialise OpenGL
void initOpenGL()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	//Create OpenGL Context
	glcontext = SDL_GL_CreateContext(window);

	//something went wrong in creating the context, if it is NULL
	if (!glcontext)
	{
		std::cout << "ERROR Creating OpenGL Context" << SDL_GetError() << std::endl;
	}

	glewExperimental = GL_TRUE;

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "ERROR" << glewGetErrorString(err) << std::endl;
	}

	//Smooth shading
	glShadeModel(GL_SMOOTH);
	//clear the background to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Clear the depth buffer to 1.0
	glClearDepth(1.0f);
	//Enable depth testing
	glEnable(GL_DEPTH_TEST);
	//The depth test to use
	glDepthFunc(GL_LEQUAL);
	//Trun on best perspective correction
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

//Function to set/reset viewport
void setViewport(int width, int height)
{
	//screen ration
	GLfloat ratio;
	//make sure height is always above 0
	if (height == 0)
	{
		height = 1;
	}
	//calculate screen ration
	ratio = (GLfloat)width / (GLfloat)height;
	//Setup viewport
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	//Setup the Transformation
	//Change to poject matrix mode
	// - glMatrixMode(GL_PROJECTION);
	// - glLoadIdentity();

	//Calculate perspective matrix, using gly library functions
	// - gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	//Swoth to ModelView
	// - glMatrixMode(GL_MODELVIEW);

	//Reset using the Indentity Matrix
	// - glLoadIdentity();


}




//Global function
void InitWindow(int width, int height, bool fullscreen)
{
	//Create a window
	window = SDL_CreateWindow(
		"Lab 1",				//Window name
		SDL_WINDOWPOS_CENTERED, //x position centered
		SDL_WINDOWPOS_CENTERED, //y position centered
		width,					//width in pixel
		height,					//height in pixel
		SDL_WINDOW_OPENGL		//flags
		);
}

void createShader()
{
	GLuint vertexShaderProgram = 0;	std::string vsPath = ASSET_PATH + SHADER_PAT + "/simpleVS.glsl";	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);	GLuint fragmentShaderProgram = 0;	std::string fsPath = ASSET_PATH + SHADER_PAT + "/simpleFS.glsl";	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);

	shaderProgram =	glCreateProgram();	glAttachShader(shaderProgram, vertexShaderProgram);	glAttachShader(shaderProgram, fragmentShaderProgram);	glLinkProgram(shaderProgram);	checkForLinkErrors(shaderProgram);	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShaderProgram);
	glAttachShader(shaderProgram, fragmentShaderProgram);
	glLinkProgram(shaderProgram);
	checkForLinkErrors(shaderProgram);

	glBindAttribLocation(shaderProgram, 0, "vertexPosition");

	//now	we	can	delete	the	VS	&	FS	Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);
}

//Main Method - Entry Point
int main(int argc, char* arg[]){

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "ERROR SDL_Init" << SDL_GetError() << std::endl;
		return -1;
	}

	InitWindow(WINDOW_HEIGHT, WINDOW_HEIGHT, false);
	//Call out InitOpenGL Function
	initOpenGL();
	initGeometry();
	//Set our viewport
	setViewport(WINDOW_WIDTH, WINDOW_HEIGHT);

	update();
	render();
	createShader();

	//Game loop
	while (running)
	{
		if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
		{
			//set out=r bool to false
			running = false;
		}
		while (SDL_PollEvent(&event))
		{

		}
	}

	CleanUp();
	return 0;
}

>>>>>>> parent of 9382281... Lab3 16/10/2014
