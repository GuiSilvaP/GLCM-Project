//>>>>>>>>>>>>>>>>>>>>>>> LABORATORIO DE PROGRAMAÇÃO <<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PROJETO FINAL <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PROFESSOR <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>Daniel Ferreira<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> ALUNOS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/*		            José Igor de Carvalho		              */
/*		            Guilherme Pessoa Silva			      */
/******************************************************************************/

/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DESAFIO PPGER <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "func.h"

/********************* FUNCTIONS *********************/

void read_header (IMAGE *img, FILE *pf){		// Função que lê o cabeçalho da imagem

	if (!img){
		puts ("No memory!");
		exit(1);
	}
	fscanf(pf,"%s %d %d %d", img->code, &img->l, &img->c, &img->lum);
}
void show_header(IMAGE *img, FILE *pf){			// Função que mostra o cabeçalho da imagem

	printf ("Image's Code:\t\t\t%s\n", img->code);
	printf ("Image's Order:\t\t\t%d X %d\n", img->l, img->c);
	printf ("Image's Greatest Element:\t%d\n", img->lum);
}
void read_image(IMAGE *img, FILE *pf){			// Função que lê a imagem e a armazena em uma matriz
	
	int i;
	img->pdata = (unsigned char*)calloc((img->l)*(img->c),sizeof(unsigned char));
	if (!(img->pdata)){
		puts("No memory!");
		exit(1);
	}
	fseek(pf, 1, SEEK_CUR);
	for (i=0;i<(img->l*img->c);i++){
		fread(img->pdata+i, sizeof(unsigned char), 1, pf);
	}
}
void quant_matrix (IMAGE *img, MATRICES *matrix){	// Função que quantiza a matriz da imagem

	int i;
	matrix->qdata=(unsigned char*)malloc(img->l*img->c*sizeof(unsigned char));
	if (!(matrix->qdata)){
		puts("No memory!");
		exit(1);
	}
	for (i=0;i<img->l*img->c;i++){
		*(matrix->qdata+i)=(*(img->pdata+i)/16);
	}
}
void cooc_matrix (IMAGE *img, MATRICES *matrix){	// Função que calcula a matriz de coocorrência

	int i, j, p1, p2;
	matrix->cdata = (unsigned int*)calloc(MAX_C*MAX_C,sizeof(unsigned int));
	if (!(matrix->cdata)){
		puts("No memory!");
		exit(1);
	}
	for (i=0;i<img->l;i++){
		for (j=0;j<img->c-1;j++){
			p1=(*(matrix->qdata+i*img->c+j));
			p2=(*(matrix->qdata+i*img->c+(j+1)));
			*(matrix->cdata+p1*MAX_C+p2)+=1;
		}
	}
}
void norm_matrix (MATRICES *matrix){		// Função que normaliza a matriz da imagem

	int i;
	double sum=0;
	matrix->ndata = (double*)calloc(MAX_C*MAX_C,sizeof(double));
	if (!(matrix->ndata)){
		puts("No memory!");
		exit(1);
	}
	for (i=0;i<MAX_C*MAX_C;i++){
		sum+=(double)(*(matrix->cdata+i));
	}
	for (i=0;i<MAX_C*MAX_C;i++){
		*(matrix->ndata+i)=(double)((*(matrix->cdata+i))/sum);
	}
}
void show_cooc (MATRICES *matrix){		// Função que mostra a matriz de coocorrência

	int i;
	for (i=0;i<MAX_C*MAX_C;i++){
		printf ("%d\t", *(matrix->cdata+i));
		if (!((i+1)%MAX_C))
			printf ("\n");
	}
}
/*********************** ATRIBUTES ***********************/

double contrast (MATRICES *matrix){		// Função que calcula a CONTRASTE da matrix normalizada

	int i, j;
	double contrast=0;
	for (i=0;i<MAX_C;i++){
		for (j=0;j<MAX_C;j++){
			contrast+=pow((fabs(i-j)), 2)*(*(matrix->ndata+i*MAX_C+j));
		}
	}
	return contrast;
}
double correlation (MATRICES *matrix){		// Função que calcula a CORRELAÇÃO da matrix normalizada

	int i, j;
	double m1=0, m2=0, sig1=0, sig2=0, correlation=0;
	for (i=0;i<MAX_C;i++){
		for (j=0;j<MAX_C;j++){
			m1+=i*(*(matrix->ndata+MAX_C*i+j));
			m2+=j*(*(matrix->ndata+MAX_C*i+j));
		}
	}
	for (i=0;i<MAX_C;i++){
		for (j=0;j<MAX_C;j++){
			sig1+=(*(matrix->ndata+i*MAX_C+j)*pow((i-m1), 2));
			sig2+=(*(matrix->ndata+i*MAX_C+j)*pow((j-m2), 2));
		}
	}
	sig1=sqrt(sig1);
	sig2=sqrt(sig2);
	for (i=0;i<MAX_C;i++){
		for (j=0;j<MAX_C;j++){
			correlation+=*(matrix->ndata+i*MAX_C+j)*(i-m1)*(j-m2)/(sig1*sig2);
		}
	}
	return correlation;
}
double energy (MATRICES *matrix){		// Função que calcula a ENERGIA	 da matrix normalizada

	int i;
	double energy=0;
	for (i=0;i<MAX_C*MAX_C;i++){
		energy+=pow((*(matrix->ndata+i)), 2);
	}
	return energy;
}
double homogeneity (MATRICES *matrix){		// Função que calcula a HOMOGENEIDADE da matrix normalizada

	int i, j;
	double homogeneity=0;
	for (i=0;i<MAX_C;i++){
		for (j=0;j<MAX_C;j++){
			homogeneity+=((double)*(matrix->ndata+i*MAX_C+j))/(1+fabs(i-j));
		}
	}
	return homogeneity;
}
/******************** WRITE INFORMATION *******************/

void write_inf (MATRICES *matrix, FILE *inf, double a_t){ 	// Função que armazena os dados obtidos em um arquivo .txt
	
	fprintf (inf, "%s\n", "*******************************************************");
	fprintf (inf, "\n\t%s\n\t%s\n", "***LABORATÓRIO DE PROGRAMAÇÃO***", "**TRABALHO FINAL/DESAFIO PPGER**");
	fprintf (inf, "%s\n\n%s\n%s\n\n", "EQUIPE:", "-> Jose Igor de Carvalho", "-> Guilherme Pessoa Silva");
	fprintf (inf, "%s\n\n%s\n\n", "PROFESSOR:", "-> Daniel Ferreira");
	fprintf (inf, "\t%s\n\n", "***RESULTADOS OBTIDOS***");
	fprintf (inf, "%s\t%f%s\n\n", "AVERAGE TIME:", a_t/TIMES_EXEC, " ms");
	fprintf (inf, "%s\n\n", "ATRIBUTES:");
	fprintf (inf, "%s\t%.4f\n", "Contrast:", contrast(matrix));
	fprintf (inf, "%s\t%.4f\n", "Correlation:", correlation(matrix));
	fprintf (inf, "%s\t\t%.4f\n", "Energy:", energy(matrix));
	fprintf (inf, "%s\t%.4f\n", "Homogeneity:", homogeneity(matrix));
	fprintf (inf, "\n%s\n", "*******************************************************");	
}
