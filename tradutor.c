#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINESZ 256
struct vet{
 int i;
 int size;
 int valor;
 int endereco;
};
struct var{
 int i;
 int valor;
 int endereco;
};

struct par{
     char indice[3];
     int num[3];
     char nome;
};
struct vet vet[3];
struct var var[3];
struct par par;
// Remove o '\n' do fim da linha
void remove_newline(char *ptr)
{
  while (*ptr) {
    if (*ptr == '\n')
      *ptr = 0;
    else
      ptr++;
  }
}

int main()
{
  char nome;
  char nomevar;
  char tipo[3];
  int indice,valor;
  int r, i1,i2,va=0,vi=0;
  int inicio, fim, passo;
  char line[LINESZ];
  int count = 0;
  int tamanho=0,i;
  int flag=0;
  char carac;
  int parametros;
  printf(".section .rodata\n\n"
          ".data\n\n"
          ".text\n\n"
          );
  // Lê uma linha por vez
  while (fgets(line, LINESZ, stdin) != NULL) {
    count++;
    remove_newline(line);
    
    if (strncmp(line, "function", 7) == 0) {
      parametros = sscanf(line, "function f%c p%c1 p%c2 p%c3", &nome, &tipo[0], &tipo[1], &tipo[2]);
      parametros--;
      printf(".globl f%c\n",nome);
      printf("f%c :\n\n",nome);
      printf("     pushq %%rbp\n     movq %%rsp,%%rbp\n");  
   }
  
	if (strncmp(line, "var", 3) == 0) {
	r = sscanf(line, "vet vi%d", &var[vi].i);
	tamanho=tamanho+4;
	var[vi].endereco=tamanho;
	vi++;
	}
	if (strncmp(line, "vet", 3) == 0) {
	r = sscanf(line, "vet va%d size ci%d", &vet[va].i,&vet[va].size);
	tamanho=tamanho + vet[va].size;
	vet[va].endereco=tamanho;
	va++;
	}
	if (strncmp(line, "enddef", 6) == 0){
	while(tamanho % 16 !=0)tamanho++;
	printf("     subq $%d,%%rsp\n",tamanho);
	for(i=0;i<va;i++) printf("     movl $%d,-%d(%%rbp)\n",vet[i].valor, vet[i].endereco);
	for(i=0;i<vi;i++) printf("     movl $%d,-%d(%%rbp)\n",var[i].valor, var[i].endereco);
	flag=1;
	}
	
	
	r = sscanf(line, "v%c%d = ci%d",&carac, &indice,&valor);

	if(r==3 && carac == 'i'){
	printf("     movl $%d,-%d(%%rbp)\n",valor,var[indice-1].endereco);
	}
	int indice2;
	r = sscanf(line, "vi%d = vi%d ", &indice,&indice2);
	if(r==2){
	printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
	printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	char operador;
	int registrador;
	r = sscanf(line, "vi%d = pi%d %c vi%d", &indice,&registrador,&operador,&indice2);
	if(r==4 && registrador == 1 && operador == '+'){
	printf("     addl %%edi,-%d(%%rbp)\n",var[indice2-1].endereco);
	printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
	printf("     addl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 1 && operador == '*'){
	printf("     imull %%edi,-%d(%%rbp)\n",var[indice2-1].endereco);
	printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
	printf("     imull %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 2 && operador == '+'){
	printf("     addl %%esi,-%d(%%rbp)\n",var[indice2-1].endereco);
	printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
	printf("     addl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 2 && operador == '*'){
	printf("     imull %%esi,-%d(%%rbp)\n",var[indice2-1].endereco);
	printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
	printf("     imull %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 3 && operador == '+'){
	printf("     addl %%edx,-%d(%%rbp)\n",var[indice2-1].endereco);
	printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
	printf("     addl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 3 && operador == '*'){
	printf("     imull %%edx,-%d(%%rbp)\n",var[indice2-1].endereco);
	printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
	printf("     imull %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	int constante;
	r = sscanf(line, "vi%d = vi%d %c ci%d", &indice,&indice2,&operador,&constante);
	
	
      if (strlen(line)==3)
      if (strncmp(line, "end", 3) == 0) {
      printf("     leave\n     ret\n");
      continue;
    } 
  }
  return 0;

}
