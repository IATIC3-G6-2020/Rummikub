#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "moha.h"

typedef enum {clicplateau,clicchevalet,clicstop,clic777,clic789,clicredo,clicvalid} BOUTON;

void SDL_ExitWithError(const char *message);
SDL_Rect SDL_CreationRectangle(SDL_Renderer *renderer, int x, int y, int w, int h);
SDL_Rect SDL_CreationRectangleRempli(SDL_Renderer *renderer, int x, int y, int w, int h);
void SDL_CreationLigne(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);
void SDL_CreationTableau(SDL_Renderer *renderer, int x, int y, int w, int h);
void SDL_CreationImage(SDL_Renderer *renderer, SDL_Surface *picture, SDL_Texture *texture, SDL_Rect dest_rect, char *imageName);
BOUTON Mouse_Events(SDL_Renderer *renderer,TUILE plateau[13][10],TUILE chevalet[10][3], int coords[2]);
void affiche_fin_partie();
void SDL_AfficheTuile_plateau(SDL_Renderer *renderer, TUILE plateau[13][10]);
void SDL_AfficheTuile_chevalet(SDL_Renderer *renderer, TUILE chevalet[10][3]);
void SDL_Update_window(SDL_Renderer *renderer,TUILE plateau[13][10], TUILE chevalet[10][3]);
void SDL_AfficheSelectonChevalet(SDL_Renderer *renderer, int ncc, int ncl, TUILE selectedtuile);
void Change_TuileDeTableau(TUILE *a, TUILE *b);

