#include "glObject.h"

class glCollider {
private:
	bool tetris_matrix[7][10][7];
public:
	void glColli_init();
	void glColli_set_block_pos(int x, int y, int z, bool is_block);
	bool glColli_is_block_pos(int x, int y, int z);
	bool glColli_set_block_rot(glObject* obj, char angle, int rot);
};