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

#ifndef ScreenChooseEditor_hpp
#define ScreenChooseEditor_hpp

#include "ScreenChoose.hpp"

#include "gui/Button.hpp"
#include "gui/Canvas.hpp"

class ScreenChooseEditor : public ScreenChoose
{
public:
  ScreenChooseEditor();
  virtual ~ScreenChooseEditor();

private:
	Button bChooseEditor;

	Canvas cLevelInfo;

};

#endif
