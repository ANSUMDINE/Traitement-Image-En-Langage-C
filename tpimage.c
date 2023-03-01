/*******************************************************************
 Nom ET Prénom : ANSUMDINE SAID
 L2 Informatique
 UE langage C avancé
 
 *******************************************************************/

#include <stdio.h>
#include <stdlib.h>
//
//  tpimage.c
//  cctpCavance22
//
//  Corrige partie 1
//
#include "tpimage.h"




// -------------------------------------------
// initImCouleur : effectue l'allocation memoire necessaire pour une image de haut x larg pixels
// le type et la valeur maximale ne sont pas initialisea a 0 par defaut
// -------------------------------------------


tImCouleurP3 initImCouleur(int haut, int larg, int maxval){
    tImCouleurP3 im;
    im.hauteur = haut;
    im.largeur = larg;
    im.maxval = maxval;
    
    im.tabpix = malloc(haut * sizeof(tPixel *));
    for(int i=0; i<haut; i++){
        im.tabpix[i]= malloc(larg * sizeof(tPixel));
    }
    return im;
}




// -------------------------------------------
// copieImage : retourne une copie de l'image donnee en parametre
// -------------------------------------------

tImCouleurP3 copieImCouleur(tImCouleurP3 im){
    
    tImCouleurP3 copie = initImCouleur(im.hauteur, im.largeur, im.maxval);
    
    for(int i=0; i<im.hauteur; i++){
        for(int j=0; j<im.largeur;j++)
            copie.tabpix[i][j] = im.tabpix[i][j];
    }
    
    return copie;
    
}





// -------------------------------------------
// initImGris : effectue l'allocation memoire necessaire pour une imgris de haut x larg pixels
// le type et la valeur maximale ne sont initialisea a 0 par defaut
// -------------------------------------------

tImGrisP2 initImGris(int haut, int larg, int maxval){
    tImGrisP2 img;
    img.hauteur = haut;
    img.largeur = larg;
    img.maxval = maxval;
    
    img.tabgris = malloc(haut * sizeof(int *));
    for(int i=0; i<haut; i++){
        img.tabgris[i]= malloc(larg * sizeof(int));
    }
    return img;
}




// -------------------------------------------
// copieImGris : retourne une copie de l'image donnee en parametre
// -------------------------------------------

tImGrisP2 copieImGris(tImGrisP2 im){
    
    tImGrisP2 copie = initImGris(im.hauteur, im.largeur, im.maxval);
    
    for(int i=0; i<im.hauteur; i++){
        for(int j=0; j<im.largeur;j++)
            copie.tabgris[i][j] = im.tabgris[i][j];
    }
    return copie;
}





// ************************************************
// chargePPM : charge dans une structure de type tImage
// -------------------------------------------
// l'image contenue dans le fichier donnee en parametre
// Chaque ligne d'un fichier pnm contient au maximum 70 caracteres


tImCouleurP3 chargePPM(char* fichier){
    FILE* flot;
    tImCouleurP3 im;
    char c;
    int h, l, vmax;   // hauteur et largeur, vmax
    char t[3];        // Type de l'image
    
    // Ouverture du fichier texte en lecture
    if ((flot = fopen(fichier, "r")) == NULL){
        fprintf(stderr, "\nErreur dans chargePPM : %s innaccessible", fichier);
        
        return initImCouleur(0, 0, 0);
    };
    
    // Premiere ligne = type de l'image sur 2 caracteres de la forme Px
    fscanf(flot, "%s", t);
    
    // On passe la fin de la ligne
    while((c = fgetc(flot)) != '\n');
    // on passe aussi toutes les lignes commencant par #
    while ((c = fgetc(flot))=='#') {
        while((c = fgetc(flot)) != '\n');
    }
    // On replace dans le flot du fichier le caractère lu qui n'est pas un #
    ungetc(c, flot);
    
    // On recupere la taille de l'image et on fait l'allocation
    fscanf(flot, "%d", &l); // On lit la largeur de l'image
    fscanf(flot, "%d", &h); // On lit la hauteur de l'image
    // On recupere la valeur maxi des pixels
    fscanf(flot, "%d", &vmax);
    im = initImCouleur(h, l, vmax);

    
    // Puis on lit tous les pixels qu'on place dans le tableau
    for (int i=0; i<im.hauteur; i++) {
        for(int j=0; j< im.largeur; j++){
            fscanf(flot, "%i", &(im.tabpix[i][j].r));
            fscanf(flot, "%i", &(im.tabpix[i][j].v));
            fscanf(flot, "%i", &(im.tabpix[i][j].b));
        }
    }
    
    // On ferme le fichier
    fclose(flot);
    // Et on retourne l'image lue
    return im;
}


 





// ************************************************
// sauvePPM :  creer le fichier image pnm  a partir
// de la structure tImage donnee
// -------------------------------------------

