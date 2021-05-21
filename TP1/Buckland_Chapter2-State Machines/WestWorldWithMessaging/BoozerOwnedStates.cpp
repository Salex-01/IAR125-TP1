#include "BoozerOwnedStates.h"
#include "MinerOwnedStates.h"
#include "Boozer.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-------------------------------------------------------------------------Drinking

Drinking* Drinking::Instance()
{
  static Drinking instance;

  return &instance;
}


void Drinking::Enter(Boozer* boozer)
{
  SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
  cout << "\n" << GetNameOfEntity(boozer->ID()) << ": Let's drink !";
}


void Drinking::Execute(Boozer* boozer)
{
  switch(RandInt(0,1))
  {
  case 0:
      SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(boozer->ID()) << ": That hit the spot !";

    break;

  case 1:
    SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    cout << "\n" << GetNameOfEntity(boozer->ID()) << ": Am Drunk yey !";
    boozer->GetFSM()->ChangeState(Drunk::Instance());
    break;
  }
}

void Drinking::Exit(Boozer* boozer)
{
}

bool Drinking::OnMessage(Boozer* boozer, const Telegram& msg)
{
  return false;
}

//------------------------------------------------------------------------Drunk

Drunk* Drunk::Instance()
{
  static Drunk instance;

  return &instance;
}


void Drunk::Enter(Boozer* boozer)
{  
  SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
  cout << "\n" << GetNameOfEntity(boozer->ID()) << ": I see double !"; 
}


void Drunk::Execute(Boozer* boozer)
{
  if (RandInt(0, 3) > 0) {
      SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
      cout << "\n" << GetNameOfEntity(boozer->ID()) << ": Bouah!";
  } 
  else {
      SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
      cout << "\n" << GetNameOfEntity(boozer->ID()) << ": My head hurts I drank to much !";
      boozer->GetFSM()->ChangeState(Drinking::Instance());
  }
}

void Drunk::Exit(Boozer* boozer)
{
  cout << "\n" << GetNameOfEntity(boozer->ID()) << ": buuh !";
}


bool Drunk::OnMessage(Boozer* boozer, const Telegram& msg)
{
    switch (msg.Msg)
    {
    case Msg_IsInSaloon:
    {
        cout << "\nMessage received by " << GetNameOfEntity(boozer->ID()) <<
            " at time: " << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout << "\n" << GetNameOfEntity(boozer->ID()) << "Boozer insults Bob";

        //Start fight
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
            boozer->ID(),
            ent_Miner_Bob,
            Msg_Fighting,
            NO_ADDITIONAL_INFO);

        boozer->SetFighting(true);
        boozer->SetDrinking(false);
        boozer->GetFSM()->ChangeState(Fighting::Instance());
    }

    return true;

    }//end switch

    return false;
}


//------------------------------------------------------------------------Fighting

Fighting* Fighting::Instance()
{
  static Fighting instance;

  return &instance;
}

void Fighting::Enter(Boozer* boozer)
{
  SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

  cout << "\n" << GetNameOfEntity(boozer->ID()) << ": Come here you stupid !";
}


void Fighting::Execute(Boozer* boozer)
{
  SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
  
  cout << "\n" << GetNameOfEntity(boozer->ID()) << ": I'm gonna hit you ! Yaah!";
}

void Fighting::Exit(Boozer* boozer)
{
  SetTextColor(FOREGROUND_BLUE |FOREGROUND_INTENSITY);
  
  cout << "\n" << GetNameOfEntity(boozer->ID()) << ": Ah it hurts !";
}


bool Fighting::OnMessage(Boozer* boozer, const Telegram& msg)
{
  SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

  switch(msg.Msg)
  {
    case Msg_Fighting:
    {
      cout << "\nMessage received by " << GetNameOfEntity(boozer->ID()) <<
           " at time: " << Clock->GetCurrentTime();

      SetTextColor(FOREGROUND_BLUE|FOREGROUND_INTENSITY);
      cout << "\n" << GetNameOfEntity(boozer->ID()) << " gets hit by Bob and flees";

      //Start fight
      Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
                                boozer->ID(),
                                ent_Miner_Bob,
                                Msg_Fighting,
                                NO_ADDITIONAL_INFO);

      boozer->SetFighting(false);
      boozer->SetDrinking(true);
      boozer->GetFSM()->ChangeState(Drunk::Instance());               
    }

    return true;

  }//end switch

  return false;
}