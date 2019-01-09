#include "glCollider.h"
#include "OpenGL.h"
#include <iostream>
using namespace std;

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
			if (tetris_matrix[floor][i][j]) {
				count++;
			}
		}
	}
	return count;
}

void glCollider::glColli_crash_block() {
	int blocks = 0;
	for (int i = 1; i < 12; i++) {
		blocks = glColli_is_floor_full(i);
		cout << blocks << '\n';
		if (blocks == 25) {
			glColli_set_blocks_down(i);
		} else if(blocks == 0){
			break;
		}
	}
}

void glCollider::glColli_set_blocks_down(int floor) {
	for (int i = 1; i < 6; i++) {
		for (int j = 1; j < 6; j++) {
			tetris_matrix[floor][i][j] = false;
		}
	}
	int t_count = 0;
	for (int i = floor+1; i < 12; i++) {
		for (int j = 1; j < 6; j++) {
			for (int k = 1; k < 6; k++) {
				if (tetris_matrix[i][j][k]) {
					t_count++;
					tetris_matrix[i - 1][j][k] = tetris_matrix[i][j][k];
					tetris_matrix[i][j][k] = false;
				}
			}
		}
		if (t_count == 0) break;
		else t_count = 0;
	}
}

void glCollider::glColli_set_pre_blocks() {
	glPushMatrix(); {
		glObject cube;
		for (int i = 1; i < 12; i++) {
			for (int j = 1; j < 6; j++) {
				for (int k = 1; k < 6; k++) {
					if (tetris_matrix[i][j][k]) {
						cube.glObj_setX(block_pos[j-1]);
						cube.glObj_setY(i*2-1);
						cube.glObj_setZ(block_pos[k-1]);
						cube.glObj_create_cube(block_size);
					}
				}
			}
		}
	}
	glPopMatrix();
}