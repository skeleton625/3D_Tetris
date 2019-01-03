#include "glTexture.h"

void glTexture::glTex_init() {
	glEnable(GL_TEXTURE_GEN_S);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, plane_coef_s);
	glEnable(GL_TEXTURE_GEN_T);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, plane_coef_t);
}

unsigned int* glTexture::glTex_get_texID() {
	return tex_id;
}

void glTexture::glTex_create_texture(const char* str, int id_num) {
	tex[id_num] = auxDIBImageLoad(str);
	glGenTextures(2, &tex_id[id_num]);
	glBindTexture(GL_TEXTURE_2D, tex_id[id_num]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, tex[id_num]->sizeX, tex[id_num]->sizeY, 
		0, GL_RGB, GL_UNSIGNED_BYTE, tex[id_num]->data);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}