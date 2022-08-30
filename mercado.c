#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h> // No Linux/Mac, #include <unistd.h>


typedef struct {
	int codigo;
	char nome[30];
	float preco;
} Produto;

typedef struct {
	Produto produto;
	int quantidade;
} Carrinho;

void infoProduto(Produto prod);
void menu();
void cadastrarProduto();
void listarProdutos();
void comprarProduto();
void visualizarCarrinho();
Produto pegarProdutoPorCodigo(int codigo);
int * temNoCarrinho(int codigo);
void fecharPedido();

static int contador_produto = 0;
static int contador_carrinho = 0;
static Carrinho carrinho[50];
static Produto produtos[50];

int main(){

	menu();

	return 0;
}

void infoProduto(Produto prod){
	printf("Código: %d \nNome: %s \nPreço: %.2f\n", prod.codigo, strtok(prod.nome, "\n"), prod.preco);
}

void menu(){
	printf("==================================\n");
	printf("========== Bem-vindo(a) ==========\n");
	printf("==========  Geek  Shop  ==========\n");
	printf("==================================\n");

	printf("Selecione uma das opções abaixo: \n");
	fflush(stdout);
	printf("1 - Cadastrar produto\n");
	fflush(stdout);
	printf("2 - Listar produtos\n");
	fflush(stdout);
	printf("3 - Comprar produto\n");
	fflush(stdout);
	printf("4 - Visualizar carrinho\n");
	fflush(stdout);
	printf("5 - Fechar pedido\n");
	fflush(stdout);
	printf("6 - Sair do sistema\n");
	fflush(stdout);

	int opcao;
	scanf("%d", &opcao);
	getchar();

	switch(opcao){
	case 1:
		cadastrarProduto();
		break;
	case 2:
		listarProdutos();
		break;
	case 3:
		comprarProduto();
		break;
	case 4:
		visualizarCarrinho();
		break;
	case 5:
		fecharPedido();
	case 6:
		printf("Volte sempre!\n");
		fflush(stdout);
		Sleep(2);
		exit(0);
	default:
		printf("Opção inválida!\n\n");
		fflush(stdout);
		Sleep(2);
		menu();
		break;
	}
}

void cadastrarProduto(){
	printf("\nCadastro de produto\n");
	fflush(stdout);
	printf("====================\n");
	fflush(stdout);

	printf("Informe o nome do produto: \n");
	fflush(stdout);
	fgets(produtos[contador_produto].nome, 30, stdin);

	printf("Informe o preço do produto: \n");
	fflush(stdout);
	scanf("%f", &produtos[contador_produto].preco);

	printf("O produto %s for cadastrado com sucesso.\n\n", strtok(produtos[contador_produto].nome, "\n"));
	fflush(stdout);

	produtos[contador_produto].codigo = (contador_produto + 1);
	contador_produto++;

	Sleep(2);
	menu();
}

void listarProdutos(){
	if(contador_produto > 0){
		printf("\nListagem de produtos\n");
		fflush(stdout);
		printf("---------------------\n");
		fflush(stdout);
		for(int i = 0; i < contador_produto; i++){
			infoProduto(produtos[i]);
			printf("---------------------\n");
			printf("\n");
			fflush(stdout);
			Sleep(1);
		}
		sleep(2);
		menu();
	}else{
		printf("Não temos produtos cadastrados ainda.\n\n");
		fflush(stdout);
		Sleep(2);
		menu();
	}
}

