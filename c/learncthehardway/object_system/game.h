#ifndef _game_h
#define _game_h

#include "object.h"

typedef struct {
    Object proto;
    int hit_points;
} Monster;

int Monster_attack(void *self, int damage);
int Monster_init(void *self);

struct Room {
    Object proto;
    Monster *bad_guy;

    struct Room *north;
    struct Room *south;
    struct Room *east;
    struct Room *west;
};

typedef struct Room Room;

void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);
int Room_init(void *self);

typedef struct {
    Object proto;
    Room *start;
    Room *location;
} Map;

void *Map_move(void *self, Direction direction);
int Map_attck(void *self, int damage);
int Map_init(void *self);

#endif
