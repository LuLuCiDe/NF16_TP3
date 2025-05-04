#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

#define MAX_MOT 30
#define MAX_TITRE 50

int main() {
    //--- Définition variables : ---
    //Liste de tous les lexiques
    lex* liste_lexique = init();

    //Nombre de lexique
    int nb_lexique = 2;

    // ( Les inputs )
    char *input_mot=malloc(MAX_MOT * sizeof(char));
    char *input_titre=malloc(MAX_TITRE * sizeof(char));
    int num_lex = 0;

    lex* lexique_choisi = liste_lexique;

    //Parcoureur de liste de lexiques
    lex* parcours = liste_lexique;
    lex* precedent = liste_lexique;

    //Pour la fusion de lexique
    lex* lexiqueB_choisi = NULL;
    int num_lexB = 0; //pour la selection du lexique à fusionner

    char choixMenu = '0'; //pour la selection d'une action dans le menu

    do {
        printf("\n========================================");
        printf("\n  [1] Afficher un lexique");
        printf("\n  [2] Creer un lexique"); //Pourait être utile à l'utilisateur
        printf("\n  [3] Ajouter un mot dans un lexique");
        printf("\n  [4] Retirer un mot d'un lexique");
        printf("\n  [5] Fusionner deux lexiques");
        printf("\n  [6] Charger un fichier dans un lexique");
        printf("\n  [7] Quitter");
        printf("\n========================================");
        printf("\nVotre choix : ");
        choixMenu = getchar();
        viderBuffer();

        switch (choixMenu) {
            case '1' :
                printf("\n\n==== Affichage des lexiques ====\n\n");

                //On récupère le numéro du lexique à afficher
                afficherTitreLex(liste_lexique);
                lexique_choisi=selectLex(liste_lexique, nb_lexique);

                //On affiche le lexique
                printf("\n_____ *( %s )* _____ \n", lexique_choisi->titre);
                afficherMots(lexique_choisi->liste_mot);
                break;

            case '2' :
                printf("\n\n==== Creation d'un lexique ====\n\n");

                //On prend le titre du nouveau lexique
                printf("\n\n\t<Entrez le titre du nouveau lexique>\n\n");
                scanf(" %s", input_titre);
                viderBuffer();

                //On prend l'input du mot à insérer
                printf("\n\n\t<Entrez le mot du nouveau lexique>\n\n");
                scanf(" %s", input_mot);
                viderBuffer();

                ajouterQueueLex(liste_lexique,creerLex(input_titre,creerMot(input_mot)));
                nb_lexique++;

                //On affiche le résultat
                afficherTitreLex(liste_lexique);
                break;


            case '3' :
                printf("\n\n==== Ajout d'un mot ====\n\n");

                //On récupère le numéro du lexique à modifier
                afficherTitreLex(liste_lexique);
                lexique_choisi=selectLex(liste_lexique, nb_lexique);

                //On prend l'input du mot à insérer
                printf("\n\n\t<Entrez le mot a INSERER dans le lexique '%s'>\n\n", lexique_choisi->titre);
                scanf(" %s", input_mot);
                viderBuffer();

                //On ajoute le mot au lexique sélectionné
                lexique_choisi->liste_mot = ajouterMot(lexique_choisi->liste_mot, input_mot);

                //On affiche le résultat
                printf("\nLe lexique '%s' devient : \n", lexique_choisi->titre);
                afficherMots(lexique_choisi->liste_mot);
                break;


            case '4' :
                printf("\n\n==== Suppression d'un mot ====\n\n");

                //On récupère le numéro du lexique à modifier
                afficherTitreLex(liste_lexique);
                lexique_choisi=selectLex(liste_lexique, nb_lexique);

                //On prend l'input du mot à retirer
                printf("\n\n\t<Entrez le mot a RETIRER dans le lexique '%s'>\n\n", lexique_choisi->titre);
                scanf(" %s", input_mot);
                viderBuffer();

                //On retire le mot du lexique sélectionné
                lexique_choisi->liste_mot = retirerMot(lexique_choisi->liste_mot, input_mot);

                //On affiche le résultat
                printf("\nLe lexique '%s' devient : \n", lexique_choisi->titre);
                afficherMots(lexique_choisi->liste_mot);
                break;


            case '5' :
                printf("\n\n==== Fusion lexique A et lexique B (A+B->A) ====\n\n");

                afficherTitreLex(liste_lexique);

                printf("\n\t<Selection du lexique A>\n");
                lexique_choisi=selectLex(liste_lexique, nb_lexique);

                printf("\n\t<Selection du lexique B>\n");
                lexiqueB_choisi=selectLex(liste_lexique, nb_lexique);

                if (lexiqueB_choisi == liste_lexique) {//Le lexique B est en tête de liste
                    //On supprime le lexique B de la liste (mais on le garde pour la fusion)
                    liste_lexique=liste_lexique->suivant;
                }
                else {//On parcourt les lexiques jusqu'au precedent du lexique B choisi
                    precedent = liste_lexique;
                    while(precedent->suivant != lexiqueB_choisi){
                        precedent=precedent->suivant;
                    }

                    //On supprime le lexique B de la liste (mais on le garde pour la fusion)
                    precedent->suivant=precedent->suivant->suivant;
                }

                //On demande de choisir un nouveau titre
                printf("\n\n\t<Entrez le nouveau titre du lexique>\n\n");
                scanf(" %s", input_titre);
                viderBuffer();

                //On attribue à la liste A la fusion des deux listes et le nouveau titre du lexique
                lexique_choisi->liste_mot=fusionner(lexique_choisi->liste_mot, lexiqueB_choisi->liste_mot);
                lexique_choisi->titre=input_titre;

                //On libère la mémoire du lexique B (mais pas des mots qui étaient présents dans le lexique)
                free(lexiqueB_choisi->titre);
                free(lexiqueB_choisi);

                //On affiche le résultat
                printf("\nLe lexique '%s' devient : \n", lexique_choisi->titre);
                afficherMots(lexique_choisi->liste_mot);
                break;

            case '6' :
                printf("\n\n==== Chargement d'un nouveau lexique ====\n\n");

                //On récupère le numéro du lexique à modifier
                afficherTitreLex(liste_lexique);
                lexique_choisi=selectLex(liste_lexique, nb_lexique);

                lexique_choisi->liste_mot=importerFichier(lexique_choisi->liste_mot);

                //On affiche le résultat
                printf("\nLe lexique '%s' devient : \n", lexique_choisi->titre);
                afficherMots(lexique_choisi->liste_mot);
                break;
        }
    } while (choixMenu != '7');

    //--- Libération mémoire : ---
    //Le programme réalise 4 "types" d'allocation dynamique de mémoire sur les :
    // - t_mot
    // - mots (string)
    // - titres (string)
    // - lexiques

    precedent=liste_lexique;
    parcours=liste_lexique;
    while(parcours!=NULL){
        parcours=precedent->suivant;
        libererListe(precedent->liste_mot); //libère les mots et les t_mots du lexiques
        free(precedent->titre); //libère les titres
        free(precedent); //libère les lexiques
    }

    printf("\n\n*** FIN DU PROGRAMME ***\n");

    return 0;
}
