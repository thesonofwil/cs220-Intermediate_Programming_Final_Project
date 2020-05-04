//Jingyu Huang
//jhuan146

#include "textui.h"
#include "game.h"
#include "maze.h"
#include "tile.h"
#include "position.h"
#include "entity.h"
#include "ui.h"
#include <iostream>

using namespace std;

TextUI::TextUI(){
}

TextUI::~TextUI(){
}

Direction TextUI::getMoveDirection(){
  std::cout << "Your move (u/d/l/r): ";
  std::string inputline;
  std::cin >> inputline;
  char input = inputline.at(0);
  while((input!='u') && (input!='d') && (input!='l') && (input!='r')){
    std::cout << "Unknown direction" <<	std::endl;
    std::cin >> inputline;
    input = inputline.at(0);
  }
  switch(input){
    case 'u':
      return Direction::UP;
    case 'd':
      return Direction::DOWN;
    case 'l':
      return Direction::LEFT;
    case 'r':
      return Direction::RIGHT;
  }
  return Direction::NONE;
}

void TextUI::displayMessage(const std::string &msg, bool){
  //Save a message string to the field message
  this->message = msg;
}

void TextUI::render(Game *game){
  //Get and print maze
  Maze *maze = game->getMaze();
  int width = maze->getWidth();
  int height = maze->getHeight();
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) { 
      Position curr(j, i);
      Entity* target = game->getEntityAt(curr);
      if (target != nullptr){
        std::cout << target->getGlyph();
      } else {
	const Tile *tile = maze->getTile(curr);
        std::cout << tile->getGlyph();
      }
    }
    std::cout << std::endl;
  }
  /**
  //Error checking
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      Position curr(j, i);
      Entity* target = game->getEntityAt(curr);
      if (target != nullptr){
        std::cout << "(" << j << " " << i << std::endl;
      }
    }
  }
  */
  //Check if a message needs to be printed and print
  if (!(this->message).empty()){
    std::cout << ": " << this->message << std::endl;
    (this->message).erase();
  }
}
