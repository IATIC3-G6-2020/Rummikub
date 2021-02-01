//main.c

void notifyError(SDL_Renderer *renderer);

// à appeler juste en dessous de SDL_Log("nn tjrs pas") où il y a verification combinaisons et tout ça


notifyError(renderer);


void notifyError(SDL_Renderer *renderer){
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
	SDL_Surface* surfaceMessage = NULL ;
	char buf[32];
	sprintf(buf, "Combinaison non valide");              
	surfaceMessage = TTF_RenderText_Solid(verdana, buf, red);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
	SDL_FreeSurface(surfaceMessage);
	SDL_Rect Message_rect;
	Message_rect.x = 630;
	Message_rect.y = 555; 
	Message_rect.w = 140;
	Message_rect.h = 40;
	SDL_RenderCopy(renderer,Message,NULL,&Message_rect);
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(Message);
    TTF_CloseFont(verdana);

}
