#include "glTetrisObj.h"
#include "glObject.h"
#include "OpenGL.h"

void glTetrisObj::glTet_init() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			tetris_matrix[i][0][j] = true;
			tetris_matrix[i][j][0] = true;
		}
	}
}

void glTetrisObj::glTet_create_background() {

	obj_light.glLight_setObjectLight(plane_ambi, plane_diff, plane_spec);
	for (int i = 0; i < 4; i++) {
		glObject floor_pla;
		int floor_size[3] = { 1, 1, 1 };
		for (int j = 0; j < 4; j++) {
			floor_pla.glObj_setX(j+1);
			floor_pla.glObj_setY(0);
			floor_pla.glObj_setZ(i+1);
		}
	}
}

void glTetrisObj::glTet_create_block(int val) {

}

void glTetrisObj::glTet_set_pre_blocks() {

}

void glTetrisObj::glTet_set_block_pos(int pos[3]) {

}

bool glTetrisObj::glTet_is_block_pos(int pos[3]) {
	return tetris_matrix[pos[0]][pos[1]][pos[2]];
}