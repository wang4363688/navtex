/*
 *programmpe d'emission de message Navtex, via raspberry
 * associé à la carte modulation
 * auteur:joan Erra BTSSN lycée Rouvière
 */

#include <stdio.h>
#include <stdlib.h>


#include <wiringPi.h>
// DATA Pin - wiringPi pin 0 is BCM_GPIO 17 is pin plug 11
#define DATA 0

// horl Pin - wiringPi pin 3 is BCM_GPIO 22 is pin plug 15.
#define horl 1


/* mot binaire de 7 bits à envoyer et codant un caractère encode navtex*/
char caractere_navtex ;

/* tableau contenant les caractères du message en code ASCII*/
char Tabtouche[256];

/* tableau contenant les caractères de la trame en code ASCII*/
char trame_navtex[300];

/* tableau contenant les caractères du message en code navtex*/
char codenavtex[300];


/* tableau contenant les caractères du message en code navtex en mode B collectif*/
/* le mode B collectif consiste à envoyer deux fois chaque caractère */
/*mais de façon entrelaçée tous les cinq caractères*/

char trame_modeB[600];

/* tableau de conversion code ASCII des codes 41hex  5ahex et 61hex  7Ahex: lettres en code navtex*/
char Tab_lettres[26] = {0x71, 0x27, 0x5c, 0x65, 0x35, 0x6c, 0x56, 0x4b, 0x59, 0x74, 0x3c, 0x53,
                        0x4e, 0x4d, 0x47, 0x5a, 0x3a, 0x55, 0x69, 0x17, 0x39, 0x1e, 0x72, 0x2e, 0x6a, 0x63
                       };

/* tableau de conversion code ASCII des codes 20hex  3Fhex :chiffres et ponctuation en code navtex*/
char Tab_chiffres[33] = {
  0x1d, 0x65, 0x69, 0x1d, 0x1d, 0x1d,
  0x1d, 0x69, 0x3c, 0x53, 0x1d, 0x63,
  0x4d, 0x71, 0x4e, 0x2e, 0x5a, 0x3a,
  0x72, 0x35, 0x55, 0x17, 0x6a, 0x39,
  0x59, 0x47, 0x5c, 0x1d, 0x1d, 0x1e,
  0x1d, 0x27
};

/* tableau entete "ZCZC WA 00"en code navtex*/
char entete[13] = {0x63, 0x5c, 0x63, 0x5c, 0x1d, 0x72, 0x71, 0x36, 0x5a, 0x5a, 0xf, 0x1b, 0x2d};

void acquisition();
void traduire();
void remplir_trame_navtex();
void convertir_modeB();
void envoyer7bits();
void envoyer_trame();
void envoyer_mise_en_phase();
void attendre_front_H();
//void Inittab ();

int main() {
  wiringPiSetup () ;
  // Set RPI  PIN plug 15 (horl) to be an input
  pinMode (horl, INPUT) ;
  //  with a pullup

  // Set the PIN plug 11 (DATA) to be an output
  pinMode (DATA, OUTPUT);
  char touche[2];
  do {
    system ("clear");
    // Inittab();
    //printf("\n retour d'inittab");
    acquisition();/*aquérir le message de lettres tapé en  clavier*/


    traduire();// traduire ce message en codes navtex

    remplir_trame_navtex();

    convertir_modeB();//convertir en mode B collectif

    envoyer_trame();// envoyer toute la trame en série , sur le bit D0 du port parallèle

    printf ("\n appuyer sur entrée pour envoyer un autre message, pour quitter CTRL C \n");

  }
  while (fgets (touche, 2, stdin) != NULL);
  return 0 ;
}
//*******************************************************************/

/*void Inittab ()
{
int a;
for (a=0;a<256;a++)
  {
  Tabtouche[a]=0;
  codenavtex[a]=0;
  trame_navtex[a]=0;
  }
for (a=256;a<600;a++)
  {
  trame_modeB[a]=0;
  }
}
* */
//**********************************************************************/
void acquisition() {

  printf ("Tapez un message de 255 caracteres maxi,sans saut de ligne,\n valider par la touche entree\n");
  printf (" message  :  ");
  fgets (Tabtouche, 256, stdin);
  return ;
}

//**********************************************************************/

