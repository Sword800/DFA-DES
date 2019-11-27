#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Permutation.h"
#include "../Fonctions/fonctions.h"
#include "Tables_Permu.h"

/*! \file      fonction_f.c
 *  \brief     Fichier contenant la fonction f de DES.
 *  \author    ROBIN JORAN
 *  \version   1.00
 *  \date      25 Mars 2019
 */

 /*! \fn long f(long R, long sous_cle) 
 *  \brief Fonction qui permet d'appliquer la fonction f du DES
 *  \param R :  partie R du message
 *  \param sous_cle : clé sous_cle
 *  \return un message 48bits
 */
long f(long R, long sous_cle) 
{
	long Enter_Sbox;//Entree SBOX
	long Sortie_Sbox=0x0;//Sortie SBOX
	long expansion;// Expansion
	long ligne,colonne;//Ligne et Colonne SBOX
	long bloc_6bits;// Decoupage 6bits pour entréee des SBOX
	
	expansion = permutation(R,E,32,48);// Expansion de R
	
	Enter_Sbox = or_exclu(expansion,sous_cle);//Enter_Sbox = R xor les sous-clés sous_cle
	
	for (int i=0;i<8;i++)
	{
		bloc_6bits = shift_droit(Enter_Sbox,et_binaire((48 - 6 - i*6),0x3F));//Recuperation des 6bits pour chaque SBOX
		
		ligne = calcul_lignes_SBOX(bloc_6bits);//Calcul Ligne SBOX
		colonne = calcul_col_SBOX(bloc_6bits);//Calcul Colonne SBOX
		
		Sortie_Sbox = concat(Sortie_Sbox,shift_gauche(Sbox[i][ligne][colonne],(32 - 4 - i*4)));//Concatenation des sorties de chaque SBOX
	}
	
	return permutation(Sortie_Sbox,P,32,32);
}
