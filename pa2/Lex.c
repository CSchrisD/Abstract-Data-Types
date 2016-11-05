//Christina Duran
//crduran
//cmps101
//10/17/14
//Uses List.c to order files in alphebetical order

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){
   List A = newList();
   int g=0, count=0;
   FILE *in, *out;
   char line[MAX_LEN];
   char* token;
   append(A,0);

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");

   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   /* read each line of input file, then count*/
   while( fgets(line, MAX_LEN, in) != NULL)  {
      count++;
   }

   char** nonAlpha = calloc(count, sizeof(char)*100);
   char** alpha = calloc(count, sizeof(char)*100);

   fclose(in);
   in = fopen(argv[1], "r");

   while( fgets(line, MAX_LEN, in) != NULL)  {
       token = strtok(line, " \n");
       nonAlpha[g]= malloc(sizeof(char)*100);
       strcpy(nonAlpha[g],token);
       g++;
 }

 for(int w = 0; w<count; w++){
       moveTo(A,0);
       while(getIndex(A) >= 0){
           if(strcmp(nonAlpha[w],nonAlpha[getElement(A)])<0){
                   insertBefore(A,w);
                   break;
            }else if((strcmp(nonAlpha[w],nonAlpha[getElement(A)])>0) && (getIndex(A)==length(A)-1)){
                   append(A,w);
                   break;
            }
            moveNext(A);
        }
    }

    moveTo(A,0);

   for(int k = 0; k<count; k++){
      alpha[k] = nonAlpha[getElement(A)];
       moveNext(A);
   }

   for(int q=0; q<count; q++){
      fprintf(out,"%s\n", alpha[q]);
   }
  for(int v =0; v<count;v++){
   free(&nonAlpha[v]);
   }
   free(&nonAlpha);
   free(&alpha);
   freeList(&A);
   fclose(in);
   fclose(out);

   return(0);
}