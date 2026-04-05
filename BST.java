public class BST<E> implements Table<E>
{

    private class Node{
        int key;
        E value;
        Node left; 
        Node right;
        public Node(int key, E value){
            this.key=key;
            this.value=value;
        }
    }

    private Node root;
    public BST()
    {
    }

    public void insert(int key, E value)
    {
        Node curr=root;
        boolean found=false;
        if(root==null){
            root=new Node (key,value);
            return;
        }

        while(!found){
            if(key==curr.key){
                curr.value=value;
                found=true;
            }else if(key<curr.key){
                //curr=curr.left;
                if(curr.left==null){
                    curr.left=new Node(key,value);
                    found=true;
                }else{
                    curr=curr.left;
                }
            }else if (key > curr.key){
                //curr=curr.right;
                if(curr.right==null){
                curr.right=new Node(key,value);
                found=true;
                }else{
                curr=curr.right;
                }
            }
        }
    }

   public E search(int key)
    {
        Node curr=root;
        boolean found=false;  
        if(root==null){
            found=true; //check if tree is empty before entering while loop
        }        
        E temp=null; //starts off as null and stays null until key is found      
        while(!found){
            if(key==curr.key){
                temp=curr.value;
                found=true;
            }else if(key<curr.key){
                if(curr.left==null){
                    found=true;
                }else{
                    curr=curr.left;
                }
            }else if (key > curr.key){
                if(curr.right==null){
                found=true;
                }else{
                curr=curr.right;
                }
            }
        }
        return temp;
    }

    public void delete(int key)
    {
        root= deleteHelper(key, root);
    }

    private Node deleteHelper(int key, Node curr){
        if(curr==null){
            return null;
        }

        if(key<curr.key){
            curr.left=deleteHelper(key, curr.left);
        }else if(key>curr.key){
            curr.right=deleteHelper(key, curr.right);
        }else{
            if(curr.left==null && curr.right==null){ //no children
                return null;
            }else if(curr.left==null){ // one child (on right)
                return curr.right;
            }else if(curr.right==null){ // one child (on left)
                return curr.left;
            }else{
                Node replace= successor(curr.right);
                curr.key=replace.key;
                curr.value=replace.value;
                curr.right=deleteHelper(replace.key, curr.right);
            }
        }
        return curr;
    }

    private Node successor(Node node){
        while(node.left!=null){
            node=node.left;
        }
        return node;
    }


    public void print()
    {
        printRecursive(root, 0);
    }

    private void printRecursive(Node curr, int currDepth){
        if(curr==null){
            return;
        }

        printRecursive(curr.left, currDepth+1);

        for (int i = 0; i < currDepth; i++) {
            System.out.print("    ");  // 4 spaces
        }
        System.out.println(curr.key);
        printRecursive(curr.right, currDepth+1);
    }
}