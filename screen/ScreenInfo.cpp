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

#include "ScreenInfo.hpp"

#include "utils/Callback.hpp"

#include "keyboard.hpp"

ScreenInfo::ScreenInfo(const char* message)
{
	bAccept = Button(5.0, CALLBACK(ScreenInfo, clickButtonAccept), message, KEY_ENTER);
	mItems.push_back(&bAccept);
}

ScreenInfo::~ScreenInfo()
{
  // empty
}

void ScreenInfo::clickButtonAccept()
{
	gMenuManager->popScreen();
}
