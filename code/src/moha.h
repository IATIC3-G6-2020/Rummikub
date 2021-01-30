typedef enum {VIDE, NON_VIDE} TYPE_TUILE;
typedef enum {c1,c2,c3,c4,c0} COULEUR_TUILE;

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
	TUILE tuiles[30];
}JOUEUR;


void initialisation_plateau(TUILE plateau[13][10]);
void initialisation_chevalet(TUILE chevalet[10][3]);
void creation_tuiles(TUILE *paquet);
void melanger_paquet_tuiles(TUILE *paquet);
void distribuer_tuiles(JOUEUR *joueur, TUILE *paquet);

void creation_joueurs(JOUEUR *joueurs);
void tri_777(JOUEUR *joueurs);
void tri_789(JOUEUR *joueurs);
void tri_par_couleur(JOUEUR *joueurs);
void tri_par_selection(JOUEUR *joueurs);
void inventaire_en_chevalet(JOUEUR *joueur, TUILE chevalet[10][3]);
int inventaire_plein(JOUEUR *joueur);
int paquet_vide(TUILE *paquet);
void piocher_tuile(JOUEUR *joueur, TUILE *paquet);
void initialisation_inventaire(JOUEUR *joueur);
