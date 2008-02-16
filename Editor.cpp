#include "Editor.hpp"

#include "editormenu.hpp"
#include "menumanager.hpp"

#include "level.hpp"
#include "ball.hpp"
#include "field.hpp"
#include "callback.hpp"
#include "camera.hpp"
#include "keyboard.hpp"
#include "atlas.hpp"
#include "common.hpp"

#include "functions.hpp"

#include "types.hpp"

#include <GL/glew.h>
#include <GL/glut.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>

Editor::Editor()
{
  // empty
}

Editor::~Editor()
{
  // empty
}

void Editor::init()
{
	initEditor();
}

void Editor::start()
{
	startEditor();
}

void Editor::update(float interval)
{
	updateEditor(interval);
}

void Editor::draw(void)
{
	drawEditor();
}

#define DRAW_DEBUG_LINES 0

typedef struct
{
	Vector3 v1;
	Vector3 v2;
} Line;

#if (DRAW_DEBUG_LINES)
Line gLines[10 * 10 * LIGHT_MAP_SIZE * LIGHT_MAP_SIZE * 32 * 8];
int gCntLines = 0;
#endif

static bool gIsEditorRunning;

static int gShowCursor;

static FieldCoord gCurStart;
static FieldCoord gCurEnd;
static int gCamAngle = 0;

static int gSin[] = { 0, 1, 0, -1 };
static int gCos[] = { 1, 0, -1, 0 };

static bool gDirtyTexCoords;
static bool gDirtyLightmaps;

static bool gIsTestMode;

void pauseEditor(void)
{
	showEditorScreen(0);
	gIsEditorRunning = false;
}

void startEditor(void)
{
	sgLevel.lightMap = 0;
	if (sgLevel.saved)
	{
		gDirtyLightmaps = false;
	}

	updateTexCoords();
	gDirtyTexCoords = false;

	gCurStart.x = 0;
	gCurStart.y = 0;
	gCurEnd.x = 0;
	gCurEnd.y = 0;

	gIsTestMode = 0;
	gShowCursor = 1;

	pauseEditor();
}

void stopEditor(void)
{
	gShowCursor = 0;
}

void resumeEditor(void)
{
	glutSetCursor(GLUT_CURSOR_NONE);
	gIsEditorRunning = true;
}

void lightMapsReady(void)
{
	gDirtyLightmaps = false;
	saveLevel();
}

void saveLevel(void)
{
	if (gDirtyLightmaps)
	{
		destroyCommon();

		initCommon();
		setUpdateFrequency(10);
		pushWaitScreen(lightMapsReady);
		updateLightMap(1);
	}
	else
	{
		if (saveLevelToFile())
		{
			sgLevel.saved = true;
			showEditorScreen(1);
		}
		else
		{
			showEditorScreen(2);
		}
	}
}

#if (DRAW_DEBUG_LINES)
void addLine(Vector3 v1, Vector3 v2)
{
	gLines[gCntLines].v1 = v1;
	gLines[gCntLines].v2 = v2;
	gCntLines++;
}
#endif

void updateEditorCamera(float interval, Vector3 marker)
{
	static float distance = 5.0f;
	static float height = 2.0f;
	static Vector3 dest(0.0f, 0.0f, 0.0f);
	float angle;

	/* camera controls for editor */

	/* zoom */
	if (isKeyPressed('v'))
		distance += 0.1f;
	if (isKeyPressed('c') && distance > 0.5)
		distance -= 0.1f;

	/* rotation */
	if (wasKeyPressed('b'))
		gCamAngle--;
	if (wasKeyPressed('n'))
		gCamAngle++;

	if (gCamAngle < 0)
		gCamAngle += 4;
	if (gCamAngle >= 4)
		gCamAngle -= 4;

	/* height */
	if (isKeyPressed('x'))
		height += 0.1f;
	if (isKeyPressed('y'))
		height -= 0.1f;

	angle = gCamAngle * 90.0f;

	/* new camera position */
	dest.x = sin(angle * M_PI / 180.0f) * distance + marker.x;
	dest.y = -cos(angle * M_PI / 180.0f) * distance + marker.y;
	dest.z = height + marker.z;

	moveCamera(interval, dest, marker);
}

void markerChanged(void)
{
	int x;
	int y;

	for (x = gCurStart.x - 1; x <= gCurEnd.x + 1; x++)
	{
		for (y = gCurStart.y - 1; y <= gCurEnd.y + 1; y++)
		{
			if (x >= 0 && y >= 0 && x < sgLevel.size.x && y < sgLevel.size.y)
			{
				sgLevel.field[x][y].dirty = 1;
			}
		}
	}

	sgLevel.saved = false;
	gDirtyLightmaps = true;
	gDirtyTexCoords = true;
}

