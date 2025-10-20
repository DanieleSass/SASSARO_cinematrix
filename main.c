#include <stdio.h>

typedef struct {
    char *titolo;
    char *regista;
    int anno;
    float durata;
} Film;

Film RichiediFilm();
void StampaFilm(Film*,int);
int main(void) {
    int cont;
    return 0;
}

Film RichiediFilm()
{
    printf("Nome Film");
    printf("Nome regista");
    printf("Anno di pubblicazione");
    printf("Durata");
}

void StampaFilm(Film* lista,cont)
{
    for (int i=0;i<cont;i++)
    {
        printf("Nome: Regista: Anno Pubblicazione: Durata: ");
    }
}