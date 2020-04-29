// Wilson Tjoeng
// wtjoeng1

#include "basicgamerules.h"

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
  // and check if it can be moved 
  if (!checkObjCanBePushed(game, dest)) {
    return false; // There exists an object that can't be pushed and therefore actor can't move
  }

  // Check if actor can move to dest tile
  return checkMoveResult(game, source, dest); 
}

// Update the positions of the entity and the inanimate object if pushed
void BasicGameRules::enactMove(Game *game, Entity *actor, const Position &dest) const {
  assert(allowMove()); // Assert move is allowed
  actor.setPosition(dest); // Update Player's position

  // Set the new position for the moveable object, if any. 
  Entity *object = game->getEntityAt(dest);
  Direction dir = getPushDirection(actor, object);
  Position newPos = getPushPosition(game, dir, object);
  object.setPosition(newPos); 
}

// Return the current game state.
// If hero reaches Goal, return GameResult::HERO_WINS.
// If minotour reaches hero, return GameResult::HERO_LOSES.
// Otherwise return GameResult::UNKNOWN.
// GameResult defined in gamerules.h
GameResult checkGameResult(Game *game) const {
  Maze *maze = game->getMaze();
  std::vector<Entity *> heroes = game->getEntitiesWithProperty('h'); // Get vector of heroes. A game may have multiple heroes
  std::vector<Entity *> minotaurs = game->getEntitiesWithProperty('m'); // Get vector of minotaurs.
  // Get list of positions of minotaurs
  std::vector<Position> minPositions;
  if (!minotaurs.is_empty()) {
    for (Entity* minotaur : minotaurs) {
      minPositions.push_back(minotaur.getPosition());
    }
  }
  
  for (Entity* hero : heroes) {
    Position pos = hero.getPosition();
    Tile *tile = maze.getTile(pos);
    if (tile.isGoal()) {
      return GameResult::HERO_WINS;
    }
    // Check if any minotaur is at the same position as hero
    if (!minPositions,is_empty()) {
      for (Position p : minPositions) {
	if (p == pos) {
	  return GameResult::HERO_LOSES;
	}
      }
    }
  }
  return GameResult::UNKNOWN;
}

bool BasicGameRules::checkMoveResult(Game *game, const Position &source, const Position &dest) const {
  Maze *maze = game->getMaze(); // Get the maze
  Tile *tile = maze->getTile(dest); // Get the tile specified at destination. Assume tile is one its subclass, which
                                   // allows it to be a tile object despite the base class being abstract.
  
  MoveResult result = tile.checkMoveOnto(actor, source, dest);
  if (result == MoveResult::ALLOW) {
    return true;
  }
  return false;
}

// Get the direction of the actor pushing onto an inanimate object. 
Direction BasicGameRules::getPushDirection(Entity *actor, Entity *obj) {
  Position actorPos = actor.getPosition(); // Get position of object
  Position objPos = obj.getPosition(); // Get position if it were displaced

  int x = obj.pos.x - actor.pos.x;
  int y = obj.pos.y - actor.pos.y;

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

// Get the new position of an object when it's pushed
Position BasicGameRules::getPushPosition(Game *game, Direction dir, Entity *obj) {
  Maze *maze = game->getMaze();
  Position newPos = Position::displace(dir);
  Tile *destTile = maze->getTile(newPos); // Get tile at destination
  MoveResult check = destTile.checkMoveOnto(obj, obj.getPosition(), newPos);
  
  // Check if newPos is valid
  if (!newPos.inBounds(maze->width, maze->height) || check == MoveResult::BLOCK) {
    return obj.getPosition(); // No change in position
  }
  return newPos; 
}

bool BasicGameRules::checkObjCanBePushed(Game *game, Position &dest) {
  Entity *object = game->getEntityAt(dest);
  if (object.hasProperty('v') && object.getProperties() != nullptr) { // v denotes moveable entity

    // Check if moveable object can be moved further
    Direction dir = getPushDirection(actor, object);
    if (dir == Direction::NONE) {
      return false;
    }
    
    Position pushPos = getPushPosition(game, dir, object);
    if (pushPos == object.getPosition()) { // Object cannot be pushed
      return false;
    }
    return true;
  }
  return true; // Default: there is no object
}
