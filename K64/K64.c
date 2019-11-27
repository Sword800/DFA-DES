#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../K16_56/K16_56.h"
#include "K64.h"
#include "../DES/Permutation.h"
#include "../Fonctions/fonctions.h"
#include "../DES/Tables_Permu.h"
#include "../DES/Des.h"

/*! \file      K64.c
 *  \brief     Fichier contenant les fonctiçons necessaires pour retrouver K 64bits
 *  \author    ROBIN JORAN
 *  \version   1.00
 *  \date      25 Mars 2019
 */

 /*! \fn long bitsParite(long K56b) 
 *  \brief Fonction qui permet de retrouver les bits de parité
 *  \param K56b : clé K 56bits
 *  \return recup : K 64bits
 */
long recup_bits_de_Parite(long K56b) 
{
	long recup = K56b;
	long test, parite;
	
	for(int i=0;i<8;i++) 
	{
		parite = 0;
		
		for(int j=0;j<8;j++) 
		{
			if(j!=7) 
			{
				test = shift_gauche(1,( ((7 - i) * 8) + (7 - j) ));
				test = et_binaire(K56b,test);
				
				if(test)
				{
					parite = or_exclu(parite,1);
				}
				else
				{
					parite = or_exclu(parite,0);
				}
			}
			else 
			{
				test = !parite;
				recup = concat(recup,shift_gauche(test,((7 - i) * 8)));
			}
		}
	}
	return recup;
}

 /*! \fn long trouver_K64(long clair, long chiffre, long K16) 
 *  \brief Fonction qui permet de retrouver K 64bits
 *  \param msg_Clair : message clair
 *  \param msg_EncJuste : message chiffré
 *  \param K16_56b : clé K 56bits
 *  \return K64b : K 64bits
 */
long trouver_K64(long msg_Clair,long msg_EncJuste,long K16_56b) 
{	
	printf("\n###################### RECHERCHE K16 56BITS ######################\n\n");
	
	long K56b = trouverK16_56b(msg_Clair, msg_EncJuste, K16_56b);
	
	printf("\n###################### FIN RECHERCHE K16 56BITS ######################\n\n");
	
	printf("\K 56bits = %lX\n", K56b);
	
	printf("\n###################### RECHERCHE K 64BITS ######################\n\n");
	
	long K64b = recup_bits_de_Parite(K56b);
	
	return K64b;
}
