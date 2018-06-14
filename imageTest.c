#include<stdio.h>
#include<stdlib.h>
#include<math.h>

extern int* imageToMat(char* name,int* dims);
extern void matToImage(char* name, int* mat, int* dims);

int main(int argc, char** argv){

    int *mat;
    int *tempmat;
    int *kernel;
    char *name="image.jpg";
    int *dims;
    int kernelSize = 9;
    dims=(int*) malloc(sizeof(*dims)*2);
    kernel=(int*) malloc(sizeof(*kernel)*kernelSize); //3x3
    for(int i = 0; i < 9; i++)
    {
        kernel[i] = 0;
    }
    kernel[4] = 1;

    for(int i = 0; i < kernelSize; i++)
    {
        printf("%d ", kernel[i]);
    }

    mat=imageToMat(name,dims);
    tempmat = (int*) malloc(sizeof(*tempmat)*dims[0]*dims[1]);
    for(int i = 0; i < dims[0]*dims[1]; i++)
    {
        tempmat[i] = mat[i];
    }

    printf("Dims: %d %d\n",dims[0],dims[1]);

    //do stuff with the matrix
    

    //for each pixel
    for(int i = 0; i < dims[0]*dims[1]; i++)
    {
        //Get neighborhood matrix
        int *local = (int*) malloc(sizeof(*local)*kernelSize);

        //if(i <= dims[0] || i%dims[1] == 0 || i%(dims[1]-1) == 0 || i > dims[0]*dims[1] -dims[0])
        //{
         //   tempmat[i] = 0;
        //}
        //else
        //{
        //for(int j = 0; j <= kernelSize; j++)
        //{
            //if(j >= 0 && j <= 2)
            //{
                //for(int k = -1; k <= 1; k++)
                //{
                //    local[j] = mat[i-dims[0]+k];
              //  }
            //}
            //if(j >= 3 && j <= 5)
            //{
                //for(int k = -1; k <= 1; k++)
                //{
                //    local[j] = mat[i+k];
              //  }
            //}
            //else
            //{
                //for(int k = -1; k <= 1; k++)
                //{
                //    local[j] = mat[i+dims[0]+k];
              //  }
           // }
        //}



        //Multiply by kernel
        int *result = (int*) malloc(sizeof(*result)*kernelSize);
        for(int j = 0; j < kernelSize; j++)
        {
            result[j] = 0;
            for(int k = 0; k < kernelSize; k++)
            {
                result[j] += kernel[j]*local[k];
            }
        }
        
        //Sum all values in result of multiplication
        int sum = 0;
        for(int j = 0; j < kernelSize; j++)
        {
            sum += result[j];
        }
        
        //Divide by size of kernel
        sum = sum / kernelSize;

        //Set as new pixel 
        tempmat[i] = sum;
        }
    }

    matToImage("newImage.jpg",tempmat,dims);

    return 0;
}





