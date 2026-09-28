/*
 * Author: Jesse Sergent
 * Email: jtsergen
 * Description: This program manages the player's status, including their name and 
 * inventory of gems and keys. It handles the initialization and deallocation of 
 * avatar data and tracks resources collected during gameplay.
 */

#include "Avatar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// this handles declaring the gems, keys, and the name
void avatarInit(Avatar* avatar, const char* name)
{
    avatar->gems = 0;
    avatar->keys = 0;
    avatar->name = malloc(strlen(name) + 1);
    if (avatar->name != NULL)
    {
        strcpy(avatar->name, name);
    }
}

void avatarUninit(Avatar* avatar)
{
    free(avatar->name);
    avatar->name = NULL;
}
// this displays the players inventory
void avatarDisplay(const Avatar* avatar)
{
    printf("%s's inventory: gems %d, keys %d\n", avatar->name, avatar->gems, avatar->keys);
}
// counter for gems
void avatarAddGem(Avatar* avatar)
{
    avatar->gems++;
}
// counter for keys
void avatarAddKey(Avatar* avatar)
{
    avatar->keys++;
}
// if the player has enough keys it uses it
bool avatarUseKey(Avatar* avatar)
{
    if (avatar->keys > 0)
    {
        avatar->keys--;
        return true;
    }
    return false;
}
