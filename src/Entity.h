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


/**
* @brief initializes entity system
* @param maxEntities, a Uint32 to let the system know whats the maximum amount of entities
*/
void  gf2d_entity_system_init(Uint32 maxEntities);

/**
* @brief creates a new entity of type entity
* @return An Entity object
*/
Entity * Ent_new(); 


/**
* @brief releases the entity from memory space
* @param takes an pointer of type entity
*/
void Entity_free(Entity *self); 


/**
* @brief draws a single entity
* @param takes a pointer to the entity to be drawn
*/
void Ent_draw(Entity *self);


/**
* @brief calls Ent_draw() function and draws all entities
*/
void Ent_draw_all();

/**
* @brief possible actions an entity could cause
*/
void Ent_think();

/**
* @brief updates the entity each frame
* @param takes in the Entity pointer to be updated
*/
void Ent_Update(Entity *self);

/**
* @brief checks to see if the entity is out of bounds which is screen space 1200x720
* @param takes in the entity to be evaluated and makes it stay in boundary
*/
void Ent_OOB(Entity *self);

/**
* @brief takes two entities and detects if they are touching
* @param first entity to be tested if touching another entity
* @param second entity to be tested against the first entity self
* @return a bool, true if colliding or false if not colliding
*/
Bool ifCollision(Entity*self, Entity *targ);



#endif