#pragma once

class glObject {
private:
	unsigned int id;
	float x, y, z;
	float Tex[4][2] = {
		{0, 0},
		{1, 0},
		{1, 1},
		{0, 1}
	};
	float plane[4][3] = {
		{0, 1, 0}, {2, 1, 0}, 
		{2, 1, 2}, {0, 1, 2}
	};
	float cube[6][4][3] = { 
		{ {0, 0, 2}, {0, 2, 2}, {2, 2, 2}, {2, 0, 2} },
		{ {0, 0, 0}, {0, 2, 0}, {2, 2, 0}, {2, 0, 0} },
		{ {0, 0, 2}, {0, 0, 0}, {0, 2, 0}, {0, 2, 2} },
		{ {2, 0, 2}, {2, 0, 0}, {2, 2, 0}, {2, 2, 2} },
		{ {0, 0, 2}, {2, 0, 2}, {2, 0, 0}, {0, 0, 0} },
		{ {0, 2, 2}, {2, 2, 2}, {2, 2, 0}, {0, 2, 0} } 
	};
public:
	void glObj_create_sphere(float size[3]);
	void glObj_create_plane(float size[3]);
	void glObj_create_cube(float size[3], float angle, bool stan[3]);
	void glObj_setX(float x);
	void glObj_setY(float y);
	void glObj_setZ(float z);
	void glObj_set_texID(unsigned int id);
	float glObj_getX();
	float glObj_getY();
	float glObj_getZ();
};