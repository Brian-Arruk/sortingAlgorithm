#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>
#define TAM2 10
#define TAM 100000
#define FIX 1000000

typedef struct Usuarios{
	long int cod;
	char nome[50];
	char email[50];
	int senha[30];
}TUsuario;



//BUBBLE SORT
void BubbleSort(TUsuario *usuarios){
	long int i,bolha;
	TUsuario aux;
	
	for(i=1; i<=TAM-1;i++){
		for(bolha=TAM-1;bolha>=i;bolha--){
			if(usuarios[bolha].cod< usuarios[bolha-1].cod){
				aux=usuarios[bolha];
				usuarios[bolha] = usuarios[bolha-1];
				usuarios[bolha-1]=aux;
			
			}
		}			
	}
}

//Insertion SORT
void InsertionSort(TUsuario *vet){
	long int i, idChave;
	TUsuario chaveAtual;
	
	
	for(idChave=1;idChave<TAM;idChave++){// come�a na chave da posi��o 
		chaveAtual = vet[idChave];// armazena a chave da posi��o 1
		i = idChave-1;//armazena-se em i a posi��o anterior
		while(i>=0 && vet[i].cod > chaveAtual.cod){// compara��o aos pares
			vet[i+1] = vet[i];//manda as chaves maiores para a direita
			i--;//decrementa-se uma posi��o para se comparar as chaves novamente
		}
		vet[i+1] = chaveAtual;//coloca a chave rec�m recebida na posi��o ideal
	}
}


//SELECTION SORT
void SelectionSort(TUsuario *vet){
	long int idChave, idMenor, menorChave,idTemp;
	TUsuario aux;
	
	for(idChave=0;idChave<TAM-1;idChave++){// para cada uma das chaves, exceto a �ltima
		menorChave = vet[idChave].cod; // armazena-se a primeira chave n�o ordenada
		idMenor = idChave; // armazena-se o menor �ndice
		for(idTemp=idChave+1;idTemp<TAM;idTemp++){ // procura a menor chave
			if(vet[idTemp].cod < menorChave){// compara cada chave com a menor
				menorChave = vet[idTemp].cod; // atualiza a menor chave
				idMenor = idTemp; // atualiza o �ndice da menor chave
			}
		}
		aux = vet[idChave];//coloca a menor chave selecionada no seu lugar
		vet[idChave] = vet[idMenor];//complementa o comando anterior
		vet[idMenor] = aux;//complementa os dois comandos anteriores
	}
}

//SHELL SORT
void ShellSort(TUsuario *vet){
	long int k=3,h=1,i; // utilizadas na defini��o da dist�ncia inicial � valores �tradicionais�
	long int idChave;
	TUsuario chaveAtual;
	
	while(h<=TAM){// a dist�ncia n�o pode exceder o tamanho da entrada
		h = (k*h)+1; // defini��o da dist�ncia inicial
	}
	
	while(h!=1){// quando h=1 o comportamento ser� o do Insertion Sort
		h=h/k; // atualiza o valor da dist�ncia
		for(idChave=h;idChave<TAM;idChave++){ // daqui at� a Linha 24---Insertion Sort
			chaveAtual.cod = vet[idChave].cod;
			i = idChave-h;
			while(i>=0 && vet[i].cod>chaveAtual.cod){ // compara��o aos pares
				vet[i+h].cod = vet[i].cod; // �arrasta� as chaves maiores para a direita
				i = i-h;
			}
			vet[i+h] = chaveAtual;
		}
	}
}

//MERGE SORT
void Merge(TUsuario *vet,long int p,long int q,long int r){// p: �ndice inicial, q: �ndice central, r: �ndice final 
	long int n1,n2,i,j,k;
	n1 = q-p+1; // define o tamanho do subvetor esquerdo
	n2 = r-q;// define o tamanho do subvetor direito
	
	TUsuario *D;
	TUsuario *E;
	D=(TUsuario*)malloc(sizeof(TUsuario)*(n2+1)); // aloca na memoria o subvetor direito
	E=(TUsuario*)malloc(sizeof(TUsuario)*(n1+1));// aloca na memoria o subvetor esquerdo
	
	for(i=0;i<n1;i++){
		E[i] = vet[p+i]; // preenche o subvetor esquerdo
	}
	for(j=0;j<n2;j++){
		D[j] = vet[q+1+j]; // preenche o subvetor direito
	}
	
	E[n1].cod = INT_MAX;// atribui um valor sentinela �s �ltimas posi��es dos subvetores
	D[n2].cod = INT_MAX;// atribui um valor sentinela �s �ltimas posi��es dos subvetores
	i=0; // inicializa as vari�veis para a execu��o da intercala��o
	j=0; // inicializa as vari�veis para a execu��o da intercala��o
	
	for(k=p;k<=r;k++){// intercala��o das menores chaves
		if(E[i].cod<=D[j].cod){// intercala as menores chaves
			vet[k] = E[i];
			i++;
		}else{
			vet[k] = D[j];
			j++;
		}
	}
	free(E);
	free(D);
}

