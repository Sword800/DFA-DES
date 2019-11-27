#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Permutation.h"
#include "../Fonctions/fonctions.h"
#include "../DES/Tables_Permu.h"

/*! \file      Permutation.c
 *  \brief     Fichier contenant la fonction de permutation selon les différentes tables
 *  \author    ROBIN JORAN
 *  \version   1.00
 *  \date      25 Mars 2019
 */

 /*!\fn long permutation(long msg, int tab_perm[] ,int tailleBits_in, int tailleBits_out) 
 *  \brief Fonction qui permet d'appliquer une Permutation avec le nombre d'éléments de tab_perm[] équivalent à tailleBits_out
 *  \param msg : Message à permuter selon la table
 *  \param tab_perm[] : tableau d'entiers d'une Permutation
 *  \param tailleBits_in : entier qui représente le nombre de bits à l'entrée de la permutation
 *  \param tailleBits_out : entier qui représente le nombre de bits à la sortie de la permutation
 *  \return final contenant le résultat final de la permutation correspondante
 */
long permutation(long msg, int tab_perm[] ,int tailleBits_in, int tailleBits_out) 
{	
	long tempo;
		
	long final = 0x0;
	long bit_position = 0x1;
	
	for (int i=0;i<tailleBits_out;i++) 
	{
		tempo = et_binaire(msg, shift_gauche(bit_position,tailleBits_in - tab_perm[i]));//Recuperation du bit
		
		if (tempo != 0)
		{		
			tempo = bit_position;
			tempo = shift_gauche(tempo,(tailleBits_out - i - 1));//On place le bit à sa place
		}
		
		final = concat(final,tempo);//Concatenation de ce bit avec final
	}
	return final;
}
