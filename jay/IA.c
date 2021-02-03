bool IA(JOUEUR *joueur, TUILE plateau[13][10]) {		//i = k, j = l
	
	bool opt=true;
	int cpt=0,i,j,k,l;
	SDL_Log("message0");
	if(opt){
		tri_777(joueur);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 9; j+=3) {
				if(joueur->tuiles[j].chiffre + joueur->tuiles[j+1].chiffre + joueur->tuiles[j+2].chiffre == 3*(joueur->tuiles[j].chiffre)){
				  SDL_Log("message S");
					for(k=0; k<10; k++){
						for (l=0; l<13; l++){
							SDL_Log("%d", plateau[l][k].chiffre);
							if(cpt==5){
								SDL_Log("message GOGOGO");
								for(cpt=4; cpt<1; cpt--){
								plateau[l-cpt][k].chiffre = joueur->tuiles[j].chiffre;
								j++;
								}
							SDL_Log("opt");
							opt=false;
							return opt;
							
							}
							else if(plateau[l][k].typeTuile == VIDE){cpt++;}
							else{cpt=0;}
			
						}	
					}
			}
			SDL_Log("1 - nn");
		}
	}
}

else if (opt){

	tri_789(joueur);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 9; j+=3) {
			SDL_Log("message1");
			if(joueur->tuiles[j].chiffre + joueur->tuiles[j+1].chiffre + joueur->tuiles[j+2].chiffre == 3+(3*(joueur->tuiles[j].chiffre))){
				SDL_Log("message S");
					for(k=0; k<10; k++){
						for (l=0; l<13; l++){
							SDL_Log("%d", plateau[l][k].chiffre);
							if(cpt==5){
								SDL_Log("message GOGOGO");
								for(cpt=4; cpt<1; cpt--){
								plateau[l-cpt][k].chiffre = joueur->tuiles[j].chiffre;
								j++;
								}
							SDL_Log("opt");
							opt=false;
							return opt;
							}
							else if(plateau[l][k].typeTuile == VIDE){cpt++;}
							else{cpt=0;}			
						}	
					}
			}
			SDL_Log("1 - nn");
		}
	}
}
return opt;
}
