#include <stdio.h>
#include <stdlib.h>

typedef enum {VIDE, NON_VIDE} TYPE_TUILE;
typedef enum {c1,c2,c3,c4,TRANSPARENT} COULEUR_TUILE;

typedef struct TUILE
{
	int chiffre; //-1 pour les tuiles vides, 0 pour le joker? et le reste normal
	COULEUR_TUILE couleurTuile;
	TYPE_TUILE	typeTuile;
}TUILE;

TUILE plateau[212][212];
TUILE paquet[56];

typedef struct JOUEUR
{
	char* pseudo;
	int numero, score;
	TUILE tuiles[14];
}JOUEUR;

JOUEUR *joueurs;

void initialisation_plateau() {
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

void creation_tuiles() {
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

void melanger_paquet_tuiles() {
	int i, j;
	TUILE t;
	for (i = 0; i < 56; i++) {
		j = i + rand() / (RAND_MAX / (56 - i) +1);
		t = paquet[j];
		paquet[j] = paquet[i];
		paquet[i] = t;
	}
}

void distribuer_tuiles(JOUEUR *joueur) {
	TUILE *tuile = paquet + (joueur->numero * 14);
	for (int i = 0; i < 14; i++) {
		joueur->tuiles[i] = tuile[i];
	}
}

void creation_joueurs() {
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

void tri_777() {
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

void tri_789() {
//mm couleur + suite croissante
}

int main() {
	creation_tuiles();
	printf("Avant mélange\n");
	for (int i = 0; i < 56; i++) {
		printf("couleur %d numero %d\n", paquet[i].couleurTuile, paquet[i].chiffre);
	}
	printf("-------------------------------------------------\n");
	melanger_paquet_tuiles();
	printf("Après mélange\n");
	for (int i = 0; i < 56; i++) {
		printf("couleur %d numero %d\n", paquet[i].couleurTuile, paquet[i].chiffre);
	}
	printf("-------------------------------------------------\n");
	tri_777();
	printf("Après tri\n");
	for (int i = 0; i < 56; i++) {
		printf("couleur %d numero %d\n", paquet[i].couleurTuile, paquet[i].chiffre);
	}
	printf("-------------------------------------------------\n");
	creation_joueurs();
	size_t n = sizeof(joueurs)/sizeof(JOUEUR);
	for (int j = 0; j < n; j++) {
		printf("Joueur %d (%d) :\nPseudo : %s\nScore : %d", joueurs[j].numero + 1, joueurs[j].numero, joueurs[j].pseudo, joueurs[j].score);
		printf("_____________________________________________________\n");
	}
	return 0;
}
