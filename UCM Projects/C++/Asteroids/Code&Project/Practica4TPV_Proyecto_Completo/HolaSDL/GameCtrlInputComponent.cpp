#include "GameCtrlInputComponent.h"
#include "GameManager.h"

GameCtrlInputComponent::GameCtrlInputComponent() {
}

GameCtrlInputComponent::~GameCtrlInputComponent() {
}

void GameCtrlInputComponent::handleInput(GameObject* o, Uint32 time, const SDL_Event& event) {

	GameManager* gm = static_cast<GameManager*>(o);

	if (event.type == SDL_KEYDOWN) {
		if (!gm->isRunning()) {
			if (gm->isGameOver()||gm->isWon()) {
				//debemos reinicializar los parámetros de vidas y meteoritos para empezar una nueva ronda
				if (gm->isWon())
					gm->newRound();
				else 
					gm->resetAllParameters();
			}
			gm->setRunning(true);
		}
	}

}
