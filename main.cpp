#include <SDL.h>
#include <iostream>


//ablak középpontja, etolva a rect-ekhez
const int rect_midX = 300;
const int rect_midY = 200;

//max elmozdulás konstansok az ablak közepéhez viszonyítva
const int maxX = 400 + 30;
const int minX = 400 - 30;
const int maxY = 300 + 30;
const int minY = 300 - 30;



int main( int argc, char* args[] )
{
	atexit([] {
			std::cout << "Press a key to exit the application..." << std::endl;
			std::cin.get();
		});


	if ( SDL_Init( SDL_INIT_VIDEO ) == -1 )
	{
		std::cout << "[SDL initialization] Error during the SDL initialization: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = nullptr;
    win = SDL_CreateWindow( "Hello SDL!",				// az ablak fejléce
							100,						// az ablak bal-felsõ sarkának kezdeti X koordinátája
							100,						// az ablak bal-felsõ sarkának kezdeti Y koordinátája
							800,						// ablak szélessége
							600,						// és magassága
							SDL_WINDOW_SHOWN);			// megjelenítési tulajdonságok

    if (win == nullptr)
	{
		std::cout << "[Window creation] Error during the creation of an SDL window: " << SDL_GetError() << std::endl;
        return 1;
    }


    SDL_Renderer *ren = nullptr;
    ren = SDL_CreateRenderer(	win, // melyik ablakhoz rendeljük hozzá a renderert
								-1,  // melyik indexú renderert inicializáljuka
									 // a -1 a harmadik paraméterben meghatározott igényeinknek megfelelõ elsõ renderelõt jelenti
								SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);	// az igényeink, azaz
																						// hardveresen gyorsított és vsync-et beváró
    if (ren == nullptr)
	{
        std::cout << "[Renderer creation] Error during the creation of an SDL renderer: " << SDL_GetError() << std::endl;
        return 1;
    }



	bool quit = false;
	SDL_Event ev;
	Sint32 mouseX = 0, mouseY = 0;

	while (!quit)
	{
		while ( SDL_PollEvent(&ev) )
		{
			switch (ev.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if ( ev.key.keysym.sym == SDLK_ESCAPE )
					quit = true;
				break;
			case SDL_MOUSEMOTION:
				mouseX = ev.motion.x;
				mouseY = ev.motion.y;
				break;
			case SDL_MOUSEBUTTONUP:
				// egérgomb felengedésének eseménye; a felengedett gomb a ev.button.button -ban található
				// a lehetséges gombok a következõek: SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE, 
				//		SDL_BUTTON_RIGHT, SDL_BUTTON_WHEELUP, SDL_BUTTON_WHEELDOWN
				break;
			}
		}

		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderClear(ren);
	

        SDL_Rect back_rekt;
        SDL_Rect front_rekt;
        front_rekt.w = back_rekt.w = 200;
        front_rekt.h = back_rekt.h = 200;


		if(mouseX > maxX)	mouseX = maxX;
		if(mouseX < minX)	mouseX = minX;
		if(mouseY > maxY)	mouseY = maxY;
		if(mouseY < minY)	mouseY = minY;


		front_rekt.x = mouseX - 100;
		front_rekt.y = mouseY - 100;

		back_rekt.x = rect_midX + (rect_midX - front_rekt.x);
		back_rekt.y = rect_midY + (rect_midY - front_rekt.y);




        SDL_SetRenderDrawColor(ren, 0, 50, 100, 255);
        SDL_RenderDrawRect(ren, &back_rekt);
        SDL_RenderDrawRect(ren, &front_rekt);
		SDL_RenderDrawLine(ren, front_rekt.x, front_rekt.y, back_rekt.x, back_rekt.y);
		SDL_RenderDrawLine(ren, front_rekt.x + 200, front_rekt.y + 200, back_rekt.x + 200, back_rekt.y + 200);
		SDL_RenderDrawLine(ren, front_rekt.x + 200, front_rekt.y, back_rekt.x + 200, back_rekt.y);
		SDL_RenderDrawLine(ren, front_rekt.x, front_rekt.y + 200, back_rekt.x, back_rekt.y + 200);

        
		SDL_RenderPresent(ren);
	}


	SDL_DestroyRenderer( ren );
	SDL_DestroyWindow( win );

	SDL_Quit();

	return 0;
}
