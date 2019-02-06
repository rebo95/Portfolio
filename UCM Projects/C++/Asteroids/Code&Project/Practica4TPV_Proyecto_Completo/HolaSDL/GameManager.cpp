#include "GameManager.h"



GameManager::GameManager(SDLGame* game) : Container(game), Observable(), Observer(), scoreRenderer_(ScoreRenderer()), livesRenderer_(LiveRenderer(game->getResources()->getImageTexture(Resources::Badges), 3, 3, 2, 2, 40, 40, 500, 2))
, badgeRenderer_(BadgeRenderer(game->getResources()->getImageTexture(Resources::Badges), 3, 3, 0, 1, 40, 40, 50, 50)), gameMsg_(GameMsgRenderer()), badgeTimer_(BadgeTimer()),
gameCtrl_(GameCtrlInputComponent())
{
	this->addRenderComponent(&scoreRenderer_);
	this->addRenderComponent(&livesRenderer_);
	this->addRenderComponent(&badgeRenderer_);
	this->addRenderComponent(&gameMsg_);
	this->addPhysicsComponent(&badgeTimer_);
	this->addInputComponent(&gameCtrl_);

	lives_ = 3;
	badgeCounter_ = 0;
	points_ = 0;
	round_ = 0;

	badgeActivated_ = false;
	gameOver_ = false;
	won_ = false;
	running_ = false;
}

GameManager::~GameManager()
{
}

void GameManager::receive(Message* msg) {
	switch (msg->id_)
	{
	case BULLET_ASTROID_COLLISION:
		//amenta la puntuación 
		//si el contador de asteroides destruidos llega a 10 se hace un envío de mensaje al fighter manager para activar el badge
		if (static_cast<BulletAstroidCollision*>(msg)->bullet_->isActive() && static_cast<BulletAstroidCollision*>(msg)->astroid_->isActive()) {
			points_ += 1;
			if (!badgeActivated_) {
				badgeCounter_++;
				if (badgeCounter_ >= 2) {
					setBadges(true);
					badgeTimer_.start(5000);
				}
			}
		}
		break;
	case ASTROID_FIGHTER_COLLISION:
		//resta vidas
		lives_--; // el Gm también recibe este mensaje
		points_ -= 1;
		if (points_ < 0) {//penalización por morir
			points_ = 0;
		}
		setBadges(false);
		if (lives_ == 0) {
			gameOver_ = true;
		}
		setRunning(false);
		break;
	case NO_MORE_ATROIDS:
		//asteroidsmanager envía mensaje de que no quedan asteroides en juego , emite mensaje de badge of y pone 
		won_ = true;
		setRunning(false);
		setBadges(false);
		break;
	}
}

bool GameManager::isGameOver() const {
	return gameOver_;
}

bool GameManager::isWon() const {
	return won_;
}


int GameManager::getLives() const { return lives_; }
int GameManager::getRound() const { return round_; }

bool GameManager::isRunning() const { return running_; }
void GameManager::setRunning(bool running) {

	if (running_ != running) {
		running_ = running;

		Message* m = new Message{ running ? ROUND_START : ROUND_OVER };
		send(m);

		delete(m);
		m = nullptr;

		if (gameOver_ && running)
			gameOver_ = false;

		if (won_ && running)
			won_ = false;
	}

}
int GameManager::getScore() const { return points_; }

void GameManager::setBadges(bool b) {
	//este método es el que envía los mensajes al fightermanager para que este active y desactive los badges del arma 
	Message* m;
	if (b) {
		m = new Message{ BADGE_ON };
		badgeActivated_ = true;
	}
	else {
		m = new Message{ BADGE_OFF };
		badgeActivated_ = false;
		badgeCounter_ = 0;
	}

	send(m);

	delete(m);
	m = nullptr;

}

void GameManager::resetAllParameters() {
	gameOver_ = false;
	won_ = false;
	lives_ = 3;
	points_ = 0;
}

void GameManager::newRound() {
	won_ = false;
	round_++;
	lives_ = 3;
}

bool GameManager::isBadged() {
	return badgeActivated_;

}