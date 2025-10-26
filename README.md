**CINEMATRIX – Videoteca Digitale in C**

Gestisce una piccola videoteca con struct, puntatori, memoria dinamica e file binari.

Struttura dati:

- struct Film: titolo, regista, anno, durata (ore)

- Film memorizzati in array dinamico di puntatori

- Funzionalità

- Caricamento automatico da catalogo.dat se presente

- Aggiunta film (memoria allocata dinamicamente, array aggiornato)

- Visualizzazione catalogo in formato tabellare

- Ricerca film per titolo (ricerca parziale)

- Ordinamento per anno crescente

- Salvataggio su file binario

- Pulizia della memoria alla chiusura


  Requisiti tecnici

- struct e puntatori a struct (->)

- Allocazione dinamica (malloc, realloc, free)

- File binari (fread, fwrite)

- Ordinamento array dinamico per anno

- Modularità e gestione errori