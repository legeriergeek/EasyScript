#include <stdio.h>
#include <string.h>

#define MAX_VAR_NAME_LENGTH 50
#define MAX_LINE_LENGTH 100

typedef struct {
    char name[MAX_VAR_NAME_LENGTH];
    int value;
} Variable;

Variable variables[100];
int varCount = 0;

void print(const char* texte) {
    printf("%s\n", texte);
}

void int_variable(const char* nom, int valeur) {
    Variable variable;
    strncpy(variable.name, nom, MAX_VAR_NAME_LENGTH - 1);
    variable.value = valeur;
    variables[varCount] = variable;
    varCount++;
}

void printvar(const char* nom) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(variables[i].name, nom) == 0) {
            printf("%d\n", variables[i].value);
            return;
        }
    }
    printf("Variable non définie\n");
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <fichier.es>\n", argv[0]);
        return 1;
    }

    FILE* fichier = fopen(argv[1], "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    char ligne[MAX_LINE_LENGTH];
    char mot[20];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        sscanf(ligne, "%s", mot);

        if (strcmp(mot, "affiche") == 0) {
            char texte[80];
            sscanf(ligne, "%*s \"%79[^\"]\"", texte);
            print(texte);
        } else if (strcmp(mot, "int") == 0) {
            char nom[MAX_VAR_NAME_LENGTH];
            int valeur;
            sscanf(ligne, "%*s %s %d", nom, &valeur);
            int_variable(nom, valeur);
        } else if (strcmp(mot, "affichevar") == 0) {
            char nom[MAX_VAR_NAME_LENGTH];
            sscanf(ligne, "%*s %s", nom);
            printvar(nom);
        } else {
            printf("Commande non reconnue\n");
        }
    }

    fclose(fichier);
    return 0;
}
