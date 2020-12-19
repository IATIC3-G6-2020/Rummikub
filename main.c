
/*
    GNU/Linux et MacOS
        > gcc -o bin/executable src/main.c  `sdl2-config --cflags --libs` `pkg-config --cflags --libs SDL2_image`
    Windows
        > gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void SDL_ExitWithError(const char *message);
SDL_Rect SDL_CreationRectangle(SDL_Renderer *renderer, int x, int y, int w, int h);
void SDL_CreationLigne(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
void SDL_CreationTableau(SDL_Renderer *renderer);
void SDL_CreationImage(SDL_Renderer *renderer, SDL_Surface *picture, SDL_Texture *texture, SDL_Rect dest_rect, char *imageName);

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *picture = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect dest_rect;

    int largeur = 800, hauteur = 600;

    //Lancement SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialisation SDL");

    //Création fenêtre
    window = SDL_CreateWindow("RUMMIKUB™", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, largeur, hauteur, 0);

    if(window == NULL)
        SDL_ExitWithError("Creation fenetre echouee");

    /* ---------------------------------------------------------- */

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
    	SDL_Log("ERREUR : Creation rendu echouee %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /* ==================== AJOUT D'IMAGE =================== */

    dest_rect = SDL_CreationRectangle(renderer, 0, 0, 800, 600);
    SDL_CreationImage(renderer, picture, texture, dest_rect, "CouleurArrierePlan.jpg");

    dest_rect = SDL_CreationRectangle(renderer, 10, 20, 100, 100);
    SDL_CreationImage(renderer, picture, texture, dest_rect, "Femme.png");

    dest_rect = SDL_CreationRectangle(renderer, 10, 250, 100, 100);
    SDL_CreationImage(renderer, picture, texture, dest_rect, "Homme.png");

    dest_rect = SDL_CreationRectangle(renderer, 10, 490, 100, 100);
    SDL_CreationImage(renderer, picture, texture, dest_rect, "Femme.png");

    dest_rect = SDL_CreationRectangle(renderer, 705, 470, 80, 80);
    SDL_CreationImage(renderer, picture, texture, dest_rect, "Valider_combinaison.png");

    dest_rect = SDL_CreationRectangle(renderer, 705, 390, 80, 80);
    SDL_CreationImage(renderer, picture, texture, dest_rect, "Reprendre_combinaison.png");

    dest_rect = SDL_CreationRectangle(renderer, 200, 450, 400, 200);
    SDL_CreationImage(renderer, picture, texture, dest_rect, "Chevalet.jpg");

    dest_rect = SDL_CreationRectangle(renderer, 700, 205, 90, 90);
    SDL_CreationImage(renderer, picture, texture, dest_rect, "Triage.png");

    /* ========================================================== */

    if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0)
	    SDL_ExitWithError("Impossible de charger la couleur pour le menu");

	
	
	/*SDL_CreationRectangle(renderer, 700, 200, 90, 100);
	SDL_CreationRectangle(renderer, 700, 380,90, 180);
	SDL_CreationRectangle(renderer, 200, 450, 400, 150);
	SDL_CreationRectangle(renderer, 10, 20, 100, 100);
	SDL_CreationRectangle(renderer, 10, ((hauteur/2) - 50), 100, 100);
	SDL_CreationRectangle(renderer, 10, (hauteur - 110), 100, 100);*/

	

	SDL_CreationTableau(renderer);

	

    /* ========================================================== */

    SDL_RenderPresent(renderer);
     
    while(1)
    	SDL_Delay(1000);
    /* ---------------------------------------------------------- */

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

SDL_Rect SDL_CreationRectangle(SDL_Renderer *renderer, int x, int y, int w, int h)
{
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;

	if (SDL_RenderDrawRect(renderer, &rectangle) != 0)
		SDL_ExitWithError("Impossible de dessiner un rectangle");
	return rectangle;
}

void SDL_CreationLigne(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
{
	if (SDL_RenderDrawLine(renderer, x1, y1, x2, y2) != 0)
		SDL_ExitWithError("Impossible de dessiner une ligne"); 
}

void SDL_CreationTableau(SDL_Renderer *renderer)
{
	SDL_CreationRectangle(renderer, 150, 20, 520, 400);
	for (int i = 20; i < 530; i+=40)
	{
		if (i < 420)
			SDL_CreationLigne(renderer, 150, i, 670, i);
		SDL_CreationLigne(renderer, (130 + i), 20, (130 + i), 420);
	}
}


void SDL_CreationImage(SDL_Renderer *renderer, SDL_Surface *picture, SDL_Texture *texture, SDL_Rect dest_rect, char *imageName)
{
	char path[100] = "src/";
	strcat(path, imageName);

	printf("%s\n", path);
	picture = IMG_Load(path);
	if(picture == NULL)
	{
	    printf("HOUSSAM Erreur de chargement de l'image : %s\n",SDL_GetError());
	   SDL_ExitWithError("Erreur de chargement de l'image"); 
	}
	

	texture = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_FreeSurface(picture);
	if (texture == NULL)
	{
		printf("Erreur de chargement de l'image : %s",SDL_GetError());
	    SDL_ExitWithError("Erreur de chargement de l'image"); 
	}

	if (SDL_QueryTexture(texture, NULL, NULL, NULL, NULL) != 0)
	{
		printf("Erreur de chargement de l'image : %s",SDL_GetError());
	    SDL_ExitWithError("Erreur de chargement de l'image"); 
	}

	if (SDL_RenderCopy(renderer, texture, NULL, &dest_rect) != 0)
	{
		printf("Erreur de copie de l'image : %s",SDL_GetError());
	    SDL_ExitWithError("Erreur de chargement de l'image"); 
	}
}
