//Brhea D'Mello
//bdmello2

#include "astarchasehero.h"
#include <vector>

AStarChaseHero ::AStarChaseHero(){
}

AStarChaseHero::~AStarChaseHero(){
}

Direction AStarChaseHero::getMoveDirection(Game *game, Entity *entity) {
  
  std::vector<Entity *> heroes = game->getEntitiesWithProperty('h');
  Position posminotaur = entity ->getPosition();
  Entity *curr = heroes[0];
  Position poshero = curr->getPosition();
  int distance = poshero.distanceFrom(posminotaur);
  
  for (int i = 0; i < heroes.size(); i++){
    curr = heroes[i];
    poshero = curr->getPosition();
    int distance2 = poshero.distanceFrom(posminotaur);
    Position nearest;
    if (distance2 > distance){
      distance = distance2;
      nearest = poshero;
    }
  }
  
  int horizontal = poshero.getX()-posminotaur.getX();
  int vertical = poshero.getY()-posminotaur.getY();
  
  if(vertical == 0){
    if(horizontal<0){
      return Direction::LEFT;
    }else{
      return Direction::RIGHT;
    }
  }
  else if(horizontal == 0){
    if(vertical<0){
      return Direction::UP;
    }else{
      return Direction::DOWN;
    }
  }
  else{
    if(abs(horizontal)>abs(vertical)){
      if(vertical<0){
        return Direction::UP;
      }else{
        return Direction::DOWN;
      }
    }else{
      if(horizontal<0){
        return Direction::LEFT;
      }else{
        return Direction::RIGHT;
      }
    }
  }
  return Direction::NONE;
}

bool AStarChaseHero::isUser() const {
        return false;
}



