#include "init.h"

using namespace std;


init::init()
{
	this->screen = NULL;
	this->renderer = NULL;
}


init::~init()
{

}


SDL_Renderer * init::getrenderer() const
{
	return renderer;
}


void init::initialise(char * title)
{
	/* On cr�e la fen�tre, repr�sent�e par le pointeur jeu.window en utilisant la largeur et la
	hauteur d�finies dans les defines (defs.h).
	Nouveaut�s SDL2 : on peut centrer la fen�tre avec SDL_WINDOWPOS_CENTERED, et choisir la taille
	de la fen�tre, pour que la carte graphique l'agrandisse automatiquement. Notez aussi qu'on peut
	maintenant cr�er plusieurs fen�tres. */

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
	{
		cout << endl;
		cout << "Unable to initialize SDL : " << SDL_GetError() << endl;
		return;
	}

	screen = SDL_CreateWindow(title,
									SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									SCREEN_WIDTH, SCREEN_HEIGHT,
									SDL_WINDOW_SHOWN);
	
	//On cr�e un renderer pour la SDL et on active la synchro verticale : VSYNC
	renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC);

	// Si on n'y arrive pas, on quitte en enregistrant l'erreur dans stdout.txt
	if (screen == NULL || renderer == NULL)
	{
		cout << "Impossible d'initialiser le mode �cran � " << SCREEN_WIDTH << " x "
			<< SCREEN_HEIGHT << " : " << SDL_GetError() << endl;
		exit(1);
	}

	//Initialisation du chargement des images png avec SDL_Image 2
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		cout << "SDL_image n'a pu �tre initialis�e! SDL_image Error: " << IMG_GetError() << endl;
		exit(1);
	}

	//On cache le curseur de la souris 
	SDL_ShowCursor(SDL_DISABLE);

	//On initialise SDL_TTF 2 qui g�rera l'�criture de texte
	if (TTF_Init() < 0)
	{
		cout << "Impossible d'initialiser SDL TTF: " << TTF_GetError() << endl;
		exit(1);
	}

	/* Chargement de la police */
	loadFont("font/GenBasB.ttf", 32);

	//On initialise SDL_Mixer 2, qui g�rera la musique et les effets sonores
	int flags = MIX_INIT_MP3;
	int initted = Mix_Init(flags);
	if ((initted & flags) != flags)
	{
		cout << "Mix_Init: Failed to init SDL_Mixer" << endl;
		cout << "Mix_Init: " << Mix_GetError() ;
		exit(1);
	}

	/* Open 44.1KHz, signed 16bit, system byte order,
	stereo audio, using 1024 byte chunks (voir la doc pour plus d'infos ;) ) */
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		cout << "Mix_OpenAudio: " << Mix_GetError();
		exit(1);
	}

	// D�finit le nombre de pistes audio (channels) � mixer
	Mix_AllocateChannels(32);


	// Initialise le sous-syt�me de la SDL g�rant les joysticks
	SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	//On cherche s'il y a des joysticks
	if (SDL_NumJoysticks() > 0)
	{
		openJoystick();
	}
}


void init::loadGame() const
{
	//On charge les donn�es pour la map
	initMaps();

	//On initialise les menus
	initMenus();



	//On charge la feuille de sprites (spritesheet) de notre h�ros 
	initPlayerSprites();

	//On commence au premier niveau
	SetValeurDuNiveau(1);
	changeLevel();

	/* On initialise les variables du jeu */
	setNombreDeVies(3);
	setNombreDetoiles(0);

	/* On charge le HUD */
	initHUD();


	//On charge notre plateforme
	loadPlateforme();

	//On charge la musique
	loadSong("music/Caviator.mp3");

	/* On charge les sounds Fx */
	loadSound();

	//On commence par le menu start
	setOnMenu(1, START);
}


void init::cleanup()
{
	//Nettoie les sprites de la map et des menus
	cleanMaps();
	cleanMenus();

	/* Lib�re le sprite du h�ros */
	cleanPlayer();



	//Lib�re le HUD
	cleanHUD();

	//Lib�re la plateforme
	cleanPlateforme();

	/* Ferme la prise en charge du joystick */
	closeJoystick();

	/* On lib�re la musique */
	cleanUpMusic();

	//On lib�re les sons
	freeSound();

	//On quitte SDL_Mixer 2 et on d�charge la m�moire
	Mix_CloseAudio();
	Mix_Quit();

	//On fait le m�nage et on remet les pointeurs � NULL
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(screen);
	screen = NULL;

	//On quitte SDL_TTF 2
	TTF_Quit();

	//On quitte la SDL 
	SDL_Quit();
}




