moha.h 

#include <stdbool.h>

int vi;
int vj;     //variables globales


main.c 


bool test = verification_combinaisons(plateau);
SDL_Log("boolean : %d", test);
if(test == true){
    SDL_Log("BON pos: %d ; %d", posX, posY);
    break;
}
else{SDL_Log("nnn tjrs pas");}
break; 
						}
------------------------------

moha.c 

bool verification_combinaisons(TUILE plateau[13][10]){
	vi = 0, vj = 0;
	bool a;
	a = false;
	SDL_Log("a(1) = %d", a);
	for(vi=0; vi<10; vi++){
		for (vj=0; vj<13; vj++){
			SDL_Log("-------1-----"); 
			//SDL_Log("typeTuile : %s",plateau[vj][vi].typeTuile);
			if (plateau[vj][vi].typeTuile != VIDE)
			{
				SDL_Log("-------2-----");
				if(verification_combinaisons789(plateau, vi, vj)==true){
					a = true;
					SDL_Log("a(2) = %d", a);
					continue;
				}
				else{return false;} 
			}
	}
//|| verification_combinaisons777(plateau, vi, vj)==true
}

SDL_Log("a3 = %d", a);
return a;
}
bool verification_combinaisons789(TUILE plateau[13][10], int i, int j){
	int total=0, index_debut = j;
	SDL_Log("i  : %d", i);
	for (j=j; j<13; j++){
		SDL_Log("message 1  : val i : %d ; plateau : %d ", i, plateau[j][i].typeTuile);
		if(plateau[index_debut+1][i].typeTuile == VIDE || plateau[index_debut+2][i].typeTuile == VIDE){SDL_Log("message 2  : val i %d", i);return false;}	
		else if(plateau[j][i].typeTuile == VIDE){SDL_Log("message 3");break;}
		if(plateau[j+1][i].typeTuile == NON_VIDE){
			SDL_Log("%d - %d ",  plateau[j+1][i].chiffre, plateau[j][i].chiffre); 
			total = plateau[j+1][i].chiffre - plateau[j][i].chiffre; 
			SDL_Log("total final : %d", total);
			if(total != 1){
				return false;
			}
		}
	}
	SDL_Log("total2 = %d", total);		//+2 = cpt+1 	/ +1 = cpt  / +0 ?
	vi = i;
	vj = j;
	if(total==1){return true;}
	else{return false;}
}

/*
bool verification_combinaisons777(){    

	int total=0, validator=0, disrupt=vi+3;
	vi=0,vj=0;
	for (vi=vi; vi<=13; vi++){
		if(plateau[vj][vi].typeTuile == VIDE && (vi<disrupt){return false;}
		else if(plateau[vj][vi].typeTuile == VIDE){break;}
		else{
			validator=validator + plateau[vj][vi].chiffre;
		}
		total=total+vi;
	}
	if(total * 3 == validator || total * 4 == validator){return true;}
	else{return false;}

}*/
