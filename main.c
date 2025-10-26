#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *titolo;
    char *regista;
    int anno;
    float durata;
} Film;

static char *const nome_file = "../catalogo.dat";

Film* RichiediFilm();
void StampaFilm(Film**,int);
void RicercaPerTitolo(Film**, int);
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
        getchar();

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
            RicercaPerTitolo(lista,cont);
            break;
        case 4:
            OrdinaPerAnno(lista,cont);
            break;
        case 5:
            salva_file(lista,cont);
            printf("Ciao\n");
            break;
        default:
            printf("Errore scelta\n");
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
    Film *film=malloc(sizeof(Film));

    film->titolo = malloc(50 * sizeof(char));
    film->regista = malloc(50 * sizeof(char));

    printf("Nome Film\n");
    fgets(film->titolo, 50, stdin);

    printf("Nome regista\n");
    fgets(film->regista, 50, stdin);

    do
    {
        printf("Anno di pubblicazione: \n");
        if (scanf("%d", &film->anno) != 1) {
            printf("Errore\n");
            while (getchar() != '\n'); // pulisce il buffer
        } else {
            getchar(); // <-- pulisce il '\n' rimasto
            break; // input corretto → esci
        }
    }while (1);

    do {
        printf("Durata: \n");
        if (scanf("%f", &film->durata) != 1) {
            printf("Errore\n");
            while (getchar() != '\n'); // pulisce il buffer
        } else {
            getchar(); // <-- pulisce il '\n' rimasto
            break; // input corretto → esci
        }
    }while (1);


    film->titolo[strcspn(film->titolo, "\n")] = '\0';
    film->regista[strcspn(film->regista, "\n")] = '\0';
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
        printf("Nome: %s Regista: %s Anno Pubblicazione: %d Durata: %f\n",lista[i]->titolo,lista[i]->regista,lista[i]->anno,lista[i]->durata);
    }
}

void RicercaPerTitolo(Film** lista, int cont)
{

    if (cont==0) {
        printf("Nessun film in lista\n");
        return;
    }

    printf("Provvedi a scrivere una parola per vedere i film che la contengono nel loro titolo\n");
    char parola[50];
    fgets(parola,50,stdin);
    parola[strcspn(parola, "\n")] = 0;
    for (int i=0;i<cont;i++) {
        if (strstr(lista[i]->titolo,parola) != NULL) {
            printf("Titolo: %s  Regista: %s\n", lista[i]->titolo, lista[i]->regista);
        }
    }
}

void OrdinaPerAnno(Film** lista, int cont)
{
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
int file_esiste()
{
    FILE* file=fopen(nome_file,"r");
    if (file)
    {
        fclose(file);
        return 1;   //trovato
    }
        return 0;   //NON trovato
}


Film** leggi_file(int* dim) {
    FILE* file_bin;
    fopen(nome_file,"rb");
    if (file_bin==NULL)
    {
        printf("Errore apertura file");
        return NULL;
    }

    fread(dim,sizeof(int),1,file_bin);

    Film** listone=malloc(sizeof(Film*) * (*dim));
    if (listone==NULL)
    {
        printf("Errore allocazione memoria durante lettura file");
        fclose(file_bin);
        return 0;
    }

    for (int i = 0; i < *dim; i++)
    {
        listone[i] = malloc(sizeof(Film));
        listone[i]->titolo = malloc(50);
        listone[i]->regista = malloc(50);

        fread(listone[i]->titolo, sizeof(char), 50, file_bin);
        fread(listone[i]->regista, sizeof(char), 50, file_bin);
        fread(&listone[i]->anno, sizeof(int), 1, file_bin);
        fread(&listone[i]->durata, sizeof(float), 1, file_bin);

    }
    fclose(file_bin);
    return listone;
}



    void salva_file(Film** lista,int dim){
        OrdinaPerAnno(lista,dim);
        FILE* filebin=fopen(nome_file,"wb");
        if (filebin==NULL) {
            printf("Errore apertura file durante scrittura");
            return;
        }

        fwrite(&dim,sizeof(int),1,filebin);

        for (int i=0; i <dim;i++)
        {
            fwrite(lista[i]->titolo,sizeof(char),50,filebin);
            fwrite(lista[i]->regista,sizeof(char),50,filebin);
            fwrite(&lista[i]->anno, sizeof(int), 1, filebin);
            fwrite(&lista[i]->durata, sizeof(float), 1, filebin);
        }


        fclose(filebin);
    }