/*Draw*/

void init::drawGame(int pauseMenu)
{/*
	// Affiche le fond (background) aux coordonn�es (0,0) 
	drawImage(getBackground(), 0, 0);

	// Affiche la map de tiles : layer 2 (couche du fond) 
	drawMap(2);


	// Affiche la map de tiles : layer 1 (couche active : sol, etc.)
	drawMap(1);

	// Affiche le joueur 
	drawPlayer();


	//Affiche les plateformes flottantes
	drawPlateforme();


	// Affiche la map de tiles : layer 3 (couche en foreground / devant) 
	drawMap(3);

	//On affiche le HUD par-dessus tout le reste
	drawHud();

	//On affiche le menu Pause, si on est en Pause
	if (pauseMenu)
		drawPauseMenu();

	// Affiche l'�cran 
	SDL_RenderPresent(getrenderer());

	// D�lai pour laisser respirer le proc 
	SDL_Delay(1);*/
}

SDL_Texture * init::loadImage(char * name)
{
	SDL_Surface *loadedImage = NULL;
	SDL_Texture *texture = NULL;
	loadedImage = IMG_Load(name);

	if (loadedImage != NULL)
	{
		// Conversion de l'image en texture
		texture = SDL_CreateTextureFromSurface(getrenderer(), loadedImage);

		// On se d�barrasse du pointeur vers une surface
		SDL_FreeSurface(loadedImage);
		loadedImage = NULL;
	}
	else
		cout << "L'image n'a pas pu �tre charg�e! SDL_Error : " << SDL_GetError() << endl;

	return texture;
}

void init::drawImage(SDL_Texture * image, int x, int y)
{
	SDL_Rect dest;

	/* R�gle le rectangle � dessiner selon la taille de l'image source */
	dest.x = x;
	dest.y = y;

	/* Dessine l'image enti�re sur l'�cran aux coordonn�es x et y */
	SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(getrenderer(), image, NULL, &dest);
}

