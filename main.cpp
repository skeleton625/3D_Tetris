#include "OpenGL.h"
#include "glDisplay.h"
#include "glTexture.h"
#include <thread>
using namespace std;

glDisplay glDis;
glTexture glTex;

void norKey_press(unsigned char key, int x, int y) {
	glDis.glDis_norKey_press(key);
}

void norKey_up(unsigned char key, int x, int y) {

}

void specKey_press(int key, int x, int y) {
	glDis.glDis_specKey_press(key);
}

void specKey_up(int key, int x, int y) {

}

void Idle() {

}

void display() {
	glDis.glDis_display();
}

void reshape(int w, int h) {
	float ratio = w / (float)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, ratio, 1, 2000);
}

/**/
void main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("3D Tetris");
	
	glTex.glTex_init();
	glTex.glTex_create_texture("red.bmp",0);
	glTex.glTex_create_texture("blue.bmp", 1);
	glTex.glTex_create_texture("green.bmp", 2);
	glTex.glTex_create_texture("pink.bmp", 3);
	glTex.glTex_create_texture("brown.bmp", 4);
	glTex.glTex_create_texture("orange.bmp", 5);
	glTex.glTex_create_texture("gray.bmp", 6);
	glTex.glTex_create_texture("floor.bmp", 7);

	glDis.glDis_init(glTex.glTex_get_texID());
	thread block_down{&glDisplay::glDis_block_cycle, &glDis};
	glutIdleFunc(Idle);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(norKey_press);
	//glutKeyboardUpFunc(norKey_up);
	glutSpecialFunc(specKey_press);
	//glutSpecialUpFunc(specKey_up);
	glutMainLoop();
}