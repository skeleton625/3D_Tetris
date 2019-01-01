#include "glLight.h"
#include "glObject.h"

class glDisplay {
private:
	glLight light;
	double cam_pos[3] = { 0, 0, 0 };
public:
	void glDis_display();
	void glDis_create_object();
	void glDis_create_background();
	void glDis_setTexID(unsigned int* tex_id);
	void glDis_norKey_press(unsigned char key);
	void glDis_norKey_up(unsigned char key);
	void glDis_specKey_press(int key);
	void glDIs_specKey_up(int key);
};