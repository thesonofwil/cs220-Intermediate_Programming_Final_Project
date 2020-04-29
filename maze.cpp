// Wilson Tjoeng
// wtjoeng1

#include "maze.h"
#include "tile.h"
#include "tilefactory.h"
#include "position.h"
#include <fstream>

Maze::Maze(int width, int height) {
  this->width = width;
  this->height = height;
  //this->maze = new Tile*[width];
  // stl container - vector<Tile*> 
  //for (int i = 0; i < width; i++) {
  //  this->maze[i] = new Tile[height];
  //}
  this->maze = new std::vector<Tile *>(width * height);
}

Maze::~Maze() {
  //for (int i = 0; i < this->width * this->height; i++) {
  //  delete maze[i];
  //}
  delete this->maze;
}

// Get the 1D index that corresponds to a given 2D index.
int Maze::getIndex(int x, int y) const {
  return x * getWidth() + y;
}

// Get the x coordinate given a 1D index.
int Maze::getX(int i) const {
  return i / getWidth();
}

// Get the y coordinate given a 1D index.
int Maze::getY(int i) const {
  return i % getWidth();
}

int Maze::getWidth() const {
  return this->width;
}

int Maze::getHeight() const {
  return this->height;
}

// Return true of the specified position is in bound
// according to the Maze's width and height.
bool Maze::inBounds(const Position &pos) const {
  return pos.inBounds(this->width, this->height);
}

// Set a Tile at the specified Position. The Maze assumes responsibility
// for deleting the Tile.
void Maze::setTile(const Position &pos, Tile *tile) {
  int i = getIndex(pos.getX(), pos.getY());

  // Since maze is a pointer to a vector of pointers,
  // Need to dereference to access index.
  this->maze->at(i) = tile;
}

// Get the Tile at the specified Position.
// Note: Floor and Wall is a Tile and may be returned. 
const Tile* Maze::getTile(const Position &pos) const {
  int i = getIndex(pos.getX(), pos.getY());

  return this->maze->at(i);
}

// Read a description of a Maze from specified istream, and return it. 
Maze* Maze::read(std::istream &in) {
  int width;
  int height;
  in >> width; // Get first number
  in >> height; // Get second number

  Maze *maze = new Maze(width, height); // Create a new maze
  
  TileFactory *tileFactory = TileFactory::getInstance(); // Get instance to call its member function
  // Get chars for maze 
  for (int i = 0; i < height * width; i++) {
    char ch;
    in >> ch;
    Tile *tile = tileFactory->TileFactory::createFromChar(ch); // Get tile
    
    if (tile == nullptr) {
      std::cerr << "Error: maze is not valid" << std::endl;
      return nullptr;
    }
    Position pos(maze->getX(i), maze->getY(i));
    
    // Populate the empty maze
    //maze->maze->at(i) = tile;
    maze->setTile(pos, tile);
  }
  return maze;
}
