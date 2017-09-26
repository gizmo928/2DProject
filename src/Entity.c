//This will actually have the function definitons, variables

#include "Entity.h"
#include "simple_logger.h"
#include "gf2d_sprite.h"

typedef struct 
{
	Uint32 maxEntities;
	Entity *entityList;
	Uint64 autoincrement;
	

	
}EntityManager;




static EntityManager entity_manager = { 0 };



void gf2d_entity_system_init(Uint32 maxEntities)

{
	if (!maxEntities)
	{
		slog("cannot initialize entity system for zero entities");
		return;
	}
	//memset(&entity_manager, 0, sizeof(EntityManager));

	entity_manager.entityList = (Entity*)malloc(sizeof(Entity)*maxEntities);
	
	//memset(&entity_manager.entityList, 0, sizeof(Entity)*maxEntities);// sets your whole entity list to your max entities, which is 1024 for me i think
	entity_manager.maxEntities = maxEntities;
	slog("entity system initialized");

}


Entity * Ent_new()
{
	int i;
	for (i = 0; i < entity_manager.maxEntities; i++)
	{
		if (entity_manager.entityList[i].inuse == 0)
		{
			memset(&entity_manager.entityList[i], 0, sizeof(Entity));
			entity_manager.entityList[i].inuse = 1;
			return &entity_manager.entityList[i];
		}
	}
	return NULL;
}

void Ent_free(Entity *self)
{
	if (!self) return;
	if (self->free) self->free(self); // what??
	memset(self, 0, sizeof(Entity)); // sets the value to 0 but still has a size of Entity?
}

void Ent_draw(Entity *self)
{
	
	if (!self)return;
	if (!self->inuse) return; // dont really need thse 2 lines of code but i guess its for being careful?

	gf2d_sprite_draw(
		self->sprite,
		self->position,
		&self->scale,
	&self->scaleCenter, 
	NULL,
	NULL,
	NULL,
	(Uint32) self->frame);
	
	/*
	if (self->draw != NULL)
	{
		self->draw(self);
	}
	*/
}

















