#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "K16_56.h"
#include "../DES/Permutation.h"
#include "../Fonctions/fonctions.h"
#include "../DES/Tables_Permu.h"
#include "../DES/Des.h"

/*! \file      K16_56.c
 *  \brief     Fichier contenant les fonctiçons necessaires pour retrouver K16 56bits
 *  \author    ROBIN JORAN
 *  \version   1.00
 *  \date      25 Mars 2019
 */

 /*! \fn long bitsPerdus(long mask) 
 *  \brief Fonction qui permet de retrouver les bits perdus de la clé K
 *  \param mask : On applique le mask
 *  \return recup : la clé K avec les bits perdus
 */
long bitsPerdus(long mask) 
{
	long recup = 0;
	long bits_perdu[] = {14,15,19,20,51,54,58,60};
	
	for(int i = 0;i<8;i++) 
	{
		recup = concat(recup,shift_gauche(et_binaire(shift_droit(mask,i),1),(64 - bits_perdu[i])));
	}

	return recup;
}

 /*! \fn long trouverK16_56b(long msg_Clair,long msg_EncJuste,long K16_48b)
 *  \brief Fonction qui permet de retrouver la clé K16 de 56 bits
 *  \param msg_Clair : message Clair
 *  \param msg_EncJuste : message crypté juste
 *  \param K16_48bits : Clé K16 de 48bits
 *  \return K16 la clé de 56 bits
 */
long trouverK16_56b(long msg_Clair,long msg_EncJuste,long K16_48b)
{
	long K48_56;//K après inverse PC1
	long K56_64;//K après inverse PC2
	
	long mask = 0;
	long RE_K ;//Recherche exhaustive pour trouver les 8bits faux
	
	K48_56 = permutation(K16_48b,inverse_PC2,48,56);//Permutation PC2 inverse pour recuperer K48 sous forme 56
	
	K56_64 = permutation(K48_56,inverse_PC1,56,64);//Permutation PC1 inverse pour recupere K56 sous forme 64
	
	RE_K = K56_64;
	
	while(mask<256 && msg_EncJuste != DES(msg_Clair,RE_K) ) 
	{
		RE_K = concat(K56_64,bitsPerdus(mask));//2^8 =256 possibilités
		mask++;
	}

	if (mask == 256)
	{
		printf("\nErreur K 56bits\n");
	}
	
	return RE_K;
	
}
