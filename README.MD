# Projet AOA 2024

Myriam Hjiej (L1)
Tom Macard (L2)
Houda Talib (L3)
Jean-Christopher Sem (RAM)

# compilation

dans dossier src/ :
"make OPT=NOOPT" : compilation sans optimisation et en GCC 02
"make go OPT=NOOPT" : compilation ET EXECUTION de toutes les versions (02, 03, ICX, funroll loops...)
"make go_maqao OPT=NOOPT" de même mais exécution avec maqao

!!!! Attention, il faut s'assurer des chemins de maqao et ICX dans le Makefile pour les deux dernières commandes !!!!