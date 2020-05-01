//jhuan146
//Jingyu Huang

#include "uicontrol.h"

UIControl::UIControl(){
}

UIControl::~UIControl(){
}

//Get suggested move from UI object
Direction UIControl::getMoveDirection(Game, Entity){
  UI *ui = UI::getInstance();
  Direction dir = ui->getMoveDirection();
  return dir;
}

//EntityController is controlled by use input
bool UIControl::isUser() const{
  return true;
}
