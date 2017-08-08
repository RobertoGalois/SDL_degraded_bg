#include    <stdlib.h>
#include    <stdio.h>
#include    <SDL/SDL.h>
#include    "deg.h"

void    ev_loop(void)
{
        signed short    bool_continue = 1;
        SDL_Event       ev;

        while (bool_continue)
        {
            SDL_WaitEvent(&ev);
            switch(ev.type)
            {   
                case SDL_QUIT:
                bool_continue = 0;
            }
        }
}

void    check_SDL_Init(SDL_Surface* p_element)
{
        if (p_element == NULL)
        {
            fprintf(stderr, "Impossible de charger le mode vidéo : %s\n",
                    SDL_GetError());
            
            exit(EXIT_FAILURE);
        }
}

void    free_rects(SDL_Surface* p_array[])
{
        for (unsigned short i = 0; i< 256; i++)
            SDL_FreeSurface(p_array[i]);
}

int     main(int argc, char *argv[])
{
        SDL_Surface     *window = NULL;
        SDL_Surface     *rectangle[256];
        SDL_Rect        position;

        position.x = 0;

        /* init sdl */
        SDL_Init(SDL_INIT_VIDEO);

        /* init window */
        window = SDL_SetVideoMode(640, 256, 32, SDL_HWSURFACE);
        check_SDL_Init(window);
        SDL_WM_SetCaption("Ma super fenêtre SDL EN DEGRADED !", NULL);
        SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 
                                                255, 255, 255));
        /* surfaces */
        for (signed short i = 0; i<256; i++)
        {
            position.y = i;
            /* creating surface */
            rectangle[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,
                                                640, 1, 32, 0, 0, 0, 0); 
            /* color surface */
            SDL_FillRect(rectangle[i], NULL, 
                            SDL_MapRGB(window->format, i, i, i));

            /* append surface */
            SDL_BlitSurface(rectangle[i], NULL, window, &position);
        }

        /* update display window */
        SDL_Flip(window);
        /* await */
        ev_loop();

        /* free memory */
        free_rects(rectangle);
        SDL_Quit();

        return EXIT_SUCCESS;
} 
