#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_LENGTH 256
#define MAX_VALUES 50

typedef struct {
    int id;
    char name[50];
    char nationality[30];
    struct
    {
        int year;
        int month;
        int day;
    }birthdate;
    int world_titles;
    int darts_weight;
} DartsPlayer;

int read_darts_players(const char *filename, DartsPlayer players[], int max_players);
void print_darts_players(const DartsPlayer players[], int size);
int nationality_count(const DartsPlayer players[], int size);
int darts_weight_count(const DartsPlayer players[], int size);
int oldest_player(const DartsPlayer players[], int size);
int nationality_and_world_title_count(const DartsPlayer players[], int size);
void nationality_and_darts_weight(const DartsPlayer players[], int size);
int add_unique_value(char values[][30], int count, const char *new_value);
void group_by_world_titles_and_nationality(const DartsPlayer players[], int size);

int main() {
    const char *filename = "darts_players.txt";
    const int max_players = 100;
    DartsPlayer players[max_players];

    int size = read_darts_players(filename, players, max_players);

    print_darts_players(players, size);

    //1. Feladat: Szomolja meg a fajl sorainak szamat fugvennyel.
    printf("Number of lines in the file: %d\n", size);

    printf("--------------------------------------------------------------------\n");

    //2. Feladat: Kerjen be egy A oszlopban levo erteket es szamolja meg, hany ilyen rekord van.
    int na_count = nationality_count(players, size);
    if (na_count == 0)
    {
        printf("There are no players of this nationality in this txt.\n");
    }
    else
    {
        printf("Number of players with the same nationality: %d\n", na_count);
    }

    printf("--------------------------------------------------------------------\n");

    //3. Feladat: Kerjen be egy B oszlopban levo erteket es szamolja meg, hany olyan rekord van, amelyben ez az ertek nem szerepel.
    int dw_count = darts_weight_count(players, size);
    if (dw_count == 0)
    {
        printf("There are no players with this darts weight in this txt.\n");
    }
    else
    {
        printf("The dart weight you entered is not displayed this many times: %d\n", dw_count);
    }

    printf("--------------------------------------------------------------------\n");

    //4. Feladat: Allapitsa meg, hogy a C oszlopban melyik a legnagyobb ertek. Es hanyadik volt az a rekord, amikor ez ez ertek eloszor elofordult.
    int op = oldest_player(players, size);
    printf("The oldest player is:\n");
    printf("Name: %s -> ID: %d\n", players[op].name, players[op].id);
    printf("Nationality: %s\n", players[op].nationality);
    printf("Birthdate: %d.%d.%d\n", players[op].birthdate.year, players[op].birthdate.month, players[op].birthdate.day);
    printf("World titles: %d\n", players[op].world_titles);
    printf("Darts weight: %d\n", players[op].darts_weight);

    printf("--------------------------------------------------------------------\n");

    //5. Feladat: Szamolja meg, hogy egy megadott A es B oszlopbeli ertekbol hany sor van.
    int nawt_count = nationality_and_world_title_count(players, size);
    if (nawt_count == 0)
    {
        printf("There are no players with this nationality and world title in this txt.\n");
    }
    else
    {
        printf("The nationality and world title you entered: %d\n", nawt_count);
    }

    printf("--------------------------------------------------------------------\n");

    //6. Feladat: Szamitsa ki, hogy egy megadott A oszlopbeli ertekbol a kulonbozo B oszlopbeli ertekekbol hany darab volt.
    nationality_and_darts_weight(players, size);

    printf("--------------------------------------------------------------------\n");

    //7. Feladat: Osszesitse a B oszlopbeli ertekenkent, hogy a C oszlopban milyen ertekek jelentek meg.
    group_by_world_titles_and_nationality(players, size);

    printf("--------------------------------------------------------------------\n");

    return 0;
}

int read_darts_players(const char *filename, DartsPlayer players[], int max_players) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    char line[LINE_LENGTH];
    int size = 0;

    while (fgets(line, sizeof(line), file) && size < max_players) {
        sscanf(line, "%d;%49[^;];%29[^;];%d.%d.%d;%d;%d",
               &players[size].id,
               players[size].name,
               players[size].nationality,
               &players[size].birthdate.year,
               &players[size].birthdate.month,
               &players[size].birthdate.day,
               &players[size].world_titles,
               &players[size].darts_weight);
        size++;
    }

    fclose(file);
    return size;
}

