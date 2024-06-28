/*
Trabalho pratico para hotel
Mateus rodrigues costa
Lucas José Lopes Ferreira
*/
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
  int codigo;
  char nome[100];
  char endereco[100];
  char telefone[15];
  int ProgramaDeFidelidad;
} Cliente;

typedef struct {
  int codigo;
  char nome[100];
  char telefone[15];
  char cargo[50];
  char salario[1000];
} Funcionario;

typedef struct {
  int codigoEstadia;
  int numeroDoQuarto;
  char dataEntrada[11]; // dd/mm/aaaa
  char dataSaida[11];   // dd/mm/aaaa
  int quantidadeDiarias;
  int codigoCliente;
} Estadia;

typedef struct {
  int numero;
  int quantidade_Hospedes;
  float valor_Diaria;
  char status[10];
} Quarto;

int gerarCodigoUnico(int referemciaDoCodigo) {
  /*
  Propósito: Gerar um código único sequencial para clientes, funcionários ou estadias, evitando duplicatas.
Parâmetros de entrada:
referenciaDoCodigo: Indica o tipo de código a ser gerado (1 para clientes, 2 para funcionários, 3 para estadias).
Valor de retorno:
O próximo código único disponível.
-1 em caso de erro ao abrir o arquivo.
  */
  char linhas[300];
  char *token;
  int vetor[20000];
  int contador = 0, codigoUnico = 1;
  FILE *arquivo;
  switch (referemciaDoCodigo) {
  case 1:
    arquivo = fopen("clientes.txt", "r");
    break;
  case 2:
    arquivo = fopen("funcionarios.txt", "r");
    break;
  case 3:
    arquivo = fopen("estadias.txt", "r");
    break;
  case 4:
    arquivo = fopen("quartos.txt", "r");
    break;
  }
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return -1;
  }
  while (fgets(linhas, sizeof(linhas), arquivo)) {
    if (strstr(linhas, "Código: ") != NULL) {
      token = strstr(linhas, "Código: ") + strlen("Código: ");
      while (*token == ' ')
        token++;
      char *end = strchr(token, ';');
      if (end != NULL) {
        *end = '\0';
      }
      vetor[contador] = atoi(token);
      contador++;
      if (contador >= 20000) {
        printf("numero macimo de codigos cadastrados");
        break;
      } else {
        for (int a = 0; a < contador; a++) {
          if (codigoUnico == vetor[a]) {
            codigoUnico++;
          }
        }
      }
    }
  }
  fclose(arquivo);
  return codigoUnico;
}

void cadastro_cliente() {
  /*
  Propósito: Cadastrar um novo cliente no arquivo clientes.txt Baseado na Estrutura clientes.
  Parâmetros de entrada: Nenhum.
  Valor de retorno: Cliente cadastrado com sucesso! OU Erro au abrir o aquirvo Clientes.
  */
  setlocale(LC_ALL, "Portuguese");
  Cliente cliente;
  FILE *arquivo = fopen("clientes.txt", "a");
  if (!arquivo) {
    printf("Erro ao abrir o arquivo de clientes.\n");
    return;
  }

  cliente.codigo = gerarCodigoUnico(1);
  printf("Código do Cliente: %d\n", cliente.codigo);

  printf("Digite o nome do cliente: ");
  fgets(cliente.nome, sizeof(cliente.nome), stdin);
  cliente.nome[strcspn(cliente.nome, "\n")] = '\0';

  printf("Digite o endereço do cliente: ");
  fgets(cliente.endereco, sizeof(cliente.endereco), stdin);
  cliente.endereco[strcspn(cliente.endereco, "\n")] = '\0';

  printf("Digite o telefone do cliente: "); // +55 (31) xxxxx-xxxx
  fgets(cliente.telefone, sizeof(cliente.telefone), stdin);
  cliente.telefone[strcspn(cliente.telefone, "\n")] = '\0';

  fprintf(arquivo,
          "Código: %d;\nNome: %s;\nEndereço: %s;\nTelefone: %s;\nPontos de "
          "fidelidade: %d;\n\n",
          cliente.codigo, cliente.nome, cliente.endereco, cliente.telefone,
          cliente.ProgramaDeFidelidad = 0);

  fclose(arquivo);
  printf("Cliente cadastrado com sucesso!\n");
}