void sauvePPM(char* nom, tImCouleurP3 im){
    FILE* flot;
    tPixel unPix;
    // Ouverture du fichier
    if( (flot = fopen(nom, "w")) == NULL){
        fprintf(stderr, "\nErreur dans sauvePPM : impossible de creer le fichier %s", nom);
        return;
    }
    // On ecrit d'abord le type de l'image
    fprintf(flot, "%s\n", "P3");
    
    // On ecrit une ligen de commentaire pour indiquer le createur
    fprintf(flot, "# CREATOR : devoir de langage C\n");
    
    // On ecrit les dimensions de l'image
    fprintf(flot, "%d %d\n", im.largeur, im.hauteur);
    
    // Puis la valeur maxi des pixels
    fprintf(flot, "%d\n", im.maxval);
    
    // On ecrit tous les pixels
    for(int i=0; i<im.hauteur; i++){
        for(int j=0; j<im.largeur; j++){
            unPix = im.tabpix[i][j];
            fprintf(flot, "%d\n", unPix.r);
            fprintf(flot, "%d\n", unPix.v);
            fprintf(flot, "%d\n", unPix.b);
        }
    }
    
    // et on ferme le fichier
    fclose(flot);
}

// -------------------------------------------
// Calcul de la luminance
// -------------------------------------------
/*
 La C.I.E (Commission Internationale de l'ƒclairage) propose, de caracteriser lÕinformation de luminance (la valeur de gris) dÕun pixel par deux formules :
 
 Dans sa recommandation 709, qui concerne les couleurs Ç vraies È ou naturelles :
 Gris = 0.2125 Rouge + 0.7154 Vert + 0.0721 Bleu
 */
float luminance(tPixel p){
    return(0.299*p.r + 0.587*p.v + 0.114*p.b);
}

// retourne une image en niveau de gris créée à partir de l’image couleur donnée en paramètre
tImGrisP2 niveauGris(tImCouleurP3 im)
{
    //On déclare les variables
    tPixel pl;
    tImGrisP2 nGris;
    //On initialise les valeurs de nGris par les variables de im
    nGris = initImGris(im.hauteur, im.largeur, im.maxval);

    // On rempli les valeurs de tabgris
    for (int i = 0; i < im.hauteur; i++)
    {
        for (int j = 0; j < im.largeur; j++)
        {
            pl = im.tabpix[i][j];
            nGris.tabgris[i][j] = (int) luminance(pl);
        }
        
    }
    return nGris;
}

// -------------------------------------------
// Squelette de la fonction sauvePGM qui sauve dans le fihcier nom
// l'image contenue dans la structure tImGrisP2 donnée
// On doit créer un fichier qui respecte rigoureusement le format pgm
// -------------------------------------------

void sauvePGM(char* nom, tImGrisP2 im)
{
    // ** Declaration des variables locales
    
    FILE * flot;
    
    
    // Ouverture du fichier en ecriture
    
    flot = fopen(nom, "w");
    if (flot == NULL)
    {
        fprintf(stderr, "\nsauvePGM: erreur; le fichier est vide");
        return;
    }
    
    
    // On ecrit d'abord le type de l'image P3
    
    fprintf(flot, "%s\n", "P2");
    
    // On ecrit une ligne de commentaire pour indiquer le createur

    fprintf(flot, "# CREATOR : ANSUMDINE SAID\n");
    
    // On ecrit les dimensions de l'image
    
    fprintf(flot, "%d %d\n", im.largeur, im.hauteur);
    
    // Puis la valeur maxi d'intensité des couleurs des pixels
    
    fprintf(flot, "%d\n", im.maxval);
    
    // Ensuite on ecrit tous les pixels (une valeur par ligne) contenus dans le tableau

    for (int j = 0; j < im.hauteur; j++)
    {
        for (int k = 0; k < im.largeur; k++)
        {
            fprintf(flot, "%d\n", im.tabgris[j][k]);
        }
        
    }
    
    
    // et on ferme le fichier
    
    fclose(flot);
}


// fonction permettant de charger une image couleur PGM dans une structure tImGrisP2
tImGrisP2 chargePGM(char* fichier)
{
    // ** Declaration des variables locales
    
    FILE * flot;
    char c;
    tImGrisP2 img;
        
    // ** Ouverture du fichier texte en lecture
    // S'il y a erreur à l'ouverture, retourne une image vide avec le champ img égal à NULL
    
    flot = fopen(fichier, "r");
    if (flot == NULL)
    {
        img.hauteur = 0;
        img.largeur = 0;
        img.maxval = 0;
        fprintf(stderr, "\nchargePGM: erreur; le fichier est vide");
        return img;
    }
    
    
    // ** Première ligne : type de l'image sur 2 caracteres de la forme Px
   
    char tpe[3];
    fscanf(flot, "%s", tpe);
        
    // ** On passe la fin de la 1ere ligne et on se positionne au début de la ligne suivante
    while((c = fgetc(flot)) != '\n');
    // On passe aussi toutes les lignes de commentaire commencant par #
    while ((c = fgetc(flot))=='#') {
        while((c = fgetc(flot)) != '\n');
    }
    ungetc(c, flot);		// Comme on a lu un caractère de trop on le remet dans le flot.
    
    
    // ** On récupère les dimensions de l'image, la valeur maximale de l'intensite des couleurs
    // et on initialise la structure que la fonction doit retourner
    
    int h, l, valmax;
    fscanf(flot, "%d", &l);
    fscanf(flot, "%d", &h);
    fscanf(flot, "%d", &valmax);

    img = initImGris(h, l, valmax);
    
    // ** Puis on lit tous les pixels qu'on place dans le tableau de la structure à retourner

    for (int i = 0; i < img.hauteur; i++)
    {
        for (int j = 0; j < img.largeur; j++)
        {
            fscanf(flot, "%d", &(img.tabgris[i][j]));
        }
        
    }
    
        
    // ** On ferme le fichier et on retourne la structure contenant l'image
    
    fclose(flot);

    return img;
}

