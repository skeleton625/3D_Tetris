#include "OpenGL.h"
#include "glDisplay.h"
#include <iostream>
using namespace std;

void glDisplay::glDis_display(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam_pos[0], cam_pos[1], cam_pos[2], 0, 0, 0, 0, 1, 0);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	light.glLight_init();
	light.glLight_setSunLight();

	glDis_create_background();
	glDis_create_object();

	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glutPostRedisplay();
	glFlush();
}

void glDisplay::glDis_create_object() {
	for (int i = 0; i < 1; i++) {
		glTranslatef(pre_pos[0]-2, pre_pos[1]+31, pre_pos[2]+2);
		tetris.glTet_create_block(i);
	}
}

void glDisplay::glDis_create_background() {
	tetris.glTet_create_background();
}

void glDisplay::glDis_setTexID(unsigned int* tex_id) {

}

void glDisplay::glDis_norKey_press(unsigned char key) {
	keyboard.glInput_press_norKey(key, pre_pos);
	cout << pre_pos[0] << ' ' << pre_pos[1] << ' ' << pre_pos[2] << '\n';
}

void glDisplay::glDis_norKey_up(unsigned char key) {

}

void glDisplay::glDis_specKey_press(int key) {

}

void glDisplay::glDIs_specKey_up(int key) {

}