void cadastro_funcionario() {
  /*
  Propósito: Cadastrar um novo funcionário no arquivo funcionarios.txt.
  Parâmetros de entrada: Nenhum.
  Valor de retorno: Fumcionarios cadastrado com sucesso! OU Erro au abrir o aquirvo funcionarios.

  */
  setlocale(LC_ALL, "Portuguese");
  Funcionario funcionario;
  FILE *arquivo = fopen("funcionarios.txt", "a");
  if (!arquivo) {
    printf("Erro ao abrir o arquivo de funcionario.\n");
    return;
  }

  funcionario.codigo = gerarCodigoUnico(2);
  printf("Código do Funcionario: %d\n", funcionario.codigo);

  printf("Digite o nome do funcionario: ");
  fgets(funcionario.nome, sizeof(funcionario.nome), stdin);
  funcionario.nome[strcspn(funcionario.nome, "\n")] = '\0';

  printf("Digite o telefone do funcionario: ");
  fgets(funcionario.telefone, sizeof(funcionario.telefone), stdin);
  funcionario.telefone[strcspn(funcionario.telefone, "\n")] = '\0';

  printf("Digite o cargo do funcionario: ");
  fgets(funcionario.cargo, sizeof(funcionario.cargo), stdin);
  funcionario.cargo[strcspn(funcionario.cargo, "\n")] = '\0';

  printf("Digite o salario do funcionario: ");
  fgets(funcionario.salario, sizeof(funcionario.salario), stdin);
  funcionario.salario[strcspn(funcionario.salario, "\n")] = '\0';

  fprintf(
      arquivo,
      "Código: %d;\nNome: %s;\nTelefone: %s;\nCargo: %s;\nSalario: R$%s;\n\n",
      funcionario.codigo, funcionario.nome, funcionario.telefone,
      funcionario.cargo, funcionario.salario);

  fclose(arquivo);
  printf("Funcionario cadastrado com sucesso!\n");
}

void cadastro_quarto() {
  /*
  Propósito: Cadastrar um novo quarto no arquivo quartos.txt.
  Parâmetros de entrada: Nenhum.
  Valor de retorno: Quarto cadastrado com sucesso! OU Erro au abrir o aquirvo Quartos.

  */
  setlocale(LC_ALL, "Portuguese");
  Quarto quarto;
  FILE *arquivo = fopen("quartos.txt", "a");
  if (!arquivo) {
    printf("Erro ao abrir o arquivo de quartos.\n");
    return;
  }
  quarto.numero = gerarCodigoUnico(4);
  printf("Número do quarto: %d\n", quarto.numero);
  printf("Quantidade de hóspedes: ");
  scanf("%d", &quarto.quantidade_Hospedes);
  printf("Valor da diária: ");
  scanf("%f", &quarto.valor_Diaria);
  strcpy(quarto.status, "desocupado");

  fprintf(arquivo,
          "Código: %d;\nQuantidade de hóspedes: %d;\nValor da diária: "
          "R$%2.f\nStatus: %s;\n\n",
          quarto.numero, quarto.quantidade_Hospedes, quarto.valor_Diaria,
          quarto.status);
  fclose(arquivo);
  printf("Quarto cadastrado com sucesso!\n");
}
  
