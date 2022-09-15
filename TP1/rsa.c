#include <stdio.h>
#include <stdli.h>
#include "gmp.h"


/*
 *Le fichier private key.txt contient les valeurs du module n et de l’exposant
      prive d d’une cl ́e RSA de 1024 bits.
  
  Ecrivez un programme qui utilise cette cl ́e pour d ́echiffrer le chiffr ́e c
  contenu dans le fichier ciphertext.txt par la m ́ethode du “square and multiply” de gauche `a droite.
  Votre programme devra comparer la valeur obtenue avec la valeur du clair  m se trouvant
  dans le fichier plaintext.txt.
 
 
  Variante de votre programme : utilisez la m ́ethode d’exponentiation “square
  and multiply” de droite `a gauche.
 *
 *
 **
 */


