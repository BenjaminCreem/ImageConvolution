#include<stdio.h>
#include<stdlib.h>
#include<math.h>

extern int* imageToMat(char* name,int* dims);
extern void matToImage(char* name, int* mat, int* dims);

int main(int argc, char** argv){

    int *mat; //matrix to store image in 
    int *tempmat; //matrix to hold new values for the image in
    int *kernel; //kernel matrix
    char *name="image.jpg"; //image to conv
    int *dims; //dimensions of image
    int k = 1;
    int kw = 2*k+1; //Kernel width = kernel height
    int kernelSize = kw*kw; //size of kernel matrix
    dims=(int*) malloc(sizeof(*dims)*2);
    kernel=(int*) malloc(sizeof(*kernel)*kernelSize); //3x3
    for(int i = 0; i < kernelSize; i++)
    {
        //kerneil[i] = 0;
        //if(i == kernelSize/2)
        //{
            kernel[i] = 1;
        //}
    }

    //printing the kernel matrix
    for(int i = 0; i < kernelSize; i++)
    {
        printf("%d ", kernel[i]);
        if((i+1)%(int)sqrt((double)kernelSize) == 0)
        {
            printf("\n");
        }
    }

    //convert image to matrix
    mat=imageToMat(name,dims);
    //matrix with new image
    tempmat = (int*) malloc(sizeof(*tempmat)*dims[0]*dims[1]);

    printf("Dims: %d %d\n",dims[0],dims[1]);

    //do stuff with the matrix
    //for each pixel
    for(int i = 0; i < dims[0]; i++)
    {
        for(int j = 0; j < dims[1]; j++)
        {
            //Get neighborhood matrix
            //int *local = (int*) malloc(sizeof(*local)*kernelSize);
            //int adjustVal = (int)((0.5*(double)kernelSize)-0.5);
            int sum = 0;
            int product = 0;
            int newVal;
            //Make sure we wont go past the edge of the image
            for(int x=-k; x<= k; x++)
            {
                for(int y=-k; y<=k; y++)
                {
                    if(i-k<0 || j-k<0 || i+k>=dims[1] || j+k>=dims[0])
                    {
                        product = 0;
                    }
                    else
                    {
                        product = kernel[(k+x)*kw+(k+y)] * mat[(i-x)*dims[1]+(j-y)];  
                    }
                    sum += product;
                }
            }
            newVal = sum/kernelSize;
            tempmat[i*dims[1]+j] = newVal;
        }
    }
    matToImage("newImage.jpg",tempmat,dims);
    return 0;
}





