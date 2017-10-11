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

    
    int mx,my;
    float mf = 0;
	int pressed = 0;

    Sprite *mouse;
	Sprite * spacebug; //added for testing sake
	Sprite* ed;
	
    Vector4D mouseColor = {255,100,255,200};
	Vector4D cavemanColor = { 255,0,0,200 };
	Entity temp; // this is my ENTITY
	Entity temp2;
	
	SDL_Event ev; // my event 
	Sint32 SMOUSEX = 32;
	Sint32 SMOUSEY = 32;
	Sint32 SEDX = 128;
	Sint32 SEDY = 128;
	Sint32 SCAVEMX = 240 ;
	Sint32 SCAVEMY = 280 ;
	Sint32 SSBUGX = 128;
	Sint32 SSBUGY = 128;

	
	


	//gf2d_shape_circle(0, 0, 8);
	
    
    /*program initializtion*/
    init_logger("gf2d.log");
    slog("---==== BEGIN ====---");
    gf2d_graphics_initialize(
        "gf2d",
        1200,
        720,
        1200,
        720,
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
	gf2d_entity_system_init(100); //added, 100 entities is the max entities
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    sprite = gf2d_sprite_load_image("images/backgrounds/reddit.png");
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
	spacebug = gf2d_sprite_load_all("images/space_bug.png", 128, 128, 16);
	ed = gf2d_sprite_load_all("images/ed210.png", 128, 128, 16);
	cavem = gf2d_sprite_load_all("images/caveman.png", 240, 280, 1);
	


	//--------------------------------------
	Ent_new(); // reserves space for all entities(MAxentities?)
	temp.sprite = spacebug;
	//temp.inuse = 1;
	temp.position = vector2d(500, 500);
	temp.frame = mf; //  could just set to variable
	temp.scale = vector2d(1, 1);
	temp.scaleCenter = vector2d(100, 100);
	temp.color = vector4d(255, 255, 255, 200);
	
	//---------------------------------------
	
	temp2.inuse = 1;
	temp2.sprite = cavem;
	//temp2.position = vector2d(400, 400);
	//temp2.velocity = vector2d(20, 20);
	temp2.scale = vector2d(1, 1);
	temp2.scaleCenter = vector2d(100, 100);
	temp2.frame = mf;
	temp2.health = 100; // cavemen health set to 100
	temp2.color = cavemanColor;
	Vector2D toc;

	//------------------------------------

	



	


    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();  // update SDL's internal event structures user input(event)
		SDL_PollEvent(&ev);
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;
		temp.frame += 0.1;
		temp2.frame = 0.1;
		if (temp.frame >=80) temp.frame = 0;
		//if (temp2.frame >= 15) temp2.frame = 0;
        
		
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));
			
			if (keys[SDL_SCANCODE_0])
			{
				
				toc= vector2d(mx, my); // assign mouse position at time of click
				pressed =1;
				temp2.position = toc;
				
				

			}
			
			Ent_draw(&temp2); // after you press '0' the entity draws temp2 with the position of toc
				

					if (keys[SDL_SCANCODE_LEFT])
					{
						//temp2.position.x -= 1;
						if (temp2.position.x < 75) // value to change
						{
							temp2.position.x = 74; //value to change
						}
						else
							temp2.position.x -= 1;
					}

					if (keys[SDL_SCANCODE_RIGHT])
					{
						if (temp2.position.x > 1224)
						{
							temp2.position.x = 1225;
						}
						else
						temp2.position.x += 1;
					}
					if (keys[SDL_SCANCODE_UP])
					{
						if (temp2.position.y < 50) // value to change
						{
							temp2.position.y = 49; // value too change
						}
						else
						temp2.position.y -= 1;
					}
					if (keys[SDL_SCANCODE_DOWN])
					{
						if (temp2.position.y > 726)
						{
							temp2.position.y = 727;
						}
						else
						temp2.position.y += 1;
					}
					
					
				

				if (keys[SDL_SCANCODE_9]) // if press 9 deletes the entity, but if press 0 again, cant spawn the same entity in.OHH because im setting all values to 0 and its not getting those values back
				{
						if (pressed == 1)
						{
							Entity_free(&temp2);
							continue;
						}
						else
						{
							pressed = 0;
						}
				}
			
				/*
		
			if (ev.type == SDL_MOUSEBUTTONDOWN)
			{
				if (ev.button.button == SDL_BUTTON_LEFT)
				{


					temp.position = vector2d(mx, my);
					
					Ent_draw(&temp);
					//temp.position = vector2d(pressed++, pressed++);



				}
				else if (ev.button.button == SDL_BUTTON_RIGHT)
				{
					temp2.position = vector2d(mx, my);
					Ent_draw(&temp2);
				}
				

			else if (ev.type == SDL_MOUSEBUTTONUP)
				{

					if (ev.button.button == SDL_BUTTON_LEFT)
					{



						temp.position = vector2d(mx, my);
						Ent_draw(&temp);


					}

					
			}*/
			
			


			
            
            //UI elements last
            gf2d_sprite_draw(
                mouse,
                vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseColor,
                (int)mf);
        
			Ent_draw(&temp);

			if (temp2.position.x + SCAVEMX < temp.position.x || temp2.position.x > temp.position.x + SSBUGX || 
				temp2.position.y + SCAVEMY < temp.position.y || temp2.position.y > temp.position.y + SSBUGY)
			{
				temp2.health - 0;

			}

			else
			{
				mouseColor = vector4d( 255,0,0,200);
				cavemanColor = vector4d(255, 0, 0, 200);

				temp2.health = 0;
			}
			/*
			if (temp2.health <= 0)
			{

				Entity_free(&temp2);
			}*/


			//Bool ifCollide(Entity  self,Sint32 w1, Sint32 h1, Entity *targ, Sint32 w2, Sint32 h2)
		//	{
				//if ((self.position.x + w1) < targ.position.x || (targ.position.x + w2) < self.position.x)

				//	return false;

			//	if ((self.position.y + h1) < targ.position.y || (targ.position.y + h2) < self.position.y)
				//return false;
			//}










			/*
			if (keys[SDL_SCANCODE_LEFT])
			{
				temp2.position.x -= 1;
			}
			
			if (keys[SDL_SCANCODE_RIGHT])
			{
				temp2.position.x += 1;
			}
			if (keys[SDL_SCANCODE_UP])
			{
				temp2.position.y -= 1;
			}
			if (keys[SDL_SCANCODE_DOWN])
			{
				temp2.position.y += 1;
			}

			/*
			gf2d_sprite_draw(
				spacebug,
				vector2d(200, 200),
				&temp.scale,
				&temp.scaleCenter,
				NULL,
				NULL,
				NULL,
				temp.frame);
			*/
			
		gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
		if (keys[SDL_SCANCODE_ESCAPE]) { done = 1; pressed = 0; } // exit condition
        slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());
    }
    slog("---==== END ====---");
    return 0;

}
/*eol@eof*/
