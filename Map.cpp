#include "Map.h"



Map::Map()
{
}


Map::~Map()
{
}

int Map::getStartX() const
{
	return startX;
}

void Map::setStartX(int valeurX)
{
	startX = valeurX;
}

int Map::getStartY() const
{
	return startY;
}

void Map::setStartY(int valeurY)
{
	startY = valeurY;
}

int Map::getMaxX() const
{
	return maxX;
}

int Map::getMaxY() const
{
	return maxY;
}

int Map::getBeginX() const
{
	return beginx;
}

int Map::getBeginY() const
{
	return beginy;
}

SDL_Texture * Map::getBackground() const
{
	return background;
}

int Map::getTileValue(int y, int x)
{
	return tile[y][x];
}

SDL_Texture * Map::getTileSetA() const
{
	return tileSet;
}

SDL_Texture * Map::getTileSetB() const
{
	return tileSetB;
}

void Map::initMaps()
{
	// Charge l'image du fond (background)  
	background = loadImage("graphics/background.png");

	//On initialise le timer
	mapTimer = TIME_BETWEEN_2_FRAMES * 3;
	tileSetNumber = 0;
}

void Map::loadMap(char * name)
{
	int x, y;
	FILE *fp;
	errno_t err;

	/*ATTENTION REGARDER TP C++ POUR OUVERTURE ECRITURE LECTURE FICHIER*/
	//Ouvre le fichier en lecture (renvoie une erreur s'il n'existe pas)
	if ((err = fopen_s(&fp, name, "rb")) != 0)
	{
		cout << "Le fichier map n'a pas pu etre ouvert." << endl;
		exit(1);
	}


	cout << beginx << endl;
	cout << beginy << endl;

	/* lit la val de tileset */

	cout << tilesetAffiche;

	maxX = maxY = 0;

	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			/* On lit le num�ro de la tile et on le copie dans notre tableau */

			cout << tile[y][x] << endl;

			/* Permet de d�terminer la taille de la map (voir plus bas) */
			if (tile[y][x] > 0)
			{
				if (x > maxX)
				{
					maxX = x;
				}

				if (y > maxY)
				{
					maxY = y;
				}
			}
		}
	}

	//Deuxi�me couche de tiles
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			/* On lit le num�ro de la tile et on le copie dans notre tableau */

			cout << tile2[y][x] << endl;
		}
	}

	//Troisi�me couche de tiles
	for (y = 0; y < MAX_MAP_Y; y++)
	{
		for (x = 0; x < MAX_MAP_X; x++)
		{
			/* On lit le num�ro de la tile et on le copie dans notre tableau */

			cout << tile3[y][x] << endl;
		}
	}

	/* maxX et maxY sont les coordonn�es de fin de la map.
	On les trouve d�s qu'il n'y a plus que des z�ros � la suite.
	Comme �a, on peut faire des maps de tailles diff�rentes avec la m�me
	structure de fichier. */
	maxX = (maxX + 1) * TILE_SIZE;
	maxY = (maxY + 1) * TILE_SIZE;

	/* Et on referme le fichier */
	fclose(fp);
}

