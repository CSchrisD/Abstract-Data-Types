//Christina Duran
//crduran
//cmps101
//10/10/14
//I recived help from Mr.Tantalo during office hours
//Lex alphabetizes an input file and prints the end result

import java.io.*;
import java.util.Scanner;

class Lex{
   public static void main(String args[]) throws IOException{
      Scanner in = null;
      PrintWriter out = null;
      int i, n, lineNumber = 0;
      in = new Scanner(new File(args[0]));
      out = new PrintWriter(new FileWriter(args[1]));
      String curr; //current word
      int k=0;
      List A = new List();
      A.append(0);

      if(args.length < 2){
         System.out.println("error: not enough arguments, file1 file2");
         System.exit(1);
      }

      //read file and count the number of lines
      while(in.hasNextLine()){
           lineNumber++;
           in.nextLine();
      }

      in.close();
      String[] nonAlpha = new String[lineNumber];
      String[] alpha = new String[lineNumber];
      in = new Scanner(new File(args[0]));

      //place strings in unordered array
      while(in.hasNextLine()){
            nonAlpha[k]= in.nextLine();
            k++;
      }

      //reorder List indices to alphabatized ADT
      for(int j=0; j<lineNumber;j++){
         A.moveTo(0);

         while(A.getIndex() != -1){

              if(nonAlpha[j].compareTo(nonAlpha[A.getElement()])<0){
                A.insertBefore(j);
                break;
              }else if(nonAlpha[j].compareTo(nonAlpha[A.getElement()])>0 && A.getIndex() == (A.length()-1)){
                A.append(j);
                break;
              }
              A.moveNext();
         }
       }

       A.moveTo(0);

       //place strings in order
       for(int g = 0; g<lineNumber; g++){
           alpha[g]=nonAlpha[A.getElement()];
           A.moveNext();
       }

       //print alphabatized file
       for(int g = 0; g<alpha.length; g++){
           out.println(alpha[g]);
       }

       in.close();
       out.close();
   }
}