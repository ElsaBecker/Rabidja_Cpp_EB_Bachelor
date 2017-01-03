#pragma once

//Structure pour gérer l'affichage des sprites
class GameObject
{

	//Données membres
	// Points de vie/santé + chrono d'invicibilité
	int life, invincibleTimer;

	// Coordonnées du sprite
	int x, y;

	// Largeur, hauteur du sprite 
	int h, w;

	// Checkpoint pour le héros (actif ou non)
	int checkpointActif;
	// + coordonnées de respawn (réapparition)
	int respawnX, respawnY;


	// Variables utiles pour l'animation :
	// Numéro de la frame (= image) en cours + timer
	int frameNumber, frameTimer, frameMax;
	// Nombre max de frames, état du sprite et direction
	//   dans laquelle il se déplace (gauche / droite)
	int etat, direction;


	// Variables utiles pour la gestion des collisions :
	//Est-il sur le sol, chrono une fois mort
	int onGround, timerMort;
	//Vecteurs de déplacement temporaires avant détection
	//des collisions avec la map
	float dirX, dirY;
	//Sauvegarde des coordonnées de départ
	int saveX, saveY;

	//Variable pour le double saut
	int jump;

	//Variables pour gérer les plateformes flottantes
	//Coordonnées de départ
	int beginX, beginY;
	// Type de plateforme (horizontale ou verticale)
	// Le joueur est-il dessus ?
	int type, player_dessus;

public:
	GameObject();
	~GameObject();
};

