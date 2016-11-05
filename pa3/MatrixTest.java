//Christina Duran
//crduran
//cmps101
//11/4/14
//Client to test the functions of Matrix ADT

class MatrixTest{
   public static void main(String[] args){
         int x = 3;
         Matrix A = new Matrix(x);
         Matrix B = new Matrix(x);

         A.changeEntry(1,1,1);
         A.changeEntry(1,2,2);
         A.changeEntry(1,3,3);
         A.changeEntry(2,1,4);
         A.changeEntry(2,2,5);
         A.changeEntry(2,3,6);
         A.changeEntry(3,1,7);
         A.changeEntry(3,2,8);
         A.changeEntry(3,3,9);

         System.out.println(A.getNNZ());
         System.out.println(A);

         B.changeEntry(1,1,1);
         B.changeEntry(1,2,0);
         B.changeEntry(1,3,1);
         B.changeEntry(2,1,0);
         B.changeEntry(2,2,1);
         B.changeEntry(2,3,0);
         B.changeEntry(3,1,1);
         B.changeEntry(3,2,1);
         B.changeEntry(3,3,1);

         System.out.println(B.getNNZ());
         System.out.println(B);

         //give error message that desired location is out of bounds
         //A.changeEntry(4,2,8);
         //A.changeEntry(2,7,2);

         Matrix C = A.scalarMult(3);
         Matrix D = B.scalarMult(3);

         System.out.println(C.getNNZ());
         System.out.println(C);

         System.out.println(D.getNNZ());
         System.out.println(D);

         Matrix E = A.add(B);

         System.out.println(E.getNNZ());
         System.out.println(E);

         Matrix F = B.sub(A);

         System.out.println(F.getNNZ());
         System.out.println(F);

         Matrix G = A.sub(A);

         System.out.println(G.getNNZ());
         System.out.println(G);

         Matrix H = A.transpose();
         Matrix K = B.transpose();

         System.out.println(H.getNNZ());
         System.out.println(H);
         System.out.println(K);

         Matrix I = A.mult(B);

         System.out.println(I.getNNZ());
         System.out.println(I);

         Matrix J = A.mult(A);

         System.out.println(J.getNNZ());
         System.out.println(J);

         Matrix T = A.copy();
         System.out.println(T.equals(A));
         System.out.println(T.equals(B));
         System.out.println(T);

         Matrix Q = B.copy();
         System.out.println(Q);

         A.makeZero();
         System.out.println(A);
   }
}