int atualizarProgramaDeFidelidade(int codigo_do_hospede) {
  setlocale(LC_ALL, "Portuguese");
  FILE *arquivo = fopen("clientes.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo\n");
    return -1;
  }

  FILE *temp = fopen("temp.txt", "w");
  if (temp == NULL) {
    printf("Erro ao criar arquivo temporário\n");
    fclose(arquivo);
    return -1;
  }

  char linha[100];
  int codigo;
  int pontos;
  int encontrou = 0;
  while (fgets(linha, sizeof(linha), arquivo)) {
    if (strstr(linha, "Código: ") != NULL) {
      sscanf(linha, "Código: %d;", &codigo);
      fputs(linha, temp);
    } else if (strstr(linha, "Pontos de fidelidade: ") != NULL &&
               codigo == codigo_do_hospede) {
      sscanf(linha, "Pontos de fidelidade: %d;", &pontos);
      pontos += 10;
      fprintf(temp, "Pontos de fidelidade: %d;\n", pontos);
      encontrou = 1;
    } else {
      fputs(linha, temp);
    }
  }

  fclose(arquivo);
  fclose(temp);

  if (encontrou == 1) {
    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");
    return 0;
  } else {
    remove("temp.txt");
    printf("Código do hóspede não encontrado\n");
    return -2;
  }
}

int atualizarStatusQuarto(int numero_quarto, int quemChama) {
  /*
  Propósito: Atualiza o status de um quarto para "ocupado" ou "desocupado".
  Parâmetros de entrada:
  numero_quarto: Número do quarto a ser atualizado.
  quemChama: Indica quem está chamando a função (1 para ocupar o quarto, 2 para       
  desocupar).
  Valor de retorno:
  0 se a atualização for bem-sucedida.
  -1 se houver erro ao abrir o arquivo.

  */
  setlocale(LC_ALL, "Portuguese");
  FILE *arquivo = fopen("quartos.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo\n");
    return -1;
  }

  FILE *temp = fopen("temp.txt", "w");
  if (temp == NULL) {
    printf("Erro ao criar arquivo temporário\n");
    fclose(arquivo);
    return -1;
  }

  char linha[100];
  int numero;
  while (fgets(linha, sizeof(linha), arquivo)) {
    if (strstr(linha, "Numero: ") != NULL) {
      sscanf(linha, "Numero: %d;", &numero);
      fputs(linha, temp);
    } else if (strstr(linha, "Status: ") != NULL && numero == numero_quarto) {
      if (quemChama == 1) {
        fputs("Status: ocupado;\n", temp);
      } else {
        fputs("Status: desocupado;\n", temp);
      }
    } else {
      fputs(linha, temp);
    }
  }

  fclose(arquivo);
  fclose(temp);
  remove("quartos.txt");
  rename("temp.txt", "quartos.txt");
  return 0;
}

int acharUmQuartoLivre(int numero_de_hospedes) {
  /*
  Propósito: Encontrar um quarto livre com capacidade para um número específico de 
  hóspedes.
  Parâmetros de entrada:
  numero_de_hospedes: Número de hóspedes para o qual se busca um quarto.
  Valor de retorno:
  O número do quarto livre encontrado.
  -1 se houver erro ao abrir o arquivo.
  -2 se não houver quartos livres com a capacidade desejada.

  */
  setlocale(LC_ALL, "Portuguese");
  FILE *arquivo = fopen("quartos.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo\n");
    return -1;
  }

  int numero;
  int quantidade_Hospedes;
  float valor_Diaria;
  char status[15];
  char linha[100];

  while (fgets(linha, sizeof(linha), arquivo)) {
    if (strstr(linha, "Código: ") != NULL) {
      sscanf(linha, "Código: %d;", &numero);
    }
    if (strstr(linha, "Quantidade de hóspedes: ") != NULL) {
      sscanf(linha, "Quantidade de hóspedes: %d;", &quantidade_Hospedes);
    }
    if (strstr(linha, "Valor da diária: R$") != NULL) {
      sscanf(linha, "Valor da diária: R$%f", &valor_Diaria);
    }
    if (strstr(linha, "Status: ") != NULL) {
      sscanf(linha, "Status: %s;", status);
      if (quantidade_Hospedes >= numero_de_hospedes &&
          strcmp(status, "desocupado;") == 0) {
        fclose(arquivo);
        atualizarStatusQuarto(numero, 1);
        return numero;
      }
    }
  }
  printf("Todos os quartos estão ocupados\n");
  fclose(arquivo);
  return -2;
}

