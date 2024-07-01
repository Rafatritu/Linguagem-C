#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nome[50];
  char curso[20];
  float nota1;
  float nota2;
  float nota3;
  float media;
} Aluno;

void cadastrar_aluno(Aluno *aluno) {
   
  printf("----- CADASTRO DE ALUNO -----\n");

  printf("Digite o nome do aluno: ");
  scanf("%s", aluno->nome);

  printf("Digite o curso do aluno: ");
  scanf("%s", aluno->curso);

  do {
    printf("Digite a nota 1 do aluno (0 a 10): ");
    scanf("%f", &(aluno->nota1));
  } while (aluno->nota1 < 0 || aluno->nota1 > 10);

  do {
    printf("Digite a nota 2 do aluno (0 a 10): ");
    scanf("%f", &(aluno->nota2));
  } while (aluno->nota2 < 0 || aluno->nota2 > 10);

  do {
    printf("Digite a nota 3 do aluno (0 a 10): ");
    scanf("%f", &(aluno->nota3));
  } while (aluno->nota3 < 0 || aluno->nota3 > 10);
}

void calcular_media_aluno(Aluno alunos[], int tamanho, char buscar[]) {
  printf("Pressione Enter para continuar...");
  getchar(); // Aguardando a entrada do usuário

  float soma = 0;
  int contador = 0;
  int i;

  for (i = 0; i < tamanho; i++) {
    if (strcmp(alunos[i].nome, buscar) == 0) {
      soma = alunos[i].nota1 + alunos[i].nota2 + alunos[i].nota3;
      contador++;
      break;
    }
  }

  if (contador == 0) {
    printf("Aluno nao encontrado.\n");
  } else {
    float media = soma / 3;
    printf("A media do aluno %s e: %.2f\n", alunos[i].nome, media);
  }
}

float calcular_media_geral(Aluno alunos[], int tamanho) {
  printf("Pressione Enter para continuar...");
  getchar(); // Aguardando a entrada do usuário

  float soma_media = 0;
  int i;

  for (i = 0; i < tamanho; i++) {
    soma_media += alunos[i].nota1 + alunos[i].nota2;
  }

  return soma_media / (2 * tamanho);
}

void gerar_ranking(Aluno alunos[], int tamanho) {
  printf("Pressione Enter para continuar...");
  getchar(); // Aguardando a entrada do usuário

  int i, j;
  Aluno temp;

  for (i = 0; i < tamanho - 1; i++) {
    for (j = 0; j < tamanho - i - 1; j++) {
      if (alunos[j].media < alunos[j + 1].media) {
        temp = alunos[j];
        alunos[j] = alunos[j + 1];
        alunos[j + 1] = temp;
      }
    }
  }

  printf("Ranking dos 10 melhores alunos:\n");

  for (i = 0; i < 10 && i < tamanho; i++) {
    printf("%d. Aluno: %s, Curso: %s, Media: %.2f\n", i + 1, alunos[i].nome,
           alunos[i].curso, alunos[i].media);
  }
}

void salvar_alunos_csv(Aluno alunos[], int tamanho) {
  printf("Pressione Enter para continuar...");
  getchar(); // Aqui aguarda a entrada do usuário

  FILE *arquivo;
  arquivo = fopen("alunos.csv", "w"); // Aqui é pra abrir o arquivo em modo de escrita ("w")

  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo.\n");
    return;
  }
  // Ele escreve o cabeçalho no arquivo
  fprintf(arquivo, "Nome;Curso;Nota 1;Nota 2;Nota 3;Media\n");
  // Irá percorrer os alunos e escreve suas informações no arquivo CSV
  for (int i = 0; i < tamanho; i++) {
    // Aqui Calcula a média 
    alunos[i].media =
        (alunos[i].nota1 + alunos[i].nota2 + alunos[i].nota3) / 3.0;
    // Irá escrever os dados no arquivo
    fprintf(arquivo, "%s;%s;%.2f;%.2f;%.2f;%.2f\n", alunos[i].nome,
            alunos[i].curso, alunos[i].nota1, alunos[i].nota2, alunos[i].nota3,
            alunos[i].media);
  }
  fclose(arquivo);
  printf("Alunos salvos em alunos.csv com sucesso!\n");
}
void carregar_alunos_csv(Aluno alunos[], int *tamanho) {
  FILE *arquivo;
  arquivo = fopen("alunos.csv", "r"); // Também para abrir o arquivo só que em modo de leitura ("r")
  if (arquivo == NULL) {
    printf("Nenhum aluno encontrado.\n");
    return;
  }
  char linha[100];
  fgets(linha, sizeof(linha), arquivo); // Ele ignora a linha do cabeçalho
  int i = 0;
  while (fgets(linha, sizeof(linha), arquivo)) {
    char *atributo;
    atributo = strtok(
        linha, ";"); // Nessa parte ele divide a linha em campos separados pelo ponto e vírgula
    // Copiar os valores para a struct Aluno
    strcpy(alunos[i].nome, atributo);
    atributo = strtok(NULL, ";");
    strcpy(alunos[i].curso, atributo);
    atributo = strtok(NULL, ";");
    alunos[i].nota1 = atof(atributo);
    atributo = strtok(NULL, ";");
    alunos[i].nota2 = atof(atributo);
    atributo = strtok(NULL, ";");
    alunos[i].nota3 = atof(atributo);
    // Calcula a média
    alunos[i].media =
        (alunos[i].nota1 + alunos[i].nota2 + alunos[i].nota3) / 3.0;
    i++;
  }
  fclose(arquivo);
  *tamanho = i;
  printf("Alunos carregados de alunos.csv com sucesso!\n");
}
int main() {
  Aluno alunos[100];
  int num_alunos = 0;
  int opcao;

  carregar_alunos_csv(alunos, &num_alunos);

 do {
        printf("----- MENU -----\n");
        printf("1. Cadastrar aluno\n");
        printf("2. Calcular media do aluno\n");
        printf("3. Calcular media geral\n");
        printf("4. Gerar ranking\n");
        printf("5. Salvar alunos em arquivo CSV\n");
        printf("0. Sair\n");

        printf("Digite a opcao desejada: ");
        scanf("%d", &opcao);
        getchar(); // Serve para consumir o caractere de nova linha (\n)

        switch (opcao) {
            case 1:
                if (num_alunos < 100) {
                    cadastrar_aluno(&alunos[num_alunos]);
                    num_alunos++;
                    printf("Aluno cadastrado com sucesso!\n");
                } else {
                    printf("Limite de alunos atingido!\n");
                }
                break;
            case 2:
                if (num_alunos > 0) {
                    char nome[50];
                    printf("Digite o nome do aluno: ");
                    scanf("%s", nome);
                    calcular_media_aluno(alunos, num_alunos, nome);
                } else {
                    printf("Nenhum aluno cadastrado.\n");
                }
                break;
            case 3:
                if (num_alunos > 0) {
                    float media_geral = calcular_media_geral(alunos, num_alunos);
                    printf("A media geral dos alunos e: %.2f\n", media_geral);
                } else {
                    printf("Nenhum aluno cadastrado.\n");
                }
                break;
            case 4:
                if (num_alunos > 0) {
                    gerar_ranking(alunos, num_alunos);
                } else {
                    printf("Nenhum aluno cadastrado.\n");
                }
                break;
            case 5:
                if (num_alunos > 0) {
                    salvar_alunos_csv(alunos, num_alunos);
                } else {
                    printf("Nenhum aluno cadastrado.\n");
                }
                break;
                case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
        printf("\n");
    } while (opcao != 0);
    return 0;
}