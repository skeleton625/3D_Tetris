#include "OpenGL.h"
#include "glDisplay.h"
#include "glTexture.h"

glDisplay glDis;
glTexture glTex;

void norKey_press(unsigned char key, int x, int y) {

}

void norKey_up(unsigned char key, int x, int y) {

}

void specKey_press(int key, int x, int y) {

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
	gluPerspective(45, ratio, 1, 300);
}

void main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("3D Tetris");
	
	glTex.glTex_init();

	glDis.glDis_setTexID(glTex.glTex_get_texID());
	glutIdleFunc(Idle);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(norKey_press);
	glutKeyboardUpFunc(norKey_up);
	glutSpecialFunc(specKey_press);
	glutSpecialUpFunc(specKey_up);
	glutMainLoop();
}