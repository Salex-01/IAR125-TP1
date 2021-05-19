#ifndef BOOZER_H
#define BOOZER_H
//------------------------------------------------------------------------
//
//  Name: MinersWife.h
//
//  Desc: class to implement Miner Bob's wife.
//
//  Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include <string>

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "BoozerOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"



class Boozer : public BaseGameEntity
{
private:

  //an instance of the state machine class
  StateMachine<Boozer>* m_pStateMachine;

  location_type   m_Location;

  //is he presently drinking?
  bool            m_bDrinking;


public:

  Boozer(int id):m_Location(saloon),
//                     m_bCooking(false),
                     BaseGameEntity(id)
                                        
  {
    //set up the state machine
    m_pStateMachine = new StateMachine<Boozer>(this);

    m_pStateMachine->SetCurrentState(Drinking::Instance());

    m_pStateMachine->SetGlobalState(BoozerGlobalState::Instance());
  }

  ~Boozer(){delete m_pStateMachine;}


  //this must be implemented
  void          Update();

  //so must this
  virtual bool  HandleMessage(const Telegram& msg);

  StateMachine<Boozer>* GetFSM()const{return m_pStateMachine;}

  //----------------------------------------------------accessors
  location_type Location()const{return m_Location;}
  void          ChangeLocation(location_type loc){m_Location=loc;}

  bool          Drinking()const{return m_bDrinking;}
  void          SetDrinking(bool val){m_bDrinking = val;}
   
};

#endif