//retourne une image en niveaux de gris créée à partir de l’image donnée en paramètre en appliquant l’opèration de pixelisation décrite ci-dessus
tImGrisP2 pixelise(tImGrisP2 im, int h, int l)
{
    // Déclaration des variables locales
    tImGrisP2 img;
    int som = 0;
    int moy ;
    int haut, larg; // haut et larg represente la hauteur et la largeur du nouveau image
    int x = h*l;
    // On cherche la dimension du nouveu image
    haut = (int) im.hauteur / h;
    haut = haut * h;
    larg = (int) im.largeur / l;
    larg = larg * l;

    img = initImGris(haut, larg, im.maxval);
    //On parcours l'image en entier
    int count = 0;
    int cmpt;

    while (count < haut)
    {
        cmpt =0;
        while (cmpt < larg)
        {
        
            // On cherche la moyenne de chaque pavé
            som = 0;
            for (int i = count; i < count + h; i++)
                {
                    for (int j = cmpt; j < cmpt + l; j++)
                    {
                        som = som + im.tabgris[i][j];
                    }
                }
                // On calcul la moyenne du pavé
                moy = (int) som/x;
                // On parcours le nouveau image et on initialise le pavé

                for (int k = count; k < count + h; k++)
                {
                    for (int q = cmpt; q < cmpt + l; q++)
                    {
                        img.tabgris[k][q] = moy;
                    }
            
                }
                // On incrémente cmpt
            cmpt = cmpt + l;
        }
        // On incréménte count
        count = count + h;      
    }
    return img;
}

// retourne un créé à partir de l’image donnée en paramètre en associant à chaque pavé de h × l pixels le caractère correspondant à la moyenne des pixels de ce pavé
tASCIIArt creerAsciiArt(tImGrisP2 im, int h, int l)
{
    // Déclaration des variables
    tASCIIArt imAsciiArt;
    char asci[] = {' ', '.', ',', ':', ';', 'o', 'x', '%', '#', '@'};
    int som = 0; // Somme pour calculer la moyenne
    int moy ; // Moyenne
    int haut, larg; // haut et larg represente la hauteur et la largeur du nouveau image
    int x = h*l;
    int count = 0; // Pour parcourir la hauteur de l'image
    int cmpt ; // Pour parcourir la largeur de l'image

    // On cherche la dimension du nouveu image
    haut = (int) im.hauteur / h;
    haut = haut * h;
    larg = (int) im.largeur / l;
    larg = larg * l;

    // Initialisons l'image en ascii
    imAsciiArt.nbcol = haut;
    imAsciiArt.nblig = larg;
    
     //On alloue en mémoire un espace de type char
    imAsciiArt.tabcar = malloc(haut*sizeof(char*));
    for (int k = 0; k < haut; k++)
    {
        imAsciiArt.tabcar[k] = malloc(larg*sizeof(char));
    }
    // On parcours l'image en entier
    while (count < haut)
    {
        cmpt = 0;
        while (cmpt < larg)
        {
            som = 0;
            for (int i = count; i < count + h; i++)
            {
                for (int j = cmpt; j < cmpt + l; j++)
                {
                    som = som + im.tabgris[i][j];
                }
                
            }
            // On calcul la moyenne du pavé et On cherche sa valeur ascii correspondant
            moy = (int) som/x;
            moy = 255 - moy;
            moy = moy * 10;
            moy = (int) moy/256;

            // On parcours le nouveau image et on initialise le pavé
            for (int p = count; p < count + h; p++)
            {
                for (int t = cmpt; t < cmpt + l; t++)
                {
                    imAsciiArt.tabcar[p][t] = asci[moy];
                }
                
            }
            
            
            cmpt = cmpt + l;
        }
        
        count = count + h;
    }
    return imAsciiArt;
}

// sauve dans un fichier texte dont le nom est donné en argument le tASCIIArt donné
void sauveASCII(char* nom, tASCIIArt art)
{
    // ** Declaration des variables locales
    
    FILE * flot;
    
    
    // Ouverture du fichier en ecriture
    
    flot = fopen(nom, "w");
    if (flot == NULL)
    {
        fprintf(stderr, "\nsauveASCII: erreur; le fichier est vide");
        return;
    }


    for (int j = 0; j < art.nbcol; j++)
    {
        for (int k = 0; k < art.nblig; k++)
        {
            fprintf(flot, "%c", art.tabcar[j][k]);
        }
        printf("\n");
    }
    
    // et on ferme le fichier
    
    fclose(flot);
}
