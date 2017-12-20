#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "gf2d_audio.h"
#include "gf2d_vector.h"
#include <SDL_mixer.h>
#include <math.h>



#include "Entity.h"

int main(int argc, char * argv[])
{
	/*variable declarations*/
	float myGravity = 0.2f;
	float jumpVel = 6;
	float deltaTime;
	float tocy;
	Bool m_jumping = false;

	int weapon_choice = 1;
	int done = 0;
	int done1 = 0;
	int done2 = 0;
	double dx, dy, angle[5];
	int is_armored = 0;
	const Uint8 * keys;
	Sprite *sprite;
	Sprite * grounds;
	Sprite * pause_s;
	
	Sprite * load;
	Sprite * cavem;
	Sprite *cavemL;
	Sprite *cavemL_armor;
	Sprite * cavem_armor;
	Vector2D direction[5];


	int mx, my;
	float mf = 0;
	int pressed = 0;
	int count = 0;
	
	

	Sprite *mouse;
	Sprite * spacebug; //added for testing sake
	Sprite *dino;
	Sprite * meteor;
	Sprite * spear;
	Sprite * rocks;
	Sprite * big_healthS;
	Sprite * heart;
	Sprite *small_healthS;
	Sprite * trex;
	Sprite * ptero;
	Sprite * armorS;
	Sprite * clubs;
	
	

	Vector4D mouseColor = { 255,100,255,200 };
	
	Entity *temp; // this is my ENTITY
	Entity *temp2;
	Entity *temp3;
	Entity * temp4;
	Entity * W_spear[5];
	Entity * rock[5];
	Entity * big_health;
	Entity * small_health;
	Entity * ent_ptero;
	Entity * ent_armor;
	Entity * club;
	Entity * ground;
	Entity * ground2;
	Entity * dead;

	Mix_Music *bg;
	Mix_Chunk * spear_throw_fx;
	Mix_Chunk * pickup_smallhealth;
	Mix_Chunk * pickup_bighealth;
	Mix_Chunk * pickup_armor;
	Mix_Chunk * gruntFX;
	Mix_Chunk * break_bonesFX;
	SDL_Event ev; // my event 








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
	gf2d_audio_init(256, 16, 4, 1, 1, 1);
	gf2d_sprite_init(1024);
	gf2d_entity_system_init(100); //added, 100 entities is the max entities
	SDL_ShowCursor(SDL_DISABLE);

	
	/*demo setup*/
	//pause_s = gf2d_sprite_load_image("images/backgrounds/pause.jpg");
	sprite = gf2d_sprite_load_image("images/backgrounds/reddit.png");
	dead = gf2d_sprite_load_image("images/backgrounds/diestate.png");

	load = gf2d_sprite_load_image("images/backgrounds/loading.png");
	mouse = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16);
	spacebug = gf2d_sprite_load_all("images/space_bug.png", 128, 128, 16);
	dino = gf2d_sprite_load_all("images/d1_run.png", 91, 41, 6);
	cavem = gf2d_sprite_load_all("images/small_caveman_SS.png", 32, 32, 4); // was 240,280 //  197,237
	cavemL = gf2d_sprite_load_all("images/small_caveman_SSL.png", 32, 32, 4);
	cavem_armor = gf2d_sprite_load_all("images/small_caveman_SS_armored.png", 32, 32, 4);
	cavemL_armor = gf2d_sprite_load_all("images/small_caveman_SSL_armored.png", 35, 32, 4);
	meteor = gf2d_sprite_load_all("images/meteor.png", 80, 120, 5);
	spear = gf2d_sprite_load_all("images/spear.png", 112, 41, 1);
	rocks = gf2d_sprite_load_all("images/rock.png", 85, 79, 1);
	clubs = gf2d_sprite_load_all("images/club.png", 128, 125, 1);
	grounds = gf2d_sprite_load_all("images/fossilground.png", 1200, 400, 1);

	big_healthS = gf2d_sprite_load_all("images/big_health.png", 113, 80, 1);
	small_healthS = gf2d_sprite_load_all("images/small_health.png", 58, 61, 1);
	trex = gf2d_sprite_load_all("images/t-rex.png", 104, 52, 2);
	ptero = gf2d_sprite_load_all("images/ptero.png", 169, 131, 6);
	armorS = gf2d_sprite_load_all("images/armor.png", 126, 72, 7);

	spear_throw_fx = Mix_LoadWAV("sounds/spear_throw.wav");
	pickup_smallhealth = Mix_LoadWAV("sounds/pickup_smallhealth.wav");
	pickup_bighealth = Mix_LoadWAV("sounds/pickup_bighealth.wav");
	pickup_armor = Mix_LoadWAV("sounds/pickup_armor.wav");
	gruntFX = Mix_LoadWAV("sounds/human_grunt.wav");
	break_bonesFX = Mix_LoadWAV("sounds/bb.wav"); 
	bg = Mix_LoadMUS("sounds/root.wav"); // was root



	Mix_VolumeMusic(20); // changes bg volume
	Mix_PlayMusic(bg, -1);

	Mix_VolumeChunk(gruntFX, 20);
	
	
	ground = Ent_new();
	ground->sprite = grounds;
	ground->position = vector2d(0, 430);
	ground->scale = vector2d(1, 1);
	ground->color = vector4d(255, 255, 255, 255);
	//--------------------------------------
	ground2 = Ent_new();
	ground2->sprite = grounds;
	ground2->position = vector2d(1200, 430);
	ground2->scale = vector2d(1, 1);
	ground2->color = vector4d(255, 255, 255, 255);
	
	//--------------------------------------
	temp = Ent_new(); // reserves space for all entities(MAxentities?)
	temp->sprite = dino;
	temp->inuse = 1;

	
	temp->position = vector2d(1000, 400);
	temp->frame = mf; //  could just set to variable
	temp->scale = vector2d(1, 1);
	temp->scaleCenter = vector2d(1, 1);
	temp->health = 100;
	temp->color = vector4d(255, 255, 255, 255);

	//---------------------------------------

	temp2 = Ent_new();
	//temp2->inuse = 1;
	temp2->sprite = cavem;
	temp2->position = vector2d(10, 410);
	//temp2->velocity = vector2d(3, 3);
	temp2->scale = vector2d(1, 1);
	temp2->scaleCenter = vector2d(0, 0); // scale this much to the x and to the y to center the sprite with blank/empty space
	temp2->frame = mf;
	temp2->health = 100; // cavemen health set to 100
	temp2->color = vector4d(0,0,0,255);
	temp2->rotation = vector3d(0, 0, 0); // so z is what rotates the sprite hmmmm interesting yes very interesting

	temp2->think = Ent_think;
	Vector2D toc[5];



	//------------------------------------

	temp3 = Ent_new();
	temp3->inuse = 1;

	temp3->sprite = meteor;
	temp3->position = vector2d(800, 10);

	temp3->scale = vector2d(1, 1);
	temp3->scaleCenter = vector2d(1, 1);
	temp3->color = vector4d(255, 255, 255, 255);
	temp3->rotation = vector3d(0, 0, 50);

	temp3->frame = mf;

	//------------------------------
	for (int i = 0; i < 5; i++) {
		W_spear[i] = Ent_new();
		//W_spear[i]->inuse = 1; // 

		W_spear[i]->sprite = spear;
		W_spear[i]->scale = vector2d(0.5, 0.5);
		//W_spear[i]->position = vector2d(200, 200);
		W_spear[i]->scaleCenter = vector2d(1, 1);
		W_spear[i]->color = vector4d(255, 255, 255, 500);
		//W_spear[i]->rotation = vector3d(10, 10, 180);
		
		W_spear[i]->frame = mf;
}
	//-------------------------------------
	for (int i = 0; i < 5; i++)
	{
		rock[i] = Ent_new();
		rock[i]->sprite = rocks;
		rock[i]->scale = vector2d(0.5, 0.5);
		//rock->color = vector4d(255, 255, 255, 255);
		//rock->frame = mf;
	}
	
	//-------------------------------------
	club = Ent_new();
	club->sprite = clubs;

	club->scale = vector2d(0.3, 0.3);

	//-------------------------------------
	big_health = Ent_new();
	big_health->sprite = big_healthS;
	big_health->scale = vector2d(0.5, 0.5);
	big_health->position = vector2d(300, 300);
	big_health->frame = mf;
	big_health->scaleCenter = vector2d(1, 1);
	big_health->color = vector4d(255, 255, 255, 255);
	//--------------------------------------------
	small_health = Ent_new();
	small_health->sprite = small_healthS;
	small_health->scale = vector2d(0.5, 0.5);
	small_health->position = vector2d(600, 300);
	small_health->frame = mf;
	small_health->scaleCenter = vector2d(1, 1);
	small_health->color = vector4d(255, 255, 255, 255);
	//----------------------------------------------
	ent_armor = Ent_new();
	ent_armor->sprite = armorS;
	ent_armor->scale = vector2d(0.5, 0.5);
	ent_armor->position = vector2d(700, 300);
	ent_armor->frame = mf;
	ent_armor->scaleCenter = vector2d(1, 1);
	ent_armor->color = vector4d(255, 255, 255, 255);
	
	//--------------------------------------
	temp4 = Ent_new(); // reserves space for all entities(MAxentities?)
	temp4->sprite = trex;
	
	temp4->inuse = 1;


	temp4->position = vector2d(1200, 400);
	temp4->frame = mf; //  could just set to variable
	temp4->scale = vector2d(1, 1);
	temp4->scaleCenter = vector2d(1, 1);
	temp4->health = 300;
	temp4->color = vector4d(255, 255, 255, 255);
	//=========================================
	//fixScaling(health);
	//========================================
	ent_ptero = Ent_new(); // reserves space for all entities(MAxentities?)
	ent_ptero->sprite = ptero;
	ent_ptero->inuse = 1;
	ent_ptero->rotation = vector3d(0, 0, 0);

	ent_ptero->position = vector2d(1300, 200);
	ent_ptero->frame = mf; //  could just set to variable
	ent_ptero->scale = vector2d(1, 1);
	ent_ptero->scaleCenter = vector2d(1, 1);
	ent_ptero->health = 300;
	ent_ptero->color = vector4d(255, 255, 255, 255);

	while (!done1)
	{
		SDL_PumpEvents();
		gf2d_graphics_clear_screen();
		gf2d_sprite_draw_image(load, vector2d(0, 0));
		keys = SDL_GetKeyboardState(NULL);
		gf2d_grahics_next_frame();
		if (keys[SDL_SCANCODE_RETURN])
		{

			done1 = 1;
		}


		
	}
	


	/*main game loop*/
	while (!done)
	{
		deltaTime = 0.3;
		pressed++;

		SDL_PumpEvents();  // update SDL's internal event structures user input(event)
		SDL_PollEvent(&ev);
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		/*update things here*/
		SDL_GetMouseState(&mx, &my);
		mf += 0.1;
		if (mf >= 16.0)mf = 0;
		temp->frame += 0.05;
		temp4->frame += 0.05;
		temp2->frame += 0.07;
		big_health->frame = 0.1;
		ent_ptero->frame += 0.1;
		if (temp->frame >= 5) temp->frame = 0.1;
		if (temp4->frame >= 6) temp4->frame = 0.1;
		//if (ent_ptero->frame >= 4) ent_ptero->sprite->frame_w = 143;
		if (ent_ptero->frame >= 6) { ent_ptero->frame = 0.1; ent_ptero->sprite->frame_w = 169; }
		//if (big_health->frame >= 7) big_health->frame = 1;
		if (temp2->frame >= 16) temp2->frame = 0.1;



		gf2d_graphics_clear_screen();// clears drawing buffers
		// all drawing should happen betweem clear_screen and next_frame
			//backgrounds drawn first
		gf2d_sprite_draw_image(sprite, vector2d(0, 0));

		//Ent_draw_all();

		if (keys[SDL_SCANCODE_0])
		{

			toc[count] = vector2d(mx, my); // assign mouse position at time of click
			pressed = 2;
			temp2->position = toc[count];

		}

		/*MOVING METEOR*/

		
		if (temp3->position.y > 720)
		{
			temp3->position.x = temp2->position.x +1000;
			temp3->position.y = -20;
			Ent_draw_all();
		}
		else {
			temp3->position.y += 0.7; // this is how you get the entity to move
			temp3->position.x -= 0.9;
		}


		if (!is_armored)
			temp2->think(keys, temp2, cavemL, cavem);
		else
			temp2->think(keys, temp2, cavemL_armor, cavem_armor);// this works
		//Ent_think(keys, temp2); // this works


		if (keys[SDL_SCANCODE_SPACE])
		{
			m_jumping = true;


		}

		if (m_jumping)
		{
			temp2->position.y -= jumpVel * deltaTime;

			jumpVel -= myGravity * deltaTime;
		}

		if (temp2->position.y > 400) // this is the fake ground
		{
			jumpVel = 6; // to reset
			m_jumping = false;
		}

		//Ent_Update(temp2);

		vector2d_add(temp2->position, temp2->position, temp2->velocity);// idk about this

		Ent_OOB(temp2); // calls to see if out of bounds and keeps them inside



		if (keys[SDL_SCANCODE_1])
		{
			weapon_choice = 1;

		}
		if (keys[SDL_SCANCODE_2])
		{
			weapon_choice = 2;

		}
		if (keys[SDL_SCANCODE_3])
		{
			weapon_choice = 3;
		}

		


		if (ev.type == SDL_MOUSEBUTTONDOWN)
		{

			if (ev.button.button == SDL_BUTTON_LEFT && pressed >= 40 && weapon_choice == 1)
			{

				W_spear[count]->position = vector2d(temp2->position.x + 10, temp2->position.y + 10);



				toc[count] = vector2d(mx, my);
				direction[count].x = toc[count].x - W_spear[count]->position.x; // mouse x minus caveman's x position and sets to vector2d directions x
				direction[count].y = toc[count].y - W_spear[count]->position.y;

				vector2d_normalize(&direction[count]); // normalize the vector


				angle[count] = atan2(toc[count].y - W_spear[count]->position.y, toc[count].x - W_spear[count]->position.x); //  acquire angle
				angle[count] = 180 / M_PI * angle[count]; // convert angle from radians to degrees

				W_spear[count]->rotation = vector3d(0, 0, angle[count]); // IT WORKS THANK U



				count++;
				if (count > 4)
				{
					count = 0;
				}
				pressed = 1;
				Mix_PlayChannel(-1, spear_throw_fx, 0); // doesnt look right so far, might move into for loop

			//Ent_draw(W_spear[count]);
			}

			else if (ev.button.button == SDL_BUTTON_LEFT && pressed >= 80 && weapon_choice == 2)
			{

				rock[count]->position = vector2d(temp2->position.x + 10, temp2->position.y + 10);

				rock[count]->color = vector4d(255, 255, 255, 255);

				toc[count] = vector2d(mx, my);
				direction[count].x = toc[count].x - rock[count]->position.x; // mouse x minus caveman's x position and sets to vector2d directions x
				direction[count].y = toc[count].y - rock[count]->position.y;

				vector2d_normalize(&direction[count]); // normalize the vector


				angle[count] = atan2(toc[count].y - rock[count]->position.y, toc[count].x - rock[count]->position.x);
				angle[count] = 180 / M_PI * angle[count];

				rock[count]->rotation = vector3d(0, 0, angle[count]);

				count++;
				if (count > 4)
				{
					count = 0;
				}
				pressed = 1;
				Mix_PlayChannel(-1, spear_throw_fx, 0); // change to rock sound
			}
			else if (ev.button.button == SDL_BUTTON_LEFT  && weapon_choice == 3)
			{
				club->position = vector2d(temp2->position.x + 46, temp2->position.y - 15);
				
				club->color = vector4d(255, 255, 255, 255);
				club->rotation = vector3d(0, 0, 40);
				
				
			}
		

		}
		if (ev.type == SDL_MOUSEBUTTONUP)
		{
			if (ev.button.button == SDL_BUTTON_LEFT && weapon_choice == 3)
			{
				club->color = vector4d(255, 255, 255, 0);
			}
		}


		for (int i = 0; i < 5; i++)
		{

			W_spear[i]->position.x += direction[i].x * 3; // still working
			W_spear[i]->position.y += direction[i].y * 3; // still working
												   //W_spear[i]->rotation = vector3d(0, 0, angle); THIS WAS SCREWING WITH ME, WHAT IS ANGLE???? SEEMED LIKE 0

			Ent_draw(W_spear[i]);


		}


		for (int i = 0; i < 5; i++)
		{

			rock[i]->position.x += direction[i].x * 2; // still working
			rock[i]->position.y += direction[i].y; // still working		

			Ent_draw(rock[i]);


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

	

		/*
		DINO/TREX/PTERO/METEOR HURTS CAVEMAN(PLAYER)
		*/
		if (ifCollision(temp2, temp) == false && ifCollision(temp2, temp3) == false && ifCollision(temp2, temp4) == false && ifCollision(temp2, ent_ptero) == false) // if caveman collides with raptor or meteor

		{

			temp2->color = vector4d(255, 255, 255, 255);
			//vector2d_set_angle_by_radians(&temp2->position, 20);


		}

		else // if touch
		{


			Mix_PlayChannel(-1, gruntFX, 0);
			temp2->color = vector4d(255, 0, 0, 255);
			Ent_draw(temp2); // still need ent_draw in here so caveman turns red

			temp2->health -= 1;
		}
		/*
		SPEAR DAMAGES DINO
		*/


		if (ifCollision(W_spear[0], temp) == false && ifCollision(W_spear[1], temp) == false && ifCollision(W_spear[2], temp) == false && ifCollision(W_spear[3], temp) == false && ifCollision(W_spear[4], temp) == false && ifCollision(rock[0], temp) == false && ifCollision(rock[1], temp) == false && ifCollision(rock[2], temp) == false && ifCollision(rock[3], temp) == false && ifCollision(rock[4], temp) == false && ifCollision(club,temp)== false)
		{
			temp->color = vector4d(255, 255, 255, 255);
		}
		else {
			temp->health -= 1; // if dino hit with spear minus health by 10.
			//Mix_PlayChannel(-1, break_bonesFX, 0);
			temp->color = vector4d(255, 0, 0, 255);

		}
		/*
		SPEAR DAMAGES TREX
		*/
		if (ifCollision(W_spear[0], temp4) == false && ifCollision(W_spear[1], temp4) == false && ifCollision(W_spear[2], temp4) == false && ifCollision(W_spear[3], temp4) == false && ifCollision(W_spear[4], temp4) == false && ifCollision(rock[0], temp4) == false && ifCollision(rock[1], temp4) == false && ifCollision(rock[2], temp4) == false && ifCollision(rock[3], temp4) == false && ifCollision(rock[4], temp4) == false && ifCollision(club, temp) == false) // if spear hits the fino
		{
			temp4->color = vector4d(255, 255, 255, 255);
		}
		else {
			temp4->health -= 1; // if trex hit with spear minus health by 10.
		//	Mix_PlayChannel(-1, break_bonesFX, 0);
			temp4->color = vector4d(255, 0, 0, 255);
		}
		/*
		SPEAR DAMAGES PTERO
		*/
		if (ifCollision(W_spear[0], ent_ptero) == false && ifCollision(W_spear[1], ent_ptero) == false && ifCollision(W_spear[2], ent_ptero) == false && ifCollision(W_spear[3], ent_ptero) == false && ifCollision(W_spear[4], ent_ptero) == false && ifCollision(rock[0], ent_ptero) == false && ifCollision(rock[1], ent_ptero) == false && ifCollision(rock[2], ent_ptero) == false && ifCollision(rock[3], ent_ptero) == false && ifCollision(rock[4], ent_ptero) == false && ifCollision(club, temp) == false) // if spear hits the fino
		{
			ent_ptero->color = vector4d(255, 255, 255, 255);
		}
		else {
			ent_ptero->health -= 1; // if ptero hit with spear minus health by 10.
			//Mix_PlayChannel(-1, break_bonesFX, 0);
			ent_ptero->color = vector4d(255, 0, 0, 255);
		}


		/*
		BIG HEALTH PICKUP
		*/
		if (ifCollision(temp2, big_health) == true) // if player touches big health pack
		{
			//temp2->color = vector4d(255,255,255,255);
			temp2->color = vector4d(0, 255, 0, 255);
			Mix_PlayChannel(-1, pickup_bighealth, 0);
			Entity_free(big_health);
		}

		/*
		SMALL HEALTH PCIKUP
		*/
		if (ifCollision(temp2, small_health) == true) // if player touches big health pack
		{
			//temp2->color = vector4d(255,255,255,255);
			temp2->color = vector4d(0, 255, 0, 255);
			Mix_PlayChannel(-1, pickup_smallhealth, 0);
			Entity_free(small_health);
		}

		/*
		ARMOR PICKUP
		*/
		if (ifCollision(temp2, ent_armor) == true) // if player touches big health pack // WHAT IF I JUST SAY IF COLLISION == TRUE
		{
			//	temp2->color = vector4d(255,255,255,255);
			temp2->color = vector4d(0, 255, 255, 255);
			is_armored = 1;
			Ent_draw(temp2);
			Mix_PlayChannel(-1, pickup_armor, 0);
			//SDL_Delay(500);
			Entity_free(ent_armor);
		}


		if (temp->health <= 0)
		{
			Mix_PlayChannel(-1, break_bonesFX, 0);
			temp->position.x = temp2->position.x + 1450;
			temp->health = 100;

		}
		else if (temp->position.x < -20)
		{
			temp->position.x = temp2->position.x + 1450;
		}
		else
		{
			//Ent_draw(temp); // dino
			temp->position.x -= 0.5;
		
		}
		if (temp4->health <= 0)
		{
			Mix_PlayChannel(-1, break_bonesFX, 0);
			temp4->position.x = temp2->position.x + 1500;
			temp4->health = 300;
		}
		else if (temp4->position.x < -40)
		{
			temp4->position.x = temp2->position.x + 1450;
		}
		else
		{
			//Ent_draw(temp4); //trex
			temp4->position.x -= 0.3;
			
		}
		if (ent_ptero->health <= 0)
		{
			Mix_PlayChannel(-1, break_bonesFX, 0);
			ent_ptero->position.x = temp2->position.x + 1380;
			ent_ptero->health = 360;
		}
		else if (ent_ptero->position.x < -60)
		{
			ent_ptero->position.x = temp2->position.x + 1450;
		}
		else {
			//Ent_draw(ent_ptero); //ptero
			ent_ptero->position.x -= 0.8;
		}

	
	
		Ent_draw_all();

		

			while (temp2->health <= 0)
			{
				SDL_PumpEvents();
				gf2d_graphics_clear_screen();
				gf2d_sprite_draw_image(dead, vector2d(0, 0));
				keys = SDL_GetKeyboardState(NULL);
				gf2d_grahics_next_frame();
				if (keys[SDL_SCANCODE_RETURN])
				{

					done2 = 1;
					temp2->health = 100;
				}



			
		}

			
		gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
		if (keys[SDL_SCANCODE_ESCAPE]) { done = 1; pressed = 0; } // exit condition
        slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;
	
}
/*eol@eof*/
