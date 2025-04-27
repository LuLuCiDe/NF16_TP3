#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

int main() {
    char mot1[] = "abeille";
    char mot2[] = "arbre";
    char mot3[] = "avion";
    char mot4[] = "bateau";
    char mot5[] = "bulle";
    char mot6[] = "dans";
    char mot7[] = "du";
    t_mot* liste;

    // Creation de la liste
    liste = creerMot(&mot1);

    // Ajout des mots au lexique
    // mot en A
    liste = ajouterMot(liste, &mot2);
    liste = ajouterMot(liste, &mot2);
    liste = ajouterMot(liste, &mot2);
    liste = ajouterMot(liste, &mot3);

    // mot en B
    liste = ajouterMot(liste, &mot4);
    liste = ajouterMot(liste, &mot5);
    liste = ajouterMot(liste, &mot5);

    // mot en D
    for (int i=0; i<7; i++){liste = ajouterMot(liste, &mot6);}
    for (int i=0; i<10; i++){liste = ajouterMot(liste, &mot7);}


    // Retrait de mot
    liste = retirerMot(liste, &mot7);


    char motB1[]= "Kaamelott";
    t_mot* listeB = creerMot(&motB1);


    //liste = fusionner(liste, listeB);



    listeB = importerFichier(listeB);

    // Affichage
    afficherMots(listeB);

    libererListe(liste);
    libererListe(listeB);

    return 0;
}


