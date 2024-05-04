#!/bin/bash

# Définir le dossier de destination
destination="$PWD/rapportsMAQAO"
mkdir -p "$destination"

# Parcourir tous les dossiers dans le dossier actuel
for folder in *_MAQAO_*/; do
    # Extraire le nom du dossier (sans le chemin)
    folder_name="${folder%/}"
    # Extraire les caractères avant le premier _ dans le nom du dossier
    prefix=$(echo "$folder_name" | cut -d'_' -f1)
    # Trouver les dossiers commençant par "measure" dans le dossier RESULTS
    measure_folder=$(find "${folder}RESULTS/" -maxdepth 1 -type d -name "measure*")
    measure_folder_name=$(basename "$measure_folder")
    new_measure_folder_name="${prefix}_${measure_folder_name}"
    # Copier le dossier de mesure vers le dossier de destination
    cp -r "$measure_folder" "$destination/${new_measure_folder_name}"
    # Afficher le chemin du nouveau dossier copié
    #echo "Nouveau dossier copié : $destination/${new_measure_folder_name}"

done

echo "La copie des dossiers est terminée."
