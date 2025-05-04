#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

// Instructions preprocesseur
#define MAX_TITRE 50
#define MAX_MOT 30

// Structures demandees
struct s_mot {
    char* mot;
    int nombre_occurences;
    struct s_mot* suivant;
};

typedef struct s_mot t_mot;

// Structures AJOUTEES
typedef struct lexique {
    char* titre;
    struct s_mot *liste_mot;
    struct lexique *suivant;
} lex;

// Fonctions demandees
t_mot *creerMot(char *mot);

t_mot *ajouterMot(t_mot *liste, char *mot);

t_mot *retirerMot(t_mot *liste, char *mot);

void afficherMots(t_mot *liste);

t_mot *fusionner(t_mot *listeA, t_mot *listeB);

t_mot *importerFichier(t_mot *liste);


// fonction utile pour vider le tampon clavier
void viderBuffer() ;

// EN PLUS //////////////////////
t_mot* ajouterTete (t_mot *liste, t_mot *val);

char convMaj(char c);

char *toutMinuscule(char *mot);

void libererListe(t_mot* liste);

//--- Fonctions lexique ----

lex *creerLex(char *titre, t_mot *lexique);

lex *ajouterQueueLex(lex *liste, lex *lexique);

lex* init();

//--- Fonctions Affichage ---
//(pour pouvoir modifier le style d'affichage en une fois)
//(-> comme mettre le style dans une page css à part)

void afficherTitreLex(lex* liste_lex);

lex* selectLex(lex* liste_lex, int nb_lex);


#endif // TP3_H_INCLUDED
