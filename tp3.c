#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

#define TAILLE_MAX_LIGNE 50

// Création nouvel élément
t_mot *creerMot(char *mot) {
    t_mot * new_mot = malloc(sizeof(t_mot));
    mot = toutMinuscule(mot);
    if (!new_mot) {
        return NULL;
    }
    new_mot-> mot = mot;
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
    if(!liste){return NULL;}
    if (liste->mot==mot && liste->nombre_occurences==1){ //mot est au début du lexique et si = à 1
        return liste->suivant;
    }


    t_mot *pred=liste;
    while(pred->suivant != NULL && strcmp(pred->suivant->mot, mot) != 0){
        pred = pred->suivant;
    }


    if(pred->suivant == NULL){//le mot n'est pas dans la liste
        return liste;
    }


    //else : pred->suivant->mot == mot
    t_mot *found=pred->suivant;
    if(found->nombre_occurences<=1){
        pred->suivant = found->suivant;
        free(found);
        return liste;
    }
    else {
        found->nombre_occurences--;
        return liste;
    }
}

/* ====== FIN ajouterMot ====== */


// Affichage mots d'un lexique
void afficherMots(t_mot *liste){
    char first_car = "0";
    char car_precedent = "1";
    while (liste){
        char* mot = liste->mot;
        if (convMaj(mot) != first_car){
            first_car = convMaj(mot);
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


// Import fichier de mots dans une liste
t_mot *importerFichier(t_mot *liste){


    // recuperation du nom du fichier a ouvrir
    char nom_fichier[20];
    printf("Entrez le nom du fichier : ");
    scanf("%20s", nom_fichier);

    // ouverture du fichier
    FILE* fichier = NULL;
    fichier = fopen(nom_fichier, "r+");


    if (fichier != NULL)
    {
        char chaine[TAILLE_MAX_LIGNE] = "", mot[TAILLE_MAX_LIGNE];
        while (fgets(chaine, TAILLE_MAX_LIGNE, fichier)!=NULL) {
            chaine[strcspn(chaine, "\n")] = '\0';
            liste = ajouterMot(liste, strdup(chaine));
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

////////////////// EN PLUS ////////////////////////
t_mot* ajouterTete (t_mot *liste, t_mot *val) {
    //fonction qui ajoute en tête de liste pour pouvoir simpliier la complexité de la fonction fusionner
    val->suivant = liste;
    liste = val;
    return liste;
}

char convMaj(char *mot) {
    char caractere = mot[0]-32 ;
    return caractere;
}

void libererListe(t_mot* liste) {
    t_mot* temp;
    while (liste != NULL) {
        temp = liste;
        liste = liste->suivant;
        free(temp->mot);
        free(temp->nombre_occurences);
        free(temp);
    }
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






