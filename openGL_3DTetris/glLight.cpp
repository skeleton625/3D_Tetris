#include "glLight.h"
#include "glObject.h"
#include "OpenGL.h"

void glLight::glLight_init() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
}

void glLight::glLight_setSunLight() {
	glObject sun;
	float size[3] = { 1, 1, 1 };
	/* 빛의 위치와 빛의 밝기 지정 */
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambi);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diff);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);

	/* 태양 object 위치 지정 */
	sun.glObj_setX(light_pos[0]);
	sun.glObj_setY(light_pos[1]);
	sun.glObj_setZ(light_pos[2]);

	/* 태양 object 생성 */
	glLight_setObjectEmi();
	sun.glObj_create_sphere(size);
	glLight_setEmiFormat();
}

void glLight::glLight_setObjectLight(float ambi[4], float diff[4], float spec[4]) {
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
}

void glLight::glLight_setObjectEmi() {
	glMaterialfv(GL_FRONT, GL_EMISSION, light_emi);
}

void glLight::glLight_setEmiFormat() {
	glMaterialfv(GL_FRONT, GL_EMISSION, emi_format);
}