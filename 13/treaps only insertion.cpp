#include<iostream>
#include<cstdlib>
#include<ctime>


/**
more priority number is down
*/
using namespace std;

struct datapack
{
    int key;
    datapack *parent;
    datapack *left;
    datapack *right;
    int priority;
};


void instructions();
void insert_element();
int preorder_print();
int successor();

datapack* tree_search(int suc,struct datapack *node);
datapack* tree_minimun(struct datapack *node);
datapack* tree_maximum(struct datapack *node);

void left_rotate(struct datapack *x);
void right_rotate(struct datapack *x);
void check_priority(struct datapack *x);


struct datapack *root = NULL;

int main()
{
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
                successor();
                break;
            case 2:
                cout<<"\nEnter the element to search :: ";
                {
                    int _g;
                    cin>>_g;
                    struct datapack *_u;
                    _u = tree_search(_g,root);
                    if(_u == NULL)
                    {
                        cout<<"\n      NOT FOUND\n";
                    }
                    else
                    {
                        cout<<"      found";
                    }
                }
                break;
            case 3:
                preorder_print();
                break;
            case 4:
                insert_element();
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
    cout<<"1.To find Successor"<<endl;
    cout<<"2.To Search a number"<<endl;
    cout<<"3.Print data in Pre-order way"<<endl;
    cout<<"4.To Insert an element"<<endl;
    cout<<"DEFAULT : TO EXIT"<<endl;
}

int successor()
{
    cout<<"\nEnter the number whose successor you ant to find :: ";
    int suc;
    cin>>suc;
    struct datapack *temp,*_store;
    temp = tree_search(suc,root);
    if(temp == NULL)
    {
        cout<<"\n             INVALID ELEMENT ENTERED\n";
    }
    else if(temp->key == tree_maximum(root)->key)
    {
        cout<<"\n IT'S THE HIGHEST NUMBER IT CANNOT HAVE A SUCCESSOR \n";
    }
    else
    {
        if(temp->right != NULL)
        {
            _store = tree_minimun(temp->right);
            cout<<"\nsuccessor :: "<<_store->key<<endl;
            return 0;
        }
        _store = temp->parent;
        while(_store != NULL && temp == _store->right)
        {
            temp = _store;
            _store = _store->parent;
        }
        cout<<"\nsuccessor :: "<<_store->key<<endl;
    }
}

datapack* tree_minimun(struct datapack *node)
{
    while(node->left != NULL)
        node = node->left;
    return node;
}

datapack* tree_maximum(struct datapack *node)
{
    while(node->right != NULL)
        node = node->right;
    return node;
}


datapack* tree_search(int suc,struct datapack *node)
{
    struct datapack *temp;
    temp = node;
    if(temp == NULL)
    {
        return NULL;
    }
    else if(suc == temp->key)
    {
        return temp;
    }
    else if(suc < temp->key)
    {
        return tree_search(suc,temp->left);
    }
    else
    {
        return tree_search(suc,temp->right);
    }

}

void insert_element()
{
     srand (time(NULL));
     struct datapack *temp = new datapack;
     struct datapack *storage = new datapack;
     struct datapack *_find = root;
     int num;
     cout<<"\nEnter the number :: ";
     cin>>num;
     if(_find == NULL)   ///it's first element
     {
         storage->key = num;
         storage->left = NULL;
         storage->right = NULL;
         storage->parent = NULL;
         root = storage;
         storage->priority =rand()%1000;
     }
     else
     {
         while(_find!=NULL)
         {
             temp = _find;
             if(_find->key > num)
             {
                 _find = _find->left;
             }
             else
             {
                 _find = _find->right;
             }
         }
         storage->key = num;
         storage->left = NULL;
         storage->right = NULL;
         storage->parent = temp;
         storage->priority =rand()%1000;
         if(temp->key > num)
         {
             temp->left = storage;
         }
         else
         {
             temp->right = storage;
         }
     }
     check_priority(storage);
}

void check_priority(struct datapack *x)
{
    while(x != root && x->priority <x->parent->priority)
    {
        if(x == x->parent->left)
            right_rotate(x->parent);
        else
            left_rotate(x->parent);
    }
}

void left_rotate(struct datapack *x)
{
    struct datapack *y;
    y=x->right;
    x->right = y->left;
    if(y->left != NULL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL)
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
    if(y->right != NULL)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL)
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

///printing area

int preorder_print()
{
    if(root == NULL)
    {
        cout<<" it's null  "<<endl;
        return 0;
    }
    struct datapack *_stack[50];
    int top=-1;
    struct datapack *temp;
    temp = root;
    if(root == NULL)
    {
        //do nothing
    }
    _stack[++top] = temp;
    while(top>=0)
    {
        cout<<_stack[top]->key<<" ( "<<_stack[top]->priority<<" )"<<"  -->  ";
        temp = _stack[top];
        --top;
        if(temp->right != NULL)
        {
            _stack[++top] = (temp->right);
        }
        if(temp->left != NULL)
            _stack[++top] = (temp->left);
    }
    cout<<"null\n";
}


