#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Permutation.h"
#include "Tables_Permu.h"
#include "algo_keyschedule.h"
#include "../Fonctions/fonctions.h"

/*! \file      algo_keyschedule.h
 *  \brief     Fichier contenant l'algorithme des sous clés.
 *  \author    ROBIN JORAN
 *  \version   1.00
 *  \date      25 Mars 2019
 */

 /*! \fn long Rotation_Gauche(long K56)
 *  \brief Fonction qui permet la Rotation à gauche de chaque moitié de K56
 *  \param K56 :  clé 56bits
 *  \return un message crypté
 */
long Rotation_Gauche(long K56)
{
	long C28,D28; 
	long test;
	
	C28 = shift_droit(et_binaire(K56,0xFFFFFFF0000000),28);
	D28 = et_binaire(K56,0xFFFFFFF);
		
	test = shift_droit(C28,27);//Choix du bit le plus à droite	
	C28 = shift_gauche(C28,1);//Décalage des bits à gauche	
	C28 = et_binaire(C28,0xFFFFFFF);//Suppression du bit de poids fort
	C28 = concat(C28,test);//Mis à la position voulue

	test = shift_droit(D28,27);//Choix du bit le plus à droite	
	D28 = shift_gauche(D28,1);//Décalage des bits à gauche	
	D28 = et_binaire(D28,0xFFFFFFF);//Suppression du bit de poids fort
	D28 = concat(D28,test);//Mis à la position voulue
	
	C28 = shift_gauche(C28,28);
	
	return et_binaire(concat(C28,D28),0xFFFFFFFFFFFFFF);
}

 /*! \fn void DES_sousCle(long sous_cles[], long K)
 *  \brief Fonction qui permet de calculer chaque sous clé
 *  \param sous_cles[] :  Tableau des sous-clés
 *  \param K :  Clé K
 */
void DES_sousCle(long sous_cles[],long K64)
{
	//Permutation Key Schedule
	int perm_ks[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
	
	long K56 = permutation(K64,PC1,64,56);// Permutation de K64 dans PC1 donc on a K56
	
	for(int i=0;i<16;i++) 
	{
		if (perm_ks[i] == 1)
		{
			K56 = Rotation_Gauche(K56);
		}	
		else
		{
			K56 = Rotation_Gauche(Rotation_Gauche(K56));
		}

		sous_cles[i] = permutation(K56,PC2,56,48);//Permutation de K56 dans PC2 pour obtenir les 16 sous clés K48
	}
}
