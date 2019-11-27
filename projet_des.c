#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "K16_48/K16_48.h"
#include "K16_56/K16_56.h"
#include "K64/K64.h"
#include "DES/Des.h"
#include "DES/Messages.h"

/*! \file      projet_des.c
 *  \brief     Fichier contenant la fonction principale
 *  \author    ROBIN JORAN
 *  \version   1.00
 *  \date      25 Mars 2019
 */

/*! \fn int main()
 *  \brief Fonction qui exécute le programme
 *  \return retourne 0 une fois terminé
 */
int main()
{	
	long verif;					 					 
    long K16_48bits;
    long K_64bits;
    
    printf("\n###################### RECHERCHE K16 48BITS ######################\n\n");
    
    K16_48bits = trouverK16_48b(msg_EncJuste,msg_EncFaux);
    
	printf("\nK16_48bits = %lX \n",K16_48bits);
	
	
	
	
	K_64bits=trouver_K64(msg_clair,msg_EncJuste,K16_48bits);
	
	printf("\nK 64bits = %lX\n", K_64bits); 
	
	printf("\n###################### FIN RECHERCHE K 64BITS ######################\n\n");
	
	printf("\n###################### VERIFICATION K 64 BITS ######################\n\n");
	
	verif=DES(msg_clair,K_64bits);
	
	printf("Message Clair = %lX \n",msg_clair);
	printf("Message Chiffré Juste = %lX \n",msg_EncJuste);
	printf("Chiffré trouvé avec DES et K64 = %lX \n",verif);
   
    return 0;
}
