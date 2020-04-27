// Wilson Tjoeng
// wtjoeng1

#include "basicgamerules.h"

// A::B() to call a static function from another class

BasicGameRules::BasicGameRules() {
}

BasicGameRules::~BasicGameRules() {
}

/* Allow Entity to make a move if:
 1. it is onto an adjacent unnocupied Tile, and the Tile's checkMoveOnto member function allows the move, or

 2. it is onto an adjacent Tile occupied by an entity with the “v” (moveable) property, and the moveable entity is permitted to move onto an unoccupied adjacent Tile in the same direction that the original entity is moving. This case allows the entity to "push" a moveable entity.

Moves out of bounds, or moves by more than 1 unit of distance, are not allowed.
*/
bool BasicGameRules::allowMove(Game *game, Entity *actor, const Position &source, const Position &dest) const {
  
  int distance = source.distanceFrom(dest);
  if (distance > 1) { // Can't move more than 1 tile
    return false;
  }

  // Check if tile at dest contains a moveable object
  Entity *object = getEntityAt(dest);
  if (object.getGlyph() == "v") { // v denotes moveable entity
    // Check if moveable object can be moved further
    Position displaced = Position::displace( // How to get direction?
    
  }
    
  return checkMoveResult(game, source, dest); 
}

void BasicGameRules::enactMove(Game *game, Entity *actor, const Position &dest) const {
}

GameResult checkGameResult(Game *game) const {
}

bool BasicGameRules::checkMoveResult(Game *game, const Position &source, const Position &dest) const {
  Maze *maze = game.getMaze(); // Get the maze
  Tile *tile = maze.getTile(dest); // Get the tile specified at destination. Assume tile is one its subclass, which
                                   // allows it to be a tile object despite the base class being abstract.

  MoveResult result = tile.checkMoveOnto(actor, source, dest);
  if (result == MoveResult::ALLOW) {
    return true;
  }
  return false;
}
