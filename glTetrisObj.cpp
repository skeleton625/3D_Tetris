#include "glTetrisObj.h"
#include "glObject.h"
#include "OpenGL.h"

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
	float block_size[3] = { 1, 1, 1 };
	for (int i = 0; i < 4; i++) {
		glObject block;
		block.glObj_setX(tetris_block[val][i][0]*2);
		block.glObj_setZ(tetris_block[val][i][1]*2);
		block.glObj_create_cube(block_size);
	}
}

void glTetrisObj::glTet_set_pre_blocks() {

}

void glTetrisObj::glTet_set_block_pos(int pos[3]) {

}