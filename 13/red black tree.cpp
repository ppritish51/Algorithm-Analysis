///THINGS TO RESOLVE
/*

*/
///NOTES
/**

*/


#include<iostream>
#include<cstdlib>

using namespace std;

void instructions();
void insert_data(float x);
void rb_insert_fix_up(struct datapack *x);   ///will take pointer to insert node
void left_rotate(struct datapack *x);
void right_rotate(struct datapack *x);
void inorder_print(struct datapack *point);

datapack* tree_minimun(struct datapack *node);
datapack* tree_maximum(struct datapack *node);
datapack* search_data(float x,struct datapack *temp);
void delete_data(struct datapack *z);
void transplant(struct datapack *u,struct datapack *v);
void delete_fix_up(struct datapack *x);




#define RED 0
#define BLACK 1

struct datapack
{
    float key;
    int color;
    datapack *parent;
    datapack *left;
    datapack *right;
};

static struct datapack *nil = new datapack;
struct datapack *root = nil;


int main()
{
    nil->left =NULL;
    nil->right = NULL;
    nil->parent =NULL;
    nil->color = BLACK;
    nil->key = 0;
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
                inorder_print(root);
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
         storage->color = BLACK;
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
         storage->color = RED;
         if(temp->key > x)
         {
             temp->left = storage;
         }
         else
         {
             temp->right = storage;
         }
     }
     rb_insert_fix_up(storage);
}


void rb_insert_fix_up(struct datapack *x)
{
    while(x->parent->color == RED)
    {
        //cout<<"\n786";
        struct datapack *y;
        if(x->parent == x->parent->parent->left)
        {
            y =x->parent->parent->right;
            if(y->color == RED)
            {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
               // cout<<"  1";
            }
            else
            {
                if(x == x->parent->right)
                {
                    x = x->parent;
                    left_rotate(x);
                                   // cout<<"  96";

                }
                x->parent->color = BLACK;
                x->parent->parent->color =RED;
                right_rotate(x->parent->parent);
               // cout<<"   2";
           }
          // cout<<"over 1\n";
        }

        else //if(x->parent == x->parent->parent->right)
        {
            y =x->parent->parent->left;
            if(y->color == RED)
            {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
                //cout<<"  3";
            }
            else
            {
                if(x == x->parent->left)
                {
                    x = x->parent;
                    right_rotate(x);
                                 //   cout<<"00";

                }
                x->parent->color = BLACK;
                x->parent->parent->color =RED;
                left_rotate(x->parent->parent);
                           //     cout<<" 32.1";

           }
                  // cout<<"over 2\n";

        }
            //cout<<"\nover at second last\n";

    }
   // cout<<"\nover at last\n";
    root->color = BLACK;
}



void left_rotate(struct datapack *x)
{
    struct datapack *y;
    y=x->right;
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

}

void right_rotate(struct datapack *x)
{
    struct datapack *y;
    y=x->left;
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

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///deleting area
void delete_data(struct datapack *z)
{
    struct datapack *x;
    struct datapack *y =z;
    int y_original_color = y->color;
    if(z->left == nil)
    {
        x = z->right;
        ///it's simple just transplant z with it's right child
        transplant(z,z->right);
    }
    else if(z->right == nil)
    {
        x = z->left;
        ///it's simple just transplant z with it's left child
        transplant(z,z->left);
    }
    else
    {
        y = tree_minimun(z->right);
        cout<<"right mini = "<<y->key;
        y_original_color = y->color;
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
        y->color = z->color;
    }

    if(y_original_color == BLACK)
        delete_fix_up(x);
    delete(z);
}

void delete_fix_up(struct datapack *x)
{
    struct datapack *w;
    while(x != root && x->color == BLACK)
    {
        if(x == x->parent->left)
        {
            w = x->parent->right;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(x->parent);
                w = x->parent->right;
            }
            else if(w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color =RED;
                x = x->parent;
            }
            else
            {
                if(w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(x->parent);
                x = root;
            }
        }

        else
        {
            w = x->parent->left;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(x->parent);
                w = x->parent->left;
            }
            else if(w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color =RED;
                x = x->parent;
            }
            else
            {
                if(w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(x->parent);
                x = root;
            }
            }
        }
    x->color = BLACK;
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

void inorder_print(struct datapack *point)
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
        inorder_print(temp->left);
        cout<<temp->key<<"  [ ";
        if(temp->color == RED)
            cout<<"RED ] --> ";
        else
            cout<<"BLACK ] --> ";
        inorder_print(temp->right);
    }
}
