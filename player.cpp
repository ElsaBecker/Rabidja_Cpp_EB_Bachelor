#include "player.h"



player::player()
{
}


player::~player()
{
}

GameObject * player::getPlayer()
{
	return nullptr; //WTF ???
}

int player::getPlayerDirection()
{
	return 0;
}

int player::getPlayerx(void)
{
	return 0;
}

void player::setPlayerx(int valeur)
{
}

int player::getPlayery(void)
{
	return 0;
}

void player::setPlayery(int valeur)
{
}

int player::getLevel(void)
{
	return 0;
}

void player::SetValeurDuNiveau(int valeur)
{
}

int player::getLife(void)
{
	return 0;
}

int player::getNombreDeVies(void)
{
	return 0;
}

void player::setNombreDeVies(int valeur)
{
}

int player::getNombreDetoiles(void)
{
	return 0;
}

void player::setNombreDetoiles(int valeur)
{
}

void player::initPlayerSprites(void)
{
}

void player::cleanPlayer(void)
{
}

void player::killPlayer(void)
{
}

void player::playerHurts(GameObject * monster)
{
}

void player::initializePlayer(int newLevel)
{
}

void player::updatePlayer(input * input)
{
}

void player::drawPlayer(void)
{
}

void player::centerScrollingOnPlayer(void)
{
}

void player::getItem(int itemNumber)
{
}