void init::drawImagePlus(SDL_Texture * image, int x, int y, double rotation, SDL_Point center, SDL_RendererFlip flip)
{
	//Nouvelle fonction en SDL2 qui g�re le flip et les rotations

	SDL_Rect dest;

	/* R�gle le rectangle � dessiner selon la taille de l'image source */
	dest.x = x;
	dest.y = y;

	/* Dessine l'image enti�re sur l'�cran aux coordonn�es x et y */
	SDL_QueryTexture(image, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopyEx(getrenderer(), image, NULL, &dest, rotation, &center, flip);
}

void init::drawTile(SDL_Texture * image, int destx, int desty, int srcx, int srcy)
{
	/* Rectangle de destination � dessiner */
	SDL_Rect dest;

	dest.x = destx;
	dest.y = desty;
	dest.w = TILE_SIZE;
	dest.h = TILE_SIZE;

	/* Rectangle source */
	SDL_Rect src;

	src.x = srcx;
	src.y = srcy;
	src.w = TILE_SIZE;
	src.h = TILE_SIZE;

	/* Dessine la tile choisie sur l'�cran aux coordonn�es x et y */
	SDL_RenderCopy(getrenderer(), image, &src, &dest);
}

void init::delay(unsigned int frameLimit)
{
	// Gestion des 60 fps (images/stories/seconde)
	unsigned int ticks = SDL_GetTicks();

	if (frameLimit < ticks)
	{
		return;
	}

	if (frameLimit > ticks + 16)
	{
		SDL_Delay(16);
	}

	else
	{
		SDL_Delay(frameLimit - ticks);
	}
}

void init::drawHud(void)
{/*
	//On cr�e une varuiable qui contiendra notre texte (jusqu'� 200 caract�res, y'a de la marge ;) ).
	char text[200];

	int i;

	//Affiche le nombre de coeurs
	//On cr�e une boucle pour afficher de 1 � 3 coeurs
	//selon la vie, avec un d�calage de 32 pixels
	for (i = 0; i < getLife(); i++)
	{
		// Calcul pour d�couper le tileset comme dans la fonction drawMap()
		int ysource = TILE_POWER_UP_COEUR / 10 * TILE_SIZE;
		int xsource = TILE_POWER_UP_COEUR % 10 * TILE_SIZE;

		drawTile(getTileSetA(), 60 + i * 32, 20, xsource, ysource);
	}

	//Affiche le nombre de vies en bas � droite - Adaptation � la fen�tre auto 
	drawImage(HUD_vie, SCREEN_WIDTH - 120, SCREEN_HEIGHT - 70);

	//Pour afficher le nombre de vies, on formate notre string pour qu'il prenne la valeur de la variable
	//sprintf(text, "x %d", getNombreDeVies());   //Version d�pr�ci�e remplac�e par :
	sprintf_s(text, sizeof(text), "x %d", getNombreDeVies());


	//Puis on utilise notre fonction cr��e pr�c�demment pour �crire en noir (0, 0, 0, 255)
	//et en blanc (255, 255, 255, 255) afin de surligner le texte et de le rendre plus
	//visible
	drawString(text, SCREEN_WIDTH - 80, SCREEN_HEIGHT - 60, 0, 0, 0, 255);
	drawString(text, SCREEN_WIDTH - 82, SCREEN_HEIGHT - 62, 255, 255, 255, 255);

	//Affiche le nombre d'�toiles en haut � gauche //
	drawImage(HUD_etoiles, 60, 60);

	sprintf_s(text, sizeof(text), "%d", getNombreDetoiles());
	drawString(text, 100, 57, 0, 0, 0, 255);
	drawString(text, 98, 55, 255, 255, 255, 255);*/
}

void init::initHUD(void)
{
	/* On charge les images du HUD */
	HUD_vie = loadImage("graphics/life.png");
	HUD_etoiles = loadImage("graphics/stars.png");
}

void init::cleanHUD(void)
{
	if (HUD_etoiles != NULL)
	{
		SDL_DestroyTexture(HUD_etoiles);
	}
	if (HUD_vie != NULL)
	{
		SDL_DestroyTexture(HUD_vie);
	}
}




/*Font*/

void init::loadFont(char * name, int size)
{
	/* Use SDL_TTF pour charger la police */

	font = TTF_OpenFont(name, size);

	if (font == NULL)
	{
		cout << "Failed to open Font " << name << " : " << TTF_GetError() << endl;
		exit(1);
	}
}

void init::closeFont()
{
	/* Ferme police */

	if (font != NULL)
	{
		TTF_CloseFont(font);
	}
}

void init::drawString(char * text, int x, int y, int r, int g, int b, int a)
{
	SDL_Rect dest;
	SDL_Surface *surface; //Pour �crire le texte
	SDL_Texture *texture; //Pour convertir la surface en texture
	SDL_Color foregroundColor;

	/* Couleur du texte RGBA */
	foregroundColor.r = r;
	foregroundColor.g = g;
	foregroundColor.b = b;
	foregroundColor.a = a;


	/* On utilise SDL_TTF pour g�n�rer une SDL_Surface � partir d'une cha�ne de caract�res (string) */
	surface = TTF_RenderUTF8_Blended(font, text, foregroundColor);

	if (surface != NULL)
	{
		/* NOUS MODIFIONS QUELQUE PEU NOTRE CODE POUR PROFITER DE LA MEMOIRE GRAPHIQUE
		QUI GERE LES TEXTURES  */
		// Conversion de l'image en texture
		texture = SDL_CreateTextureFromSurface(getrenderer(), surface);

		// On se d�barrasse du pointeur vers une surface
		/* On lib�re la SDL_Surface temporaire (pour �viter les fuites de m�moire - cf. chapitre
		d�di�) */
		SDL_FreeSurface(surface);
		surface = NULL;

		// On dessine cette texture � l'�cran 
		dest.x = x;
		dest.y = y;

		SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
		SDL_RenderCopy(getrenderer(), texture, NULL, &dest);

		//On supprime la texture
		SDL_DestroyTexture(texture);

	}
	else
	{
		cout << "La chaine n'a pu �tre �crite " << text << " : " << TTF_GetError() << endl;
		exit(0);
	}
}
