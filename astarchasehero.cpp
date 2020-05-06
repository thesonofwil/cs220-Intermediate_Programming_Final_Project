//Brhea D'Mello
//bdmello2
//Jingyu Huang
//jhuan146
//Wilson Tjoeng
//wtjoeng1

#include "astarchasehero.h"
#include "position.h"
#include "entity.h"
#include "game.h"
#include "maze.h"
#include "gamerules.h"
#include "entitycontroller.h"
#include <cstdlib>
#include <vector>
#include <utility> 
#include <map>
#include <queue>
#include <iostream>
#include <limits>

using std::vector;
using std::priority_queue;
using std::map;
using std::pair;

AStarChaseHero::AStarChaseHero(){
 }
 
 AStarChaseHero::~AStarChaseHero(){
 }
 
 AStarChaseHero::Node* AStarChaseHero::getN(Node* current, Direction x, Game *game, Entity *entity,Position poshero) {
 	if (!available(game,entity, current, x)){
		return nullptr;
	}
	Node *neighbor = new Node;
        neighbor->f = 0;
        neighbor->g = 0;
        neighbor->h = (current->pos).distanceFrom(poshero);
        neighbor->pos = current->pos.displace(x);//check is syntax is right
        neighbor->parent = current;
	return neighbor;
 }

bool AStarChaseHero::available(Game *game,Entity *entity, Node *n, Direction x){

    GameRules* gamerules = game -> getGameRules();
    return gamerules -> allowMove(game, entity, n->pos, (n->pos).displace(x));
}

bool AStarChaseHero::contain(vector<Node*> v, Node *x){
	for(Node *n : v){
		if(x == n){
			return true;
	        }else {
		        return false;
	        }
        }
	return false;
}

Direction AStarChaseHero::reconstruct_path(Node *goal) {
	vector<Node*> total_path;
        Node *temp = goal;
	while(temp->parent != nullptr){
		  total_path.push_back(temp);
                  temp= temp->parent;
	}
		int length = total_path.size();
		return getPushDirection(total_path[length]->pos, total_path[length-1]->pos);
        }

Direction AStarChaseHero::getPushDirection(Position last, Position secondlast) const {

  int x = last.getX() - secondlast.getX();
  int y = last.getY() - secondlast.getY();

  if (x == 0 && y == 1) {
    return Direction::UP;
  } else if (x == 0 && y == -1) {
    return Direction::DOWN;
  } else if (x == 1 && y == 0) {
    return Direction::RIGHT;
  } else if (x == -1 && y == 0) {
    return Direction::LEFT;
  }
  return Direction::NONE; // Invalid push
}

 Direction AStarChaseHero::getMoveDirection(Game *game, Entity *entity){
   
    std::vector<Entity *> heroes;
    heroes = game->getEntitiesWithProperty('h');
    if(heroes.empty()){
      return Direction::NONE;
    }
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
    
  	Node *start = new Node;
	start->f = std::numeric_limits<int>::max();
	start->g = 0;
	start->h = posminotaur.distanceFrom(poshero);
	start->pos = posminotaur;
	start->parent = nullptr;
	

    priority_queue <Node*> openSet;
    vector<Node*> openSetCopy;
    openSet.push(start);
    openSetCopy.push_back(start);

    while(!openSet.empty()){
        Node* current = openSet.top();
	if(current->pos == poshero){
		return reconstruct_path(current);
	}

	openSetCopy.pop_back();
	openSet.pop();
	Node* up = getN(current, Direction::UP, game, entity,poshero);
        Node* down = getN(current, Direction::DOWN, game, entity,poshero);
        Node* left = getN(current, Direction::LEFT, game, entity,poshero);
        Node* right = getN(current, Direction::RIGHT, game, entity,poshero);

	vector<Node*> neighbors{up, down, left, right};
		
	for(Node* n : neighbors) {
	        if(n == nullptr){
			continue;
		}
		int newg = current->g +1;
		if(newg < n->g) {
			n->parent = current;
			n->g = newg;
			n->f = n->g + n->h;
			if(!contain(openSetCopy, n)){
				openSet.push(n);
				openSetCopy.push_back(n);
			}
		}				
	}
    }
    return Direction::NONE;
 }
   

 bool AStarChaseHero::isUser() const {
   return false;
 }
