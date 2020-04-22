// Wilson Tjoeng
// wtjoeng1

#include "floor.h"


// A Floor tile is one that any Entity can move onto 
Floor::Floor() {
}

Floor::~Floor() {
}

// Check whether specified Entity is allowed to move from fromPos onto
// tilePos. tilePos can be assumed to be Position of this Tile.
// fromPos is not necessarily the Entity's Position, because this
// member function could be called as part of pathfinding, where
// it is important to know where in the Maze the Entity can move,
// regardless of where it is currently located.

// A floor tile is always valid 
MoveResult Floor::checkMoveOnto(Entity *entity, const Position &fromPos, const Position &tilePos) const {
  //entity.setPosition(tilePos); 
  return MoveResult::ALLOW;
}

// A floor tile is nevver the goal
bool Floor::isGoal() const {
  return false;
}

// A floor tile is marked as a '.' per the instructions
std::string Floor::getGlyph() const {
  return ".";
}