#ifndef K16_48_H
#define K16_48_H

/*! \file      K16_48.h
 *  \brief     Fichier contenant les fonctions necessaires pour retrouver K16 48bits
 *  \author    ROBIN JORAN
 *  \version   1.00
 *  \date      25 Mars 2019
 */

void analyse_bit_faute(long msg_EncJuste,long msg_EncFaux[],int num);

void affiche_sol(int NUM_SBOX,int solPossibles[][6],int cle[][6][64]);

long recupSolution(int cle[][6][64],int solPossibles[][6],int NUM_SBOX,long K16);


long trouverK16_48b(long msg_EncJuste, long msg_EncFaux[]);

#endif
