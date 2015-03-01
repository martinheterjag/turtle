//defined and typedefs for turtle state machines

#ifndef __STATE_MACHINE_H 
#define __STATE_MACHINE_H
typedef enum
{
  STATE_WAIT_FOR_COMMAND = 1,
  STATE_FORWARD = 2,
  STATE_RIGHT = 3,
  STATE_LEFT = 4,
  STATE_PENUP = 5,
  STATE_PENDOWN = 6
}state;

#endif