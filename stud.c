#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "run.c"

int main(){
    printf("Choose the way to input matrix:\n1)File\n2)Keyboard\n3)Random\nInput the number: ");
    int var, var0;
    scanf("%d", &var);

    if (var < 1 || var > 3){
        printf("Incorrect number\n");
        return 0;
    }

    printf("Choose the way to output matrix:\n1)File\n2)Console\nInput the number: ");
    int var1;
    scanf("%d", &var1);

    if (var1 < 1 || var1 > 2){
        printf("Incorrect number\n");
        return 0;
    }


    int first_row, first_col;
    printf("Input first matrix row count: ");
    scanf("%d", &first_row);
    printf("\n");

    printf("Input first matrix column count: ");
    scanf("%d", &first_col);
    printf("\n");

    int **first_mat = allocate_2d_array(first_row, first_col);


    int second_row, second_col;

    printf("Input second matrix row count: ");
    scanf("%d", &second_row);
    printf("\n");

    printf("Input second matrix colum count: ");
    scanf("%d", &second_col);
    printf("\n");

    int **second_mat = allocate_2d_array(second_row, second_col);

    if (var == 1){
        printf("Input first file name: ");
        char filename[100];
        scanf("%s", filename);

        readMatrixFromFile(filename, first_row, first_col, first_mat);
        print_matrix(first_mat, first_col, first_row);


        printf("Input second file name: ");
        char filename1[100];
        scanf("%s", filename1);

        readMatrixFromFile(filename1, second_row, second_col, second_mat);
        print_matrix(second_mat, second_col, second_row);
    }

    
    if (var == 2){
        printf("Input elements of first matrix\n");
        scan_matrix(first_mat, first_row, first_col);

        printf("Input elements of second matrix\n");
        scan_matrix(second_mat, second_row, second_col);
    }

    if (var == 3){
        srand(time(NULL));

        input_random(first_mat, first_row, first_col);


        input_random(second_mat, second_row, second_col);
    }

    if (first_col != second_row){
        printf("Impossible to do");
        return 0;
    }

    int **result = allocate_2d_array(first_col, second_row);

    clock_t start = clock();

    
    for (int i = 0; i < first_col; i++){
        for (int j = 0; j < second_row; j++){
            for (int k = 0; k < first_col; k++){
                result[i][j] = 0;
                result[i][j] += first_mat[i][k] * second_mat[k][j];
                }
        }
    }

    clock_t finish = clock();
    double timee = (double)(finish - start) / CLOCKS_PER_SEC;


    if (var1 == 2){
        printf("Final matrix\n");
        print_matrix(result, first_col, second_row);
    }

    if (var1 == 1){
        FILE * file = fopen("output.txt", "w");
        for (int i = 0; i < first_col; i++){
            for (int j = 0; j < second_row; j++){
                fprintf(file, "%d ", result[i][j]);
            }
            fprintf(file, "\n");
        }
    }

    printf("Transpose matrix?\n1)Yes\n2)No\nInput the number: ");
    int var2;
    scanf("%d", &var2);

    if (var2 == 1){
        if (var1 == 2){
            printf("Transposed matrix\n");
        for (int i = 0; i < first_col; i++){
                for (int j = 0; j < second_row; j++){
                    printf("%d ", result[j][i]);
                }
                printf("\n");
            }
        }
    }
    free_2d_array(first_mat, first_row);
    free_2d_array(second_mat, second_row);
    free_2d_array(result, second_row);
    printf("%f", timee);

}