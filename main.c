//Alunos: Michael Gomes e Rhuar Carvalho

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Produto {
    int codigo;
    double valor_unitario, valor_atacado;
    int min_atacado;
    char descricao[200];
} Produto;

double crediario[10];
int estoque[10];

void sorteia_cliente(){
    int sorteado[10];
    memset(sorteado, 0, sizeof sorteado);
    for (int i = 0; i < 10; ++i) {
        int cliente = rand() % 10;
        while (sorteado[cliente] != 0) {
            cliente = rand() % 10;
        }
        sorteado[cliente] = 1;
        if (crediario[cliente] != 0) {
            sorteado[cliente] = 1;
            crediario[cliente] = 0;
            printf("Cliente %d perdoado!\n\n", cliente);
            return;
        }
    }
    printf("Não foi possível perdoar um cliente.\n\n");
}

void novo_estoque(){
    for (int i = 0; i < 10; ++i) estoque[i] = rand() % 222;
}

Produto carrega_produto(int i){
    Produto p[10];
    char s[10][200] = {"ALGODAO", "FRANGO", "SABONETE", "MANTEIGA", "BATATA PALHA", 
                    "PRESTOBARBA", "CREME DENTAL", "LEITE EM PO", "AGUA SANITARIA", "SHAMPOO"};
    double valor_unitario[10] = {3.88, 18.9, 3.15, 25, 18.5, 28, 5, 18, 7.57, 9.9};
    double valor_atacado[10] = {3, 15, 2.5, 20, 16, 25, 3.99, 14.47, 7, 9};
    int min_atacado[10] = {30, 20, 100, 10, 50, 80, 237, 60, 30, 40};

    for (int i = 0; i < 10; ++i) {
        p[i].codigo = i;
        strcpy(p[i].descricao, s[i]);
        p[i].valor_unitario = valor_unitario[i];
        p[i].valor_atacado = valor_atacado[i];
        p[i].min_atacado = min_atacado[i];
    }
    return p[i];
}

void pagarComCrediario(double total){
    int codigo;
    printf("Insira o código do cliente: ");
    scanf("%d", &codigo);
    crediario[codigo] += total;
    printf("Valor do crediário atualizado: R$ %.2lf\n\n", crediario[codigo]);
}

void consulta_debitos(){
    int codigo;
    printf("Insira o código do cliente: ");
    scanf("%d", &codigo);
    printf("O cliente %d possui R$ %.2lf de débitos\n\n", codigo, crediario[codigo]);
}

void paga_debitos(){
    int codigo;
    double valor;
    printf("Insira o código do cliente: ");
    scanf("%d", &codigo);
    printf("Insira o valor que deseja pagar: ");
    scanf("%lf", &valor);
    if (crediario[codigo] < valor){
        printf("O valor é maior do que o débito\n\n");
        return;
    }
    crediario[codigo] -= valor;
}

void comprar(){
    int codigo, qtd;
    double total = 0;
    int carrinho[10];
    for (int i = 0; i < 10; ++i) carrinho[i] = 0;
    while(1){
        printf("Produtos são códigos de 0 a 9\n");

        printf("Insira o código do produto (ou -1 para sair): ");
        scanf("%d", &codigo);
        if (codigo == -1){
            break;
        }
        if (codigo > 9) {
            printf("Produto não encontrado.\n\n");
            continue;
        }
        Produto p = carrega_produto(codigo);
        printf("Insira a quantidade que deseja: ");
        scanf("%d", &qtd);
        if (qtd > estoque[codigo%10]){
            printf("O estoque para o produto é de %d, favor informar número menor.\n\n", estoque[codigo%10]);
            continue;
        }
        estoque[codigo%10] -= qtd;
        carrinho[codigo%10] += qtd;
    }
    for (int i = 0; i < 10; ++i){
        Produto p = carrega_produto(i);
        if (carrinho[i] >= p.min_atacado){
            total += carrinho[i]*p.valor_atacado;
        }
        else {
            total += carrinho[i]*p.valor_unitario;
        }

    }
    printf("Valor total da compra: R$ %.2lf\n", total);
    
    printf("1 - Pix (Desconto de 5%%)\n");
    printf("2 - Cartão\n");
    printf("3 - Dinheiro em espécie (Desconto de 2%%)\n");
    printf("4 - Crediário\n");
    printf("Qual a forma de pagamento?\nOpção: ");
    int opcao;
    scanf("%d", &opcao);
    if (opcao == 1) printf("Valor total: R$ %.2lf\n\n", 0.95*total);
    else if (opcao == 2) printf("Valor total: R$ %.2lf\n\n", total);
    else if (opcao == 3) printf("Valor total: R$ %.2lf\n\n", 0.98*total);
    else if (opcao == 4) pagarComCrediario(total);
}

void menu(){
    printf("\nBem vindo ao Mercadinho MR");

    printf("\n\n1 - Simular compra\n");
    printf("2 - Consultar débitos de clientes do crediário\n");
    printf("3 - Preencher estoque\n");
    printf("4 - Consultar estoque\n");
    printf("5 - Pagar débitos de clientes do crediário (total ou parcial)\n");
    printf("6 - Sortear um cliente que terá sua dívida do crediário perdoada\n");
    printf("0 - Sair\n\n");
}

void aumenta_estoque(){
    int codigo, qtd;
    printf("Insira o codigo do produto: ");
    scanf("%d", &codigo);
    if (!(codigo >= 0 && codigo <= 9)){
        printf("Produto não encontrado.\n\n");
        return;
    }
    printf("Insira a quantidade a preencher: ");
    scanf("%d", &qtd);
    estoque[codigo % 10] += qtd;
}

void consulta_estoque(){
    int codigo;
    printf("Insira o código do produto: ");
    scanf("%d", &codigo);
    if (!(codigo >= 0 && codigo <= 9)){
        printf("Produto não encontrado.\n\n");
        return;
    }
    printf("A quantidade do produto %d é: %d\n\n", codigo, estoque[codigo % 10]);
}

int entrada(){
    int a;
    printf("Acao: ");
    scanf("%d", &a);
    return a;
}

int main(){
    srand(time(NULL));
    novo_estoque();
    while (1){
        menu();
        int opcao = entrada();
        if (opcao == 1) comprar(); 
        else if (opcao == 2) consulta_debitos();
        else if (opcao == 3) aumenta_estoque();
        else if (opcao == 4) consulta_estoque();
        else if (opcao == 5) paga_debitos();
        else if (opcao == 6) sorteia_cliente();
        else if (opcao == 0) return 0;
    }
    return 0;
}