void Map::drawMap(int layer)
{
	int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;

	/* On initialise mapX � la 1�re colonne qu'on doit blitter.
	Celle-ci correspond au x de la map (en pixels) divis�s par la taille d'une tile (32)
	pour obtenir la bonne colonne de notre map
	Exemple : si x du d�but de la map = 1026, on fait 1026 / 32
	et on sait qu'on doit commencer par afficher la 32eme colonne de tiles de notre map */
	mapX = startX / TILE_SIZE;

	/* Coordonn�es de d�part pour l'affichage de la map : permet
	de d�terminer � quels coordonn�es blitter la 1�re colonne de tiles au pixel pr�s
	(par exemple, si la 1�re colonne n'est visible qu'en partie, on devra commencer � blitter
	hors �cran, donc avoir des coordonn�es n�gatives - d'o� le -1). */
	x1 = (startX % TILE_SIZE) * -1;

	/* Calcul des coordonn�es de la fin de la map : jusqu'o� doit-on blitter ?
	Logiquement, on doit aller � x1 (d�part) + SCREEN_WIDTH (la largeur de l'�cran).
	Mais si on a commenc� � blitter en dehors de l'�cran la premi�re colonne, il
	va falloir rajouter une autre colonne de tiles sinon on va avoir des pixels
	blancs. C'est ce que fait : x1 == 0 ? 0 : TILE_SIZE qu'on pourrait traduire par:
	if(x1 != 0)
	x2 = x1 + SCREEN_WIDTH + TILE_SIZE , mais forc�ment, c'est plus long ;)*/
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	/* On fait exactement pareil pour calculer y */
	mapY = startY / TILE_SIZE;
	y1 = (startY % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);


	//On met en place un timer pour animer la map 
	if (mapTimer <= 0)
	{
		if (tileSetNumber == 0)
		{
			tileSetNumber = 1;
			mapTimer = TIME_BETWEEN_2_FRAMES * 3;
		}
		else
		{
			tileSetNumber = 0;
			mapTimer = TIME_BETWEEN_2_FRAMES * 3;
		}
	}
	else
		mapTimer--;


	/* Dessine la carte en commen�ant par startX et startY */

	/* On dessine ligne par ligne en commen�ant par y1 (0) jusqu'� y2 (480)
	A chaque fois, on rajoute TILE_SIZE (donc 32), car on descend d'une ligne
	de tile (qui fait 32 pixels de hauteur) */
	if (layer == 1)
	{
		for (y = y1; y < y2; y += TILE_SIZE)
		{
			/* A chaque d�but de ligne, on r�initialise mapX qui contient la colonne
			(0 au d�but puisqu'on ne scrolle pas) */
			mapX = startX / TILE_SIZE;

			/* A chaque colonne de tile, on dessine la bonne tile en allant
			de x = 0 � x = 640 */
			for (x = x1; x < x2; x += TILE_SIZE)
			{

				//Si la tile � dessiner n'est pas une tile vide
				if (tile[mapY][mapX] != 0)
				{

					/*On teste si c'est une tile plateforme flottante */
					if (tile[mapY][mapX] >= TILE_PLATEFORME_DEBUT
						&& tile[mapY][mapX] <= TILE_PLATEFORME_FIN)
					{
						//On initialise une plateforme flottante
						//Pour obtenir le type (dernier arg), on enl�ve le num�ro de la 1�re tile plateforme
						//(TILE_PLATEFORME_DEBUT) au num�ro de la til en cours (map.tile[mapY][mapX])
						//et on rajoute 1 pour que le premier type soit le 1 et pas le 0 ;)
						initPlateforme(mapX * TILE_SIZE, mapY * TILE_SIZE, tile[mapY][mapX] - TILE_PLATEFORME_DEBUT + 1);

						//Et on efface cette tile de notre tableau pour �viter un spawn de plateformes
						//infini !
						tile[mapY][mapX] = 0;
					}
				}

				/* Suivant le num�ro de notre tile, on d�coupe le tileset (a = le num�ro
				de la tile */
				a = tile[mapY][mapX];

				/* Calcul pour obtenir son y (pour un tileset de 10 tiles
				par ligne, d'o� le 10 */
				ysource = a / 10 * TILE_SIZE;
				/* Et son x */
				xsource = a % 10 * TILE_SIZE;

				/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
				if (tileSetNumber == 0)
					drawTile(tileSet, x, y, xsource, ysource);
				else
					drawTile(tileSetB, x, y, xsource, ysource);

				mapX++;
			}

			mapY++;
		}
	}

	else if (layer == 2)
	{
		//Deuxi�me couche de tiles ;)
		for (y = y1; y < y2; y += TILE_SIZE)
		{
			mapX = startX / TILE_SIZE;

			for (x = x1; x < x2; x += TILE_SIZE)
			{
				//Si la tile � dessiner n'est pas une tile vide
				if (tile2[mapY][mapX] != 0)
				{


					/*On teste si c'est une tile plateforme flottante */
					if (tile2[mapY][mapX] >= TILE_PLATEFORME_DEBUT
						&& tile2[mapY][mapX] <= TILE_PLATEFORME_FIN)
					{
						//On initialise une plateforme flottante
						//Pour obtenir le type (dernier arg), on enl�ve le num�ro de la 1�re tile plateforme
						//(TILE_PLATEFORME_DEBUT) au num�ro de la til en cours (map.tile[mapY][mapX])
						//et on rajoute 1 pour que le premier type soit le 1 et pas le 0 ;)
						initPlateforme(mapX * TILE_SIZE, mapY * TILE_SIZE, tile2[mapY][mapX] - TILE_PLATEFORME_DEBUT + 1);
						//Et on efface cette tile de notre tableau pour �viter un spawn de plateformes
						//infini !
						tile2[mapY][mapX] = 0;
					}
				}

				/* Suivant le num�ro de notre tile, on d�coupe le tileset (a = le num�ro
				de la tile */
				a = tile2[mapY][mapX];

				/* Calcul pour obtenir son y (pour un tileset de 10 tiles
				par ligne, d'o� le 10 */
				ysource = a / 10 * TILE_SIZE;
				/* Et son x */
				xsource = a % 10 * TILE_SIZE;

				/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
				if (tileSetNumber == 0)
					drawTile(tileSet, x, y, xsource, ysource);
				else
					drawTile(tileSetB, x, y, xsource, ysource);

				mapX++;
			}
			mapY++;
		}
	}

	else if (layer == 3)
	{
		//Troisi�me couche de tiles ;)
		for (y = y1; y < y2; y += TILE_SIZE)
		{
			mapX = startX / TILE_SIZE;

			for (x = x1; x < x2; x += TILE_SIZE)
			{
				//Si la tile � dessiner n'est pas une tile vide
				if (tile3[mapY][mapX] != 0)
				{


					/*On teste si c'est une tile plateforme flottante */
					if (tile3[mapY][mapX] >= TILE_PLATEFORME_DEBUT
						&&tile3[mapY][mapX] <= TILE_PLATEFORME_FIN)
					{
						//On initialise une plateforme flottante
						//Pour obtenir le type (dernier arg), on enl�ve le num�ro de la 1�re tile plateforme
						//(TILE_PLATEFORME_DEBUT) au num�ro de la til en cours (map.tile[mapY][mapX])
						//et on rajoute 1 pour que le premier type soit le 1 et pas le 0 ;)
						initPlateforme(mapX * TILE_SIZE, mapY * TILE_SIZE, tile3[mapY][mapX] - TILE_PLATEFORME_DEBUT + 1);
						//Et on efface cette tile de notre tableau pour �viter un spawn de plateformes
						//infini !
						tile3[mapY][mapX] = 0;
					}
				}

				/* Suivant le num�ro de notre tile, on d�coupe le tileset (a = le num�ro
				de la tile */
				a = tile3[mapY][mapX];

				/* Calcul pour obtenir son y (pour un tileset de 10 tiles
				par ligne, d'o� le 10 */
				ysource = a / 10 * TILE_SIZE;
				/* Et son x */
				xsource = a % 10 * TILE_SIZE;

				/* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
				if (tileSetNumber == 0)
					drawTile(tileSet, x, y, xsource, ysource);
				else
					drawTile(tileSetB, x, y, xsource, ysource);

				mapX++;
			}
			mapY++;
		}
	}
}

void Map::changeLevel() //Attention � cette fonction, regarder pour ouverture fichier
{
	char file[200];

	/* Charge la map depuis le fichier */
	//Regarder comment faire appel au fichier en C++
	sprintf_s(file, sizeof(file), "map/map%d.txt", getLevel());
	loadMap(file);

	//Charge le tileset
	if (tileSet != NULL)
	{
		SDL_DestroyTexture(tileSet);
	}
	if (tileSetB != NULL)
	{
		SDL_DestroyTexture(tileSetB);
	}

	sprintf_s(file, sizeof(file), "graphics/tileset%d.png", tilesetAffiche);
	tileSet = loadImage(file);

	sprintf_s(file, sizeof(file), "graphics/tileset%dB.png", tilesetAffiche);
	tileSetB = loadImage(file);
}

void Map::cleanMaps()
{
	// Lib�re la texture du background 
	if (background != NULL)
	{
		SDL_DestroyTexture(background);
		background = NULL;
	}

	// Lib�re les textures des tilesets 
	if (tileSet != NULL)
	{
		SDL_DestroyTexture(tileSet);
		tileSet = NULL;
	}

	if (tileSetB != NULL)
	{
		SDL_DestroyTexture(tileSetB);
		tileSetB = NULL;
	}
}

void Map::mapCollision(GameObject * entity)
{
	int i, x1, x2, y1, y2;

	/* D'abord, on consid�re le joueur en l'air jusqu'� temps
	d'�tre s�r qu'il touche le sol */
	entity->onGround = 0;

	/* Ensuite, on va tester les mouvements horizontaux en premier
	(axe des X). On va se servir de i comme compteur pour notre boucle.
	En fait, on va d�couper notre sprite en blocs de tiles pour voir
	quelles tiles il est susceptible de recouvrir.
	On va donc commencer en donnant la valeur de Tile_Size � i pour qu'il
	teste la tile o� se trouve le x du joueur mais aussi la suivante SAUF
	dans le cas o� notre sprite serait inf�rieur � 	la taille d'une tile.
	Dans ce cas, on lui donnera la vraie valeur de la taille du sprite
	Et on testera ensuite 2 fois la m�me tile. Mais comme �a notre code
	sera op�rationnel quelle que soit la taille de nos sprites ! */

	if (entity->h > TILE_SIZE)
		i = TILE_SIZE;
	else
		i = entity->h;


	//On lance alors une boucle for infinie car on l'interrompra selon 
	//les r�sultats de nos calculs
	for (;;)
	{
		//On va calculer ici les coins de notre sprite � gauche et � 
		//droite pour voir quelle tile ils touchent.
		x1 = (entity->x + entity->dirX) / TILE_SIZE;
		x2 = (entity->x + entity->dirX + entity->w - 1) / TILE_SIZE;

		//M�me chose avec y, sauf qu'on va monter au fur et � mesure 
		//pour tester toute la hauteur de notre sprite, gr�ce � notre 
		//fameuse variable i.
		y1 = (entity->y) / TILE_SIZE;
		y2 = (entity->y + i - 1) / TILE_SIZE;

		//De l�, on va tester les mouvements initi�s dans updatePlayer 
		//gr�ce aux vecteurs dirX et dirY, tout en testant avant qu'on 
		//se situe bien dans les limites de l'�cran.
		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			//Si on a un mouvement � droite
			if (entity->dirX > 0)
			{

				//Test des tiles Power-up
				if (map.tile[y1][x2] >= TILE_POWER_UP_DEBUT
					&& map.tile[y1][x2] <= TILE_POWER_UP_FIN)
				{
					//On appelle la fonction getItem()
					getItem(map.tile[y1][x2] - TILE_POWER_UP_DEBUT + 1);

					//On remplace la tile power-up par une tile transparente
					map.tile[y1][x2] = 0;
				}
				else if (map.tile[y2][x2] >= TILE_POWER_UP_DEBUT
					&& map.tile[y2][x2] <= TILE_POWER_UP_FIN)
				{
					//On appelle la fonction getItem()
					getItem(map.tile[y2][x2] - TILE_POWER_UP_DEBUT + 1);

					//On remplace la tile power-up par une tile transparente
					map.tile[y2][x2] = 0;
				}


				//Test de la tile checkpoint
				if (map.tile[y1][x2] == TILE_CHECKPOINT)
				{
					//On active le bool�en checkpoint
					entity->checkpointActif = 1;

					//On enregistre les coordonn�es
					entity->respawnX = x2 * TILE_SIZE;
					entity->respawnY = (y1 * TILE_SIZE) - entity->h;

					//On change la tile
					map.tile[y1][x2] += 1;
				}
				else if (map.tile[y2][x2] == TILE_CHECKPOINT)
				{
					//On active le bool�en checkpoint
					entity->checkpointActif = 1;

					//On enregistre les coordonn�es
					entity->respawnX = x2 * TILE_SIZE;
					entity->respawnY = (y2 * TILE_SIZE) - entity->h;

					//On change la tile
					map.tile[y2][x2] += 1;
				}


				//On v�rifie si les tiles recouvertes sont solides
				if (map.tile[y1][x2] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
				{
					// Si c'est le cas, on place le joueur aussi pr�s que possible
					// de ces tiles, en mettant � jour ses coordonn�es. Enfin, on 
					//r�initialise son vecteur d�placement (dirX).

					entity->x = x2 * TILE_SIZE;
					entity->x -= entity->w + 1;
					entity->dirX = 0;

				}
			}

			//M�me chose � gauche
			else if (entity->dirX < 0)
			{

				//Test des tiles Power-up : Etoile et vie
				if (map.tile[y1][x1] >= TILE_POWER_UP_DEBUT
					&& map.tile[y1][x1] <= TILE_POWER_UP_FIN)
				{
					//On appelle la fonction getItem()
					getItem(map.tile[y1][x1] - TILE_POWER_UP_DEBUT + 1);

					//On remplace la tile power-up par une tile transparente
					map.tile[y1][x1] = 0;
				}
				else if (map.tile[y2][x1] >= TILE_POWER_UP_DEBUT
					&& map.tile[y2][x1] <= TILE_POWER_UP_FIN)
				{
					//On appelle la fonction getItem()
					getItem(map.tile[y2][x1] - TILE_POWER_UP_DEBUT + 1);

					//On remplace la tile power-up par une tile transparente
					map.tile[y2][x1] = 0;
				}

				//Test de la tile checkpoint
				if (map.tile[y1][x1] == TILE_CHECKPOINT)
				{
					//On active le bool�en checkpoint
					entity->checkpointActif = 1;

					//On enregistre les coordonn�es
					entity->respawnX = x1 * TILE_SIZE;
					entity->respawnY = (y1 * TILE_SIZE) - entity->h;

					//On change la tile
					map.tile[y1][x1] += 1;
				}
				else if (map.tile[y2][x1] == TILE_CHECKPOINT)
				{
					//On active le bool�en checkpoint
					entity->checkpointActif = 1;

					//On enregistre les coordonn�es
					entity->respawnX = x1 * TILE_SIZE;
					entity->respawnY = (y2 * TILE_SIZE) - entity->h;

					//On change la tile
					map.tile[y2][x1] += 1;
				}


				if (map.tile[y1][x1] > BLANK_TILE || map.tile[y2][x1] > BLANK_TILE)
				{
					entity->x = (x1 + 1) * TILE_SIZE;
					entity->dirX = 0;
				}

			}

		}

		//On sort de la boucle si on a test� toutes les tiles le long de la hauteur du sprite.
		if (i == entity->h)
		{
			break;
		}

		//Sinon, on teste les tiles sup�rieures en se limitant � la heuteur du sprite.
		i += TILE_SIZE;

		if (i > entity->h)
		{
			i = entity->h;
		}
	}

	//On recommence la m�me chose avec le mouvement vertical (axe des Y)
	if (entity->w > TILE_SIZE)
		i = TILE_SIZE;
	else
		i = entity->w;


	for (;;)
	{
		x1 = (entity->x) / TILE_SIZE;
		x2 = (entity->x + i) / TILE_SIZE;

		y1 = (entity->y + entity->dirY) / TILE_SIZE;
		y2 = (entity->y + entity->dirY + entity->h) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (entity->dirY > 0)
			{
				/* D�placement en bas */

				//Test des tiles Power-up)
				if (map.tile[y2][x1] >= TILE_POWER_UP_DEBUT
					&& map.tile[y2][x1] <= TILE_POWER_UP_FIN)
				{
					//On appelle la fonction getItem()
					getItem(map.tile[y2][x1] - TILE_POWER_UP_DEBUT + 1);

					//On remplace la tile power-up par une tile transparente
					map.tile[y2][x1] = 0;
				}
				else if (map.tile[y2][x2] >= TILE_POWER_UP_DEBUT
					&& map.tile[y2][x2] <= TILE_POWER_UP_FIN)
				{
					//On appelle la fonction getItem()
					getItem(map.tile[y2][x2] - TILE_POWER_UP_DEBUT + 1);

					//On remplace la tile power-up par une tile transparente
					map.tile[y2][x2] = 0;
				}

				//Test de la tile checkpoint
				if (map.tile[y2][x1] == TILE_CHECKPOINT)
				{
					//On active le bool�en checkpoint
					entity->checkpointActif = 1;

					//On enregistre les coordonn�es
					entity->respawnX = x1 * TILE_SIZE;
					entity->respawnY = (y2 * TILE_SIZE) - entity->h;

					//On change la tile
					map.tile[y2][x1] += 1;
				}
				else if (map.tile[y2][x2] == TILE_CHECKPOINT)
				{
					//On active le bool�en checkpoint
					entity->checkpointActif = 1;

					//On enregistre les coordonn�es
					entity->respawnX = x2 * TILE_SIZE;
					entity->respawnY = (y2 * TILE_SIZE) - entity->h;

					//On change la tile
					map.tile[y2][x2] += 1;
				}


				/* Gestion des pics */
				if ((map.tile[y2][x1] == TILE_PIKES) || (map.tile[y2][x2] == TILE_PIKES))
				{

					//On joue le son
					playSoundFx(DESTROY);
					//On fait sauter le joueur
					entity->dirY = -JUMP_HEIGHT;

					if (entity->life > 1)
					{
						//Si le timer d'invincibilit� est � 0
						//on perd un coeur
						if (entity->invincibleTimer == 0)
						{
							entity->life--;
							entity->invincibleTimer = 80;
						}
					}
					else
					{
						//On met le timer � 1 pour tuer le joueur intantan�ment
						entity->timerMort = 1;
						//On joue le son
						playSoundFx(DESTROY);
					}
				}

				/* Gestion du ressort */
				else if ((map.tile[y2][x1] == TILE_RESSORT) || (map.tile[y2][x2] == TILE_RESSORT))
				{
					entity->dirY = -20;
					//On indique au jeu qu'il a atterri pour r�initialiser le double saut
					entity->onGround = 1;
					playSoundFx(BUMPER);
				}


				//Gestion des plateformes traversables : elles se situent juste avant 
				//les tiles bloquantes dans notre tileset (dont la valeur butoire est 
				//BLANK_TILE). Il suffit donc d'utiliser le num�ro de la premi�re tile 
				//traversable au lieu de BLANK_TILE pour bloquer le joueur, 
				//seulement quand il tombe dessus (sinon, il passe au-travers
				//et le test n'est donc pas effectu� dans les autres directions 
				else if (map.tile[y2][x1] > TILE_TRAVERSABLE || map.tile[y2][x2] > TILE_TRAVERSABLE)
				{
					//Si la tile est une plateforme ou une tile solide, on y colle le joueur et
					//on le d�clare sur le sol (onGround).
					entity->y = y2 * TILE_SIZE;
					entity->y -= entity->h;
					entity->dirY = 0;
					entity->onGround = 1;
				}


				// Test de collision avec la plateforme mobile 
				if (getPlateformeNumber > 0)
					checkCollisionsWithPlateforms(entity);

			}

			else if (entity->dirY < 0)
			{

				/* D�placement vers le haut */

				//Test des tiles Power-up 
				if (map.tile[y1][x1] >= TILE_POWER_UP_DEBUT
					&& map.tile[y1][x1] <= TILE_POWER_UP_FIN)
				{
					//On appelle la fonction getItem()
					getItem(map.tile[y1][x1] - TILE_POWER_UP_DEBUT + 1);

					//On remplace la tile power-up par une tile transparente
					map.tile[y1][x1] = 0;
				}
				if (map.tile[y1][x2] >= TILE_POWER_UP_DEBUT
					&& map.tile[y1][x2] <= TILE_POWER_UP_FIN)
				{
					//On appelle la fonction getItem()
					getItem(map.tile[y1][x2] - TILE_POWER_UP_DEBUT + 1);

					//On remplace la tile power-up par une tile transparente
					map.tile[y1][x2] = 0;
				}

				//Test de la tile checkpoint
				if (map.tile[y1][x1] == TILE_CHECKPOINT)
				{
					//On active le bool�en checkpoint
					entity->checkpointActif = 1;

					//On enregistre les coordonn�es
					entity->respawnX = x1 * TILE_SIZE;
					entity->respawnY = (y1 * TILE_SIZE) - entity->h;

					//On change la tile
					map.tile[y1][x1] += 1;
				}
				else if (map.tile[y1][x2] == TILE_CHECKPOINT)
				{
					//On active le bool�en checkpoint
					entity->checkpointActif = 1;

					//On enregistre les coordonn�es
					entity->respawnX = x2 * TILE_SIZE;
					entity->respawnY = (y1 * TILE_SIZE) - entity->h;

					//On change la tile
					map.tile[y1][x2] += 1;
				}


				if (map.tile[y1][x1] > BLANK_TILE || map.tile[y1][x2] > BLANK_TILE)
				{
					entity->y = (y1 + 1) * TILE_SIZE;
					entity->dirY = 0;
				}

			}
		}

		//On teste la largeur du sprite (m�me technique que pour la hauteur pr�c�demment)
		if (i == entity->w)
		{
			break;
		}

		i += TILE_SIZE;

		if (i > entity->w)
		{
			i = entity->w;
		}
	}

	/* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqu� */
	entity->x += entity->dirX;
	entity->y += entity->dirY;

	//Et on contraint son d�placement aux limites de l'�cran.
	if (entity->x < 0)
	{
		entity->x = 0;
	}

	else if (entity->x + entity->w >= map.maxX)
	{
		//Si on touche le bord droit de l'�cran, on passe au niveau sup
		SetValeurDuNiveau(getLevel() + 1);
		//Si on d�passe le niveau max, on annule et on limite le d�placement du joueur
		if (getLevel() > LEVEL_MAX)
		{
			SetValeurDuNiveau(LEVEL_MAX);
			entity->x = map.maxX - entity->w - 1;
		}
		//Sinon, on passe au niveau sup, on charge la nouvelle map et on r�initialise le joueur
		else
		{
			//On d�sactive le checkpoint
			entity->checkpointActif = 0;

			changeLevel();
			initializePlayer(1);
		}
	}

	//Maintenant, s'il sort de l'�cran par le bas (chute dans un trou sans fond), on lance le timer
	//qui g�re sa mort et sa r�initialisation (plus tard on g�rera aussi les vies).
	if (entity->y > map.maxY)
	{
		entity->timerMort = 60;
	}
}
