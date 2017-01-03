#pragma once
#include "init.h"
#include "Hub.h"

//Classe pour g�rer l'affichage de la map
class Map :
	public init
{


private:
	//Donn�e membres
		SDL_Texture *background;
		SDL_Texture *tileSet, *tileSetB;
		//Num�ro du tileset � utiliser
		int tilesetAffiche;

		/* Coordonn�es de d�part du h�ros, lorsqu'il commence le niveau */
		int beginx, beginy;

		/* Coordonn�es de d�but, lorsqu'on doit dessiner la map */
		int startX, startY;

		/* Coordonn�es max de fin de la map */
		int maxX, maxY;

		/* Tableau � double dimension repr�sentant la map de tiles */
		int tile[MAX_MAP_Y][MAX_MAP_X];

		//Deuxi�me couche de tiles
		int tile2[MAX_MAP_Y][MAX_MAP_X];

		//Troisi�me couche de tiles
		int tile3[MAX_MAP_Y][MAX_MAP_X];

		/* Timer et num�ro du tileset � afficher pour animer la map */
		int mapTimer, tileSetNumber;

	

public:

	//Mutateurs
	Map();
	~Map();

	//get, set
	int getStartX() const;
	void setStartX(int valeurX);

	int getStartY() const;
	void setStartY(int valeurY);

	int getMaxX() const;
	int getMaxY() const;

	int getBeginX() const;
	int getBeginY() const;

	SDL_Texture *getBackground() const;

	int getTileValue(int y, int x);

	SDL_Texture *getTileSetA() const;
	SDL_Texture *getTileSetB() const;


	//Autre M�thodes/Fonctions
	void initMaps();
	void loadMap(char *name);
	void drawMap(int layer);
	void changeLevel();
	void cleanMaps();
	//void mapCollision(GameObject *entity);



};

