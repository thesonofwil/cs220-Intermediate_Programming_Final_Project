//Jingyu Huang
//jhuan146

#include "chasehero.h"
#include "position.h"
#include "entity.h"
#include "game.h"
#include "entitycontroller.h"
#include <vector>
#include <cstdlib>

ChaseHero::ChaseHero(){
}

ChaseHero::~ChaseHero(){
}

Direction ChaseHero::getMoveDirection(Game *game, Entity *entity){
  std::vector<Entity *> heroes;
  heroes = game->getEntitiesWithProperty('h');
  if(heroes.empty()){
    return Direction::NONE;
  }
  Position posminotaur = entity->getPosition();
  Position nearest;
  std::vector<Entity *>::iterator iter;
  for (iter = heroes.begin(); iter != heroes.end(); iter++){
    Position poshero = (*iter) -> getPosition();
    int distance2 = poshero.distanceFrom(posminotaur);
    int distance = distance2;
    if (distance2 > distance){
      distance = distance2;
      nearest = poshero;
    }
  }
  int horizontal = nearest.getX()-posminotaur.getX();
  int vertical = nearest.getY()-posminotaur.getY();
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

bool ChaseHero::isUser() const{
  return false;
}
