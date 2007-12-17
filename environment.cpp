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

#include "environment.hpp"

#include "features.hpp"
#include "skysphere.hpp"
#include "skyplane.hpp"
#include "water.hpp"

#include "field.hpp"
#include "ball.hpp"

#include <GL/gl.h>

#define REFLECTION 1
#define SKY 1
#define WATER 1

void initEnvironment(void)
{
	initSkysphere();
	initSkyplane();
	initWater();
}

void updateEnvironment(float interval)
{
	updateWater(interval);
}

void drawEnvironment(funcDraw reflection)
{
#if (WATER)
	if (useReflection())
	{
		GLdouble equation[4] = { 0.0f, 0.0f, 1.0f, 0.0f };

		glPushMatrix();

		glScalef(1.0f, 1.0f, -1.0f);
		glClipPlane(GL_CLIP_PLANE0, equation);

		glEnable(GL_CLIP_PLANE0);
		glCullFace(GL_FRONT);

#  if (SKY)
		glDisable(GL_DEPTH_TEST);
		drawSkysphere();
		drawSkyplane();
		glEnable(GL_DEPTH_TEST);
#  endif

		if (reflection)
		{
			reflection();
		}

		glCullFace(GL_BACK);
		glDisable(GL_CLIP_PLANE0);

		glPopMatrix();
	}

	drawWater();
# endif

#if (SKY)
	glDisable(GL_DEPTH_TEST);
	drawSkysphere();
	drawSkyplane();
	glEnable(GL_DEPTH_TEST);
#endif
}