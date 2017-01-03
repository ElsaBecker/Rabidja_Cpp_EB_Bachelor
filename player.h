#pragma once

#include "Hub.h"
#include "defs.h"

class player :
	public GameObject
{

	//Données Membres
	int vies, etoiles, level;
	Hub hubObject;
	SDL_Texture *playerSpriteSheet;


public:
	//Constructeur, Destructeur
	player();
	~player();

	//Mutateurs
	GameObject *getPlayer();
	int getPlayerDirection();
	int getPlayerx();
	void setPlayerx(int valeur);
	int getPlayery();
	void setPlayery(int valeur);
	int getLevel();
	void SetValeurDuNiveau(int valeur);
	int getLife();
	int getNombreDeVies();
	void setNombreDeVies(int valeur);
	int getNombreDetoiles();
	void setNombreDetoiles(int valeur);


	void initPlayerSprites();
	void cleanPlayer();
	void killPlayer();
	void playerHurts(GameObject *monster);
	void initializePlayer(int newLevel);
	void updatePlayer(input *input);
	void drawPlayer();
	void centerScrollingOnPlayer();
	void getItem(int itemNumber);

};

