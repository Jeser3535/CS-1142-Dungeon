/*
 * Author: Jesse Sergent
 * Email: jtsergen
 * Description: This program manages the game world by loading dungeon layouts from 
 * files into dynamic memory. It handles player movement logic, grid boundaries, and   * updates the avatar's inventory as items are collected or used.
 */

#include "Map.h"
#include <stdio.h>
#include <stdlib.h>

//
bool mapInit(Map* map, const char* filename)
{
    map->rows = 0;
    map->cols = 0;
    map->tiles = NULL;

    FILE* file = fopen(filename, "r");
    if (file == NULL) return false;

    if (fscanf(file, "%d %d", &map->rows, &map->cols) != 2) {
        fclose(file);
        return false;
    }
    if (fscanf(file, "%d %d", &map->avatarRow, &map->avatarCol) != 2) {
        fclose(file);
        return false;
    }

    map->tiles = malloc(map->rows * sizeof(Tile*));
    if (map->tiles == NULL) {
        fclose(file);
        return false;
    }

    for (int i = 0; i < map->rows; i++) {
        map->tiles[i] = malloc(map->cols * sizeof(Tile));
        if (map->tiles[i] == NULL) {
            for (int j = 0; j < i; j++) free(map->tiles[j]);
            free(map->tiles);
            map->tiles = NULL;
            fclose(file);
            return false;
        }
    }

    map->gemsRemaining = 0;
    for (int r = 0; r < map->rows; r++) {
        for (int c = 0; c < map->cols; c++) {
            char ch;
            fscanf(file, " %c", &ch);
            map->tiles[r][c] = tileFromChar(ch);
            if (map->tiles[r][c] == TileGem) map->gemsRemaining++;
        }
    }

    fclose(file);
    return true;
}

void mapUninit(Map* map)
{
    if (map->tiles != NULL) {
        for (int i = 0; i < map->rows; i++) free(map->tiles[i]);
        free(map->tiles);
        map->tiles = NULL;
    }
}

// this dislpays th map using tile.c 
void mapDisplay(const Map* map)
{
    for (int r = 0; r < map->rows; r++) {
        for (int c = 0; c < map->cols; c++) {
            if (r == map->avatarRow && c == map->avatarCol) {
                printf("@");
            } else {
                tileDisplay(map->tiles[r][c]);
            }
        }
        printf("\n");
    }
}

// this handles displaying the map after the user moves
bool mapMoveAvatar(Map* map, Avatar* avatar, Action action)
{
    int dRow, dCol;
    if (!actionMoveDelta(action, &dRow, &dCol)) return false;

    int nR = map->avatarRow + dRow;
    int nC = map->avatarCol + dCol;

    if (nR < 0 || nR >= map->rows || nC < 0 || nC >= map->cols) return false;

    Tile t = map->tiles[nR][nC];
    if (t == TileLockedDoor) {
        if (avatarUseKey(avatar)) map->tiles[nR][nC] = TileEmpty;
        else return false;
    } else if (!tilePassable(t)) {
        return false;
    }

    map->avatarRow = nR;
    map->avatarCol = nC;

    if (map->tiles[nR][nC] == TileGem) {
        avatarAddGem(avatar);
        map->gemsRemaining--;
        map->tiles[nR][nC] = TileEmpty;
    } else if (map->tiles[nR][nC] == TileKey) {
        avatarAddKey(avatar);
        map->tiles[nR][nC] = TileEmpty;
    }
    return true;
}
