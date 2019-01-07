#include "glLight.h"
#include "glCollider.h"
#include "glObject.h"

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

			~node() { this->prev->next = this->next; }
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
	bool is_end = true;
	glLight obj_light; /* Tetris 기본 Object들의 빛 처리 객체 */
	glCollider collider; /* BLOCK 충돌 처리 객체 */
	glObject block[4];	/* BLOCK을 이루는 육면체 4개 */
	Tetris_queue queue;
	float block_size[3] = { 1, 1, 1 }; /* Object 크기 */
	/* 평면 빛 세기 */
	float plane_ambi[4] = { 0.8, 0.8, 0.8, 1.0 };
	float plane_diff[4] = { 0.4, 0.4, 0.4, 1.0 };
	float plane_spec[4] = { 0.2, 0.2, 0.2, 1.0 };
	/* BLOCK의 현재 위치 */
	int pre_pos[3] = { -2, 17, 2 }, block_val;
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
	int angle[3];	/* 회전 각도 */
public:
	void glTetris_init();
	bool glTetris_is_end();
	void glTet_create_background();
	void glTet_create_block(int val);
	void glTet_set_random_blocks();
	void glTet_move_block();
	bool glTet_block_trans(int x, int y, int z);
	void glTet_block_specKey(int key);
	void glTet_block_norKey(unsigned char key);
};