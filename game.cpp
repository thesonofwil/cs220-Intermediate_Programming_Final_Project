// Wilson Tjoeng
// wtjoeng1

#include "game.h"
#include "maze.h"
#include "tile.h"
#include "position.h"
#include "entity.h"
#include "entitycontroller.h"
#include "ecfactory.h"
#include "ui.h"
#include "gamerules.h"

Game::Game() {
  this->maze = nullptr;
  this->ui = nullptr;
  this->gameRules = nullptr;
  this->entityVec = new Game::EntityVec(); 
}

Game::~Game() {
  delete this->maze;
  delete this->ui;
  delete this->gameRules;
  for (int i = 0; i < (int) this->entityVec->size(); i++) {
    delete this->entityVec->at(i); 
  }
  delete this->entityVec;
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
  this->entityVec->push_back(entity);
}

// Get the Entity at the specified Position. Return nullptr if
// there is no Entity at the specified Position.
Entity* Game::getEntityAt(const Position &pos) {
  // Loop through list and find Entity with matching Position
  for (int i = 0; i < (int) this->entityVec->size(); i++) {
    if (this->entityVec->at(i)->getPosition() == pos) {
      return this->entityVec->at(i);
     }
  }
  return nullptr;
}

// Get a const reference to the Game object's internal vector
// of pointers to Entity objects.
const Game::EntityVec& Game::getEntities() const {
  return *this->entityVec;
}

// Get a vector of pointers to Entity objects that have the
// specified property. The vector could be empty if no Entity objects
// have the specified property.
std::vector<Entity *> Game::getEntitiesWithProperty(char prop) const {
  std::vector<Entity *> entities;

  for (int i = 0; i < (int) this->entityVec->size(); i++) {
    if (this->entityVec->at(i)->hasProperty(prop)) {
	entities.push_back(this->entityVec->at(i));
      }
  }
  return entities;
}

// Get the Maze object.
Maze* Game::getMaze() {
  return this->maze;
}

// Get the UI object.
UI* Game::getUI() {
  return this->ui;
}

// Get the GameRules object.
GameRules* Game::getGameRules() {
  return this->gameRules;
}

// Let the Entity objects take turns in round-robin fashion until
// the GameRules object determines that the hero has won or lost.
// Should call the render member function on the UI object just before
// an Entity whose EntityController is controlled by the user takes
// a turn.
void Game::gameLoop() {
  bool gameOver = false;
  
  // Continuously take turns until game over
  while (!gameOver) {
    for (int i = 0; i < (int) this->entityVec->size(); i++) {
      // If entity is controller, display the maze
      EntityController *controller = this->entityVec->at(i)->getController();
      if (controller->isUser()) {
	this->ui->render(this);
      }
      
      takeTurn(this->entityVec->at(i)); // Enact turn

      // Check if game over condition has been met
      GameResult status = this->gameRules->checkGameResult(this);
      if (status == GameResult::HERO_WINS) {
	this->ui->displayMessage("Hero wins", true); // endgame = true
	gameOver = true;
	break; // Exit out of for and while loops
      } else if (status == GameResult::HERO_LOSES) {
	this->ui->displayMessage("Hero loses", true);
	gameOver = true;
	break;
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
  Direction dir = controller->getMoveDirection(this, actor);
  Position source = actor->getPosition();
  Position dest = source.displace(dir); // Get the potential new position

  // Check if move is valid and execute it if it is
  if (this->gameRules->allowMove(this, actor, actor->getPosition(), dest)) {
    this->gameRules->enactMove(this, actor, dest);
  } else {
    if (controller->isUser()) { // Output error if user makes an illegal move
      this->ui->displayMessage("Illegal Move"); // No need for second parameter, defaults to false
    }
  }
}

// Read initial Game data from the specified istream, and return
// the resulting Game object.
Game* Game::loadGame(std::istream &in) {
  if (!in) { // Game data not valid
    return nullptr;
  }

  Game *game = new Game();
  
  // Get maze data 
  Maze *maze = Maze::read(in);
  game->setMaze(maze);

  // isstream pointer now should be at descriptors
  while (!in.eof()) { // Read until end of file
    game->setEntity(in);
  }
  return game;
}

// Given the stream pointer is past the maze and reading the string below it,
// extract each character that describes a new entity and create it.
void Game::setEntity(std::istream &in) {

  // Get entity data
  char glyph;
  char controller;
  std::string property;
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
  e->setProperties(property);
  EntityControllerFactory *ecf = EntityControllerFactory::getInstance();
  EntityController *control = ecf->createFromChar(controller);
  e->setController(control);
  Position pos(x, y); // Create new position
  e->setPosition(pos);

  addEntity(e); // Add new entity to list
}

// Convert char to string
// string class has a constructor with size of string as
// first param and the text as the second parameter.
std::string Game::getString(char ch) { 
  std::string str(1, ch);
  return str;
}
