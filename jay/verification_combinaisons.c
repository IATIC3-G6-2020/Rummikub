//main.c 

if(posX >= 705 && posX <= 785 && posY >= 471 && posY <= 550)  {	
	bool test = verification_combinaisons(plateau);
	if(test == true){
		SDL_Log("BON pos: %d ; %d", posX, posY);
		break;
		}
		else{
		SDL_Log("nnnnn");
		}
		break; 
		}
	
//moha.h

int vi;		//variables globales juste en dessous de typedef enum
int vj;

bool verification_combinaisons(TUILE plateau[13][10]);
bool verification_combinaisons789(TUILE plateau[13][10], int i, int j);
bool verification_combinaisons777(TUILE plateau[13][10], int i, int j);
	
		
//moha.c

bool verification_combinaisons(TUILE plateau[13][10]){
	vi = 0, vj = 0;
	bool a;
	a = false;
	for(vi=0; vi<10; vi++){
		for (vj=0; vj<13; vj++){
			if (plateau[vj][vi].typeTuile != VIDE){
				if(verification_combinaisons789(plateau, vi, vj)){ 
					a = true; 
					continue;
				}
				else if(verification_combinaisons777(plateau, vi, vj)){ 
					SDL_Log("777");
					a = true; continue;}
				else{return false;} 
			}
	}
}
return a;
}
bool verification_combinaisons789(TUILE plateau[13][10], int i, int j){
	int total=0, index_debut = j; 
	for (j=j; j<13; j++){
		if(plateau[index_debut+1][i].typeTuile == VIDE || plateau[index_debut+2][i].typeTuile == VIDE){return false;}	
		if(plateau[index_debut+1][i].couleurTuile != plateau[index_debut+1][i].couleurTuile || plateau[index_debut+2][i].couleurTuile != plateau[index_debut+1][i].couleurTuile){return false;}	
		else if(plateau[j][i].typeTuile == VIDE){break;}
		if(plateau[j+1][i].typeTuile == NON_VIDE){
			//if(plateau[j+1][i].chiffre == 0 || plateau[j][i].chiffre ==0){total=1;break;} //joker
			total = plateau[j+1][i].chiffre - plateau[j][i].chiffre; 
			
			if(total != 1){
				return false;
			}
		}
	}
	vi = i;
	vj = j;
	if(total==1){return true;}
	else{return false;}
}


bool verification_combinaisons777(TUILE plateau[13][10], int i, int j){    
	int total = 1, index_debut = j;
	for (j=j; j<13; j++){
		if(plateau[index_debut+1][i].typeTuile == VIDE || plateau[index_debut+2][i].typeTuile == VIDE){
			return false;
			}	
		else if(plateau[j][i].typeTuile == VIDE){
			break;
			}
		if(plateau[j+1][i].typeTuile == NON_VIDE){
			total=0;
			//if(plateau[j+1][i].chiffre == 0 || plateau[j][i].chiffre ==0){total=0;break;} //joker
			total = 1 + plateau[j+1][i].chiffre - plateau[j][i].chiffre; 
			
			if(total != 1){
				return false;
			}
		}
	}
	vi = i;
	vj = j;
	if(total==1){return true;}
	else{return false;}
}
