/** ::points to note

   --> when elements are equal then it is inserted in right node
       so see when you are analyzing balance function

*/

#include<iostream>
#include<cstdlib>

using namespace std;

void instructions();
void insert_data(float x);
void left_rotate(struct datapack *x);
void right_rotate(struct datapack *x);
void pre_order_print(struct datapack *point);

datapack* tree_minimun(struct datapack *node);
datapack* tree_maximum(struct datapack *node);
datapack* search_data(float x,struct datapack *temp);
void delete_data(struct datapack *z);
void transplant(struct datapack *u,struct datapack *v);
void delete_fix_up(struct datapack *x);

/**
it will return maximum height among left and right subtree
so remember to add one (++1) to it when assigning the height
or updating the height
*/

int check_height(struct datapack *node);
void rotation_height_correction(struct datapack *x);
void rb_insert_height_fix_up(struct datapack *node);
void balance(struct datapack *x);


/** ::: how height maintenance is working???

step 1 -: first we will insert number and assign it height to be 1 .
step 2 -: then we run "rb_insert_height_fix_up" to maintain the the height of parent element by back tracking the path
step 3 -: then run "insert_fix_up" for maintaining the property of red black tree which only cause problem in height
          if left_rotation or right_rotation is called.
*/
/**

    :::  so now adjust rotation part
    let's see left rotation and you can adjust right rotation same as in left
-----------------------------------------------------------
case 1-1
     |              |
     x              y       #note :: height of m does not change (look from bottom)
    / \    ==>     / \      # x height is initially m + 1(for y) + 1(itself)
  nil  y          x   m     # finally x height is 1
      / \       / \
    nil  m   nil   nil
 -----------------------------------------------------------
 case 1-2
     |              |
     x              y       #note :: height of m does not change (look from bottom)
    / \    ==>     / \
  nil  y          x   nil
      / \       / \
    nil  nil   nil   nil
 -----------------------------------------------------------
 case 2-1
     |              |
     x              y       #note :: height of m and p does not change (look from bottom)
    / \    ==>     / \      # x height is initially m + 1(for y) + 1(itself) or p + 1
   p   y          x   nil   # finally it's p+1 (compare y) or q+1
      / \       / \
      q  nil   p   q
 -----------------------------------------------------------
case 2-2(special case of 2-1 but no need to treat specially as nil.height = 0 so any node height is greater than nil.height)
     |              |
     x              y       #note :: height of m and p does not change (look from bottom)
    / \    ==>     / \      # x height is initially m + 1(for y) + 1(itself) or p + 1
   p   y          x   nil   # finally it's p+1 (compare y)
      / \       / \
    nil  nil   p   nil
 -----------------------------------------------------------
 */
 /**
step 4 -: now after rotation you need to update the height of all node from y to root
          as root height has been disturbed ,so we call rotation_height_correction
          by passing y parent in it
step 5 -: now check for height difference which is greater than one
*/



struct datapack
{
    float key;
    int height;
    datapack *parent;
    datapack *left;
    datapack *right;
};

static struct datapack *nil = new datapack;
struct datapack *root = nil;


int main()
{
    nil->left =NULL;
    nil->height = 0;
    nil->right = NULL;
    nil->parent =NULL;
    nil->key = -100000;
    int choice;
    instructions();
    do{
        cout<<"\nCHOICE :: ";
        cin>>choice;
        switch(choice)
        {
            case 0:
                instructions();
                break;
            case 1:
                {
                    float x;
                    cout<<"Enter the number :: ";
                    cin>>x;
                    insert_data(x);
                }
                break;
            case 2:
                {
                    float x;
                    cout<<"enter the number you want to delete ::";
                    cin>>x;
                    struct datapack *_u;
                    _u = search_data(x,root);
                    if(_u == nil)
                    {
                        cout<<"\n      ELEMENT DON'T EXIST IN LIST\n";
                    }
                    else
                    {
                        delete_data(_u);
                    }
                }
                break;
            case 3:
                cout<<"\n";
                pre_order_print(root);
                break;
            default :
                choice = 100; ///for exiting program
        }
    }while(choice>=0&&choice<=8);
    //system("pause");
}

void instructions()
{
    cout<<"                 INSTRUCTIONS           "<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<"  PRESS THE RESPECITVE KEY TO TAKE THE FOLLOWING ACTION"<<endl;
    cout<<"0.To print Instructions"<<endl;
    cout<<"1.To Insert Element"<<endl;
    cout<<"2.To Delete an element"<<endl;
    cout<<"3.To print IN-ORDER"<<endl;
    cout<<"DEFAULT : TO EXIT"<<endl;
}


void insert_data(float x)
{
     struct datapack *temp ;
     struct datapack *storage = new datapack;
     struct datapack *_find = root;
     if(_find == nil)                ///it's first element
     {
         root = storage;
         root->parent = nil;
         storage->key = x;
         storage->left = nil;
         storage->right = nil;
         storage->height = 1;
     }
     else
     {
         while(_find!=nil)
         {
             temp = _find;
             if(_find->key > x)
             {
                 _find = _find->left;
             }
             else
             {
                 _find = _find->right;
             }
         }
         storage->key = x;
         storage->left = nil;
         storage->right = nil;
         storage->parent = temp;
         storage->height = 1;
         if(temp->key > x)
         {
             temp->left = storage;
         }
         else
         {
             temp->right = storage;
         }
     }
     rb_insert_height_fix_up(storage->parent);
     balance(storage);
}

