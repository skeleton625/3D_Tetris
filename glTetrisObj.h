#include "glLight.h"
#include "glCollider.h"
#include "glObject.h"

class glTetrisObj {
private:
	bool is_end = true;
	glLight obj_light;
	glCollider collider;
	glObject block[4];	/* BLOCK�� �̷�� ����ü 4�� */
	float block_size[3] = { 1, 1, 1 }; /* Object ũ�� */
	/* ��� �� ���� */
	float plane_ambi[4] = { 0.8, 0.8, 0.8, 1.0 };
	float plane_diff[4] = { 0.4, 0.4, 0.4, 1.0 };
	float plane_spec[4] = { 0.2, 0.2, 0.2, 1.0 };

	/* BLOCK�� ���� ��ġ */
	int pre_pos[3] = { -2, 17, 2 }, block_val;
	/* �� BLOCK���� ���� ��ġ */
	int tetris_block[7][4][2] = {
		{{0,-1},{0,1},{1,-1},{0,0}},
		{{0,-1},{0,1},{-1,-1},{0,0}},
		{{1,1},{0,-1},{1,0},{0,0}},
		{{-1,1},{0,-1},{-1,0},{0,0}},
		{{-1,0},{0,1},{1,0},{0,0}},
		{{0,-1},{0,1},{0,2},{0,0}},
		{{0,0},{0,-1},{1,0},{1,-1}}
	};
	int angle[3];	/* ȸ�� ���� */
public:
	void glTetris_init();
	bool glTetris_is_end();
	void glTet_create_background();
	void glTet_create_block(int val);
	void glTet_move_block();
	bool glTet_block_trans(int x, int y, int z);
	void glTet_block_specKey(int key);
	void glTet_block_norKey(unsigned char key);
};