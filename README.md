# IN204 - Comic Book Reader

Comic Book Reader réalisé en C++ dans le cadre du cours IN204 "Génie Logiciel et Programmation Orientée Objet" à ENSTA Paris

## Description du projet

L'objectif de ce logiciel est de pouvoir fournir un lecteur permettant de prendre en charge les différents formats utilisés par les bandes dessinées. Dit autrement, notre objectif est de créer une visionneuse d'images adapatée à la lecture de bandes dessinées, ces derniers étant souvent sous l'extension .cbz ou .cbr

## Dépendances
* Qt version 5.7.0 (Utilisé pour la gestion de l'interface)
* Libarchive (Utilisation pour la gestion des archives)

## Compilation
```
qmake
make
./ComicBookReader
```
![CBR Image](CBR%20Image.png)

## Fonctionnalités
* Ouverture d'un Comic Book (formats acceptés : *.cbr, *.cbz, *.rar, *.zip, *.7zip, *.7z) contenant des images (formats acceptés : *.bmp, *.gif, *.jpeg, *.jpg, *.png)
* Possibilité de choisir et d'extraire des pages d'un ouvrage au format .cbz
* Navigation possible entre les différentes pages (première, dernière, suivante, précédente ou au choix) avec les boutons ou à l'aide de raccourci (Flèches directionnelles droite/gauche, bouton Début/Fin)
* Possibilité de redimensionner l'image (zoom, adapté à la page, adapté à la largeur) avec les boutons ou à l'aide de raccourci (Ctrl + Molette, Ctrl + +, Ctrl + -, Ctrl + 0)
* Affichage en mode double page avec choix si page de couverture ou non (première page unique ou double page)
