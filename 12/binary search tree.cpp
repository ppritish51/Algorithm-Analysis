#include<iostream>
#include<cstdlib>

///THINGS TO RESOLVE
/*
* if two elements are same then it's successor is that element only ::

  solution ::
       when you compare the successor with it's key and find both to be same,
       then find a number higher then itself

*/
///NOTES
/**

*for printing
   -> in-order I have used recursive function
   -> pre-order I have used iterative function
   -> post-order I have used recursive function

*Predecessor part left to do

     // just copy successor part and make changes

*/

using namespace std;

void instructions();
void insert_element();
void inorder_print(struct datapack *point);
void inorder_print_iterative(struct datapack *point);
int preorder_print();
void postorder_print(struct datapack *point);
int successor();
int predecessor();

void tree_delete(struct datapack *node);
void transplant(struct datapack *u,struct datapack *v);

datapack* tree_search(int suc,struct datapack *node);
datapack* tree_minimun(struct datapack *node);
datapack* tree_maximum(struct datapack *node);


struct datapack
{
    int key;
    datapack *parent;
    datapack *left;
    datapack *right;
};

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
                predecessor();
                break;
            case 3:
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
            case 4:
                cout<<"\n";
                inorder_print(root);
                break;
            case 5:
                preorder_print();
                break;
            case 6:
                postorder_print(root);
                break;

            case 7:
                insert_element();
                break;
            case 8:
                {
                    int _g;
                    cout<<"\nEnter the value which you want to delete :: ";
                    cin>>_g;

                    struct datapack *_u;
                    _u = tree_search(_g,root);
                    if(_u == NULL)
                    {
                        cout<<"\n      ELEMENT DON'T EXIST IN LIST\n";
                    }
                    else
                    {
                        tree_delete(_u);
                    }
                }
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
    cout<<"2.To find Predecessor"<<endl;
    cout<<"3.To Search a number"<<endl;
    cout<<"4.Print data in In-order way"<<endl;
    cout<<"5.Print data in Pre-order way"<<endl;
    cout<<"6.Print data in Post-order way"<<endl;
    cout<<"7.To Insert an element"<<endl;
    cout<<"8.To Delete an element"<<endl;
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
         if(temp->key > num)
         {
             temp->left = storage;
         }
         else
         {
             temp->right = storage;
         }
     }

}


void tree_delete(struct datapack *node)
{
    if(node->left == NULL)
    {
        ///it's simple just transplant node with it's right child
        transplant(node,node->right);
    }
    else if(node->right == NULL)
    {
        ///it's simple just transplant node with it's left child
        transplant(node,node->left);
    }
    else
    {
        struct datapack *temp;
        temp = tree_minimun(node->right);
        if(temp->parent != node)
        {
            transplant(temp,temp->right);
            temp->right = node->right;
            temp->right->parent = temp;
        }
        transplant(node,temp);
        temp->left = node->left;
        temp->left->parent = temp;
    }
    delete(node);
}

void transplant(struct datapack *u,struct datapack *v)
{
    if(u->parent == NULL)
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
    if(v != NULL)   ///v null doesn't mean key value in it , it simply means that it s pointing to something and it exist
    {
        v->parent = u->parent;
    }
}

///printing area

void inorder_print(struct datapack *point)
{
    //cout<<"\nin different function check root key -->"<<root->key<<endl;
    struct datapack *temp = point;
    if(temp==NULL)
    {
       // cout<<"it's null";
        //nothing
        if(root==NULL)
        {
            cout<<"it's null\n";
        }
    }
    else
    {
        inorder_print(temp->left);
        cout<<temp->key<<" --> ";
        inorder_print(temp->right);
    }
}

void inorder_print_iterative(struct datapack *root) {
    if(root == NULL) {
        return;
    }
    struct datapack *_stack[50];
    int top = -1;
    while(true) {
        if(root != NULL) {
            _stack[++top] = root;
            root = root->left;
        } else {
            if(top<0) break;//going out of while
            root = _stack[top];
            --top;
            cout<<root->data<<" ";
            root = root->right;
        }
    }
    cout<<endl;
    /** If using STL
    if(root == NULL) {
        return;
    }
    stack<datapack *> s;
    while(true) {
        if(root != NULL) {
            s.push(root);
            root = root->left;
        } else {
            if(s.empty()) break;//going out of while
            root = s.top();
            s.pop();
            cout<<root->data<<" ";
            root = root->right;
        }
    }

    */

}

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
        cout<<_stack[top]->key<<"  -->  ";
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


void postorder_print(struct datapack *point)
{
    struct datapack *temp = point;
    if(temp==NULL)
    {
       // cout<<"it's null";
        //nothing
        if(root==NULL)
        {
            cout<<"it's null\n";
        }
    }
    else
    {
        inorder_print(temp->left);
        inorder_print(temp->right);
        cout<<temp->key<<" --> ";
    }
}


/// left to make


int predecessor()
{
    cout<<"\n  YOU HAVE TO MAKE THIS PART \n"<<endl;
}
