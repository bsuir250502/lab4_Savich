#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree
{
    int info;
    struct tree *left,*right;
};

void view_menu(void)
{
    puts("1-create tree");
    puts("2-add node to the tree");
    puts("3-show tree");
    puts("4-count nodes at N level");
    puts("5-finish program");
}

char* check_input(void)
{
    char *string=(char*)calloc(6,sizeof(char));
    do {
        fgets(string,6, stdin);
        if(strlen(string)==5)
            while(getchar()!='\n');
    } while (string[0] == '\n');
    return string;
}

struct tree* create_root(struct tree *root)
{
    int input_number;
    if(root)
    {
        puts("tree has been already created");
        return(root);
    }
    if(!(root=(struct tree *) calloc(1,sizeof(struct tree))))
    {
        puts("not enough free memory");
        return NULL;
    }
    puts("enter number for adding");
    input_number=atoi(check_input());
    root->info=input_number;
    root->left=root->right=NULL;
    return(root);
}

int add(struct tree *root)
{
    struct tree *node, *current;
    int input_number,flag;
    if(!root)
    {
        puts("create tree please");
        return;
    }
            puts("enter information to node");
            input_number=atoi(check_input());
            node=root;
            flag=0;
            do
            {
                if(input_number==node->info)
                    flag=1;
                else
                {
                    if (input_number<node->info)
                    {
                        if (node->left!=NULL)
                            node=node->left;
                        else flag=1;
                    }
                    else
                    {
                        if (node->right!=NULL)
                            node=node->right;
                        else flag=1;
                    }
                }
            } while(!flag);
            if (input_number!=node->info)
            {
                if (!(current=(struct tree*) malloc(sizeof(struct tree))))
                {
                    puts("not enough free memory");
                    return;
                }
                if (input_number<node->info)
                    node->left=current;
                else node->right=current;
                current->info=input_number;
                current->left=NULL;
                current->right=NULL;
            }

}

void show(struct tree *current)
{
    if(!current)
    {
        puts("enter tree please");
        return;
    }
    if(current)
    {
        printf("node : %d\n",current->info);
        if (current->left)
            show(current->left);
        if (current->right)
            show(current->right);
    }
}

int count_el(struct tree *node,int level_number)
{
    static int level=0;
    int elements=0;
    level++;
    if(level==level_number)
    {
        elements++;
        level--;
        return elements;
    }
    if(node->left)
        elements=elements+count_el(node->left,level_number);
    if(node->right)
        elements=elements+count_el(node->right,level_number);
    level--;
    return elements;
}

void enter_level(struct tree *root)
{
    int elements,level_number;
    if(!root)
    {
        puts("enter tree please");
        return;
    }
    puts("enter the number of level");
    while(!(level_number=atoi(check_input())));
    elements=count_el(root,level_number);
    printf("\nlevel %d",level_number);
    printf("\n%d elements",elements);
}

void show_help(void)
{
    puts("create tree, add nodes to tree,count elements at N level");
}

int main(int argc, char *argv[])
{
    if(argc>1)
    {
        if(strcmp(argv[1],"-h"))
        {
            show_help();
        }
    }
    struct tree *root=NULL;
    while(1)
    {
        view_menu();
        int number=atoi(check_input());
        if(number==5)
            break;
        switch(number)
        {
            case 1: root=create_root(root); break;
            case 2: add(root); break;
            case 3: show(root); break;
            case 4: enter_level(root); break;
            default : puts("unknown command, try again"); break;
        }

    }
    return 0;
}
