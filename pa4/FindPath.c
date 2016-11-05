//Christina Duran
//crduran
//cmps101
//11/20/14
//client that uses Graph.c/List.c to make a graph based on infile and prints in outfile
//the adjacent edges of each vertex, and finds the paths between 2 desired vertecies
//if such a path exists.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

int main(int argc, char * argv[]){
   int k,g,h,j,a,b;
   FILE *in, *out;

// check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

//Open files for reading and writing 
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

   if(fscanf(in,"%d", &g) != EOF){
      k = g;
   }

   Graph A = newGraph(k);

   while(fscanf(in,"%d %d",&h,&j) != EOF){
        if(h != 0 && j!=0){
           addEdge(A,h,j);
        }else{
           break;
        }
   }

   printGraph(out,A);
   fprintf(out,"\n");

   while(fscanf(in,"%d %d",&a,&b) != EOF){
         List L = newList();
        if(a != 0 && b!=0){
            BFS(A,a);
            int dis = getDist(A,b);
            if(dis == -2){
               fprintf(out,"The distance from %d to %d is infinity\n",a,b);
               fprintf(out,"No %d-%d path exists\n",a,b);
               fprintf(out,"\n");
            }else{
               getPath(L,A,b);
               fprintf(out,"The distance from %d to %d is %d\n",a,b,dis);
               fprintf(out,"A shortest %d-%d path is: ",a,b);
               printList(out,L);
               fprintf(out,"\n\n");
            }
        }else{
          break;
        }
        freeList(&L);
   }
   freeGraph(&A);
   fclose(in);
   fclose(out);
   return(0);
}