#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINESZ 256

struct vet{
 int i;
 int size;
 int endereco;
};
struct var{
 int i;
 int endereco;
};

struct vet vet[5];
struct var var[5];

int parametros=0;

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
void cons (int pos,int valor){
	if(pos==1){
		printf("     movl $%d,%%edi\n",valor);
	}
	if(pos==2){
		printf("     movl $%d,%%esi\n",valor);
	}
	if(pos==3){
		printf("     movl $%d,%%edx\n",valor);
	}
}
void varI (int pos,struct var * x){
	if(pos==1){
		printf("     movl -%d(%%rbp),%%edi\n",x->endereco);
	}
	if(pos==2){
		printf("     movl -%d(%%rbp),%%esi\n",x->endereco);
	}
	if(pos==3){
		printf("     movl -%d(%%rbp),%%edx\n",x->endereco);
	}
}
void pi (int pos, int registrador, int tamanho){
	if(pos==1 && registrador==1)
		printf("     movl -%d(%%rbp),%%edi\n",tamanho+8);	
	if(pos==1 && registrador==2)
		printf("     movl -%d(%%rbp),%%edi\n",tamanho+16);
	if(pos==1 && registrador==3)
		printf("     movl -%d(%%rbp),%%edi\n",tamanho+24);
	if(pos==2 && registrador==1)
		printf("     movl -%d(%%rbp),%%esi\n",tamanho+8);	
	if(pos==2 && registrador==2)
		printf("     movl -%d(%%rbp),%%esi\n",tamanho+16);
	if(pos==2 && registrador==3)
		printf("     movl -%d(%%rbp),%%esi\n",tamanho+24);
	if(pos==3 && registrador==1)
		printf("     movl -%d(%%rbp),%%edx\n",tamanho+8);	
	if(pos==3 && registrador==2)
		printf("     movl -%d(%%rbp),%%edx\n",tamanho+16);
	if(pos==3 && registrador==3)
		printf("     movl -%d(%%rbp),%%edx\n",tamanho+24);
}
void pa (int pos, int registrador, int tamanho) {
	if(pos==1 && registrador==1)
		printf("     movq -%d(%%rbp),%%rdi\n",tamanho+8);	
	if(pos==1 && registrador==2)
		printf("     movq -%d(%%rbp),%%rdi\n",tamanho+16);
	if(pos==1 && registrador==3)
		printf("     movq -%d(%%rbp),%%rdi\n",tamanho+24);
	if(pos==2 && registrador==1)
		printf("     movq -%d(%%rbp),%%rsi\n",tamanho+8);	
	if(pos==2 && registrador==2)
		printf("     movq -%d(%%rbp),%%rsi\n",tamanho+16);
	if(pos==2 && registrador==3)
		printf("     movq -%d(%%rbp),%%rsi\n",tamanho+24);
	if(pos==3 && registrador==1)
		printf("     movq -%d(%%rbp),%%rdx\n",tamanho+8);	
	if(pos==3 && registrador==2)
		printf("     movq -%d(%%rbp),%%rdx\n",tamanho+16);
	if(pos==3 && registrador==3)
		printf("     movq -%d(%%rbp),%%rdx\n",tamanho+24);
}

void vetI(int pos, struct vet * x){
	int tmp;
	tmp=x->endereco;
	if(pos==1) {
	printf("     leaq -%d(%%rbp),%%r9\n",tmp);
	printf("     movq %%r9,%%rdi\n");
	}
	if(pos==2) {
	printf("     leaq -%d(%%rbp),%%r9\n",tmp);
	printf("     movq %%r9,%%rsi\n");
	}
	if(pos==3) {
	printf("     leaq -%d(%%rbp),%%r9\n",tmp);
	printf("     movq %%r9,%%rdx\n");
	}
}

