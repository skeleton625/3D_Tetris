#include "glLight.h"
#include "glCollider.h"
#include "glObject.h"
#include "stddef.h"	/* NULL�� �ĺ��ϱ� ���� ���� */

class glTetrisObj {
private:
	/* ������ ��� ������ QUEUE*/
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
	float block_size[3] = { 1, 1, 1 }; /* Object ũ�� */
	float plane_ambi[4] = { 1.0, 1.0, 1.0, 1.0 }; /* ��ü �ֺ��� */
	float plane_diff[4] = { 0.8, 0.8, 0.8, 1.0 }; /* ��ü ���̱� */
	float plane_spec[4] = { 0.7, 0.7, 0.7, 1.0 }; /* ��ü �ݻ籤 */
	unsigned int tex_id[10];
	int tetris_score;
	int field_rotate, rot_count; /* �ʵ� ��ü�� ȸ����Ű�� ���� */
	/* BLOCK�� ���� ��ġ */
	int pre_pos[3] = { 0, 21, 0 }, block_val;
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
	glLight obj_light; /* Tetris �⺻ Object���� �� ó�� ��ü */
	glCollider collider; /* BLOCK �浹 ó�� ��ü */
	glObject block[4];	/* BLOCK�� �̷�� ����ü 4�� */
	glObject plane[4]; /* BLOCK�� ���̰� �� �ٴڸ� ǥ�� */
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