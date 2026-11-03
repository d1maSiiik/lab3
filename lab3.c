#include <stdio.h>
#include <stdlib.h>

int is_natural_string(const char *str) {
    if (str[0] == '\0' || str[0] == '0' || str[0] == '-') {
        return 0;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }

    return 1;
}

int is_float_string(const char *str) {
    int start = 0;

    if (str[0] == '-' || str[0] == '+') {
        start++;
    }

    if (str[start] == '\0') {
        return 0;
    }

    int dot_count = 0;
    int digit_count = 0;

    for (int i = start; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            dot_count++;

            if (dot_count > 1) {
                return 0;
            }
        } else if (str[i] >= '0' && str[i] <= '9') {
            digit_count++;
        } else {
            return 0;
        }
    }

    if (digit_count == 0) {
        return 0;
    }

    return 1;
}

int main() {
    char *N_str = NULL;
    char *M_str = NULL;

    int N, M;
    int found = 0;
    float S = 0;
    float max;

    // Ввод количества строк N
    while (1) {
        printf("Введите N (не менее 4): ");

        if (scanf("%ms", &N_str) != 1) {
            printf("Ошибка чтения.\n");
            free(N_str);
            N_str = NULL;
            continue;
        }

        if (is_natural_string(N_str)) {
            N = atoi(N_str);
            free(N_str);
            N_str = NULL;

            if (N >= 4) {
                break;
            } else {
                printf("Количество строк должно быть не менее 4!\n");
            }
        } else {
            printf("Число должно быть натуральным!\n");
            free(N_str);
            N_str = NULL;
        }
    }

    // Ввод количества столбцов M
    while (1) {
        printf("Введите M: ");

        if (scanf("%ms", &M_str) != 1) {
            printf("Ошибка чтения.\n");
            free(M_str);
            M_str = NULL;
            continue;
        }

        if (is_natural_string(M_str)) {
            M = atoi(M_str);
            free(M_str);
            M_str = NULL;
            break;
        } else {
            printf("Число должно быть натуральным!\n");
            free(M_str);
            M_str = NULL;
        }
    }

    // Выделение памяти под матрицу
    float *Matrix = malloc(N * M * sizeof(*Matrix));

    if (Matrix == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    // Ввод элементов матрицы
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char *element = NULL;
            float value;

            while (1) {
                printf("Введите элемент [%d][%d]: ", i, j);

                if (scanf("%ms", &element) != 1) {
                    printf("Ошибка чтения.\n");
                    free(element);
                    element = NULL;
                    continue;
                }

                if (is_float_string(element)) {
                    value = atof(element);
                    free(element);
                    element = NULL;
                    break;
                } else {
                    printf("Некорректный ввод!\n");
                    free(element);
                    element = NULL;
                }
            }

            Matrix[i * M + j] = value;
        }
    }

    // Вывод исходной матрицы
    printf("\nИсходная матрица:\n");

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("| %8.2f |", Matrix[i * M + j]);
        }
        printf("\n");
    }

    // 1. Сумма положительных элементов над главной диагональю
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < M; j++) {
            if (Matrix[i * M + j] > 0) {
                S += Matrix[i * M + j];
            }
        }
    }

    printf("\nСумма положительных элементов над главной диагональю: %.2f\n", S);

    // 2. Поиск максимального отрицательного элемента 4-й строки
    for (int j = 0; j < M; j++) {
        float value = Matrix[3 * M + j];

        if (value < 0) {
            if (found == 0 || value > max) {
                max = value;
                found = 1;
            }
        }
    }

    // 3. Замена найденного элемента на сумму S
    if (found == 1) {
        printf("Максимальный отрицательный элемент 4-й строки: %.2f\n", max);

        for (int j = 0; j < M; j++) {
            if (Matrix[3 * M + j] == max) {
                Matrix[3 * M + j] = S;
                break;
            }
        }

        printf("\nМатрица после замены:\n");

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                printf("| %8.2f |", Matrix[i * M + j]);
            }
            printf("\n");
        }
    } else {
        printf("В 4-й строке нет отрицательных элементов.\n");
    }

    // Освобождение памяти
    free(Matrix);

    return 0;
}
