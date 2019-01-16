#include "glObject.h"
#include "OpenGL.h"

void glObject::glObj_create_sphere(float size[3]) {
	GLUquadric *sphere = gluNewQuadric();
	glPushMatrix(); {
		glTranslatef(x, y, z);
		glScalef(size[0], size[1], size[2]);
		gluQuadricTexture(sphere, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D, id);
		gluSphere(sphere, 1, 40, 100);
	}
	glPopMatrix();
}

void glObject::glObj_create_plane(float size[3], int clip) {
	glPushMatrix(); {
		glTranslatef(x, y, z);
		glScalef(size[0], size[1], size[2]);
		glBindTexture(GL_TEXTURE_2D, id);
		glBegin(clip); {
			for (int i = 0; i < 4; i++) {
				glTexCoord2fv(Tex[i]);
				glNormal3fv(plane[i]);
				glVertex3fv(plane[i]);
			}
		}
		glEnd();
	}
	glPopMatrix();
}

void glObject::glObj_create_cube(float size[3]) {
	glPushMatrix(); {
		glTranslatef(x, y, z);
		glScalef(size[0], size[1], size[2]);
		for (int i = 0; i < 6; i++) {
			glBindTexture(GL_TEXTURE_2D, id);
			glBegin(GL_QUADS);
			for (int j = 0; j < 4; j++) {
				glTexCoord2fv(Tex[i]);
				glNormal3fv(cube[i][j]);
				glVertex3fv(cube[i][j]);
			}
			glEnd();
		}
	}
	glPopMatrix();
}

void glObject::glObj_setX(float x) { this->x = x; }
void glObject::glObj_setY(float y) { this->y = y; }
void glObject::glObj_setZ(float z) { this->z = z; }
void glObject::glObj_set_texID(unsigned int id) { this->id = id; }
int glObject::glObj_getX() { return x; }
int glObject::glObj_getY() { return y; }
int glObject::glObj_getZ() { return z; }