//Brhea D'Mello
//bdmello2

#include <string>
#include "entity.h"

Entity::Entity() {
  controller = nullptr;
}
  
Entity::~Entity() {
  delete this->controller;
}

// Set the glyph that will represent this Entity.
// Should consist of a single character.
void Entity::setGlyph(const std::string &glyph){
  this->glyph = glyph;
}

// Set the properties of this Entity.  Each character in the
// string represents a single property.
void Entity::setProperties(const std::string &props){
  this->properties = props;
}

// Get the glyph representing this Entity.
Entity::std::string getGlyph() const{
  return this->glyph;
}

// Get the string containing this Entity's properties.
Entitiy::std::string getProperties() const{
  return this->properties;
}

// Return true if the Entity's properties contain the specified
// character, false otherwise.
bool Entity::hasProperty(char prop) const{
  return this->properties == prop; 
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
