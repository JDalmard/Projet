#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"

int main(int argc, char *argv[])
{
  SDL_Window* fenetre;  // Déclaration de la fenêtre
  SDL_Event evenements; // Événements liés à la fenêtre
  bool terminer = false;
  if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
  {
    printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
    SDL_Quit();
    return EXIT_FAILURE;
  }
  // Créer la fenêtre
  fenetre = SDL_CreateWindow("Fenetre SDL",
      SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
  if(fenetre == NULL) // En cas d’erreur
  {printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
  SDL_Quit();
  return EXIT_FAILURE;
  }
  // Mettre en place un contexte de rendu de l’écran
  SDL_Renderer* ecran;
  ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
  // Charger l’image
  SDL_Texture* fond = charger_image( "fond.bmp", ecran );

  // Boucle principale
  while(!terminer)
{
  SDL_RenderClear(ecran);
  SDL_RenderCopy(ecran, fond, NULL, NULL);
  SDL_RenderPresent(ecran);

  while( SDL_PollEvent( &evenements ) )
  switch(evenements.type)
  {
    case SDL_QUIT:
      terminer = true; break;
    case SDL_KEYDOWN:
    switch(evenements.key.keysym.sym)
    {
      case SDLK_ESCAPE:
      case SDLK_q:
        terminer = true; break;
      }
    }
}

// Libération de l’écran (renderer)
SDL_DestroyRenderer(ecran);

// Quitter SDL
SDL_DestroyWindow(fenetre);
SDL_Quit();
return 0;
}
