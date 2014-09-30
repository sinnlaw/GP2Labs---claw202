//Head file
#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>

//Golbal variables
bool running = true;

float objectA_X = 0.0;

//Pointer to our SDL Windows
//SDL_GLContext
SDL_Window * window;
SDL_Event event;
SDL_GLContext glcontext = NULL;

//Constants to control window creation
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

void keyPress(unsigned char key, int x, int y)
{
	if (key == 'a')
		exit(0);
}

//Function to draw
void render()
{

	//set colour(background)
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the colour and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Switch to ModelView
	glMatrixMode(GL_MODELVIEW);
	//Reset using the Indentity Matrix
	glLoadIdentity();
	//Translate to -5.0f on z-axis
	glTranslatef(0.0f, 0.0f, -5.0f);

	//Begin drawing triangles
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);	//Colour of the vertices
		glVertex3f(objectA_X, 0.5f, 0.0f);	//Top
		glVertex3f(objectA_X - 0.5f, -0.5f, 0.0f);	//Bottom Left
		glVertex3f(objectA_X + 0.5f, -0.5f, 0.0f);
		
		glColor3f(1.0f, 5.0f, 0.0f);	//Colour of the vertices
		glVertex3f(-0.5f, -0.5f, 0.0f);	//Top
		glVertex3f(-1.0f, -1.0f, 0.0f);	//Bottom Left
		glVertex3f(0.0f, -1.0f, 0.0f);//Bottom Right
	glEnd();




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

