#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "logic.h"

void SDL_ExitWithError(const char *message);
SDL_Rect SDL_CreationRectangle(SDL_Renderer *renderer, int x, int y, int w, int h);
SDL_Rect SDL_CreationRectangleRempli(SDL_Renderer *renderer, int x, int y, int w, int h);
void SDL_CreationLigne(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
void SDL_CreationTableau(SDL_Renderer *renderer, int x, int y, int w, int h);
void SDL_CreationImage(SDL_Renderer *renderer, SDL_Surface *picture, SDL_Texture *texture, SDL_Rect dest_rect, char *imageName);
void SDL_AfficheTuile_plateau(SDL_Renderer *renderer, TUILE plateau[13][10]);
void SDL_AfficheTuile_chevalet(SDL_Renderer *renderer, TUILE chevalet[10][3]);
void SDL_Update_window(SDL_Renderer *renderer,TUILE plateau[13][10], TUILE chevalet[10][3]);
void SDL_AfficheSelectonChevalet(SDL_Renderer *renderer, int ncc, int ncl, TUILE selectedtuile);
