#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"

#include "Entity.h"

int main(int argc, char * argv[])
{
	/*variable declarations*/
	int done = 0;
	const Uint8 * keys;
	Sprite *sprite;
	Sprite * cavem;


	int mx, my;
	float mf = 0;
	int pressed = 0;

	Sprite *mouse;
	Sprite * spacebug; //added for testing sake
	Sprite *dino;
	Sprite * meteor;
	Sprite * spear;
	Sprite * meat;

	Vector4D mouseColor = { 255,100,255,200 };
	Vector4D cavemanColor = { 255,255,255,100 };
	Entity *temp; // this is my ENTITY
	Entity *temp2;
	Entity *temp3;
	Entity * W_spear;
	Entity *health;


	SDL_Event ev; // my event 
	/*
	Sint32 SMOUSEX = 32;
	Sint32 SMOUSEY = 32;
	Sint32 SEDX = 128;
	Sint32 SEDY = 128;
	Sint32 SCAVEMX = 197;
	Sint32 SCAVEMY = 237;
	Sint32 SSBUGX = 80;
	Sint32 SSBUGY = 128;
	*/





	


	/*program initializtion*/
	init_logger("gf2d.log");
	slog("---==== BEGIN ====---");
	gf2d_graphics_initialize(
		"gf2d",
		1200,
		720,
		1200,
		720,
		vector4d(0, 0, 0, 255), // was black
		0);
	
	
	gf2d_graphics_set_frame_delay(16);
	gf2d_sprite_init(1024);
	gf2d_entity_system_init(100); //added, 100 entities is the max entities
	SDL_ShowCursor(SDL_DISABLE);


	/*demo setup*/
	sprite = gf2d_sprite_load_image("images/backgrounds/reddit.png");
	mouse = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16);
	spacebug = gf2d_sprite_load_all("images/space_bug.png", 128, 128, 16);
	dino = gf2d_sprite_load_all("images/d1_run.png", 91, 41, 6);
	cavem = gf2d_sprite_load_all("images/caveman.png", 152, 185, 1); // was 240,280 //  197,237
	meteor = gf2d_sprite_load_all("images/meteor.png", 80, 120, 5);
	spear = gf2d_sprite_load_all("images/spear.png", 112, 41, 1);
	meat = gf2d_sprite_load_all("images/meat.png", 260, 128, 1);



	//--------------------------------------
	temp = Ent_new(); // reserves space for all entities(MAxentities?)
	temp->sprite = dino;
	temp->inuse = 1;


	temp->position = vector2d(1000, 400);
	temp->frame = mf; //  could just set to variable
	temp->scale = vector2d(1, 1);
	temp->scaleCenter = vector2d(1, 1);
	temp->health = 100;
	temp->color = vector4d(255, 255, 255, 200);

	//---------------------------------------
	
	temp2 = Ent_new();
	//temp2->inuse = 1;
	temp2->sprite = cavem;
	temp2->position = vector2d(300, 300);

	temp2->scale = vector2d(1, 1);
	temp2->scaleCenter = vector2d(0, 0); // scale this much to the x and to the y to center the sprite with blank/empty space
	temp2->frame = mf;
	temp2->health = 100; // cavemen health set to 100
	temp2->color = cavemanColor;
	Vector2D toc;

	//------------------------------------

	temp3 = Ent_new();
	temp3->inuse = 1;

	temp3->sprite = meteor;
	temp3->position = vector2d(800, 10);

	temp3->scale = vector2d(1, 1);
	temp3->scaleCenter = vector2d(1, 1);
	temp3->color = vector4d(255, 255, 255, 200);

	temp3->frame = mf;

	//------------------------------
	W_spear = Ent_new();
	W_spear->inuse = 1;

	W_spear->sprite = spear;
	W_spear->scale = vector2d(0.5, 0.5);
	W_spear->position = vector2d(200, 200);
	W_spear->scaleCenter = vector2d(1, 1);
	W_spear->color = vector4d(255, 255, 255, 500);
	W_spear->frame = mf;
	//
	health = Ent_new();
	health->sprite = meat;
	health->scale = vector2d(0.3, 0.3);
	health->position = vector2d(300, 300);
	health->frame = mf;
	health->scaleCenter = vector2d(1, 1);
	health->color = vector4d(255, 255, 255, 255);
	








	/*main game loop*/
	while (!done)
	{
		SDL_PumpEvents();  // update SDL's internal event structures user input(event)
		SDL_PollEvent(&ev);
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		/*update things here*/
		SDL_GetMouseState(&mx, &my);
		mf += 0.1;
		if (mf >= 16.0)mf = 0;
		temp->frame += 0.05;
		temp2->frame = 0.1;
		if (temp->frame >= 5) temp->frame = 1;
		//if (temp2->frame >= 15) temp2->frame = 0;
		


		gf2d_graphics_clear_screen();// clears drawing buffers
		// all drawing should happen betweem clear_screen and next_frame
			//backgrounds drawn first
		gf2d_sprite_draw_image(sprite, vector2d(0, 0));
		

		if (keys[SDL_SCANCODE_0])
		{

			toc = vector2d(mx, my); // assign mouse position at time of click
			pressed = 2;
			temp2->position = toc;

		}

		Ent_draw(temp2); //spawns caveman at mouse cursor


		temp3->position.y += 0.7; // this is how you get the entity to move
		temp3->position.x -= 0.9;



		Ent_draw(temp3);// meteor shower, and give warning that its coming.

		Ent_draw(health);


		if (keys[SDL_SCANCODE_LEFT])
		{
			temp2->position.x -= 1;
		}

		if (keys[SDL_SCANCODE_RIGHT])
		{
			temp2->position.x += 1;
		}
		if (keys[SDL_SCANCODE_UP])
		{
			temp2->position.y -= 1;
		}
		if (keys[SDL_SCANCODE_DOWN])
		{
			temp2->position.y += 1;
		}
		Ent_OOB(temp2); // calls to see if out of bounds and keeps them inside



		if (keys[SDL_SCANCODE_9]) // if press 9 deletes the entity, but if press 0 again, cant spawn the same entity in.OHH because im setting all values to 0 and its not getting those values back
		{
			if (pressed == 2)
			{
				Entity_free(temp2);
				continue;
			}
			else
			{
				pressed = 0;
			}
		}



		if (ev.type == SDL_MOUSEBUTTONDOWN)
		{
			if (ev.button.button == SDL_BUTTON_LEFT)
			{
				//spawn_Spear(&temp2, &spear);
				W_spear->position = vector2d(temp2->position.x + 120, temp2->position.y + 140);
				Ent_draw(W_spear);
				//W_spear->position.x += 100;
				//Ent_draw(W_spear);
				pressed = 1;

			}

			else if (ev.button.button == SDL_BUTTON_RIGHT)
			{
				temp2->position = vector2d(mx, my);
				Ent_draw(temp2);
			}
		}

		/*
		else if (ev.type == SDL_MOUSEBUTTONUP)
			{
				if (ev.button.button == SDL_BUTTON_LEFT)
					{
						temp->position = vector2d(mx, my);
						Ent_draw(temp);
					}
			}

		*/
		if (pressed == 1) // if player shot, move spear forwards
		{

			W_spear->position.x += 3;
			Ent_draw(W_spear);
		}


		

		//UI elements last
		gf2d_sprite_draw(
			mouse,
			vector2d(mx, my),
			NULL,
			NULL,
			NULL,
			NULL,
			&mouseColor,
			(int)mf);

		Ent_draw(temp);
		temp->position.x-= 1;
		
		if (ifCollision(temp2, temp) == false && ifCollision(temp2, temp3) == false) // if caveman collides with raptor or meteor

		{
			//temp2->health - 0;
			cavemanColor = vector4d(255, 255, 255, 200);
			temp2->color = cavemanColor;
		}

		else // if touch
		{
			//mouseColor = vector4d( 255,0,0,200);
			cavemanColor = vector4d(255, 0, 0, 200);
			temp2->color = cavemanColor;
			Ent_draw(temp2);

			temp2->health -= 1;
		}
		if (ifCollision(W_spear, temp) == false)
		{
			temp->color = vector4d(255, 255, 255, 200);
		}
		else { 
			    temp->health -= 1; // if dino hit with spear minus health by 10.
				temp->color = vector4d(255, 0, 0, 200); 
			}

		

		if (temp->health <= 0)
		{
			Entity_free(temp);
		}

		







			/*
			gf2d_sprite_draw(
				spacebug,
				vector2d(200, 200),
				&temp->scale,
				&temp->scaleCenter,
				NULL,
				NULL,
				NULL,
				temp->frame);
			*/
			
		gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
		if (keys[SDL_SCANCODE_ESCAPE]) { done = 1; pressed = 0; } // exit condition
        slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
	
}
/*eol@eof*/