void lerData(struct tm *data) {
  /*
  Propósito: Ler uma data no formato dd/mm/yyyy e armazená-la em uma struct tm.
  Parâmetros de entrada:
  data: Ponteiro para a struct tm onde a data será armazenada.
  Valor de retorno: Nenhum.
  */
  setlocale(LC_ALL, "Portuguese");
  printf("Digite a data nesse formato dd/mm/yyyy : ");
  scanf("%d/%d/%d", &data->tm_mday, &data->tm_mon, &data->tm_year);
  data->tm_mon -= 1;
  data->tm_year -= 1900;
  data->tm_hour = 0;
  data->tm_min = 0;
  data->tm_sec = 0;
}

double calculadoraDeDiarias(struct tm *data1, struct tm *data2) {
  /*
  Propósito: Calcular a diferença em dias entre duas datas.
  Parâmetros de entrada:
  data1: Ponteiro para a struct tm da primeira data.
  data2: Ponteiro para a struct tm da segunda data.
  Valor de retorno:
  A diferença em dias entre as duas datas (double)

  */
  setlocale(LC_ALL, "Portuguese");
  time_t tempo1 = mktime(data1);
  time_t tempo2 = mktime(data2);
  return difftime(tempo2, tempo1) / (60 * 60 * 24);
}

int pesquisar_codigo(int codigo, int identificador) {
  /*
  Propósito: Verificar se um código existe em um dos arquivos de dados (clientes, funcionários ou estadias).
  Parâmetros de entrada:
  codigo: O código a ser pesquisado.
  identificador: Indica o tipo de arquivo a ser pesquisado (1 para clientes, 2 para funcionários, 3 para estadias).
  Valor de retorno:
  1 se o código for encontrado.
  -1 se houver erro ao abrir o arquivo.
  -2 se o código não for encontrado.
  */
  setlocale(LC_ALL, "Portuguese");
  FILE *arquivo;
  char linha[100];
  int codigoUnico;

  switch (identificador) {
  case 1:
    arquivo = fopen("clientes.txt", "r");
    break;
  case 2:
    arquivo = fopen("funcionarios.txt", "r");
    break;
  case 3:
    arquivo = fopen("estadias.txt", "r");
    break;
  }
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return -1;
  }
  while (fgets(linha, sizeof(linha), arquivo)) {
    if (strstr(linha, "Código: ") != NULL) {
      sscanf(linha, "Código: %d;", &codigoUnico);
    }
    if (codigoUnico == codigo) {
      fclose(arquivo);
      return 1;
    }
  }
  fclose(arquivo);
  return -2;
}

int pesquisar_cliente() {
  /*
  Propósito: Pesquisar um cliente pelo código e exibir seus dados.
  Parâmetros de entrada: Nenhuma.
  Valor de retorno:
  1 se o cliente for encontrado.
  -1 se o cliente não for encontrado.
  -2 se houver erro ao abrir o arquivo.

  */
  setlocale(LC_ALL, "Portuguese");
  int codigo = 0;
  char linha[100];
  int codigoDeTeste;
  int encontrado = 0;

  printf("insira o codigo do cliente: ");
  scanf("%d", &codigo);
  if (pesquisar_codigo(codigo, 1) == 1) {
    FILE *arquivo = fopen("clientes.txt", "r");
    if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo\n");
      return -2;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
      if (strstr(linha, "Código: ") != NULL) {
        sscanf(linha, "Código: %d;", &codigoDeTeste);
      }
      if (codigoDeTeste == codigo) {
        encontrado = 1;
        printf("%s", linha);
        while (fgets(linha, sizeof(linha), arquivo) &&
               strstr(linha, "Código: ") == NULL) {
          printf("%s", linha);
        }
        break;
      }
    }

    fclose(arquivo);
    return 1;
  } else {
    printf("Não há nenhum cliente com o código %d cadastrado\n", codigo);
  }

  return -1;
}

