#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

#define TAILLE_MAX_MOT 100

int main() {
    char choixMenu = '0' ;
    char choixLexique = '0';
    char confirmation = '0';
    char mot[TAILLE_MAX_MOT] = "alphabet";
    t_mot *lexiqueA, *lexiqueB = malloc(sizeof(t_mot));
    lexiqueA = NULL;
    lexiqueB = NULL;

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
        //choixMenu = scanf(" %c", &choixMenu);
        choixMenu = getchar();
        viderBuffer();

        switch (choixMenu) {
            case '1' :
                printf("\nLexique A ou B : ");
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
                printf("\n\n\n\n\n\n\n\n\n\n");
                break;

            case '2' :
                printf("\nEntrez le mot a INSERER : ");
                char input_mot[TAILLE_MAX_MOT]=""; //allocation en mémoire plus claire que *mot
                scanf(" %s", input_mot);
                viderBuffer();
                printf("\nDans A ou B : ");
                choixLexique = getchar();
                viderBuffer();
                switch (choixLexique) {
                    case 'A':
                        lexiqueA = ajouterMot(lexiqueA, input_mot);
                        if (!lexiqueA){printf("Ca marche pas.");}
                        break;
                    case 'B':
                        lexiqueB = ajouterMot(lexiqueB, input_mot);
                        if (!lexiqueB){printf("Ca marche pas.");}
                        break;
                }
                printf("\n\n\n\n\n\n\n\n\n\n");
                break;

            case '3' :
                printf("\nEntrez le mot a RETIRER : ");
                char to_supp[100]=""; //allocation en mémoire plus claire que *mot
                scanf(" %s", to_supp);
                viderBuffer();
                printf("\nDans A ou B : ");
                choixLexique = getchar();
                viderBuffer();
                switch (choixLexique) {
                    case 'A':
                        lexiqueA = retirerMot(lexiqueA, to_supp);
                        break;
                    case 'B':
                        lexiqueB = retirerMot(lexiqueB, to_supp);
                        break;
                }
                printf("\n\n\n\n\n\n\n\n\n\n");
                break;


            case '4' :
                printf("\nLa fusion a lieu dans A, B ou on annule (A/B/N) : ");
                confirmation = getchar();
                viderBuffer();
                switch (confirmation) {
                    case 'A':
                        lexiqueA = fusionner(lexiqueA,lexiqueB);
                        break;
                    case 'B':
                        lexiqueB = fusionner(lexiqueA,lexiqueB);
                        break;
                    case 'N':
                        printf("\n\n\t<FUSION ANNULEE>\n\n");
                        break;
                }
                printf("\n\n\n\n\n\n\n\n\n\n");
                break;


            case '5' :
                printf("\nChargez le fichier dans A ou B : ");
                choixLexique = getchar();
                viderBuffer();
                switch (choixLexique) {
                    case 'A':
                        lexiqueA = importerFichier(lexiqueA);
                        break;
                    case 'B':
                        lexiqueB = importerFichier(lexiqueB);
                        break;
                }
                printf("\n\n\n\n\n\n\n\n\n\n");

                break;
        }
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
