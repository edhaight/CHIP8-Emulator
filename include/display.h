#ifndef DISPLAY_H
#define DISPLAY_H

#define WINDOW_WIDTH 64
#define WINDOW_HEIGHT 32
#define WINDOW_SCALE 10
#define ON_COLOR 0xFF
#define OFF_COLOR 0x00

struct display
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
};
typedef struct display display;

int setupDisplay(display *display);
void drawDisplay(display *display, unsigned char pixels[WINDOW_WIDTH * WINDOW_HEIGHT]);
void cleanupDisplay(display *display);

#endif
