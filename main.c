#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAMBRES 50
#define MAX_CLIENTS 50

typedef struct {
    int numero;
    char type[10];
    float tarif;
    int estLibre;
} Chambre;

typedef struct {
    char nom[50];
    char prenom[50];
    char telephone[15];
    char dateArrivee[15];
    char dateDepart[15];
    int numeroChambre;
} Client;

typedef struct {
    Client client;
    Chambre *chambre;
} Reservation;


Chambre chambres[MAX_CHAMBRES];
Client clients[MAX_CLIENTS];
int nbChambres = 0;
int nbClients = 0;


void sauvegarderDonnees() {
    Client c;
    FILE *f = fopen("resevation.txt", "a+");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier pour la sauvegarde !\n");
        return;
    }


    fprintf(f, "%d\n", nbChambres);
    for (int i = 0; i < nbChambres; i++) {
        fprintf(f, "%d %s %.2f %d\n", chambres[i].numero, chambres[i].type, chambres[i].tarif, chambres[i].estLibre);
    }


    fprintf(f, "%d\n", nbClients);
    for (int i = 0; i < nbClients; i++) {
        fprintf(f, "%s %s %s %d %s %s\n",
                c.nom,
                c.prenom,
                c.telephone,
                c.numeroChambre,
                c.dateArrivee,
                c.dateDepart);
    }
}
void chargerDonnees() {
    Client c;
    FILE *f = fopen("resevation.txt", "r");
    if (f == NULL) {
        printf("Aucune donnée à charger (fichier inexistant).\n");
        return;
    }


    fscanf(f, "%d", &nbChambres);
    for (int i = 0; i < nbChambres; i++) {
        fscanf(f, "%d %s %f %d", &chambres[i].numero, chambres[i].type, &chambres[i].tarif, &chambres[i].estLibre);
    }


    fscanf(f, "%d", &nbClients);
    for (int i = 0; i < nbClients; i++) {
        fscanf(f, "%s %s %s %d %s %s",
               c.nom,
               c.prenom,
               c.telephone,
               &c.numeroChambre,
               c.dateArrivee,
               c.dateDepart);
    }

    fclose(f);
    printf("Données chargées avec succès.\n");
}
void initialiserChambres() {
    printf("Initialisation des chambres...\n");
    for (int i = 0; i < MAX_CHAMBRES; i++) {
        chambres[i].numero = i + 1;
        if (i % 3 == 0) {
            strcpy(chambres[i].type, "simple");
            chambres[i].tarif = 50.0;
        } else if (i % 3 == 1) {
            strcpy(chambres[i].type, "double");
            chambres[i].tarif = 80.0;
        } else {
            strcpy(chambres[i].type, "suite");
            chambres[i].tarif = 120.0;
        }
        chambres[i].estLibre = 1;
        nbChambres++;
    }
}

void afficherChambres() {
    printf("\nListe des chambres\n");
    for (int i = 0; i < nbChambres; i++) {
        printf("Chambre %d: Type: %s, Tarif: %.2f, Etat: %s\n",
               chambres[i].numero,
               chambres[i].type,
               chambres[i].tarif,
               chambres[i].estLibre ? "Libre" : "Occupée");
    }
}

void ajouterReservation() {
    if (nbClients >= MAX_CLIENTS) {
        printf("Capacité maximale des clients atteinte !\n");
        return;
    }

    Client c;
    printf("\n Ajouter une réservation\n");
    printf("Nom du client : ");
    scanf("%s", c.nom);
    printf("Prénom du client : ");
    scanf("%s", c.prenom);
    printf("Téléphone : ");
    scanf("%s", c.telephone);
    printf("Date d'arrivée (jj/mm/aaaa) : ");
    scanf("%s", c.dateArrivee);
    printf("Date de départ (jj/mm/aaaa) : ");
    scanf("%s", c.dateDepart);


    int numeroChambre;
    printf("Numéro de la chambre souhaitée : ");
    scanf("%d", &numeroChambre);

    if (numeroChambre < 1 || numeroChambre > nbChambres || !chambres[numeroChambre - 1].estLibre) {
        printf("Chambre non disponible !\n");
        return;
    }

    c.numeroChambre = numeroChambre;
    chambres[numeroChambre - 1].estLibre = 0;
    clients[nbClients++] = c;

    printf("Réservation ajoutée avec succès pour le client %s %s, chambre %d.\n",
           c.nom, c.prenom, c.numeroChambre);
           sauvegarderDonnees();
}

