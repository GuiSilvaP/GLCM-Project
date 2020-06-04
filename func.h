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

#define MAX_C 16
#define TIMES_EXEC 10000

typedef struct{		// Estrutura para imagem
	char code[3];
	int l, c, lum;
	unsigned char *pdata;
}IMAGE;

typedef struct{		// Estrutura para matrizes
	unsigned char *qdata;
	unsigned int *cdata;
	double *ndata;
}MATRICES;

/* >>>>>>>>>>>> CABEÇALHOS DAS FUNÇÕES UTILIZADAS <<<<<<<<<<<<<<<*/

void read_header (IMAGE *img, FILE *pf);
void show_header (IMAGE *img, FILE *pf);
void read_image(IMAGE *img, FILE *pf);
void quant_matrix (IMAGE *img, MATRICES *matrix);
void cooc_matrix (IMAGE *img, MATRICES *matrix);
void norm_matrix (MATRICES *matrix);
void show_cooc (MATRICES *matrix);
double contrast (MATRICES *matrix);
double correlation (MATRICES *matrix);
double energy (MATRICES *matrix);
double homogeneity (MATRICES *matrix);
void write_inf (MATRICES *matrix, FILE *inf, double a_t);
