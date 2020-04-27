#ifndef BASICGAMERULES_H
#define BASICGAMERULES_H

#include "gamerules.h"

class BasicGameRules : public GameRules {
private:
  // copy constructor and assignment operator are disallowed
  BasicGameRules(const BasicGameRules &);
  BasicGameRules &operator=(const BasicGameRules &);

public:
  BasicGameRules();
  virtual ~BasicGameRules();

  virtual bool allowMove(Game *game, Entity *actor, const Position &source, const Position &dest) const;
  virtual void enactMove(Game *game, Entity *actor, const Position &dest) const;
  virtual GameResult checkGameResult(Game *game) const;

private:
  // add your own private member functions...
  virtual bool checkMoveResult(Game *game, const Position &source, const Position &dest) const;
  virtual Direction getPushDirection(Entity *actor, Entity *obj);
  virtual Position getPushPosition(Game *game, Direction dir, Entity *obj);
  virtual bool checkObjCanBePushed(Game *game, Position &dest);
};

#endif // BASICGAMERULES_H
