// Wilson Tjoeng
// wtjoeng1

#include "inanimate.h"

Inanimate::Inanimate() {
}

Inanimate::~Inanimate() {
}

// Inanimate objects never move on their own and can only be pushed by others.
// @param entity the inanimate entity 
Direction Inanimate::getMoveDirection(Game*, Entity*) {
  return Direction::NONE;
}


// An inanimate object is never the user 
bool Inanimate::isUser() const {
  return false;
}
