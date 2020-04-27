//Brhea D'Mello
//bdmello2

  #include <string>
  #include "entity.h"


  Entity::Entity() {
  }
  
  Entity::~Entity() {
  }

  // Set the glyph that will represent this Entity.
  // Should consist of a single character.
  void Entity::setGlyph(const std::string &glyph){
	  return "@";
	  "M:
  }

  // Set the properties of this Entity.  Each character in the
  // string represents a single property.
  void Entity::setProperties(const std::string &props){
	  "h";
	  "m";
  }

  // Get the glyph representing this Entity.
  Entity::std::string getGlyph() const{
	  return "";
  }

  // Get the string containing this Entity's properties.
  Entitiy::std::string getProperties() const{
	  return "";
  }

  // Return true if the Entity's properties contain the specified
  // character, false otherwise.
  bool Entity::hasProperty(char prop) const{
	return true;
  }

  // Set this Entity's EntityController, which will determine how it moves.
  // The Entity assumes responsibility for deleting it.
  void Entity::setController(EntityController *controller){

  }

  // Get this Entity's EntityController.
  Entity::EntityController *getController(){
	  getX();
          getY();

  }

  // Set this Entity's Position.
  void Entity::setPosition(const Position &pos){
	  getX();
	  getY();
  }

  // Return this Entity's Position.
  Position Entity::getPosition() const{
	  displace(Direction dir);
  }

