extern struct tree_node {
   char data;
   struct tree_node *left;
   struct tree_node *right;
}tree_node;

extern struct list_node {
   char data;
   struct list_node *next;
}list_node;

extern struct tree_node* MaxST(int graph[5][5], int size);
extern struct list_node* Amigos_Sugeridos(int graph[5][5],int size, struct tree_node *tree, char name);