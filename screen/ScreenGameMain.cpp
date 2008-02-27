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

#include "ScreenGameMain.hpp"

#include "PlayersBall.hpp"

#include "screen/ScreenGameHelp.hpp"

#include "MenuManager.hpp"

#include "utils/Singleton.hpp"

#include "features.hpp"
#include "keyboard.hpp"
#include "main.hpp"

static Singleton<MenuManager> gMenuManager;
static Singleton<ScreenGameHelp> gScreenHelp;

static void clickButtonHelp()
{
	gMenuManager->pushScreen(gScreenHelp);
}

static void clickButtonQuit()
{
	gMenuManager->popScreen();
	setMainState(STATE_MAIN);
}

static void changeBallEdit(const void *self)
{
	// TODO
#if 0
	PlayersBall::sgoBall.changeBall(gBallLayouts[((SpinEdit *) self)->value]);
#endif
}

static void changeBallShadow(const void *self)
{
	const Check *check = (const Check *) self;
	setBallShadow(check->value);
}

static void changeReflection(const void *self)
{
	const Check *check = (const Check *) self;
	setReflection(check->value);
}

ScreenGameMain::ScreenGameMain()
{
	gBallLayouts.push_back(BALL_LAYOUT_DEFAULT);

	if (Ball::hasBallTexture())
	{
		gBallLayouts.push_back(BALL_LAYOUT_TEXTURE);
	}

	if (PlayersBall::sgoBall.hasCubeMap())
	{
		gBallLayouts.push_back(BALL_LAYOUT_METAL);
	}

	if (hasGolfballShader())
	{
		gBallLayouts.push_back(BALL_LAYOUT_GOLFBALL);
	}

	if (hasGolfballShader() && PlayersBall::sgoBall.hasCubeMap())
	{
		gBallLayouts.push_back(BALL_LAYOUT_GOLFBALL_METAL);
	}

	gseBall = SpinEdit(gBallLayouts.size() - 1, 0, gBallLayouts.size() - 1, 4.3, 5.2f, drawMenuBall, changeBallEdit);
	mItems.push_back(&gseBall);

	gcBallShadow = Check(4.0f, changeBallShadow, "ball shadow");
	mItems.push_back(&gcBallShadow);
	
	gcReflection = Check(3.0f, changeReflection, "reflection");
	mItems.push_back(&gcReflection);

	bHelp = Button(2.0f, clickButtonHelp, "help", 'h');
	mItems.push_back(&bHelp);
	
	bQuit = Button(1.0f, clickButtonQuit, "give up", KEY_ESC);
	mItems.push_back(&bQuit);
}

ScreenGameMain::~ScreenGameMain()
{
  // empty
}

void ScreenGameMain::show()
{
	gcBallShadow.set(useBallShadow());
	gcReflection.set(useReflection());
	changeBallEdit(&gseBall);
}
