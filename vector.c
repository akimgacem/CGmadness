#include "vector.h"

#include <math.h>

/*
 * Dieses Modul f�hrt Vektor rechenoberationen aus. Die einzelnen Funktionen sind selbst erkl�rend.
 */

float sqr(float x) {
	return x * x;
}

float len(Vector3 v) {
	return sqrt(sqr(v.x) + sqr(v.y) + sqr(v.z));
}

void normalize(Vector3* v) {
	float l = len(*v);
	if (l > 0.0f) {
		v->x /= l;
		v->y /= l;
		v->z /= l;
	}
}

Vector3 norm(Vector3 v) {
	normalize(&v);
	return v;
}

Vector3 scale(float s, Vector3 a) {
	Vector3 b;

	b.x = s * a.x;
	b.y = s * a.y;
	b.z = s * a.z;

	return b;
}

Vector3 add(Vector3 a, Vector3 b) {
	Vector3 c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;

	return c;
}

Vector3 sub(Vector3 a, Vector3 b) {
	Vector3 c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;

	return c;
}

float dot(Vector3 a, Vector3 b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 cross(Vector3 a, Vector3 b) {
	Vector3 c;

	c.x = a.y * b.z - b.y * a.z;
	c.y = b.x * a.z - a.x * b.z;
	c.z = a.x * b.y - b.x * a.y;

	return c;
}

/*
 * Projektions-Matrix mit Farplane im Unendlichen
 */
void initProjectMat(Matrix m, float fovy) {
	int x;
	int y;
	float f = 1.0f / tan(fovy / 2.0f * PI / 180.0f);

	for (x = 0; x < 4; x++) {
		for (y = 0; y < 4; y++) {
			m[x][y] = 0.0f;
		}
	}

	m[0][0] = f;
	
	m[1][1] = f;
	
	m[2][2] = -1;
	m[2][3] = -1;
	
	m[3][2] = -2 * 0.01f;
}
