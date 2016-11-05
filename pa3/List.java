//Christina Duran
//crduran
//cmps101
//11/4/14
//List ADT for holding Indexes of a List and altering them as the user finds appropriate

public class List{
   private class Node{
     Node next;
     Node before;
     Object item;

//Constructor for nodes
     Node(Object x){
       item = x;
       next = null;
       before = null;
     }
   }

//feilds
   private Node front;
   private Node back;
   private Node cursor;
   private int length;
   private int index;

//Constructor for list
   List(){
       front = null;
       back = null;
       cursor = null;
       length = 0;
       index = -1;
   }

//Access functions
//Returns number of elements in this list.
   int length(){
       return length;
   }

//Returns the index of the cursor elemtent in this list, or returns
//-1 if the cursor element is undefined.
   int getIndex(){
        if(this.cursor == null){
           return -1;
        }
        return index;
   }

//Returns front element in this list. Pre: length()>0
    Object front(){
        if(this.length == 0){
            throw new RuntimeException("List Error in front(): List does not contain any elements.");
        }
        return this.front.item;
    }

//Returns back element in this List. Pre: length()>0
    Object back(){
        if(this.length == 0){
            throw new RuntimeException("List Error in back(): List does not contain any elments.");
        }
        return this.back.item;
    }

//Returns cursor element in this list. Pre: length()>0, getIndex()>=0
    Object getElement(){
        if(this.length<=0){
            throw new RuntimeException("List Error in getElement(): List is empty.");
        }if(this.getIndex()<0){
            throw new RuntimeException("List Error in getElement(): Cursor is not pointing at an element");
        }
        return this.cursor.item;
    }

//Returns true if this List and L are the same integer sequence. 
//The cursor is ignored in both lists
    boolean equals(List L){
        boolean start = true;
        Node N = this.front;
        Node Q = L.front;
        if(this.length == L.length){
           while(start && N!=null){
               start = (N.item.equals(Q.item));
               N = N.next;
               Q = Q.next;
           }
           return start;
        }else{
           return false;
        }
     }

//Manipulation procedures

//Re-sets this List to the empty state
     void clear(){
         this.front = null;
         this.back = null;
         this.cursor = null;
         this.length = 0;
         this.index = -1;
     }

//If 0<=i<=length()-1, moves the cursor to the element at 
//index i, otherwise the cursor becomes undefined.
     void moveTo(int i){
         Node N = this.front;
         int j = 0;
         if(0<=i && i<=(this.length)-1){
              while(j != i){
                   j++;
                   N = N.next;
              }
              this.cursor = N;
              this.index = i;
         }else{
              this.cursor = null;
              this.index = -1;
         }
      }

//If 0<getIndex()<=length()-1, moves the cursor one step toward the 
//front of the list. If getIndex()==0, cursor becomes undefined.
//If getIndex()==-1, cursor remains undefined. This operation is
//equivalent to moveTo(getIndex()-1).
      void movePrev(){
          Node N = this.front;
          int j = 0;
          if(0<this.getIndex() && this.getIndex()<= ((this.length)-1)){
               while(j != this.getIndex()){
                      N = N.next;
                      j++;
               }
               this.cursor = N.before;
               this.index = this.index-1;
           }else{
              this.cursor = null;
              this.index = -1;
           }
       }

//If 0<=getIndex()<length()-1, moves the cursor one step toward the 
//back of the list. If getIndex()==length()-1, cursor becomes
//undefined. If index==-1, cursor remains undefined. This
//operation is equivalent to moveTo(getIndex()+1).
       void moveNext(){
           Node N = this.front;
           int j = 0;
           if(0<=this.getIndex() && this.getIndex()<(this.length)-1){
                 while(j != this.getIndex()){
                       N = N.next;
                       j++;
                 }
                 this.cursor = N.next;
                 this.index = this.index + 1;
           }else{
              this.cursor = null;
              this.index = -1;
           }
        }

//Inserts new element before front element in this List.
        void prepend(Object data){
                if(this.front == null){
                        this.front = this.back = new Node(data);
                }else{
                        Node N = this.front;
                        this.front = new Node(data);
                        this.front.next = N;
                        this.front.before = null;
                        N.before = this.front;
                }
                length++;
        }

//Inserts new element after back element in this List.
        void append(Object data){
                 if(this.back == null){
                        this.back = this.front = new Node(data);
                 }else{
                     Node N = this.back;
                     Node T = new Node(data);
                     N.next = T;
                     T.before = N;
                     T.next = null;
                     this.back = T;
                 }
                 length++;
        }

//inserts new element before cursor element in this List. 
//Pre:length()>0, getIndex()>=0
        void insertBefore(Object data){
             Node G = this.cursor.before;
             if(this.length<0){
                    throw new RuntimeException("List Error in insertBefore(): cannot insert on empty list.");
             }if(this.getIndex()<0){
                    throw new RuntimeException("List Error in insertBefore(): cannot insert negative index.");
             }if(G == null){
                    Node N = this.front;
                    Node R = new Node(data);
                    N.before = R;
                    R.next = N;
                    R.before = null;
                    this.front = R;
                    this.index = this.index +1;
             }else{
                    Node N = new Node(data);
                    G.next = N;
                    N.before = G;
                    N.next = this.cursor;
                    this.cursor.before = N;
                    this.index = this.index + 1;
             }
             length++;
         }

//Inserts new element after cursor element in this List.
//Pre: length()>0, getIndex()>=0
         void insertAfter(Object data){
             Node G = this.cursor.next;
             if(this.length<0){
                  throw new RuntimeException("List Error in insertAfter(): cannot insert on empty list.");
             }if( this.getIndex()<0){
                  throw new RuntimeException("List Error in insertAfter(): cannot insert negative index.");
             }if(G == null){
                  Node N = this.back;
                  this.back = new Node(data);
                  this.back.next = null;
                  this.back.before = N;
             }else{
                  Node N = new Node(data);
                  this.cursor.next = N;
                  N.before = this.cursor;
                  N.next = G;
                  G.before = N;
             }
             length++;
          }

//Deletes the front element in this List. Pre:length()>0
          void deleteFront(){
             if(this.length == 0){
                  throw new RuntimeException("List Error: List does not contain any elements.");
             }
             Node N = this.front.next;
             this.front = N;
             N.before = null;
             length--;
             if(this.cursor != null){
                this.index = this.index - 1;
             }
           }

//Deletes the back element in this List. Pre: length()>0
           void deleteBack(){
              if(this.length == 0){
                    throw new RuntimeException("List Error: List does not contain any elements.");
              }
              Node N = this.back.before;
              this.back = N;
              this.back.next = null;
              (this.length)--;
           }

//Deletes cursor element in this List. Curosr is undefined 
//after this operation. Pre: length()>0, getIndex()>=0
           void delete(){
               if(this.length>0 && this.getIndex()>=0){
                  if(this.cursor.before == null){
                      Node N = this.cursor.next;
                      this.front = N;
                      N.before = null;
                      (this.length)--;
                      this.cursor = null;
                      this.index = -1;
                  }else if(this.cursor.next == null){
                      Node G = this.cursor.before;
                      this.back = G;
                      this.back.next = null;
                      this.cursor = null;
                      (this.length)--;
                      this.index = -1;
                  }else{
                      Node N = this.cursor.before;
                      Node G = this.cursor.next;
                      N.next = G;
                      G.before = N;
                      this.cursor = null;
                      (this.length)--;
                      this.index = -1;
                  }
               }
           }

//Other methods

//Overides Object's toString method. Creates a string 
//consisting of a space separated sequence of integers 
//with front on the left and back on the right. The 
//cursor is ignored.
           public String toString(){
                String str = "";
                int i =1;
                for(Node D = this.front; D != null; D=D.next){
                    str = i+": " + D.item.toString()+"\n";
                }
                return str;
           }

//Returns a new list representing the same integer sequence
//as this list. The cursor in the new list is undefined, regardless 
//of the state of the cursor in this List. This List is unchanged.
           List copy(){
                List copyList = new List();
                for( Node N = this.front; N != null; N = N.next){
                     copyList.append(N.item);
                }
                return copyList;
          }
}