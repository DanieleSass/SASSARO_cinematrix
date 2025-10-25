#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *titolo;
    char *regista;
    int anno;
    float durata;
} Film;

Film* RichiediFilm();
void StampaFilm(Film**,int);
void RicercaPerTItolo(Film**,int);
void OrdinaPerAnno(Film**, int);

int main(void) {

    int cont=0;
    int quantitaarray=10;
    int scelta;
    Film** lista= (Film**)malloc(sizeof(Film*)*quantitaarray);

    printf("CINEMATRIX");
    do {
        printf("1 Aggiungi Film\n2 Visualizza Catalogo\n3 Cerca Film per TItolo\n4 Ordina Libreria per anno\n5 Salva ed Esci\nScelta:");
        scanf("%d",&scelta);

    switch (scelta) {

        case 1:
            if (cont>=quantitaarray)    //NON  c'è + spazio
            {
                quantitaarray+=10;
                lista=realloc(lista,sizeof(Film)*quantitaarray);
                if (lista==NULL) {
                    printf("Errore realloc");
                    return 0;
                }
            }
            else    //c'è abbastanza spazio
            {
                Film* temp=RichiediFilm();
                lista[cont]=temp;
                cont++;
            }
            break;

        case 2:
            StampaFilm(lista,cont);
            break;
        case 3:
            RicercaPerTItolo(lista,cont);
            break;
        case 4:
            OrdinaPerAnno(lista,cont);
            break;
        case 5:
            exit(1);
    }
    }while (scelta!=5);

    for (int i=0;i<cont;i++)
    {
        free(lista[i]->titolo);
        free(lista[i]->regista);
        free(lista[i]);
    }
    free(lista);
    lista=NULL;
    return 0;
}

Film* RichiediFilm()
{

    Film *film;

    printf("Nome Film");
    fgets(film->regista, 30, stdin);
    printf("Nome regista");
    fgets(film->titolo, 30, stdin);
    printf("Anno di pubblicazione");
    scanf("%d",&film->anno);
    printf("Durata");
    scanf("%f",&film->durata);
}

void StampaFilm(Film** lista,int cont)
{
    if (cont==0) {
        printf("Nessun film in lista");
        return;
    }

    for (int i=0;i<cont;i++)
    {
        printf("Nome: %s Regista: %s Anno Pubblicazione: %d Durata: %f",lista[i]->titolo,lista[i]->titolo,lista[i]->titolo,lista[i]->titolo);
    }
}

void RicercaPerTitolo(Film** lista, int cont) {
    printf("Provvedi a scrivere una parola per vedere i film che la contengono nel loro titolo");
    char parola[50];
    fgets(parola,50,stdin);
    for (int i=0;i<cont;i++) {
        if (strstr(lista[i]->titolo,parola) != NULL) {
            printf("Titolo: %s Regista: %s", lista[i]->titolo, lista[i]->regista);
        }
    }
}

void OrdinaPerAnno(Film** lista, int cont) {
    Film *temp;
    for (int i=0;i<cont;i++)
    {
        for (int j=0;j<cont-1;j++)
        {
            if (lista[j]->anno>lista[j+1]->anno) {
                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }

    StampaFilm(lista,cont);
}