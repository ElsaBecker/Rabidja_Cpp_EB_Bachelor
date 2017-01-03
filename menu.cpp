#include "menu.h"



menu::menu()
{
}


menu::~menu()
{
}

int menu::getOnMenu()
{
	return onMenu;
}

int menu::getMenuType()
{
	return menuType;
}

void menu::setOnMenu(int valeur, int type)
{
	onMenu = valeur;
	menuType = type;
}

void menu::initMenus()
{
	titlescreen = hubObject.getInit().loadImage("graphics/title.png");
}

void menu::cleanMenus()
{
	// Libère la texture de l'écran-titre 
	if (titlescreen != NULL)
	{
		SDL_DestroyTexture(titlescreen);
		titlescreen = NULL;
	}
}

/*void menu::updateStartMenu(input * input)
{
	//Si on appuie sur BAS
	if (input->getDown() == 1)
	{
		//Si choice = O (il est sur start), on le met à 1 (quit)
		if (choice == 0)
			choice++;

		input->setDown(0);
	}

	//Si on appuie sur HAUT
	if (input->getUp() == 1)
	{
		//Si choice = 1 (il est sur Quit), on le met à 0 (Start)
		if (choice == 1)
			choice--;

		input->setUp(0);
	}

	//Choix du level
	if (input->getRight() == 1)
	{
		//Si choice = 1 (il est sur Quit), on le met à 0 (Start)
		if (getLevel() >= LEVEL_MAX)
			SetValeurDuNiveau(1);
		else
			SetValeurDuNiveau(getLevel() + 1);

		input->setRight(0);
	}

	if (input->getLeft() == 1)
	{
		//Si choice = 1 (il est sur Quit), on le met à 0 (Start)
		if (getLevel() <= 1)
			SetValeurDuNiveau(LEVEL_MAX);
		else
			SetValeurDuNiveau(getLevel() - 1);

		input->setLeft(0);
	}



	//Si on appuie sur Enter ou A (manette Xbox 360) et qu'on est sur Start, on recharge le jeu et on quitte l'état menu
	if (input->getEnter()|| input->getJump())
	{
		if (choice == 0)
		{
			resetCheckpoint();
			initializePlayer(1);
			changeLevel();
			// On réinitialise les variables du jeu 
			setNombreDeVies(3);
			setNombreDetoiles(0);
			onMenu = 0;
		}
		//Sinon, on quitte le jeu
		else if (choice == 1)
		{
			exit(0);
		}
		input->setEnter(0);
		input->setJump(0);
	}

}*/

void menu::updatePauseMenu(input * input)
{
	//Si on appuie sur BAS
	if (input->getDown() == 1)
	{
		//Si choice = O (il est sur start), on le met à 1 (quit)
		if (choice == 0)
			choice++;

		input->setDown(0);
	}

	//Si on appuie sur HAUT
	if (input->getUp() == 1)
	{
		//Si choice = 1 (il est sur Quit), on le met à 0 (Start)
		if (choice == 1)
			choice--;

		input->setUp(0);
	}

	//Si on appuie sur Enter ou A (manette Xbox 360) et qu'on est sur Start, on recharge le jeu et on quitte l'état menu
	if (input->getEnter() || input->getJump())
	{
		if (choice == 0)
		{
			//Si on appuie sur Enter on quitte l'état menu
			onMenu = 0;
		}
		//Sinon, on quitte le jeu
		else if (choice == 1)
		{
			choice = 0;
			menuType = START;
		}
		input->setEnter(0);
		input->setJump(0);
	}
}

void menu::drawStartMenu()
{
	//On crée une variable qui contiendra notre texte
	char text[200];

	//On affiche l'écran-titre
	hubObject.getInit().drawImage(titlescreen, 0, 0);

	//Si l'option n'est pas en surbrillance, on l'affiche normalement
	if (choice != 0)
	{
		// !! FICHIER
		sprintf_s(text, sizeof(text), "START: Lvl %d", getLevel());
		//Ombrage en noir
		hubObject.getInit().drawString(text, 375, 252, 0, 0, 0, 255);
		hubObject.getInit().drawString(text, 373, 250, 255, 255, 255, 255);
	}
	if (choice != 1)
	{
		//!! FICHIER
		sprintf_s(text, sizeof(text), "QUIT");
		//Ombrage en noir
		hubObject.getInit().drawString(text, 425, 292, 0, 0, 0, 255);
		hubObject.getInit().drawString(text, 422, 290, 255, 255, 255, 255);
	}

	//Si l'option est en surbrillance, on change la couleur
	if (choice == 0)
	{
		// !! FICHIER
		sprintf_s(text, sizeof(text), "START: Lvl %d", getLevel());
		//Ombrage en noir
		hubObject.getInit().drawString(text, 375, 252, 0, 0, 0, 255);
		hubObject.getInit().drawString(text, 373, 250, 255, 255, 0, 255);
	}
	else if (choice == 1)
	{
		//!! FICHIER
		sprintf_s(text, sizeof(text), "QUIT");
		//Ombrage en noir
		hubObject.getInit().drawString(text, 425, 292, 0, 0, 0, 255);
		hubObject.getInit().drawString(text, 422, 290, 255, 255, 0, 255);
	}
}

void menu::drawPauseMenu()
{
	char text[200];

	//On écrit PAUSE

	sprintf_s(text, sizeof(text), "** PAUSE **");
	hubObject.getInit().drawString(text, 322, 200, 0, 0, 0, 255);
	hubObject.getInit().drawString(text, 320, 198, 255, 255, 255, 255);


	//Si l'option n'est pas en surbrillance, on l'affiche normalement
	if (choice != 0)
	{

		sprintf_s(text, sizeof(text), "Continue");
		//Ombrage en noir
		hubObject.getInit().drawString(text, 346, 252, 0, 0, 0, 255);
		hubObject.getInit().drawString(text, 344, 250, 255, 255, 255, 255);
	}
	if (choice != 1)
	{

		sprintf_s(text, sizeof(text), "Exit");
		//Ombrage en noir
		hubObject.getInit().drawString(text, 386, 292, 0, 0, 0, 255);
		hubObject.getInit().drawString(text, 384, 290, 255, 255, 255, 255);
	}

	//Si l'option est en surbrillance, on change la couleur
	if (choice == 0)
	{

		sprintf_s(text, sizeof(text), "Continue");
		//Ombrage en noir
		hubObject.getInit().drawString(text, 346, 252, 0, 0, 0, 255);
		hubObject.getInit().drawString(text, 344, 250, 255, 255, 0, 255);
	}
	else if (choice == 1)
	{

		sprintf_s(text, sizeof(text), "Exit");
		//Ombrage en noir
		hubObject.getInit().drawString(text, 386, 292, 0, 0, 0, 255);
		hubObject.getInit().drawString(text, 384, 290, 255, 255, 0, 255);
	}
}
