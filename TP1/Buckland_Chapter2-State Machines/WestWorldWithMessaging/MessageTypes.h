#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
    Msg_HiHoneyImHome,
    Msg_StewReady,
    Msg_Fighting,
    Msg_HeyIAmDrunk,
    Msg_IsInSaloon
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case 0:
    
    return "HiHoneyImHome"; 

  case 1:
    
    return "StewReady";

  case 2 :
      
      return "Fighting";

  case 3 :

      return "HeyIAmDrunk";

  case 4:

      return "IsInSaloon";

  default:

    return "Not recognized!";
  }
}

#endif