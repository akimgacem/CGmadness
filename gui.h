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

#ifndef _gui_h_
#define _gui_h_

#include "vector.h"
#include "mouse.h"
#include "types.h"

typedef void (*funcClick)(void);

typedef void (*funcChange)(void* self);

/***/

typedef enum {
	MI_LABEL,
	MI_PROGRESS_BAR,
	MI_BUTTON,
	MI_CHECK,
	MI_SPIN_EDIT
} MenuItemType;

typedef struct {
	MenuItemType type;

	Vector2 position;
	float width;
	float height;

	int hover;
	float emphasize;
} MenuItem;

typedef struct Menu {
	int cntItems;
	MenuItem** items;

	struct Menu* back;
} Menu;

typedef struct {
	MenuItem item;

	char* text;
} Label;

typedef struct {
	MenuItem item;

	float* progress;
} ProgressBar;

typedef struct {
	MenuItem item;

	char* text;

	funcClick click;
} Button;

typedef struct {
	MenuItem item;

	char* text;
	int value;

	funcChange change;
} Check;

typedef struct {
	MenuItem item;

	int value;
	int minValue;
	int maxValue;

	int side;

	funcDraw draw;
	funcChange change;
} SpinEdit;

void initGUI(void);

void setSomeLight(void);

/* Label */

void initLabel(Label* label, float x, float z, int alignRight, char* text);

/* ProgressBar */

void initProgressBar(ProgressBar* progressBar, float z, float* progress);

/* Button */

void initButton(Button* button, float z, funcClick click, char* text);

/* Check */

void setCheck(Check* check, int value);
void initCheck(Check* check, float z, funcChange change, char* text);

/* SpinEdit */

void initSpinEdit(SpinEdit* spinedit, int value, int min, int max, float z, funcDraw draw, funcChange change);

/* Menu */

#define INIT_MENU(menu, items) initMenu((menu), LENGTH(items), (items))

void initMenu(Menu* menu, int cntItems, MenuItem** items);
void showMenu(Menu* menu);
void updateMenu(Menu* menu, float interval);
void drawMenu(const Menu* menu);
void eventMenu(Menu* menu, float x, float y, MouseEvent event);

#endif
