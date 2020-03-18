typedef struct tree_node* tree_branch;
struct tree_node  {
    char line[20];
    int count;
    tree_branch left;
    tree_branch right;
};
int search_tree(tree_branch ,char*);
int find_count(tree_branch , char*);
int add_node_tree(tree_branch *,char*);
void increase_count(tree_branch,char*);
void destroy_tree(tree_branch);