void salvaR (int tamanho){
	if(parametros==1)
	printf("     movq %%rdi,-%d(%%rbp)\n",tamanho+8);
	if(parametros==2){
	printf("     movq %%rdi,-%d(%%rbp)\n",tamanho+8);
	printf("     movq %%rsi,-%d(%%rbp)\n",tamanho+16);
}	if(parametros==3){
	printf("     movq %%rdi,-%d(%%rbp)\n",tamanho+8);
	printf("     movq %%rsi,-%d(%%rbp)\n",tamanho+16);
	printf("     movq %%rdx,-%d(%%rbp)\n",tamanho+24);
}
}
void recuperaR (int tamanho){
	if(parametros==1)
	printf("     movq -%d(%%rbp),%%rdi\n",tamanho+8);
	if(parametros==2){
	printf("     movq -%d(%%rbp),%%rdi\n",tamanho+8);
	printf("     movq -%d(%%rbp),%%rsi\n",tamanho+16);
}	if(parametros==3){
	printf("     movq -%d(%%rbp),%%rdi\n",tamanho+8);
	printf("     movq -%d(%%rbp),%%rsi\n",tamanho+16);
	printf("     movq -%d(%%rbp),%%rdx\n",tamanho+24);
}
}
int main()
{
  char tipo[3],line[LINESZ],operador;
  int nome;
  int indice;
  int r,va=0,vi=0;
  int count = 0;
  int tamanho=0;
  int countif=1;
  int getPos;
  int indice2;
  int constante2;
  int atribuicao=1;
  int constante;
  int registrador;
  int indice3;
  int getarray;
  int registrador2;
  printf(".section .rodata\n\n"
          ".data\n\n"
          ".text\n\n"
          );
  // Lê uma linha por vez
  while (fgets(line, LINESZ, stdin) != NULL) {
    count++;
    remove_newline(line);
    
    if (strncmp(line, "function", 7) == 0) {
	  tamanho=0;
	  vi=0;
      parametros = sscanf(line, "function f%d p%c1 p%c2 p%c3", &nome, &tipo[0], &tipo[1], &tipo[2]);
      parametros--;
      printf(".globl f%d\n",nome);
      printf("f%d :\n",nome);
      printf("     pushq %%rbp\n     movq %%rsp,%%rbp\n");  
   }
  
	if (strncmp(line, "var", 3) == 0) {
		r = sscanf(line, "var vi%d", &var[vi].i);
		tamanho=tamanho+4;
		var[vi].endereco=tamanho;
		vi++;
	}
	if (strncmp(line, "vet", 3) == 0) {
		r = sscanf(line, "vet va%d size ci%d", &vet[vi].i,&vet[vi].size);
		tamanho=tamanho + vet[vi].size * 4;
		vet[vi].endereco=tamanho;
		vi++;
	}
	if (strncmp(line, "enddef", 6) == 0){
		int auxtamanho = tamanho;
		if(parametros == 1) auxtamanho = auxtamanho + 8;
		if(parametros == 2) auxtamanho = auxtamanho + 16;
		if(parametros == 3) {
		auxtamanho = auxtamanho + 24;
		getPos=auxtamanho;
	}
	
	while(auxtamanho % 16 !=0)auxtamanho++;
		printf("     subq $%d,%%rsp\n",auxtamanho);
	}
	// início atribuição de valores
	atribuicao=1;
	r = sscanf(line, "vi%d = ci%d %c ci%d", &indice,&constante,&operador,&constante2);
	if(r==4 && operador == '+'){
		printf("     movl $%d,%%r9d\n",constante);
		printf("     addl $%d,%%r9d\n",constante2);
		printf("     movl %%r9d,-%d(%%rbp)\n", var[indice-1].endereco);
		atribuicao = 0;
	}
	if(r==4 && operador == '-'){
		printf("     movl $%d,%%r9d\n",constante);
		printf("     subl $%d,%%r9d\n",constante2);
		printf("     movl %%r9d,-%d(%%rbp)\n", var[indice-1].endereco);
		atribuicao = 0;
	}
	if(r==4 && operador == '*'){
		printf("     movl $%d,%%r9d\n",constante);
		printf("     imull $%d,%%r9d\n",constante2);
		printf("     movl %%r9d,-%d(%%rbp)\n", var[indice-1].endereco);
		atribuicao = 0;
	}
	if(r==4 && operador == '/' && parametros != 3){
		printf("     movl $%d,%%ebx\n",constante);
		printf("     movl $%d,%%ecx\n",constante2);
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n", var[indice-1].endereco);
		atribuicao = 0;
	}
	if(r==4 && operador == '/' && parametros == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl $%d,%%ebx\n",constante);
		printf("     movl $%d,%%ecx\n",constante2);
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n", var[indice-1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
		atribuicao = 0;
	}
	r = sscanf(line, "vi%d = ci%d %c vi%d", &indice,&constante,&operador,&indice2);
	
	if(r==4 && operador == '+'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     addl $%d,%%r9d\n",constante);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
		atribuicao=0;
	}
	if(r==4 && operador == '-'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     movl $%d,%%r8d\n",constante);
		printf("     subl %%r9d,%%r8d\n");
		printf("     movl %%r8d,-%d(%%rbp)\n",var[indice-1].endereco);
		atribuicao=0;
	}
	if(r==4 && operador == '*'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     imull $%d,%%r9d\n",constante);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
		atribuicao=0;
	}
	if(r==4 &&  operador == '/' && parametros != 3){
		printf("     movl $%d,%%ebx\n",constante);
		printf("     movl -%d(%%rbp),%%ecx\n",var[indice2 - 1].endereco);
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
                printf("     divl %%ecx\n");
                printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
                atribuicao = 0;
	}
	if(r==4 &&  operador == '/' && parametros == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl $%d,%%ebx\n",constante);
		printf("     movl -%d(%%rbp),%%ecx\n",var[indice2 - 1].endereco);
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
                printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
        printf("     movq -%d(%%rbp),%%rdx\n",getPos);
        atribuicao = 0;
	}
	r = sscanf(line, "vi%d = ci%d %c pi%d", &indice,&constante,&operador,&registrador);
	if(r==4 && operador == '+' && registrador==1){
		printf("     movl %%edi,%%r9d\n");
		printf("     addl $%d,%%r9d\n",constante);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '+' && registrador==2){
		printf("     movl %%esi,%%r9d\n");
		printf("     addl $%d,%%r9d\n",constante);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '+' && registrador==3){
		printf("     movl %%edx,%%r9d\n");
		printf("     addl $%d,%%r9d\n",constante);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '-' && registrador==1){
		printf("     movl %%edi,%%r9d\n");
		printf("     movl $%d,%%r8d\n",constante);
		printf("     subl %%r9d,%%r8d\n");
		printf("     movl %%r8d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '-' && registrador==2){
		printf("     movl %%esi,%%r9d\n");
		printf("     movl $%d,%%r8d\n",constante);
		printf("     subl %%r9d,%%r8d\n");
		printf("     movl %%r8d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '-' && registrador==3){
		printf("     movl %%edx,%%r9d\n");
		printf("     movl $%d,%%r8d\n",constante);
		printf("     subl %%r9d,%%r8d\n");
		printf("     movl %%r8d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '*' && registrador==1){
		printf("     movl %%edi,%%r9d\n");
		printf("     imull $%d,%%r9d\n",constante);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '*' && registrador==2){
		printf("     movl %%esi,%%r9d\n");
		printf("     imull $%d,%%r9d\n",constante);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '*' && registrador==3){
		printf("     movl %%edx,%%r9d\n");
		printf("     imull $%d,%%r9d\n",constante);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '/' && registrador == 1 && parametros != 3){
		printf("     movl $%d,%%ebx\n",constante);
		printf("     movl %%edi,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
        atribuicao=0;
	}
	if(r==4 && operador == '/' && registrador == 1 && parametros == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl $%d,%%ebx\n",constante);
		printf("     movl %%edi,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
        printf("     movq -%d(%%rbp),%%rdx\n",getPos);
        atribuicao=0;
	}
	if(r==4 && operador == '/' && registrador == 2 && parametros != 3){
		printf("     movl $%d,%%ebx\n",constante);
		printf("     movl %%esi,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
        atribuicao=0;
	}
	if(r==4 && operador == '/' && registrador == 2 && parametros == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl $%d,%%ebx\n",constante);
		printf("     movl %%esi,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
        printf("     movq -%d(%%rbp),%%rdx\n",getPos);
        atribuicao=0;
	}
	if(r==4 && operador == '/' && registrador == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl $%d,%%ebx\n",constante);
		printf("     movl %%edx,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
        printf("     movq -%d(%%rbp),%%rdx\n",getPos);
        atribuicao=0;
	}
	r = sscanf(line, "vi%d = ci%d", &indice,&constante);
	if(r==2 && atribuicao){
		printf("     movl $%d,-%d(%%rbp)\n",constante,var[indice-1].endereco);
	}
	
	r = sscanf(line, "vi%d = vi%d", &indice,&indice2);
	if(r==2 && strlen(line)==9){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	
	r = sscanf(line, "vi%d = pi%d ", &indice,&indice2);
	if(r==2 && indice == 1 && strlen(line)==9){
		printf("     movl %%edi,-%d(%%rbp)\n",var[indice2-1].endereco);
	}
	if(r==2 && indice == 2 && strlen(line)==9){
		printf("     movl %%esi,-%d(%%rbp)\n",var[indice2-1].endereco);
	}
	if(r==2 && indice == 3 && strlen(line)==9){
		printf("     movl %%edx,-%d(%%rbp)\n",var[indice2-1].endereco);
	}

	r = sscanf(line, "vi%d = pi%d %c vi%d", &indice,&registrador,&operador,&indice2);
	if(r==4 && registrador == 1 && operador == '+'){
		printf("     addl %%edi,-%d(%%rbp)\n",var[indice2-1].endereco);
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 1 && operador == '*'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     imull %%edi,%%r9d\n");
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 1 && operador == '-'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
        printf("     movl %%edi,%%r8d\n");	
		printf("     subl %%r9d,%%r8d\n");
		printf("     movl %%r8d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 1 && operador == '/' && parametros != 3){
		printf("     movl %%edi,%%ebx\n");
		printf("     movl -%d(%%rbp),%%ecx\n",var[indice2-1].endereco);
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 1 && operador == '/' && parametros == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%edi,%%ebx\n");
		printf("     movl -%d(%%rbp),%%ecx\n",var[indice2-1].endereco);
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	if(r==4 && registrador == 2 && operador == '+'){
		printf("     addl %%esi,-%d(%%rbp)\n",var[indice2-1].endereco);
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     addl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 2 && operador == '*'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     imull %%esi,%%r9d\n");
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 2 && operador == '-'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
        printf("     movl %%esi,%%r8d\n");	
		printf("     subl %%r9d,%%r8d\n");
		printf("     movl %%r8d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 2 && operador == '/' && parametros != 3){
		printf("     movl %%esi,%%ebx\n");
		printf("     movl -%d(%%rbp),%%ecx\n",var[indice2-1].endereco);
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 2 && operador == '/' && parametros == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%esi,%%ebx\n");
		printf("     movl -%d(%%rbp),%%ecx\n",var[indice2-1].endereco);
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	if(r==4 && registrador == 3 && operador == '+'){
		printf("     addl %%edx,-%d(%%rbp)\n",var[indice2-1].endereco);
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     addl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 3 && operador == '*'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     imull %%edx,%%r9d\n");
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 3 && operador == '-'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
        printf("     movl %%edx,%%r8d\n");	
		printf("     subl %%r9d,%%r8d\n");
		printf("     movl %%r8d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 3 && operador == '/'){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%edx,%%ebx\n");
		printf("     movl -%d(%%rbp),%%ecx\n",var[indice2-1].endereco);
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	r = sscanf(line, "vi%d = vi%d %c ci%d", &indice,&indice2,&operador,&constante);
    if (r==4 && operador== '+') {
        printf("     movl -%d(%%rbp), %%eax\n",var[indice2-1].endereco);
        printf("     addl $%d, %%eax\n",constante);
        printf("     movl %%eax, -%d(%%rbp)\n",var[indice-1].endereco);
        }
    if (r==4 && operador== '-') {
        printf("     movl -%d(%%rbp), %%eax\n",var[indice2-1].endereco);
        printf("     subl $%d, %%eax\n",constante);
        printf("     movl %%eax, -%d(%%rbp)\n",var[indice-1].endereco);
        }
    if (r==4 && operador== '*') {
        printf("     movl -%d(%%rbp), %%eax\n",var[indice2-1].endereco);
        printf("     imull $%d, %%eax\n",constante);
        printf("     movl %%eax, -%d(%%rbp) \n",var[indice-1].endereco);
        }
    if(r==4 && operador == '/' && parametros != 3){
		printf("     movl -%d(%%rbp), %%ebx\n",var[indice2-1].endereco);
		printf("     movl $%d, %%ecx\n",constante);
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '/' && parametros == 3){
		printf("     movl -%d(%%rbp), %%ebx\n",var[indice2-1].endereco);
		printf("     movl $%d, %%ecx\n",constante);
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
       
	r = sscanf(line, "vi%d = vi%d %c vi%d", &indice,&indice2,&operador,&indice3);
	if(r==4 && operador == '+'){
		printf("     movl -%d(%%rbp), %%r9d\n",var[indice2-1].endereco);
        printf("     addl -%d(%%rbp), %%r9d\n",var[indice-1].endereco);
        printf("     movl %%r9d, -%d(%%rbp) \n",var[indice3-1].endereco);
	}
	if(r==4 && operador == '-'){
		printf("     movl -%d(%%rbp), %%r9d\n",var[indice2-1].endereco);
        printf("     subl -%d(%%rbp), %%r9d\n",var[indice-1].endereco);
        printf("     movl %%r9d, -%d(%%rbp) \n",var[indice3-1].endereco);
	}
	if(r==4 && operador == '*'){
		printf("     movl -%d(%%rbp), %%r9d\n",var[indice2-1].endereco);
        printf("     imull -%d(%%rbp), %%r9d\n",var[indice3-1].endereco);
        printf("     movl %%r9d, -%d(%%rbp) \n",var[indice-1].endereco);
	}
	if(r==4 && operador == '/' && parametros != 3){
		printf("     movl -%d(%%rbp), %%ebx\n",var[indice2-1].endereco);
		printf("     movl -%d(%%rbp), %%ecx\n",var[indice3-1].endereco);
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '/' && parametros == 3){
		printf("     movl -%d(%%rbp), %%ebx\n",var[indice2-1].endereco);
		printf("     movl -%d(%%rbp), %%ecx\n",var[indice3-1].endereco);
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	r = sscanf(line, "vi%d = vi%d %c pi%d", &indice,&indice2,&operador,&registrador);
	if(r==4 && registrador == 1 && operador == '+'){
		printf("     movl %%edi,%%r8d\n");
		printf("     addl -%d(%%rbp),%%r8d\n",var[indice2-1].endereco);
		printf("     addl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 1 && operador == '*'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     imull %%edi,%%r9d\n");
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 1 && operador == '-'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
        printf("     movl %%edi,%%r8d\n");	
		printf("     subl %%r8d,%%r9d\n");
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 1 && operador == '/' && parametros != 3){
		printf("     movl -%d(%%rbp),%%ebx\n",var[indice2-1].endereco);
		printf("     movl %%edi,%%ecx\n");
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 1 && operador == '/' && parametros == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl -%d(%%rbp),%%ebx\n",var[indice2-1].endereco);
		printf("     movl %%edi,%%ecx\n");
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	if(r==4 && registrador == 2 && operador == '+'){
		printf("     addl %%esi,-%d(%%rbp)\n",var[indice2-1].endereco);
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     addl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 2 && operador == '*'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     imull %%esi,%%r9d\n");
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 2 && operador == '-'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
        printf("     movl %%esi,%%r8d\n");	
		printf("     subl %%r8d,%%r9d\n");
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 2 && operador == '/' && parametros != 3){
		printf("     movl -%d(%%rbp),%%ebx\n",var[indice2-1].endereco);
		printf("     movl %%esi,%%ecx\n");
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 2 && operador == '/' && parametros == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl -%d(%%rbp),%%ebx\n",var[indice2-1].endereco);
		printf("     movl %%esi,%%ecx\n");
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	if(r==4 && registrador == 3 && operador == '+'){
		printf("     addl %%edx,-%d(%%rbp)\n",var[indice2-1].endereco);
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     addl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 3 && operador == '*'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
		printf("     imull %%edx,%%r9d\n");
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && registrador == 3 && operador == '-'){
		printf("     movl -%d(%%rbp),%%r9d\n",var[indice2-1].endereco);
        printf("     movl %%edx,%%r8d\n");	
		printf("     subl %%r8d,%%r9d\n");
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}

	if(r==4 && registrador == 3 && operador == '/'){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl -%d(%%rbp),%%ebx\n",var[indice2-1].endereco);
		printf("     movl %%edx,%%ecx\n");
		printf("     movl $0,%%edx\n");
		printf("     movl %%ebx,%%eax\n");
		printf("     divl %%ecx\n");
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	
	r = sscanf(line, "vi%d = pi%d %c ci%d", &indice,&constante,&operador,&registrador);
	if(r==4 && operador == '+' && registrador == 1){
		printf("     movl %%edi,%%r9d\n");
		printf("     addl $%d,%%r9d\n",constante);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '+' && registrador == 2){
		printf("     movl %%esi,%%r9d\n");
		printf("     addl $%d,%%r9d\n",constante);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '+' && registrador == 3){
		printf("     movl %%edx,%%r9d\n");
		printf("     addl $%d,%%r9d\n",constante);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '-' && registrador == 1){
		printf("     movl %%edi,%%r9d\n");
		printf("     movl $%d,%%r8d\n",constante);
		printf("     subl %%r8d,%%r9d\n");
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '-' && registrador == 2){
		printf("     movl %%esi,%%r9d\n");
		printf("     movl $%d,%%r8d\n",constante);
		printf("     subl %%r8d,%%r9d\n");
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '-' && registrador == 3){
		printf("     movl %%edx,%%r9d\n");
		printf("     movl $%d,%%r8d\n",constante);
		printf("     subl %%r8d,%%r9d\n");
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '*' && registrador == 1){
		printf("     movl %%edi,%%r9d\n");
		printf("     imull $%d,%%r9d\n",constante);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '*' && registrador == 2){
		printf("     movl %%esi,%%r9d\n");
		printf("     imull $%d,%%r9d\n",constante);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '*' && registrador == 3){
		printf("     movl %%edx,%%r9d\n");
		printf("     imull $%d,%%r9d\n",constante);
		printf("     movl %%r9d,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '/' && registrador == 1 && parametros != 3){
		printf("     movl %%edi,%%ebx\n");
		printf("     movl $%d,%%ecx\n",constante);
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '/' && registrador == 1 && parametros == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%edi,%%ebx\n");
		printf("     movl $%d,%%ecx\n",constante);
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
        printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	if(r==4 && operador == '/' && registrador == 2 && parametros != 3){
		printf("     movl %%esi,%%ebx\n");
		printf("     movl $%d,%%ecx\n",constante);
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==4 && operador == '/' && registrador == 1 && parametros == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%esi,%%ebx\n");
		printf("     movl $%d,%%ecx\n",constante);
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
        printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	if(r==4 && operador == '/' && registrador == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%edx,%%ebx\n");
		printf("     movl $%d,%%ecx\n",constante);
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
        printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	r = sscanf(line, "vi%d = pi%d %c pi%d", &indice,&registrador,&operador,&registrador2);
	if(r==4 && registrador == 1 && registrador2 == 1 && operador == '/' && parametros != 3){
		printf("     movl %%edi,%%ebx\n");
        printf("     movl %%edi,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
	}
	if(r==4 && registrador == 1 && registrador2 == 1 && operador == '/' && parametros == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%edi,%%ebx\n");
        printf("     movl %%edi,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	if(r==4 && registrador == 2 && registrador2 == 2 && operador == '/' && parametros != 3){
		printf("     movl %%esi,%%ebx\n");
        printf("     movl %%esi,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
	}
	if(r==4 && registrador == 2 && registrador2 == 2 && operador == '/' && parametros == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%esi,%%ebx\n");
        printf("     movl %%esi,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	if(r==4 && registrador == 3 && registrador2 == 3 && operador == '/'){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%edx,%%ebx\n");
        printf("     movl %%edx,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	if(r==4 && registrador == 1 && registrador2 == 2 && operador == '/' && parametros != 3){
		printf("     movl %%edi,%%ebx\n");
        printf("     movl %%esi,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
	}
	if(r==4 && registrador == 1 && registrador2 == 2 && operador == '/' && parametros == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%edi,%%ebx\n");
        printf("     movl %%esi,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	if(r==4 && registrador == 2 && registrador2 == 1 && operador == '/' && parametros != 3){
		printf("     movl %%esi,%%ebx\n");
        printf("     movl %%edi,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
	}
	if(r==4 && registrador == 2 && registrador2 == 1 && operador == '/' && parametros == 3){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%esi,%%ebx\n");
        printf("     movl %%edi,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	if(r==4 && registrador == 1 && registrador2 == 3 && operador == '/'){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%edi,%%ebx\n");
        printf("     movl %%edx,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	if(r==4 && registrador == 3 && registrador2 == 1 && operador == '/'){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%edx,%%ebx\n");
        printf("     movl %%edi,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	if(r==4 && registrador == 2 && registrador2 == 3 && operador == '/'){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%esi,%%ebx\n");
        printf("     movl %%edx,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	if(r==4 && registrador == 3 && registrador2 == 2 && operador == '/'){
		printf("     movq %%rdx,-%d(%%rbp)\n",getPos);
		printf("     movl %%edx,%%ebx\n");
        printf("     movl %%esi,%%ecx\n");
        printf("     movl $0,%%edx\n");
        printf("     movl %%ebx,%%eax\n");
        printf("     divl %%ecx\n");
        printf("     movl %%eax,-%d(%%rbp)\n",var[indice - 1].endereco);
		printf("     movq -%d(%%rbp),%%rdx\n",getPos);
	}
	// fim atribuições de valores 
	//início chamadas de função
	char c1,c2,c3,c4,c5,c6;
	int indice4;
	r = sscanf(line, "vi%d = call f%d %c%c%d %c%c%d %c%c%d", &indice,&nome,&c1,&c2,&indice2,&c3,&c4,&indice3,&c5,&c6,&indice4);
	if(r==11 && strlen(line)==25){
		salvaR(tamanho);
		if(c1== 'v' && c2=='i'){
		varI(1,&var[indice2-1]);
		}
		if(c3== 'v' && c4=='i'){
		varI(2,&var[indice3-1]);
		}
		if(c5== 'v' && c6=='i'){
		varI(3,&var[indice4-1]);
		}
		if(c1== 'v' && c2=='a'){
		vetI(1,&vet[indice2-1]);
		}
		if(c3== 'v' && c4=='a'){
		vetI(2,&vet[indice3-1]);
		}
		if(c5== 'v' && c6=='a'){
		vetI(3,&vet[indice4-1]);
		}
		if(c1== 'c' && c2=='i'){
		cons(1,indice2);
		}
		if(c3== 'c' && c4=='i'){
		cons(2,indice3);
		}
		if(c5== 'c' && c6=='i'){
		cons(3,indice4);
		}
		if(c1== 'p' && c2=='i'){
		pi(1,indice2,tamanho);
		}
		if(c3== 'p' && c4=='i'){
		pi(2,indice3,tamanho);
		}
		if(c5== 'p' && c6=='i'){
		pi(3,indice4,tamanho);
		}
		if(c1== 'p' && c2=='a'){
		pa(1,indice2,tamanho);
		}
		if(c3== 'p' && c4=='a'){
		pa(2,indice3,tamanho);
		}
		if(c5== 'p' && c6=='a'){
		pa(3,indice4,tamanho);
		}
		printf("     call f%d\n",nome);
		recuperaR(tamanho);
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==8 && strlen(line)==21){
		salvaR(tamanho);
		if(c1== 'v' && c2=='i'){
		varI(1,&var[indice2-1]);
		}
		if(c3== 'v' && c4=='i'){
		varI(2,&var[indice3-1]);
		}
		if(c1== 'v' && c2=='a'){
		vetI(1,&vet[indice2-1]);
		}
		if(c3== 'v' && c4=='a'){
		vetI(2,&vet[indice3-1]);
		}
		if(c1== 'c' && c2=='i'){
		cons(1,indice2);
		}
		if(c3== 'c' && c4=='i'){
		cons(2,indice3);
		}
		if(c1== 'p' && c2=='i'){
		pi(1,indice2,tamanho);
		}
		if(c3== 'p' && c4=='i'){
		pi(2,indice3,tamanho);
		}
		if(c1== 'p' && c2=='a'){
		pa(1,indice2,tamanho);
		}
		if(c3== 'p' && c4=='a'){
		pa(2,indice3,tamanho);
		}
		printf("     call f%d\n",nome);
		recuperaR(tamanho);
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	if(r==5 && strlen(line)==17){
		salvaR(tamanho);
		if(c1== 'v' && c2=='i'){
		varI(1,&var[indice2-1]);
		}
		if(c1== 'v' && c2=='a'){
		vetI(1,&vet[indice2-1]);
		}
		if(c1== 'c' && c2=='i'){
		cons(1,indice2);
		}
		if(c1== 'p' && c2=='i'){
		pi(1,indice2,tamanho);
		}
		if(c1== 'p' && c2=='a'){
		pa(1,indice2,tamanho);
		}
		printf("     call f%d\n",nome);
		recuperaR(tamanho);
		printf("     movl %%eax,-%d(%%rbp)\n",var[indice-1].endereco);
	}
	//fim chamadas de função
	//início set 
	int setarray;
	r = sscanf(line, "set va%d index ci%d with vi%d ",&indice,&constante,&indice2);
	if(r==3){
		setarray=vet[indice-1].endereco;
		setarray=setarray - (constante-1) * 4;
		printf("     movq -%d(%%rbp),%%r9d,\n",var[indice2 - 1].endereco);
		printf("     movq %%r9d,-%d(%%rbp)\n",setarray);
	}
	
	r = sscanf(line, "set va%d index ci%d with pi%d ",&indice,&constante,&indice2);
	if(r==3 && indice2 == 1){
		setarray=vet[indice-1].endereco;
		setarray=setarray - constante * 4;
		printf("     movl %%edi,-%d(%%rbp)\n",setarray);
	}
	if(r==3 && indice2 == 2){
		setarray=vet[indice-1].endereco;
		setarray=setarray - constante * 4;
		printf("     movl %%esi,-%d(%%rbp)\n",setarray);
	}
	if(r==3 && indice2 == 3){
		setarray=vet[indice-1].endereco;
		setarray=setarray - constante * 4;
		printf("     movl %%edx,-%d(%%rbp)\n",setarray);
	}
	r = sscanf(line, "set va%d index ci%d with ci%d ",&indice,&constante,&constante2);
	if(r==3) {
		setarray=vet[indice-1].endereco;
		setarray=setarray - constante * 4;
		printf("     movl $%d,-%d(%%rbp)\n",constante2,setarray);
	}
       // set com parâmetro
    r = sscanf(line, "set pa%d index ci%d with pi%d ",&indice,&constante,&indice2);
    if(r==3 && indice == 1 && indice2 == 2){
       setarray = (constante-1) * 4;
       printf("     movl %%esi, %d(%%rdi)\n",setarray);
       }
    if(r==3 && indice == 1 && indice2 == 3){
       setarray = (constante-1) * 4;
       printf("     movl %%edx, %d(%%rdi)\n",setarray);
       }
	if(r==3 && indice == 2 && indice2 == 1){
       setarray = (constante-1) * 4;
       printf("     movl %%edi,%d(%%rsi)\n",setarray);
       }
    if(r==3 && indice == 2 && indice2 == 3){
       setarray = (constante-1) * 4;
       printf("     movl %%edx,%d(%%rsi)\n",setarray);
       }
    if(r==3 && indice == 3 && indice2 == 1){
       setarray = (constante-1) * 4;
       printf("     movl %%edi,%d(%%rdx)\n",setarray);
       }
    if(r==3 && indice == 3 && indice2 == 2){
       setarray = (constante-1) * 4;
       printf("     movl %%esi,%d(%%rdx)\n",setarray);
       }
       r = sscanf(line, "set pa%d index ci%d with vi%d ",&indice,&constante,&indice2);
	if(r==3 && indice == 1){
       setarray = (constante-1) * 4;
       printf("     movl -%d(%%rbp),%d(%%rdi)\n",var[indice2-1].endereco,setarray);
       }
    if(r==3 && indice == 2){
       setarray = (constante-1) * 4;
       printf("     movl -%d(%%rbp),%d(%%rsi)\n",var[indice2-1].endereco,setarray);
       }
	if(r==3 && indice == 3){
       setarray = (constante-1) * 4;
       printf("     movl -%d(%%rbp),%d(%%rdx)\n",var[indice2-1].endereco,setarray);
       }
	   r = sscanf(line, "set pa%d index ci%d with ci%d ",&indice,&constante,&indice2);
	if(r==3 && indice == 1){
       setarray = (constante-1) * 4;
	   printf("     movl $%d,%d(%%rdi)\n",constante2,setarray);
	   }
	if(r==3 && indice == 2){
       setarray = (constante-1) * 4;
	   printf("     movl $%d,%d(%%rsi)\n",constante2,setarray);
	   }
	if(r==3 && indice == 3){
       setarray = (constante-1) * 4;
	   printf("     movl $%d,%d(%%rdx)\n",constante2,setarray);
	   }
	//fim set
	//início get
	int getarray;
	r = sscanf(line, "get va%d index ci%d to vi%d ",&indice,&constante,&indice2);
	if(r==3){
		getarray=vet[indice-1].endereco;
		getarray=getarray - constante * 4;
		printf("     movq -%d(%%rbp),%%r9d\n",getarray);
		printf("     movq %%r9d,-%d(%%rbp)\n",var[indice2 - 1].endereco);
	}
	
	r = sscanf(line, "get va%d index ci%d to pi%d ",&indice,&constante,&indice2);
	if(r==3 && indice2 == 1){
		getarray=vet[indice-1].endereco;
		getarray=getarray - constante * 4;
		printf("     movl -%d(%%rbp),%%edi\n",getarray);
	}
	if(r==3 && indice2 == 2){
		getarray=vet[indice-1].endereco;
		getarray=getarray - constante * 4;
		printf("     movl -%d(%%rbp),%%esi\n",getarray);
	}
	if(r==3 && indice2 == 3){
		getarray=vet[indice-1].endereco;
		getarray=getarray - constante * 4;
		printf("     movl -%d(%%rbp),%%edx\n",getarray);
	}
    //get com parâmetro de array
    r = sscanf(line, "get pa%d index ci%d to pi%d ",&indice,&constante,&indice2);
    if(r==3 && indice == 1 && indice2 == 2){
       getarray = (constante-1) * 4;
       printf("     movl %d(%%rdi),%%esi\n",getarray);
       }
    if(r==3 && indice == 1 && indice2 == 3){
       getarray = (constante-1) * 4;
       printf("     movl %d(%%rdi),%%edx\n",getarray);
       }
	if(r==3 && indice == 2 && indice2 == 1){
       getarray = (constante-1) * 4;
       printf("     movl %d(%%rsi),%%edi\n",getarray);
       }
    if(r==3 && indice == 2 && indice2 == 3){
       getarray = (constante-1) * 4;
       printf("     movl %d(%%rsi),%%edx\n",getarray);
       }
    if(r==3 && indice == 3 && indice2 == 1){
       getarray = (constante-1) * 4;
       printf("     movl %d(%%rdx),%%edi\n",getarray);
       }
    if(r==3 && indice == 3 && indice2 == 2){
       getarray = (constante-1) * 4;
       printf("     movl %d(%%rdx),%%esi\n",getarray);
       }
       r = sscanf(line, "get pa%d index ci%d to vi%d ",&indice,&constante,&indice2);
	if(r==3 && indice == 1){
       getarray = (constante-1) * 4;
       printf("     movl %d(%%rdi),-%d(%%rbp)\n",getarray,var[indice2-1].endereco);
       }
       if(r==3 && indice == 2){
       getarray = (constante-1) * 4;
       printf("     movl %d(%%rsi),-%d(%%rbp)\n",getarray,var[indice2-1].endereco);
       }
       
	if(r==3 && indice == 3){
       getarray = (constante-1) * 4;
       printf("     movl %d(%%rdx),-%d(%%rbp)\n",getarray,var[indice2-1].endereco);
       }
	 //fim get
	//inicio if
	r = sscanf(line, "if vi%d",&indice);
	if(r==1){
		printf("     cmpl $0,-%d(%%rbp)\n",var[indice-1].endereco);
		printf("     jne endif%d\n",countif);
	}
	r = sscanf(line, "if pi%d",&indice);
	if(r==1 && indice == 1){
		printf("     cmpl $0,%%edi\n");
		printf("     jne endif%d\n",countif);
	}
	if(r==1 && indice == 2){
		printf("     cmpl $0,%%esi\n");
		printf("     jne endif%d\n",countif);
	}
	if(r==1 && indice == 1){
		printf("     cmpl $0,%%edx\n");
		printf("     jne endif%d\n",countif);
	}
	r = sscanf(line, "if ci%d",&constante);
	if(r==1){
		printf("     cmpl $0,%d\n",constante);
		printf("     jne endif%d\n",countif);
	}
	if (strncmp(line, "endif", 6) == 0){
		printf("endif%d:\n",countif);
		countif++;
	}
	//fim if
	
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
