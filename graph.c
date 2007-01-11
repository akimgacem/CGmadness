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

#include "graph.h"

#include <GL/gl.h>

#include <stdio.h>

void initObject(Object* obj, funcDraw draw) {
	int i;

	/* Position auf Null setzen */
	obj->pos.x = 0.0f;
	obj->pos.y = 0.0f;
	obj->pos.z = 0.0f;

	obj->scaleX = 1.0f;
	obj->scaleY = 1.0f;
	obj->scaleZ = 1.0f;

  /* Matrix auf Einheitsmatrix initialisieren */
	for (i = 0; i < 16; i++) {
		obj->rotMatrix[i] = ((i % 4) == (i / 4)) ? 1.0f : 0.0f;
	}

	/* Farbe auf wei� setzen */
	obj->colRed = 1.0f;
	obj->colGreen = 1.0f;
	obj->colBlue = 1.0f;

	obj->ambient = 0.2f;
	obj->diffuse = 0.8f;
	obj->shininess = 0.0f;
	
	obj->texture = -1;

	obj->draw = draw;

	obj->pickName = -1;

	obj->visible = 1;
	
	obj->subObjects = NULL;
}

void initObjectGroup(Object* obj) {
	initObject(obj, NULL);
}

/*
 * Abk�rzungen
 */

void setObjectPosition2f(Object* obj, float x, float y) {
	obj->pos.x = x;
	obj->pos.y = y;
}

void setObjectPosition3f(Object* obj, float x, float y, float z) {
	obj->pos.x = x;
	obj->pos.y = y;
	obj->pos.z = z;
}

void setObjectColor(Object* obj, float r, float g, float b) {
	obj->colRed = r;
	obj->colGreen = g;
	obj->colBlue = b;
}

void setObjectGroupColor(Object* obj, float r, float g, float b) {
	List run;

	setObjectColor(obj, r, g, b);

	for (run = obj->subObjects; run; run = run->next) {
		Object* obj = run->info;
		setObjectGroupColor(obj, r, g, b);
	}
}

void rotateObject(Object* obj, float angle, float* axis) {
	int matrixMode;
	/* aktuellen Matrixmodus sichern */
	glGetIntegerv(GL_MATRIX_MODE, &matrixMode);
	glMatrixMode(GL_MODELVIEW);

  /* Rotation ausfuehren */
	glPushMatrix();
	glLoadIdentity();

	glRotatef(angle, axis[0], axis[1], axis[2]);

  /* Aktuelle Matrix mit der Objektmatrix multiplizieren */
	glMultMatrixf(obj->rotMatrix);
	/* Aktuelle Matrix in Objekt speichern */
	glGetFloatv(GL_MODELVIEW_MATRIX, obj->rotMatrix);
	/* Matrix von vor der Operation wiederherstellen */
	glPopMatrix();

	/* vorherigen Matrixmodus wiederherstellen */
	glMatrixMode(matrixMode);
}

void rotateObjectX(Object* obj, float angle) {
	float axis[] = { 1.0f, 0.0f, 0.0f };
	rotateObject(obj, angle, axis);
}

void rotateObjectY(Object* obj, float angle) {
	float axis[] = { 0.0f, 1.0f, 0.0f };
	rotateObject(obj, angle, axis);
}

void rotateObjectZ(Object* obj, float angle) {
	float axis[] = { 0.0f, 0.0f, 1.0f };
	rotateObject(obj, angle, axis);
}

void setObjectScalef(Object* obj, float scale) {
	obj->scaleX = scale;
	obj->scaleY = scale;
	obj->scaleZ = scale;
}

void setObjectScale2f(Object* obj, float x, float y) {
	obj->scaleX = x;
	obj->scaleY = y;
}

void setObjectScale3f(Object* obj, float x, float y, float z) {
	obj->scaleX = x;
	obj->scaleY = y;
	obj->scaleZ = z;
}

