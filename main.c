//>>>>>>>>>>>>>>>>>>>>>>> LABORATORIO DE PROGRAMAÇÃO <<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PROJETO FINAL <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PROFESSOR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>Daniel Ferreira<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ALUNOS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*		            José Igor de Carvalho		              */
/*		            Guilherme Pessoa Silva			      */
/******************************************************************************/

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DESAFIO PPGER <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

/*#############################  RESULTADOS ####################################

Contrast	= 0.7109
Correlation	= 0.9527
Energy		= 0.0555
Homogeneity	= 0.7891
Average time 	= 0.002600

################################################################################*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "func.h" 	// Biblioteca criada


int main(int argc, char *argv[]){
		
	IMAGE *img=NULL;
	MATRICES *matrix=NULL;
	FILE *pf=NULL, *inf=NULL;
	
	clock_t ini, fin;
	double t, tt=0;
	register int i;
	
//************************************************************
	img = (IMAGE*)calloc(1,sizeof(IMAGE));		     	// Alocando espaço para as estruturas
	matrix = (MATRICES*)calloc(1,sizeof(MATRICES));		// Verificação de memória
	if (!img||!matrix){
		puts ("Out of memory!");
		exit(1);
	}
//************************************************************		
	if (argc!=2){
		puts ("No file name!");
		exit(1);
	}
	
	pf=fopen(*(argv+1), "rb"); 	// Abrindo arquivo via argc e argv
	inf=fopen("Inf.txt", "w");	// Abrindo arquivo que armazenará as informações  
	
	read_header(img, pf);  		// Lendo o cabeçalho da imagem
	read_image(img, pf);		// Lendo o a imagem completa
	
	// Calculando tempo médio de execução 
	
	puts ("###### Executando!!! ######");
	
	// Calculando tempo medio para 10.000 execuções
	
	for (i=0;i<TIMES_EXEC;i++){
		
		ini=clock();
		
		// Matrizes
		quant_matrix (img, matrix);	// Quantizando a matriz da imagem
		cooc_matrix (img, matrix);	// Criando matriz de coocorrência
		norm_matrix (matrix);		// Normalizando matriz de coocorrência
		
		// Atributos 
		contrast (matrix);		// Cálculo do Contraste
		correlation (matrix);		// Cálculo de Correlação
		homogeneity (matrix);		// Cálculo da Homogeneidade
		energy (matrix);		// Cálculo da Energia
		
		// Desalocando
		free(matrix->qdata);		// Desalocando matriz quantizada
		free(matrix->cdata);		// Desalocando matriz de coocorrência
		free(matrix->ndata);		// Desalocando matriz normalizada
			
		
		fin=clock();
		
		t= ((double)(fin-ini))/CLOCKS_PER_SEC;
		tt+=t;
		
	}
	
	puts ("###### Finalizado ######");
	puts ("Informações escritas em 'Inf.txt', no mesmo diretorio do programa.");
	
	write_inf (matrix, inf, tt);		// Escervendo informações gerais em arquivo ".txt"
	
	free(img->pdata);			// Desalocando matriz da imagem				
	fclose(pf);				// Fechando arquivo ultilizado para armazenar imagem
	fclose(inf);				// Fechando arquivo ultilizado para armazernar informações gerais
			
	return 0;
}
