#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "K16_48.h"
#include "../DES/Permutation.h"
#include "../Fonctions/fonctions.h"
#include "../DES/Tables_Permu.h"

/*! \file      K16_48.c
 *  \brief     Fichier contenant les fonctions necessaires pour retrouver K16 48bits
 *  \author    ROBIN JORAN
 *  \version   1.00
 *  \date      25 Mars 2019
 */

 /*! \fn void affiche_sol(int NUM_SBOX,int t1[],int t2[],int s)
 *  \brief Fonction qui permet d'afficher les résultats
 *  \param NUM_SBOX : numéro courant de la SBOX
 *  \param solPossibles[][6] : Tableau des solutions possibles
 *  \param cle[][6][64] : Tableau des clé Possibles 
 */
void affiche_sol(int NUM_SBOX,int solPossibles[][6],int cle[][6][64])
{
	 printf("\n###################### Sbox %d ###################### \n\n", NUM_SBOX + 1);
	 
		for (int nbr_faux=0;nbr_faux<6;nbr_faux++) 
		{
			printf("Chiffré Faux %d : %d clés K16 ->	", nbr_faux+1, solPossibles[NUM_SBOX][nbr_faux]);
			
			for (int i =0;i<solPossibles[NUM_SBOX][nbr_faux];i++) 
			{
				printf("%X ", cle[NUM_SBOX][nbr_faux][i]);
			}
			printf("\n"); 
		}
}

 /*! \fn int analyse_bit_faute(long msg_EncJuste,long msg_EncFaux[],int num)
 *  \brief Fonction qui permet d'analysé la position du bit fauté sur chaque chiffré 
 *  \param msg_EncJuste : Message crypté juste
 *  \param msg_EncFaux : Message crypté faux
 *  \param num : numéro du chiffré
 */
void analyse_bit_faute(long msg_EncJuste,long msg_EncFaux[],int num)
{	
	long msg_Dec_EncJuste,msg_Dec_EncFaux;//Dechiffré OK par rapport au message crypté OK
	long R16,R16f,R15,R15f;
	long position_bit_faute;
	int tmp_pos =33;
	
	//~ printf("\n###################### PERMUTATION IP Chiffrés Juste ######################\n\n");
	 
	msg_Dec_EncJuste = permutation(msg_EncJuste, IP, 64, 64); 

    R16 = decoupage_msgL(msg_Dec_EncJuste,0xFFFFFFFF);
    R16 = decoupage_msgR(R16,0xFFFFFFFF);
    
    R15=R16;
   
		//~ printf("\n###################### PERMUTATION IP Chiffrés Faux ######################\n\n");
    
		msg_Dec_EncFaux = permutation(msg_EncFaux[num], IP, 64, 64);
  
		R16f = decoupage_msgL(msg_Dec_EncJuste,0xFFFFFFFF);
		R16f = decoupage_msgR(R16f,0xFFFFFFFF);
		
		R15f=R16f;
		
		position_bit_faute = or_exclu(R15,R15f);
		
		//~ printf("\n###################### XOR ######################\n\n");
		
		while(position_bit_faute)
		{
			tmp_pos--;
			position_bit_faute = position_bit_faute >> 1;
		}
		
		//~ printf("\n###################### POSITION BIT FAUTE ######################\n\n");
		
		if(num <9)
		{
			printf("Chiffré faux  %d --> Position bit fauté %d \n",num+1,tmp_pos);
		}
		else
		{
			printf("Chiffré faux %d --> Position bit fauté %d \n",num+1,tmp_pos);
		}
}

 /*! \fn long recupSolution(long cle[][6][64],solPossibles[][6],int NUM_SBOX,long K16)
 *  \brief Fonction qui permet de récupérer la valeur de K16_46bits
 *  \param cle[][6][64] : Tableau des 64 solutions pour les 8 Sbox avec les 6 chiffrés fautés correspondants
 *  \param solPossibles[][6] : Nombre de solutions possibles des 6 fautes pour les 8 Sbox
 *  \param NUM_SBOX : numéro SBOX
 *  \param K16 : K16
 *  \return K16 48bits
 */
