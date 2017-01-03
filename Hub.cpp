#include "Hub.h"



Hub::Hub()
{
}


Hub::~Hub()
{
}

Map Hub::getMap()
{
	return map;
}

GameObject Hub::getGameObject()
{
	return gameObject;
}

input Hub::getInput()
{
	return inputObject;
}

init Hub::getInit()
{
	return initObject;
}

menu Hub::getMenu()
{
	return menuObject;
}
