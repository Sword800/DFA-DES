#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Permutation.h"
#include "Des.h"
#include "fonction_f.h"
#include "algo_keyschedule.h"
#include "../Fonctions/fonctions.h"
#include "Tables_Permu.h"

/*! \file      Des.c
 *  \brief     Fichier contenant l'algorithme de DES.
 *  \author    ROBIN JORAN
 *  \version   1.00
 *  \date      25 Mars 2019
 */

 /*! \fn long DES(long msg_clair, long cle_K) 
 *  \brief Fonction qui permet execute l'algorithme de DES
 *  \param msg_clair :  message clair
 *  \param cle_K : clé K
 *  \return un message crypté
 */
long DES(long msg_clair,long K64) 
{
	long sous_cles[16]={0};//16 sous-clés K48 de K64
	long L,R;//Partie L et R du msg clair apres permutation IP
	long Li,Ri;//les Li et Ri de chaque tour
	
	DES_sousCle(sous_cles,K64);//Calcule des 16 sous-clés K48
	
	L = decoupage_msgL(permutation(msg_clair,IP,64,64),0xFFFFFFFF);//Calcule de L
	R = decoupage_msgR(permutation(msg_clair,IP,64,64),0xFFFFFFFF);//Calcule de R
	
	for (int i=0;i<16;i++) 
	{
		Li = R; // Li recoit R
		Ri = or_exclu(L,f(R,sous_cles[i])); //Ri recoit L xor f
		
		L = Li;//on stocke le nouvel Li dans L
		R = Ri;//on stocke le nouvel Ri dans R
	}
	
	return permutation(concat(shift_gauche(R,32),L),inverse_IP,64,64);//Permutation IP inverse
	
}
