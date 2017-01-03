#pragma once

//Structure pour g�rer l'affichage des sprites
class GameObject
{

	//Donn�es membres
	// Points de vie/sant� + chrono d'invicibilit�
	int life, invincibleTimer;

	// Coordonn�es du sprite
	int x, y;

	// Largeur, hauteur du sprite 
	int h, w;

	// Checkpoint pour le h�ros (actif ou non)
	int checkpointActif;
	// + coordonn�es de respawn (r�apparition)
	int respawnX, respawnY;


	// Variables utiles pour l'animation :
	// Num�ro de la frame (= image) en cours + timer
	int frameNumber, frameTimer, frameMax;
	// Nombre max de frames, �tat du sprite et direction
	//   dans laquelle il se d�place (gauche / droite)
	int etat, direction;


	// Variables utiles pour la gestion des collisions :
	//Est-il sur le sol, chrono une fois mort
	int onGround, timerMort;
	//Vecteurs de d�placement temporaires avant d�tection
	//des collisions avec la map
	float dirX, dirY;
	//Sauvegarde des coordonn�es de d�part
	int saveX, saveY;

	//Variable pour le double saut
	int jump;

	//Variables pour g�rer les plateformes flottantes
	//Coordonn�es de d�part
	int beginX, beginY;
	// Type de plateforme (horizontale ou verticale)
	// Le joueur est-il dessus ?
	int type, player_dessus;

public:
	GameObject();
	~GameObject();
};

