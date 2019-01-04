#include "glTetrisObj.h"
#include "OpenGL.h"
#include <cmath>
#include <iostream>
using namespace std;

void glTetrisObj::glTetris_init() {
	collider.glColli_init();
}

void glTetrisObj::glTet_create_background() {
	// 기본 x = -1, y = -5, z = -1
	float floor_size[3] = { 1, 1, 1 };
	obj_light.glLight_setObjectLight(plane_ambi, plane_diff, plane_spec);
	// 테트리스 공간 바닥 생성
	glPushMatrix(); {
		for (int i = -2; i < 3; i++) {
			glObject floor_pla;
			for (int j = -2; j < 3; j++) {
				floor_pla.glObj_setX(-j*2);
				floor_pla.glObj_setY(0);
				floor_pla.glObj_setZ(-i*2);
				floor_pla.glObj_create_plane(floor_size);
			}
		}
	}
	glPopMatrix();
	// 테트리스 공간 옆, 뒷면 생성
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
						floor_pla.glObj_create_plane(floor_size);

					}
				}
			}
			glPopMatrix();
			glRotatef(-90, 0, 1, 0);
		}
	}
	glPopMatrix();
}

void glTetrisObj::glTet_create_block(int val) {
	block_val = val;
	glPushMatrix(); {
		// BLOCK 하나에 대한 이동과 회전
		glTranslatef(2, 17, -2);
		// BLOCK 하나(육면체 4개) 생성
		for (int i = 0; i < 4; i++) {
			block[i].glObj_setX(tetris_block[val][i][0] * 2);
			block[i].glObj_setY(0);
			block[i].glObj_setZ(tetris_block[val][i][1] * 2);
			block[i].glObj_create_cube(block_size);
		}
	}
	glPopMatrix();
	is_end = false;
}

void glTetrisObj::glTet_move_block() {
	glPushMatrix(); {
		// BLOCK 하나에 대한 이동과 회전
		glTranslatef(pre_pos[0], pre_pos[1], pre_pos[2]);
		// BLOCK 하나(육면체 4개) 생성
		for (int i = 0; i < 4; i++) {
			block[i].glObj_create_cube(block_size);
		}
	}
	glPopMatrix();
}

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
	switch (key) {
		case 'z':
			if(glTet_block_trans(pre_pos[0], pre_pos[1]-2, pre_pos[2])) 
				return;
			pre_pos[1] -= 2;
			break;
		case 'x': /* Y 축 기준 회전 */
			/* 
				한 번에 90도 씩 돌아가기 때문에 불필요한 계산식 제거
				(y축 기준)
				x = x*cos(t) + z*sin(t)
				z = z*cos(t) - x*sin(t)
			*/
			for (int i = 0; i < 3; i++) {
				x = block[i].glObj_getX();
				y = block[i].glObj_getY();
				z = block[i].glObj_getZ();
				if (collider.glColli_is_block_pos(-z + pre_pos[0], y + pre_pos[1], x + pre_pos[2]))
					return;
			}
			for (int i = 0; i < 3; i++) {
				x = block[i].glObj_getX();
				z = block[i].glObj_getZ();
				block[i].glObj_setX(-z);
				block[i].glObj_setZ(x);
			}
			break;
		case 'c': /* z 축 기준 회전 */
			/*
				한 번에 90도 씩 돌아가기 때문에 불필요한 계산식 제거
				(y축 기준)
				x = x*cos(t) - y*sin(t)
				z = y*cos(t) + x*sin(t)
			*/
			for (int i = 0; i < 3; i++) {
				x = block[i].glObj_getX();
				y = block[i].glObj_getY();
				z = block[i].glObj_getZ();
				if (collider.glColli_is_block_pos(-y + pre_pos[0], x + pre_pos[1], z + pre_pos[2]))
					return;
			}
			for (int i = 0; i < 3; i++) {
				x = block[i].glObj_getX();
				y = block[i].glObj_getY();
				block[i].glObj_setX(-y);
				block[i].glObj_setY(x);
			}
			break;
	}
}

bool glTetrisObj::glTetris_is_end() { return is_end; }