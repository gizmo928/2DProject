#pragma once

#ifndef __GF2D_ENTITY_H__
#define __GF2D_ENTITY_H__

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
	Vector4D color;
	Vector2D scale;
	Vector2D scaleCenter;
	

	void(*update) (struct Entity_s * self);
	void(*draw)(struct Entity_s *self);
	void(*think)(struct Entity_s *self);
	void(*die)(struct Entity_s *self);
	void(*free)(struct Entity_s *self);
	float health;
	int dead;

}Entity;



void  gf2d_entity_system_init(Uint32 maxEntities);//initializes entity system

Entity * Ent_new(); // gets a new entity from system

void Entity_free(Entity *self); // returns an entity back to system for reycling


void Ent_draw(Entity *self);// draw a single entity

void Ent_Update(Entity *self);

#endif