long recupSolution(int cle[][6][64],int solPossibles[][6],int NUM_SBOX,long K16)
{
	int test = 0;
	int final_solution;
	
	long elu = (long) cle[NUM_SBOX][0][test];
	
		for (int nbr_Faux = 1; nbr_Faux < 6; nbr_Faux++)
		{	
			for (final_solution = 0;final_solution<solPossibles[NUM_SBOX][nbr_Faux];final_solution++)
			{
				if (elu == cle[NUM_SBOX][nbr_Faux][final_solution])
				{
					break;
				}
			}
			
			if(final_solution == solPossibles[NUM_SBOX][nbr_Faux])
			{
				if(test+1 >= solPossibles[NUM_SBOX][0])
				{
					printf("\nProblème Sbox numéro %d,chiffré faux %d\n",NUM_SBOX,nbr_Faux);
					break;
				}
				nbr_Faux = 1;
				++test;
				elu = (long) cle[NUM_SBOX][0][test];
			}
		}
		printf("\nClé K de 6bits Choisie dans la SBOX %d : %lX donc on concat avec l'ancien K\n",NUM_SBOX+1,elu);
		K16 = shift_gauche(K16,6);
		K16 = concat(K16,elu);
		printf("\nK16 courant = %lX\n",K16);
		
		return K16;
}

 /*! \fn long trouverK16_48b(long msg_EncJuste, long msg_EncFaux[]);
 *  \brief Fonction qui permet de retrouver la clé K16 de 48 bits
 *  \param msg_EncJuste : message crypté juste
 *  \param msg_EncFaux : messages cryptés faux
 *  \return K16 la clé de 48 bits
 */
