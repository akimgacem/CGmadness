/*
 * CG Madness - a Marble Madness clone
 * Copyright (C) 2007  Sven Reinck <sreinck@gmx.de>
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

#ifndef _level_h_
#define _level_h_

#include "vector.h"

#define MAX_LEVEL_HEIGHT 10
#define HEIGHT_STEPS 10

typedef struct
{
	Vector3 normal;
	Vector2 colormap[4];
	Vector2 lightmap[4];
	Vector2 texcoord[4];
	Vector3 vertices[4];

	float area;
	Vector3 mid;
} Square;

typedef struct
{
	int cntSquares;
	Square squares[MAX_LEVEL_HEIGHT + 2];

	float bottom;
	float top;
} SideFace;

typedef struct
{
	int z;
	int dzx;
	int dzy;

	int dirty;
	Square roof;

	SideFace sideFaces[4];
} Plate;

typedef struct
{
	int x;
	int y;
} FieldCoord;

typedef struct
{
	Plate** field;
	FieldCoord start;
	FieldCoord finish;
	FieldCoord size;
	unsigned int borderTexture;
	unsigned int colorMap;
	unsigned int lightMap;

	int waiting;
} Level;

extern const int sgEdgeX[4];
extern const int sgEdgeY[4];

extern Level sgLevel;

void initLevel(void);
void destroyLevel(void);

void newLevel(void);
int loadFieldFromFile(const char* filename);
int saveFieldToFile(const char* filename);

void updatePlate(int x, int y);
void getRoofSquare(int x, int y, Square* square);
void getSideFace(int x, int y, int side, SideFace* face);

float getMaxZValue(const Square* square);

#endif