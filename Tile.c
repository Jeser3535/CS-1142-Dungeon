/*
 * Author: Jesse Sergent
 * Email: jtsergen
 * Description: This program manages the different types of terrain and objects found  * on the dungeon map. It determines how tiles are displayed and whether the player is * allowed to walk through them.
 */

#include "Tile.h"
#include <stdio.h>

// after reading the input file it uses the case to then call what tile type it is
Tile tileFromChar(char ch)
{
    switch (ch)
    {
        case ' ':
        case '.': return TileEmpty;
        case '#': return TileWall;
        case '-': return TileDoor;
        case '=': return TileLockedDoor;
        case 'S': return TileSecretPassage;
        case '*': return TileGem;
        case '+': return TileKey;
        default:  return TileInvalid;
    }
}
// this handles displaying the tile after calling it
void tileDisplay(Tile tile)
{
    switch (tile)
    {
        case TileEmpty:
            printf(" ");
            break;
        case TileWall:
            printf("#");
            break;
        case TileGem:
            printf("*");
            break;
        case TileKey:
            printf("+"); 
            break;
        case TileLockedDoor:
            printf("=");
            break;
        case TileDoor:
            printf("-"); 
            break;
        case TileSecretPassage:
            printf("#"); 
            break;
        default:
            printf(" ");
            break;
    }
}
// this handles what tiles the player is able to pass through
bool tilePassable(Tile tile)
{
    switch (tile)
    {
        case TileEmpty:
        case TileGem:
        case TileKey:
        case TileDoor:
        case TileSecretPassage:
            return true;
        default:
            return false;
    }
}
