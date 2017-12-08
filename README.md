# Émulation d'un émetteur NAVTEX

Le programme `navtex-em` permet de piloter une carte émetteur
[NAVTEX](https://fr.wikipedia.org/wiki/Navtex) à partir d'un Raspberry Pi.  
La carte émetteur est développée par le
[lycée Rouvière](https://www.lycee-rouviere.fr/index.php/superieur/b-t-s/systemes-numeriques-option-b)
de Toulon, France pour la formation des techniciens supérieurs en systèmes 
numériques option "Électronique et Communication".

Le câblage est le suivant:  
* broche 11 du GPIO (BCM_GPIO 17) pour le signal de données  
* broche 15 du GPIO broche (BCM_GPIO 22) pour le signal d'horloge

Il faudra évidement **relier la masse du Raspberry Pi à la masse de la carte émetteur**.


## Installation du programme

Le programme `navtex-em` utilise la libraire [wiringPi](http://wiringpi.com/).

### Raspbian Jessie et ultérieur (à partir du 24/09/2015)

Sur les nouvelles versions de Raspbian à partir de Jessie, wiringPi est 
disponible sous forme de paquet debian. Il suffit de télécharger le paquet
`naxtex` et de l'installer:

      wget 
      sudo gdebi navtex*.deb

Si gdebi n'est pas installé, il faudra le faire avec :

      sudo apt install gdebi

### Raspbian Wheezy

Il faut d'abord cloner le dépôt wiringPi et l'installer :

Puis on peut compiler et installer `navtex-em` :

## Utilisation

