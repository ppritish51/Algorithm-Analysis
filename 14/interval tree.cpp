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
void insert_data(float x,float y);
void rb_insert_fix_up(struct datapack *x);   ///will take pointer to insert node
void left_rotate(struct datapack *x);
void right_rotate(struct datapack *x);
void inorder_print(struct datapack *point);

datapack* tree_minimun(struct datapack *node);
datapack* tree_maximum(struct datapack *node);
datapack* search_exact_interval(float x,float y,struct datapack *node);
void delete_data(struct datapack *z);
void transplant(struct datapack *u,struct datapack *v);
void delete_fix_up(struct datapack *x);

datapack* search_interval(float x,float y);
void max_fixup(struct datapack *storage);

#define RED 0
#define BLACK 1

struct datapack
{
    int color;
    float x_int_low;
    float x_int_high;
    float x_max;
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
    nil->x_int_high = -100000;
    nil->x_int_low = -100000;
    nil->x_max = -100000;
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
                    float x,y;
                    cout<<"Enter the lower bound :: ";
                    cin>>x;
                    cout<<"Enter the upper bound :: ";
                    cin>>y;
                    if(x>y)
                    {
                        cout<<"\nwrong interval entered ! try different choice\n";
                        break;
                    }
                    insert_data(x,y);
                }
                break;
            case 2:
                {
                    float x,y;
                    cout<<"enter the lower bound of number you want to delete ::";
                    cin>>x;
                    cout<<"enter the upper bound of number you want to delete ::";
                    cin>>y;
                    if(x>y)
                    {
                        cout<<"\nwrong interval entered ! try different choice\n";
                        break;
                    }
                    struct datapack *_u;
                    _u = search_exact_interval(x,y,root);
                    if(_u == nil)
                    {
                        cout<<"\n      INTERVAL DON'T EXIST IN LIST\n";
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
            case 4:
                {
                    struct datapack *_u;
                    int x,y;
                    cout<<"Enter the lower bound ::";
                    cin>>x;
                    cout<<"Enter the upper bound ::";
                    cin>>y;
                    if(x>y)
                    {
                        cout<<"\nwrong interval entered ! try different choice\n";
                        break;
                    }
                    _u = search_interval(x,y);
                    if(_u == nil)
                        cout<<"NO INTERVAL MATCH"<<endl;
                    else
                        cout<<"[ "<<x<<" , "<<y<<" ] has intersection with interval :: [ "<<_u->x_int_low<<" , "<<_u->x_int_high<<" ]\n";
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
    cout<<"  PRESS THE RESPECITVE x_int_low TO TAKE THE FOLLOWING ACTION"<<endl;
    cout<<"0.To print Instructions"<<endl;
    cout<<"1.To Insert Interval"<<endl;
    cout<<"2.To Delete an Interval"<<endl;
    cout<<"3.To print IN-ORDER"<<endl;
    cout<<"4.To Find an Interval for an Element"<<endl;
    cout<<"DEFAULT : TO EXIT"<<endl;
}


void insert_data(float x,float y)
{
     struct datapack *temp ;
     struct datapack *storage = new datapack;
     struct datapack *_find = root;
     if(_find == nil)                ///it's first element
     {
         root = storage;
         root->parent = nil;
         storage->x_int_low = x;
         storage->x_int_high = y;
         storage->x_max = y;
         storage->left = nil;
         storage->right = nil;
         storage->color = BLACK;
     }
     else
     {
         while(_find!=nil)
         {
             temp = _find;
             if(_find->x_int_low > x)
             {
                 _find = _find->left;
             }
             else
             {
                 _find = _find->right;
             }
         }
         storage->x_int_low = x;
         storage->x_int_high = y;

         storage->left = nil;
         storage->right = nil;
         storage->parent = temp;
         storage->color = RED;
         if(temp->x_int_low > storage->x_int_low)
         {
             temp->left = storage;
         }
         else
         {
             temp->right = storage;
         }
     }
     max_fixup(storage);
     rb_insert_fix_up(storage);
}
void max_fixup(struct datapack *storage)
{
    while(storage != nil)
    {
        int k;
        if(storage->left->x_max > storage->right->x_max)
        k= storage->left->x_max;
        else
            k = storage->right->x_max;
        if(k>storage->x_int_high)
            storage->x_max = k;
        else
            storage->x_max = storage->x_int_high;
        storage = storage->parent;
    }
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
    y->x_max = x->x_max;
    int k;
    if(x->x_int_high > x->left->x_max)
        k = x->x_int_high ;
    else
        k = x->left->x_max;
    if(k>x->right->x_max)
        x->x_max = k;
    else
        x->x_max = x->right->x_max;

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
    y->x_max = x->x_max;
    int k;
    if(x->x_int_high > x->left->x_max)
        k = x->x_int_high ;
    else
        k = x->left->x_max;
    if(k>x->right->x_max)
        x->x_max = k;
    else
        x->x_max = x->right->x_max;

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
    if(z->parent == nil)  //if we are deleting root
    {
        max_fixup(y);
    }
    else
    {
        max_fixup(x->parent);
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

datapack* search_exact_interval(float x,float y,struct datapack *node)
{
    struct datapack *temp,*_z;
    temp = node;
    if(temp == nil)
    {
        return nil;
    }
    else if(x == temp->x_int_low)
    {
        if(temp->x_int_high == y)
        {
            return temp;
        }
        else
        {
            _z=search_exact_interval(x,y,temp->left);
            if(_z == nil)
                return search_exact_interval(x,y,temp->right);
            else
                return _z;
        }
    }
    else if(x < temp->x_int_low)
    {
        return search_exact_interval(x,y,temp->left);
    }
    else
    {
        return search_exact_interval(x,y,temp->right);
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
datapack* search_interval(float x,float y)
{
    struct datapack *node = root;
    while(node !=nil && ((y<node->x_int_low)||(x>node->x_int_high)) )
    {
        if(node->left != nil && node->left->x_max >= x )
        {
            node =node->left;
        }
        else
        {
            node = node->right;
        }
    }
    return node;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///printing area

void inorder_print(struct datapack *point)
{
    //cout<<"\nin different function check root x_int_low -->"<<root->x_int_low<<endl;
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
        cout<<"[ "<<temp->x_int_low<<" , "<<temp->x_int_high<<" ] ( "<<temp->x_max<<" ) -->  ";
        /*if(temp->color == RED)
            cout<<"RED ) -->  ";
        else
            cout<<"BLACK ) -->  ";*/
        inorder_print(temp->right);
    }
}