void cadastro_estadia() {
  /*
  Propósito: Cadastrar uma nova estadia para um cliente.
  Parâmetros de entrada: Nenhum.
  Valor de retorno: Estadio cadastrada com suceçõ ou Erro au abri arquivo Estadis.

  */
  setlocale(LC_ALL, "Portuguese");
  Estadia estadia;
  int numero_de_hospedes, respostaPesquisarCodigo;

  printf("Insira o código do cliente: ");
  scanf("%d", &estadia.codigoCliente);
  getchar();
  atualizarProgramaDeFidelidade(estadia.codigoCliente);
  respostaPesquisarCodigo = pesquisar_codigo(estadia.codigoCliente, 1);

  if (respostaPesquisarCodigo == 1) {
    printf("Insira o número de hóspedes: ");
    scanf("%d", &numero_de_hospedes);
    getchar();
    estadia.numeroDoQuarto = acharUmQuartoLivre(numero_de_hospedes);

    if (estadia.numeroDoQuarto == -2) {
      printf("Cadastre um novo quarto ou dê baixa em um quarto já existente\n");
      return;
    }

    printf("O quarto que atende a esse hóspede é o de número %d\n",
           estadia.numeroDoQuarto);
    estadia.codigoEstadia = gerarCodigoUnico(3);
    printf("O código dessa estadia é %d\n", estadia.codigoEstadia);
    struct tm entrada = {0}, saida = {0};
    do {
    printf("Insira a data de entrada dessa estadia");
    lerData(&entrada);

    printf("Insira a data de saída dessa estadia");
    lerData(&saida);

    strftime(estadia.dataEntrada, sizeof(estadia.dataEntrada), "%d/%m/%Y",
             &entrada);
    strftime(estadia.dataSaida, sizeof(estadia.dataSaida), "%d/%m/%Y", &saida);
    estadia.quantidadeDiarias = calculadoraDeDiarias(&entrada, &saida);
      if (estadia.quantidadeDiarias){
        printf("Data de saída e antecessora da data de saída digite novamente");
      }
    }while(estadia.quantidadeDiarias<1);
    FILE *arquivo = fopen("estadias.txt", "a");
    if (arquivo == NULL) {
      printf("Erro ao gravar estadia por falha ao abrir o arquivo\n");
      return;
    }

    fprintf(arquivo,
            "Código Cliente: %d;\nCódigo: %d;\nNúmero Do Quarto: %d;\nData De "
            "Entrada: %s;\nData De "
            "Saída: %s;\nQuantidade De Diárias: %d;\n\n",
            estadia.codigoCliente, estadia.codigoEstadia,
            estadia.numeroDoQuarto, estadia.dataEntrada, estadia.dataSaida,
            estadia.quantidadeDiarias);

    fclose(arquivo);
    printf("Estadia cadastrado com sucesso!\n");
  } else {
    printf("Código do Cliente inválido\n");
  }
}

int pesquisar_funcionario() {
  /*Propósito: Pesquisar um funcionário pelo código e exibir seus dados.
Parâmetros de entrada: Nenhum.
Valor de retorno:
1 se o funcionário for encontrado.
-1 se o funcionário não for encontrado.
*/
  setlocale(LC_ALL, "Portuguese");
  int codigo = 0;
  char linha[100];
  int codigoDeTeste;

  printf("insira o codigo do funcionarios: ");
  scanf("%d", &codigo);
  if (pesquisar_codigo(codigo, 2) == 1) {
    FILE *arquivo = fopen("funcionarios.txt", "r");
    if (arquivo == NULL) {
      printf("Erro ao abrir o arquivo\n");
      return -2;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
      if (strstr(linha, "Código: ") != NULL) {
        sscanf(linha, "Código: %d;", &codigoDeTeste);
      }
      if (codigoDeTeste == codigo) {
        printf("%s", linha);
        while (fgets(linha, sizeof(linha), arquivo) &&
               strstr(linha, "Código: ") == NULL) {
          printf("%s", linha);
        }
        break;
      }
    }

    fclose(arquivo);
    return 1;
  } else {
    printf("Não há nenhum funcionarios com o código %d cadastrado\n", codigo);
  }

  return -1;
}

