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
	memset(&entity_manager, 0, sizeof(EntityManager));

	entity_manager.entityList = (Entity*)malloc(sizeof(Entity)*maxEntities);
	
	memset(entity_manager.entityList, 0, sizeof(Entity)*maxEntities);// sets your whole entity list to your max entities, which is 1024 for me i think
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

void Entity_free(Entity *self)
{
	if (!self) return;
//	if (self->free) self->free(self); // what??
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
	&self->rotation,
	NULL,
	&self->color,
	(Uint32) self->frame);
	
	
	if (self->draw != NULL)
	{
		self->draw(self);
	}
	
	//if (self->scale.x >= 1 || self->scale.y >= 1)
	{
		self->box.x = self->position.x; // right?
		self->box.y = self->position.y;
		self->box.w = self->sprite->frame_w;
		self->box.h = self->sprite->frame_h;
	}
	
}
/*AS OF NOW, JUST GETS PLAYER MOVEMENT*/
void Ent_think(Uint8 * keys, Entity * self, Sprite * wl, Sprite * wr) // walk left brings left walking sprite sheet, wlk right does it for the right side
{
	int pressed = 0;
	int velocity = 20;
	int gravity = 9;
	gravity += velocity;
	if (keys[SDL_SCANCODE_A])
	{
		self->sprite = wl;
		self->position.x -= 1;
		
		for (int i = 0; i < 21; i++) {


			entity_manager.entityList[i].position.x += 1;
			if (entity_manager.entityList[0].position.x + 1200 <  0 && entity_manager.entityList[0].position.x + 1200 < entity_manager.entityList[1].position.x)
			{
				entity_manager.entityList[0].position.x = entity_manager.entityList[1].position.x + 1199;
				Ent_draw_all();
			}
			else if (entity_manager.entityList[1].position.x + 1200 < 0 && entity_manager.entityList[1].position.x < entity_manager.entityList[0].position.x)
			{
				entity_manager.entityList[1].position.x = entity_manager.entityList[0].position.x + 1200;
				Ent_draw_all();
			}
		}

	}

	if (keys[SDL_SCANCODE_D])
	{
		self->sprite = wr;
		self->position.x += 1;
		
		
		for (int i = 0; i < 21; i++) {

			
			entity_manager.entityList[i].position.x -= 1;
			if (entity_manager.entityList[0].position.x + 1200 <  0 && entity_manager.entityList[0].position.x + 1200 < entity_manager.entityList[1].position.x)
			{
				entity_manager.entityList[0].position.x = entity_manager.entityList[1].position.x +1199;
				Ent_draw_all();
			}
			else if (entity_manager.entityList[1].position.x + 1200 < 0 && entity_manager.entityList[1].position.x < entity_manager.entityList[0].position.x)
			{
				entity_manager.entityList[1].position.x = entity_manager.entityList[0].position.x + 1200;
				Ent_draw_all();
			}
		}


	}

	
}

void Ent_draw_all()
{
	int i;
	for (i = 0; i < entity_manager.maxEntities; i++)
	{
		if (entity_manager.entityList[i].inuse == 0)continue;
		Ent_draw(&entity_manager.entityList[i]);
	}

}

void Ent_update(Entity *self)
{
	if (self->dead != 0)
	{
		Entity_free(self);
		return;
	}
	vector2d_add(self->position, self->position, self->velocity);// idk about this
	


}

void Ent_OOB(Entity *self) // Out of bounds
{
	

	if (self->box.x < 0)
	{
		self->position.x = 0;
	}
	else if (self->box.x > 1200 - self->box.w)
	{
		self->position.x = 1200 - self->box.w;
	}
	if (self->box.y < 0)
	{
		self->position.y = 0;
	}
	else if (self->box.y > 700 - self->box.h)
	{
		self->position.y = 700 - self->box.h;
	}

}
Bool ifCollision(Entity*self, Entity *targ)
{
	
		if (!self->inuse) return false; // if its freed then dont collide.
		/*if (self->position.x + self->sprite->frame_w < targ->position.x || self->position.x > targ->position.x + targ->sprite->frame_w ||  // maybe use rect_box???
			self->position.y + self->sprite->frame_h < targ->position.y || self->position.y > targ->position.y + targ->sprite->frame_h)*/
			/*
			if (self->scale.x < 1 ) // if the scale is less than 1 set bounding box accordingly to the scale.
			{
				float holdx = self->sprite->frame_w * self->scale.x;


				self->sprite->frame_w = self->sprite->frame_w - holdx;
				self->box.w = self->sprite->frame_w;


			}
			if (self->scale.y < 1)
			{
				float holdy = self->sprite->frame_h * self->scale.y;

				self->sprite->frame_h = self->sprite->frame_h - holdy;
				self->box.h = self->sprite->frame_h;
			}
			if (targ->scale.x < 1 )
			{
				float holdxx = targ->sprite->frame_w * targ->scale.x;


				targ->sprite->frame_w = targ->sprite->frame_w - holdxx;
				targ->box.w = targ->sprite->frame_w;


			}
			if (targ->scale.y < 1)
			{
				float holdyy = targ->sprite->frame_h * targ->scale.y;

				targ->sprite->frame_h = targ->sprite->frame_h - holdyy;
				targ->box.h = targ->sprite->frame_h;
			}
			*/
		if (self->box.x + self->box.w < targ->box.x || self->box.x > targ->box.x + targ->box.w ||  // maybe use rect_box???
			self->box.y + self->box.h < targ->box.y || self->box.y > targ->box.y + targ->box.h)
		{
			return false;
		}
		else return true;
	}


void  spawn_Spear(Entity *self, Entity * owner)
{
	Entity *sp;
	sp = malloc(sizeof(Entity));
	sp = Ent_new();
	sp->position =vector2d(owner->position.x + 120, owner->position.y + 140);
	sp->sprite = self->sprite;
	sp->scale = vector2d(0.5, 0.5);

	sp->scaleCenter = vector2d(1, 1);
	sp->color = vector4d(255, 255, 255, 255);
	sp->frame = 1;
	
	sp->position.x -= 10;
	
}

void fixScaling(Entity * self)
{
	if (self->scale.x < 1) // if the scale is less than 1 set bounding box accordingly to the scale.
	{
		float holdx = self->sprite->frame_w * self->scale.x;


		float xx= self->sprite->frame_w - holdx;
		self->box.w = xx;


	}
	if (self->scale.y < 1)
	{
		float holdy = self->sprite->frame_h * self->scale.y;

		float yy = self->sprite->frame_h - holdy;
		self->box.h = yy;
	}

	
}