int main(int argc, char *argv[]){
    /* ==================== INITIALISATION =================== */
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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL){
    	SDL_Log("ERREUR : Creation rendu echouee %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if(TTF_Init() == -1){
        fprintf(stderr, "Erreur TTF_INIT : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    
    /* ====================INIT TABLEAU======================= */

    TUILE plateau[13][10];
    TUILE chevalet[10][3];
    TUILE paquet [56];

    initialisation_plateau(plateau);
    initialisation_chevalet(chevalet);
    
    JOUEUR joueur[4];
    joueur[0].pseudo = "joueur1";
    joueur[0].numero = 0;
    joueur[0].score = 0;
    joueur[1].pseudo = "joueur2";
    joueur[1].numero = 1;
    joueur[1].score = 0;
    joueur[2].pseudo = "joueur3";
    joueur[2].numero = 2;
    joueur[2].score = 0;
    joueur[3].pseudo = "joueur4";
    joueur[3].numero = 3;
    joueur[3].score = 0;
    creation_tuiles(paquet);
    melanger_paquet_tuiles(paquet);
    distribuer_tuiles(&joueur[0], paquet);
    distribuer_tuiles(&joueur[1], paquet);
    distribuer_tuiles(&joueur[2], paquet);
    distribuer_tuiles(&joueur[3], paquet);
    inventaire_en_chevalet(&joueur[0], chevalet);
    /*
    ////////////////////////VERIFICATION FONCTIONNEMENT PIOCHE////////////////////////////
    //verif inventaire//
    printf("inventaire :\n");
    for (int i = 0; i < 30; i++) {
		printf("numero %d couleur %d\n", test.tuiles[i].chiffre, test.tuiles[i].couleurTuile);
	}
	printf("\n____________________________________\n");
    ////////////////////

	piocher_tuile(&test,paquet);

    //verif inventaire après pioche//
	printf("inventaire :\n");
	for (int i = 0; i < 30; i++) {
		printf("numero %d couleur %d\n", test.tuiles[i].chiffre, test.tuiles[i].couleurTuile);
	}
    //////////////////////////////////

	inventaire_en_chevalet(&test, chevalet);

    //verif paquet de carte//
	printf("\n____________________________________\n");
	printf("paquet de carte :\n");
	for (int i = 0; i < 56; i++) {
		printf("numero %d couleur %d\n", paquet[i].chiffre, paquet[i].couleurTuile);
	}
    ////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    */
    SDL_Update_window(renderer, plateau, chevalet);
    SDL_RenderPresent(renderer);
    SDL_Delay(0);
	printf("-------------------------------------------------\n");
    int coord[2]={0,0};
    BOUTON tableau = -1;
    int tuile_posee = 0;
    TUILE selectedtuile[30];
    int placement[30][4];
    int tourjoueur = 0;

    /* ====================MOUSE EVENT======================= */
    while(tableau != clicstop){
        printf("\npremiere mouse event\n");
        tableau = Mouse_Events(renderer,plateau,chevalet,coord);
        if(tableau == clicplateau){
            //printf("returned coords x:%d,y:%d -> plateau\n",coord[0],coord[1]);
            int ncl = (coord[0]-150)/40;
            int ncc = (coord[1]-20)/40;
            //printf("case [%d][%d] of plateau\n",ncl,ncc);
        }
        else if(tableau == clicchevalet){
            //printf("returned coords x:%d,y:%d -> chevalet\n",coord[0],coord[1]);
            int ncl = (coord[0]-200)/40;
            int ncc = (coord[1]-450)/40;
            //printf("case [%d][%d] of chevalet\n",ncl,ncc);
            if(chevalet[ncl][ncc].typeTuile == NON_VIDE){
                //printf("non_vide");
                Change_TuileDeTableau(&chevalet[ncl][ncc],&selectedtuile[tuile_posee]);

                joueur[tourjoueur].tuiles[ncc*10+ncl].chiffre = -1;
                joueur[tourjoueur].tuiles[ncc*10+ncl].couleurTuile = VIDE;
                joueur[tourjoueur].tuiles[ncc*10+ncl].typeTuile = VIDE;
                placement[tuile_posee][1] = ncl;
                placement[tuile_posee][2] = ncc;

                SDL_Update_window(renderer, plateau, chevalet);
                SDL_AfficheSelectonChevalet(renderer, ncc, ncl, selectedtuile[tuile_posee]);
                SDL_RenderPresent(renderer);
                SDL_Delay(0);
                ncc = 0;
                ncl = 0;
                int coord2[2]={0,0};
                BOUTON tableau2 = -1;
                int ok = 0;
                while (!ok){
                    printf("\ndeuxieme mouse event\n");
                    tableau2 = Mouse_Events(renderer,plateau,chevalet,coord2);
                    if(tableau2 == clicplateau){
                        int ncl2 = (coord2[0]-150)/40;
                        int ncc2 = (coord2[1]-20)/40;
                        if(plateau[ncl2][ncc2].typeTuile == VIDE){
                            ok = 1;
                            plateau[ncl2][ncc2].chiffre = selectedtuile[tuile_posee].chiffre;
                            plateau[ncl2][ncc2].couleurTuile = selectedtuile[tuile_posee].couleurTuile;
                            plateau[ncl2][ncc2].typeTuile = selectedtuile[tuile_posee].typeTuile;
                            placement[tuile_posee][3] = ncl2;
                            placement[tuile_posee][4] = ncc2;
                            tuile_posee = tuile_posee +1;
                        }
                    }else if(tableau2 == clicchevalet){
                        int ncl2 = (coord2[0]-200)/40;
                        int ncc2 = (coord2[1]-450)/40;
                        if(chevalet[ncl2][ncc2].typeTuile == VIDE && ncl == ncl2 && ncc == ncc2){
                            ok = 1;
                            joueur[tourjoueur].tuiles[ncc2*10+ncl2].chiffre = selectedtuile[tuile_posee].chiffre;
                            joueur[tourjoueur].tuiles[ncc2*10+ncl2].couleurTuile = selectedtuile[tuile_posee].couleurTuile;
                            joueur[tourjoueur].tuiles[ncc2*10+ncl2].typeTuile = selectedtuile[tuile_posee].typeTuile;
                            Change_TuileDeTableau(&selectedtuile[tuile_posee],&chevalet[ncl2][ncc2]);
                        }
                    }else if(tableau2 == clicstop){
                        tableau = clicstop;
                        ok = 1;
                    }
                }
                //printf("\n\nTuiles posées : %d tuiles\n\n",tuile_posee);
                ok = 0;
                SDL_Update_window(renderer, plateau, chevalet);
                SDL_RenderPresent(renderer);
                SDL_Delay(0);
            }
            SDL_Update_window(renderer, plateau, chevalet);
        }
        else if(tableau == clicstop){
            //printf("returned coords x:%d,y:%d -> stop\n");
            //printf("\n\nLE PROGRAMME S'ARETE\n\n");
        }
        else if (tableau == clic777){
            //printf("returned coords x:%d,y:%d -> tri 777\n");
            initialisation_chevalet(chevalet);
            tri_777(&joueur[tourjoueur]);
            inventaire_en_chevalet(&joueur[tourjoueur], chevalet);
            SDL_Update_window(renderer, plateau, chevalet);
        }
        else if (tableau == clic789){
            //printf("returned coords x:%d,y:%d -> tri 789\n");
            initialisation_chevalet(chevalet);
            tri_789(&joueur[tourjoueur]);
            inventaire_en_chevalet(&joueur[tourjoueur], chevalet);
            SDL_Update_window(renderer, plateau, chevalet);
        }
        else if (tableau == clicredo){
            //printf("returned coords x:%d,y:%d -> redo\n");
            int xcoord, ycoord;
            tuile_posee = tuile_posee -1;
            while(tuile_posee != -1){
                //printf("\n\ntuile posée a retirer : %d tuile(s)\n\n",tuile_posee+1);
                xcoord = placement[tuile_posee][3];
                ycoord = placement[tuile_posee][4];
                //printf("\n\ncoords du plateau a vider : x:%d y:%d\n\n",xcoord,ycoord);
                plateau[xcoord][ycoord].chiffre = -1;
                plateau[xcoord][ycoord].couleurTuile = VIDE;
                plateau[xcoord][ycoord].typeTuile = VIDE;
                //printf("\n\ntuile retirée du plateau\n\n");
                int xcoord = placement[tuile_posee][1];
                int ycoord = placement[tuile_posee][2];                
                chevalet[xcoord][ycoord].chiffre = selectedtuile[tuile_posee].chiffre;
                chevalet[xcoord][ycoord].couleurTuile = selectedtuile[tuile_posee].couleurTuile;
                chevalet[xcoord][ycoord].typeTuile = selectedtuile[tuile_posee].typeTuile;
                joueur[tourjoueur].tuiles[xcoord*10+ycoord].chiffre = selectedtuile[tuile_posee].chiffre;
                joueur[tourjoueur].tuiles[xcoord*10+ycoord].chiffre = selectedtuile[tuile_posee].couleurTuile;
                joueur[tourjoueur].tuiles[xcoord*10+ycoord].chiffre = selectedtuile[tuile_posee].typeTuile;
                //printf("\n\ntuile reposé dans le chevalet\n\n");
                selectedtuile[tuile_posee].chiffre = -1;
                selectedtuile[tuile_posee].couleurTuile = VIDE;
                selectedtuile[tuile_posee].typeTuile = VIDE;
                //printf("\n\nliste selectedtuile vidée\n\n");
                tuile_posee = tuile_posee -1;
            }
            //printf("fin redo");
            SDL_Update_window(renderer, plateau, chevalet);
        }
        else if (tableau == clicvalid){
            if(tuile_posee == 0){
	            piocher_tuile(&joueur[tourjoueur],paquet);
	            inventaire_en_chevalet(&joueur[tourjoueur], chevalet);
                SDL_Update_window(renderer, plateau, chevalet);
            }else{
                tuile_posee = 0;
            }
            printf("sleep for 2sec, changement de tour\n");
            sleep(2);
            if (tourjoueur == 3){
                tourjoueur = 0;
            }else{    
                tourjoueur = tourjoueur +1;
            }
	        inventaire_en_chevalet(&joueur[tourjoueur], chevalet);
            SDL_Update_window(renderer, plateau, chevalet);
            printf("\nau tour de joueur %d\n",tourjoueur+1);
        }
        else{
            //printf("returned coords x:%d,y:%d -> nothing\n");
        }
    }

    /* ====================FERMETURE======================= */    
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    
    return EXIT_SUCCESS;
}

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
    //SDL_Color white = {255, 255 ,255, 0};
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
    //SDL_Color white = {255, 255 ,255, 0};
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

BOUTON Mouse_Events(SDL_Renderer *renderer,TUILE plateau[13][10],TUILE chevalet[10][3],int coords[2]){
	SDL_bool game = SDL_TRUE;
	int posX, posY;
    BOUTON bouton = -1;	
	while(game){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT: 	
                    game = SDL_FALSE;
                    break;
                case SDL_MOUSEBUTTONUP: // Click souris relâché
                    SDL_GetMouseState(&posX, &posY);
                    if (posX >= 705 && posX <= 785 && posY >= 390 && posY <= 469) { 
                        bouton = clicredo;	
                        //SDL_Log("Redo %d ; %d", posX, posY);
                        break; 
                    }
                    if(posX >= 705 && posX <= 785 && posY >= 471 && posY <= 550)  {		
                        bouton = clicvalid;
                        //SDL_Log("Valid %d ; %d", posX, posY);
                        break; 
                    }
                    if(posX >= 705 && posX <= 790 && posY >= 205 && posY <= 250) {
                        bouton = clic789;
                        //SDL_Log("789 %d ; %d", posX, posY);
                        break; 
                    }
                    if(posX >= 705 && posX <= 785 && posY >= 251 && posY <= 290) {
                        bouton = clic777;
                        //SDL_Log("777 %d ; %d", posX, posY);
                        break; 

                    }
                    if(posX >= 780 && posX <= 800 && posY >= 0 && posY <= 20) {
                        bouton = clicstop;
                        //SDL_Log("Stop %d ; %d", posX, posY);
                        break; 

                    }
                    if(posX >= 150 && posX <= 670 && posY >= 20 && posY <= 420){
                        bouton = clicplateau;
                        //SDL_Log("Plateau %d ; %d", posX, posY);
                        int ncl = (posX-150)/40;
                        int ncc = (posY-20)/40;
                        //SDL_Log("case %d ; %d", ncl, ncc);
                        if(plateau[ncl][ncc].typeTuile == NON_VIDE){
                            //printf("c'est non vide\n");
                            //printf("C'est le chiffre %d\n",plateau[ncl][ncc].chiffre);
                            switch (plateau[ncl][ncc].couleurTuile){
                            case c1:
                                //printf("De couleur rouge\n\n");
                                break;
                            case c2:
                                //printf("De couleur bleu\n\n");
                                break;
                            case c3:
                                //printf("De couleur dorée\n\n");
                                break;
                            case c4:
                                //printf("De couleur noir\n\n");
                                break;
                            }
                        }else{
                            //printf("\n");
                        }
                        break;
                    }
                    if(posX >= 200 && posX <= 600 && posY >= 450 && posY <= 570){
                        bouton = clicchevalet;
                        //SDL_Log("Chevalet %d ; %d", posX, posY);
                        int ncl = (posX-200)/40;
                        int ncc = (posY-450)/40;
                        //SDL_Log("case %d ; %d", ncl, ncc);
                        if(chevalet[ncl][ncc].typeTuile == NON_VIDE){
                            //printf("c'est non vide\n");
                            //printf("C'est le chiffre %d\n",chevalet[ncl][ncc].chiffre);
                            switch (chevalet[ncl][ncc].couleurTuile){
                            case c1:
                                //printf("De couleur rouge\n\n");
                                break;
                            case c2:
                                //printf("De couleur bleu\n\n");
                                break;
                            case c3:
                                //printf("De couleur dorée\n\n");
                                break;
                            case c4:
                                //printf("De couleur noir\n\n");
                                break;
                            }
                        }else{
                            //printf("\n");
                        }
                        break;
                    }

                    else{ 
                        //SDL_Log("NaN : x = %d ; y = %d ", posX, posY);
                    }
                    break;
            }
            break;
            if(bouton != -1){
                break;
            }
        }
        if(bouton != -1){
                break;
        }
	}
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    coords[0] = posX;
    coords[1] = posY;
    //printf("coords function x:%d,y:%d\n\n",coords[0],coords[1]);
    return bouton;
}

