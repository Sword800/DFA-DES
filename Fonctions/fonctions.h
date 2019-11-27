#ifndef FONCTIONS_COMMUNES_H
#define FONCTIONS_COMMUNES_H

/*! \file      fonctions.h
 *  \brief     Fichier contenant les différentes fonctions communes aux autres fichiers
 *  \author    ROBIN JORAN
 *  \version   1.00
 *  \date      25 Mars 2019
 */

long et_binaire(long a, long b);

long shift_droit(long a, int b);

long shift_gauche(long a, int b);
 
long concat(long a,long b);

long or_exclu(long a,long b);

long decoupage_msgR(long msg,long mask);

long decoupage_msgL(long msg,long mask);

int calcul_col_SBOX(int bloc6bits);

int calcul_lignes_SBOX(int bloc6bits);

int trouver_SBOX_4bits(int NUM_SBOX);

int trouver_SBOX_6bits(int SBOX);

long decoupe_4bits(long check,int NUM_SBOX);

long decoupe_6bits(long expansion,int SBOX);

int recup_sortieSBOX_fonctionF(int SBOX);

#endif
