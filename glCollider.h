#pragma once
#include "glObject.h"
#include "glLight.h"

class glCollider {
private:
	bool tetris_matrix[14][7][7];
	int block_pos[5] = { 4, 2, 0, -2, -4 };
	float block_size[3] = { 1, 1, 1 }; /* Object Å©±â */
	float plane_ambi[4] = { 0.8, 0.8, 0.8, 1.0 };
	float plane_diff[4] = { 0.4, 0.4, 0.4, 1.0 };
	float plane_spec[4] = { 0.2, 0.2, 0.2, 1.0 };
	glLight light;
public:
	void glColli_init();
	int glColli_is_floor_full(int floor);
	void glColli_set_blocks_down(int floor);
	int glColli_crash_block();
	void glColli_rot_block_pos();
	bool glColli_is_block_pos(int x, int y, int z);
	int glColli_mark_block_floor(int x, int z);
	void glColli_set_block_pos(int x, int y, int z);
	void glColli_set_pre_blocks();
};