void changeMarkerArea(int incz, int incdzx, int incdzy)
{
	int x;
	int y;
	int incx;
	int incy;

	incx = -(gCurEnd.x - gCurStart.x) * incdzx;

	for (x = gCurStart.x; x <= gCurEnd.x; x++)
	{
		incy = -(gCurEnd.y - gCurStart.y) * incdzy;

		for (y = gCurStart.y; y <= gCurEnd.y; y++)
		{
			Plate *p = &sgLevel.field[x][y];
			int z = p->z;
			int dzx = p->dzx;
			int dzy = p->dzy;

			z += incz + incx + incy;
			dzx += incdzx;
			dzy += incdzy;

			if (z - (abs(dzx) + abs(dzy)) >= 0
					&& (z + (abs(dzx) + abs(dzy))) <= MAX_LEVEL_HEIGHT * HEIGHT_STEPS
					&& abs(dzx) <= 5 && abs(dzy) <= 5)
			{
				p->z = z;
				p->dzx = dzx;
				p->dzy = dzy;
			}

			incy += 2 * incdzy;
		}

		incx += 2 * incdzx;
	}

	markerChanged();
}

void flattenMarkerArea(void)
{
	int x;
	int y;

	for (x = gCurStart.x; x <= gCurEnd.x; x++)
	{
		for (y = gCurStart.y; y <= gCurEnd.y; y++)
		{
			Plate *p = &sgLevel.field[x][y];

			p->dzx = 0;
			p->dzy = 0;
		}
	}

	markerChanged();
}


void modBetween(int *value, int mod, int min, int max)
{
	*value += mod;

	if (*value < min)
	{
		*value = min;
	}
	else if (*value >= max)
	{
		*value = max - 1;
	}
}

void moveMarker(int markermode, int dx, int dy)
{
	if (markermode)
	{
		modBetween(&gCurEnd.x, dx, gCurStart.x, sgLevel.size.x);
		modBetween(&gCurEnd.y, dy, gCurStart.y, sgLevel.size.y);
	}
	else
	{
		int sx = gCurEnd.x - gCurStart.x;
		int sy = gCurEnd.y - gCurStart.y;

		modBetween(&gCurStart.x, dx, 0, sgLevel.size.x - sx);
		modBetween(&gCurStart.y, dy, 0, sgLevel.size.y - sy);

		gCurEnd.x = gCurStart.x + sx;
		gCurEnd.y = gCurStart.y + sy;
	}
}

void moveMarkerLeft(int markermode)
{
	moveMarker(markermode, -gCos[gCamAngle], -gSin[gCamAngle]);
}

void moveMarkerRight(int markermode)
{
	moveMarker(markermode, gCos[gCamAngle], gSin[gCamAngle]);
}

void moveMarkerUp(int markermode)
{
	moveMarker(markermode, -gSin[gCamAngle], gCos[gCamAngle]);
}

void moveMarkerDown(int markermode)
{
	moveMarker(markermode, gSin[gCamAngle], -gCos[gCamAngle]);
}

void animateEditor(float interval)
{
	int markermode = 0;

	/* editor controls for changing environment */
	if (wasKeyPressed('a'))
	{
		changeMarkerArea(0, gCos[gCamAngle], gSin[gCamAngle]);
	}

	if (wasKeyPressed('d'))
	{
		changeMarkerArea(0, -gCos[gCamAngle], -gSin[gCamAngle]);
	}


	if (wasKeyPressed('s'))
	{
		changeMarkerArea(0, -gSin[gCamAngle], gCos[gCamAngle]);
	}

	if (wasKeyPressed('w'))
	{
		changeMarkerArea(0, gSin[gCamAngle], -gCos[gCamAngle]);
	}

	if (wasKeyPressed('f'))
	{
		changeMarkerArea(-1, 0, 0);
	}

	if (wasKeyPressed('r'))
	{
		changeMarkerArea(1, 0, 0);
	}

	if (wasKeyPressed('0'))
	{
		flattenMarkerArea();
	}

	/* editor controls for current field */
	if (wasKeyPressed('1'))
	{
		if (gCurStart.x != sgLevel.finish.x || gCurStart.y != sgLevel.finish.y)
		{
			sgLevel.start.x = gCurStart.x;
			sgLevel.start.y = gCurStart.y;
		}
	}

	if (wasKeyPressed('2'))
	{
		if (gCurStart.x != sgLevel.start.x || gCurStart.y != sgLevel.start.y)
		{
			sgLevel.finish.x = gCurStart.x;
			sgLevel.finish.y = gCurStart.y;
		}
	}

	markermode = getModifiers() == GLUT_ACTIVE_SHIFT;

	/*  editor controls for moving selection */
	if (wasCursorPressed(CURSOR_LEFT))
	{
		moveMarkerLeft(markermode);
	}

	if (wasCursorPressed(CURSOR_RIGHT))
	{
		moveMarkerRight(markermode);
	}

	if (wasCursorPressed(CURSOR_DOWN))
	{
		moveMarkerDown(markermode);
	}

	if (wasCursorPressed(CURSOR_UP))
	{
		moveMarkerUp(markermode);
	}
}

