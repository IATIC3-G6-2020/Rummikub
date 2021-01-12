#include <stdio.h>
#include <stdlib.h>
#include "moha.h"

void initialisation_plateau(TUILE plateau[13][10]) {
	TUILE tuileVide;
	int i,j;
	tuileVide.chiffre = -1;
	tuileVide.couleurTuile = VIDE;
	tuileVide.typeTuile = VIDE;
	for(i = 0; i < 13; i++) 
	{
		for (j = 0; j < 10; j++)
		{
			plateau[i][j] = tuileVide;
		}
	}
}

void initialisation_chevalet(TUILE chevalet[10][3]) {
	TUILE tuileVide;
	int i,j;
	tuileVide.chiffre = -1;
	tuileVide.couleurTuile = VIDE;
	tuileVide.typeTuile = VIDE;
	for(i = 0; i < 10; i++) 
	{
		for (j = 0; j < 3; j++)
		{
			chevalet[i][j] = tuileVide;
		}
	}
}

void creation_tuiles(TUILE *paquet) {
	TUILE tuile;
	tuile.typeTuile = NON_VIDE;
	for (int tuiles = 0; tuiles < 56; tuiles++)
	{
		for (int i = 0; i < 4; i++)
		{	
			tuile.couleurTuile = i;
			for (int j = 0; j < 14; j++)
			{
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
	TUILE *tuile = paquet + (joueur->numero * 14);
	for (int i = 0; i < 14; i++) {
		joueur->tuiles[i] = tuile[i];
	}
}


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
}

void tri_777(TUILE *paquet) {
	int val, compteur;
	TUILE pivot;
	for (int i = 0; i < 56; i++) {
		val = paquet[i].chiffre;
		if (val != -1) {
			compteur = 1;
			for (int j = i+1; j < 56; j++) {
				if (paquet[j].chiffre == val) {
					pivot = paquet[i+compteur];
					paquet[i+compteur] = paquet[j];
					paquet[j] = pivot;
					compteur++;
				}
				
			}
		}
	}
}

void tri_789(TUILE *paquet) {
	tri_par_couleur(paquet);
	tri_par_selection(paquet);
}

void tri_par_couleur(TUILE *paquet) {
	int couleur, compteur;
	TUILE pivot;
	for (int i = 0; i < 56; i++) {
		couleur = paquet[i].couleurTuile;
		if (couleur != c0) {
			compteur = 1;
			for (int j = i+1; j < 56; j++) {
				if (paquet[j].couleurTuile == couleur) {
					pivot = paquet[i+compteur];
					paquet[i+compteur] = paquet[j];
					paquet[j] = pivot;
					compteur++;
				}
			}
		}
	}
}

void tri_par_selection(TUILE *paquet) {
	int min, couleur;
	TUILE pivot;
	for (int i = 0; i < 56; i++ ) {
		min = i;
		couleur = paquet[i].couleurTuile;
		if (couleur != c0) {
			for (int j = i+1; j < 56; j++) {
				if (paquet[j].couleurTuile == couleur) {
					if (paquet[min].chiffre > paquet[j].chiffre) {
						pivot = paquet[min];
						paquet[min] = paquet[j];
						paquet[j] = pivot;
					}
				}
			}
		}
	}
}