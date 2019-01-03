#include "glLight.h"
#include "glCollider.h"
#include "glObject.h"
enum { BLOCK1, BLOCK2, BLOCK3, BLOCK4, BLOCK5, BLOCK6, BLOCK7 };

class glTetrisObj {
private:
	glLight obj_light;
	glCollider collider;
	glObject block[4];
	float block_angle;
	bool block_stan[3];
	float plane_ambi[4] = { 0.8, 0.8, 0.8, 1.0 };
	float plane_diff[4] = { 0.4, 0.4, 0.4, 1.0 };
	float plane_spec[4] = { 0.2, 0.2, 0.2, 1.0 };
	// X, Z
	int tetris_block[7][4][2] = {
		{{0,-2}, {1,-2}, {1,-1}, {1,0}},
		{{0,0},{0,-1},{0,-2},{1,-2}},
		{{1,0},{1,-1},{0,-1},{0,-2}},
		{{0,0},{0,-1},{1,-1},{1,-2}},
		{{0,0},{0,-1},{0,-2},{0,-3}},
		{{1,0},{0,-1},{1,-1},{2,-1}},
		{{0,0},{0,-1},{1,0},{1,-1}}
	};
public:
	void glTetris_init();
	void glTet_create_background();
	void glTet_create_block(int val, int pos[3]);
	void glTet_block_trans(int key, int* pre_pos);
	void glTet_block_trans(unsigned char key, int* pre_pos);
};