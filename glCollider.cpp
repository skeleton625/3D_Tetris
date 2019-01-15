#include "glCollider.h"
#include "OpenGL.h"
#include "string"

void glCollider::glColli_init() {
	for (int i = 1; i < 12; i++) {
		for (int j = 0; j < 7; j++) {
			tetris_matrix[i][0][j] = true;
			tetris_matrix[i][j][0] = true;
			tetris_matrix[i][j][6] = true;
			tetris_matrix[i][6][j] = true;
		}
	}
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++)
			tetris_matrix[0][i][j] = true;
	}
	for (int i = 1; i < 12; i++) {
		for (int j = 1; j < 6; j++) {
			for (int k = 1; k < 6; k++)
				tetris_matrix[i][j][k] = false;
		}
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

void glCollider::glColli_rot_block_pos() {
	int blocks;
	for (int i = 1; i < 12; i++) {
		blocks = glColli_is_floor_full(i);
		if(blocks != 0){
			bool tmp_matrix[7][7] = { 
				{1,1,1,1,1,1,1}, 
				{0,}, {0,}, {0,}, {0,}, {0,}, 
				{1,1,1,1,1,1,1}
			};
			for (int j = 1; j < 6; j++) {
				tmp_matrix[j][0] = 1;
				for (int k = 1; k < 6; k++) {
					if (tetris_matrix[i][j][k])
						tmp_matrix[6 - k][j] = tetris_matrix[i][j][k];
				}
				tmp_matrix[j][6] = 1;
			}
			memcpy(tetris_matrix[i], tmp_matrix, sizeof(tetris_matrix[i]));
		} else {
			break;
		}
	}
}

int glCollider::glColli_crash_block() {
	int blocks = 0, crash_count = 0;
	for (int i = 1; i < 12; i++) {
		blocks = glColli_is_floor_full(i);
		if (blocks == 25) {
			glColli_set_blocks_down(i);
			crash_count++;
		} else if(blocks == 0){
			if (i == 11) { return -1; }
			break;
		}
	}
	return crash_count;
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
		glRotatef(-180, 0, 1, 0);
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