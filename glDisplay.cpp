#include "OpenGL.h"
#include "glDisplay.h"
#include "glCollider.h"
#include <string>
using namespace std;

glCollider colli;

void glDisplay::Display_draw_text(int WinPosX, int WinPosY, const char* strMsg, void* font, double font_color[3])
{
	int len = (int)strlen(strMsg);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glPushMatrix(); {
		glColor3f(font_color[0], font_color[1], font_color[2]);
		glRasterPos2f(WinPosX, WinPosY);
		for (int i = 0; i < len; ++i)
		{
			glutBitmapCharacter(font, strMsg[i]);
		}
	}
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

void glDisplay::glDis_display(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cam_pos[0], cam_pos[1], cam_pos[2], 0, 0, 0, 0, 1, 0);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	light.glLight_init();
	if (!tetris.glTet_is_end()) {
		light.glLight_setSunLight();
		Display_draw_text(-15, 20,
			to_string(tetris.glTet_getScore()).c_str(),
			GLUT_BITMAP_TIMES_ROMAN_24, font_color);
		glPushMatrix(); {
			glDis_create_background();
			glDis_create_object();
		}
	} else {
		Display_draw_text(25, -5,
			"If you want to restart the game, Press 'ESC'!",
			GLUT_BITMAP_TIMES_ROMAN_24, font_color);
	}
	glPopMatrix();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glutPostRedisplay();
	glFlush();
}

void glDisplay::glDis_block_cycle() {
	tetris.glTet_block_cycle();
}

void glDisplay::glDis_create_object() {
	if (game_start) {
		tetris.glTet_create_block();
		game_start = false;
	}
	else tetris.glTet_move_block();
}

void glDisplay::glDis_create_background() {
		tetris.glTet_create_background();
}

void glDisplay::glDis_init(unsigned int* tex_id) {
	tetris.glTetris_init(tex_id);
}

void glDisplay::glDis_norKey_press(unsigned char key) {
	switch (key) {
	case 27:
		if (tetris.glTet_is_end()) {
			tetris.glTetris_init();
			game_start = true;
		}
		break;
	default:
		tetris.glTet_block_norKey(key);
	}
}

void glDisplay::glDis_norKey_up(unsigned char key) {
}

void glDisplay::glDis_specKey_press(int key) {
	tetris.glTet_block_specKey(key);
}

void glDisplay::glDIs_specKey_up(int key) {

}