#include "graphic.h"

void SDL_AfficheTuile_plateau(SDL_Renderer *renderer, TUILE plateau[13][10]){

    SDL_Init(SDL_INIT_VIDEO);
    if(TTF_Init() == -1){
        fprintf(stderr, "Erreur TTF_INIT : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    TTF_Font* verdana = TTF_OpenFont("src/verdana.ttf", 20);
    if (verdana == NULL){
        fprintf(stderr, "error: pas de font\n");
        exit(EXIT_FAILURE);
    }
    SDL_Color red = {255, 0, 0, 0};
    SDL_Color blue = {0, 0, 255, 0};
    SDL_Color gold = {255, 200, 0, 0};
    SDL_Color black = {0, 0, 0, 0};
    SDL_Color white = {255, 255 ,255, 0};
    for(int i=0; i<13; i++){
        for(int j=0; j<10; j++){
            if(plateau[i][j].typeTuile == NON_VIDE){
                //printf("Il y a une tuile non vide dans le plateau à %d,%d\n",i,j);
                SDL_CreationRectangleRempli(renderer,155+i*40,20+j*40,30,40);
                SDL_Surface* surfaceMessage = NULL ;
                char buf[16];
                if(plateau[i][j].chiffre == 0){
                    sprintf(buf,"J");
                    //printf("c'est le joker");
                }else{
                    sprintf(buf,"%d",plateau[i][j].chiffre);
                    //printf("C'est le chiffre %d\n",plateau[i][j].chiffre);
                }
                switch (plateau[i][j].couleurTuile){
                    case c1:
                        //printf("De couleur rouge\n\n");
                        surfaceMessage = TTF_RenderText_Solid(verdana, buf, red);
                        break;
                    case c2:
                        //printf("De couleur bleu\n\n");
                        surfaceMessage = TTF_RenderText_Solid(verdana, buf, blue);
                        break;
                    case c3:
                        //printf("De couleur dorée\n\n");
                        surfaceMessage = TTF_RenderText_Solid(verdana, buf, gold);
                        break;
                    case c4:
                        //printf("De couleur noir\n\n");
                        surfaceMessage = TTF_RenderText_Solid(verdana, buf, black);
                        break;
                    case c0:
                        //printf("De couleur noir\n\n");
                        surfaceMessage = TTF_RenderText_Solid(verdana, buf, white);
                        break;
                }
                SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
                SDL_FreeSurface(surfaceMessage);
                SDL_Rect Message_rect;
                Message_rect.x = 163+i*40; //150+13+0*40
                Message_rect.y = 30+j*40;  //20+10+0*40
                Message_rect.w = 16;
                Message_rect.h = 30;
                SDL_RenderCopy(renderer,Message,NULL,&Message_rect);
                SDL_RenderPresent(renderer);
                SDL_DestroyTexture(Message);
            }
        }
    }
    TTF_CloseFont(verdana);
}

void SDL_AfficheTuile_chevalet(SDL_Renderer *renderer, TUILE chevalet[10][3]){
    SDL_Init(SDL_INIT_VIDEO);
    if(TTF_Init() == -1){
        fprintf(stderr, "Erreur TTF_INIT : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    TTF_Font* verdana = TTF_OpenFont("src/verdana.ttf", 20);
    if (verdana == NULL){
        fprintf(stderr, "error: pas de font\n");
        exit(EXIT_FAILURE);
    }
    SDL_Color red = {255, 0, 0, 0};
    SDL_Color blue = {0, 0, 255, 0};
    SDL_Color gold = {255, 200, 0, 0};
    SDL_Color black = {0, 0, 0, 0};
    SDL_Color white = {255, 255 ,255, 0};
    for(int i=0; i<10; i++){
        for(int j=0; j<3; j++){
            if(chevalet[i][j].typeTuile == NON_VIDE){
                //printf("Il y a une tuile non vide dans le chevalet à %d,%d\n",i,j);
                SDL_CreationRectangleRempli(renderer,205+i*40,450+j*40,30,40);
                SDL_Surface* surfaceMessage = NULL ;
                char buf[16];
                if(chevalet[i][j].chiffre == 0){
                    sprintf(buf,"J");
                    //printf("c'est le joker");
                }else{
                    sprintf(buf,"%d",chevalet[i][j].chiffre);
                    //printf("C'est le chiffre %d\n",chevalet[i][j].chiffre);
                }
                switch (chevalet[i][j].couleurTuile){
                    case c1:
                        //printf("De couleur rouge\n\n");
                        surfaceMessage = TTF_RenderText_Solid(verdana, buf, red);
                        break;
                    case c2:
                        //printf("De couleur bleu\n\n");
                        surfaceMessage = TTF_RenderText_Solid(verdana, buf, blue);
                        break;
                    case c3:
                        //printf("De couleur dorée\n\n");
                        surfaceMessage = TTF_RenderText_Solid(verdana, buf, gold);
                        break;
                    case c4:
                        //printf("De couleur noir\n\n");
                        surfaceMessage = TTF_RenderText_Solid(verdana, buf, black);
                        break;
                    case c0:
                        //printf("De couleur noir\n\n");
                        surfaceMessage = TTF_RenderText_Solid(verdana, buf, white);
                        break;
                }
                SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
                SDL_FreeSurface(surfaceMessage);
                SDL_Rect Message_rect;
                Message_rect.x = 213+i*40; //150+13+0*40
                Message_rect.y = 460+j*40;  //20+10+0*40
                Message_rect.w = 16;
                Message_rect.h = 30;
                SDL_RenderCopy(renderer,Message,NULL,&Message_rect);
                SDL_RenderPresent(renderer);
                SDL_DestroyTexture(Message);
            }
        }
    }
    TTF_CloseFont(verdana);
}

void SDL_ExitWithError(const char *message){
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

SDL_Rect SDL_CreationRectangle(SDL_Renderer *renderer, int x, int y, int w, int h){
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
	if (SDL_RenderDrawRect(renderer, &rectangle) != 0)
		SDL_ExitWithError("Impossible de dessiner un rectangle");
	return rectangle;
}

SDL_Rect SDL_CreationRectangleRempli(SDL_Renderer *renderer, int x, int y, int w, int h){
	SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = w;
	rectangle.h = h;
	if (SDL_RenderFillRect(renderer, &rectangle) != 0)
		SDL_ExitWithError("Impossible de dessiner un rectangle");
	return rectangle;
}

void SDL_CreationLigne(SDL_Renderer *renderer, int x1, int y1, int x2, int y2){
	if (SDL_RenderDrawLine(renderer, x1, y1, x2, y2) != 0)
		SDL_ExitWithError("Impossible de dessiner une ligne"); 
}

void SDL_CreationTableau(SDL_Renderer *renderer, int x, int y, int w, int h){
	SDL_CreationRectangle(renderer, x, y, w, h);
	for (int i = y; i < y+h; i+=40){	
		SDL_CreationLigne(renderer, x, i, x+w, i);	
	}
    for (int i = x; i < x+w; i+=40){
        SDL_CreationLigne(renderer, i, y, i, y+h);
    }
}

void SDL_CreationImage(SDL_Renderer *renderer, SDL_Surface *picture, SDL_Texture *texture, SDL_Rect dest_rect, char *imageName){
	char path[100] = "src/";
	strcat(path, imageName);
	//printf("%s\n", path);
	picture = IMG_Load(path);
	if(picture == NULL){
	    printf("Erreur de chargement de l'image : %s\n",SDL_GetError());
	   SDL_ExitWithError("Erreur de chargement de l'image"); 
	}
	texture = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_FreeSurface(picture);
	if (texture == NULL){
		printf("Erreur de chargement de l'image : %s",SDL_GetError());
	    SDL_ExitWithError("Erreur de chargement de l'image"); 
	}
	if (SDL_QueryTexture(texture, NULL, NULL, NULL, NULL) != 0){
		printf("Erreur de chargement de l'image : %s",SDL_GetError());
	    SDL_ExitWithError("Erreur de chargement de l'image"); 
	}
	if (SDL_RenderCopy(renderer, texture, NULL, &dest_rect) != 0){
		printf("Erreur de copie de l'image : %s",SDL_GetError());
	    SDL_ExitWithError("Erreur de chargement de l'image"); 
	}
}

void SDL_Update_window(SDL_Renderer *renderer,TUILE plateau[13][10], TUILE chevalet[10][3]){
    SDL_Surface *picture = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect dest_rect;

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
    dest_rect = SDL_CreationRectangle(renderer,780,0,20,20);
    SDL_CreationImage(renderer, picture, texture, dest_rect, "Supprimer_combinaison.png");

    /* ====================AFFICHE TABLEAU======================= */

    if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE) != 0)
	   SDL_ExitWithError("Impossible de charger la couleur pour le menu");
    SDL_CreationTableau(renderer,150, 20, 520, 400);
    SDL_CreationTableau(renderer,200, 450, 400, 120);
    SDL_RenderPresent(renderer);
    SDL_AfficheTuile_plateau(renderer, plateau);
    SDL_AfficheTuile_chevalet(renderer, chevalet);

}

void SDL_AfficheSelectonChevalet(SDL_Renderer *renderer, int ncc, int ncl, TUILE selectedtuile){
    SDL_Init(SDL_INIT_VIDEO);
    if(TTF_Init() == -1){
        fprintf(stderr, "Erreur TTF_INIT : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    TTF_Font* verdana = TTF_OpenFont("src/verdana.ttf", 20);
    if (verdana == NULL){
        fprintf(stderr, "error: pas de font\n");
        exit(EXIT_FAILURE);
    }
    SDL_Color red = {255, 0, 0, 0};
    SDL_Color blue = {0, 0, 255, 0};
    SDL_Color gold = {255, 200, 0, 0};
    SDL_Color black = {0, 0, 0, 0};
    SDL_Color white = {255, 255 ,255, 0};
    printf("Il y a une tuile non vide dans le chevalet à %d,%d\n",ncl,ncc);
    SDL_CreationRectangleRempli(renderer,205+ncl*40,440+ncc*40,30,40);
    SDL_Surface* surfaceMessage = NULL ;
    char buf[16];
    sprintf(buf,"%d",selectedtuile.chiffre);
    printf("C'est le chiffre %d\n",selectedtuile.chiffre);
    switch (selectedtuile.couleurTuile){
        case c1:
            printf("De couleur rouge\n\n");
            surfaceMessage = TTF_RenderText_Solid(verdana, buf, red);
            break;
        case c2:
            printf("De couleur bleu\n\n");
            surfaceMessage = TTF_RenderText_Solid(verdana, buf, blue);
            break;
        case c3:
            printf("De couleur dorée\n\n");
            surfaceMessage = TTF_RenderText_Solid(verdana, buf, gold);
            break;
        case c4:
            printf("De couleur noir\n\n");
            surfaceMessage = TTF_RenderText_Solid(verdana, buf, black);
            break;
        case c0:
                    //printf("De couleur noir\n\n");
                    surfaceMessage = TTF_RenderText_Solid(verdana, buf, white);
                    break;
    }
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = 213+ncl*40; //150+13+0*40
    Message_rect.y = 440+ncc*40;  //20+10+0*40
    Message_rect.w = 16;
    Message_rect.h = 30;
    SDL_RenderCopy(renderer,Message,NULL,&Message_rect);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(Message);
}
