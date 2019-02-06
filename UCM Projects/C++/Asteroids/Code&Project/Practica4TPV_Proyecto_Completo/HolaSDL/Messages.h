#ifndef MESSAGES_H_
#define MESSAGES_H_

#include "Asteroid.h"
#include "Bullet.h"
#include "Fighter.h"

enum MessageId {
	BULLET_ASTROID_COLLISION,
	BULLET_FIGHTER_COLLISION,
	ASTROID_FIGHTER_COLLISION,
	FIGHTER_SHOOT,
	GAME_OVER,
	ROUND_START,
	ROUND_OVER,
	BULLET_CREATED,
	NO_MORE_ATROIDS,
	BADGE_ON,
	BADGE_OFF
};

struct Message {
	Message(MessageId id) :
			id_(id) {
	}
	MessageId id_;
};

struct BulletAstroidCollision: Message {
	BulletAstroidCollision(Bullet* bullet, Asteroid* astroid) :
			Message(BULLET_ASTROID_COLLISION), bullet_(bullet), astroid_(
					astroid) {
	}
	Bullet* bullet_;
	Asteroid* astroid_;
};

struct BulletFighterCollision: Message {
	BulletFighterCollision(Bullet* bullet, Fighter* fighter) :
			Message(BULLET_FIGHTER_COLLISION), bullet_(bullet), fighter_(
					fighter) {
	}
	Bullet* bullet_;
	Fighter* fighter_;
};

struct AstroidFighterCollision: Message {
	AstroidFighterCollision(Asteroid* astroid, Fighter* fighter) :
			Message(ASTROID_FIGHTER_COLLISION), astroid_(astroid), fighter_(
					fighter) {
	}

	Asteroid* astroid_;
	Fighter* fighter_;
};

struct FighterIsShooting: Message {
	FighterIsShooting(Fighter* fighter, Vector2D bulletPosition,
			Vector2D bulletVelocity) :
			Message(FIGHTER_SHOOT), fighter_(fighter), bulletPosition_(
					bulletPosition), bulletVelocity_(bulletVelocity) {
	}

	Fighter* fighter_;
	Vector2D bulletPosition_;
	Vector2D bulletVelocity_;
};
#endif /* MESSAGES_H_ */
