//Brhea D'Mello
//bdmello2

#include "AStarChaseHero.h"

AStarChaseHero ::AStarChaseHero(){
}

AStarChaseHero::~AStarChaseHero(){
}

Direction AStarChaseHero::getMoveDirection(Game *game, Entity *entity) {
  return Direction::UP;
}

bool AStarChaseHero::isUser() const {
        return false;
}



