# Thunder

## Autori

Alberto Carli

Aleardo Lodi VR463652 [E-Mail](mailto:aleardo.lodi@studenti.univr.it)

## Link progetto originale 

http://thunder-project.org/

## Descrizione del progetto
Il nostro progetto é una riscrittura di una sezione del codice di [thunder](https://github.com/thunder-project/thunder) in C++17. 
Il progetto originario é una collezione di librerie, suddivisa in piú pacchetti, per importare immagini o serie dati e poi analizzarle. 
Scritto in python puó essere eseguito in locale o con il supporto di uno Spark cluster.
Thunder é suddiviso in un core package che definisce delle semplici funzioni di lettura e scrittura dei dati e da vari pacchetti (si veda [questo](https://github.com/thunder-project/thunder-regression) o [questo](https://github.com/thunder-project/thunder-registration)) di supporto.

Come progetto non é piú supportato e attivamente in sviluppo, per questo durante la fase di benchmark abbiamo trovato alcune funzioni che tornano errori.


## Il porting
### Design implementation choices
IL nostro porting della libreria comprende dua parti: il caricamento d'immagini e serie numeriche e il poter applicare alcune operazioni classiche sui dati.
Per quanto concerne il caricamento dei dati in un oggetto generico della nostra libreria é possible tramite vari sistemi:
- Passare al costruttore array o liste 
- Caricare un'immagine di tipo png
- Caricare un'immagine di tipo tif
- Estrarre una serie numerica o serie da un file

Questi dati vengono poi salvati in un array all'interno dell'oggetto NDArray da cui si potranno poi accedere varie funzioni. 
Delle funzioni aggiuntive sono state scelte la maggior parte presente nel pacchetto base di [thunder](https://github.com/thunder-project/thunder).
Quali ad esempio: count, max, min, filter, std, var...


## Program workflow

## I/O esempi

## Code statistics 
### __cloc tool__
### Coverage
### Static analysis (maybe)

## Testing

É stata usata la libreria catch2 importata in third_party/ per eseguire i test. 
Per ogni componente principale sono stati creati dei file equivalenti per il testing, sia per testare il caricamento di file e immagini sia per tutte le funzioni create.



## Third party libraries

## Performance C++ vs Python