long trouverK16_48b(long msg_EncJuste, long msg_EncFaux[])
 {
	 long K16 = 0;//48bits
	 long msg_Dec_EncJuste;//Dechiffré OK par rapport au message crypté OK
	 long msg_Dec_EncFaux;//Dechiffré Faux OK par rapport au message faux crypté OK
	 long check;//Verification de 32bits
	 long entree_SBOX,entree_SBOXf;//Entree des Sbox
	 long EXP_R15, EXP_R15f;//Expansion
	 long L16,R16,R15,L16f,R16f,R15f;//L et R fautés ou non
	 
	 
	 int cle[8][6][64] = {{{0}}};//Tableau des 64 solutions pour les 8 Sbox avec les 6 chiffrés fautés correspondants
	 int solPossibles[8][6] = {{0}};//Nombre de solutions possibles des 6 chiffrés faux pour les 8 Sbox 
	
	 int nbr_faux;
	 
	 int check_4bits;//Sbox de verification
	 int SBOX_4bits;//Obtenue avec les fautés
	 int ligne,colonne;//SBOX 
	 int ligne_f,colonne_f;//SBOX fautée
	 int NUM_SBOX ;//Numéro SBOX
	 int RE_k16;//recherche exaustive K16
	 
	 
	 //~ printf("\n###################### Analyse Bit Fauté ######################\n\n");
	 
	 //~ for (int analyse=0;analyse<32;analyse++)
	 //~ {
		 //~ analyse_bit_faute(msg_EncJuste,msg_EncFaux,analyse);
	 //~ }
	 
	//printf("\n### PERMUTATION IP Chiffré Juste ### \n");
	 
	msg_Dec_EncJuste = permutation(msg_EncJuste, IP, 64, 64); //Permutation IP avec le chiffré
    
    //printf("\n### DECOUPAGE L16 et R16 Juste ### \n");
    
    L16 = decoupage_msgL(msg_Dec_EncJuste,0xFFFFFFFF);//On stocke la partie L16
    
    R16 = decoupage_msgR(msg_Dec_EncJuste,0xFFFFFFFF);//On stocke la partie R16
    R15 = R16;//On stocke R16 dans R15
		
		//~ printf("\n### PERMUTATION IP 32 chiffrés Faux ### \n");
		//~ printf("\n### DECOUPAGE 32 Chiffrés Faux L16F et R16F ### \n");
		
		//~ printf("\n### PERMUTATION INVERSE DE P avec L16 ^ L16f ### \n");
		
		//~ printf("\n### EXPANSION R15 et R15F ### \n");
		//~ printf("\n### DECOUPAGE EXPANSION en 8blocs de 6bits ### \n");
		//~ printf("\n### XOR AVEC RECHERCHE EXHAUSTIVE K16 ### \n");
		//~ printf("\n### INJECTION DANS LES BONNES SBOX### \n");
		//~ printf("\n### CALCUL LIGNES ET COLONNES DES SBOX ### \n");
		
		//~ printf("\n### DECOUPAGE PERMUTATION INVERSE DE P avec L16 ^ L16f en 8blocs 4bits ### \n");
		//~ printf("\n### CORRESPONDANCE AVEC LES BONNES SBOX ### \n");
		//~ printf("\n### RECUPERATION DES VALEURS SBOX CHIFFRE JUSTE ET 32 FAUX### \n");
		//~ printf("\n### XOR DES 2 SBOX ### \n");
		//~ printf("\n### COMPARAISON ENTRE CHECK ET VALEUR SBOX DE SORTIE ### \n");
		//~ printf("\n### SI EGAL ALORS STOCKAGE DE K16 6bits par SBOX ### \n");
		//~ printf("\n### STOCKAGE ELEMENT COMMUN SUR 6 FAUTE PAR SBOX ### \n");
		//~ printf("\n### CONCATENATION DES MORCEAUX DE K16 ### \n");
		//~ printf("\n### AFFICHAGE ### \n");

		//Recherche exhaustive
		for(NUM_SBOX=0;NUM_SBOX<8;NUM_SBOX++)
		{	
			for(nbr_faux=0;nbr_faux<6;nbr_faux++)
			{
				msg_Dec_EncFaux = permutation(msg_EncFaux[pos_bitfaux[NUM_SBOX][nbr_faux]], IP, 64, 64);//Permutation IP chiffré FAUX
				
				L16f = decoupage_msgL(msg_Dec_EncFaux,0xFFFFFFFF);//Stockage L16f
				R16f = decoupage_msgR(msg_Dec_EncFaux,0xFFFFFFFF);//Stockage R16f
				R15f=R16f;//Stockage R15f

				check = permutation(or_exclu(L16,L16f),inverse_P,32,32);//Valeur de Verification pour la sortie de SBOX 
				
				EXP_R15=permutation(R15,E,32,48);//Expansion R15
				EXP_R15f=permutation(R15f,E,32,48);//Expansion R15f
			
				for (RE_k16=0;RE_k16<64;RE_k16++)
				{				
					entree_SBOX = or_exclu(shift_droit(decoupe_6bits(EXP_R15,NUM_SBOX),trouver_SBOX_6bits(NUM_SBOX)),RE_k16);//Entrée Sbox 6bits XOR k16
					entree_SBOXf = or_exclu(shift_droit(decoupe_6bits(EXP_R15f,NUM_SBOX),trouver_SBOX_6bits(NUM_SBOX)),RE_k16);//Entrée Sboxf 6bits XOR k16
					
					ligne = calcul_lignes_SBOX(entree_SBOX);//Ligne SBOX
					colonne = calcul_col_SBOX(entree_SBOX);//Colonne SBOX
					
					ligne_f = calcul_lignes_SBOX(entree_SBOXf);//Ligne SBOXf
					colonne_f = calcul_col_SBOX(entree_SBOXf);//colonne SBOXf
					
					check_4bits =shift_droit(decoupe_4bits(check,NUM_SBOX),trouver_SBOX_4bits(NUM_SBOX));//Valeur de Verification pour la sortie de SBOX 4bits
					SBOX_4bits = or_exclu(Sbox[NUM_SBOX][ligne][colonne],Sbox[NUM_SBOX][ligne_f][colonne_f]);//Valeur de sortie SBOX 4 bits
					
					if(check_4bits == SBOX_4bits)//Comparaison
					{	
						cle[NUM_SBOX][nbr_faux][solPossibles[NUM_SBOX][nbr_faux]] = RE_k16;//Stockage valeurs clés
						++solPossibles[NUM_SBOX][nbr_faux];//Incrementation
					}
				}
			}
					
			//affiche_sol(NUM_SBOX,solPossibles,cle);//Affichage Possibilités par SBOX
			
			K16=recupSolution(cle,solPossibles,NUM_SBOX,K16);//Récupération de la solution commune des 6 chiffrés fautés par SBOX puis Concatenation de la clé K16
		}
		
	printf("\n#################### FIN RECHERCHE K16 48BITS ############################\n");
	
	return K16;
 }
