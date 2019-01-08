#include "glObject.h"

class glCollider {
private:
	bool tetris_matrix[12][7][7];
	int block_pos[5] = { -4 - 2, 0, 2, 4 };
	glObject cubes;
public:
	void glColli_init();
	int glColli_is_floor_full(int floor);
	void glColli_crash_block();
	void glColli_set_blocks_down(int floor, int end);
	bool glColli_is_block_pos(int x, int y, int z);
	void glColli_set_block_pos(int x, int y, int z);
	void glColli_set_pre_blocks();
};