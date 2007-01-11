/*
 * CG Madness - a Marble Madness clone
 * Copyright (C) 2007  Sven Reinck
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
 *
 * $Id$
 *
 */

#include "mouse.h"

#include "callback.h"
#include "pick.h"

#include <GL/glut.h>

#define SELECT_BUFFER_SIZE 512

typedef struct {
	GLuint stackSize;
	GLuint minDepth;
	GLuint maxDepth;
	GLuint stackBottom;
} SelectBuffer;

static GLuint gSelectBuffer[SELECT_BUFFER_SIZE];

static MotionFunc gMotionFunc = 0;
static int gLastMouseX = 0;
static int gLastMouseY = 0;

/*
 * Mouse-Click Callback:
 * Ermittelt, ob ein Objekt geklickt wurde und
 * l�st entpsrechende Aktionen aus
 */
void mouseButton(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		int cntHits = pick(x, y);

		/* Select-Buffer auswerten */
		if (cntHits > 0) {
			GLuint minDepth = 0xffffffff;
			GLuint name = -1;
			GLuint* ptr = gSelectBuffer;
			int i;
			SelectBuffer* buf;

			/* Den Namen des Objektes herausfinden, dass am n�chsten an der Kamera gepickt wurde. */
			for (i = 0; i < cntHits; i++) {
				buf = (SelectBuffer*) ptr;

				if (buf->minDepth < minDepth) {
					minDepth = buf->minDepth;
					if (buf->stackSize > 0) {
						name = buf->stackBottom;
					} else {
						name = -1;
					}
				}

				ptr += 3 + buf->stackSize;
			}

			doPick(name);
		}
	}
}

void mouseMotion(int x, int y) {
	if (gMotionFunc) {
		centerMouse(&gLastMouseX, &gLastMouseY);
		gMotionFunc(x - gLastMouseX, y - gLastMouseY);
	}
}	

/*
 * Registriert Mouse-Button-Callback (wird ausgefuehrt, wenn eine Maustaste
 * gedrueckt oder losgelassen wird) 
 */
void startMouse(void) {
	/* SelectBuffer initialisieren */
	glSelectBuffer(SELECT_BUFFER_SIZE, gSelectBuffer);
	
	glutPassiveMotionFunc(mouseMotion);
}

void grabMouse(MotionFunc motionFunc) {
	glutSetCursor(GLUT_CURSOR_NONE);
	centerMouse(&gLastMouseX, &gLastMouseY);
  glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMotion);
	gMotionFunc = motionFunc;
}

void releaseMouse(void) {
	glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
  glutMouseFunc(NULL);
	glutMotionFunc(NULL);
	gMotionFunc = NULL;
}
