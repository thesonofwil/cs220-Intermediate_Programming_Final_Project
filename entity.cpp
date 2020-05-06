//Brhea D'Mello                                                                                                              
//bdmello2                                                                                                                       
//Jingyu Huang                                                                                                                   
//jhuan146                                                                                                                       
//Wilson Tjoeng                                                                                                                  
//wtjoeng1 

#include <string>
#include "entity.h"
#include "entitycontroller.h"
#include "position.h"

Entity::Entity() {
  this->controller = nullptr;
}
  
Entity::~Entity() {
  delete this->controller;
}

// Set the glyph that will represent this Entity.
// Should consist of a single character.
void Entity::setGlyph(const std::string &glyph){
  char ch = glyph[0]; // Game class passes a char converted to string
  this->glyph = ch;
}

// Set the properties of this Entity. Each character in the
// string represents a single property. "Any remaining character
// in the entity descriptor are the entity's properties."
void Entity::setProperties(const std::string &props){
  this->properties = props;
}

// Get the glyph representing this Entity.
std::string Entity::getGlyph() const{
  std::string str(1, this->glyph); // Convert char to string
  return str;
}

// Get the string containing this Entity's properties.
std::string Entity::getProperties() const{
  return this->properties;
}

// Return true if the Entity's properties contain the specified
// character, false otherwise.
bool Entity::hasProperty(char prop) const{
  // Check if string contains the specified char
  if (this->properties.find(prop) != std::string::npos) { 
    return true;
  }
  return false;
}

// Set this Entity's EntityController, which will determine how it moves.
// The Entity assumes responsibility for deleting it.
void Entity::setController(EntityController *controller){
  this->controller = controller;
}

// Get this Entity's EntityController.
EntityController* Entity::getController(){
  return this->controller;
}

// Set this Entity's Position.
void Entity::setPosition(const Position &pos){
  this->pos = pos;
}

// Return this Entity's Position.
Position Entity::getPosition() const{
  return this->pos;
}
