#include "glTetrisObj.h"
#include "OpenGL.h"
#include <ctime>
#include <random>
#include <iostream>
using namespace std;

void glTetrisObj::glTetris_init(unsigned int* tex_id) {
	collider.glColli_init();
	queue.queue_init();
	for(int i = 0; i < 10; i++)
		this->tex_id[i] = tex_id[i];
}

void glTetrisObj::glTetris_init() {
	is_end = false;
	tetris_score = 0;
	collider.glColli_init();
	queue.queue_init();
}

bool glTetrisObj::glTet_is_end() { return is_end; }

int glTetrisObj::glTet_getScore() { return tetris_score; };


void glTetrisObj::glTet_create_background() {
	// �⺻ x = -1, y = -5, z = -1
	float floor_size[3] = { 1, 1, 1 };
	obj_light.glLight_setObjectLight(plane_ambi, plane_diff, plane_spec);
	// ��Ʈ���� ���� �ٴ� ����
	glPushMatrix(); {
		for (int i = -2; i < 3; i++) {
			glObject floor_pla;
			for (int j = -2; j < 3; j++) {
				floor_pla.glObj_setX(-j*2);
				floor_pla.glObj_setY(0);
				floor_pla.glObj_setZ(-i*2);
				floor_pla.glObj_create_plane(floor_size, GL_LINE_LOOP);
			}
		}
	}
	glPopMatrix();
	// ��Ʈ���� ���� ��, �޸� ����
	glPushMatrix(); {
		for (int i = 0; i < 2; i++) {
			glPushMatrix(); {
				glTranslatef(5, 1, 0);
				glRotatef(-90, 0, 0, 1);
				for (int j = -2; j < 3; j++) {
					glObject floor_pla;
					for (int k = 0; k < 10; k++) {
						floor_pla.glObj_setX(-k * 2);
						floor_pla.glObj_setY(0);
						floor_pla.glObj_setZ(-j * 2);
						floor_pla.glObj_create_plane(floor_size, GL_LINE_LOOP);

					}
				}
			}
			glPopMatrix();
			glRotatef(-90, 0, 1, 0);
		}
	}
	glPopMatrix();
	collider.glColli_set_pre_blocks();
}

void glTetrisObj::glTet_create_block() {
	block_val = queue.queue_pop();
	glPushMatrix(); {
		for (int i = 0; i < 4; i++) {
			plane[i].glObj_setX(tetris_block[block_val][i][0] * 2);
			plane[i].glObj_setY(0);
			plane[i].glObj_setZ(tetris_block[block_val][i][1] * 2);
			plane[i].glObj_set_texID(tex_id[6]);
			plane[i].glObj_create_plane(block_size, GL_QUADS);
		}
		glTranslatef(0, 21, 0);
		// BLOCK �ϳ�(����ü 4��) ����
		for (int i = 0; i < 4; i++) {
			block[i].glObj_setX(tetris_block[block_val][i][0] * 2);
			block[i].glObj_setY(0);
			block[i].glObj_setZ(tetris_block[block_val][i][1] * 2);
			block[i].glObj_set_texID(tex_id[block_val]);
			block[i].glObj_create_cube(block_size);
		}
	}
	glPopMatrix();
	queue.queue_push();
}

void glTetrisObj::glTet_move_block() {
	glPushMatrix(); {
		glTranslatef(pre_pos[0],0,pre_pos[2]);
		for (int i = 0; i < 4; i++) {
			plane[i].glObj_setY(collider.glColli_mark_block_floor(
			pre_pos[0]+plane[i].glObj_getX(), pre_pos[2]+plane[i].glObj_getZ())*2);
			plane[i].glObj_create_plane(block_size, GL_QUADS);
		}
		// BLOCK �ϳ��� ���� �̵��� ȸ��
		glTranslatef(0, pre_pos[1], 0);
		// BLOCK �ϳ�(����ü 4��) ����
		for (int i = 0; i < 4; i++)
			block[i].glObj_create_cube(block_size);
	}
	glPopMatrix();
}

void glTetrisObj::glTet_block_down() {
	int is_crash;
	if (glTet_block_trans(pre_pos[0], pre_pos[1] - 2, pre_pos[2])) {
		/* ���� BLOCK�� �ִ� ��ġ�� BLOCK�� �ִٴ� ���� ǥ�� */
		for (int i = 0; i < 4; i++) {
			collider.glColli_set_block_pos(
				block[i].glObj_getX() + pre_pos[0],
				block[i].glObj_getY() + pre_pos[1],
				block[i].glObj_getZ() + pre_pos[2]
			);
		}
		/* BLOCK���� �� �� ���� �����ϰ� ���� BLOCK���� �Ʒ��� ���� */
		is_crash = collider.glColli_crash_block();
		if (is_crash == -1) {
			is_end = true;
		} else {
			tetris_score += is_crash * 100;
		}
		/* BLOCK�� �ʱ� ��ġ�� �̵���Ŵ */
		pre_pos[0] = 0;
		pre_pos[1] = 21;
		pre_pos[2] = 0;
		/* ������ BLOCK ���� */
		glTet_create_block();
	}
}

void glTetrisObj::glTet_block_cycle() {
	int count = 0;
	while (1) {
		glTet_block_down();
		/* 1.5�ʿ� �� ���� �Ʒ��� �̵� */
		pre_pos[1] -= 2; /* �ð��� ������ ���� BLOCK�� �Ʒ��� �̵���Ŵ */
		_sleep(1500);
	}
}

