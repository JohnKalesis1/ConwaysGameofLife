#include <stdio.h>
#include "binary_tree.h"
int main(void)  {
    char line[20];
    tree_branch root;
    root=NULL;
    while (fgets(line,20,stdin)!=NULL)  { 
        if (line[0]!='\n')  {
            if (search_tree(root,line)==1)  {  // αν υπαρχει ηδη η γραμμη στο δεντρο
                increase_count(root,line);     // αυξανουμε τον μετρητη της κατα 1
            }
            else  {
                add_node_tree(&root,line);   // αλλιως καταχωρουμε τη γραμμη στο δεντρο με μετρητη 0
            }
            printf("%s Line occurence : %d \n",line,find_count(root,line));
        }
    }
    destroy_tree(root); // αποδεσμευση μνημης δεντρου
    return 0;
}