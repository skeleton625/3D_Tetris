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

bool glCollider::glColli_is_block_pos(int x, int y, int z) {
	return tetris_matrix[(y + 2) / 2][(x + 6) / 2][(z+6) / 2];
}

void glCollider::glColli_set_block_pos(int x, int y, int z) {
	tetris_matrix[(y + 2) / 2][(x + 6) / 2][(z + 6) / 2] = true;
}