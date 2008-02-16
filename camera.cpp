/*
 * CG Madness - a Marble Madness clone
 * Copyright (C) 2007  Sven Reinck <sreinck@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "camera.hpp"

#include "callback.hpp"

#include <GL/glu.h>

Vector3 sgCamera;
Vector3 sgLookat;

void resetCamera(void)
{
	sgCamera.x = 0.0f;
	sgCamera.y = 0.0f;
	sgCamera.z = 1.0f;

	sgLookat.x = 0.0f;
	sgLookat.y = 0.0f;
	sgLookat.z = 0.0f;
}

void moveCamera(float interval, Vector3 camera, Vector3 lookat)
{
	Vector3 diff;
	Vector3 up = { 0.0f, 0.0f, 1.0f };
	float error;

	/* new values */
	diff = sub(camera, sgCamera);
	error = len(diff);
	sgCamera = add(sgCamera, scale(5.0f * interval * error, norm(diff)));

	diff = sub(lookat, sgLookat);
	error = len(diff);
	sgLookat = add(sgLookat, scale(5.0f * interval * error, norm(diff)));

	/* set camera */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(sgCamera.x, sgCamera.y, sgCamera.z,
						sgLookat.x, sgLookat.y, sgLookat.z, up.x, up.y, up.z);

	glGetFloatv(GL_MODELVIEW_MATRIX, &sgWindowViewport.view[0][0]);
}

Vector3 rotateVector(const Vector3& dir)
{
	Vector3 direction;
	
#if 1
	Viewport *v = &sgWindowViewport;
	
	direction.x =
		dir.x * v->view[0][0] + dir.y * v->view[0][1] + dir.z * v->view[0][2];
	direction.y =
		dir.x * v->view[1][0] + dir.y * v->view[1][1] + dir.z * v->view[1][2];
	direction.z =
		dir.x * v->view[2][0] + dir.y * v->view[2][1] + dir.z * v->view[2][2];
#else
	Matrix view;
	
	Vector3 f = sgLookat - sgCamera;
	
#endif
	
	return direction;
}
