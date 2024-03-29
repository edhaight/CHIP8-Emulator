#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "display.h"

// https : //github.com/scanlong/c8/blob/master/src/display.c
static int checkDisplayError(char *component, void *pointer)
{
    if (pointer == NULL)
    {
        printf("Could not create %s: %s\n", component, SDL_GetError());
        return -1;
    }
    return 0;
}

int setupDisplay(display *display)
{
    // Try to initialize an SDL video component
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Error initializing SDL: %s\n", SDL_GetError());
        return -1;
    }

    // Instantiate window
    display->window = SDL_CreateWindow("Chip 8 Emu",
                                       SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       WINDOW_WIDTH * WINDOW_SCALE, WINDOW_HEIGHT * WINDOW_SCALE,
                                       SDL_WINDOW_RESIZABLE);
    // Check if window creation failed
    if (checkDisplayError("window", display->window))
    {
        return -1;
    }

    // Instantiate renderer
    display->renderer = SDL_CreateRenderer(display->window, -1, SDL_RENDERER_ACCELERATED);
    // Check if renderer creation failed
    if (checkDisplayError("renderer", display->renderer))
    {
        return -1;
    }

    // Instantiate Texture
    display->texture = SDL_CreateTexture(display->renderer,
                                         SDL_PIXELFORMAT_RGB332, SDL_TEXTUREACCESS_STREAMING,
                                         WINDOW_WIDTH, WINDOW_HEIGHT);
    // Check if texture creation failed
    if (checkDisplayError("texture", display->texture))
    {
        return -1;
    }

    return 0;
}

void drawDisplay(display *display, unsigned char pixels[WINDOW_WIDTH * WINDOW_HEIGHT])
{
    SDL_UpdateTexture(display->texture, NULL, pixels, WINDOW_WIDTH * sizeof(unsigned char));
    SDL_RenderCopy(display->renderer, display->texture, NULL, NULL);
    SDL_RenderPresent(display->renderer);
}

void cleanupDisplay(display *display)
{
    //Clean up
    SDL_DestroyTexture(display->texture);
    SDL_DestroyRenderer(display->renderer);
    SDL_DestroyWindow(display->window);
    SDL_Quit();
}