void enableTestMode(void)
{
	resetBall();
	resetBallCamera();
	changeBall(BALL_LAYOUT_TEXTURE);
	enableBallCamera();

	initGameField();

	gIsTestMode = 1;
	gShowCursor = 0;
}

void disableTestMode(void)
{
	destroyGameField();
	disableBallCamera();

	gIsTestMode = 0;
	gShowCursor = 1;
}

void updateEditor(float interval)
{
	if (!gIsEditorRunning)
	{
		updateMenuManager(interval);
	}
	else if (gIsTestMode)
	{
		if (wasKeyPressed(KEY_ESC))
		{
			disableTestMode();
		}

		updateBall(interval);
	}
	else
	{
		Vector3 markerPos;

		if (wasKeyPressed(KEY_ESC))
		{
			pauseEditor();
		}

		if (wasKeyPressed(KEY_ENTER))
		{
			enableTestMode();
		}

		markerPos.x = (gCurStart.x + gCurEnd.x) / 2.0f + 0.5f;
		markerPos.y = (gCurStart.y + gCurEnd.y) / 2.0f + 0.5f;
		markerPos.z =
			(float) sgLevel.field[gCurStart.x][gCurStart.y].z / HEIGHT_STEPS;

		updateEditorCamera(interval, add(markerPos, sgLevel.origin));
		animateEditor(interval);

		if (gDirtyTexCoords)
		{
			updateTexCoords();
			gDirtyTexCoords = false;
		}
	}
}

void drawEditorField(void)
{
	int i;
	int j;
	FieldCoord cur;
	Square square;

	float pos[4] = { 0.0f, 0.0f, 1.0f, 0.0f };

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);

	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sgLevel.borderTexture);

	for (cur.x = 0; cur.x < sgLevel.size.x; cur.x++)
	{
		for (cur.y = 0; cur.y < sgLevel.size.y; cur.y++)
		{

			if (gShowCursor && cur.x >= gCurStart.x && cur.x <= gCurEnd.x
					&& cur.y <= gCurEnd.y && cur.y >= gCurStart.y)
			{
				glColor3f(1.0f, 0.0f, 0.0f);
			}
			else if (cur.x == sgLevel.start.x && cur.y == sgLevel.start.y)
			{
				glColor3f(0.0f, 1.0f, 0.0f);
			}
			else if (cur.x == sgLevel.finish.x && cur.y == sgLevel.finish.y)
			{
				glColor3f(0.0f, 0.0f, 1.0f);
			}
			else
			{
				glColor3f(1.0f, 1.0f, 1.0f);
			}

			getRoofSquare(cur.x, cur.y, &square);

			glBegin(GL_QUADS);
			glNormal3fv(&square.normal.x);
			for (i = 0; i < 4; i++)
			{
				glTexCoord2fv(&square.texcoord[i].x);
				glVertex3fv(&square.vertices[i].x);
			}
			glEnd();

			glColor3f(1.0f, 1.0f, 1.0f);

			glBegin(GL_QUADS);
			for (j = 0; j < 4; j++)
			{
				SideFace face;
				int k;

				getSideFace(cur.x, cur.y, j, &face);

				for (k = 0; k < face.cntSquares; k++)
				{
					glNormal3fv(&face.squares[k].normal.x);
					for (i = 0; i < 4; i++)
					{
						glTexCoord2fv(&face.squares[k].texcoord[i].x);
						glVertex3fv(&face.squares[k].vertices[i].x);
					}
				}
			}
			glEnd();
		}
	}

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);

#if (DRAW_DEBUG_LINES)
	glBegin(GL_LINES);
	for (i = 0; i < gCntLines; i++)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(gLines[i].v1.x, gLines[i].v1.y, gLines[i].v1.z);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(gLines[i].v2.x, gLines[i].v2.y, gLines[i].v2.z);
	}
	glEnd();
#endif

	if (gIsTestMode)
	{
		drawGameBall();
	}
}

void drawEditor(void)
{
	drawEditorField();

	if (!gIsEditorRunning)
	{
		drawMenuManager();
	}
}

void initEditor(void)
{
	gShowCursor = 0;

	initEditorMenu();
}