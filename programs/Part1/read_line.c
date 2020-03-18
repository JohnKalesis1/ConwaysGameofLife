#include <stdio.h>
#include "binary_tree.h"
int main(void)  {
    char line[20];
    tree_branch root;
    root=NULL;
    while (fgets(line,20,stdin)!=NULL)  {
        if (line[0]!='\n')  {
            if (search_tree(root,line)==1)  {
                increase_count(root,line);
            }
            else  {
                add_node_tree(&root,line);
            }
            printf("%s Line occurence : %d \n",line,find_count(root,line));
        }
    }
    destroy_tree(root);
    return 0;
}