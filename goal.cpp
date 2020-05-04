//jhuan146
//Jingyu Huang

#include "goal.h"

Goal::Goal(){
}

Goal::~Goal(){
}

//A goal tile is always allowed to access
MoveResult Goal::checkMoveOnto(Entity *, const Position&, const Position&) const{
  return MoveResult::ALLOW;
}

//A goal tile is the goal
bool Goal::isGoal() const {
  return true;
}

//A goal tile is marked as '<' in the maze
std::string Goal::getGlyph() const {
  return "<";
}
