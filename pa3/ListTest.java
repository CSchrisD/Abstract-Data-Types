//Christina Duran
//crduran
//cmps101
//11/4/14
//Client to test the List functions with object types rather than ints.

import java.io.*;
import java.util.Scanner;

class ListTest{
   public static void main(String args[]) throws IOException{
      List A = new List();
      List B = new List();
      List C = new List();

      System.out.println("insert 10 numbers 0-9");

      for(int i = 0; i<10; i++){
             A.append(i);
             C.append(i);
      }
      A.moveTo(0);

      for(int k = 0; k<10; k++){
             System.out.print(A.getElement() + " ");
             A.moveNext();
      }
      System.out.println();

      B.append("Word 1");
      B.append("Word 2");
      B.append("Word 3");
      B.append("Word 4");
      B.moveTo(0);

      A.append(10);
      A.prepend(-1);
      A.moveTo(0);

      System.out.println("add -1 to the front of the list and 10 to the back");

      for(int j = 0; j<A.length(); j++){
             System.out.print(A.getElement()+ " ");
             A.moveNext();
      }
      System.out.println();

      System.out.println("print string objects");

      for(int w = 0; w<B.length(); w++){
             System.out.print(B.getElement()+ " ");
             B.moveNext();
      }
      System.out.println();

      B.moveTo(B.length()/2);
      B.insertBefore("new word");
      B.insertAfter("newer word");
      B.moveTo(0);

      System.out.println("insert a word before and after cursor node");

      for(int w = 0; w<B.length(); w++){
             System.out.print(B.getElement()+ " ");
             B.moveNext();
      }

      System.out.println();

      A.deleteFront();
      A.deleteBack();
      A.moveTo(0);

      B.moveTo(1);
      B.delete();
      B.moveTo(0);

      System.out.println("delete the front and back of list");

      for(int j = 0; j<A.length(); j++){
             System.out.print(A.getElement()+ " ");
             A.moveNext();
      }

      System.out.println();

      System.out.println("delete cursor node in list");

      for(int w = 0; w<B.length(); w++){
             System.out.print(B.getElement()+ " ");
             B.moveNext();
      }

      System.out.println();

      B.moveTo(0);
      B.delete();
      B.moveTo(B.length()-1);
      B.delete();
      B.moveTo(0);

      System.out.println("using delete() to eliminate front and back");

      for(int w = 0; w<B.length(); w++){
             System.out.print(B.getElement()+ " ");
             B.moveNext();
      }

      System.out.println();
     }
}