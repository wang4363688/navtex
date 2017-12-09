# Émulation d'un émetteur NAVTEX

Le programme `navtex-em` permet de piloter une carte émetteur
[NAVTEX](https://fr.wikipedia.org/wiki/Navtex) à partir d'un Raspberry Pi.  
La carte émetteur est développée par le
[lycée Rouvière](https://www.lycee-rouviere.fr/index.php/superieur/b-t-s/systemes-numeriques-option-b)
de Toulon, France pour la formation des techniciens supérieurs en systèmes 
numériques option "Électronique et Communication".

## Utilisation

Il suffit de relier les signaux broches du GPIO au connecteur B1 de la carte
émission, le câblage est le suivant:  
* broche 15 du GPIO (BCM_GPIO 22) pour le signal d'horloge **B1a**. C'est une
entrée GPIO, comme la carte émetteur génère ce signal en logique 5V, il est 
nécessaire d'**ajouter un pont diviseur constitué de 2 résistances de 180&Omega; **
* broche 11 du GPIO (BCM_GPIO 17) pour le signal de données **B1b** (sortie GPIO)  
* broche 14 du GPIO (GND) pour la masse **B1c**.

Il suffit de taper `navtex-em` sur la ligne de commande:

    $ navtex-em

Le programme est interactif, il suffit de taper le texte à transmettre:

    Tapez un message de 255 caracteres maxi,sans saut de ligne,
     valider par la touche entree
     message  :  Test

     message en code ASCII notation hexadecimale :
    54 65 73 74 
     
     message en code Navtex notation hexadecimale :
    17 35 69 17 
     
     message en mode B collectif(sans entete ni caratères de fin) en notation hexadecimale : 
    17 1B 35 2D 69 17 17 35 F 69 1B 17 1B F 
      
     envoie des signaux de mise en phase pendant quelques secondes :
    (0X33) 0110011  (0X78) 1111000  (0X33) 0110011  (0X78) 1111000  (0X33) 0110011  (0X78) 1111000  (0X33) 0110011  (0X78) 1111000  (0X33) 0110011  (0X78) 1111000  (0X33) 0110011  (0X78) 1111000  (0X33) 0110011  (0X78) 1111000  (0X33) 0110011  (0X78) 1111000  (0X33) 0110011  (0X78) 1111000  (0X33) 0110011  (0X78) 1111000  
     
     envoyer le reste de la trame : 
     (63) 1100011  (0) 0000000  (5C) 1011100  (0) 0000000  (63) 1100011  (63) 1100011  (5C) 1011100  (5C) 1011100  (1D) 0011101  (63) 1100011  (72) 1110010  (5C) 1011100  (71) 1110001  (1D) 0011101  (36) 0110110  (72) 1110010  (5A) 1011010  (71) 1110001  (5A) 1011010  (36) 0110110  
     transmission terminee
     appuyer sur entrée pour envoyer un autre message, pour quitter CTRL C 

L'appui simultané sur CTRL + C, permet d'arrêter le programme, 
Entrée pour émettre un nouveau message.

### Schéma de la carte d'émission

![Schéma](https://raw.githubusercontent.com/epsilonrt/navtex/master/img/navtex-em-sch.png)

## Installation du programme `navtex-em`

Le programme `navtex-em` utilise la libraire [wiringPi](http://wiringpi.com/).

### Raspbian Jessie et ultérieur

Sur les versions de Raspbian à partir du 24/09/2015, wiringPi est 
disponible sous forme de paquet debian. Il suffit de télécharger le paquet
`naxtex` et de l'installer:

    $ cd
    $ wget https://github.com/epsilonrt/navtex/releases/download/v1.0/navtex_1.00_armhf.deb
    $ sudo gdebi navtex*.deb

Cela doit donner un résultat similaire à ça:

    Reading package lists... Done
    Building dependency tree        
    Reading state information... Done
    Building data structures... Done 
    Building data structures... Done 

    navtex built using CMake
    Voulez-vous installer le paquet logiciel ? [o/N] :o
    (Lecture de la base de données... 205576 fichiers et répertoires déjà installés.)
    Préparation du dépaquetage de navtex_1.00_armhf.deb ...
    Dépaquetage de navtex (1.00) sur (1.00) ...
    Paramétrage de navtex (1.00) ...

**C'est tout !**

Si gdebi n'est pas installé, il faudra le faire avec :

      $ sudo apt install gdebi

Pour les versions ultérieures, on remplacera `1.00`, par le numéro de la dernière version.

### Raspbian Wheezy

Sur les versions plus anciennes de Raspbian, il faut d'abord cloner le dépôt 
wiringPi, le compiler et l'installer :

    $ cd
    $ git clone git://git.drogon.net/wiringPi
    $ cd ~/wiringPi
    $ ./build

Puis on peut cloner le dépôt navtex, compiler et installer `navtex-em` :

    $ cd
    $ git clone https://github.com/epsilonrt/navtex.git
    $ cd ~/navtex
    $ ./build
    $ ./install