void calcularValorDaEstadia(int codigo) {
  /*Propósito: Calcular o valor total de uma estadia com base no número de diárias e no valor da diária do quarto.
Parâmetros de entrada:
codigo: Código da estadia.
Valor de retorno: Nenhum.
*/
  setlocale(LC_ALL, "Portuguese");
  FILE *arquivoEstadia = fopen("estadias.txt", "r");
  if (arquivoEstadia == NULL) {
    printf("Erro ao abrir o arquivo Estadia\n");
    return;
  }

  FILE *arquivoQuarto = fopen("quartos.txt", "r");
  if (arquivoQuarto == NULL) {
    printf("Erro ao abrir o arquivo Quartos\n");
    fclose(arquivoEstadia);
    return;
  }

  char linha[200];
  int numerodediarias = 0, numeroDoQuarto = 0;
  float valorDiaria = 0.0;
  int codigoTeste = 0, codigoDoCliente = 0;
  int encontrouEstadia = 0;

  while (fgets(linha, sizeof(linha), arquivoEstadia)) {
    if (strstr(linha, "Código Cliente: ") != NULL) {
      sscanf(linha, "Código Cliente: %d;", &codigoDoCliente);
    }
    if (strstr(linha, "Código: ") != NULL) {
      sscanf(linha, "Código: %d;", &codigoTeste);
    }
    if (codigoTeste == codigo) {
      encontrouEstadia = 1;
      if (strstr(linha, "Número Do Quarto: ") != NULL) {
        sscanf(linha, "Número Do Quarto: %d;", &numeroDoQuarto);
      }
      if (strstr(linha, "Quantidade De Diárias: ") != NULL) {
        sscanf(linha, "Quantidade De Diárias: %d;", &numerodediarias);
      }
      if (numeroDoQuarto && numerodediarias) {
        break;
      }
    }
  }

  if (encontrouEstadia==1) {
    while (fgets(linha, sizeof(linha), arquivoQuarto)) {
      if (strstr(linha, "Código: ") != NULL) {
        sscanf(linha, "Código: %d;", &codigoTeste);
      }
      if (codigoTeste == numeroDoQuarto &&
          strstr(linha, "Valor da diária: R$") != NULL) {
        sscanf(linha, "Valor da diária: R$%f;", &valorDiaria);
        break;
      }
    }
  }

  fclose(arquivoEstadia);
  fclose(arquivoQuarto);

  if (numerodediarias > 0 && valorDiaria > 0.0) {
    printf("O valor a ser pago pelo cliente %d é de R$%.2f\n", codigoDoCliente,
           valorDiaria * numerodediarias);
    atualizarStatusQuarto(numeroDoQuarto, 2);
  } else {
    printf("Não foi possível calcular o valor da estadia para a estadia com "
           "código %d\n", codigo);
  }
}

void baixa_estadia() {
  /*Propósito: Exibir o histórico de estadias de um cliente.
Parâmetros de entrada: Nenhum.
Valor de retorno: Nenhum.
*/
  setlocale(LC_ALL, "Portuguese");
  int codigoEstadia;
  printf("insira o codigo da estadia: ");
  scanf("%d", &codigoEstadia);
  pesquisar_codigo(codigoEstadia, 3);
  calcularValorDaEstadia(codigoEstadia);
}

