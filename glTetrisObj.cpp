#include "glTetrisObj.h"
#include "OpenGL.h"

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
				glTranslatef(5, 3, 0);
				glRotatef(-90, 0, 0, 1);
				for (int j = -2; j < 3; j++) {
					glObject floor_pla;
					for (int k = 0; k < 8; k++) {
						floor_pla.glObj_setX(-k * 2);
						floor_pla.glObj_setY(0);
						floor_pla.glObj_setZ(-j * 2);
						floor_pla.glObj_create_plane(floor_size);

					}
				}
			}
			glPopMatrix();
			glTranslatef(2, 0, 0);
			glRotatef(-90, 0, 1, 0);
		}
	}
	glPopMatrix();
}

void glTetrisObj::glTet_create_block(int val, int pos[3]) {
	float block_size[3] = { 1, 1, 1 };
	glPushMatrix(); {
		glTranslatef(pos[0], pos[1], pos[2]);
		glRotatef(block_angle, block_stan[0], block_stan[1], block_stan[2]);
		for (int i = 0; i < 4; i++) {
			block[i].glObj_setX(tetris_block[val][i][0] * 2);
			block[i].glObj_setY(0);
			block[i].glObj_setZ(tetris_block[val][i][1] * 2);
			block[i].glObj_create_cube(block_size, block_angle, block_stan);
		}
	}
	glPopMatrix();
}

void glTetrisObj::glTet_block_trans(int key, int* pre_pos) {
	switch (key) {
		case GLUT_KEY_UP:
			for (int i = 0; i < 4; i++) {
				if (collider.glColli_is_block_pos(block[i].glObj_getX(), 
					block[i].glObj_getY(), block[i].glObj_getZ()+2)){
					return;
				}
			}
			pre_pos[2] += 2;
			break;
		case GLUT_KEY_DOWN:
			for (int i = 0; i < 4; i++) {
				if (collider.glColli_is_block_pos(block[i].glObj_getX(),
					block[i].glObj_getY(), block[i].glObj_getZ()-2)) {
					return;
				}
			}
			pre_pos[2] -= 2;
			break;
		case GLUT_KEY_LEFT:
			for (int i = 0; i < 4; i++) {
				if (collider.glColli_is_block_pos(block[i].glObj_getX()+2,
					block[i].glObj_getY(), block[i].glObj_getZ())) {
					return;
				}
			}
			pre_pos[0] += 2;
			break;
		case GLUT_KEY_RIGHT:
			for (int i = 0; i < 4; i++) {
				if (collider.glColli_is_block_pos(block[i].glObj_getX()-2,
					block[i].glObj_getY(), block[i].glObj_getZ())) {
					return;
				}
			}
			pre_pos[0] -= 2;
			break;
	}
}

void glTetrisObj::glTet_block_trans(unsigned char key, int* pre_pos) {
	switch (key) {
		case 'z':
			for (int i = 0; i < 4; i++) {
				if (collider.glColli_is_block_pos(block[i].glObj_getX(),
					block[i].glObj_getY() - 2, block[i].glObj_getZ())) {
					return;
				}
			}
			pre_pos[1] -= 2;
			break;
		case 'x':
			if (!block_stan[1]) {
				block_stan[0] = false;
				block_stan[1] = true;
				block_stan[2] = false;
			}
			if (block_angle < 360) block_angle += 90;
			else block_angle = 90;
			break;
	}
}