/*******************************************************************
 Nom ET Prénom : ANSUMDINE SAID
 L2 Informatique
 UE langage C avancé
 
 *******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "tpimage.h"

int main(int argc, char *argv[]) {
    int vrai = 1;
    int h,l ;
    tImCouleurP3 tP3;
    tImGrisP2 tP2;
    tImGrisP2 tP4;
    tASCIIArt tAS;
    char fichier[30];
    char fichier1 [30];
    int choix;
    
    do {
        printf("Quelle operation voulez-vous effectuer ?\n");
        printf("1. Charger une image couleur en memoire\n");
        printf("2. Sauver une image couleur\n");
        printf("3. Transformer une image couleur en niveau de gris\n");
        printf("4. Charger une image en niveau de gris en memoire\n");
        printf("5. Sauver une image en niveau de gris\n");
        printf("6. Pixeliser une image en niveau de gris\n");
        printf("7. Creer un ASCII Art a partir d'une image en niveau de gris\n");
        printf("8. Sauver un ASCII Art\n");
        printf("0. Quitter\n");
        printf("Choix ==>\n");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                printf("Ecris le nom de l'image et son extension\n");
                scanf("%s", fichier);
                tP3 = chargePPM(fichier);
                break;
            case 2:
                printf("Ecris le nom du nouveau image et son extension\n");
                scanf("%s", fichier1);
                sauvePPM(fichier1, tP3);
                break;
            case 3:
                printf("Ecris le nom de l'image couleur et son extension\n");
                scanf("%s", fichier);
                tP3 = chargePPM(fichier);
                tP2 = niveauGris(tP3);
                break;
            case 4:
                printf("Ecris le nom de l'image et son extension\n");
                scanf("%s", fichier);
                tP2 = chargePGM(fichier);
                break;
            case 5:
                printf("Ecris le nom du nouveau image gris et son extension\n");
                scanf("%s", fichier1);
                sauvePGM(fichier1, tP2);
                break;
            case 6:
                printf("Donner la hauteur de chaque pave du pixel\n");
                scanf("%d", &h);
                printf("Donner la largeur de chaque pave du pixel\n");
                scanf("%d", &l);
                printf("Donner le nom et l'extension de l'image gris a pixeliser\n");
                scanf("%s", fichier);
                tP2 = chargePGM(fichier);
                tP2 = pixelise(tP2, h, l);
                break;
            case 7:
                printf("Donner l'image a convertir en ASCCI Art\n ");
                scanf("%s", fichier);
                tP2 = chargePGM(fichier);
                printf("Donner la hauteur de chaque pave à convertir en ASCII\n");
                scanf("%d", &h);
                printf("Donner la largeur de chaque pave à Convertir en ASCII\n");
                scanf("%d", &l);
                tAS = creerAsciiArt(tP2, h, l);
                break;
            case 8:
                printf("Ecris le nom du nouveau image ASCII Art et son extension\n");
                scanf("%s", fichier1);
                sauveASCII(fichier1, tAS);
                break;
            case 0:
                printf("Etes vous sur de quitter?\n");
                printf("Si vous voulez quitter appuyer 0 sinon appuyer 1\n");
                scanf("%d", &vrai);
                break;
                
            default:
                printf("Vous n'avez pas mis un nombre correct\n");
                break;
        }
    } while(vrai);
    
    
    
}