void comprarProduto(){
	if(contador_produto > 0){
		printf("\nInforme o código do produto que deseja adicionar ao carrinho: \n");
		fflush(stdout);
		printf("====== Produtos Disponíveis ======\n");
		fflush(stdout);
		for(int i = 0; i < contador_produto; i++){
			infoProduto(produtos[i]);
			printf("---------------------\n");
			fflush(stdout);
			Sleep(1);
		}
		int codigo;
		scanf("%d", &codigo);
		getchar();

		int tem_mercado = 0;
		for(int i = 0; i < contador_produto; i++){
			if(produtos[i].codigo == codigo){
				tem_mercado = 1;

				if(contador_carrinho > 0){
					int * retorno = temNoCarrinho(codigo);

					if(retorno[0] == 1){
						carrinho[retorno[1]].quantidade++;
						printf("Aumentei a quantidade do produto %s já existente no carrinho.\n\n",
								strtok(carrinho[retorno[1]].produto.nome, "\n"));
						fflush(stdout);
						Sleep(2);
						menu();
					}else{
						Produto p = pegarProdutoPorCodigo(codigo);
						carrinho[contador_carrinho].produto = p;
						carrinho[contador_carrinho].quantidade = 1;
						contador_carrinho++;
						printf("O produto %s foi adicionado ao carrinho.\n", strtok(p.nome, "\n"));
						fflush(stdout);
						Sleep(2);
						menu();
					}
				}else{
					Produto p = pegarProdutoPorCodigo(codigo);
					carrinho[contador_carrinho].produto = p;
					carrinho[contador_carrinho].quantidade = 1;
					contador_carrinho++;
					printf("\nO produto %s foi adicionado ao carrinho.\n\n", strtok(p.nome, "\n"));
					fflush(stdout);
					Sleep(2);
					menu();
				}
			}
		}
		if(tem_mercado < 1){
			printf("Não foi encontrado o produto com código %d\n\n", codigo);
			fflush(stdout);
			Sleep(2);
			menu();
		}
	}else{
		printf("Ainda não existem produtos para vender.\n\n");
		fflush(stdout);
		Sleep(2);
		menu();
	}
}

void visualizarCarrinho(){
	if(contador_carrinho > 0){
		printf("\nProdutos do carrinho\n");
		fflush(stdout);
		printf("---------------------\n");
		fflush(stdout);
		for(int i = 0; i < contador_carrinho; i++){
			infoProduto(carrinho[i].produto);
			printf("Quantidade: %d\n", carrinho[i].quantidade);
			fflush(stdout);
			printf("---------------------\n");
			printf("\n");
			fflush(stdout);
			Sleep(1);
		}
		Sleep(2);
		menu();
	}else{
			printf("Não temos produtos no carrinho ainda.\n\n");
			fflush(stdout);
			Sleep(2);
			menu();
	}
}

Produto pegarProdutoPorCodigo(int codigo){
	Produto p;
	for(int i = 0; i < contador_produto; i++){
		if(produtos[i].codigo == codigo){
			p = produtos[i];
		}
	}
	return p;
}

int * temNoCarrinho(int codigo){
	int static retorno[] = {0, 0};
	for(int i = 0; i < contador_carrinho; i++){
		if(carrinho[i].produto.codigo == codigo){
			retorno[0] = 1; //tem o produto com este código no carrinho
			retorno[1] = i; //o índice do produto no carrinho
		}
	}
	return retorno;
}

void fecharPedido(){
	if(contador_carrinho > 0){
		float valorTotal = 0.0;
		printf("\nProdutos do carrinho\n");
		fflush(stdout);
		printf("---------------------\n");
		fflush(stdout);
		for(int i = 0; i < contador_carrinho; i++){
			Produto p = carrinho[i].produto;
			int quantidade = carrinho[i].quantidade;
			valorTotal += p.preco * quantidade;
			infoProduto(p);
			printf("Quantidade : %d\n", quantidade);
			fflush(stdout);
			printf("---------------------\n");
			fflush(stdout);
			Sleep(1);
		}
		printf("Sua fatura é: %.2f\n", valorTotal);
		fflush(stdout);

		//limpar carrinho
		contador_carrinho = 0;
		printf("Obrigado pela preferência.\n\n");
		fflush(stdout);
		Sleep(5);
		menu();
	}else{
		printf("Você ainda não tem nenhum produto no carrinho.\n\n");
		fflush(stdout);
		Sleep(2);
		menu();
	}
}
