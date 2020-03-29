#include <stdlib.h>
#include <string.h>
typedef struct tree_node* tree_branch;
struct tree_node  {
    char line[20];
    int count;
    tree_branch left;
    tree_branch right;
};
int search_tree(tree_branch root,char* line)  {
    if (root==NULL)  {
        return 0;
    }
    if (strcmp(line,root->line)==0)  {
        return 1;
    }
    else if (strcmp(line,root->line)>0)  {
        search_tree(root->right,line);
    }
    else  {
        search_tree(root->left,line);
    }
}
int find_count(tree_branch root,char* line)  {
    if (strcmp(line,root->line)==0)  { 
        return root->count;
    }
    else if (strcmp(line,root->line)>0)  {
        find_count(root->right,line);
    }
    else  {
        find_count(root->left,line);
    }
}
void add_node_tree(tree_branch *root,char*line)  {
    if (*root==NULL)  {
        *root=malloc(sizeof(struct tree_node));
        (*root)->count=0;
        (*root)->left=NULL;
        (*root)->right=NULL; 
        strcpy((*root)->line,line);   
    }
    else if (strcmp(line,(*root)->line)>0)  {
        add_node_tree(&(*root)->right,line);
    }
    else  {
        add_node_tree(&(*root)->left,line);
    }
}
void increase_count(tree_branch root,char*line)  {
    if (strcmp(line,root->line)==0)  {
        root->count++;
        return ;
    }
    else if (strcmp(line,root->line)>0)  {
        increase_count(root->right,line);
    }
    else  {
        increase_count(root->left,line);
    }
}
void destroy_tree(tree_branch root)  {
    if (root==NULL)  {
        return;
    }
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root);
}
