#pragma once
#include "init.h"
#include "Map.h"
#include "GameObject.h"
#include "input.h"
#include "menu.h"


//Hub pour permettre de récupérer des variables/méthodes des autres classes
//Et de les faire interagir
class Hub :
	public init
{

protected:
	Map map;
	GameObject gameObject;
	input inputObject;
	init initObject;
	menu menuObject;


public:
	//Constructeur, Destructeur
	Hub();
	~Hub();

	//Mutateurs
	Map getMap();
	GameObject getGameObject();
	input getInput();
	init getInit();
	menu getMenu();




};

