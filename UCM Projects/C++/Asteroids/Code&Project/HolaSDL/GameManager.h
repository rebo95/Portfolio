#pragma once

#include "Container.h"
#include "Observable.h"
#include "Observer.h"
#include "BadgeTimer.h"
#include "ScoreRenderer.h"
#include "LiveRenderer.h"
#include "GameMsgRenderer.h"
#include "GameCtrlInputComponent.h"
#include "BadgeRenderer.h"


class GameManager : public Container, public Observable, public Observer
{
public:
	GameManager(SDLGame* game);
	virtual~GameManager();

	bool isGameOver() const;
	bool isWon() const;
	int getLives() const;
	int getRound() const;
	bool isRunning() const;
	void setRunning(bool running);
	int getScore() const;
	void setBadges(bool b);
	void receive(Message* msg);
	void resetAllParameters();
	void newRound();
	bool isBadged();

private:

	LiveRenderer livesRenderer_;
	BadgeRenderer badgeRenderer_;
	BadgeRenderer badgeRendererSuperBullet_;
	BadgeRenderer badgeRendererMultiBullet_;
	ScoreRenderer scoreRenderer_;
	GameCtrlInputComponent gameCtrl_;
	GameMsgRenderer gameMsg_;
	BadgeTimer badgeTimer_;

	int lives_;
	int badgeCounter_;
	int points_;
	int round_;
	bool badgeActivated_;
	int activeBadge_;
	bool running_;
	bool gameOver_;
	bool won_;
};


