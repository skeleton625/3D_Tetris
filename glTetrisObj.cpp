#include "glTetrisObj.h"
#include "OpenGL.h"

void glTetrisObj::glTetris_init() {
	collider.glColli_init();
}

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
				floor_pla.glObj_create_plane(floor_size);
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
					for (int k = 0; k < 8; k++) {
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
		// BLOCK �ϳ��� ���� �̵��� ȸ��
		glTranslatef(pre_pos[0], pre_pos[1], pre_pos[2]);
		// BLOCK �ϳ�(����ü 4��) ����
		for (int i = 0; i < 4; i++) {
			block[i].glObj_setX(tetris_block[val][i][0] * 2);
			block[i].glObj_setY(0);
			block[i].glObj_setZ(tetris_block[val][i][1] * 2);
			block[i].glObj_create_cube(block_size);
		}
	}
	glPopMatrix();
}

void glTetrisObj::glTet_block_trans(int key) {
	switch (key) {
		case GLUT_KEY_UP:
			pre_pos[2] += 2;
			break;
		case GLUT_KEY_DOWN:
			pre_pos[2] -= 2;
			break;
		case GLUT_KEY_LEFT:
			pre_pos[0] += 2;
			break;
		case GLUT_KEY_RIGHT:
			pre_pos[0] -= 2;
			break;
	}
}

void glTetrisObj::glTet_block_trans(unsigned char key) {
	switch (key) {
		case 'z':
			pre_pos[1] -= 2;
			break;
		case 'x': /* Y �� ���� ȸ�� */
			break;
		case 'c': /* z �� ���� ȸ�� */
			break;
	}
}