typedef enum {VIDE, NON_VIDE} TYPE_TUILE;
typedef enum {c1,c2,c3,c4} COULEUR_TUILE;

typedef struct TUILE
{
	int chiffre; //-1 pour les tuiles vides, 0 pour le joker? et le reste normal
	COULEUR_TUILE couleurTuile;
	TYPE_TUILE	typeTuile;
}TUILE;



typedef struct JOUEUR
{
	char* pseudo;
	int numero, score;
	TUILE tuiles[14];
}JOUEUR;


void initialisation_plateau(TUILE plateau[13][10]);
void creation_tuiles(TUILE *paquet);
void melanger_paquet_tuiles(TUILE *paquet);
void distribuer_tuiles(JOUEUR *joueur, TUILE *paquet);

void creation_joueurs(JOUEUR *joueurs);
void tri_777(TUILE *paquet);
void tri_789(TUILE *paquet);