#include "logic.h"


int vi;
int vj;

void initialisation_plateau(TUILE plateau[13][10]) {
	TUILE tuileVide;
	int i,j;
	tuileVide.chiffre = -1;
	tuileVide.couleurTuile = c0;
	tuileVide.typeTuile = VIDE;
	for(i = 0; i < 13; i++) {
		for (j = 0; j < 10; j++){
			plateau[i][j] = tuileVide;
		}
	}
}

void initialisation_chevalet(TUILE chevalet[10][3]) {
	TUILE tuileVide;
	int i,j;
	tuileVide.chiffre = -1;
	tuileVide.couleurTuile = c0;
	tuileVide.typeTuile = VIDE;
	for(i = 0; i < 10; i++) {
		for (j = 0; j < 3; j++){
			chevalet[i][j] = tuileVide;
		}
	}
}

void initialisation_inventaire(JOUEUR *joueur) {
	TUILE tuileVide;
	tuileVide.chiffre = -1;
	tuileVide.couleurTuile = c0;
	tuileVide.typeTuile = VIDE;
	for (int i = 0; i < 30; i++) {
		joueur->tuiles[i] = tuileVide;
	}
}

void creation_tuiles(TUILE *paquet) {
	TUILE tuile;
	tuile.typeTuile = NON_VIDE;
	for (int tuiles = 0; tuiles < 56; tuiles++){
		for (int i = 0; i < 4; i++){	
			tuile.couleurTuile = i;
			for (int j = 0; j < 14; j++){
				tuile.chiffre = j;
				paquet[tuiles] = tuile;
				tuiles++;
			}
		}
	}
}

void melanger_paquet_tuiles(TUILE *paquet) {
	int i, j;
	TUILE t;
	for (i = 0; i < 56; i++) {
		j = i + rand() / (RAND_MAX / (56 - i) +1);
		t = paquet[j];
		paquet[j] = paquet[i];
		paquet[i] = t;
	}
}

void distribuer_tuiles(JOUEUR *joueur, TUILE *paquet) {
	initialisation_inventaire(joueur);
	TUILE *tuile = paquet + (joueur->numero * 14);
	for (int i = 0; i < 14; i++) {
		joueur->tuiles[i] = tuile[i];
	}
}
/*
void creation_joueurs(JOUEUR *joueurs) {
	int i, nbJoueurs;
	printf("Entre 2 et 4, combien de joueurs souhaitez-vous ?\n");
	scanf("%d", &nbJoueurs);
	while (nbJoueurs<1 || nbJoueurs>4) {
		printf("Erreur. Entre 2 et 4, combien de joueurs souhaitez-vous ?\n");
		scanf("%d", &nbJoueurs);
	}
	printf("nbjoueurs = %d", nbJoueurs);
	joueurs = realloc(joueurs, nbJoueurs * sizeof(JOUEUR));
	free(joueurs);
	printf("size of joueur = %ld", sizeof(joueurs));
	for (i = 0; i < nbJoueurs; i++) {
		printf("Entrez le pseudo du Joueur %d :\n", i+1);
		scanf("%s", joueurs[i].pseudo);
		joueurs[i].numero = i;
		joueurs[i].score = 0;
	}
}*/

void tri_777(JOUEUR *joueurs) {
	int val, compteur;
	TUILE pivot;
	for (int i = 0; i < 30; i++) {
		val = joueurs->tuiles[i].chiffre;
		if (val != -1) {
			compteur = 1;
			for (int j = i+1; j < 30; j++) {
				if (joueurs->tuiles[j].chiffre == val) {
					pivot = joueurs->tuiles[i+compteur];
					joueurs->tuiles[i+compteur] = joueurs->tuiles[j];
					joueurs->tuiles[j] = pivot;
					compteur++;
				}
				
			}
		}
	}
}

void tri_789(JOUEUR *joueurs) {
	tri_par_couleur(joueurs);
	tri_par_selection(joueurs);
}

void tri_par_couleur(JOUEUR *joueurs) {
	int couleur, compteur;
	TUILE pivot;
	for (int i = 0; i < 30; i++) {
		couleur = joueurs->tuiles[i].couleurTuile;
		if (couleur != c0) {
			compteur = 1;
			for (int j = i+1; j < 30; j++) {
				if (joueurs->tuiles[j].couleurTuile == couleur) {
					pivot = joueurs->tuiles[i+compteur];
					joueurs->tuiles[i+compteur] = joueurs->tuiles[j];
					joueurs->tuiles[j] = pivot;
					compteur++;
				}
			}
		}
	}
}

void tri_par_selection(JOUEUR *joueurs) {
	int min, couleur;
	TUILE pivot;
	for (int i = 0; i < 30; i++ ) {
		min = i;
		couleur = joueurs->tuiles[i].couleurTuile;
		if (couleur != c0) {
			for (int j = i+1; j < 30; j++) {
				if (joueurs->tuiles[j].couleurTuile == couleur) {
					if (joueurs->tuiles[min].chiffre > joueurs->tuiles[j].chiffre) {
						pivot = joueurs->tuiles[min];
						joueurs->tuiles[min] = joueurs->tuiles[j];
						joueurs->tuiles[j] = pivot;
					}
				}
			}
		}
	}
}

void inventaire_en_chevalet(JOUEUR *joueur, TUILE chevalet[10][3]) {
	int k = 0;
	initialisation_chevalet(chevalet);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 10; j++) {
			if (k < 30) {
				chevalet[j][i] = joueur->tuiles[k];
				k++;
			}
		}
	}
}

int inventaire_plein(JOUEUR *joueur) {
	int plein = 1;
	for (int i = 0; i < 30; i++) {
		if (joueur->tuiles[i].typeTuile == VIDE && plein == 1) {
			plein = 0;
		}
	}
	return plein;
}

int paquet_vide(TUILE *paquet) {
	int vide = 1;
	for (int i = 0; i < 56; i++) {
		if (paquet[i].typeTuile == NON_VIDE && vide == 1) {
			vide = 0;
		}
	}
	return vide;
}

void piocher_tuile(JOUEUR *joueur, TUILE *paquet) {
	int vide = paquet_vide(paquet);
	int plein = inventaire_plein(joueur);
	int pioche = 0;
	TUILE tuileVide;
	tuileVide.typeTuile = VIDE;
	tuileVide.chiffre = -1;
	tuileVide.couleurTuile = c0;
	if (vide == 0 && plein == 0) {
		for (int i = 0; i < 30; i++) {
			if (joueur->tuiles[i].typeTuile == VIDE && pioche == 0) {
				joueur->tuiles[i] = paquet[0];
				for (int j = 1; j < 56; j++) {
					paquet[j-1] = paquet[j];
				}
				paquet[55] = tuileVide;
				pioche = 1;
			}
		}
	}
}

void Change_TuileDeTableau(TUILE *a, TUILE *b){
    b->chiffre = a->chiffre;
    b->couleurTuile = a->couleurTuile;
    b->typeTuile = a->typeTuile;
    a->chiffre = -1;
    a->couleurTuile = VIDE;
    a->typeTuile = VIDE;
}

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