void estadiasDoCliente() {
  /*Propósito: Exibir o histórico de estadias de um cliente.
Parâmetros de entrada: Nenhum.
Valor de retorno: Nenhum.
*/
  setlocale(LC_ALL, "Portuguese");
  int codigoDoCliente;
  char linha[200];
  int codigoDeTeste;
  int encontrouEstadia = 0;

  printf("Insira o código do cliente que deseja ver o histórico de estadias: ");
  scanf("%d", &codigoDoCliente);

  if (pesquisar_codigo(codigoDoCliente, 1) != 1) {
    printf("Não há nenhum cliente com o código %d cadastrado\n",
           codigoDoCliente);
    return;
  }

  FILE *arquivo = fopen("estadias.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir arquivo estadias\n");
    return;
  }

  while (fgets(linha, sizeof(linha), arquivo)) {
    if (strstr(linha, "Código Cliente: ") != NULL) {
      sscanf(linha, "Código Cliente: %d;", &codigoDeTeste);
      if (codigoDeTeste == codigoDoCliente) {
        encontrouEstadia = 1;
        printf("%s", linha);
        while (fgets(linha, sizeof(linha), arquivo) &&
               strstr(linha, "Código Cliente: ") == NULL) {
          printf("%s", linha);
        }
      }
    }
  }

  if (!encontrouEstadia) {
    printf("Nenhuma estadia encontrada para o cliente com código %d\n",
           codigoDoCliente);
  }

  fclose(arquivo);
}

void calcular_pontos_fidelidade() {
  /*Propósito: Calcular e exibir os pontos de fidelidade de um cliente.
Parâmetros de entrada: Nenhum.
Valor de retorno: Nenhum.
*/
  setlocale(LC_ALL, "Portuguese");
  int codigoDecliente, pontosDeFidelida = 0, codigoDeTeste = 0;
  char linha[300];

  printf("Insira o código do cliente que deseja ver os pontos de fidelidade: ");
  scanf("%d", &codigoDecliente);

  if (pesquisar_codigo(codigoDecliente, 1) != 1) {
    printf("Cliente %d inexistente\n", codigoDecliente);
    return;
  }

  FILE *arquivo = fopen("clientes.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo clientes.txt\n");
    return;
  }

  while (fgets(linha, sizeof(linha), arquivo)) {
    if (strstr(linha, "Código: ") != NULL) {
      sscanf(linha, "Código: %d;", &codigoDeTeste);
    }
    if (codigoDeTeste == codigoDecliente &&
        strstr(linha, "Pontos de fidelidade: ") != NULL) {
      sscanf(linha, "Pontos de fidelidade: %d;", &pontosDeFidelida);
      printf("O cliente %d possui %d pontos de fidelidade\n", codigoDecliente,
             pontosDeFidelida);
      break;
    }
  }

  fclose(arquivo);
}

int main(void) {
  setlocale(LC_ALL, "Portuguese");
  int opcao;
  do {
    printf("Menu:\n");
    printf("1. Cadastrar Cliente\n");
    printf("2. Cadastrar Funcionario\n");
    printf("3. Cadastrar Quarto\n");
    printf("4. Cadastrar Estadia\n");
    printf("5. Buscar Cliente\n");
    printf("6. Buscar Funcionario\n");
    printf("7. Dar baixa em uma estadia\n");
    printf("8. Ver histrico de Estadia de um cliente\n");
    printf("9. Ver pontos de fidelidae de um cliente\n");
    printf("10. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
    case 1:
      cadastro_cliente();
      break;

    case 2:
      cadastro_funcionario();
      break;
    case 3:
      cadastro_quarto();
      break;
    case 4:
      cadastro_estadia();
      break;
    case 5:
      pesquisar_cliente();
      break;
    case 6:
      pesquisar_funcionario();
      break;
    case 7:
      baixa_estadia();
      break;
    case 8:
      estadiasDoCliente();
      break;
    case 9:
      calcular_pontos_fidelidade();
      break;
    case 10:
      printf("Saindo...\n");
      return 0;
    default:
      printf("Opcao invalida!\n");
    }
  } while (opcao != 10);

  return 0;
}