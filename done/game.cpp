// Wilson Tjoeng
// wtjoeng1

#include "game.h"

Game::Game() {
  this->maze = nullptr;
  this->ui = nullptr;
  this->gameRules = nullptr;
}

Game::~Game() {
  delete this->maze;
  delete this->ui;
  delete this->gameRules;
  for (int i = 0; i < Game::EntityVec.size(); i++) {
    delete Game::EntityVec[i];
  }
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

  // Continuously take turns until game over
  while (status == GameResult::UNKNOWN) {
    for (Entity *e : Game::EntityVec) {
      // If entity is controller, display the maze
      EntityController *controller = e->getController();
      if (e.isUser()) {
	this->ui.render(this);
      }
      
      takeTurn(e); // Enact turn

      // Check if game over condition has been met
      status = this->gameRules.checkGameResult(this);
      if (status == GameResult::HERO_WINS) {
	this->ui.displayMessage("Hero wins", true); // endgame = true
	break; // Exit out of for and while loops
      } else if (status == GameResult::HERO_LOSES) {
	this->ui.displayMessage("Hero loses", true);
      }
    }
  }
}

// Let specified actor Entity take a turn.
// This is public so that it can be called from
// unit tests. It is mainly intended to be called from
// the gameLoop member function.
void Game::takeTurn(Entity *actor) {
  // Get move from controller 
  EntityController *controller = actor->getController();
  Direction dir = controller.getMoveDirection(this, actor);
  Position dest = Position::displace(dir); // Get the potential new position

  // Check if move is valid and execute it if it is
  if (this->gameRules.allowMove(this, actor, actor.getPosition(), dest)) {
    this->gameRules.enactMove(this, actor, dest);
  } else {
    if (controller.isUser()) { // Output error if user makes an illegal move
      this->ui.displayMessage("Illegal Move"); // No need for second parameter, defaults to false
    }
  }
}

// Read initial Game data from the specified istream, and return
// the resulting Game object.
static Game Game::*loadGame(std::isstream &in) {
  if (!in) { // Game data not valid
    return nullptr;
  }

  // Get maze data 
  Maze *maze = Maze::read(in);
  setMaze(maze);

  // isstream pointer now should be at descriptors
  while (!in.eof()) { // Read until end of file
    setEntity(in);
  }
}

// Given the stream pointer is past the maze and reading the string below it,
// extract each character that describes a new entity and create it.
void Game::setEntity(std::isstream &in) {
  if (!in) {
    return nullptr;
  }

  // Get entity data
  char glyph;
  char controller;
  char property;
  int x;
  int y;

  in >> glyph;
  in >> controller;
  in >> property;
  in >> x;
  in >> y;

  // Create new entity and set properties
  Entity *e = new Entity();
  e->setGlyph(getString(glyph));
  e->setProperties(getString(property));
  EntityControllerFactory *ecf = EntityControllerFactory::getInstance();
  EntityController *control = ecf.EntityControllerFactory::createFromChar(controller);
  e.setController(control);
  Position pos = new Position(x, y);
  e.setPosition(pos);

  addEntity(e); // Add new entity to list
}

// Convert char to string
// string class has a constructor with size of string as
// first param and the text as the second parameter.
std::string Game::getString(char ch) { 
  std::string str(1, ch);
  return str;
}