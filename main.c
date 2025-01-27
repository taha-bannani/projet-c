#include <stdio.h>
#include <string.h>

#define MAX_CHAMBRES 50
#define MAX_RESERVATIONS 50


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
    int numeroChambre;
} Reservation;


Chambre chambres[MAX_CHAMBRES];
Reservation reservations[MAX_RESERVATIONS];
int nbChambres = 0;
int nbReservations = 0;

void initialiserChambres() {
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
    printf("\n--- Liste des chambres ---\n");
    for (int i = 0; i < nbChambres; i++) {
        printf("Chambre %d : Type : %s, Tarif : %.2f, Etat : %s\n",
               chambres[i].numero,
               chambres[i].type,
               chambres[i].tarif,
               chambres[i].estLibre ? "Libre" : "Occupée");
    }
}


void ajouterReservation() {



    if (nbReservations >= MAX_RESERVATIONS) {
        printf("Capacité maximale des réservations atteinte !\n");

        return;
    }

    Reservation res;
    printf("\n--- Ajouter une réservation ---\n");
    printf("Nom : ");
    scanf("%s", res.nom);
    printf("Prénom : ");
    scanf("%s", res.prenom);
    printf("Téléphone : ");
    scanf("%s", res.telephone);

    int numeroChambre;
    printf("Numéro de la chambre souhaitée : ");
    scanf("%d", &numeroChambre);

    if (numeroChambre < 1 || numeroChambre > nbChambres || !chambres[numeroChambre - 1].estLibre) {
        printf("La chambre n'est pas disponible !\n");
        return;
    }

    res.numeroChambre = numeroChambre;
    chambres[numeroChambre - 1].estLibre = 0;
    reservations[nbReservations++] = res;

    printf("Réservation ajoutée avec succès pour %s %s, chambre %d.\n",
           res.nom, res.prenom, res.numeroChambre);
}

void annulerReservation() {

    int numeroChambre;
    printf("Numéro de la chambre à libérer : ");
    scanf("%d", &numeroChambre);

    for (int i = 0; i < nbReservations; i++) {
        if (reservations[i].numeroChambre == numeroChambre) {
            chambres[numeroChambre - 1].estLibre = 1;
            printf("Réservation de %s %s annulée pour la chambre %d.\n",
                   reservations[i].nom, reservations[i].prenom, numeroChambre);


            for (int j = i; j < nbReservations - 1; j++) {
                reservations[j] = reservations[j + 1];
            }
            nbReservations--;
            return;
        }
    }
    printf("Aucune réservation trouvée pour cette chambre !\n");
}

void afficherRapportQuotidien() {


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
    printf("Revenus journaliers : %.2f \n", revenus);
}

void afficherRapportHebdomadaire() {


    int totalReservations;
    float totalRevenue = 0.0;
    int roomsOccupied = 0;
    totalReservations = nbReservations;
    for (int i = 0; i < nbReservations; i++) {
        int chambreIndex = reservations[i].numeroChambre - 1;
        totalRevenue += chambres[chambreIndex].tarif;
        roomsOccupied++;
    }


    float occupancyRate;
    occupancyRate = (nbChambres > 0) ? ((float)roomsOccupied / nbChambres) * 100 : 0;


    printf("Nombre total de réservations : %d\n", totalReservations);
    printf("Revenu hebdomadaire total : %.2f\n", totalRevenue);
    printf("Taux d'occupation : %.2f%%\n", occupancyRate);
}


void modifierTarifs() {
    printf("\n Modifier les tarifs\n");
    for (int i = 0; i < nbChambres; i++) {
        printf("Chambre %d (type : %s, tarif actuel : %.2f) : ",
               chambres[i].numero, chambres[i].type, chambres[i].tarif);
        scanf("%f", &chambres[i].tarif);
    }
    printf("Tarifs modifiés avec succès.\n");
}

void afficherMenu() {

    printf("1. Afficher les chambres\n");
    printf("2. Ajouter une réservation\n");
    printf("3. Annuler une réservation\n");
    printf("4. Afficher un rapport quotidien\n");
    printf("5. Afficher un rapport hebdomadaire\n");
    printf("6. Modifier les tarifs\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");
}

int main() {
    FILE*f=fopen("Reservation.txt","a+");
    initialiserChambres();
    int choix;

    do {
        afficherMenu();
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
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choix != 0);
   fclose(f);
    return 0;
}
