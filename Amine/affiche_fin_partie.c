void affiche_fin_partie()
{
    int position_clic_x, position_clic_y;
    bool quit = false;
    SDL_Event event;
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow("Game Over",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, 0);

    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Surface * image = NULL;
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_Rect dest_rect;

    dest_rect = SDL_CreationRectangle(renderer, 125, 5, 250, 250);

    SDL_Surface * image_rep = NULL;
    SDL_Texture * texture_rep = SDL_CreateTextureFromSurface(renderer, image_rep);
    SDL_Rect dest_rect_rep;

    //Tester le numero du joueur actuel pour savoir le vainqueur
    //j[i].numero=1;
    if(j[i].numero==1)
    SDL_CreationImage(renderer, image, texture, dest_rect, "1wins.png");

    if(j[i].numero==2)
    SDL_CreationImage(renderer, image, texture, dest_rect, "2wins.png");


    if(j[i].numero==3)
    SDL_CreationImage(renderer, image, texture, dest_rect, "3wins.png");


    if(j[i].numero==4)
    SDL_CreationImage(renderer, image, texture, dest_rect, "4wins.png");


    //Creation de deux zones cliquables une pour rejouer et l'autre pour quitter
    dest_rect_rep = SDL_CreationRectangle(renderer, 0, 250, 250, 250);
    SDL_CreationImage(renderer, image_rep, texture_rep, dest_rect_rep, "rejouer.png");

    dest_rect_rep = SDL_CreationRectangle(renderer, 250, 250, 250, 250);
    SDL_CreationImage(renderer, image_rep, texture_rep, dest_rect_rep, "quitter.png");

    while (!quit)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                position_clic_x = event.button.x;      position_clic_y = event.button.y;
                //Tester la position du curseur sur le bouton rejouer
                if(position_clic_x<=250 && position_clic_x>=0 && position_clic_y <= 500 && position_clic_y >=250)
                   {
                        quit = true;
                        SDL_DestroyTexture(texture);    SDL_FreeSurface(image);    SDL_DestroyRenderer(renderer);   SDL_DestroyWindow(window);
                        affiche_palteau();
                    }
                //Tester la position du curseur sur le bouton Quitter
                if(position_clic_x<=500 && position_clic_x>=250 && position_clic_y <= 500 && position_clic_y >=250)
                    {
                        quit = true;
                    }break;
        }
        SDL_RenderCopy(renderer, texture, NULL, NULL);          SDL_RenderPresent(renderer);
    }
    SDL_DestroyTexture(texture);        SDL_FreeSurface(image);         SDL_DestroyRenderer(renderer);          SDL_DestroyWindow(window);
    SDL_Quit();
}
