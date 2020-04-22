//Brhea D'Mello
//bdmello2

#include "wall.h"


Wall::Wall(){
}

Wall::~Wall(){
}

MoveResult Wall::checkMoveOnto(Entity *entity, const Position &fromPos, const Position &tilePos) const {
  return MoveResult::block;
}

bool Wall::isGoal() const {
	return false;
}

std::string Wall::getGlyph() const {
	return "#";
}

