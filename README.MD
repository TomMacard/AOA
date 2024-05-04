# Projet AOA 2024

Myriam Hjiej (L1)
Tom Macard (L2)
Houda Talib (L3)
Jean-Christopher Sem (RAM)

# compilation

dans dossier src/ :
"make OPT=NOOPT" : compilation
"make go OPT=NOOPT" : compilation ET EXECUTION de toutes les versions (02, 03, ICX, funroll loops...)
"make go_maqao OPT=NOOPT" de même mais exécution avec maqao
"make go_phase2" : compile et execute sur Maqao tous les kernel en O2 (OPT5 a l'argument supplémentaire -msse2)
"make gorgor" : toutes les versions du kernel sur tous les compilateurs (OPT5 n'a pas -msse2 ici)

!!!! Attention, il faut s'assurer des chemins de maqao et ICX dans le Makefile pour les deux dernières commandes !!!!
