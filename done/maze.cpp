// Wilson Tjoeng
// wtjoeng1

#include "maze.h"
#include <fstream>

Maze::Maze(int width, int height) {
  this->width = width;
  this->height = height;
  this->maze = new Tile*[width];
  //this->maze = new int[width][height]
  for (int i = 0; i < width; i++) {
    this->maze[i] = new Tile[height];
  }
}

Maze::~Maze() {
  for (int i = 0; i < width; i++) {
    delete[] maze[i];
  }
  delete[] maze;
}

int Maze::getWidth() const {
  return this->width;
}

int Height::getHeight() const {
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
  int x = pos.getX();
  int y = pos.getY();

  this->maze[x][y] = tile;
}


// Get the Tile at the specified Position.
// Note: Floor and Wall is a Tile and may be returned. 
const Tile Maze::*getTile(const Position &pos) const {
  return this->maze[pos.getX()][pos.getY()];
}

// Read a description of a Maze from specified istream, and return it. 
static Maze Maze::*read(std::istream &in) {
  int width;
  int height;
  in >> width; // Get first number
  in >> height; // Get second number

  Maze *maze = new Maze(width, height); // Create a new maze
  
  TileFactory *tileFactory = TileFactory::getInstance(); // Get instance to call its member function
  // Get chars for maze 
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) { 
      char ch;
      in >> ch;
      Tile *tile = tileFactory.TileFactory::createFromChar(ch); // Get tile

      if (tile == nullptr) {
	std::cerr << "Error: maze is not valid" << endl;
	return nullptr;
      }

      // Populate the empty maze
      maze[i][j] = tile;
    }
  }
  return maze;
}