/* BLOCK�� �̵��Ϸ��� ��ġ�� �ٸ� BLOCK�� �ִ��� Ȯ���ϴ� �Լ� */
bool glTetrisObj::glTet_block_trans(int x, int y, int z) {
	int obj_x, obj_y, obj_z;
	for (int i = 0; i < 4; i++) {
		obj_x = block[i].glObj_getX();
		obj_y = block[i].glObj_getY();
		obj_z = block[i].glObj_getZ();
		if (collider.glColli_is_block_pos(x+obj_x, y+obj_y, z+obj_z)) return true;
	}
	return false;
}

void glTetrisObj::glTet_block_specKey(int key) {
	switch (key) {
		case GLUT_KEY_UP:
			if (glTet_block_trans(pre_pos[0], pre_pos[1], pre_pos[2] + 2))
				return;
			pre_pos[2] += 2;
			break;
		case GLUT_KEY_DOWN:
			if(glTet_block_trans(pre_pos[0], pre_pos[1], pre_pos[2]-2)) 
				return;
			pre_pos[2] -= 2;
			break;
		case GLUT_KEY_LEFT:
			if(glTet_block_trans(pre_pos[0]+2, pre_pos[1], pre_pos[2])) 
				return;
			pre_pos[0] += 2;
			break;
		case GLUT_KEY_RIGHT:
			if(glTet_block_trans(pre_pos[0]-2, pre_pos[1], pre_pos[2])) 
				return;
			pre_pos[0] -= 2;
			break;
	}
}

void glTetrisObj::glTet_block_norKey(unsigned char key) {
	int x, y, z;
	int tmp = 0;
	switch (key) {
		case 'a':
			if (glTet_block_trans(pre_pos[0], pre_pos[1] - 2, pre_pos[2])) {
				glTet_block_down();
				return;
			}
			pre_pos[1] -= 2;
			break;
		case 's':
			
			collider.glColli_rot_block_pos();
			for (int i = 0; i < 4; i++) {
				x = block[i].glObj_getX();
				y = block[i].glObj_getY();
				z = block[i].glObj_getZ();
				if (collider.glColli_is_block_pos(-z - pre_pos[2], y + pre_pos[1], x + pre_pos[0]))
					return;
			}
			for (int i = 0; i < 4; i++) {
				x = block[i].glObj_getX();
				z = block[i].glObj_getZ();
				block[i].glObj_setX(-z);
				block[i].glObj_setZ(x);
				plane[i].glObj_setX(-z);
				plane[i].glObj_setZ(x);
			}
			tmp = pre_pos[0];
			pre_pos[0] = -pre_pos[2];
			pre_pos[2] = tmp;
			break;
		case 'z': /* Y �� ���� ȸ�� */
			/* 
				�� ���� 90�� �� ���ư��� ������ ���ʿ��� ���� ����
				(y�� ����)
				x = x*cos(t) + z*sin(t)
				z = z*cos(t) - x*sin(t)
			*/
			for (int i = 0; i < 4; i++) {
				x = block[i].glObj_getX();
				y = block[i].glObj_getY();
				z = block[i].glObj_getZ();
				if (collider.glColli_is_block_pos(-z + pre_pos[0], y + pre_pos[1], x + pre_pos[2]))
					return;
			}
			for (int i = 0; i < 4; i++) {
				x = block[i].glObj_getX();
				z = block[i].glObj_getZ();
				block[i].glObj_setX(-z);
				block[i].glObj_setZ(x);
				plane[i].glObj_setX(-z);
				plane[i].glObj_setZ(x);
			}
			break;
		case 'x': /* z �� ���� ȸ�� */
			/*
				�� ���� 90�� �� ���ư��� ������ ���ʿ��� ���� ����
				(y�� ����)
				x = x*cos(t) - y*sin(t)
				z = y*cos(t) + x*sin(t)
			*/
			for (int i = 0; i < 4; i++) {
				x = block[i].glObj_getX();
				y = block[i].glObj_getY();
				z = block[i].glObj_getZ();
				if (collider.glColli_is_block_pos(-y + pre_pos[0], x + pre_pos[1], z + pre_pos[2]))
					return;
			}
			for (int i = 0; i < 4; i++) {
				x = block[i].glObj_getX();
				y = block[i].glObj_getY();
				block[i].glObj_setX(-y);
				block[i].glObj_setY(x);
				plane[i].glObj_setX(-y);
				plane[i].glObj_setY(x);
			}
			break;
		case 'c':
			/*
				�� ���� 90�� �� ���ư��� ������ ���ʿ��� ���� ����
				(y�� ����)
				y = y*cos(t) - z*sin(t)
				z = z*cos(t) + y*sin(t)
			*/
			for (int i = 0; i < 4; i++) {
				x = block[i].glObj_getX();
				y = block[i].glObj_getY();
				z = block[i].glObj_getZ();
				if (collider.glColli_is_block_pos(x + pre_pos[0], -z + pre_pos[1], y + pre_pos[2]))
					return;
			}
			for (int i = 0; i < 4; i++) {
				y = block[i].glObj_getY();
				z = block[i].glObj_getZ();
				block[i].glObj_setY(-z);
				block[i].glObj_setZ(y);
				plane[i].glObj_setY(-z);
				plane[i].glObj_setZ(y);
			}
			break;
	}
}

void glTetrisObj::Tetris_queue::queue_init() {
	srand(time(0));
	head = new node(rand()%7, NULL);
	node *tmp = head;
	for (int i = 0; i < 3; i++) {
		tmp->setNext(rand()%7);
		tmp = tmp->getNext();
	}
	tail = tmp;
}

void glTetrisObj::Tetris_queue::queue_push() {
	srand(time(0));
	int num = rand() % 7;
	tail->setNext(num);
	tail = tail->getNext();
}

int glTetrisObj::Tetris_queue::queue_pop() {
	node *tmp = head->getNext();
	int re = head->getNum();
	delete head;
	head = tmp;
	return re;
}