void MergeSort(TUsuario *vet,long int p,long int r){ //chamada inicial: Merge-Sort(vetor, 0, n-1);
	if(p<r){// condi��o de parada (vetor de tamanho unit�rio)
		long int q;
		q =(p+r)/2;// divide o vetor (ou subvetores) �ao meio�
		MergeSort(vet,p,q);// chama recursivamente ? primeira metade do (sub)vetor
		MergeSort(vet,q+1,r);// chama recursivamente ? segunda metade
		Merge(vet,p,q,r); // intercala as duas metades das subsolu��es ao desempilhar
	}
}

//HEAP SORT
void criaHeap(TUsuario *vet,long int i,long int f){// i: �nd. da sub�rvore em an�lise; f: �nd. da �lt. posi��o (n�o ord.)
	long int j;
	TUsuario aux;
	
	aux.cod = vet[i].cod; // armazena em aux a chave pai da sub�rvore em an�lise
	j = i*2+1; // j armazena o �ndice do primeiro filho de aux
	
	while(j<=f){ // enquanto o filho analisado estiver no vetor �n�o ordenado�
		if(j<f){ // caso o filho n�o esteja na �ltima posi��o
			if(vet[j].cod<vet[j+1].cod){// maior dos dois filhos de �aux�?
				j = j+1; // se o segundo for o maior, ele ser� comparado ao pai
			}
		}
	
		if(aux.cod<vet[j].cod){ // se o maior filho for maior que o pai
			vet[i] = vet[j];// o filho se torna o pai
			i = j;// atualiza-se o �ndice do novo pai
			j = i*2+1;// o filho � atualizado em j		
		}else{// caso contr�rio, j � atualizado para parar a heap
			j = f+1;
		}
	}	
	vet[i]=aux; // o antigo pai ocupa a posi��o do �ltimo filho analisado
}

void HeapSort(TUsuario *vet){
	long int i,aux;
	
	for(i=(TAM-1)/2;i>=0;i--){// para todas as sub�vores com filhos (possivelmente)
		criaHeap(vet,i,TAM-1);// utilizando estrat�gia bottom-up, constroi a heap inicial
	}
	for(i=TAM-1;i>=1;i--){// iterage em ordem decrescente at� a segunda chave
		aux = vet[0].cod;// -
		vet[0].cod = vet[i].cod;// -Troca-se a primeira chave (raiz) com a �ltima chave ainda n�o ordenada
		vet[i].cod = aux;// -
		criaHeap(vet,0,i-1);// reconstroi a heap sem a �ltima chave (ordenada!)
	}
}

//QUICK SORT
int particiona(TUsuario *vet,long int p ,long int r){ // p: �ndice inicial, r: �ndice final do (sub)vetor em an�lise
	long int esq,dir,pivo;
	TUsuario aux;
	
	esq = p; // atribui��o da posi��o inicial � esq
	dir = r;// atribui��o da posi��o final � dir
	pivo = vet[p].cod;// (nesta vers�o), o piv�, iniclalmente � a primeira chave do (sub)vetor)
	
	while(esq<dir){// condi��o de parada: �enquanto esq e dir n�o se cruzarem�
		while(vet[esq].cod<=pivo && esq!= r+1){// chave na posi��o esq � menor ou igual ao pivo?
			esq = esq+1; // incrementa esq!
		}
		while(vet[dir].cod>pivo){// chave na posi��o em dir � maior que o pivo?
			dir = dir-1;// decrementa dir!
		}
		if(esq < dir){ // se esq e dir ainda �n�o se cruzaram�..
			aux = vet[esq]; //------
			vet[esq] = vet[dir];//--Troca as chaves das posi��es esq e dir!
			vet[dir] = aux;//-------
		}
	}
	vet[p].cod = vet[dir].cod; // atribui � posi��o inicial do (sub)vetor a chave que �dar� lugar� ao piv�
	vet[dir].cod = pivo;// atribui � posi��o dir, a chave pivo
	
	return dir; // � retornado o �ndice do piv� (n�o ser� mais enviado por par�metro) ? piv� ordenado!
}

