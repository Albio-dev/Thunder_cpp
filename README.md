# Proj_cpp_2022
Project for 2022 c++ course 

TODO:
https://docs.google.com/spreadsheets/d/1LiChLrq4bcnkJ4THrf_JW7a9WtJHMnwi73i_noTHzc0/edit#gid=0
THUNDER:
https://github.com/thunder-project/thunder
PROGETTO:
https://github.com/Albio-uni/Proj_cpp_2022

# Report stub
Creata la repository git 
Impostato cmake con doxygen, preparati i target cmake richiesti (install, doc, make) 
Installato e testata la funzionalità di catch2 con i target di test (make test)
Impostato il clang-tidy/clang-format
documentata l'inizio della classe di base di gestione dei dati
creato un primo caso di test per la classe base
coverage funzionante: "./tester.sh && gcovr -r src ."
COVERAGE NON FUNZIONANTE mannaggia a gcovr, che proprio non ha intenzione di consentire che i sorgenti (.cpp) e i file di tracing (.gcda, .gcno) venissero separati, allora ho usato lcov che invece è molto più trattabile e in 3 righe di codice si ottiene un report perfetto 
ora la coverage è un target di esecuzione, ma semplicemente esegue lo script nella root
implementata l'estrazione dei dati e ammessa l'estrazione di sotto matrici
implementate le classi figlie di ndarray: immagini e serie
NDArray si basa su vector che contiene informazioni sui dati sullo stack e i dati veri e propri sullo heap quindi anche la nostra struttura NDArray contiene solo poche informazioni sullo stack e, all'interno dei vector, puntatori ai dati veri e propri sullo heap
NDArray si può creare a partire da vector, o anche array initializer {n1, n2...}. La cosa migliore è che dal punto di vista dell'indirizzamento un vettore {5, 1} è esattamente equivalente ad uno {5}
ho aggiunto un controllo in modo che anche {0} non sia una dimensione di vettore accettabile

Aggiunta funzione fromrandom, da capire come generare meglio la distribuzione in modo dinamico diciamo... Maledetti questi template
Aggiunta estrazione frombinary (valori file default sono [11, 12 13] o simili). Controlli vari dentro funzione
Nota funzione get_current_dimension che magari puó essere bello avere una funzione che quando si modifica shape parta automaticamente
Per funzione get_current_dimension controllare sia tutto okay e usarla in giro dopo assegnamenti. O usare funzione che fa assegnamento e controlla
Fromfile non serve, si userá frompath e poi un controllo delle estensioni. Voglio usare std::path ma di C++17
Fromexample prende i valori dalle immagini e per le Series da fromrandom, sarebbe bello avere un file e poi fromtext

Sto lavorando su fromPNG e fromTIF. C'é la libreria CImg.h che é un singolo .h -> importata e non funziona perché vuole tipo le librerie in X11
"png.h" che si devono installare con alcuni comandi di brew ma non gli piacciono. Giornata persa su questo diciamo :sad:
Noto ora che sul sito fanno scaricare i binari da http://cimg.eu/download.html invece che le librerie, domani provo altrimenti devo passare a Linux
o cose simili ..... AH per migliorare il tutto il link della libreria portabile non funziona

implementate tutte le funzioni base e cominciato a portarle nelle classi figlie
problema tipo. quando dalla classe figlia di chiama la classe base passando la classe figlia nessun problema (downcasting) ma quando bisogna accettare il risultato della classe padre e trasformarlo in una classe figlia si rompe di brutto (upcasting). soluzione: implementato nella classe figlia l'operatore di conversione che è anche molto semplice, ma c++ da solo non era capace di gestirlo
