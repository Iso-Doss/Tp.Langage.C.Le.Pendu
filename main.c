#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "main.h"

int main(int argc, char* argv[]){

    int nombreCoups = 10;
    char motSecret[TAILLE_MAX] = {0}, *motTrouver = NULL, continuePartie = ' ';

    printf("Bienvenue dans le Pendu !\n\n");

    switch(menuModeJoueur()){
        case 1:
            do{
                printf("\n");
                nombreCoups = 10;
                if (!piocherMot(motSecret))
                    exit(0);

                motTrouver = malloc(sizeof(char)*strlen(motSecret));
                if (motTrouver == NULL){
                    exit(0);
                }

                genererEtoile(motSecret, motTrouver);

                do{
                    printf("Il vous reste %d coups a jouer\n", nombreCoups);
                    printf("Quel est le mot secret ? %s\n", motTrouver);
                    if(strcmp(motSecret, motTrouver) != 0)
                        printf("Proposez une lettre : ");
                    if(!verifierCaratere(motSecret, motTrouver, lireCaractere()))
                        nombreCoups--;

                    printf("\n");

                }
                while( nombreCoups != 0 && strcmp(motSecret, motTrouver) != 0);

                gagne(motSecret, motTrouver);

                printf("Voulez vous vontinuer? O = Oui / N = Non : ");
                continuePartie = lireCaractere();
                system("cls");//printf("\n");
                free(motTrouver);

            }
            while(continuePartie != 'N');
        break;

        case 2:
        break;

        default:
            printf("Mauvais choix");
        }

    return 0;
}

/**
  * La fonction qui permet de lire le premire caractere de la proposition de l'utilisateur
  * Ce dernier est mit en majuscule pour evité les conflit ente le miniscule et le majuscule
  */
char lireCaractere(){
    char caractere = 0;

    // On lit le premier caractère
    caractere = getchar();

    // On met la lettre en majuscule si elle ne l'est pas déjà
    caractere = toupper(caractere);

    // On lit les autres caractères mémorisés un à un jusqu'au \n (pour les effacer)
    while (getchar() != '\n') ;

    // On retourne le premier caractère qu'on a lu
    return caractere;
}

/**
  * La fonction qui permet generer une chaine de caractere contenant que des * de la taille du mot a deviner
  * La fonction effectuer dans un premier temps une allocation dynamique de la variable contenant la chaine "******"
  * On verifie si l'allocation à ete faite avec success
  * Si oui on parcour la variable fraichement crée a l'aide d'une boucle for et en insearant * dans chaque case et \0 a la fon
  */
void genererEtoile(char motSecret[], char motCacher[]){
    int taille = strlen(motSecret)+1, i = 0;

    for(i = 0; i < taille; i++){
        if(i == taille - 1)
            motCacher[i] = '\0';
        else
            motCacher[i] = '*';
    }
}

/**
  * La fonction qui permet de de verifier si la proposition de l'utilisateur "le caractere proposé"
  * fais partir des lettre du mot à deviviner. Si oui alors cette lettre est devoilé
  */
int verifierCaratere(char motSecret[], char motTrouver[], char caratere){
    int taille = strlen(motSecret), i = 0, verifierCaratere = 0;

    for(i = 0; i < taille; i++){
        if(motSecret[i] == caratere){
            motTrouver[i] = caratere;
            verifierCaratere = 1;
        }
    }
    return verifierCaratere;
}

void gagne(char motSecret[], char motTrouver[]){
    if (strcmp(motSecret, motTrouver))
        printf("Perdu ! Le mot secret etait : %s\n", motSecret);
    else
        printf("Gagne ! Le mot secret etait bien : %s\n", motSecret);
}

int piocherMot(char *motPioche)
{
    FILE* dico = NULL; // Le pointeur de fichier qui va contenir notre fichier
    int nombreMots = 0, numMotChoisi = 0;
    int caractereLu = 0;
    dico = fopen("dico.txt", "r"); // On ouvre le dictionnaire en lecture seule

    // On vérifie si on a réussi à ouvrir le dictionnaire
    if (dico == NULL) // Si on n'a PAS réussi à ouvrir le fichier
    {
        printf("\nImpossible de charger le dictionnaire de mots");
        return 0; // On retourne 0 pour indiquer que la fonction a échoué
        // À la lecture du return, la fonction s'arrête immédiatement.
    }

    // On compte le nombre de mots dans le fichier (il suffit de compter les
    // entrées \n
    do
    {
        caractereLu = fgetc(dico);
        if (caractereLu == '\n')
            nombreMots++;
    } while(caractereLu != EOF);

    numMotChoisi = nombreAleatoire(nombreMots); // On pioche un mot au hasard

    // On recommence à lire le fichier depuis le début. On s'arrête lorsqu'on est arrivé au bon mot
    rewind(dico);
    while (numMotChoisi > 0)
    {
        caractereLu = fgetc(dico);
        if (caractereLu == '\n')
            numMotChoisi--;
    }

    /* Le curseur du fichier est positionné au bon endroit.
    On n'a plus qu'à faire un fgets qui lira la ligne */
    fgets(motPioche, 100, dico);

    // On vire le \n à la fin
    motPioche[strlen(motPioche) - 1] = '\0';
    fclose(dico);

    return 1; // Tout s'est bien passé, on retourne 1
}

int nombreAleatoire(int nombreMax)
{
    srand(time(NULL));
    return (rand() % nombreMax);
}

int menuModeJoueur()
{
    int choix = 0;

    while (choix < 1 || choix > 2)
    {
        printf("Menu Mode Joueur:\n");
        printf("1. Mode 1 Joueur\n");
        printf("2. Mode 2 Joueurs\n");
        printf("Votre choix ? ");
        scanf("%d",&choix);
        if(choix < 1 || choix > 2){
            printf("Mauvais choix. Veuillez reesayer en choisissant l'option 1 ou 2\n");
        }
    }

    return choix;
}