void left_rotate(struct datapack *x)
{
    struct datapack *y;
    y=x->right;

    if(x->left == nil && y->left == nil)
    {
        x->height = 1; ///case 1-1 and 1-2
    }
    else
    {
        x->height = ((x->left->height > y->left->height)? x->left->height+1 : y->left->height+1);
    }
    //cout<<"x->key :: "<<x->key<<"x->height :: "<<x->height<<endl;
    //cout<<"y->key :: "<<y->key<<"y->height :: "<<y->height<<endl;
    y->height = ((x->height > y->right->height)? x->height +1: y->right->height+1);
    //cout<<"y->key :: "<<y->key<<"y->height :: "<<y->height<<endl;
    x->right = y->left;
    if(y->left != nil)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == nil)
    {
        root = y;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;            //put's x on y's left
    x->parent = y;
    rotation_height_correction(y->parent);

}

void right_rotate(struct datapack *x)
{
    struct datapack *y;
    y=x->left;

    if(x->right == nil && y->right == nil)
    {
        x->height = 1;
    }
    else
    {
        x->height = ((x->right->height > y->right->height)? x->right->height+1 : y->right->height+1);
    }
    y->height = ((x->height > y->left->height)? x->height +1: y->left->height+1);

    x->left = y->right;
    if(y->right != nil)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == nil)
    {
        root = y;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->right = x;            //put's x on y's right
    x->parent = y;
    rotation_height_correction(y->parent);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void rotation_height_correction(struct datapack *x)
{
    struct datapack *temp = x;
    while(x != nil)  /// we have passed parent of y so directly checking for nil
    {
        x->height = check_height(x)+1;
        x = x->parent;
    }
}

int check_height(struct datapack *node)
{
    if(node->right == nil && node->left == nil)
    {
        return 0;
    }
    else
    {
        if(node->left->height > node->right->height)
             return node->left->height;
        else
             return node->right->height;
    }
}

void rb_insert_height_fix_up(struct datapack *node)
{
    struct datapack *temp = node;
    while(temp != nil)
    {
        temp->height = check_height(temp)+1;
        temp = temp->parent;
    }
}

void balance(struct datapack *x)
{
    int unbalance ;
     while(x != nil)
     {
        unbalance = x->left->height - x->right->height;
        while(unbalance>1 || unbalance<-1)
        {

             if(unbalance > 0 )
             {
                  if(x->left->key <= x->left->right->key)  ///their will be =
                  {
                      left_rotate(x->left);
                  }
                  cout<<"before :: ";
                  pre_order_print(root);
                  right_rotate(x);
                  cout<<"\nafter :: ";
                  pre_order_print(root);
             }
             else if(unbalance < 0 )
             {
                  if(x->right->key > x->right->left->key  && x->right->left != nil)
                  {
                      right_rotate(x->right);
                  }
                  cout<<"before :: ";
                  pre_order_print(root);
                  left_rotate(x);
                  cout<<"\nafter :: ";
                  pre_order_print(root);
             }
             x = x->parent;
             unbalance = x->left->height - x->right->height;
        }
        x=x->parent;
     }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///deleting area
void delete_data(struct datapack *z)
{
    struct datapack *x;
    struct datapack *y =z;
    if(z->left == nil)
    {
        x = z->right;
        ///it's simple just transplant z with it's right child
        transplant(z,z->right);
        rb_insert_height_fix_up(x->parent);
    }
    else if(z->right == nil)
    {
        x = z->left;
        ///it's simple just transplant z with it's left child
        transplant(z,z->left);
        rb_insert_height_fix_up(x->parent);
    }
    else
    {
        y = tree_minimun(z->right);
        cout<<"right mini = "<<y->key;
        x = y->right;
        if(y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            transplant(y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z,y);
        y->left = z->left;
        y->left->parent = y;
        rb_insert_height_fix_up(x->parent);
    }
    if(z->parent == nil)
    {
        cout<<"\ndeleted root"<<endl;
        balance(root);
    }
    else
    {
        balance(z->parent);
    }

    delete(z);
}



void transplant(struct datapack *u,struct datapack *v)
{
    if(u->parent == nil)
    {
        root = v;
    }
    else if(u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }

    v->parent = u->parent;

}

datapack* search_data(float x,struct datapack *temp)
{
    struct datapack *node;
    node = temp;
    if(node == nil)
    {
        return nil;
    }
    else if(x == node->key)
    {
        return node;
    }
    else if(x < node->key)
    {
        return search_data(x,node->left);
    }
    else
    {
        return search_data(x,node->right);
    }

}


datapack* tree_minimun(struct datapack *node)
{
    while(node->left != nil)
        node = node->left;
    return node;
}

datapack* tree_maximum(struct datapack *node)
{
    while(node->right != nil)
        node = node->right;
    return node;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///printing area

void pre_order_print(struct datapack *point)
{
    //cout<<"\nin different function check root key -->"<<root->key<<endl;
    struct datapack *temp = point;
    if(temp==nil)
    {
       // cout<<"it's nil";
        //nothing
        if(root==nil)
        {
            cout<<"it's nil\n";
        }
    }
    else
    {
        cout<<temp->key<<" { "<<temp->height<<" } "<<" --> ";
        pre_order_print(temp->left);
        pre_order_print(temp->right);
    }
}

