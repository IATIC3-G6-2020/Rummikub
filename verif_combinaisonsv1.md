moha.h 

#include <stdbool.h>

int vi;
int vj;     //variables globales


------------------------------

moha.c 

bool verification_combinaisons(TUILE plateau[13][10], int i, int j){
	vi = 0, vj = 0;
	for(vi=0; vi<10; vi++){
		for (j=0; j<13; j++){
			if (plateau[vj][vi].typeTuile == NON_VIDE)
			{
				if(verification_combinaisons789(plateau, vi, vj)==true/* || verification_combinaisons777(plateau, vi, vj)==true*/){
					continue;
				}
				else{return false;} 
			}
	}

}
return true;
}
bool verification_combinaisons789(TUILE plateau[13][10], int i, int j){
	int total=0, validator=0, disrupt=vi+3;
	vi=0,vj=0;
	for (vi=vi; vi<=13; vi++){
		if(plateau[vj][vi].typeTuile == VIDE && vi<disrupt){return false;}
		else if(plateau[vj][vi].typeTuile == VIDE){break;}
		else{
			validator=validator + plateau[vj][vi].chiffre;
		}
		total=total+vi;
	}
	
	if(total == validator){return true;}
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
