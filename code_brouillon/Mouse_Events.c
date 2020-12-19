void Mouse_Events(SDL_Renderer *renderer);
//JAY

void Mouse_Events(SDL_Renderer *renderer){
	  
	SDL_bool game = SDL_TRUE;
	int posX, posY;
	
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
				 SDL_Log("Replay %d ; %d", posX, posY);
				 break; 
				}
				
			if(posX >= 705 && posX <= 785 && posY >= 471 && posY <= 550)  {		
				SDL_Log("VALIDE %d ; %d", posX, posY);
				 break; 
			}
			
			if(posX >= 705 && posX <= 790 && posY >= 205 && posY <= 250) {
				
				SDL_Log("789 %d ; %d", posX, posY);
				 break; 
			}
			
			if(posX >= 705 && posX <= 785 && posY >= 251 && posY <= 290) {
				
				SDL_Log("777 %d ; %d", posX, posY);
				 break; 
			}
	
		
			else { SDL_Log("NaN : x = %d ; y = %d ", posX, posY);}
	
			break;
		}
		break;
		}
	}
	
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}
