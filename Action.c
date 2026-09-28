/*
 * Author: Jesse Sergent
 * Email: jtsergen
 * Description: This program handles user input by mapping characters to movement and  * quit commands. It also provides string descriptions and coordinate changes for each * game action.
 */

#include "Action.h"
// this selects the action string based off of user input
Action actionFromChar(char ch)
{
    switch (ch)
    {
        case 'w':
            return ActionNorth;
        case 's':
            return ActionSouth;
        case 'a':
            return ActionWest;
        case 'd':
            return ActionEast;
        case 'q':
            return ActionQuit;
        default:
            return ActionInvalid;
    }
}
// this returns the string for later outputting
const char* actionToString(Action a)
{
    switch (a)
    {
        case ActionNorth:
            return "north";
        case ActionSouth:
            return "south";
        case ActionEast:
            return "east";
        case ActionWest:
            return "west";
        case ActionQuit:
            return "quit";
        default:
            return "invalid";
    }
}
// this returns the values of each action after getting the users input
bool actionMoveDelta(Action a, int* deltaRow, int* deltaCol)
{
    *deltaRow = 0;
    *deltaCol = 0;

    switch (a)
    {
        case ActionNorth:
            *deltaRow = -1;
            return true;
        case ActionSouth:
            *deltaRow = 1;
            return true;
        case ActionEast:
            *deltaCol = 1;
            return true;
        case ActionWest:
            *deltaCol = -1;
            return true;
        default:
            return false;
    }
}