void addSubObject(Object* obj, Object* subObject) {
	obj->subObjects = appendElement(obj->subObjects, subObject);
}

void delSubObject(Object* obj, Object* subObject) {
	obj->subObjects = removeElement(obj->subObjects, subObject);
}

void clearSubObjects(Object* obj) {
	obj->subObjects = removeAll(obj->subObjects);
}

void setAttributes(float red, float green, float blue, float ambient, float diffuse, float shininess) {
	float matAmbient[4];
	float matDiffuse[4];
	float matSpecular[4];
	float specular;
	
	matAmbient[0] = ambient * red;
	matAmbient[1] = ambient * green;
	matAmbient[2] = ambient * blue;
	matAmbient[3] = 1.0f;

	matDiffuse[0] = diffuse * red;
	matDiffuse[1] = diffuse * green;
	matDiffuse[2] = diffuse * blue;
	matDiffuse[3] = 1.0f;

	specular = (shininess > 0.0f) ? 1.0f : 0.0f;
	matSpecular[0] = specular;
	matSpecular[1] = specular;
	matSpecular[2] = specular;
	matSpecular[3] = 1.0f;

	/* Objektmaterial setzen */
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

/* Durchlaeuft alle Objekte der Liste und zeichnet sie */
void pickList(List list) {
	List run;
	/* Alle Objekte der Liste durchlaufen */
	for (run = list; run; run = run->next) {
		Object* obj = run->info;
		pickObject(obj);
	}
}

void pickObject(Object* obj) {
	int isNameOnStack;
	
	if (!obj->visible) {
		return;
	}

	glPushMatrix();
	
	if (obj->pickName >= 0) {
		glPushName(obj->pickName);
		isNameOnStack = 1;
	} else {
		int stackDepth;
		glGetIntegerv(GL_NAME_STACK_DEPTH, &stackDepth);
		isNameOnStack = (stackDepth > 0);
	}

	/* Objekt transformieren */
	glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
	glMultMatrixf(obj->rotMatrix);
	glScalef(obj->scaleX, obj->scaleY, obj->scaleZ);

	if (obj->draw && isNameOnStack) {
		/* Zeichenroutine des Objektes aufrufen */
		obj->draw();
	}

	/* Zeichenroutine f�r Unter-Objekte aufrufen */
	pickList(obj->subObjects);
	
	if (obj->pickName >= 0) {
		glPopName();
	}

	glPopMatrix();
}

/* Durchlaeuft alle Objekte der Liste und zeichnet sie */
void drawList(List list) {
	List run;
	/* Alle Objekte der Liste durchlaufen */
	for (run = list; run; run = run->next) {
		Object* obj = run->info;
		drawObject(obj);
	}
}

void drawObject(Object* obj) {
	if (!obj->visible) {
		return;
	}

	glPushMatrix();
	
	/* Objekt auf Position verschieben */
	glTranslatef(obj->pos.x, obj->pos.y, obj->pos.z);
	/* Objekt rotieren */
	glMultMatrixf(obj->rotMatrix);
	/* Objekt skalieren */
	glScalef(obj->scaleX, obj->scaleY, obj->scaleZ);

	if (obj->draw) {
		int alpha = 0;

		setAttributes(obj->colRed, obj->colGreen, obj->colBlue, obj->ambient, obj->diffuse, obj->shininess);

		if (obj->texture > 0) {
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, obj->texture);

			glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_ALPHA_SIZE, &alpha);
		}
		
		if (alpha > 0) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		/* Zeichenroutine des jeweiligen Objektes aufrufen */
		obj->draw();

		if (alpha > 0) {
			glDisable(GL_BLEND);
		}

		if (obj->texture) {
			glDisable(GL_TEXTURE_2D);
		}
	}

	/* Zeichenroutine f�r Unter-Objekte aufrufen */
	drawList(obj->subObjects);

	glPopMatrix();
}
