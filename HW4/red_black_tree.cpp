#include "red_black_tree.h"
#include<iomanip> 
#include <iostream>



Node::Node()
{
    left = nullptr;
    right = nullptr;
    parent = nullptr;
    color = RED;
}


/*Nodes in a red - black tree also have a link to the parent.
When adding or moving a node, 
it is important that the parent and child links are synchronized.
Because this synchronization is tedious and error-prone,
we provide several helper functions:
set_left_child, set_right_child,replace_with
*/
void Node::set_left_child(Node* child)
{
    left = child;
    if (child != nullptr) { child->parent = this; }
}

void Node::set_right_child(Node* child)
{
    right = child;
    if (child != nullptr) { child->parent = this; }
}

void RedBlackTree::replace_with(Node* to_be_replaced, Node* replacement)
{
    if (to_be_replaced->parent == nullptr)
    {
        replacement->parent = nullptr;
        root = replacement;
    }
    else if (to_be_replaced == to_be_replaced->parent->left)
    {
        to_be_replaced->parent->set_left_child(replacement);
    }
    else
    {
        to_be_replaced->parent->set_right_child(replacement);
    }
}


RedBlackTree::RedBlackTree()
{
    root = nullptr;
}

//copy constructor
RedBlackTree::RedBlackTree(const RedBlackTree& other){
    root = copy(other.root);
}

//helper function
Node* RedBlackTree::copy(Node* n){
    if (n == nullptr){
        return nullptr;
    }
    
    if ((n->left == nullptr) && (n->right==nullptr)){
        Node* newNode = new Node;
        newNode->data = n->data;
        newNode->color = n->color;
        newNode->parent = n->parent;
        return newNode;
        
    }
    else {
        Node* mom = new Node;
        mom->data = n->data;
        mom->color = n->color;
        mom->parent = n->parent;
        mom->left = copy(n->left);
        mom->right = copy(n->right);
        return mom;
    }
}

//copy assignment
RedBlackTree& RedBlackTree::operator=(const RedBlackTree& other){
    this->~RedBlackTree();
    root = copy(other.root);
    return *this;
}

RedBlackTree::~RedBlackTree(){
    DESTROY(root);
    root = nullptr;
}

void RedBlackTree::DESTROY(Node* curr){
    if (curr != nullptr){
        if ((curr->left == nullptr)&&(curr->right == nullptr)){
            delete curr;
            curr = nullptr;
        }
        else {
            DESTROY(curr->left);
            DESTROY(curr->right);
        }
    }
}

/*Insertion is handled as it is in a binary search tree.
We insert a red node. Afterward, we call a function that
fixes up the tree so it is a red-black tree again:
*/
void RedBlackTree::insert(std::string element)
{
    if (count(element)){return;}
    Node* new_node = new Node;
    new_node->data = element;
    new_node->left = nullptr;
    new_node->right = nullptr;
    if (root == nullptr) {
        root = new_node;
        root->color = BLACK;
        root->parent = nullptr;
    }
    else {
        new_node->color = RED;
        root->add_node(new_node); }
    fix_after_add(new_node);
}

void RedBlackTree::fix_after_add(Node* new_node)
{
    if (root == new_node){
        new_node->color = BLACK;
    }
    else{
        fix_double_red(new_node);
    }
    /*

    If the inserted node is the root,
    it is turned black. Otherwise, we fix up
    any double-red violations by calling fix_double_red(new_node)
    */
}