void annulerReservation() {
    printf("\nAnnuler une réservation\n");
    int numeroChambre;
    printf("Numéro de la chambre à libérer : ");
    scanf("%d", &numeroChambre);

    if (numeroChambre < 1 || numeroChambre > nbChambres || chambres[numeroChambre - 1].estLibre) {
        printf("Aucune réservation trouvée pour cette chambre !\n");
        return;
    }

    for (int i = 0; i < nbClients; i++) {
        if (clients[i].numeroChambre == numeroChambre) {
            chambres[numeroChambre - 1].estLibre = 1;
            printf("Réservation pour le client %s %s annulée.\n", clients[i].nom, clients[i].prenom);

            for (int j = i; j < nbClients - 1; j++) {
                clients[j] = clients[j + 1];
            }
            nbClients--;
            return;
        }
    }
    printf("Aucune réservation trouvée pour cette chambre !\n");
    sauvegarderDonnees();
}

void afficherRapportQuotidien() {
    printf("\nRapport quotidien\n");

    int chambresLibres = 0;
    int chambresOccupees = 0;
    float revenus = 0.0;

    for (int i = 0; i < nbChambres; i++) {
        if (chambres[i].estLibre) {
            chambresLibres++;
        } else {
            chambresOccupees++;
            revenus += chambres[i].tarif;
        }
    }

    printf("Chambres libres : %d\n", chambresLibres);
    printf("Chambres occupées : %d\n", chambresOccupees);
    printf("Revenus journaliers : %.2f\n", revenus);
}

void afficherRapportHebdomadaire() {
    printf("\n Rapport hebdomadaire\n");

    int totalReservations = nbClients;
    float totalRevenue = 0.0;
    int roomsOccupied = 0;

    for (int i = 0; i < nbClients; i++) {
        int chambreIndex = clients[i].numeroChambre - 1;
        totalRevenue += chambres[chambreIndex].tarif;
        roomsOccupied++;
    }

    float occupancyRate = (nbChambres > 0) ? ((float)roomsOccupied / nbChambres) * 100 : 0;

    printf("Nombre total de réservations : %d\n", totalReservations);
    printf("Revenu hebdomadaire total : %.2f\n", totalRevenue);
    printf("Taux d'occupation : %.2f%%\n", occupancyRate);
}

void modifierTarifs() {
    printf("\nModifier les tarifs \n");
    for (int i = 0; i < nbChambres; i++) {
        printf("Chambre %d (type : %s, tarif actuel : %.2f) : ",
               chambres[i].numero, chambres[i].type, chambres[i].tarif);
        scanf("%f", &chambres[i].tarif);
    }
    printf("Tarifs modifiés avec succès.\n");
}

void afficherMenu() {
    printf("\n Simulateur de gestion d'un hotel\n");
    printf("1. Afficher les chambres\n");
    printf("2. Ajouter une réservation\n");
    printf("3. Annuler une réservation\n");
    printf("4. Afficher un rapport quotidien\n");
    printf("5. Afficher un rapport hebdomadaire\n");
    printf("6. Modifier les tarifs\n");
    printf("0. Quitter\n");
}

int main() {
    chargerDonnees();
    initialiserChambres();
    int choix;

    do {
        afficherMenu();
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficherChambres();
                break;
            case 2:
                ajouterReservation();
                break;
            case 3:
                annulerReservation();
                break;
            case 4:
                afficherRapportQuotidien();
                break;
            case 5:
                afficherRapportHebdomadaire();
                break;
            case 6:
                modifierTarifs();
                break;
            case 0:
                printf(".\n");
                break;
            default:
                printf("Choix invalide !\n");
        }}
     while (choix != 0);

    return 0;}

