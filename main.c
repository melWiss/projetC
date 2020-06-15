#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxC 5

typedef struct Cellule
{
    char NomP[20];
    struct Cellule *PP;
} Cellule;

typedef struct Cahier
{
    char NomA[30];
    Cellule *LP;
} Cahier;

typedef struct Dossier
{
    Cahier TC[MaxC];
    int NbC;
} Dossier;

Cellule *Appartient(char NP[20], Cellule *T)
{
    while (T != NULL && strcmp(T->NomP, NP) != 0)
    {
        T = T->PP;
    }
    return T;
}

int RechercheActivite(Dossier D, char NA[20])
{
    int size = D.NbC;

    for (int i = 0; i < size; i++)
    {
        if (strcmp(D.TC[i].NomA, NA) == 0)
            return i;
    }
    return -1;
}

void AjouterPersonne(char NP[20], Cellule *T)
{
    while (T->PP != NULL)
        T = T->PP;
    Cellule *cell = (Cellule *)malloc(sizeof(Cellule));
    cell->PP = NULL;
    strcpy(cell->NomP, NP);
    T->PP = cell;
}

void AjouterCahier(Dossier *D, char NP[20], char NA[20])
{
    if (D->NbC >= MaxC)
    {
        printf("IMPOSSIBLE D'AJOUT: NBC<MAXC\n");
        return;
    }
    else
    {
        strcpy(D->TC[D->NbC].NomA, NA);
        D->TC[D->NbC].LP = (Cellule *)malloc(sizeof(Cellule));
        strcpy(D->TC[D->NbC].LP->NomP, NP);
        D->TC[D->NbC].LP->PP = NULL;
        D->NbC++;
    }
}

void AjouterInscription(Dossier *D, char NP[20], char NA[20])
{
    if (D->NbC >= MaxC)
    {
        printf("IMPOSSIBLE D'INSCRIT: NBC>=MAXC\n");
        return;
    }
    else
    {
        if (RechercheActivite(*D, NA) != -1)
        {
            if (Appartient(NP, D->TC[RechercheActivite(*D, NA)].LP) == NULL)
            {
                AjouterPersonne(NP, D->TC[RechercheActivite(*D, NA)].LP);
                D->NbC++;
            }
        }
        else
        {
            AjouterCahier(D, NP, NA);
        }
    }
}

void AfficherDossier(Dossier D, char NA[20])
{
    if (RechercheActivite(D, NA) != -1)
        while (D.TC[RechercheActivite(D, NA)].LP != NULL)
        {
            printf("%s\n", D.TC[RechercheActivite(D, NA)].LP->NomP);
            D.TC[RechercheActivite(D, NA)].LP = D.TC[RechercheActivite(D, NA)].LP->PP;
        }
}

void SupprimerPersonne(Dossier *D, char NP[20], char NA[20])
{
    if (RechercheActivite(*D, NA) != -1)
    {
        if (Appartient(NP, D->TC[RechercheActivite(*D, NA)].LP) != NULL)
        {
            Cellule *personnes = D->TC[RechercheActivite(*D, NA)].LP;
            if (strcmp(personnes->NomP, NP) == 0)
            {
                /* code */
                Cellule *p = personnes;
                personnes = personnes->PP;
                free(p);
            }
            else
            {
                while (personnes->PP != NULL && strcmp(personnes->PP->NomP, NP) != 0)
                    personnes = personnes->PP;
                if (personnes->PP != NULL)
                {
                    Cellule *p = personnes->PP;
                    personnes->PP = personnes->PP->PP;
                    D->TC[RechercheActivite(*D, NA)].LP = personnes;
                    free(p);
                }
            }
        }
    }
}

