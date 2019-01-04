#include "glObject.h"

class glCollider {
private:
	bool tetris_matrix[7][12][7];
public:
	void glColli_init();
	bool glColli_is_block_pos(int x, int y, int z);
};