#include "glLight.h"
#include "glObject.h"
#include "glTetrisObj.h"

class glDisplay {
private:
	glLight light;
	glTetrisObj tetris;
	double cam_pos[3] = { -30, 40, -30 };
public:
	void glDis_display();
	void glDis_create_object();
	void glDis_create_background();
	void glDis_init(unsigned int* tex_id);
	void glDis_norKey_press(unsigned char key);
	void glDis_norKey_up(unsigned char key);
	void glDis_specKey_press(int key);
	void glDIs_specKey_up(int key);
};