#include <GL/glfw.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cassert>
#include <set>
#include <limits>
#include <Eigen/Dense>
#define RESOLUTION 40
using namespace std;
using namespace Eigen;

GLuint text2D;
bool shiftDown = false;
double alpha = 1;

Vector2d textureCoords[RESOLUTION][RESOLUTION]; // these values should NOT change as you do your deformation
Vector2d imageCoords[RESOLUTION][RESOLUTION]; // these values should be changed except for those in "active"

enum Deformation { AFFINE, SIMILARITY, ROTATION };
Deformation deformationType;

class ArrayPosition2d : public pair<int,int> { // class for storing (i,j) indices in the above arrays
public:
	int &operator[](int i) { return (i==0)? first:second; }
	const int &operator[](int i) const { return (i==0)? first:second; }
};

set<ArrayPosition2d> active; // list of handles (the points highlighted in red)
ArrayPosition2d curDrag; // the current vertex we're dragging around
Vector2d lastMousePos; // for interaction

void deformImage() {
	if (active.size() == 0) return; // only deform if there's something to deform!

	// Fill this in!
}










/* You shouldn't need to modify anything beyond this point, but feel free to look to see what's going on! */

void GLFWCALL handleKeypress(int key, int press) {
	if (key == GLFW_KEY_ESC) exit(0);
	if (key == GLFW_KEY_LSHIFT || key == GLFW_KEY_RSHIFT) shiftDown = (press == GLFW_PRESS);
}

void GLFWCALL handleResize(int width,int height) {
	assert(width == height); // in this assignment we'll assume the window and image are square

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,1,0,1,0,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // we won't need any modelview matrices today
	glDisable(GL_DEPTH_TEST);
}

GLuint loadTexture(const char* textureName) {
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D,texture);

	if (glfwLoadTexture2D(textureName, GLFW_BUILD_MIPMAPS_BIT)){
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		return texture;
	} else return -1;
}

void makeGLVertex(int i, int j) {
	glTexCoord2d(textureCoords[i][j][0], textureCoords[i][j][1]);
	glVertex2d(imageCoords[i][j][0], imageCoords[i][j][1]);
}

void display() { // this is what renders the texture
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,text2D);

	glPushMatrix();
	glBegin(GL_QUADS);
	for (int i = 0; i < RESOLUTION-1; i++)
	for (int j = 0; j < RESOLUTION-1; j++) {
		makeGLVertex(i,j);
		makeGLVertex(i+1,j);
		makeGLVertex(i+1,j+1);
		makeGLVertex(i,j+1);
	}
	glEnd();

	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
	glPointSize(5);
	glColor3f(1,0,0);
	glBegin(GL_POINTS);

	// draw handles in red
	for (set<ArrayPosition2d>::iterator it = active.begin(); it != active.end(); it++) {
		int i = (*it)[0], j = (*it)[1];
		glVertex2d(imageCoords[i][j][0], imageCoords[i][j][1]);
	}
	glEnd();

	glfwSwapBuffers();
}

Vector2d getMousePosition() {
	int mouseX, mouseY, windowW, windowH;
	glfwGetMousePos(&mouseX, &mouseY);
	glfwGetWindowSize(&windowW, &windowH);
		
	Vector2d p;
	p[0] = mouseX / (double)windowW;
	p[1] = (windowH-1-mouseY) / (double)windowH;
	return p;
}

void GLFWCALL mouseButtonCallback(int button, int action) {
	Vector2d p = getMousePosition();
	
	if (shiftDown && action == GLFW_PRESS) { // shift click to toggle which vertices you're constraining
		double minDist = numeric_limits<double>::max();
		ArrayPosition2d which;
		for (int i = 0; i < RESOLUTION; i++)
		for (int j = 0; j < RESOLUTION; j++) {
			double dist = (p - imageCoords[i][j]).squaredNorm();
			if (minDist > dist) {
				minDist = dist;
				which[0] = i;
				which[1] = j;
			}
		}
		
		if (active.count(which)) active.erase(which);
		else active.insert(which);
	}
	else if (!shiftDown && active.size() > 0 && action == GLFW_PRESS) { // drag to move a vertex
		double minDist = numeric_limits<double>::max();
		for (set<ArrayPosition2d>::iterator it = active.begin(); it != active.end(); it++) {
			int i = (*it)[0], j = (*it)[1];
			double dist = (p - imageCoords[i][j]).squaredNorm();
			if (dist < minDist) {
				minDist = dist;
				curDrag = *it;
			}
		}
		lastMousePos = p;
	}
	else if (!shiftDown && action == GLFW_RELEASE) curDrag[0] = curDrag[1] = -1;
	
	deformImage();
}

void GLFWCALL mousePosCallback(int x, int y) {
	if (curDrag[0] != -1 && curDrag[1] != -1) {
		Vector2d p = getMousePosition();
		
		imageCoords[ curDrag[0] ][ curDrag[1] ] += p - lastMousePos; // temp!
		deformImage();
		
		lastMousePos = p;
	}
}

void init() {
	glfwInit();

	for (int i = 0; i < RESOLUTION; i++)
	for (int j = 0; j < RESOLUTION; j++) {
		textureCoords[i][j][0] = imageCoords[i][j][0] = i / (double)(RESOLUTION-1);
		textureCoords[i][j][1] = imageCoords[i][j][1] = j / (double)(RESOLUTION-1);
	}
	
	curDrag[0] = curDrag[1] = -1;
}

int main(int argc, char *argv[]) {
	if (argc < 4) {
		cout << "Usage: " << argv[0] << " texture.tga alpha deformationType\n";
		cout << "\tDeformation type is one of:  affine, similarity, rotation\n\n";
		cout << "Example: ";
		cout << argv[0] << " images/kitten.tga 1.0 rotation\n";
		return 0;
	}
	
	sscanf(argv[2],"%g",&deformationType);
	
	if (strcmp(argv[3],"affine") == 0) deformationType = AFFINE;
	else if (strcmp(argv[3], "similarity") == 0) deformationType = SIMILARITY;
	else deformationType = ROTATION;

	bool running = true;
	
	init();
	
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE); // disable window resize
	if(!glfwOpenWindow(800, 800, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) { // square window
		glfwTerminate();
		return 0;
	}

	glfwSetWindowTitle("HW 5");
	glfwSetWindowSizeCallback(handleResize);
	glfwSetKeyCallback(handleKeypress);
	glfwSetMouseButtonCallback(mouseButtonCallback);
	glfwSetMousePosCallback(mousePosCallback);
	
	text2D = loadTexture(argv[1]);
	
	while (running) {
		display();
		running = glfwGetWindowParam(GLFW_OPENED);
	}
	 
	return 0;
}