int QuickSort(TUsuario *vet,long int p,long int r){ // chamada inicial: QuickSort(vetor, 0, n-1);
	long int q;
	if(p<r){ // condi��o de parada (vetor de tamanho unit�rio)
		q = particiona(vet,p,r);// particiona o (sub)vetor e retorna a posi��o do piv�
		QuickSort(vet,p,q-1); // chama recursivamente ?elementos � esquerda do piv�
		QuickSort(vet,q+1,r); // chama recursivamente ? elementos � direita do piv�
	}
}
void GeraArquivo(){
	int i, j=TAM, k=0, *auxvet, t=0, g=0;
	long int random, random2 = 0;
	char c[100];
	auxvet = (int*)malloc(sizeof(int)*FIX); //Aloca um vetor de tamanho definido pelo FIX
	FILE *arq; // Cria uma vari�vel do tipo file
	srand(time(NULL));
	
	
		for(i=0;i<FIX;i++){ //Atribui zero a todas as posi��es do vetor auxvet 
			auxvet[i] = 0;
	}
	
	arq = fopen("UserData.dat", "w"); // Cria um arquivo chamado UserData com a extens�o .dat
	while(j!=0){ // J tem o valor atribuido de TAM	
		for(i=0;i<TAM;i++){
			random = 1+rand()%100; // Faz um random para verificar quantas vezes o la�o de repeti��o vai se repetir
			for(k=0;k<random;k++){
				random2 += rand()%10000; // Como o ramdom anterior vai de 1 a 100 e esse random vai de 0 a 10000, o valor m�ximo de um id ser� 1000000
			}
			if(auxvet[random2]==0){ 
				auxvet[random2]=1; // Se o valor de random no vetor tiver uma posi��o atribuida como 0, a posi��o ir� receber 1
				fprintf(arq,"%d",random2); // Grava o ID no arquivo UserData
				t++;
				random2=0; // Zera o valor de random2 para que ele esteja vazio na pr�xima itera��o
				break;
			}else{
				i--; // Se o valor de random j� estiver preenchido com 1, ele ignora o i++ do inicio e retorna ao come�o do for
				g++;
				random2=0;
				continue;
			}
		}
		
		fprintf(arq," ");
		
		random = 4+rand()%23; // Sorteia a quantidade de caracteres que vai compor o nome
		for(i=0;i<random;i++){	
			c[i] = (char)(65+rand()%25); // as letras sorteadas contemplam todas as letras do alfabeto baseadas na tabela ASCII, essas letras v�o para uma string.
			fprintf(arq,"%c",c[i]); // Grava uma letra de cada vez no arquivo 
			
		}
		fprintf(arq," ");
		
		for(i=0;i<random;i++){		
			fprintf(arq,"%c",c[i]);	// Usa a string gravada anteriormente para compor o email
			
		}
		
		fprintf(arq,"@e-mail.com");
		j--;
		fprintf(arq," ");
			
		for(k=0;k<5+rand()%10;k++){ // Sorteia o tamanho da senha
			random2 = rand()%2; // Sorteia entre 1 e 2 para verificar se ser� composto por um numero ou um caractere
			if(random2==1){
				fprintf(arq,"%c",(char)(65+rand()%25));
			}
			else
				fprintf(arq,"%d",rand()%9);
		}
		fprintf(arq,"\n");
		
	}
	system("cls");
	printf("\nArquivo criado com sucesso\n");
	fclose(arq);  // Fecha o arquivo                                                                                                                                                                                              
}


int BuscaSequencial(TUsuario *usuarios,long int chave){
	long int i=0;
	
	while(chave != usuarios[i].cod){
		i = i + 1;
		if(i==100000){
			return -1;
		}
	}
	return i;
}

int BuscaBinaria(TUsuario *vet,long int chave){
	long int dir,esq,meio,encontrado = 0;
	dir = TAM - 1;
	esq = 0;
	
	while(esq <= dir && !encontrado){
		meio = (esq + dir)/2;
		if(vet[meio].cod == chave){
			encontrado = 1;
		}
		else if(chave < vet[meio].cod){
			dir = meio-1;
		}else{
			esq = meio+1;
		}
	}
	if(encontrado == 1){
		return meio;
	}else{
		return -1;
	}
}

