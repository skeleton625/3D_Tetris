#include "glLight.h"

class glTetrisObj {
private:
	enum {BLOCK1, BLOCK2, BLOCK3, BLOCK4, BLOCK5, BLOCK6, BLOCK7};
	bool tetris_matrix[12][6][6];
	glLight obj_light;
	float plane_ambi[4] = { 0.8, 0.8, 0.8, 1.0 };
	float plane_diff[4] = { 0.4, 0.4, 0.4, 1.0 };
	float plane_spec[4] = { 0.2, 0.2, 0.2, 1.0 };
public:
	void glTet_init();
	void glTet_create_background();
	void glTet_create_block(int val);
	void glTet_set_pre_blocks();
	void glTet_set_block_pos(int pos[3]);
	bool glTet_is_block_pos(int pos[3]);
};