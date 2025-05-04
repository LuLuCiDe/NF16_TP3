#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

#define TAILLE_MAX_LIGNE 50

////////////////// EN PLUS ////////////////////////


//Ajoute en tête de liste pour pouvoir simplifier la complexité de la fonction fusionner
t_mot* ajouterTete (t_mot *liste, t_mot *val) {
    val->suivant = liste;
    liste = val;
    return liste;
}

char convMaj(char c){
    if (c >= 97 && c <= 122) { // Code ASCII : a = 97 et z = 122
        c -= 32; // Code ASCII : A = 65 et Z = 90
    }
    return c;
}

char *toutMinuscule(char *mot) {
    char *motParcouru = mot;
    int tailleMot = strlen(mot);
    for (int i=0; i<tailleMot; i++) {
        if (*motParcouru >= 'A' && *motParcouru<='Z') {
            *motParcouru += 32;
        }
        motParcouru++;
    }
    return mot;
}

// Création nouvel élément
t_mot *creerMot(char *mot) {
    t_mot * new_mot = malloc(sizeof(t_mot));
    if (!new_mot) {
        return NULL;
    }
    //Il y a beaucoup de problèmes de confusion entre les entrées ("scanf") et les créations du mot
    //-> Solution : Allocation mémoire plus claire avec malloc
    new_mot->mot = malloc(MAX_MOT * sizeof(char));
    if (!new_mot->mot){
        free(new_mot);
        return NULL;
    }
    toutMinuscule(mot);
    strcpy(new_mot->mot, mot); //copie la chaine de caractère de mot dans la zone mémoire allouée

    new_mot->nombre_occurences = 1;
    new_mot->suivant = NULL;
    return new_mot;
}

/* ====== FIN creerMot ====== */

// Ajout mot dans une liste
t_mot *ajouterMot(t_mot *liste, char *mot) {
    toutMinuscule(mot);

    // LISTE VIDE : ajout du premier mot
    if (liste == NULL) {
        return creerMot(mot);
    }

    // INITIALISATION des pointeurs pour parcourir
    t_mot *position = liste ;
    t_mot *precedent = NULL ;

    // PARCOURS de la chaine
    while (position!=NULL && strcmp(mot,position->mot)>0) {
        precedent = position ;
        position = position->suivant ;
    }

    //Il faut vérifier que position != NULL avant le strcmp
    // Si le mot est DEJA dans le lexique
    if (position!=NULL && strcmp(position->mot, mot) == 0) {
        position->nombre_occurences++;
        return liste;
    }

    // CREATION du mot
    t_mot *nouveauMot = creerMot(mot);
    if (precedent == NULL) {
        // Insertion en tête
        nouveauMot->suivant = liste;
        return nouveauMot;
    } else {
        // Insertion au milieu ou à la fin
        precedent->suivant = nouveauMot;
        nouveauMot->suivant = position;
        return liste;
    }
}

/* ====== FIN Ajout du mot dans une liste ====== */


// Retrait occurence mot d'une liste
t_mot *retirerMot(t_mot *liste, char *mot) {
    toutMinuscule(mot);
    if(!liste){return NULL;}
    if (strcmp(mot,liste->mot)==0){ //mot est au début du lexique et si = à 1
        if (liste->nombre_occurences==1){
            printf("\nLe mot '%s' a ete supprime du lexique.\n", mot);
            return liste->suivant;
        }
        else{
            printf("\nUne occurence du mot '%s' a ete retiree.\n", mot);
            liste->nombre_occurences--;
            return liste;
        }
    }


    t_mot *pred=liste;
    while(pred->suivant != NULL && strcmp(pred->suivant->mot, mot) != 0){
        pred = pred->suivant;
    }


    if(pred->suivant == NULL){//le mot n'est pas dans la liste
        printf("\nLe mot '%s' n'est pas dans la liste.\n", mot);
        return liste;
    }


    //else : pred->suivant->mot == mot
    t_mot *found=pred->suivant;
    if(found->nombre_occurences<=1){
        printf("\nLe mot '%s' a ete supprime du lexique.\n", mot);
        pred->suivant = found->suivant;
        free(found);
        return liste;
    }
    else {
        printf("\nUne occurence du mot '%s' a ete retiree.\n", mot);
        found->nombre_occurences--;
        return liste;
    }
}

/* ====== FIN ajouterMot ====== */


// Affichage mots d'un lexique
void afficherMots(t_mot *liste){
    if (liste == NULL) {
            printf("LE LEXIQUE EST VIDE !");
            return;
    }

    char first_car = '0';
    while (liste){
        char* mot = liste->mot;
        if (convMaj(mot[0]) != first_car){ //Si on passe à une nouvelle lettre dans le lexique
            first_car = convMaj(mot[0]);
            printf("%c ", first_car);
        }
        else{
            printf("  ");
        }
        printf("--- ");
        for (int i = 0; i < strlen(mot); i++) {
            printf("%c", *(mot+i));
        }
        printf(" [%d]\n", liste->nombre_occurences);
        liste = liste->suivant;
    }
    return;
}



/* ====== FIN afficherMots ====== */