void affiche_fin_partie(JOUEUR *joueurs){
    int position_clic_x, position_clic_y;
    int quit = 0;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("Game Over",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface * image = NULL;
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect dest_rect;
    dest_rect = SDL_CreationRectangle(renderer, 0, -70, 500, 500);
    SDL_Surface * image_rep = NULL;
    SDL_Texture * texture_rep = SDL_CreateTextureFromSurface(renderer, image_rep);
    SDL_Rect dest_rect_rep;
    //Tester le numero du joueur actuel pour savoir le vainqueur
    joueurs->numero=2;
    if(joueurs->numero==1)
        SDL_CreationImage(renderer, image, texture, dest_rect, "1wins.png");
    if(joueurs->numero==2)
        SDL_CreationImage(renderer, image, texture, dest_rect, "2wins.png");
    if(joueurs->numero==3)
        SDL_CreationImage(renderer, image, texture, dest_rect, "1wins.png");
    if(joueurs->numero==4)
        SDL_CreationImage(renderer, image, texture, dest_rect, "1wins.png");
    //Creation de deux zones cliquables une pour rejouer et l'autre pour quitter
    dest_rect_rep = SDL_CreationRectangle(renderer, 0, 250, 250, 250);
    SDL_CreationImage(renderer, image_rep, texture_rep, dest_rect_rep, "rejouer.png");
    dest_rect_rep = SDL_CreationRectangle(renderer, 250, 250, 250, 250);
    SDL_CreationImage(renderer, image_rep, texture_rep, dest_rect_rep, "quitter.png");
    while (!quit){
        SDL_WaitEvent(&event);
        switch (event.type){
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                position_clic_x = event.button.x;      
                position_clic_y = event.button.y;
                //Tester la position du curseur sur le bouton rejouer
                if(position_clic_x<=250 && position_clic_x>=0 && position_clic_y <= 500 && position_clic_y >=250){
                    quit = 1;
                    SDL_DestroyTexture(texture);    
                    SDL_FreeSurface(image);    
                    SDL_DestroyRenderer(renderer);   
                    SDL_DestroyWindow(window);
                    printf("rejouer");
                }
                //Tester la position du curseur sur le bouton Quitter
                if(position_clic_x<=500 && position_clic_x>=250 && position_clic_y <= 500 && position_clic_y >=250){
                    quit = 1;   //printf("Quitter");
                }
                break;
        }
        SDL_RenderCopy(renderer, texture, NULL, NULL);          
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);        
    SDL_FreeSurface(image);         
    SDL_DestroyRenderer(renderer);          
    SDL_DestroyWindow(window);
    SDL_Quit();
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

void Change_TuileDeTableau(TUILE *a, TUILE *b){
    b->chiffre = a->chiffre;
    b->couleurTuile = a->couleurTuile;
    b->typeTuile = a->typeTuile;
    a->chiffre = -1;
    a->couleurTuile = VIDE;
    a->typeTuile = VIDE;
}

