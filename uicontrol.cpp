//jhuan146
//Jingyu Huang

#include "uicontrol.h"

UIControl::UIControl(){
}

UIControl::~UIControl(){
}

Direction UIControl::getMoveDirection(Game, Entity){
  UI *ui = UI::getInstance();
  Direction dir = ui->getMoveDirection();
  return dir;
}

bool UIControl::isUser() const{
  return false;
}
