#ifndef STATE_WRAPPER_H
#define STATE_WRAPPER_H

#include "state.h"
#include "pddldriver.hh"
#include "predicate.hh"
#include "domain.hh"
#include "ParserController.h"
#include "heuristics.h"

using namespace std;

class StateWrapper : public State {

 private:

  LiteralList* _literalList;
  ParserController* _parserController;
  Heuristics* _heuristics;
  string *_id = nullptr;
  string *_name = nullptr;
  unsigned long long _hash = 0;
  bool _debug;
  vector<Action*> _actions;

 public:
  //Constructors
  StateWrapper(LiteralList* literalList, ParserController* parserController,
               Heuristics* heuristics, StateWrapper* father);
  StateWrapper(StateWrapper* father, LiteralList* newLiteralList, Action* action);


  string getId();
  //@Override
  vector<StateWrapper*> expand();

  //Getters
  unsigned long long getHash() const;
  friend std::ostream &operator<<(std::ostream &out, const StateWrapper &state);
  friend bool operator==(const StateWrapper first, const StateWrapper second);
  friend bool operator<=(const StateWrapper first, const StateWrapper second);
  friend bool operator>=(const StateWrapper first, const StateWrapper second);
  bool isDebug();
  string getName();
  LiteralList* getLiteralList();
  Heuristics* getHeuristics();
  ParserController* getParserController();
  vector<Action*> getActions();

  int estimate();

  // Setters
  void setDebug(bool debug);

  // Debugging Functionality
  void printExpandDebug(Action* action, StateWrapper* child, int childrenNum);
  void printActionsSequence();
};

namespace std {
  template <>
    class hash<StateWrapper>
    {
    public:
      size_t operator()(const StateWrapper &a) const
      {
        return a.getHash();
      }
    };
}
#endif //STATE_WRAPPER_H
