#include "RaceTheClock.hpp"

#include "level.hpp"
#include "highscore.hpp"
#include "gamemenu.hpp"
#include "text.hpp"

#include "functions.hpp"

#include <GL/gl.h>

#include <stdio.h>

RaceTheClock::RaceTheClock()
{
  // empty
}

RaceTheClock::~RaceTheClock()
{
  // empty
}

void RaceTheClock::resetGame()
{
	Game::resetGame();
	resetGameTime();
}

void RaceTheClock::update(float interval)
{
	Game::update(interval);
	
	if (gIsGameRunning)
	{
		if (!sgoBall.isInPieces())
		{
			gGameTime += interval;
		}

		if (sgoBall.hasHitGoal())
		{
			finishedGame();
		}
	}
}

void RaceTheClock::drawHUD(float widthWindow, float heightWindow)
{
	int tenthSecond = (int) (gGameTime * 10.0f);
	float scale = 0.06f;
	float widthDefault = widthStrokeText("x:xx.x") * scale;

	char strTime[10];
	float width;
	float height;

	sprintf(strTime, "%d:%02d.%01d", tenthSecond / 600, tenthSecond / 10 % 60,
					tenthSecond % 10);

	width = widthStrokeText(strTime) * scale;
	height = scale;

	glColor3f(1.0f, 1.0f, 0.0f);

	glPushMatrix();

	glTranslatef((widthWindow - widthDefault) / 2.0f, (heightWindow - height),
							 0.0f);
	glScalef(scale, scale, scale);

	drawStrokeThickText(strTime);

	glPopMatrix();
}

void RaceTheClock::resetGameTime()
{
	gGameTime = 0.0f;
}

void RaceTheClock::stopWatch()
{
	int i;

	int tenthSecond = (int) (gGameTime * 10.0f);
	int newIndex = sgLevel.cntScoreCols;

	while (newIndex > 0 && tenthSecond < sgLevel.scores[newIndex - 1].tenthSecond)
	{
		newIndex--;
	}

	sgLevel.cntScoreCols = min(sgLevel.cntScoreCols + 1, MAX_SCORE_COLS);

	for (i = sgLevel.cntScoreCols - 1; i > newIndex; i--)
	{
		sgLevel.scores[i] = sgLevel.scores[i - 1];
	}

	if (newIndex < MAX_SCORE_COLS)
	{
		sgLevel.scores[newIndex].name[0] = '\0';
		sgLevel.scores[newIndex].tenthSecond = tenthSecond;
	}

	sgLastPlayerIndex = newIndex;
}

void RaceTheClock::finishedGame()
{
	stopWatch();
	pauseGame();
	showGameMenu(2);
}
