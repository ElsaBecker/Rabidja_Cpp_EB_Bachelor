#pragma once

#include "Hub.h"
#include "defs.h"

//Classe pour gérer les inputs clavier et manette
class input
{

	//Donnée membres
	SDL_Joystick *joystick;
	int DPADinUse = 0;
	int left, right, up, down, jump, attack, enter, erase, pause;


public:
	//Constructeur, Destructeur
	input();
	~input();

	//Mutateurs
	int getLeft();
	void setLeft(int nb);
	int getRight();
	void setRight(int nb);
	int getUp();
	void setUp(int nb);
	int getDown();
	void setDown(int nb);
	int getJump();
	void setJump(int nb);
	int getAttack();
	void setAttack(int nb);
	int getEnter();
	void setEnter(int nb);
	int getErase();
	void setErase(int nb);
	int getPause();
	void setPause(int nb);

	void openJoystick();
	void closeJoystick();
	void gestionInputs(input *input);
	void getInput(input *input);
	void getJoystick(input *input);
};

