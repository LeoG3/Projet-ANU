# Projet Anu
Thérémine avec la lumière

Principe : Jouer du thérémine par dessus une musique. Utiliser la quantité de lumière pour changer la tonalité du thérémine à l’aide d’une photo résistance. 

Composants :
1 arduino
1 breadboard
1 haut-parleur
1 deuxième haut-parleur pour la chanson (optionnel)
1 photo-résistance
1 résistance
1 bouton-poussoir
des fils électriques

Le bouton poussoir servira de bouton on-off.

Conception :
Réaliser le circuit suivant :  (cf image dans documentation.pdf)

Télécharger la librairie Tone https://github.com/bhagman/Tone puis notre code sur : https://github.com/LeoG3/Projet-Anu
Téléverser le fichier SongAndMelody.ino vers l’arduino
    

Utilisation :
Brancher l’arduino et l’allumer.
Un son se jouera pendant que le calibrage de la lumière se fera. Essayer de faire varier la lumière pendant cette phase de calibrage.
Allumez le son en appuyant sur le bouton poussoir
Vous pouvez éteindre le son en appuyant sur ce bouton
À vous de jouer !


Pour une autre utilisation plus proche d’un véritable Thérémine, il suffit d’installer la librairie Mozzi :
https://github.com/sensorium/Mozzi
installer depuis l’IDE Arduino ( Croquis -> Inclure une bibliothèqe -> ajouter un fichier.ZIP)
Ouvrir l’exemple : Control_echo_theremin
Téléverser le code. 

