#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *titolo;
    char *regista;
    int anno;
    float durata;
} Film;

static char *const nome_file = "../film.dat";

Film* RichiediFilm();
void StampaFilm(Film**,int);
void RicercaPerTItolo(Film**,int);
void OrdinaPerAnno(Film**, int);

int file_esiste();
Film** leggi_file(int*);
void salva_file(Film**, int);


int main(void) {

    Film** lista=NULL;

    int cont=0;
    int quantitaarray=10;
    int scelta;

    int risposta_file=file_esiste();

    if (risposta_file==1)
    {
        lista=leggi_file(&cont);
    }
    else    //se il file NON esiste
    {
        lista= (Film**)malloc(sizeof(Film*) *quantitaarray);
        if (lista==NULL) {
            printf("Errore durante allocazione dinamica della memeoria");
            free(lista);
            exit(1);
        }
    }

    printf("CINEMATRIX\n");
    do {
        printf("1 Aggiungi Film\n2 Visualizza Catalogo\n3 Cerca Film per TItolo\n4 Ordina Libreria per anno\n5 Salva ed Esci\nScelta:");
        scanf("%d",&scelta);

    switch (scelta) {

        case 1:
            if (cont>=quantitaarray)    //NON  c'è + spazio
            {
                quantitaarray+=10;
                Film** temp = realloc(lista, sizeof(Film*) * quantitaarray);
                if (temp==NULL)
                {
                    printf("Errore realloc.\n");
                    free(lista);
                    return 1;
                }
                lista = temp;
            }
                Film* temp=RichiediFilm();
                lista[cont]=temp;
                cont++;
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
            salva_file(lista,cont);
            printf("Ciao\n");
            exit(1);
        default:
            printf("Errore scelta.\n");
            break;
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

    return film;
}

void StampaFilm(Film** lista,int cont)
{
    if (cont==0) {
        printf("Nessun film in lista\n");
        return;
    }
    printf("Lista:\n");
    for (int i=0;i<cont;i++)
    {
        printf("Nome: %s Regista: %s Anno Pubblicazione: %d Durata: %f\n",lista[i]->titolo,lista[i]->titolo,lista[i]->titolo,lista[i]->titolo);
    }
}

void RicercaPerTitolo(Film** lista, int cont) {

    if (cont==0) {
        printf("Nessun film in lista\n");
        return;
    }

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
    for (int i=0;i<cont-1;i++)
    {
        for (int j=0;j<cont-1-i;j++)
        {
            if (lista[j]->anno>lista[j+1]->anno) {
                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
    printf("Lista Ordinanta per Anno di Uscita:\n");
    StampaFilm(lista,cont);
}

///////////////////////////   FILE //////////////////////////
int file_esiste() {
    FILE* file=fopen(nome_file,"r");
    if (file)
    {
        fclose(file);
        return 1;   //trovato
    }
        return 0;   //NON trovato
}

Film** leggi_file(int* dim) {
    FILE* file_bin=fopen(nome_file,"rb");
    if (file_bin==NULL) {
        printf("Errore apertura file");
        return NULL;
    }

    fread(dim,sizeof(int),1,file_bin);
    Film** listone=malloc(sizeof(Film*) * (*dim));
    if (listone==NULL) {
        printf("Errore allocazione memoria durante lettura file");
        fclose(file_bin);
        return 0;
    }
    fread(listone,sizeof(Film*),*dim,file_bin);
    fclose(file_bin);
    return listone;
}

void salva_file(Film** lista,int dim) {
    FILE* filebin=fopen(nome_file,"wb");
    if (filebin==NULL) {
        printf("Errore apertura file durante scrittura");
        return;
    }
    fwrite(&dim,sizeof(int),1,filebin);
    fwrite(lista,sizeof(Film*),dim,filebin);
    fclose(filebin);
}