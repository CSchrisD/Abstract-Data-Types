//Christina Duran
//crduran
//cmps101
//11/4/14
//uses the Matrix ADT, which utalizes the list ADT, to 
//manipulate matrices taken from a file to find their new values.

import java.io.*;
import java.util.Scanner;

class Sparse{
   public static void main(String[] args) throws IOException{
      Scanner in = null;
      PrintWriter out = null;
      String num = null;
      int i=1, n=0,a=0,b=0,lineNum=1;

      if(args.length < 2){
          System.out.println("Usage: Sparse infile outfile");
          System.exit(1);
      }

      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));

      while(i<=3){
         if(i==1){
            n = in.nextInt();
         }else if(i == 2){
            a = in.nextInt();
         }else if(i == 3){
            b = in.nextInt();
         }
         i++;
       }

       Matrix A = new Matrix(n);
       Matrix B = new Matrix(n);

       in.close();
       in = new Scanner(new File(args[0]));

       while(lineNum<a+b+2){
         int row = in.nextInt();
         int column = in.nextInt();
         double value = in.nextDouble();

         if(lineNum>1 && lineNum<a+2){
           A.changeEntry(row, column,value);
         }else if(lineNum>a+1){
           B.changeEntry(row, column, value);
         }
         lineNum++;
       }

       Matrix C = A.scalarMult(1.5);
       Matrix D = A.add(B);
       Matrix E = A.add(A);
       Matrix F = B.sub(A);
       Matrix G = A.sub(A);
       Matrix H = A.transpose();
       Matrix I = A.mult(B);
       Matrix J = B.mult(B);

       out.println("A has " + A.getNNZ() + " non-zero entries:");
       out.println(A);
       out.println();

       out.println("B has " + B.getNNZ() + " non-zero entries:");
       out.println(B);
       out.println();

       out.println("(1.5)*A=");
       out.println(C);
       out.println();

       out.println("A+B=");
       out.println(D);
       out.println();

       out.println("A+A=");
       out.println(E);
       out.println();

       out.println("B-A=");
       out.println(F);
       out.println();

       out.println("A-A=");
       out.println(G);
       out.println();

       out.println("Transpose(A)");
       out.println(H);
       out.println();

       out.println("A*B=");
       out.println(I);
       out.println();

       out.println("B*B=");
       out.println(J);

       in.close();
       out.close();
   }
}