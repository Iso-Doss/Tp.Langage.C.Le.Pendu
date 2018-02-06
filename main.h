#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define TAILLE_MAX 100

char lireCaractere();

void genererEtoile(char motSecret[], char motCacher[]);

int verifierCaratere(char motSecret[], char motTrouver[], char caratere);

void gagne(char motSecret[], char motTrouver[]);

int piocherMot(char *motPioche);

int nombreAleatoire(int nombreMax);

int menuModeJoueur();

#endif // MAIN_H_INCLUDED
