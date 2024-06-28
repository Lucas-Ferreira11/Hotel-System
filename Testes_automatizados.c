#include "munit.h"
#include "main.c"  

static MunitResult test_gerarCodigoUnico(const MunitParameter params[], void* data) {
    int codigo = gerarCodigoUnico(1); 
    munit_assert_int(codigo, !=, -1);
    return MUNIT_OK;
}

static MunitResult test_cadastro_cliente(const MunitParameter params[], void* data) {
    FILE *arquivo = fopen("clientes.txt", "w"); 
    if (arquivo) fclose(arquivo);

    cadastro_cliente();

    arquivo = fopen("clientes.txt", "r");
    munit_assert_not_null(arquivo);
    char linha[300];
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "Código: ")) {
            encontrado = 1;
            break;
        }
    }
    fclose(arquivo);
    munit_assert_int(encontrado, ==, 1);
    return MUNIT_OK;
}


static MunitResult test_cadastro_funcionario(const MunitParameter params[], void* data) {
    FILE *arquivo = fopen("funcionarios.txt", "w"); 
    if (arquivo) fclose(arquivo);

    cadastro_funcionario();

    arquivo = fopen("funcionarios.txt", "r");
    munit_assert_not_null(arquivo);
    char linha[300];
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "Código: ")) {
            encontrado = 1;
            break;
        }
    }
    fclose(arquivo);
    munit_assert_int(encontrado, ==, 1);
    return MUNIT_OK;
}

static MunitResult test_cadastro_quarto(const MunitParameter params[], void* data) {
    FILE *arquivo = fopen("quartos.txt", "w"); 
    if (arquivo) fclose(arquivo);

    cadastro_quarto();

    arquivo = fopen("quartos.txt", "r");
    munit_assert_not_null(arquivo);
    char linha[300];
    int encontrado = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "Código: ")) {
            encontrado = 1;
            break;
        }
    }
    fclose(arquivo);
    munit_assert_int(encontrado, ==, 1);
    return MUNIT_OK;
}

static MunitResult test_atualizarProgramaDeFidelidade(const MunitParameter params[], void* data) {
    FILE *arquivo = fopen("clientes.txt", "w"); 
    if (arquivo) {
        fprintf(arquivo, "Código: 1;\nPontos de fidelidade: 0;\n");
        fclose(arquivo);
    }

    int resultado = atualizarProgramaDeFidelidade(1);
    munit_assert_int(resultado, ==, 0);

    arquivo = fopen("clientes.txt", "r");
    munit_assert_not_null(arquivo);
    char linha[300];
    int pontos = -1;
    while (fgets(linha, sizeof(linha), arquivo)) {
        if (strstr(linha, "Pontos de fidelidade: ")) {
            sscanf(linha, "Pontos de fidelidade: %d;", &pontos);
            break;
        }
    }
    fclose(arquivo);
    munit_assert_int(pontos, ==, 10);
    return MUNIT_OK;
}

static MunitResult test_pesquisar_cliente(const MunitParameter params[], void* data) {
    FILE *arquivo = fopen("clientes.txt", "w");
    if (arquivo) {
        fprintf(arquivo, "Código: 1;\nNome: Teste;\nEndereço: Teste;\nTelefone: Teste;\nPontos de fidelidade: 0;\n");
        fclose(arquivo);
    }

    int resultado = pesquisar_cliente();
    munit_assert_int(resultado, ==, 1);
    return MUNIT_OK;
}

static MunitTest test_suite_tests[] = {
    { (char*) "/gerarCodigoUnico", test_gerarCodigoUnico, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/cadastro_cliente", test_cadastro_cliente, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/cadastro_funcionario", test_cadastro_funcionario, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/cadastro_quarto", test_cadastro_quarto, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/atualizarProgramaDeFidelidade", test_atualizarProgramaDeFidelidade, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { (char*) "/pesquisar_cliente", test_pesquisar_cliente, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
    { NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite test_suite = {
    (char*) "",
    test_suite_tests,
    NULL,
    1,
    MUNIT_SUITE_OPTION_NONE
};

int main(int argc, char* argv[]) {
    return munit_suite_main(&test_suite, NULL, argc, argv);
}