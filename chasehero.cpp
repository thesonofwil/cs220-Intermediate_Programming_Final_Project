//Jingyu Huang
//jhuan146

#include "chasehero.h"
#include "position.h"
#include "entity.h"
#include "game.h"
#include "entitycontroller.h"
#include "gamerules.h"
#include <vector>
#include <cstdlib>

ChaseHero::ChaseHero(){
}

ChaseHero::~ChaseHero(){
}

Direction ChaseHero::getMoveDirection(Game *game, Entity *entity){
  std::vector<Entity *> heroes;
  heroes = game->getEntitiesWithProperty('h');
  //Return NONE if vector heroes is empty
  if(heroes.empty()){
    return Direction::NONE;
  }
  //Find closest hero from the minotaur
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
  //Decide direction to move towards a minotaur
  int horizontal = nearest.getX()-posminotaur.getX();
  int vertical = nearest.getY()-posminotaur.getY();
  GameRules* gamerules = game -> getGameRules();
  bool available1 = gamerules -> allowMove(game, entity, posminotaur, posminotaur.displace(Direction::UP));
  bool available2 = gamerules -> allowMove(game, entity, posminotaur, posminotaur.displace(Direction::DOWN));
  bool available3 = gamerules -> allowMove(game, entity, posminotaur, posminotaur.displace(Direction::LEFT));
  bool available4 = gamerules -> allowMove(game, entity, posminotaur, posminotaur.displace(Direction::RIGHT));
  if(abs(vertical)<abs(horizontal)){
    if(available3 && available4){
      if(horizontal<0){
        return Direction::LEFT;
      }else{
        return Direction::RIGHT;
      }
    }
    else if(available1 && available2){
      if(vertical<0){
        return Direction::UP;
      }else{
        return Direction::DOWN;
      }
    }
  }
  else{
    if(available1 && available2){
      if(vertical<0){
        return Direction::UP;
      }else{
        return Direction::DOWN;
      }
    }
    else if(available3 && available4){
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
