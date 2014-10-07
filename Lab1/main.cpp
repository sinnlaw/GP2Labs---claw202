//Head file
#include <iostream>
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include "Vertex.h"

//Golbal variables
bool running = true;

float objectA_X = 0.0;
float yRotation = 0.0f;

//Pointer to our SDL Windows
//SDL_GLContext
SDL_Window * window;
SDL_Event event;
SDL_GLContext glcontext = NULL;

//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

GLuint triangleVBO;
GLuint triangleEBO;

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

void initGeometry()
{
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
	//Establish its 3 coordinates per vertex with zero stride(space between elements)
	//in array and contain floating point numbers
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), NULL);
	//The last parameter basiclly says that the colours start 3 float into each element of the array
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (void**)(3 * sizeof(float)));
	//Establish array contains vertices (not normals, colours, texture coords etc)
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	//swith to modelview
	glMatrixMode(GL_MODELVIEW);

	//triangle one

	//reset using the indenity martix	
	glLoadIdentity();
	//3D
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -1.0f, 0.0f, 1.0, 0.0);
	//translate
	glTranslatef(0.0f, 0.0f, -6.0f);
	//Rotate
	glRotatef(yRotation, 0.0f, 1.0f, 0.0f);
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

}

//Clean Up function
void CleanUp(){
	SDL_DestroyWindow(window);
	glDeleteBuffers(1, &triangleEBO);
	glDeleteBuffers(1, &triangleVBO);
	SDL_GL_DeleteContext(glcontext);
	SDL_Quit();
}

//Function to initialise OpenGL
void initOpenGL()
{
	//Create OpenGL Context
	glcontext = SDL_GL_CreateContext(window);

	//something went wrong in creating the context, if it is NULL
	if (!glcontext)
	{
		std::cout << "ERROR Creating OpenGL Context" << SDL_GetError() << std::endl;
	}

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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Calculate perspective matrix, using gly library functions
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	//Swoth to ModelView
	glMatrixMode(GL_MODELVIEW);

	//Reset using the Indentity Matrix
	glLoadIdentity();


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

