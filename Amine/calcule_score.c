//Fonction qui cumule la valeur des tuiles pour calculer le score
int calcul_score()
{
    int num_vain;
    j[i].score=0;
    //Le score du joueur qui a encore de tuiles doit etre negatif
    for(int tt=0; tt<j[i].nbr_tuile; tt++)
    {
        j[i].score= j[i].score - j[i].tuiles[tt].chiffre;
    }
    //score du winner
     if(j[i].score==0)
     {
         num_vain=j[i].numero;

          for(int role=0; role<4; role++)
            {
                if(num_vain != j[role].numero)
                {
                    j[num_vain-1].score = j[num_vain-1].score +-1*j[role].score;
                }
            }
            return j[num_vain-1].score;
     }
     else if(j[i].score<0)
     {
         return j[i].score;
     }
}
