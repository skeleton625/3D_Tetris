#include "glCollider.h"
#include "cmath"

void glCollider::glColli_init() {
	for (int i = 1; i < 10; i++) {
		for (int j = 0; j < 7; j++) {
			tetris_matrix[0][i][j] = true;
			tetris_matrix[j][i][0] = true;
			tetris_matrix[j][i][6] = true;
			tetris_matrix[6][i][j] = true;
		}
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++)
			tetris_matrix[i][0][j] = true;
	}
}

void glCollider::glColli_set_block_pos(int x, int y, int z, bool is_block) {
	this->tetris_matrix[(x+6)/2][(y+2)/2][(z+6)/2] = is_block;
}

bool glCollider::glColli_is_block_pos(int x, int y, int z) {
	return tetris_matrix[(x+6)/2][(y+2) / 2][(z+6) / 2];
}

bool glCollider::glColli_set_block_rot(glObject* obj, char angle, int rot) {
	return false;
}