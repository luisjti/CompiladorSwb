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
	//for(i=0;i<va;i++) printf("     movl $%d,-%d(%%rbp)\n",vet[i].valor, vet[i].endereco);
	//for(i=0;i<vi;i++) printf("     movl $%d,-%d(%%rbp)\n",var[i].valor, var[i].endereco);
	flag=1;
	}
	
	// inicio bloco de operacoes
	r = sscanf(line, "v%c%d = ci%d",&carac, &indice,&valor);

	if(r==3 && carac == 'i'){
	printf("     movl $%d,-%d(%%rbp)\n",valor,var[indice-1].endereco);
	}
	int indice2;
	r = sscanf(line, "vi%d = vi%d ", &indice,&indice2);
	if(r==2 &strlen(line)==9){
	printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
	printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	//pi= x
	r = sscanf(line, "pi%d = pi%d ", &indice,&indice2);
    if(r==2 && indice == 1 && indice2 == 2){
    printf("     movl %%esi ,%%edi\n");
    }
    if(r==2 && indice == 1 && indice2 == 3){
    printf("     movl %%edx ,%%edi\n");
    }
    if(r==2 && indice == 2 && indice2 == 1){
    printf("     movl %%edi ,%%esi\n");
    }
    if(r==2 && indice == 2 && indice2 == 3){
    printf("     movl %%edx ,%%esi\n");
    }
    if(r==2 && indice == 3 && indice2 == 1){
    printf("     movl %%edi ,%%edx\n");
    }
    if(r==2 && indice == 3 && indice2 == 2){
    printf("     movl %%esi ,%%edx\n");
    }
	r = sscanf(line, "pi%d = pi%d ", &indice,&indice2);
    if(r==2 && indice == 1 && indice2 == 2){
    printf("     movl %%esi ,%%edi\n");
    }
    if(r==2 && indice == 1 && indice2 == 3){
    printf("     movl %%edx ,%%edi\n");
    }
    if(r==2 && indice == 2 && indice2 == 1){
    printf("     movl %%edi ,%%esi\n");
    }
    if(r==2 && indice == 2 && indice2 == 3){
    printf("     movl %%edx ,%%esi\n");
    }
    if(r==2 && indice == 3 && indice2 == 1){
    printf("     movl %%edi ,%%edx\n");
    }
    if(r==2 && indice == 3 && indice2 == 2){
    printf("     movl %%esi ,%%edx\n");
    }
    r = sscanf(line, "pi%d = vi%d ", &indice,&indice2);
    if(r==2 && indice == 1){
    printf("     movl -%d(%%rbp),%%edi\n",var[indice2-1].endereco);
    }
    if(r==2 && indice == 2){
    printf("     movl -%d(%%rbp),%%esi\n",var[indice2-1].endereco);
    }
    if(r==2 && indice == 3){
    printf("     movl -%d(%%rbp),%%edx\n",var[indice2-1].endereco);
    }
	//fim pi=x
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
	if (r==4 && operador== '+') {
		printf("     movl -%d(%%rbp), %%eax\n",var[indice2-1].endereco);
		printf("     addl $%d, %%eax\n",constante,var[indice2-1].endereco);
		printf("     movl %%eax, -%d(%%rbp \n",var[indice-1].endereco);
	}
	if (r==4 && operador== '*') {
		printf("     movl -%d(%%rbp), %%eax\n",var[indice2-1].endereco);
		printf("     imull $%d, %%eax\n",constante,var[indice2-1].endereco);
		printf("     movl %%eax, -%d(%%rbp) \n",var[indice-1].endereco);
	}
	r = sscanf(line, "pi%d = vi%d %c vi%d", &registrador,&indice,&operador,&indice2);
    if(r==4 && operador == '+' && registrador == 1){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice-1].endereco);
        printf("     addl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
        printf("     movl %%r9d,%%edi\n");
    }
    if(r==4 && operador == '+' && registrador == 2){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice-1].endereco);
        printf("     addl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
        printf("     movl %%r9d,%%esi\n");
    }
    if(r==4 && operador == '+' && registrador == 3){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice-1].endereco);
        printf("     addl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
        printf("     movl %%r9d,%%edx\n");
    }

    if(r==4 && operador == '' && registrador == 1){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice-1].endereco);
		printf("     movl -%d(%%rbp),%%r8d\n",var[indice2-1].endereco);
        printf("     imull %%r8d,%%r9d\n");
        printf("     movl %%r9d,%%edi\n");
    }
    if(r==4 && operador == '' && registrador == 2){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice-1].endereco);
		printf("     movl -%d(%%rbp),%%r8d\n",var[indice2-1].endereco);
        printf("     imull %%r8d,%%r9d\n");
        printf("     movl %%r9d,%%esi\n");
    }
    if(r==4 && operador == '+' && registrador == 3){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice-1].endereco);
		printf("     movl -%d(%%rbp),%%r8d\n",var[indice2-1].endereco);
        printf("     imull %%r8d,%%r9d\n");
        printf("     movl %%r9d,%%edx\n");
    }
	//chamada de funcao
	r = sscanf(line, "vi%d = call f%d vi%d ci%d", &indice,&nome,&indice2,&constante);
	if(r==4 && strlen(line)==21) {
		printf("     movq %%rdi,-%d(%%rbp)\n",tamanho+8);
		printf("     movq %%rsi,-%d(%%rbp)\n",tamanho+16);
		printf("     movq %%rdx,-%d(%%rbp)\n",tamanho+24);
		printf("     movl -%d(%%rbp), %%edi",var[indice-1].endereco);
		printf("     movl $%d, %%esi",constante);
		printf("     call f%d\n",nome);
		printf("     movq -%d(%%rbp),%%rdi\n",tamanho+8);
		printf("     movq -%d(%%rbp),%%rsi\n",tamanho+16);
		printf("     movq -%d(%%rbp),%%rdx\n",tamanho+24);
		printf("     movl %%eax,-%d(%%rbp) \n",var[indice-1].endereco);
	}
	if(r==3 && strlen(line)==17){
		printf("     movq %%rdi,-%d(%%rbp)\n",tamanho+8);
		printf("     movq %%rsi,-%d(%%rbp)\n",tamanho+16);
		printf("     movq %%rdx,-%d(%%rbp)\n",tamanho+24);
		printf("     movl -%d(%%rbp), %%edi",var[indice-1].endereco);
		printf("     call f%d\n",nome);
		printf("     movq -%d(%%rbp),%%rdi\n",tamanho+8);
		printf("     movq -%d(%%rbp),%%rsi\n",tamanho+16);
		printf("     movq -%d(%%rbp),%%rdx\n",tamanho+24);
		printf("     movl %%eax,-%d(%%rbp) \n",var[indice-1].endereco);
	}
	if(r==2 && strlen(line)==13){
		printf("     movq %%rdi,-%d(%%rbp)\n",tamanho+8);
		printf("     movq %%rsi,-%d(%%rbp)\n",tamanho+16);
		printf("     movq %%rdx,-%d(%%rbp)\n",tamanho+24);
		printf("     call f%d\n",nome);
		printf("     movq -%d(%%rbp),%%rdi\n",tamanho+8);
		printf("     movq -%d(%%rbp),%%rsi\n",tamanho+16);
		printf("     movq -%d(%%rbp),%%rdx\n",tamanho+24);
		printf("     movl %%eax,-%d(%%rbp) \n",var[indice-1].endereco);
	}
	
	//fim chamada de funcao
	//fim bloco de operacoes
	
	// inicio returns
	r= sscanf(line, "return vi%d", &indice);
	if(r==1){
		printf("     movl -%d(%%rbp), %%eax\n",var[indice-1].endereco);
	}
	r= sscanf(line, "return ci%d", &constante);
	if(r==1){
		printf("     movl $%d, %%eax\n",constante);
	}
	r= sscanf(line, "return pi%d", &registrador);
	if(r==1 && registrador==1){
		printf("     movl %%edi, %%eax\n");
	}
	if(r==1 && registrador==2){
		printf("     movl %%esi, %%eax\n");
	}
	if(r==1 && registrador==3){
		printf("     movl %%edx, %%eax\n");
	}
	// fim returns
	//end
      if (strlen(line)==3)
      if (strncmp(line, "end", 3) == 0) {
      printf("     leave\n     ret\n");
      continue;
    } 
	//end
  }
  return 0;

}