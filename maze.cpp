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
  this->maze = new std::vector<Tile *>(width * height);
}

Maze::~Maze() {
  // Delete each tile 
  for (int i = 0; i < (int) this->maze->size(); i++) {
    delete this->maze->at(i);
  }
  delete this->maze;
}

// Convert a 2D position into its corresponding 1D index.
int Maze::get1DPos(const Position &pos) const {
  int row = pos.getY(); // y coordinate specifies current row
  int col = pos.getX(); // x coordinate specifies current column

  return row * getWidth() + col;
}

// Get the x coordinate given a 1D index.
int Maze::getRow(int i) const {
  return i / getWidth();
}

// Get the y coordinate given a 1D index.
int Maze::getCol(int i) const {
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
  int i = get1DPos(pos);
  
  // Since maze is a pointer to a vector of pointers,
  // Need to dereference to access index.
  this->maze->at(i) = tile;
}

// Get the Tile at the specified Position.
// Note: Floor and Wall is a Tile and may be returned. 
const Tile* Maze::getTile(const Position &pos) const {
  int i = get1DPos(pos); // y - current row, x - current col
  
  return this->maze->at(i);
}

// Read a description of a Maze from specified istream, and return it. 
Maze* Maze::read(std::istream &in) {
  int width = 0;
  int height = 0;
  in >> width; // Get first number
  in >> height; // Get second number

  if (width == 0 || height == 0) {
    std::cerr << "Error: invalid dimensions" << std::endl;
    return nullptr;
  }
  
  Maze *maze = new Maze(width, height); // Create a new maze
  
  TileFactory *tileFactory = TileFactory::getInstance(); // Get instance to call its member function
  char ch;
  in.get(ch); // The '\n' after the dimensions is ignored
  int count = 0; // Keep track of number of tiles read
  int widthCount = 0; // Keep track if widthCount matches given width
  while (in.get(ch)) {
    if (ch == '\n') {
      if (widthCount != width) {
	std::cerr << "Error 2: invalid dimensions" << std::endl;
	return nullptr;
      }
      widthCount = 0;
      continue;
    }

    Tile *tile = tileFactory->TileFactory::createFromChar(ch); // Get tile

    if ((tile == nullptr)) { // Invalid tile either in maze or outside (e.g. entity descriptor)
      in.unget();
      delete tile;
      break;
    } else if (count >= width * height) { // More tile than stated dimensions 
      in.unget();
      std::cerr << "Error: maze is not valid" << std::endl;
      delete tile;
      delete maze;
      return nullptr;
    }
    
    Position pos(maze->getRow(count), maze->getCol(count));
    
    // Populate the empty maze
    maze->maze->at(count) = tile;
    count++;
    widthCount++;
  }
  
  if (count != width * height) { // Maze dimensions were incorrect
    std::cerr << "Error: maze is not valid" << std::endl;
    delete maze;
    return nullptr;
  }
  
  return maze;
}
