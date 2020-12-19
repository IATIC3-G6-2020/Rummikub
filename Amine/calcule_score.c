//Fonction qui cumule la valeur des tuiles pour calculer le score
int calcul_score()
{
    //on initialise le score par 0
    j->score=0;
    //Le score du joueur qui a encore de tuiles doit etre negatif
    for(int i=0; i<j->nbr_tuile; i++)
    {
        j->score=j->score - j->tuiles[i].chiffre;
    }
    return j->score;
}
