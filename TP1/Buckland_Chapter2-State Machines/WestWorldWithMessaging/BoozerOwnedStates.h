#ifndef BOOZER_OWNED_STATES_H
#define BOOZER_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  Based on MinersWifeOwnedStates.h by Mat Buckland, 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#include "fsm/State.h"

class Boozer;


//------------------------------------------------------------------------
class Drinking : public State<Boozer>
{
private:

  Drinking(){}
  
  //copy ctor and assignment should be private
  Drinking(const Drinking&);
  Drinking& operator=(const Drinking&);

public:

  //this is a singleton
  static Drinking* Instance();
  
  virtual void Enter(Boozer* boozer);

  virtual void Execute(Boozer* boozer);

  virtual void Exit(Boozer* boozer);
  
  virtual bool OnMessage(Boozer* boozer, const Telegram& msg);

};



//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class Drunk : public State<Boozer>
{
private:
  
  Drunk(){}

  //copy ctor and assignment should be private
  Drunk(const Drunk&);
  Drunk& operator=(const Drunk&);
 
public:

  //this is a singleton
  static Drunk* Instance();
  
  virtual void Enter(Boozer* boozer);

  virtual void Execute(Boozer* boozer);

  virtual void Exit(Boozer* boozer);

  virtual bool OnMessage(Boozer* boozer, const Telegram& msg);

};


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class Fighting : public State<Boozer>
{
private:
  
  Fighting(){}

  //copy ctor and assignment should be private
  Fighting(const Fighting&);
  Fighting& operator=(const Fighting&);
 
public:

  //this is a singleton
  static Fighting* Instance();
  
  virtual void Enter(Boozer* boozer);

  virtual void Execute(Boozer* boozer);

  virtual void Exit(Boozer* boozer);

  virtual bool OnMessage(Boozer* boozer, const Telegram& msg);
};


#endif