void RemplissageAutomatique(Dossier *D)
{
    //Tableau des activités à insérer dans le dossier
    char tabAct[3][20] = {"Lecture", "Jeu d'echecs", "Tennis"};
    // Tableau des personnes inscrites à l’activité 1 "Lecture"
    char PerA1[3][10] = {"Wadii", "Youssef", "Asma"};
    // Tableau des personnes inscrites à l’activité 2 "Jeu d'echecs"
    char PerA2[3][10] = {"Nour", "Mohamed", "Emir"};
    // Tableau des personnes inscrites à l’activité 3 "Tennis"
    char PerA3[3][10] = {"Wadii", "Aziz", "Sarra"};
    int i;
    D->NbC = 0;
    Cellule *cel;
    //Ajout de l'activité 1
    strcpy(D->TC[0].NomA, tabAct[0]);
    D->NbC++;
    D->TC[0].LP = NULL;
    //Insertion des personnes à l'activité 1. La nouvelle personne est insérée au début de la liste.
    for (i = 2; i >= 0; i--)
    {
        cel = (Cellule *)malloc(sizeof(Cellule));
        if (cel == NULL)
            printf("Allocation impossible !");
        else
        {
            strcpy(cel->NomP, PerA1[i]);
            cel->PP = D->TC[0].LP;
            D->TC[0].LP = cel;
        }
    }
    //Ajout de l'activité 2
    strcpy(D->TC[1].NomA, tabAct[1]);
    D->NbC++;
    D->TC[1].LP = NULL;
    //Insertion des personnes à l'activité 2. La nouvelle personne est insérée au début de la liste.
    for (i = 2; i >= 0; i--)
    {
        cel = (Cellule *)malloc(sizeof(Cellule));
        if (cel == NULL)
            printf("Allocation impossible !");
        else
        {
            strcpy(cel->NomP, PerA2[i]);
            cel->PP = D->TC[1].LP;
            D->TC[1].LP = cel;
        }
    }
    //Ajout de l'activité 3
    strcpy(D->TC[2].NomA, tabAct[2]);
    D->NbC++;
    D->TC[2].LP = NULL;
    //Insertion des personnes à l'activité 3. La nouvelle personne est insérée au début de la liste.
    for (i = 2; i >= 0; i--)
    {
        cel = (Cellule *)malloc(sizeof(Cellule));
        if (cel == NULL)
            printf("Allocation impossible !");
        else
        {
            strcpy(cel->NomP, PerA3[i]);
            cel->PP = D->TC[2].LP;
            D->TC[2].LP = cel;
        }
    }
}

void AffichageActivites(Dossier *D)
{
    if (D->NbC)
    {
        for (int i = 0; i < D->NbC; i++)
        {
            printf("%s\n", D->TC[i].NomA);
        }
    }
}

void clearScreen()
{
    #ifdef __linux__
        system("clear");
    #else
        system("cls");
    #endif
}

void main()
{
    Dossier D;
    int choix = 0;
    int D_IS_EMPTY = 1;
    clearScreen();
    while (choix != 6)
    {
        printf("1. Remplissage automatique\n2. Ajouter une inscription\n3. Afficher toutes les activités du club\n4. Afficher les personnes inscrites à une activité\n5. Supprimer une personne d’une activité\n6. Quitter\n\n    Votre choix:    ");
        scanf("%d", &choix);
        clearScreen();
        switch (choix)
        {
        case 1:
            RemplissageAutomatique(&D);
            printf("REMPLISSAGE AUTO EST TERMINEE!\n");
            D_IS_EMPTY = 0;
            break;
        case 2:
            /* code */
            if (D_IS_EMPTY != 1)
            {
                char personne[20], activite[30];
                printf("\nDonner le prenom de personne: ");
                scanf("%s", &personne);
                printf("\nDonner le nom de l'activite: ");
                scanf("%s", &activite);
                AjouterInscription(&D, personne, activite);
                printf("\n%s EST INSCRIE!\n", personne);
            }
            break;
        case 3:
            /* code */
            if (D_IS_EMPTY != 1)
            {
                AffichageActivites(&D);
            }
            break;
        case 4:
            /* code */
            if (D_IS_EMPTY != 1)
            {
                char activite[30];
                printf("\nDonner le nom de l'activite: ");
                scanf("%s", &activite);
                AfficherDossier(D, activite);
            }
            break;
        case 5:
            /* code */
            if (D_IS_EMPTY != 1)
            {
                char personne[20], activite[30];
                printf("\nDonner le prenom de personne: ");
                scanf("%s", &personne);
                printf("\nDonner le nom de l'activite: ");
                scanf("%s", &activite);
                SupprimerPersonne(&D, personne, activite);
                printf("\n%s A ETE SUPRIMÉ!\n", personne);
            }
            break;
        default:
            break;
        }
    }
}