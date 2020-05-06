//Brhea D'Mello
//bdmello2
//Jingyu Huang
//jhuan146
//Wilson Tjoeng
//wtjoeng1

#ifndef ASTARCHASEHERO_H
#define ASTARCHASEHERO_H

#include "entitycontroller.h"
#include <vector>
#include "position.h"

class AStarChaseHero : public EntityController {
private:
  // copy constructor and assignment operator are disallowed
  AStarChaseHero(const AStarChaseHero &);
  AStarChaseHero &operator=(const AStarChaseHero &);

//namespace{
       struct Node {
                Node* parent;
                Position pos;
                int f;
                int g;
                int h;

                bool operator<(const Node &o) const {
                        return f < o.f;
                }
  //      }
};

public:
  AStarChaseHero();
  virtual ~AStarChaseHero();
  virtual Direction getMoveDirection(Game *game, Entity *entity);
  virtual bool isUser() const;
	
 private:
  virtual Node *getN(Node* current,Direction x, Game *game, Entity *entity, Position poshero);
  virtual bool available(Game *game,Entity *entity, Node *n, Direction x);
  virtual bool contain(std::vector<Node*> v, Node *x);
  virtual Direction getPushDirection(Position last, Position secondlast) const;
  virtual Direction reconstruct_path(Node*);
}
;

#endif // ASTARCHASEHERO_H
