#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que gera o fractal 2: Floco de neve de onda quadrada de von Koch 
void recursao_fractal(char *buffer, int nivel) {
    if (nivel == 0) {
        strcat(buffer, "F");
    } else {
        recursao_fractal(buffer, nivel - 1);
        strcat(buffer, "-");
        recursao_fractal(buffer, nivel - 1);
        strcat(buffer, "+");
        recursao_fractal(buffer, nivel - 1);
        strcat(buffer, "+");
        recursao_fractal(buffer, nivel - 1);
        recursao_fractal(buffer, nivel - 1);
        strcat(buffer, "-");
        recursao_fractal(buffer, nivel - 1);
        strcat(buffer, "-");
        recursao_fractal(buffer, nivel - 1);
        strcat(buffer, "+");
        recursao_fractal(buffer, nivel - 1);
    }
}

void axiom_x_hilbert (char *buffer, int nivel);

// Função que define o axioma Y do fractal 6: Preenchimento de espaço de Hilbert
// Y → +XF-YFY-FX+
void axiom_y_hilbert (char *buffer, int nivel) {
    if (nivel == 0) {
        strcat(buffer, "Y");
    } else {
        strcat(buffer, "+");
        axiom_x_hilbert(buffer, nivel - 1);
        strcat(buffer, "F");
        strcat(buffer, "-");
        axiom_y_hilbert(buffer, nivel - 1);
        strcat(buffer, "F");
        axiom_y_hilbert(buffer, nivel - 1);
        strcat(buffer, "-");
        strcat(buffer, "F");
        axiom_x_hilbert(buffer, nivel - 1);
        strcat(buffer, "+");
    }
}

// Função que define o axioma X do fractal 6: Preenchimento de espaço de Hilbert
// X → -YF+XFX+FY-
void axiom_x_hilbert (char *buffer, int nivel) {
    if (nivel == 0) {
        strcat(buffer, "X");
    } else {
        strcat(buffer, "-");
        axiom_y_hilbert(buffer, nivel - 1);
        strcat(buffer, "F");
        strcat(buffer, "+");
        axiom_x_hilbert(buffer, nivel - 1);
        strcat(buffer, "F");
        axiom_x_hilbert(buffer, nivel - 1);
        strcat(buffer, "+");
        strcat(buffer, "F");
        axiom_y_hilbert(buffer, nivel - 1);
        strcat(buffer, "-");
    }
}

void axiom_x_julio (char *buffer, int nivel);

// Função que define o axioma Y do fractal 8: original
// Y=XF-YFXFY-FX
void axiom_y_julio (char *buffer, int nivel) {
    if (nivel == 0) {
        strcat(buffer, "Y");
    } else {
        strcat(buffer, "F");
        axiom_x_julio(buffer, nivel - 1);
        strcat(buffer, "F");
        strcat(buffer, "-");
        strcat(buffer, "F");
        strcat(buffer, "F");
        strcat(buffer, "F");
        axiom_y_julio(buffer, nivel - 1);
        strcat(buffer, "F");
        axiom_x_julio(buffer, nivel - 1);
        strcat(buffer, "F");
        axiom_y_julio(buffer, nivel - 1);
        strcat(buffer, "F");
        strcat(buffer, "F");
        strcat(buffer, "F");
        strcat(buffer, "-");
        strcat(buffer, "F");
        axiom_x_julio(buffer, nivel - 1);
        strcat(buffer, "F");
    }
}

// Função que define o axioma X do fractal 8: original
// X=YF+XFYFX+FY
void axiom_x_julio (char *buffer, int nivel) {
    if (nivel == 0) {
        strcat(buffer, "X");
    } else {
        strcat(buffer, "F");
        axiom_y_julio(buffer, nivel - 1);
        strcat(buffer, "F");
        strcat(buffer, "+");
        strcat(buffer, "F");
        strcat(buffer, "F");
        strcat(buffer, "F");
        axiom_x_julio(buffer, nivel - 1);
        strcat(buffer, "F");
        axiom_y_julio(buffer, nivel - 1);
        strcat(buffer, "F");
        axiom_x_julio(buffer, nivel - 1);
        strcat(buffer, "F");
        strcat(buffer, "F");
        strcat(buffer, "F");
        strcat(buffer, "+");
        strcat(buffer, "F");
        axiom_y_julio(buffer, nivel - 1);
        strcat(buffer, "F");
    }
}

// Função que remove os caracteres X e Y antes da gravação no arquivo
void remove_XY(char *buffer) {
    int writer = 0, reader = 0;
    while (buffer[reader])
    {
        if (buffer[reader] != 'X' && buffer[reader] != 'Y') buffer[writer++] = buffer[reader];
        reader++;       
    }
    buffer[writer]=0;
}

// Função que conta os valores de cada algarismo no buffer e salva em um arquivo
void count_carac(char *buffer, FILE *file_count) {
    int count_F = 0, count_X = 0, count_Y = 0, count_plus = 0, count_minus = 0, count_all = 0, reader = 0;
    
    while (buffer[reader])
    {
        if (buffer[reader] == 'F') count_F++;
        if (buffer[reader] == 'X') count_X++;
        if (buffer[reader] == 'Y') count_Y++;
        if (buffer[reader] == '+') count_plus++;
        if (buffer[reader] == '-') count_minus++;
        reader++;       
    }
    
    count_all = count_F+count_X+count_Y+count_plus+count_minus;

    fprintf(file_count, "F: %i\n", count_F);
    fprintf(file_count, "X: %i\n", count_X);
    fprintf(file_count, "Y: %i\n", count_Y);
    fprintf(file_count, "+: %i\n", count_plus);
    fprintf(file_count, "-: %i\n", count_minus);
    fprintf(file_count, "all: %i\n", count_all);
}

int main() {
    int fractal, angulo;
    char axioma[100];
    char regra[10000];

    printf("Insira o numero do fractal (2: Floco de neve de onda quadrada de von Koch; 6: Preenchimento de espaco de Hilbert; 8: Original): ");
    scanf("%d", &fractal);

    printf("Insira o axioma do fractal: ");
    scanf("%s", axioma);

    printf("Insira o angulo em graus: ");
    scanf("%i", &angulo);

    printf("Insira a regra do fractal: ");
    scanf("%s", regra);
    
    // Apenas os fractais indicados nas instruções foram implementados. Caso o fractal solicitado seja diferente, o programa retorna um erro.
    if (fractal != 2 && fractal != 6 && fractal != 8) {
        printf("Número de fractal inválido.");
        return 1;
    }
    
    // Arquivo de texto com os elementos para gerar o fractal solicitado
    FILE *file_F = fopen("fractal.txt", "w");
    if (file_F == NULL) {
        printf("Houve um erro ao abrir o arquivo.\n");
        return 1;
    }
    
    // Arquivo de texto com a contagem dos algarismos do fractal gerado
    FILE *file_count = fopen("fractal_count.txt", "w");
    if (file_count == NULL) {
        printf("Houve um erro ao abrir o arquivo.\n");
        return 1;
    }
    
    for (int i = 1; i < 5; i++) {
        char buffer[100000] = "";
        
        fprintf(file_F, "Estágio %i: ", i);
        fprintf(file_count, "Estágio %i:\n", i);

        if (fractal == 2) recursao_fractal(buffer, i);
        else if (fractal == 6) axiom_x_hilbert(buffer, i);
        else if (fractal == 8) axiom_x_julio(buffer, i);
        
        count_carac(buffer, file_count);
        remove_XY(buffer);
        fprintf(file_F, "%s\n", buffer);
    }

    fclose(file_F);
    fclose(file_count);

    return 0;
}