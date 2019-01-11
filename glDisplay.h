#include "glLight.h"
#include "glObject.h"
#include "glTetrisObj.h"

class glDisplay {
private:
	int rot_count;
	glLight light;
	glTetrisObj tetris;
	double cam_pos[3] = { -30, 35, -35 };
	double font_color[3] = { 1,1,1 };
public:
	void glDis_display();
	void glDis_block_down();
	void glDis_create_object();
	void glDis_create_background();
	void glDis_init(unsigned int* tex_id);
	void glDis_norKey_press(unsigned char key);
	void glDis_norKey_up(unsigned char key);
	void glDis_specKey_press(int key);
	void glDIs_specKey_up(int key);
	void Display_draw_text(int WinPosX, int WinPosY, const char* strMsg, void* font, double font_color[3]);
};