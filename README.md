# Emulation d'un emetteur NAVTEX

Le programme `navtex-em` permet de piloter une carte emetteur NAVTEX à partir
d'un Raspberry Pi. La carte emetteur est développée par le lycée Rouvière de
Toulon, France pour la formation des techniciens en systèmes numériques option
"Electronique et Communication".

La broche BCM_GPIO 17 est utilisée pour générer le signal DATA, 


Installation du programme d'emission Navtex (navtex-em)

Le programme navtex-em utilise la libraire [wiringPi](http://wiringpi.com/).
Sur les nouvelles versions de raspbian, wiringPi est déjà installé sous forme
de paquets. Pour vérifier si c'est le cas:

        dpkg -l | grep wiringPi

Si vous avez quelque chose qui s'affiche c'est que wiringPi est installé:

        ii  wiringpi                              2.44                               armhf        The wiringPi libraries, headers and gpio command

Si vous n'avez rien qui s'affiche, il faut télécharger et installer wiringPi

