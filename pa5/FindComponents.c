//Christina Duran
//crduran
//cmps101
//12/08/14

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Graph.h"

int main(int argc, char * argv[]){
   int k,g,h,j,a,b,z=0,connectNum=0,compNum=1;
   FILE *in, *out;
   List H = NULL;
   List S = newList(); // list that will contain a node for each vertex
   Graph A = NULL;
   Graph B = NULL;

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

   A = newGraph(k);  // new directed graph with k vertecies

   //go through the in file and add directed edges from the first
   //to second number until terminated by dummby variable
   while(fscanf(in,"%d %d",&h,&j) != EOF){
        if(h != 0 && j!=0){
           addArc(A,h,j);
        }else{
           break;
        }
   }

   //add all nodes to list S
   for(int i = 1; i<=getOrder(A);i++){
        append(S,i);
   }

   B = transpose(A); //transposed graph of A to calculate Strongly Connected Components later

   DFS(A,S); //runs DFS on Graph A changing list S into a list of vertecies by decending finish times

   H = copyList(S); //keeps original decending list for use of order later

   DFS(B,S);   //runs DFS on transposed graph with decending list

   fprintf(out,"Adjacency list representation of G:\n");
   printGraph(out,A);

   //find the number of Strongly Connected components
   for(int i=1; i<=getOrder(B);i++){
      if(getParent(B,i) == -10){
        connectNum++;
      }
   }

   fprintf(out,"\n");
   fprintf(out,"G contains %d strongly connected components: \n", connectNum);

  //print Components in order
   moveTo(H,z);
   while(z<length(H) && compNum<=connectNum){
      int element = getElement(H);
      if(getParent(B,element) == -10){
         int index = 0;
         moveTo(S,index);
         a = getElement(S);
         while(index<length(S) && a!=element){
           index++;
           moveNext(S);
           a = getElement(S);
         }
         fprintf(out,"Component %d: %d ",compNum,element);
         index++;
         if(index<length(S)){
            moveNext(S);
            b = getElement(S);
         }
         while(index<length(S) && getParent(B,b) != -10){
           fprintf(out,"%d ",b);
           index++;
           if(index<length(S)){
              moveNext(S);
              b = getElement(S);
           }
         }
         fprintf(out,"\n");
         compNum++;
      }
      z++;
      moveNext(H);
   }


   freeGraph(&A);
   freeGraph(&B);
   freeList(&S);
   freeList(&H);
   fclose(in);
   fclose(out);

   return(0);
}