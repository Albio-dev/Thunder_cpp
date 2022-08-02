# Proj_cpp_2022
Project for 2022 c++ course 

TODO:
https://docs.google.com/spreadsheets/d/1LiChLrq4bcnkJ4THrf_JW7a9WtJHMnwi73i_noTHzc0/edit#gid=0

# Report stub
Creata la repository git 
Impostato cmake con doxygen, preparati i target cmake richiesti (install, doc, make) 
Installato e testata la funzionalità di catch2 con i target di test (make test)
Impostato il clang-tidy/clang-format
documentata l'inizio della classe di base di gestione dei dati
creato un primo caso di test per la classe base
coverage funzionante: "./tester.sh && gcovr -r src ."
COVERAGE NON FUNZIONANTE mannaggia a gcovr, che proprio non ha intenzione di consentire che i sorgenti (.cpp) e i file di tracing (.gcda, .gcno) 
venissero separati, allora ho usato lcov che invece è molto più trattabile e in 3 righe di codice si ottiene un report perfetto 
ora la coverage è un target di esecuzione, ma semplicemente esegue lo script nella root

