/* screen.c -*-c-*-
 * Screen/Window handler.
 *
 * "THE BEER-WARE LICENCE" (Revision 42):
 * See the file LICENSE.md for details */

#include "screen.h"

SDL_Surface *screenInit(
    uint16_t width, uint16_t height, uint8_t fullscreen,
    const char *title)
{
    SDL_Surface *screen;

    if (-1 == SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Couldn't initialise SDL: %s\n", SDL_GetError());
        return NULL;
    }

    uint32_t flags = SDL_SWSURFACE;
    if (1 == fullscreen)
        flags = SDL_SWSURFACE | SDL_FULLSCREEN;

    screen = SDL_SetVideoMode(width, height, 16, flags);
    if (NULL == screen)
    {
        fprintf(stderr, "Couldn't set video mode: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_WM_SetCaption(title, NULL);

    return screen;
}

void screenTerminate()
{
    SDL_Quit();
}

int8_t screenDrawPixel(
    SDL_Surface *surface,
    uint16_t x, uint16_t y,
    uint8_t r, uint8_t g, uint8_t b)
{
    if (SDL_MUSTLOCK(surface))
        if (-1 == SDL_LockSurface(surface))
        {
            fprintf(stderr, "Couldn't lock surface: %s\n", SDL_GetError());
            return -1;
        }

    if (SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);

    uint16_t *bufp;
    bufp = (uint16_t *)surface->pixels + y * surface->pitch / 2 + x;
    *bufp = SDL_MapRGB(surface->format, r, g, b);

    return 0;
}
