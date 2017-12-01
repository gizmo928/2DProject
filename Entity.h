#pragma once

#ifndef __GF2D_ENTITY_H__
#define __GF2D_ENTITY_H__
#include <SDL.h>

#include "gf2d_text.h"
#include "gf2d_vector.h"

#include "gf2d_sprite.h"


#include "gf2d_graphics.h"
#include "simple_logger.h"

typedef struct Entity_s
{

	Sprite *sprite;
	Uint8 inuse; //whetherin use

	float frame;
	float curr_frame;

	Vector2D position;
	Vector2D velocity;
	Vector2D gravity;
	Vector4D color;
	Vector2D scale;
	Vector2D scaleCenter;
	Vector3D rotation;
	SDL_Rect box;
	int facing; // was gonna set this to which way you are facing.

	

	void(*update) (struct Entity_s * self);
	void(*draw)(struct Entity_s *self);
	void(*think)(struct Entity_s *self); // so im passing keys and the player entity and it works even tho this says its parameter is just an entity?
	void(*die)(struct Entity_s *self);
	void(*free)(struct Entity_s *self);
	float health;
	int dead;

}Entity;



void  gf2d_entity_system_init(Uint32 maxEntities);//initializes entity system

Entity * Ent_new(); // gets a new entity from system

void Entity_free(Entity *self); // returns an entity back to system for reycling


void Ent_draw(Entity *self);// draw a single entity
//brief
//param optional
//return optional

void Ent_draw_all();

void Ent_think();

void Ent_Update(Entity *self);

void Ent_OOB(Entity *self);

Bool ifCollision(Entity*self, Entity *targ);
void spawn_Spear(Entity*self, Entity * owner);
void fixScaling(Entity * self);



#endif