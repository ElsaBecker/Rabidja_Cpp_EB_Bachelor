#pragma once

#include "init.h"
#include "Hub.h"

class menu
{
	//Données membres
	int onMenu, menuType, choice;
	SDL_Texture *titlescreen;
	Hub hubObject;





public:
	//Mutateurs
	menu();
	~menu();

	//Gestion des menus
	int getOnMenu();
	int getMenuType();
	void setOnMenu(int valeur, int type);


	void initMenus();
	void cleanMenus();
	void updateStartMenu(input *input);
	void updatePauseMenu(input *input);
	void drawStartMenu();
	void drawPauseMenu();

};

