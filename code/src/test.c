#include <stdio.h>
#include <stdlib.h>
#include "test.h"

void initialisation_plateau(TUILE **plateau) {
	TUILE tuileVide;
	int i,j;
	tuileVide.chiffre = -1;
	tuileVide.couleurTuile = VIDE;
	tuileVide.typeTuile = VIDE;
	for(i = 0; i < 212; i++) 
	{
		for (j = 0; j < 212; j++)
		{
			plateau[i][j] = tuileVide;
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
