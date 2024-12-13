#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

#define kernel_2d_cpy 451

int main(int argc, char *argv[])
{
    int row = 2;
    int column = 2;
    float source_matrix[row][column];
    float destination_matrix[row][column];
    printf("Source Matrix :\n");
    for(int i = 0; i < row; i++){
      for(int j = 0; j < column; j++)
      {source_matrix[i][j] = i*j;
        printf("%f " source_matrix[i][j]);
      }printf("\n");
    }

    if (syscall(kernel_2d_cpy,source_matrix,destination_matrix,row,column) == 0){
      printf("system call returned 0, no error in copying\n");
    }
    else if (syscall(kernel_2d_cpy,source_matrix,destination_matrix,row,column) == -1){
      printf("system call returned -1,error in copying\n");
    }
    printf("Destination Matrix :\n");
    for(int i = 0; i < row; i++){
      for(int j = 0; j < column; j++)
      {printf("%f ",desinationt_Matrix[i][j]);}
      printf("\n");
    }
    return 0;
  }

  