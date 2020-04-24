//Jingyu Huang
//jhuan146

#include "textui.h"
#include <iostream>

using namespace std;

TextUI::TextUI(){
}

TextUI::~TextUI(){
}

Direction TextUI::getMoveDirection(){
  std::cout << "Your move (u/d/l/r): " << std::endl;
  char input;
  std::cin >> input;
  while((input!='u') && (input!='d') && (input!='l') && (input!='r')){
    std::cout << "Unknown direction" <<	std::endl;
    std::cin >> input;
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
}

void TextUI::displayMessage(const std::string &msg, bool endgame){
  this->message = *msg;
  if(this->message){
    std::cout << this->message << std::endl;
  }
}

void TextUI::render(Game *game){
  Maze *maze = game->getMaze();
  int width = maze->getWidth();
  int height = maze->getHeight();
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) { 
      //TO DO: need to check if it is entity or tile
      Tile tile = maze[i][j];
      std::cout << tile->getGlyph() << std::endl;
    }
    std::cout << "\n" << std::endl;
  }
  TextUI::displayMessage();
  std::cout << ": " <<std::endl;
}
