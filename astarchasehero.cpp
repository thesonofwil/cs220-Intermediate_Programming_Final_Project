 //Brhea D'Mello
 //bdmello2
 
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

using std::vector;
using std::priority_queue;
using std::map;
using std::pair;


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

namespace{
	struct Node {
	//	int x;
	//	int y;
		*Node parent;
		Position pos;
		int f;
		int g;
		int h;
	}
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
    
    Position goal = poshero;
    Position start = posminotaur;
    //all postiions in maze
    priority_queue <Postion> openSet;
    open.push[start];
    map<Position, Position> cameFrom;
    map<Position, int> gscore;
    map<Position, int> fscore;
   
    GameRules* gamerules = game -> getGameRules();
    bool available1 = gamerules -> allowMove(game, entity, posminotaur, posminotaur.displace(Direction::UP));
    bool available2 = gamerules -> allowMove(game, entity, posminotaur, posminotaur.displace(Direction::DOWN));
    bool available3 = gamerules -> allowMove(game, entity, posminotaur, posminotaur.displace(Direction::LEFT));
    bool available4 = gamerules -> allowMove(game, entity, posminotaur, posminotaur.displace(Direction::RIGHT));   
   
    //initialize to infinity
    int h(Position x) {
      return  poshero.distanceFrom(x);
    }

    fscore.insert(std::pair<Position,int>(start,h(start));
    
		    //find the smallest f value
    typedef std::pair<Position, int> MyPairType;
    struct CompareSecond {
    bool operator()(const MyPairType& left, const MyPairType& right) const {
        return left.second < right.second;
    }
   }

   void reconstruct_path(cameFrom, current) {
   	priority_queue<Position> total_path;
	while(cameFrom.contains(current){
			current = cameFrom(current);
			total_path.push(current);
			}
		return total_path;
	}

    while(!openSet.empty()){
        Position current;

    	void getMin(std::map<Position, int> fscore){
        std::pair<Position, int> min  = *min_element(fscore.begin(), fscore.end(), CompareSecond());
        current =  min.first;
	}

	if(current = goal){
		return reconstruct(cameFrom, current);
	}

	openSet.pop();
	//do for NSEW
	int i = 1;
	if(avaiable1){
		Position up;
		//up.setX() = current.getX()+1;
		//up.setY() = current.getY();
		gscore.insert(std::pair<Position,int>(up,i);
		int new_gscore = gscore.find(current)->second + current.distanceFrom(up);
	       	if(new_gscore < gscore.find(up)->second){
			cameFrom[up] = current;//HELP
			gscore.find(up)->second = new_gscore;
			fscore.find(up)->second = gscore.find(up)->second + h(up);
			//find in priority queue
			if(openSet.top() != up) {
				openSet.push(up);
			}
		}
	}
	if(available2){
		Position up;
                gscore.insert(std::pair<Position,int>(down,i);
                int new_gscore = gscore.find(current)->second + current.distanceFrom(down);
                if(new_gscore < gscore.find(down)->second){
                        cameFrom[down] = current;//HELP
                        gscore.find(down)->second = new_gscore;
                        fscore.find(down)->second = gscore.find(down)->second + h(down);
                        //find in priority queue
                        if(openSet.top() != down) {
                                openSet.push(down);
                        }
                }

	}
	if(avaible3) {
		Position left;
                gscore.insert(std::pair<Position,int>(left,i);
                int new_gscore = gscore.find(current)->second + current.distanceFrom(left);
                if(new_gscore < gscore.find(left)->second){
                        cameFrom[left] = current;//HELP
                        gscore.find(left->second = new_gscore;
                        fscore.find(left)->second = gscore.find(left)->second + h(left);
                        //find in priority queue
                        if(openSet.top() != left) {
                                openSet.push(left);
                        }
                }
	}
	if(available4){
		Position right;
                gscore.insert(std::pair<Position,int>(right,i);
                int new_gscore = gscore.find(current)->second + current.distanceFrom(right);
                if(new_gscore < gscore.find(right)->second){
                        cameFrom[right] = current;//HELP
                        gscore.find(right)->second = new_gscore;
                        fscore.find(right)->second = gscore.find(right)->second + h(right);
                        //find in priority queue
                        if(openSet.top() != right) {
                                openSet.push(right);
                        }
                }
	}

   }

   return Direction::NONE;
    }
    
    
    /*
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
*/
 bool AStarChaseHero::isUser() const {
   return false;
 }
