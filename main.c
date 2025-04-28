#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

#define TAILLE_MAX_MOT 50

int main() {
    char mot1[] = "abeille";
    char mot2[] = "arbre";
    char mot3[] = "avion";
    char mot4[] = "bateau";
    char mot5[] = "bulle";
    char mot6[] = "dans";
    char mot7[] = "du";
    t_mot* liste = NULL;


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


    char mot[TAILLE_MAX_MOT];
    t_mot* lexiqueA = NULL;
    t_mot* lexiqueB = NULL;

    char choixFusion = '0';
    char choixLexique = '0';
    char choixMenu = '0' ;


    do {
        printf("\n========================================");
        printf("\n  [1] Afficher un lexique");
        printf("\n  [2] Ajouter un mot dans un lexique");
        printf("\n  [3] Retirer un mot d'un lexique");
        printf("\n  [4] Fusionner deux lexiques");
        printf("\n  [5] Charger un fichier dans un lexique");
        printf("\n  [6] Quitter");
        printf("\n========================================");
        printf("\nVotre choix : ");
        choixMenu = getchar();
        viderBuffer();

        switch (choixMenu) {
            case '1' :
                printf("Affichez A ou B ? ");
                choixLexique = getchar();
                viderBuffer();
                switch (choixLexique) {
                    case 'A':
                        afficherMots(lexiqueA);
                        break;
                    case 'B':
                        afficherMots(lexiqueB);
                        break;
                }
                break;


            case '2' :
                printf("Entrez le mot que vous voulez ajouter : ");
                fgets(mot, TAILLE_MAX_MOT, stdin);
                printf("Ajoutez dans A ou dans B ? ");
                choixLexique = getchar();
                viderBuffer();
                switch (choixLexique) {
                    case 'A':
                        lexiqueA = ajouterMot(lexiqueA, &mot);
                        break;
                    case 'B':
                        lexiqueB = ajouterMot(lexiqueB, &mot);
                        break;
                }
                break;


            case '3' :
                printf("Entrez le mot que vous voulez retirer : ");
                fgets(mot, TAILLE_MAX_MOT, stdin);
                printf("Retirez dans A ou dans B ? ");
                choixLexique = getchar();
                viderBuffer();
                switch (choixLexique) {
                    case 'A':
                        lexiqueA = retirerMot(lexiqueA, &mot);
                        break;
                    case 'B':
                        lexiqueB = retirerMot(lexiqueB, &mot);
                        break;
                }
                break;


            case '4' :
                printf("Voulez-vous vraiment fusionner A et B ? (o/n) ");
                choixFusion = getchar();
                viderBuffer();
                if (choixFusion=='o'){
                    lexiqueA = fusionner(lexiqueA, lexiqueB);
                    libererListe(lexiqueB);
                    lexiqueB = NULL;
                }
                break;


            case '5' :

                break;
        }
    printf("\n\n\n\n\n\n\n\n\n");
    } while (choixMenu != '6');


    printf("\n\n*** FIN DU PROGRAMME ***\n");

    return 0;
}


























/*
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

*/
