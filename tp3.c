#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"

#define TAILLE_MAX_LIGNE 50



////////////////// FONCTIONS SUPPLEMENTAIRES | EN PLUS ////////////////////////
t_mot* ajouterTete (t_mot *liste, t_mot *val) {
    //fonction qui ajoute en tête de liste pour pouvoir simpliier la complexité de la fonction fusionner
    val->suivant = liste;
    liste = val;
    return liste;
}

char convMaj(char *mot) {
    char caractere = mot[0];
    if (caractere >= 'a' && caractere <='z') {
        caractere -= 32 ;
    }
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
////////////////// FIN DES FONCTIONS SUPPLEMENTAIRES   ////////////////////////



// Création nouvel élément
t_mot *creerMot(char *mot) {
    t_mot * new_mot = malloc(sizeof(t_mot));
    if (!new_mot) {
        return NULL;
    }
    //Il y a beaucoup de problèmes de confusion entre les entrées ("scanf") et les créations du mot
    //-> Solution : Allocation mémoire plus claire avec malloc
    new_mot->mot = malloc(strlen(mot) + 1);
    if (!new_mot->mot){
        free(new_mot);
        return NULL;
    }
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
    // Si la liste est nulle :
    if(!liste){return NULL;}

    // On convertit en minuscule le mot
    mot = toutMinuscule(mot);

    // Si le mot est au début
    if (strcmp(liste->mot, mot) == 0){
        // Si l'occurence vaut 1
        if (liste->nombre_occurences==1) {
            t_mot *new_liste = liste->suivant;
            free(liste);

            return new_liste;
        } else {
            liste->nombre_occurences--;
            return liste;
        }
    }

    // Si le mot n'est PAS au début
    t_mot *precedent=liste;
    while(precedent->suivant != NULL && strcmp(precedent->suivant->mot, mot) != 0){
        precedent = precedent->suivant;
    }   // s'arrête quand on arrive à la fin de la liste
        // OU quand on a trouvé le mot


    if(precedent->suivant == NULL){ //le mot n'est pas dans la liste
        return liste;
    }


    //else : pred->suivant->mot == mot
    t_mot *found=precedent->suivant;
    if(found->nombre_occurences<=1){
        precedent->suivant = found->suivant;
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
    if (liste == NULL) {
            printf("\nLE LEXIQUE EST VIDE !");
    }
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