// Function to perform Left Rotation
void RedBlackTree::rotateLeft(Node* x) {
//    Node* x = node->right;
//    Node* y = x->left;
//    x->left = node;
//    node->right = y;
//    node->parent = x;
//    if (y != nullptr)
//        y->parent = node;
//    return x;
//    Node *y = x->right;
//    x->right = y->left;
//    if(y->left != nullptr) {
//      y->left->parent = x;
//    }
//    y->parent = x->parent;
//    if(x->parent == nullptr) { //x is root
//      root = y;
//    }
//    else if(x == x->parent->left) { //x is left child
//      x->parent->left = y;
//    }
//    else { //x is right child
//      x->parent->right = y;
//    }
//    y->left = x;
//    x->parent = y;
    if (x == nullptr || x->right == nullptr){
        return;}

    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Function to perform Right Rotation
void RedBlackTree::rotateRight(Node* y) {
//    Node* x = node->left;
//    Node* y = x->right;
//    x->right = node;
//    node->left = y;
//    node->parent = x;
//    if (y != nullptr)
//        y->parent = node;
//    return x;
    
    //Node* y = node->left;
//    Node* y_right;
//    if (!y) {y_right = nullptr;}
//    else {y_right = y->right;}
//    node->left = y->right;
//    if(y->right != nullptr) {
//      y->right->parent = node;
//    }
//    y->parent = node->parent;
//    if(node->parent == nullptr) { //node is root
//      root = y;
//    }
//    else if(node == node->parent->right) { //node is left child
//      node->parent->right = y;
//    }
//    else { //x is right child
//      node->parent->left = y;
//    }
//    y->right = node;
//    node->parent = y;
    if (y == nullptr || y->left == nullptr)
    {return;}

    Node* x = y->left;
    y->left = x->right;
    if (x->right != nullptr)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}
void RedBlackTree::fix_double_red(Node* node){
    if(node==nullptr)
        return;
    if(node->parent==nullptr)
    {node->color=BLACK;return;}
    
    Node *p= node->parent;
    //Case 2: Parent is BLACK
    if(p!=nullptr && p->color==BLACK)
            return;
    
    //Case 3: Parent and Uncle are RED
    Node *u = nullptr;
    if(p == p->parent->left)
    {u = p->parent->right;}
    if(p == p->parent->right)
    {u = p->parent->left;}
    
    if( p->color==RED && (u!=nullptr && u->color==RED))
    {
        p->color=BLACK;
        u->color=BLACK;
        p->parent->color=RED;
        fix_double_red(p->parent);
        return;
    }

    //Case 4: Parent is Red and Uncle is Black(Or NULL)
    //If parent is left son
    if(( p->parent != nullptr ) && (p == p->parent->left))
    {
        if(( node->parent != nullptr ) && (node == node->parent->right))
        {node=p; rotateLeft(p);}
        
        p->color=BLACK;
        
        if(p->parent!=nullptr)
        {p->parent->color=RED;
        rotateRight(p->parent);}
        return;
    }
    //If parent is right son
    else if (( p->parent != nullptr ) && (p == p->parent->right))
    {
        if(( node->parent != nullptr ) && (node == node->parent->left))
        {node=p; rotateRight(p);}
        p->color=BLACK;
        if(p->parent!=NULL)
        {p->parent->color=RED;
        rotateLeft(p->parent);}
        return;
    }
}
    /*
    if(z == root) {return;}
    if (z->parent == root){root->color = BLACK; return; }
    if (z->parent->color == BLACK){return;}
    
    while(z->parent->color == RED) {
      if(z->parent == z->parent->parent->left) { //z.parent is the left child

        Node *y = z->parent->parent->right; //uncle of z

        if(y->color == RED) { //case 1
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        }
        else { //case2 or case3
          if(z == z->parent->right) { //case2
            z = z->parent; //marked z.parent as new z
            rotateLeft(z);
          }
          //case3
          z->parent->color = BLACK; //made parent black
          z->parent->parent->color = RED; //made parent red
          rotateRight(z->parent->parent);
        }
      }
      else { //z.parent is the right child
        Node *y = z->parent->parent->left; //uncle of z

        if(y->color == RED) {
          z->parent->color = BLACK;
          y->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
          } else {
              if(z == z->parent->left) {
                  z = z->parent; //marked z.parent as new z
                  rotateRight(z);
                  
              }
              z->parent->color = BLACK; //made parent black
              z->parent->parent->color = RED; //made parent red
              rotateLeft(z->parent->parent);
              
          }
          
      }
        
    }
    root->color = BLACK;
}*/

//void RedBlackTree::fix_double_red(Node* child)
//{
 /*The code for fixing up a double-red violation is quite long.
 Recall that there are four possible arrangements of the
 double-red nodes.

 In each case, we must sort the nodes and their children.
 Once we have the seven references n1, n2, n3, t1, t2, t3,
 and t4, the remainder of the procedure is straightforward.


 After the rearrangment, if we find that we introduced
 another double-red violation, we continue fixing it.
 Eventually, the violation is removed,
 or we reach the root, in which case the root is simply
 colored black.

 */
/*
void RedBlackTree::fix_double_red(Node* child){
    Node* y;
    if(child == root) {return;}
    if (child->parent == root){ root->color = BLACK; return; }
    if (child->parent->color == BLACK){return;}
    if(child-> parent == nullptr) {return;}
    if(child->parent->parent == nullptr) {return;}
    


        if (child->parent == child->parent->parent->left){ //z.parent is left child
            y = child->parent->parent->right; //uncle of child
            
            if ((y != nullptr)&&(y->color == RED)){ //case 1
                child->parent->color = BLACK;
                y->color = BLACK;
                child->parent->parent->color = RED;
                //child =  child->parent->parent;
                fix_double_red(child->parent->parent);
            }
            else {//case 2 or 3
                if (child == child->parent->right){ //case 2
//                    child = child->parent; //marked z.parent as new z
//                    rotateLeft(child); //rotated parent of orignal z
                    //Node* temp = child->parent;
                    rotateLeft(child->parent);
                    fix_double_red(child->parent);
                }
                //case 3
                child->parent->color = BLACK; // made parent black
                child->parent->parent->color = RED; // made grandparent red
                rotateRight(child->parent->parent); // right rotation on grandparent
            }
        }
        else {// z.parent is right child
            y = child->parent->parent->left; //uncle of child
            
            if ((y != nullptr)&&(y->color == RED)){ //case 1
                child->parent->color = BLACK;
                y->color = BLACK;
                child->parent->parent->color = RED;
                //child =  child->parent->parent;
                fix_double_red(child->parent->parent);
            }
            else if (y == nullptr){
                if (child == child->parent->left){ //case 2
                    //child = child->parent; //marked z.parent as new z
                    //rotateRight(child); //rotated parent of orignal z
                    //fix_double_red(child->parent);
                    //Node* temp = child->parent;
                    rotateRight(child->parent);
                    fix_double_red(child->parent);
                    
                }
                //case 3
                child->parent->color = BLACK; // made parent black
                child->parent->parent->color = RED; // made grandparent red
                rotateLeft(child->parent->parent); // right rotation on grandparent
            }
            else {//case 2 or 3
                if (child == child->parent->left){ //case 2
                    //child = child->parent; //marked z.parent as new z
                    //rotateRight(child); //rotated parent of orignal z
                    //fix_double_red(child->parent);
                    //Node* temp = child->parent;
                    rotateRight(child->parent);
                    fix_double_red(child->parent);
                    
                }
                //case 3
                child->parent->color = BLACK; // made parent black
                child->parent->parent->color = RED; // made grandparent red
                rotateLeft(child->parent->parent); // right rotation on grandparent
            }
            
        }

    root->color = BLACK;
}*/
//    Node* p = child->parent;
//    Node* gp = child->parent->parent;
    
 /*   if (child->parent->right == child) {
        if (child->parent->left == nullptr || child->parent->left->color == BLACK) {
            if (child->left != nullptr && child->left->color == RED){
                child->right = rotateRight(child->right);
                child->right->parent = child;
                child = rotateLeft(child);
                child->color = BLACK;
                child->left->color = RED;
            }
                //rl = true;
            else if ((child->right != nullptr) && (child->right->color == RED)){
                child = rotateLeft(child);
                child->color = BLACK;
                child->left->color = RED;
                //ll = true;
            }
        } else {
            child->parent->left->color = BLACK;
            child->color = BLACK;
            if (child->parent != this->root){
                child->parent->color = RED;
            }
        }
    } else {
        if (child->parent->right == nullptr || child->parent->right->color == BLACK) {
            if (child->left != nullptr && child->left->color == RED){
                child = rotateRight(child);
                child->color = BLACK;
                child->right->color = RED;
            }
                //rr = true;
            else if ((child->right != nullptr) && (child->right->color == RED)){
                child->left = rotateLeft(child->left);
                child->left->parent = child;
                child = rotateRight(child);
                child->color = BLACK;
                child->right->color = RED;
            }
                //lr = true;
        } else {
            child->parent->right->color = BLACK;
            child->color = BLACK;
            if (child->parent != this->root){
                child->parent->color = RED;
            }
        }
    }
    */
    
    
    
  /*  Node* p = child->parent;
    //is child is root (parent is null), color it black and return
    if(!p){
        child->color = BLACK;
        return;
    }
    //if parent of red child is black, exit; no double red
    if (p->color){return;}
    Node* gp = p->parent;
    
    Node* n1; Node* n2; Node* n3; Node* t1; Node* t2; Node* t3; Node* t4;
    
    //assign n nodes to the right generation, assign t nodes to correct parent
    if (child->data > p->data){
        if (p->data > gp->data){
            n3 = child;
            n2 = p;
            n1 = gp;
            t2 = n2->left; t3 = n3->left;
            //tree 4
        }
        else {
            n3 = gp;
            n2 = child;
            n1 = p;
            t2 = n2->left; t3 = n2->right;
            //tree 1
        }
    }
    else {
        if (p->data > gp->data){
            n3 = p;
            n2 = child;
            n1 = gp;
            t2 = n2->left; t3 = n2->right;
            //tree 3
        }
        else {
            n3 = gp;
            n2 = p;
            n1 = child;
            t2 = n1->right; t3 = n2->right;
            //tree 2
        }
    }
    t1 = n1->left; t4 = n3->right;
    //reassemble in correct order
    n2->color = RED;
    n1->color = BLACK;
    n3->color = BLACK;
    if (gp->parent == nullptr) {
        //gp is root so simple transformation
        root = n2;
        root->parent = nullptr;
        root->color = BLACK;
        replace_with(root->left, n1);
        replace_with(root->right, n3);
        replace_with(root->left->left, t1);
        replace_with(root->left->right, t2);
        replace_with(root->right->left, t3);
        replace_with(root->right->right, t4);
        
    } else {
        Node* ggp = gp->parent;
        if (gp == ggp->left) {
            //gp is the left child
            replace_with(ggp->left, n2);
            replace_with(ggp->left->left, n1);
            replace_with(ggp->left->right, n3);
            replace_with(ggp->left->left->left, t1);
            replace_with(ggp->left->left->right, t2);
            replace_with(ggp->left->right->left, t3);
            replace_with(ggp->left->right->right, t4);
        } else{
            replace_with(ggp->right, n2);
            replace_with(ggp->right->left, n1);
            replace_with(ggp->right->right, n3);
            replace_with(ggp->right->left->left, t1);
            replace_with(ggp->right->left->right, t2);
            replace_with(ggp->right->right->left, t3);
            replace_with(ggp->right->right->right, t4);
        }
    }
    //n2 is the red node, so recurse on n2
    fix_double_red(n2); */




void RedBlackTree::erase(std::string element)
{
    /*We remove a node in the same way as in a binary search
    tree. However, before removing it, we want to make sure
    that it is colored red. There are two cases for removal:
    removing an element with one child and removing the
    successor of an element with two children.
    Both branches must be modified.*/

    // Find node to be removed
    // If the node is not found, return
    // The node "to_be_removed" contains element
    // If one of the children is empty, use the other
   //call  fix_before_remove(to_be_removed);
   //call  replace_with(to_be_removed, new_child);
    
    
    // Find node to be removed
    Node* to_be_removed = root;
    Node* parent = nullptr;
    bool found = false;
    while (!found && to_be_removed != nullptr)
    {
        if (element == to_be_removed->data)
        {
            found = true;
        }
        else
        {
            parent = to_be_removed;
            if (element < to_be_removed->data)
            {
                to_be_removed = to_be_removed->left;
            }
            else
            {
                to_be_removed = to_be_removed->right;
            }
        }
    }

    if (!found) { return; }

    // to_be_removed contains element

    // If one of the children is empty, use the other

    if (to_be_removed->left == nullptr || to_be_removed->right == nullptr)
    {
        Node* new_child;
        if (to_be_removed->left == nullptr)
        {
            new_child = to_be_removed->right;
        }
        else if (to_be_removed->right == nullptr)
        {
            new_child = to_be_removed->left;
        }
        else {
            new_child = nullptr;
        }

        if (parent == nullptr) // Found in root
        {
            replace_with(root, new_child);
        }
        else if (parent->left == to_be_removed)
        {
            replace_with(parent->left,new_child);
        }
        else
        {
            replace_with(parent->right, new_child);
        }
        return;
    }

    // Neither subtree is empty

    // Find smallest element of the right subtree

    Node* smallest_parent = to_be_removed;
    Node* smallest = to_be_removed->right;
    while (smallest->left != nullptr)
    {
        smallest_parent = smallest;
        smallest = smallest->left;
    }

    // smallest contains smallest child in right subtree

    // Move contents, unlink child

    to_be_removed->data = smallest->data;
    to_be_removed->color = smallest->color;
    if (smallest_parent == to_be_removed)
    {
        smallest_parent->right = smallest->right;
    }
    else
    {
        smallest_parent->left = smallest->right;
    }
    
    fix_before_remove(smallest);
    replace_with(smallest, smallest->right);

    // Neither subtree is empty

    // Find smallest element of the right subtree
    // smallest contains smallest child in right subtree
    // Move contents, unlink child
    //call    fix_before_remove(smallest);
    //call replace_with(smallest, smallest->right);
    //The replace_with helper function, 
    //which was shown earlier,
    //takes care of updating the parent, child, and root links. 
}



void RedBlackTree::fix_before_remove(Node* to_be_removed)
{
    /*The fix_before_remove function has three cases. 
    Removing a red leaf is safe.
    If a black node has a single child,
    that child must be red, and we can safely swap the colors.
    (We don¡¯t actually bother to color the node
    that is to be removed.)
    The case with a black leaf is the hardest.
    We need to initiate the ¡°bubbling up¡± process.*/

    //Case1: to_be_removed is RED
    if (!to_be_removed->color){
        return;
    }

    //Case2: It is not a leaf// Color the child black
    if(to_be_removed->color){
        if(to_be_removed->right){
            to_be_removed->right->color = BLACK;
        } else if(to_be_removed->left){
            to_be_removed->left->color = BLACK;
        }
    }

    //Case3: bubble_up(to_be_removed->parent)
    if (to_be_removed->color && !to_be_removed->left && !to_be_removed->right){
        bubble_up(to_be_removed->parent);
    }
}

void RedBlackTree::bubble_up(Node* parent)
{
    /*To bubble up, we move a ¡°toll charge¡± from the children
    to the parent. This may result in a negative-red or
    double-red child, which we fix. If neither fix was
    successful, and the parent node is still double-black,
    we bubble up again until we reach the root.
    The root color can be safely changed to black.*/

    //update the color
    
    if (parent != nullptr) {parent->color +=1;}
    if (parent->left){parent->left->color -=1;}
    if (parent->right){parent->right->color -=1;}
    

    bubble_up_fix(parent->left);
    bubble_up_fix(parent->right);
 
    // if parent is DOUBLE_BLACK
    if (parent->color == 2){
        if (parent == root){ parent->color = BLACK;}
        else{ bubble_up(parent->parent);}
    }
    // If parent is root, color it black
    //If not, call  bubble_up(parent->parent)
    
}

bool RedBlackTree::bubble_up_fix(Node* child)
{
    if (child == nullptr){return false;}
    if (child->parent == nullptr){return false;}
    if (child->color == NEGATIVE_RED)
    {
        fix_negative_red(child);
        return true;
    }
    else if (child->color == RED)
    {
        if (child->left != nullptr && child->left->color == RED)
        {
            fix_double_red(child->left); return true;
        }
        if (child->right != nullptr && child->right->color == RED)
        {
            fix_double_red(child->right); return true;
        }
    }
    return false;
}



void RedBlackTree::fix_negative_red(Node* neg_red)
{
   //implement the rearrangement shown in the pictures.
    Node* n4 = neg_red->parent;
    if (n4->left == neg_red){
        //Node* n1 = neg_red->left;
        Node* n3 = neg_red->right;
        Node* t1 = n3->left;
        Node* t2 = n3->right;
        //Node* t3 = n4->right;
        
        replace_with(neg_red->right, t1); n3->left = nullptr;
        replace_with(neg_red->parent, n3);
        replace_with(n3->right, n4);
        replace_with(n4->left, t2);
        
    }
    else {
        //Node* n1 = neg_red->right;
        Node* n3 = neg_red->left;
        Node* t1 = n3->right;
        Node* t2 = n3->left;
        //Node* t3 = n4->left;
        
        replace_with(neg_red->left, t1); n3->right = nullptr;
        replace_with(neg_red->parent, n3);
        replace_with(n3->left, n4);
        replace_with(n4->right, t2);
    }
    
}


void RedBlackTree::print() const
{
    print(root, 0, ' ');
    std::cout << std::endl;
}
void RedBlackTree::print(Node* parent, int indent, char symbol) const
{
    if (parent == nullptr) { return; }
    print(parent->right, indent + 3, '/');
    // Print right subtree with increased indentation

    if (parent->color == RED)
    {
        std::cout << std::setw(indent) << symbol << "R" << parent->data << std::endl;
    }
    else
    {
        std::cout << std::setw(indent) << symbol << "B" << parent->data << std::endl;
    }
    // Print current node with indentation
    print(parent->left, indent + 3, '\\');
    // Print left subtree with increased indentation
}


int RedBlackTree::count(std::string element) const
{
    Node* current = root;
    while (current != nullptr)
    {
        if (element < current->data)
        {
            current = current->left;
        }
        else if (element > current->data)
        {
            current = current->right;
        }
        else return 1;
    }
    return 0;
}



void Node::add_node(Node* new_node)
{
    if (new_node->data < data)
    {
        if (left == nullptr)
        {
            left = new_node;
            left->parent = this;
        }
        else { left->add_node(new_node); }
    }
    else if (new_node->data > data)
    {
        if (right == nullptr)
        {
            right = new_node;
            right->parent = this;
        }
        else { right->add_node(new_node); }
    }
}