// Fusion listes
t_mot *fusionner(t_mot *listeA, t_mot *listeB){
    if (!listeA){
        return listeB;
    }
    if (!listeB){
        return listeA;
    }
    int cmp = strcmp(listeA->mot, listeB->mot);
    if (cmp == 0) {//motA == motB
        listeA->nombre_occurences+=listeB->nombre_occurences;
        return ajouterTete(fusionner(listeA->suivant,listeB->suivant), listeA);
    }
    if (cmp < 0) {//motA < motB (selon l'ordre alphabétique)
        return ajouterTete(fusionner(listeA->suivant,listeB), listeA);
    }
    if (cmp > 0) {//motA > motB (selon l'ordre alphabétique)
        return ajouterTete(fusionner(listeA,listeB->suivant), listeB);
    }
    return NULL;
}

/* ====== FIN fusionner ====== */

void libererListe(t_mot* liste) {
    t_mot* temp;
    while (liste != NULL) {
        temp = liste;
        liste = liste->suivant;
        free(temp->mot);
        //ne pas faire : free(temp->nombre_occurences); -> pas d'allocation memoire
        free(temp);
    }
}

// Import fichier de mots dans une liste
t_mot *importerFichier(t_mot *liste){

    // recuperation du nom du fichier a ouvrir
    char nom_fichier[20] = "";
    printf("Entrez le nom du fichier : ");
    scanf(" %20s", nom_fichier);

    // ouverture du fichier
    FILE* fichier = NULL;
    fichier = fopen(nom_fichier, "r+");


    if (fichier != NULL)
    {
        char chaine[TAILLE_MAX_LIGNE] = "", mot[TAILLE_MAX_LIGNE];
        while (fgets(chaine, TAILLE_MAX_LIGNE, fichier)!=NULL) {
            chaine[strcspn(chaine, "\n")] = '\0';
            liste = ajouterMot(liste, chaine);
        }
        fclose(fichier);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier test.txt");
    }

    return liste;
}

/* ====== FIN importerFichier ====== */


// fonction utile pour vider le tampon clavier
void viderBuffer() {
    int c = '0';
    while (c!='\n' && c != EOF) { c = getchar(); }
}

//------ Fonctions sur les listes de lexique ----------

// Création nouveau lexique
lex *creerLex(char *titre, t_mot *lexique) {
    lex* new_lex = malloc(sizeof(lex));
    if (!new_lex) {
        return NULL;
    }
    //Il y a beaucoup de problèmes de confusion entre les entrées ("scanf") et les créations du mot
    //-> Solution : Allocation mémoire plus claire avec malloc
    new_lex->titre = malloc(MAX_TITRE * sizeof(char));
    if (!new_lex->titre){
        free(new_lex);
        return NULL;
    }
    strcpy(new_lex->titre, titre); //copie la chaine de caractère de titre dans la zone mémoire allouée

    new_lex->liste_mot=lexique;
    new_lex->suivant = NULL;
    return new_lex;
}

/* ====== FIN creerLex ====== */

// Ajout d'un nouveau lexique en queue de liste
lex *ajouterQueueLex(lex *liste_lex, lex *lexique) {
    // LISTE VIDE : ajout du premier lexique
    if (liste_lex == NULL) {
        return lexique;
    }

    // INITIALISATION des pointeurs pour parcourir
    lex *position = liste_lex ;

    // PARCOURS de la chaine
    while (position->suivant!=NULL) {
        position = position->suivant ;
    }

    //fin while : position->suivant == NULL
    position->suivant = lexique;
    return liste_lex;
}

/* ====== FIN ajouterQueueLex ====== */

void afficherTitreLex(lex* liste_lex){
    printf("\n\t- Liste des lexiques -\n");
    int i = 1; //indice attribué dynammiquement à chaque lexique
    lex* lexique = liste_lex;
    while (lexique != NULL) {
        printf("%d) %s\n", i, lexique->titre);
        lexique = lexique->suivant;
        i++;
    }
}
/* ====== FIN ajouterQueueLex ====== */

//
lex* selectLex(lex* liste_lex, int nb_lex){
    int num_lex = 0;
    while (num_lex < 1 || num_lex > nb_lex) {
        printf("\nQuel lexique choisissez-vous ? (entrez le numero) : ");
        scanf(" %d", &num_lex);
    }

    //On parcourt les lexiques jusqu'au num_lex choisi
    lex* parcours = liste_lex;
    for(int i = 1; i < num_lex; i++){
        parcours=parcours->suivant;
    }
    return parcours;
}
/* ====== FIN ajouterQueueLex ====== */

//---- Initialisation pour tests ------
lex* init(){
    char *liste_mot_enfance[30] = {"abeille","arbre","bateau","bateau","avion","bulle", "carapuce"};
    char titre1[50] = "Enfance";

    //Creation de la liste de lexiques
    lex* liste_lexique = creerLex(titre1, creerMot(liste_mot_enfance[0]));

    for (int i=1; i<7; i++){
        liste_lexique->liste_mot = ajouterMot(liste_lexique->liste_mot, liste_mot_enfance[i]);
    }

    char *liste_mot_pokemon[30] = {"bulbizarre","bulbizarre","bulbizarre","salameche","carapuce","rattatac","togekiss", "sablette"};
    char titre2[50] = "Pokemon";

    //Creation de la liste de lexiques
    liste_lexique = ajouterQueueLex(liste_lexique, creerLex(titre2, creerMot(liste_mot_pokemon[0])));

    for (int i=1; i<8; i++){
        liste_lexique->suivant->liste_mot = ajouterMot(liste_lexique->suivant->liste_mot, liste_mot_pokemon[i]);
    }

    return liste_lexique;
}
