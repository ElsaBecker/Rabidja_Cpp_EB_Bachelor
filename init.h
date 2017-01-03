#pragma once
#include "defs.h"
#include "Hub.h"

class init
{

protected :

	//Donnée membres
		/*Initialisation*/
		SDL_Window *screen;
		SDL_Renderer *renderer;

		/*Draw*/
		SDL_Texture *HUD_vie, *HUD_etoiles;

		/*Font*/
		TTF_Font *font;



	

public:

	//Mutateurs
	init();
	~init();

	//Méthodes/Fonctions
	SDL_Renderer *getrenderer() const;

	//Initialisation
	void initialise(char *title);
	void loadGame() const;
	void cleanup();

	//Draw
	void drawGame(int pauseMenu); /*Affiche le fond, le joueur, les plateformes, Menus et HUD*/
	SDL_Texture *loadImage(char *name); /* Charge les images avec SDL Image dans une SDL_Surface */
	void drawImage(SDL_Texture *image, int x, int y); /* Dessine l'image entière sur l'écran aux coordonnées x et y */
	void drawImagePlus(SDL_Texture *image, int x, int y, double rotation, SDL_Point center, SDL_RendererFlip flip);//Nouvelle fonction en SDL2 qui gère le flip et les rotations
	void drawTile(SDL_Texture *image, int destx, int desty, int srcx, int srcy);
	void delay(unsigned int frameLimit);
	void drawHud(void); //Affichage du HUD : coeurs, vies, étoiles, etc...
	void initHUD(void); /* On charge les images du HUD */
	void cleanHUD(void);

	//Font
	void loadFont(char *name, int size);
	void closeFont();
	void drawString(char *text, int x, int y, int r, int g, int b, int a);


};