void traduire() {

  int indice, b, c;
  char lettres_chiffres = 'L';

  printf ("\n message en code ASCII notation hexadecimale :\n");
  for (b = 0; Tabtouche[b] != 0X0A; b++) {
    printf ("%X ", Tabtouche[b]);
  }
  c = 0;
  for (b = 0; Tabtouche[b] != 0X0A; b++) {
    if (Tabtouche[b] == 0x20) {
      codenavtex[c] = 0x1d ;
    }
    else if (Tabtouche[b] > 0x20 && Tabtouche[b] < 0x40) {
      indice = Tabtouche[b] - 0x20;
      if (lettres_chiffres == 'L') {
        lettres_chiffres = 'C';
        codenavtex[c] = 0x36, c++;
      }
      codenavtex[c] = Tab_chiffres[indice];
    }
    else if (Tabtouche[b] > 0x40 && Tabtouche[b] < 0x5B) {
      indice = Tabtouche[b] - 0x41;
      if (lettres_chiffres == 'C') {
        lettres_chiffres = 'L';
        codenavtex[c] = 0x2d;
        c++;
      }
      codenavtex[c] = Tab_lettres[indice];
    }
    else if (Tabtouche[b] > 60 && Tabtouche[b] < 0x7B) {
      indice = Tabtouche[b] - 0x61;
      if (lettres_chiffres == 'C') {
        lettres_chiffres = 'L';
        codenavtex[c] = 0x2d;
        c++;
      }
      codenavtex[c] = Tab_lettres[indice];
    }
    c++;
  }

  if (lettres_chiffres == 'C') {
    lettres_chiffres = 'L';
    codenavtex[c] = 0x2d;
    c++;
  }
  codenavtex[c] = 0X0F;
  codenavtex[c + 1] = 0X1B;
  codenavtex[c + 2] = 0X1B;
  codenavtex[c + 3] = 0X4D;
  codenavtex[c + 4] = 0X4D;
  codenavtex[c + 5] = 0X4D;
  codenavtex[c + 6] = 0X4D;
  codenavtex[c + 7] = 0X0F;
  codenavtex[c + 8] = 0X1B;
  codenavtex[c + 9] = 0X1B;
  codenavtex[c + 10] = 0X0D;

  printf ("\n \n message en code Navtex notation hexadecimale :\n");
  for (b = 0; codenavtex[b] != 0X0F; b++) {
    printf ("%X ", codenavtex[b]);
  }
  return;


}

void remplir_trame_navtex() {
  int i, j;
  for (i = 0; i < 13; i++) {
    trame_navtex[i] = entete[i];
  }



  for (j = 0; codenavtex[j] != 0x0d; j++) {
    trame_navtex[i] = codenavtex[j];
    i++;
  }
  trame_navtex[i] = 0x0d;
  return;

}






void convertir_modeB() {
  int d = 0;
  int b = 0;
  for (b = 0; trame_navtex[b] != 0X0D; b = b + 1) {
    trame_modeB[d] = trame_navtex[b];
    d = (d + 2);
  }

  d = 5;
  for (b = 0; trame_navtex[b] != 0X0D; b = b + 1) {
    trame_modeB[d] = trame_navtex[b];
    d = (d + 2);
  }
  printf ("\n \n message en mode B collectif(sans entete ni caratères de fin) en notation hexadecimale : \n");
  trame_modeB[d + 1] = 0X0D;

  for (b = 26; b <= (d + 2 - 22); b++) {
    printf ("%X ", trame_modeB[b]);
  }
  return;

}



void envoyer_trame() {
  int c;
  printf ("\n  \n envoie des signaux de mise en phase pendant quelques secondes :\n");
  envoyer_mise_en_phase();


  printf ("\n \n envoyer le reste de la trame : \n ");

  for (c = 0; trame_modeB[c] != 0X0F; c++) {
    caractere_navtex = trame_modeB[c];
    printf ("(%X) ", trame_modeB[c]);
    envoyer7bits();
  }

  printf ("\n transmission terminee");
  return;

}





void envoyer_mise_en_phase() {
  int n;
//printf(" \n sucessions de mots binaires de 7 bits transmis pendant la mise en phase: \n");
  for (n = 0; n < 10; n++) { // envoyer la succession de caractères de mise en phase pendant 14 secondes
    printf ("(0X33) ");
    caractere_navtex = 0x33;
    envoyer7bits();
    printf ("(0X78) ");
    caractere_navtex = 0x78;
    envoyer7bits();
  }
  return;
}



void envoyer7bits() {
// d'abord émettre le poids fort
  char mask = 0X40;
  char nbdecal;
  char resultatmasque;

  for (nbdecal = 0; nbdecal < 7; nbdecal++) {
    resultatmasque = caractere_navtex & mask;
    if (resultatmasque == 0x00) {
      attendre_front_H();
      digitalWrite (DATA, LOW) ; // Off
      printf ("0");
    }
    else {
      attendre_front_H();
      digitalWrite (DATA, HIGH) ; // On
      printf ("1");
    }

    mask = mask >> 1;
  }
  printf ("  ");
  return;

}


void attendre_front_H() {
  //while(digitalRead (horl)==0x00);
  //while(digitalRead (horl)==0x01);
  return;

}
