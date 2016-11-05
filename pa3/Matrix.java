//Christina Duran
//crduran
//cmps101
//11/4/14
//Matrix ADT to create and mathematicaly manipulate matricies

class Matrix{

//private class Entry to hold coulmn information

   private class Entry{
      double value;
      int column;

      Entry(int x , double y){
         value = y;  // value of thing in "column" or index of the list
         column = x; // index of the list
      }

      public boolean equals(Entry Q){
        return Q.value == this.value && Q.column == this.column;
      }

     public String toString(){
        return ("("+this.column+", " +this.value+")");
      }
   }

//Constructor

//feilds
   private List[] row;
   private int size;
   private int nonZeroInts;

//Makes a new nxn zero Matrix. pre: n>=1
   Matrix(int n){
       if( n<1 ){
           throw new RuntimeException("Matrix Error in Matrix(): insufficiant Matrix size.");
       }
       row  = new List[n+1];
       size = n;
       nonZeroInts = 0;

       for(int i = 1; i<=n; i++){
          row[i] = new List();
       }
   }

//Access functions

//Returns n, the number of rows and columns of this Matrix
   int getSize(){
        return size;
   }

//Retruns the number of non-zero entries in this Matrix
   int getNNZ(){
      return  nonZeroInts;
   }

//overrides Object's equals() method
   public boolean equals(Object x){
       boolean start = true;
       Matrix comp = (Matrix)x;
       int i = 1;
       int j = 0;
       if(this.getSize() == comp.getSize()){
         while(i<=this.size){
           if(this.row[i].length() == comp.row[i].length()){
            while(start && j<this.row[i].length()){
              this.row[i].moveTo(j);
              comp.row[i].moveTo(j);
              Entry curr = (Entry)this.row[i].getElement();
              Entry entComp = (Entry)comp.row[i].getElement();
              if(curr.equals(entComp)){
                 start = true;
              }else{
                 start = false;
              }
              j++;
            }
           }else{
             return false;
           }
            i++;
          }
       }else{
         return false;
       }
       return start;
    }

//Manipulation procedures

//sets this Matrix to the zero state
   void makeZero(){
        for(int i = 1; i<=this.size; i++){
            row[i].clear();
        }
        size = 0;
        nonZeroInts = 0;
   }

//returns a new Matrix having the same entries as this Matrix
   Matrix copy(){
       Matrix G = new Matrix(this.size);

       for(int i = 1; i<=this.size; i++){
          for(int j=0; j<this.row[i].length();j++){
            this.row[i].moveTo(j);
            Entry curr = (Entry)this.row[i].getElement();
            G.changeEntry(i,curr.column,curr.value);
          }
      }
      return G;
   }

//changes ith row, jth column of this Matrix to x
//pre: 1<=i<= getSize(), 1<=j<=getSize()
   void changeEntry(int i, int j, double x){
        int k = 0;
        if(i<1){
            throw new RuntimeException("Matrix Error in changeEntry(): negative row input.");
        }if(i>this.getSize()){
            throw new RuntimeException("Matrix Error in changeEntry(): row input is too large.");
        }if(j<1){
            throw new RuntimeException("Matrix Error in changeEntry(): negative column input.");
        }if(j>this.getSize()){
            throw new RuntimeException("Matrix Error in changeEntry(): column input is too large.");
        }

       Entry change = new Entry(j,x);

         if(this.row[i].length() == 0){
           if(change.value != 0.0){
              this.row[i].append(change);
              this.nonZeroInts++;
           }
          }else if(this.row[i].length()>0){
           this.row[i].moveTo(0);
           while(k<this.row[i].length()){
               Entry comp = (Entry)this.row[i].getElement();
               if(change.value == 0.0){
                    break;
               }if(comp.column == change.column){
                   if(comp.value!=0.0 &&change.value!=0.0){
                        this.row[i].insertBefore(change);
                        this.row[i].delete();
                   }if(comp.value ==0.0 &&  change.value ==0.0){
                        break;
                   }
                   break;
               }if(k == this.row[i].length()-1 && comp.column < change.column){
                   this.row[i].append(change);
                   this.nonZeroInts++;
                   break;
               }if(k == 0 && change.column < comp.column){
                   this.row[i].prepend(change);
                   this.nonZeroInts++;
                   break;
               }if(change.column < comp.column){
                   this.row[i].insertBefore(change);
                   this.nonZeroInts++;
                   break;
               }
               this.row[i].moveNext();
               k++;
           }
        }
   }

//returns a new Matrix that is the scalar product of this Matrix with x
  Matrix scalarMult(double x){
        Matrix G = new Matrix(this.size);
        for(int i = 1; i<=this.size; i++){
          for(int j = 0; j<this.row[i].length(); j++){
              this.row[i].moveTo(j);
              Entry thisMat =(Entry)this.row[i].getElement();
              G.changeEntry(i,thisMat.column,(x)*(thisMat.value));
         }
        }
        return G;
  }

//returns a new Matrix that is the difference of this Matrix with M
//pre: getSize() == M.getSize()
   Matrix add(Matrix M){
        Matrix G = new Matrix(this.size);
        if(this.size != M.size){
           throw new RuntimeException("Matrix Error in add(): Matrices are not the same size.");
       }
       for(int i = 1; i<=this.size; i++){
           int j=0,k=0;
        if(this.row[i].length() ==0 && M.row[i].length()>0){
          while(k<M.row[i].length()){
                  M.row[i].moveTo(k);
                  Entry thing =(Entry)M.row[i].getElement();
                  G.changeEntry(i,thing.column,thing.value);
                  k++;
         }
        }else if(this.row[i].length()>0 && M.row[i].length()==0){
          while(j<this.row[i].length()){
                         this.row[i].moveTo(j);
                         Entry thisMat =(Entry)this.row[i].getElement();
                         G.changeEntry(i,thisMat.column,thisMat.value);
                         j++;
          }
         }else if(this.row[i].length()!=0 && M.row[i].length()!=0){
           if(this.row[i].length() > M.row[i].length()){
             while(k<M.row[i].length() && j<this.row[i].length()){
                this.row[i].moveTo(j);
                M.row[i].moveTo(k);
                Entry thisMat =(Entry)this.row[i].getElement();
                Entry MMat =(Entry)M.row[i].getElement();
                if(thisMat.column == MMat.column){
                    G.changeEntry(i,thisMat.column, thisMat.value+MMat.value);
                    j++;
                    k++;
                }else if(thisMat.column < MMat.column){
                    G.changeEntry(i,thisMat.column, thisMat.value);
                    j++;
                }else if(thisMat.column>MMat.column){
                    G.changeEntry(i,MMat.column,MMat.value);
                    k++;
                }
              }
              while(j<this.row[i].length()){
                  this.row[i].moveTo(j);
                  Entry thisMat =(Entry)this.row[i].getElement();
                  G.changeEntry(i,thisMat.column,thisMat.value);
                  j++;
             }
        }else if(this.row[i].length() == M.row[i].length()){
              while(k<M.row[i].length() && j<this.row[i].length()){
                this.row[i].moveTo(j);
                M.row[i].moveTo(k);
                Entry thisMat =(Entry)this.row[i].getElement();
                Entry MMat =(Entry)M.row[i].getElement();
                if(thisMat.column == MMat.column){
                    G.changeEntry(i,thisMat.column, thisMat.value+MMat.value);
                    j++;
                    k++;
                }else if(thisMat.column < MMat.column){
                    G.changeEntry(i,thisMat.column, thisMat.value);
                    j++;
                }else if(thisMat.column> MMat.column){
                    G.changeEntry(i,MMat.column,MMat.value);
                    k++;
                }
               }if(k<M.row[i].length()){
                    while(k<M.row[i].length()){
                         M.row[i].moveTo(k);
                         Entry MMat =(Entry)M.row[i].getElement();
                         G.changeEntry(i,MMat.column,MMat.value);
                         k++;
                    }
               }else if(j<this.row[i].length()){
                   while(j<this.row[i].length()){
                         this.row[i].moveTo(j);
                         Entry thisMat =(Entry)this.row[i].getElement();
                         G.changeEntry(i,thisMat.column,thisMat.value);
                         j++;
                   }
               }
         }else if(this.row[i].length()< M.row[i].length()){
                while(j<this.row[i].length() && k<M.row[i].length()){
                this.row[i].moveTo(j);
                M.row[i].moveTo(k);
                Entry thisMat =(Entry)this.row[i].getElement();
                Entry MMat =(Entry)M.row[i].getElement();
                if(thisMat.column == MMat.column){
                    G.changeEntry(i,thisMat.column, thisMat.value+MMat.value);
                    j++;
                    k++;
                }else if(thisMat.column < MMat.column){
                    G.changeEntry(i,thisMat.column, thisMat.value);
                    j++;
                }else{
                    G.changeEntry(i,MMat.column,MMat.value);
                    k++;
                }
             }
             while(k<M.row[i].length()){
                  M.row[i].moveTo(k);
                  Entry thing =(Entry)M.row[i].getElement();
                  G.changeEntry(i,thing.column,thing.value);
                  k++;
             }
          }
        }
       }
 return G;
}

//returns a new Matrix that is the difference of this Matrix with M
//pre: getSize() == M.getSize()
   Matrix sub(Matrix M){
        Matrix G = new Matrix(this.size);
        if(this.size != M.size){
           throw new RuntimeException("Matrix Error in sub(): Matrices are not the same size.");
       }
       for(int i = 1; i<=this.size; i++){
           int j=0,k=0;
           if(this.row[i].length()==0 && M.row[i].length()>0){
                 while(k<M.row[i].length()){
                       M.row[i].moveTo(k);
                       Entry thing = (Entry)M.row[i].getElement();
                       G.changeEntry(i,thing.column,0.0-thing.value);
                       k++;
                 }
            }else if(this.row[i].length()>0 && M.row[i].length()==0){
                   while(j<this.row[i].length()){
                         this.row[i].moveTo(j);
                         Entry thisMat =(Entry)this.row[i].getElement();
                         G.changeEntry(i,thisMat.column,thisMat.value);
                         j++;
                   }
             }else if(this.row[i].length()!=0 && M.row[i].length()!=0){
               if(this.row[i].length() > M.row[i].length()){
                   while(k<M.row[i].length() && j<this.row[i].length()){
                      this.row[i].moveTo(j);
                       M.row[i].moveTo(k);
                       Entry thisMat =(Entry)this.row[i].getElement();
                       Entry MMat =(Entry)M.row[i].getElement();
                       if(thisMat.column == MMat.column){
                             G.changeEntry(i,thisMat.column, thisMat.value-MMat.value);
                             j++;
                             k++;
                       }else if(thisMat.column < MMat.column){
                             G.changeEntry(i,thisMat.column, thisMat.value);
                             j++;
                       }else if(thisMat.column> MMat.column){
                             G.changeEntry(i,MMat.column,0.0-MMat.value);
                             k++;
                       }
                     }
                     while(j<this.row[i].length()){
                        this.row[i].moveTo(j);
                        Entry thing =(Entry)this.row[i].getElement();
                        G.changeEntry(i,thing.column,thing.value);
                        j++;
                     }
                }else if(this.row[i].length() == M.row[i].length()){
                  while(k<M.row[i].length() && j<this.row[i].length()){
                     this.row[i].moveTo(j);
                     M.row[i].moveTo(k);
                     Entry thisMat =(Entry)this.row[i].getElement();
                     Entry MMat =(Entry)M.row[i].getElement();
                     if(thisMat.column == MMat.column){
                        G.changeEntry(i,thisMat.column, thisMat.value-MMat.value);
                        j++;
                        k++;
                      }else if(thisMat.column < MMat.column){
                        G.changeEntry(i,thisMat.column, thisMat.value);
                        j++;
                      }else if(thisMat.column> MMat.column){
                        G.changeEntry(i,MMat.column,0.0-MMat.value);
                        k++;
                      }
                   }if(k<M.row[i].length()){
                    while(k<M.row[i].length()){
                         M.row[i].moveTo(k);
                         Entry MMat =(Entry)M.row[i].getElement();
                         G.changeEntry(i,MMat.column,0.0-MMat.value);
                         k++;
                    }
               }else if(j<this.row[i].length()){
                   while(j<this.row[i].length()){
                         this.row[i].moveTo(j);
                         Entry thisMat =(Entry)this.row[i].getElement();
                         G.changeEntry(i,thisMat.column,thisMat.value);
                         j++;
                   }
               }
             }else if(this.row[i].length() < M.row[i].length()){
                    while(j<this.row[i].length() && k<M.row[i].length()){
                        this.row[i].moveTo(j);
                        M.row[i].moveTo(k);
                        Entry thisMat =(Entry)this.row[i].getElement();
                        Entry MMat =(Entry)M.row[i].getElement();
                        if(thisMat.column == MMat.column){
                              G.changeEntry(i,thisMat.column, thisMat.value-MMat.value);
                              j++;
                              k++;
                }else if(thisMat.column < MMat.column){
                    G.changeEntry(i,thisMat.column, thisMat.value);
                    j++;
                }else{
                    G.changeEntry(i,MMat.column,0.0-MMat.value);
                    k++;
                }
             }
             while(k<M.row[i].length()){
                  M.row[i].moveTo(k);
                  Entry thing =(Entry)M.row[i].getElement();
                  G.changeEntry(i,thing.column,0.0-thing.value);
                  k++;
             }
          }
        }
      }
      return G;
}

//returns a new Matrix that is the transpose of this Matrix
   Matrix transpose(){
       Matrix G = new Matrix(this.size);
       for(int i = 1; i<=this.size; i++){
           for(int j = 0; j<this.row[i].length(); j++){
                this.row[i].moveTo(j);
                Entry trans = (Entry)this.row[i].getElement();
                G.changeEntry(trans.column,i,trans.value);
           }
       }
       return G;
   }

//returns a new Matrix that is the product of this Matrix with M
//pre: getSize() == M.getSize()
   Matrix mult(Matrix M){
       Matrix G = new Matrix(this.size);
       Matrix H = M.transpose();
       if(this.size != M.size){
           throw new RuntimeException("Matrix Error in mult(): Matrices are not the same size.");
       }
       int i =1;
       while(i<=this.size){
           int j=0,k=0,g=1;
              while(g<=H.getSize()){
                  G.changeEntry(i,g,dot(this.row[i],H.row[g]));
              g++;
             }
             i++;
        }
       return G;
}

//Other functions

//helper function to find the total for a row and column in a list
        public static double dot(List P, List Q){
               double total= 0.0;
               int j=0,k=0;
               if(P.length() == 0 || Q.length()==0){
                   return 0.0;
               }
               while(j<P.length() && k<Q.length()){
                    P.moveTo(j);
                    Q.moveTo(k);
                    Entry Pitem = (Entry)P.getElement();
                    Entry Qitem = (Entry)Q.getElement();
                    if(Pitem.column == Qitem.column){
                       total = total + (Pitem.value *Qitem.value);
                       j++;
                       k++;
                    }else if(Pitem.column < Qitem.column){
                       j++;
                    }else if(Pitem.column > Qitem.column){
                       k++;
                    }
               }
               return total;
           }

//overrides Object's toString method
   public String toString(){
      String str = "";
      if(this.getNNZ()== 0){
          return str;
      }
      for(int i = 1; i<=this.size; i++){
         String thing = "";
         for(int j=0;j<this.row[i].length();j++){
            this.row[i].moveTo(j);
            thing = thing + " " + this.row[i].getElement().toString();
         }if(this.row[i].length() > 0){
           str = str + i+":"+ thing + "\n";
         }
       }
       return str;
     }
}