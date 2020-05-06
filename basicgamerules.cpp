//Brhea D'Mello
//bdmello2
//Jingyu Huang
//jhuan146
//Wilson Tjoeng
//wtjoeng1

#include "basicgamerules.h"
#include "entity.h"
#include "entitycontroller.h"
#include "game.h"
#include "maze.h"
#include "tile.h"

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

  // Return false if inanimate object, move would be > 1 space, or if dest contains a moveable object
  // that can't move further
  if (source.distanceFrom(dest) > 1) { 
    return false;           
  }

  // Check if actor can move to dest tile.
  return checkObjCanBePushed(game, actor, source, dest);
}

// Update the positions of the entity and the inanimate object if pushed
// Precondition: allowMove() returned true
void BasicGameRules::enactMove(Game *game, Entity *actor, const Position &dest) const {

  EntityController *controller = actor->getController();
    
  // Check if any pushable objects occupy the dest tile.
  if (controller->isUser()) { 
    std::vector<Entity *> objs = game->getEntitiesWithProperty('v');
    for (Entity* obj : objs) {
      if (obj->getPosition() == dest) {
      	Direction dir = getPushDirection(actor, obj);
	Position newPos = getPushPosition(game, dir, obj);
	obj->setPosition(newPos);
	break; // Only one object at a tile at a time
      }
    }
  }
  actor->setPosition(dest);
}

// Return the current game state.
// If hero reaches Goal, return GameResult::HERO_WINS.
// If minotour reaches hero, return GameResult::HERO_LOSES.
// Otherwise return GameResult::UNKNOWN.
// GameResult defined in gamerules.h
GameResult BasicGameRules::checkGameResult(Game *game) const {
  Maze *maze = game->getMaze();
  std::vector<Entity *> heroes = game->getEntitiesWithProperty('h'); // Get vector of heroes. A game may have multiple heroes
  std::vector<Entity *> minotaurs = game->getEntitiesWithProperty('m'); // Get vector of minotaurs.
  // Get list of positions of minotaurs
  std::vector<Position> minPositions;
  if (!minotaurs.empty()) {
    for (Entity* minotaur : minotaurs) {
      minPositions.push_back(minotaur->getPosition());
    }
  }
  
  for (Entity* hero : heroes) {
    Position pos = hero->getPosition();
    const Tile *tile = maze->getTile(pos);
    if (tile->isGoal()) {
      return GameResult::HERO_WINS;
    }
    // Check if any minotaur is at the same position as hero
    if (!minPositions.empty()) {
      for (Position p : minPositions) {
	if (p == pos) {
	  return GameResult::HERO_LOSES;
	}
      }
    }
  }
  return GameResult::UNKNOWN;
}

// Get the direction of the actor pushing onto an inanimate object. 
Direction BasicGameRules::getPushDirection(Entity *actor, Entity *obj) const {
  Position actorPos = actor->getPosition(); // Get position of object
  Position objPos = obj->getPosition(); // Get position if it were displaced

  int x = objPos.getX() - actorPos.getX();
  int y = objPos.getY() - actorPos.getY();
  
  if (x == 0 && y == 1) {
    return Direction::DOWN;
  } else if (x == 0 && y == -1) {
    return Direction::UP;
  } else if (x == 1 && y == 0) {
    return Direction::RIGHT;
  } else if (x == -1 && y == 0) {
    return Direction::LEFT;
  }
  return Direction::NONE; // Invalid push
}

// Get the new position of an object when it's pushed
Position BasicGameRules::getPushPosition(Game *game, Direction dir, Entity *obj) const {
  Maze *maze = game->getMaze();
  Position newPos = obj->getPosition().displace(dir); // Get new position if object were to be pushed
  const Tile *destTile = maze->getTile(newPos); // Get tile at destination
  MoveResult check = destTile->checkMoveOnto(obj, obj->getPosition(), newPos);

  Entity *block = game->getEntityAt(newPos); // Check if there exists an entity at displaced position
  
  // Check if newPos is valid
  if (!newPos.inBounds(maze->getWidth(), maze->getHeight()) || check == MoveResult::BLOCK || block != nullptr) {
    return obj->getPosition(); // No change in position
  }
  return newPos; 
}

bool BasicGameRules::checkObjCanBePushed(Game *game, Entity *actor, const Position &source, const Position &dest) const {
   Maze *maze = game->getMaze();
   const Tile *tile = maze->getTile(dest);
   MoveResult result = tile->checkMoveOnto(actor, source, dest);
   Entity *object = game->getEntityAt(dest);

   if (object == nullptr && result == MoveResult::ALLOW) { // Empty adjacent tile
     return true;
   } else if (object == nullptr && result == MoveResult::BLOCK) {
     return false;

   } else if ((actor->hasProperty('m') && object->hasProperty('h')) || (actor->hasProperty('h') && object->hasProperty('m'))) { // Hero and minotaur
     return true;

   } else if (object->hasProperty('v')) { // v denotes moveable entity
     // Check if moveable object can be moved further
     Direction dir = getPushDirection(actor, object);
     if (dir == Direction::NONE) {
       return false;
     }
    
     Position pushPos = getPushPosition(game, dir, object);
     
     if (pushPos == object->getPosition()) { // Object cannot be pushed
       return false;
     }
     return true;
   }
   return true; // Default: there is no object
}
