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

#include "level/level.hpp"

#include "common.hpp"
#include "atlas.hpp"

#include "functions.hpp"

#include GL_H

const int sgEdgeX[4] = { 0, 1, 1, 0 };
const int sgEdgeY[4] = { 0, 0, 1, 1 };

Vector3 midpoint(const Vector3 quad[4])
{
	Vector3 mid(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < 4; i++)
	{
		mid = add(mid, scale(1.0f / 4.0f, quad[i]));
	}

	return mid;
}

static float area3Points(const Vector3& a, const Vector3& b, const Vector3& c)
{
	return 0.5f * ((b - a) ^ (c - a)).len();
}

void Square::updateAttributes()
{
	for (int i = 0; i < 4; i++)
	{
		vertices[i] += sgLevel.origin;
	}

	mid = midpoint(vertices);

	float area1 = area3Points(vertices[0], vertices[1], vertices[3]);
	float area2 = area3Points(vertices[2], vertices[1], vertices[3]);

	area = area1 + area2;
}

static int getFieldEdgeHeight(int x, int y, int edge)
{
	if (x >= 0 && y >= 0 && x < sgLevel.size.x && y < sgLevel.size.y)
	{
		Plate *p = &sgLevel.field[x][y];

		return 5 + p->z + (sgEdgeX[edge] * 2 - 1) * p->dzx + (sgEdgeY[edge] * 2 -
																													1) * p->dzy;
	}

	/* value out of range */
	return 0;
}

Plate* getPlate(int x, int y)
{
	Plate* p = &sgLevel.field[x][y];

	if (p->dirty)
	{
		Square* square = &p->roof;
		int dzx = p->dzx;
		int dzy = p->dzy;

		Vector3 ex;
		Vector3 ey;

		ex.x = 0.5f;
		ex.y = 0.0f;
		ex.z = (float) dzx / HEIGHT_STEPS;

		ey.x = 0.0f;
		ey.y = 0.5f;
		ey.z = (float) dzy / HEIGHT_STEPS;

		square->normal = norm(cross(ex, ey));

		for (int i = 0; i < 4; i++)
		{
			square->vertices[i].x = x + sgEdgeX[i];
			square->vertices[i].y = y + sgEdgeY[i];
			square->vertices[i].z =
				(float) getFieldEdgeHeight(x, y, i) / HEIGHT_STEPS;
		}

		square->updateAttributes();

		for (int side = 0; side < 4; side++)
		{
			int next = (side + 1) % 4;
			int prev = (side + 3) % 4;

			int sideOpposite = (side + 3) % 4;
			int nextOpposite = (side + 2) % 4;

			int dx = sgEdgeX[side] - sgEdgeX[prev];
			int dy = sgEdgeY[side] - sgEdgeY[prev];

			int height1 = getFieldEdgeHeight(x, y, side);
			int height2 = getFieldEdgeHeight(x, y, next);

			int height3 = getFieldEdgeHeight(x + dx, y + dy, sideOpposite);
			int height4 = getFieldEdgeHeight(x + dx, y + dy, nextOpposite);

			SideFace* face = &p->sideFaces[side];

			face->squares.clear();

			if (height1 > height3 || height2 > height4)
			{
				int x1 = x + sgEdgeX[side];
				int y1 = y + sgEdgeY[side];
				int x2 = x + sgEdgeX[next];
				int y2 = y + sgEdgeY[next];

				int startHeight = min(height3, height4);

				int minHeight;
				int maxHeight;
				int x3;
				int y3;

				int bottom;

				if (height1 > height2)
				{
					minHeight = height2;
					maxHeight = height1;
					x3 = x1;
					y3 = y1;
				}
				else
				{
					minHeight = height1;
					maxHeight = height2;
					x3 = x2;
					y3 = y2;
				}

				face->bottom = (float) startHeight / HEIGHT_STEPS;
				face->top = (float) maxHeight / HEIGHT_STEPS;

				for (bottom = startHeight; bottom < minHeight;)
				{
					int top =
						min(minHeight, bottom - (bottom % HEIGHT_STEPS) + HEIGHT_STEPS);

					face->squares.push_back(Square());
					square = &face->squares.back();

					square->normal.x = dx;
					square->normal.y = dy;
					square->normal.z = 0.0f;

					square->vertices[0].x = x1;
					square->vertices[0].y = y1;
					square->vertices[0].z = (float) top / HEIGHT_STEPS;

					square->vertices[1].x = x1;
					square->vertices[1].y = y1;
					square->vertices[1].z = (float) bottom / HEIGHT_STEPS;

					square->vertices[2].x = x2;
					square->vertices[2].y = y2;
					square->vertices[2].z = (float) bottom / HEIGHT_STEPS;

					square->vertices[3].x = x2;
					square->vertices[3].y = y2;
					square->vertices[3].z = (float) top / HEIGHT_STEPS;

					square->updateAttributes();

					bottom = top;
				}

				for (; bottom < maxHeight;)
				{
					int top =
						min(maxHeight, bottom - (bottom % HEIGHT_STEPS) + HEIGHT_STEPS);

					float t1 = (float) (bottom - minHeight) / (maxHeight - minHeight);
					float t2 = (float) (top - minHeight) / (maxHeight - minHeight);

					face->squares.push_back(Square());
					square = &face->squares.back();

					square->normal.x = dx;
					square->normal.y = dy;
					square->normal.z = 0.0f;

					square->vertices[0].x = x1 * (1.0f - t2) + x3 * t2;
					square->vertices[0].y = y1 * (1.0f - t2) + y3 * t2;
					square->vertices[0].z = (float) top / HEIGHT_STEPS;

					square->vertices[1].x = x1 * (1.0f - t1) + x3 * t1;
					square->vertices[1].y = y1 * (1.0f - t1) + y3 * t1;
					square->vertices[1].z = (float) bottom / HEIGHT_STEPS;

					square->vertices[2].x = x2 * (1.0f - t1) + x3 * t1;
					square->vertices[2].y = y2 * (1.0f - t1) + y3 * t1;
					square->vertices[2].z = (float) bottom / HEIGHT_STEPS;

					square->vertices[3].x = x2 * (1.0f - t2) + x3 * t2;
					square->vertices[3].y = y2 * (1.0f - t2) + y3 * t2;
					square->vertices[3].z = (float) top / HEIGHT_STEPS;

					square->updateAttributes();

					bottom = top;
				}
			}

		}

		p->dirty = false;
	}

	return p;
}

void initLevel()
{
	sgLevel.field = new Plate*[sgLevel.size.x];
	sgLevel.field[0] = new Plate[sgLevel.size.x * sgLevel.size.y];

	for (int x = 1; x < sgLevel.size.x; x++)
	{
		sgLevel.field[x] = &sgLevel.field[x - 1][sgLevel.size.y];
	}

	sgLevel.origin.x = -sgLevel.size.x / 2.0f;
	sgLevel.origin.y = 10.0f;
	sgLevel.origin.z = 0.0f;
}

void destroyLevel()
{
	delete[] sgLevel.field[0];
	delete[] sgLevel.field;

	sgLevel.size.x = -1;
	sgLevel.size.y = -1;

	destroyCommon();
}

void getRoofSquare(int x, int y, Square* square)
{
	Plate* p = getPlate(x, y);
	*square = p->roof;
}

void getSideFace(int x, int y, int side, SideFace* face)
{
	Plate* p = getPlate(x, y);
	*face = p->sideFaces[side];
}
