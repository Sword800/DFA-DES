#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "../DES/Tables_Permu.h"

/*! \file      fonctions.c
 *  \brief     Fichier contenant les différentes fonctions communes aux autres fichiers
 *  \author    ROBIN JORAN
 *  \version   1.00
 *  \date      25 Mars 2019
 */

 /*! \fn  long et_binaire(long a, long b)
 *  \brief Fonction qui permet d'appliquer un ET binaire entre a et b
 *  \param a : long a
 *  \param b : long b
 *  \return (a & b)
 */
long et_binaire(long a, long b)
{
	return (a & b);
}

 /*! \fn  long shift_droit(long a, int b)
 *  \brief Fonction qui permet de shifter à droite de b decalage
 *  \param a : long a
 *  \param b : int b
 *  \return (a >> b)
 */
long shift_droit(long a, int b)
{
	return (a >> b);
}

 /*! \fn  long shift_gauche(long a, int b)
 *  \brief Fonction qui permet de shifter à gauche de b decalage
 *  \param a : long a
 *  \param b : int b
 *  \return (a << b)
 */
long shift_gauche(long a, int b)
{
	return (a << b);
}
 
 /*! \fn  long concat(long a,long b)
 *  \brief Fonction qui permet de concatener 2 long
 *  \param a : long a
 *  \param b : long b
 *  \return (a | b) la ocncatenation des 2
 */
long concat(long a,long b)
{
	return (a | b);
}

 /*! \fn  long or_exclu(long a,long b)
 *  \brief Fonction qui permet de xor 2 long
 *  \param a : long a
 *  \param b : long b
 *  \return (a ^ b) la concatenation des 2
 */
long or_exclu(long a,long b)
{
	return (a ^ b);
}

/*! \fn long decoupage_msgL(long msg,long mask)
 *  \brief Fonction qui permet de stocker la partie L du message
 *  \return L16 fauté ou non selon le paramètre
 */
long decoupage_msgL(long msg,long mask)
{
	return (msg >> 32) & mask;
}

/*! \fn long decoupage_msgR(long msg,long mask)
 *  \brief Fonction qui permet de stocker la partie R du message
 *  \return R16 fauté ou non selon le paramètre
 */ 
long decoupage_msgR(long msg,long mask)
{
	return msg & mask;
}

/*! \fn int calcul_col_SBOX(int bloc6bits)
 *  \brief Fonction qui permet de calculer les colonnes des SBOX
 *  \return la valeur de la colonne
 */ 
int calcul_col_SBOX(int bloc6bits)
{
	return ((bloc6bits & 0x1E) >> 1);
}

/*! \fn int calcul_lignes_SBOX(int bloc6bits)
 *  \brief Fonction qui permet de calculer les lignes des SBOX
 *  \return la valeur de la ligne
 */ 
int calcul_lignes_SBOX(int bloc6bits)
{
	return (2 * ((bloc6bits & 0x20) >> 5) + (bloc6bits & 0x1));
}

/*! \fn long decoupe_4bits(long check,int NUM_SBOX)
 *  \brief Fonction qui permet de découper le check en blocs de 4bits pour chaque SBOX
 *  \param check : XOR entre L16 et L16_fauté
 *  \param NUM_SBOX : numéro courant de la SBOX
 *  \return les 4bits de sortie pour chaque SBOX
 */ 
long decoupe_4bits(long check,int NUM_SBOX)
{
	return check & get_4bits[NUM_SBOX];
}

/*! \fn long decoupe_6bits(long expansion,int NUM_SBOX)
 *  \brief Fonction qui permet de découper l'expansion en blocs de 6bits pour chaque SBOX
 *  \param expansion : Expansion De R15 ou R15f
 *  \param NUM_SBOX : numéro courant de la SBOX
 *  \return les 6bits pour chaque SBOX
 */ 
long decoupe_6bits(long expansion,int NUM_SBOX)
{
	return expansion & get_6bits[NUM_SBOX];
}

/*! \fn int trouver_SBOX_4bits(int NUM_SBOX)
 *  \brief Fonction qui permet de trouver la bonne SBOX où se trouve les 4bits de sortie
 *  \param NUM_SBOX : numéro courant de la SBOX
 *  \return la position des 4 bits pour la bonne SBOX
 */
int trouver_SBOX_4bits(int NUM_SBOX)
{
	return (7 - NUM_SBOX) * 4;
}

/*! \fn int trouver_SBOX_6bits(int NUM_SBOX)
 *  \brief Fonction qui permet de trouver la bonne SBOX où injecté les 6bits
 *  \param NUM_SBOX : numéro courant de la SBOX
 *  \return la position des 6bits pour la bonne SBOX
 */
int trouver_SBOX_6bits(int NUM_SBOX)
{
	return (7 - NUM_SBOX) * 6;
}

/*! \fn int recup_4bits_fonctionF(int SBOX)
 *  \brief Fonction qui permet de recuperer la sortie 4bits après SBOX
 *  \param SBOX : numéro courant de la SBOX
 *  \return les 4bits de chaque SBOX
 */
int recup_sortieSBOX_fonctionF(int SBOX)
{
	return (32 - 4 - SBOX*4);
}
