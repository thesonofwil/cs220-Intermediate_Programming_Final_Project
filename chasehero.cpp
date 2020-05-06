//Brhea D'Mello
//bdmello2
//Jingyu Huang
//jhuan146
//Wilson Tjoeng
//wtjoeng1

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
  Position poshero = (*heroes.begin()) -> getPosition();
  int distance = poshero.distanceFrom(posminotaur);
  Position nearest = poshero;
  std::vector<Entity *>::iterator iter;
  for (iter = heroes.begin(); iter != heroes.end(); iter++){
    poshero = (*iter) -> getPosition();
    int distance2 = poshero.distanceFrom(posminotaur);
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
  //Cases where preferred move can be performed
  if(abs(vertical)<=abs(horizontal)){
    if(horizontal<0){
      if(available3){	
        return Direction::LEFT;
      }
    }else{
      if(available4){
        return Direction::RIGHT;
      }
    }
  }
  else{
    if(vertical<0){
      if(available1){
        return Direction::UP;
      }
    }else{
      if(available2){
        return Direction::DOWN;
      }
    }
  }
  //Cases where preferred move is invalid
  if(vertical<0){
    if(available1){
      return Direction::UP;
    }
  }
  if(vertical>0){
    if(available2){
      return Direction::DOWN;
    }
  }
  if(horizontal<0){
    if(available3){
      return Direction::LEFT;
    }
  }
  if(horizontal>0){
    if(available4){
      return Direction::RIGHT;
    }
  }
  return Direction::NONE;
}

bool ChaseHero::isUser() const{
  return false;
}
