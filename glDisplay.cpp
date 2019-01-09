#include "OpenGL.h"
#include "glDisplay.h"
#include "glCollider.h"

glCollider colli;

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

void glDisplay::glDis_block_down() {
	tetris.glTet_block_down();
}

void glDisplay::glDis_create_object() {
	if(tetris.glTetris_is_end()) tetris.glTet_create_block(0);
	else tetris.glTet_move_block();
}

void glDisplay::glDis_create_background() {
	tetris.glTet_create_background();
}

void glDisplay::glDis_init(unsigned int* tex_id) {
	tetris.glTetris_init();
}

void glDisplay::glDis_norKey_press(unsigned char key) {
	tetris.glTet_block_norKey(key);
}

void glDisplay::glDis_norKey_up(unsigned char key) {
}

void glDisplay::glDis_specKey_press(int key) {
	tetris.glTet_block_specKey(key);
}

void glDisplay::glDIs_specKey_up(int key) {

}