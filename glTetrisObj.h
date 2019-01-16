#include "glLight.h"
#include "glCollider.h"
#include "glObject.h"
#include "stddef.h"	/* NULL을 식별하기 위해 정의 */

class glTetrisObj {
private:
	/* 무작위 블록 데이터 QUEUE*/
	class Tetris_queue {
	private:
		class node {
		private:
			int num;
			node *next, *prev;
		public:
			node(int num, node *prev) {
				this->prev = prev;
				this->num = num;
			}
			node* getPrev() { return this->prev; }
			node* getNext() { return this->next; }
			int getNum() { return this->num; }
			void setNext(int num) {
				node *n_node = new node(num, this);
				this->next = n_node;
			}
		};
		node *head, *tail;
		int count;
	public:
		void queue_init();
		void queue_push();
		int queue_pop();
	};
	bool is_end = false;
	float block_size[3] = { 1, 1, 1 }; /* Object 크기 */
	float plane_ambi[4] = { 1.0, 1.0, 1.0, 1.0 }; /* 물체 주변광 */
	float plane_diff[4] = { 0.8, 0.8, 0.8, 1.0 }; /* 물체 깊이광 */
	float plane_spec[4] = { 0.7, 0.7, 0.7, 1.0 }; /* 물체 반사광 */
	unsigned int tex_id[10];
	int tetris_score;
	int field_rotate, rot_count; /* 필드 전체를 회전시키는 변수 */
	/* BLOCK의 현재 위치 */
	int pre_pos[3] = { 0, 21, 0 }, block_val;
	/* 각 BLOCK들의 현재 위치 */
	int tetris_block[7][4][2] = {
		{{0,-1},{0,1},{1,-1},{0,0}},
		{{0,-1},{0,1},{-1,-1},{0,0}},
		{{1,1},{0,-1},{1,0},{0,0}},
		{{-1,1},{0,-1},{-1,0},{0,0}},
		{{-1,0},{0,1},{1,0},{0,0}},
		{{0,-1},{0,1},{0,2},{0,0}},
		{{0,0},{0,-1},{1,0},{1,-1}}
	};
	glLight obj_light; /* Tetris 기본 Object들의 빛 처리 객체 */
	glCollider collider; /* BLOCK 충돌 처리 객체 */
	glObject block[4];	/* BLOCK을 이루는 육면체 4개 */
	glObject plane[4]; /* BLOCK이 놓이게 될 바닥면 표시 */
	Tetris_queue queue;
public:
	void glTetris_init(unsigned int* tex_id);
	void glTetris_init();
	bool glTet_is_end();
	void glTet_create_background();
	void glTet_create_block();
	int glTet_getScore();
	void glTet_block_down();
	void glTet_block_cycle();
	void glTet_move_block();
	bool glTet_block_trans(int x, int y, int z);
	void glTet_block_specKey(int key);
	void glTet_block_norKey(unsigned char key);
};