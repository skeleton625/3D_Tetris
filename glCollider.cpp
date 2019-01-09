#include "glCollider.h"
#include "OpenGL.h"

void glCollider::glColli_init() {
	for (int i = 1; i < 12; i++) {
		for (int j = 0; j < 7; j++) {
			tetris_matrix[i][0][j] = true;
			tetris_matrix[i][j][0] = true;
			tetris_matrix[i][j][6] = true;
			tetris_matrix[i][6][j] = true;
		}
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++)
			tetris_matrix[0][i][j] = true;
	}
}

bool glCollider::glColli_is_block_pos(int x, int y, int z) {
	return tetris_matrix[(y + 2) / 2][(x + 6) / 2][(z + 6) / 2];
}

void glCollider::glColli_set_block_pos(int x, int y, int z) {
	tetris_matrix[(y + 2) / 2][(x + 6) / 2][(z + 6) / 2] = true;
}

int glCollider::glColli_is_floor_full(int floor) {
	int count = 0;
	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 6; j++) {
			if (tetris_matrix[floor][i][j]) count++;
			else return count;
		}
	}
	return count;
}

void glCollider::glColli_crash_block() {
	int count = 0;
	for (int i = 1; i < 12; i++) {
		count = glColli_is_floor_full(i);
		if (count == 0) {
			glColli_set_blocks_down(count, i);
			return;
		} else if (count == 25) {
			count++;
		}
	}
}

void glCollider::glColli_set_blocks_down(int floor, int end) {
	for (int i = 1; i < floor; i++) {
		for (int j = 1; j < 6; j++) {
			for (int k = 1; k < 6; k++)
				tetris_matrix[0][j][k] = false;
		}
	}
	for (int i = floor; i < floor+end; i++) {
		for (int j = 1; j < 6; j++) {
			for (int k = 1; k < 6; k++) {
				tetris_matrix[i - floor][j][k] = tetris_matrix[i][j][k];
			}
		}
	}
}

void glCollider::glColli_set_pre_blocks() {
	glPushMatrix(); {
		glTranslatef(2, 17, -2);
		for (int i = 1; i < 12; i++) {
			for (int j = 1; j < 6; j++) {
				for (int k = 1; k < 6; k++) {
					glObject cube;
					cube.glObj_setX(i);
					cube.glObj_setY(j);
					cube.glObj_setZ(k);
					cube.glObj_create_cube(block_size);
					/*
					if (tetris_matrix[i][j][k]) {
						cube.glObj_setX(i);
						cube.glObj_setY(j);
						cube.glObj_setZ(k);
						cube.glObj_create_cube(block_size);
					}
					*/

				}
			}
		}
	}
	glPopMatrix();
}