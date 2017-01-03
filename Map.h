#pragma once
#include "init.h"
#include "Hub.h"

//Classe pour gérer l'affichage de la map
class Map :
	public init
{


private:
	//Donnée membres
		SDL_Texture *background;
		SDL_Texture *tileSet, *tileSetB;
		//Numéro du tileset à utiliser
		int tilesetAffiche;

		/* Coordonnées de départ du héros, lorsqu'il commence le niveau */
		int beginx, beginy;

		/* Coordonnées de début, lorsqu'on doit dessiner la map */
		int startX, startY;

		/* Coordonnées max de fin de la map */
		int maxX, maxY;

		/* Tableau à double dimension représentant la map de tiles */
		int tile[MAX_MAP_Y][MAX_MAP_X];

		//Deuxième couche de tiles
		int tile2[MAX_MAP_Y][MAX_MAP_X];

		//Troisième couche de tiles
		int tile3[MAX_MAP_Y][MAX_MAP_X];

		/* Timer et numéro du tileset à afficher pour animer la map */
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


	//Autre Méthodes/Fonctions
	void initMaps();
	void loadMap(char *name);
	void drawMap(int layer);
	void changeLevel();
	void cleanMaps();
	//void mapCollision(GameObject *entity);



};

