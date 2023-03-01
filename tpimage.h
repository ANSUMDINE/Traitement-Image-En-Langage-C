/*******************************************************************
 Nom ET Prénom : ANSUMDINE SAID
 L2 Informatique
 UE langage C avancé
 
 *******************************************************************/
#ifndef tpimage_H
#define tpimage_H

#include <stdio.h>
#include <stdlib.h>


// -------------------------------------------
// Definition des types
// -------------------------------------------

/// Le type tPixel pour représenter les niveaux de (rouge, vert, bleu)
typedef struct pixel {
    int r;
    int v;
    int b;
} tPixel;



// Le type tImCouleurP3 pour représenter une image en couleur PPM dans un tableau de pixels
typedef struct imagecouleur {
    int hauteur;        // Hauteur en pixels
    int largeur;        // Largeur en pixels
    int maxval;         // Valeur maximal des niveaux de rouge, vert, bleu d'un pixel
    tPixel** tabpix;       // Le tableau des pixels (tableau de structures de type tPixel)
} tImCouleurP3;



// Le type tImGrisP2 pour représenter une image PGM en mémoire
typedef struct imageGris {
    int hauteur;        // Hauteur en pixels
    int largeur;        // Largeur en pixels
    int maxval;         // Valeur maximal du niveau de gris des pixels
    int** tabgris;      // Tableau des niveaux de gris des pixels
} tImGrisP2;



// Le type tableau ascii art
typedef struct asciiart {
    int nblig;      // nombre de lignes
    int nbcol;      // nombre de colonnes
    char** tabcar;  // le tableau des caractères
} tASCIIArt;



// -------------------------------------------
// Squelette des fonctions 
// -------------------------------------------

extern tImCouleurP3 chargePPM(char* fichier);
extern void sauvePPM(char* nom, tImCouleurP3 im);
extern float luminance(tPixel p);
extern tImCouleurP3 initImCouleur(int haut, int larg, int vmax);
extern tImCouleurP3 copieImCouleur(tImCouleurP3 im);
extern tImGrisP2 initImGris(int haut, int larg, int vmax);
extern tImGrisP2 copieImGris(tImGrisP2 im);
extern tImGrisP2 niveauGris(tImCouleurP3 im);
extern void sauvePGM(char* nom, tImGrisP2 im);
extern tImGrisP2 chargePGM(char* fichier);
extern tImGrisP2 pixelise(tImGrisP2 im, int h, int l);
extern tASCIIArt creerAsciiArt(tImGrisP2 im, int h, int l);
extern void sauveASCII(char* nom, tASCIIArt art);

#endif // !tpimage_H