void CopiaDados (TUsuario *vet, TUsuario *vet2){
	long int cont;
	FILE *arq;
	arq = fopen("UserData.dat","r");
	if(arq==NULL){
		printf("\nO arquivo esta vazio");
	}
	else{
		cont=0;
		while(!feof(arq)){
			fscanf(arq, "%ld %s %s %s", &vet[cont].cod, &vet[cont].nome, &vet[cont].email, &vet[cont].senha);
			cont++;
		}
		cont=0;
		while(!feof(arq)){
			fscanf(arq, "%ld %s %s %s", &vet2[cont].cod, &vet2[cont].nome, &vet2[cont].email, &vet2[cont].senha);
			cont++;
		}
		
		
	}
}

main(){
	long int  i,p=0,r=TAM-1, cont=0, op, chaveD, random, tam1=0; 
	TUsuario chave;
	struct timeval inicio, fim;
	double tmili, tempbin=0, tempseq=0;
	FILE *arq;
	srand(time(NULL));

	TUsuario *vet; 
	TUsuario *vet2;
	
	vet2 = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
	vet = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
	
	printf("\n1- Criar arquivo\n2- Comparar Busca Sequencial e binaria \n0- Para sair\n");
	scanf("%d", &op);
	arq = fopen("saida.txt", "w");
	while(op!=0){
		switch(op){
			case 1:
				GeraArquivo();
				printf("\n1- Criar arquivo\n2- Comparar Busca Sequencial e binaria \n0- Para sair\n");
				scanf("%d", &op);
				system("cls");
			break;
			
			case 2:
				//Heap Sort
				tempbin=0.0;
				tempseq=0.0;
				CopiaDados(vet,vet2);
				gettimeofday(&inicio, NULL);
				HeapSort(vet2);	
				gettimeofday(&fim, NULL);
				tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
				tempbin = tmili;
				while(tempseq<tempbin){
					for(i=0; i<tam1; i++){
						random = 1+rand()%100; 
						random = random * (1+rand()%10000);
						gettimeofday(&inicio, NULL);
						chaveD = BuscaSequencial(vet,random);
						gettimeofday(&fim, NULL);
						tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
						tempseq += tmili;
						
						gettimeofday(&inicio, NULL);
						chaveD = BuscaBinaria(vet2,random);
						gettimeofday(&fim, NULL);
						tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
						tempbin += tmili;	
					}
					tam1+=TAM2;	
							
				}
				tam1=0;
				fprintf(arq,"-An�lise: Busca Sequencial x Busca Bin�ria + Heap Sort:\n");
				fprintf(arq," Quantidade de chaves buscadas: %d\n",i);
				fprintf(arq," Tempo (s) Busca Sequencial: %f\n",tempseq/1000);
				fprintf(arq," Tempo (s) Busca Bin�ria: %f\n\n",tempbin/1000);
				printf("\n\nNumero de verificacoes necessarias: %d", i);
				printf("\nTempo busca sequencial: %f\n", tempseq);
				printf("Tempo busca binaria + Heap Sort: %f\n", tempbin);
				free(vet);
				free(vet2);
				vet2 = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
				vet = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
				
				//Insertion Sort
				tempbin=0.0;
				tempseq=0.0;
				CopiaDados(vet,vet2);
				gettimeofday(&inicio, NULL);
				InsertionSort(vet2);	
				gettimeofday(&fim, NULL);
				tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
				tempbin = tmili;
				while(tempseq<tempbin){
					for(i=0; i<tam1; i++){
						random = 1+rand()%100; 
						random = random * (1+rand()%10000);
						gettimeofday(&inicio, NULL);
						chaveD = BuscaSequencial(vet,random);
						gettimeofday(&fim, NULL);
						tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
						tempseq += tmili;
						
						gettimeofday(&inicio, NULL);
						chaveD = BuscaBinaria(vet2,random);
						gettimeofday(&fim, NULL);
						tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
						tempbin += tmili;	
					}
					tam1+=TAM2;			
				}
				tam1=0;
				fprintf(arq,"-An�lise: Busca Sequencial x Busca Bin�ria + Insertion Sort:\n");
				fprintf(arq," Quantidade de chaves buscadas: %d\n",i);
				fprintf(arq," Tempo (s) Busca Sequencial: %f\n",tempseq/1000);
				fprintf(arq," Tempo (s) Busca Bin�ria: %f\n\n",tempbin/1000);
				printf("\n\nNumero de verificacoes necessarias: %d", i);
				printf("\nTempo busca sequencial: %f\n", tempseq);
				printf("Tempo busca binaria + Insertion Sort: %f\n", tempbin);
				free(vet);
				free(vet2);
				vet2 = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
				vet = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
				
				//Merge Sort
				tempbin=0.0;
				tempseq=0.0;
				CopiaDados(vet,vet2);
				gettimeofday(&inicio, NULL);
				MergeSort(vet2,p,r);	
				gettimeofday(&fim, NULL);
				tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
				tempbin = tmili;
				while(tempseq<tempbin){
					for(i=0; i<tam1; i++){
						random = 1+rand()%100; 
						random = random * (1+rand()%10000);
						gettimeofday(&inicio, NULL);
						chaveD = BuscaSequencial(vet,random);
						gettimeofday(&fim, NULL);
						tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
						tempseq += tmili;
						
						gettimeofday(&inicio, NULL);
						chaveD = BuscaBinaria(vet2,random);
						gettimeofday(&fim, NULL);
						tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
						tempbin += tmili;	
					}
					tam1+=TAM2;			
				}
				tam1=0;
				fprintf(arq,"-An�lise: Busca Sequencial x Busca Bin�ria + Merge Sort:\n");
				fprintf(arq," Quantidade de chaves buscadas: %d\n",i);
				fprintf(arq," Tempo (s) Busca Sequencial: %f\n",tempseq/1000);
				fprintf(arq," Tempo (s) Busca Bin�ria: %f\n\n",tempbin/1000);
				printf("\n\nNumero de verificacoes necessarias: %d", i);
				printf("\nTempo busca sequencial: %f\n", tempseq);
				printf("Tempo busca binaria+ Merge Sort: %f\n", tempbin);
				free(vet);
				free(vet2);
				vet2 = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
				vet = (TUsuario*)malloc(sizeof(TUsuario)*TAM);

				//Quick Sort
				tempbin=0.0;
				tempseq=0.0;
				CopiaDados(vet,vet2);
				gettimeofday(&inicio, NULL);
				QuickSort(vet,p,r);	
				gettimeofday(&fim, NULL);
				tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
				tempbin = tmili;
				while(tempseq<tempbin){
					for(i=0; i<tam1; i++){
						random = 1+rand()%100; 
						random = random * (1+rand()%10000);
						gettimeofday(&inicio, NULL);
						chaveD = BuscaSequencial(vet2,random);
						gettimeofday(&fim, NULL);
						tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
						tempseq += tmili;
						
						gettimeofday(&inicio, NULL);
						chaveD = BuscaBinaria(vet,random);
						gettimeofday(&fim, NULL);
						tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
						tempbin += tmili;	
					}
					tam1+=TAM2;			
				}
				tam1=0;
				fprintf(arq,"-An�lise: Busca Sequencial x Busca Bin�ria + Quick Sort:\n");
				fprintf(arq," Quantidade de chaves buscadas: %d\n",i);
				fprintf(arq," Tempo (s) Busca Sequencial: %f\n",tempseq/1000);
				fprintf(arq," Tempo (s) Busca Bin�ria: %f\n\n",tempbin/1000);
				printf("\n\nNumero de verificacoes necessarias: %d", i);
				printf("\nTempo busca sequencial: %f\n", tempseq);
				printf("Tempo busca binaria + Quick Sort: %f\n", tempbin);
				free(vet);
				free(vet2);
				vet2 = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
				vet = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
				
				//Selection Sort
				tempbin=0.0;
				tempseq=0.0;
				CopiaDados(vet,vet2);
				gettimeofday(&inicio, NULL);
				SelectionSort(vet2);	
				gettimeofday(&fim, NULL);
				tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
				tempbin = tmili;
				while(tempseq<tempbin){
					for(i=0; i<tam1; i++){
						random = 1+rand()%100; 
						random = random * (1+rand()%10000);
						gettimeofday(&inicio, NULL);
						chaveD = BuscaSequencial(vet,random);
						gettimeofday(&fim, NULL);
						tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
						tempseq += tmili;
						
						gettimeofday(&inicio, NULL);
						chaveD = BuscaBinaria(vet2,random);
						gettimeofday(&fim, NULL);
						tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
						tempbin += tmili;	
					}
					tam1+=TAM2;			
				}
				tam1=0;
				fprintf(arq,"-An�lise: Busca Sequencial x Busca Bin�ria + Selection Sort:\n");
				fprintf(arq," Quantidade de chaves buscadas: %d\n",i);
				fprintf(arq," Tempo (s) Busca Sequencial: %f\n",tempseq/1000);
				fprintf(arq," Tempo (s) Busca Bin�ria: %f\n\n",tempbin/1000);
				printf("\n\nNumero de verificacoes necessarias: %d", i);
				printf("\nTempo busca sequencial: %f\n", tempseq);
				printf("Tempo busca binaria + Selection Sort: %f\n", tempbin);
				free(vet);
				free(vet2);
				vet2 = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
				vet = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
				
				//Shell Sort
				tempbin=0.0;
				tempseq=0.0;
				CopiaDados(vet,vet2);
				gettimeofday(&inicio, NULL);
				ShellSort(vet2);	
				gettimeofday(&fim, NULL);
				tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
				tempbin = tmili;
				while(tempseq<tempbin){
					for(i=0; i<tam1; i++){
						random = 1+rand()%100; 
						random = random * (1+rand()%10000);
						gettimeofday(&inicio, NULL);
						chaveD = BuscaSequencial(vet,random);
						gettimeofday(&fim, NULL);
						tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
						tempseq += tmili;
						
						gettimeofday(&inicio, NULL);
						chaveD = BuscaBinaria(vet2,random);
						gettimeofday(&fim, NULL);
						tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
						tempbin += tmili;	
					}
					tam1+=TAM2;			
				}
				tam1=0;
				fprintf(arq,"-An�lise: Busca Sequencial x Busca Bin�ria + Shell Sort:\n");
				fprintf(arq," Quantidade de chaves buscadas: %d\n",i);
				fprintf(arq," Tempo (s) Busca Sequencial: %f\n",tempseq/1000);
				fprintf(arq," Tempo (s) Busca Bin�ria: %f\n\n",tempbin/1000);
				printf("\n\nNumero de verificacoes necessarias: %d", i);
				printf("\nTempo busca sequencial: %f\n", tempseq);
				printf("Tempo busca binaria + Shell Sort: %f\n", tempbin);
				free(vet);
				free(vet2);
				vet2 = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
				vet = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
				
				// Bubble Sort
				tempbin=0.0;
				tempseq=0.0;
				CopiaDados(vet,vet2);
				gettimeofday(&inicio, NULL);
				BubbleSort(vet2);
				gettimeofday(&fim, NULL);
				tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
				tempbin = tmili;
				while(tempseq<tempbin){
					for(i=0; i<tam1; i++){
						random = 1+rand()%100; 
						random = random * (1+rand()%10000);
						gettimeofday(&inicio, NULL);
						chaveD = BuscaSequencial(vet,random);
						gettimeofday(&fim, NULL);
						tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
						tempseq += tmili;
						
						gettimeofday(&inicio, NULL);
						chaveD = BuscaBinaria(vet2,random);
						gettimeofday(&fim, NULL);
						tmili = (1000*(fim.tv_sec-inicio.tv_sec)+(fim.tv_usec-inicio.tv_usec)/1000);
						tempbin += tmili;	
					}
					tam1+=TAM2;			
				}
				tam1=0;
				fprintf(arq,"-An�lise: Busca Sequencial x Busca Bin�ria + Bubble Sort:\n");
				fprintf(arq," Quantidade de chaves buscadas: %d\n",i);
				fprintf(arq," Tempo (s) Busca Sequencial: %f\n",tempseq/1000);
				fprintf(arq," Tempo (s) Busca Bin�ria: %f\n\n",tempbin/1000);
				printf("\n\nNumero de verificacoes necessarias: %d", i);
				printf("\nTempo busca sequencial: %f\n", tempseq);
				printf("Tempo busca binaria + Bubble Sort: %f\n", tempbin);
				free(vet);
				free(vet2);
				vet2 = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
				vet = (TUsuario*)malloc(sizeof(TUsuario)*TAM);
				
				fclose(arq);
				
				
				printf("\n1- Criar arquivo\n2- Comparar Busca Sequencial e binaria \n0- Para sair\n");
				scanf("%d", &op);
				system("cls");
				
			break;
			
		}
	}
}
