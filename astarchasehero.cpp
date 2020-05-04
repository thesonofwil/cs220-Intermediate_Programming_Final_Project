 //Brhea D'Mello
 //bdmello2
 
#include "astarchasehero.h"
#include "position.h"
#include "entity.h"
#include "game.h"
#include "gamerules.h"
#include "entitycontroller.h"
#include <cstdlib>
#include <vector>
#include <utility> 

AStarChaseHero::AStarChaseHero(){
 }
 
 AStarChaseHero::~AStarChaseHero(){
 }
 

/*
static double calculateH(int horizaontal, int vertical) {
    double H  = pow(horizontal, 2) + pow(vertical, 2);       //calculating Euclidean distance (h)
    H = sqrt(H); 
    return H;
}
*/

  Direction AStarChaseHero::getMoveDirection(Game *game, Entity *entity){
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

    int horizontal = poshero.getX()-posminotaur.getX();
    int vertical = poshero.getY()-posminotaur.getY();
    GameRules* gamerules = game -> getGameRules();
    bool available1 = gamerules -> allowMove(game, entity, posminotaur, posminotaur.displace(Direction::UP));
    bool available2 = gamerules -> allowMove(game, entity, posminotaur, posminotaur.displace(Direction::DOWN));
    bool available3 = gamerules -> allowMove(game, entity, posminotaur, posminotaur.displace(Direction::LEFT));
    bool available4 = gamerules -> allowMove(game, entity, posminotaur, posminotaur.displace(Direction::RIGHT));

    int h;
    int f1, f2, f3, f4;
    int g = 1;
    if(available1){
      horizontal = poshero.getX()-posminotaur.getX();
      vertical = poshero.getY()-(posminotaur.getY()+1);
      h = horizontal + vertical;
      f1 = g + h;
    }
    if(available2){
      horizontal = poshero.getX()-posminotaur.getX();
      vertical = poshero.getY()-(posminotaur.getY()-1);
      h = horizontal + vertical;
      f2 = g + h;
    }
    if(available3){
      horizontal = poshero.getX()-(posminotaur.getX()-1);
      vertical = poshero.getY()-posminotaur.getY();
      h = horizontal + vertical;
      f3 = g + h;
    }
    if(available4){
      horizontal = poshero.getX()-(posminotaur.getX()+1);
      vertical = poshero.getY()-posminotaur.getY();
      h = horizontal + vertical;
      f4 = g + h;
    }

    if ((f1 > f2) && (f1 > f3) && (f1 > f4)) {
      return Direction::UP;
    } else if(f2 > f1 && f2 > f3 && f2 > f4) {
      return Direction::DOWN;
    }  else if(f3 > f1 && f3 > f2 && f3 > f4) {
      return Direction::LEFT;
    } else if(f4 > f2 && f4 > f3 && f4 > f1) {
      return Direction::RIGHT;
    } else {
      return Direction::NONE;
    }
}

 bool AStarChaseHero::isUser() const {
   return false;
 }
