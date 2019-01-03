#include "glaux.h"
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")

class glTexture {
private:
	unsigned int tex_id[10];
	AUX_RGBImageRec *tex[10];
	GLfloat plane_coef_s[4] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat plane_coef_t[4] = { 0.0,1.0,0.0,1.0 };
public:
	void glTex_init();
	unsigned int* glTex_get_texID();
	void glTex_create_texture(const char* str, int id_num);
};