void print_darts_players(const DartsPlayer players[], int size) {
    printf("--------------------------------------------------------------------\n");
    printf("ID;Name;Nationality;Birthdate;World Titles;Darts Weight\n");
    printf("--------------------------------------------------------------------\n");
    for (int i = 0; i < size; i++) {
        printf("%d;%s;%s;%d.%d.%d;%d;%d\n",
               players[i].id,
               players[i].name,
               players[i].nationality,
               players[i].birthdate.year,
               players[i].birthdate.month,
               players[i].birthdate.day,
               players[i].world_titles,
               players[i].darts_weight);
    }
    printf("--------------------------------------------------------------------\n");
}

int nationality_count(const DartsPlayer players[], int size)
{
    int count = 0;
    printf("Choose a nationality: ");
    scanf("%s", players[size].nationality);
    for (int i = 0; i < size; i++)
    {
        if (strcmp(players[i].nationality, players[size].nationality) == 0)
        {
            count++;
        }
    }
    
    return count;
}

int darts_weight_count(const DartsPlayer players[], int size)
{
    int count = 0;
    printf("Enter a darts weight: ");
    scanf("%d", &players[size].darts_weight);
    for (int i = 0; i < size; i++)
    {
        if (players[i].darts_weight != players[size].darts_weight)
        {
            count++;
        }
    }
    
    return count;
}

int oldest_player(const DartsPlayer players[], int size)
{
    int oldest = 0;
    for (int i = 0; i < size; i++)
    {
        if (players[i].birthdate.year < players[oldest].birthdate.year)
        {
            oldest = i;
        }
    }
    
    return oldest;
}

int nationality_and_world_title_count(const DartsPlayer players[], int size)
{
    int count = 0;
    printf("Choose a nationality: ");
    scanf("%s", players[size].nationality);
    printf("Choose a world title: ");
    scanf("%d", &players[size].world_titles);
    for (int i = 0; i < size; i++)
    {
        if (strcmp(players[i].nationality, players[size].nationality) == 0 && players[i].world_titles == players[size].world_titles)
        {
            count++;
        }
    }
    
    return count;
}

void nationality_and_darts_weight(const DartsPlayer players[], int size)
{
    int unique_weights[MAX_VALUES] = {0};
    int freqencies[MAX_VALUES] = {0};
    int count = 0;

    printf("Choose a nationality: ");
    scanf("%s", players[size].nationality);
    for (int i = 0; i < size; i++)
    {
        if (strcmp(players[i].nationality, players[size].nationality) == 0)
        {
            int weight = players[i].darts_weight;
            int found = 0;
            
            for (int j = 0; j < count; j++)
            {
                if (unique_weights[j] == weight)
                {
                    freqencies[j]++;
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                unique_weights[count] = weight;
                freqencies[count] = 1;
                count++;
            }
        }
    }
    
    printf("Number of different dart weights: %d\n", count);
    for (int i = 0; i < count; i++)
    {
        printf("Darts weight: %d\n", unique_weights[i]);
    }
}

int add_unique_value(char values[][30], int count, const char *new_value)
{
    for (int i = 0; i < count; i++) {
        if (strcmp(values[i], new_value) == 0) {
            return count;
        }
    }
    strcpy(values[count], new_value);
    return count + 1;
}

void group_by_world_titles_and_nationality(const DartsPlayer players[], int size)
{
    int values[MAX_VALUES];
    char nationality_values[MAX_VALUES][MAX_VALUES][30];
    int counts[MAX_VALUES];
    int count = 0;

    for (int i = 0; i < size; i++) {
        int world_title_value = players[i].world_titles;
        const char *nationality_value = players[i].nationality;

        int found = 0;
        for (int j = 0; j < count; j++) {
            if (values[j] == world_title_value) {
                counts[j] = add_unique_value(nationality_values[j], counts[j], nationality_value);
                found = 1;
                break;
            }
        }

        if (!found) {
            values[count] = world_title_value;
            counts[count] = 0;
            counts[count] = add_unique_value(nationality_values[count], counts[count], nationality_value);
            count++;
        }
    }

    for (int i = 0; i < count; i++) {
        printf("World titles: %d\n", values[i]);
        printf("Nationalities: ");
        for (int j = 0; j < counts[i]; j++) {
            printf("%s", nationality_values[i][j]);
            if (j < counts[i] - 1) {
                printf(", ");
            }
        }
        printf("\n\n");
    }
}