// Wilson Tjoeng
// wtjoeng1

#include "game.h"

Game::Game() {
  this->maze = nullptr;
  this->ui = nullptr;
  this->gameRules = nullptr;
}

Game::~Game() {
}

// Set the Maze object. The Game object assumes responsibility for
// deleting it.
void Game::setMaze(Maze *maze) {
  this->maze = maze;
}

// Set the UI object. The Game object assumes responsibility for
// deleting it.
void Game::setUI(UI *ui) {
  this->ui = ui;
}

// Set the GameRules object. The Game object assumes responsibility for
// deleting it.
void Game::setGameRules(GameRules *gameRules) {
  this->gameRules = gameRules;
}

// Add an Entity to the sequence of entities. The Game object assumes
// responsibility for deleting it.
void Game::addEntity(Entity *entity) {
  Game::EntityVec.push_back(entity);
}

// Get the Entity at the specified Position. Return nullptr if
// there is no Entity at the specified Position.
Entity *getEntityAt(const Position &pos) {
  // Loop through list and find Entity with matching Position
  for (Entity *e : Game::EntityVec) {
     if (e.getPosition() == pos) {
       return e;
     }
  }
   return nullptr;
}

// Get a const reference to the Game object's internal vector
// of pointers to Entity objects.
const Game::EntityVec& Game::getEntities() const {
  return Game::EntityVec&;
}

// Get a vector of pointers to Entity objects that have the
// specified property. The vector could be empty if no Entity objects
// have the specified property.
std::vector<Entity *> Game::getEntitiesWithProperty(char prop) const {
  std::vector<Entity *> entities;

  for (Entity *e : Game::EntityVec) {
    if e.hasProperty(prop) {
	entities.push_back(e);
      }
  }
  return entities;
}

// Get the Maze object.
Maze Game::*getMaze() {
  return this->maze;
}

// Get the UI object.
UI Game::*getUI() {
  return this->ui;
}

// Get the GameRules object.
GameRules Game::*getGameRules() {
  return this->gameRules;
}

// Let the Entity objects take turns in round-robin fashion until
// the GameRules object determines that the hero has won or lost.
// Should call the render member function on the UI object just before
// an Entity whose EntityController is controlled by the user takes
// a turn.
void Game::gameLoop() {
  GameResult status = GameResult::UNKNOWN;

  while (status == GameResult::UNKNOWN) {
    for (Entity *e : Game::EntityVec) {
      takeTurn(e);
    }
  }
}

// Let specified actor Entity take a turn.
// This is public so that it can be called from
// unit tests. It is mainly intended to be called from
// the gameLoop member function.
void Game::takeTurn(Entity *actor) {
}
