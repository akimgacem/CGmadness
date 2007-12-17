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

#include "functions.hpp"

#include <math.h>

float sqr(float x)
{
	return x * x;
}

float min(float a, float b)
{
	return (a < b) ? a : b;
}

int mini(int a, int b)
{
	return (a < b) ? a : b;
}

float max(float a, float b)
{
	return (a > b) ? a : b;
}

int maxi(int a, int b)
{
	return (a > b) ? a : b;
}

float clamp(float x, float lo, float up)
{
	return min(up, max(lo, x));
}

int clampi(int x, int lo, int up)
{
	return mini(up, maxi(lo, x));
}

int between(int x, int min, int max)
{
	return x >= min && x <= max;
}