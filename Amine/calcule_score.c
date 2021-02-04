int role_actuel=1;
int calcul_score()
{
    int num_vain;
    j[role_actuel].score=0;
    //Le score du joueur qui a encore de tuiles doit etre negatif
    for(int tt=0; tt<j[role_actuel].nbr_tuile; tt++)
    {
        j[role_actuel].score= j[role_actuel].score - j[role_actuel].tuiles[tt].chiffre;
    }
    if(j[role_actuel].score<0)
        {
            return j[role_actuel].score;
        }
    //score du winner
     else if(j[role_actuel].score==0)
     {
         num_vain=j[role_actuel].numero;

          for(int i=0; i<nbr_joueurs; i++)
            {
                if(num_vain != j[i].numero)
                {
                    j[num_vain-1].score = j[num_vain-1].score +-1*j[i].score;
                }
            }return j[num_vain-1].score;
     }
}
