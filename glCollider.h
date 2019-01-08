#include "glObject.h"

class glCollider {
private:
	bool tetris_matrix[12][7][7];
public:
	void glColli_init();
	int glColli_is_floor_full(int floor);
	bool glColli_is_block_pos(int x, int y, int z);
	void glColli_set_block_pos(int x, int y, int z);
};