#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <stdlib.h> 
#include <stdio.h>
#include <time.h>
#include "catch.hpp" 
#include "Prueba4.h"


int correctArray(int A[], int B[], int N){
    // Asumiendo que son igual de largo
    for(int i =0; i<N ; i++){
        if(A[i] != B[i]) return 0;
    }
    return 1;
}

struct tree_node* newTreeNode(int data){
    struct tree_node* node = (struct tree_node*)malloc(sizeof(struct tree_node)); 
    node->data = data;
    node->left = NULL; 
    node->right = NULL; 
    return(node);
}

struct list_node* newListNode(char data){
    struct list_node* node = (struct list_node*)malloc(sizeof(struct list_node)); 
    node->data = data;
    node->next = NULL; 
    return(node);
}

int compare_trees(struct tree_node* a, struct tree_node* b){ 
    /*1. both empty */
    if (a==NULL && b==NULL) 
        return 1; 
  
    /* 2. both non-empty -> compare them */
    if (a!=NULL && b!=NULL) 
    { 
        return
        ( 
            a->data == b->data && 
            compare_trees(a->left, b->left) && 
            compare_trees(a->right, b->right) 
        ); 
    } 
      
    /* 3. one empty, one not -> false */
    return 0; 
}
int compare_list(struct list_node *list1, struct list_node *list2)  
{     
    // Traverse both lists. Stop when either end of a linked  
    // list is reached or current characters don't match 
    while (list1 && list2 && list1->data == list2->data)  
    {          
        list1 = list1->next; 
        list2 = list2->next; 
    } 
      
    //  If both lists are not empty, compare mismatching 
    //  characters 
    if (list1 && list2)  
        return (list1->data > list2->data)? 0: 0; 
  
    // If either of the two lists has reached end 
    if (list1 && !list2) return 0; 
    if (list2 && !list1) return 0; 
      
    // If none of the above conditions is true, both  
    // lists have reached end  
    return 1; 
} 
TEST_CASE( "Parte 1.1", "[MaxST]" ) {
    int graph[5][5] = {
                        {-1, 2, -1, 6, -1},
                        {2, -1, 3, 8, 5},
                        {-1, 3, -1, -1, 7},
                        {6, 8, -1, -1, 9},
                        {-1, 5, 7, 9, -1}
                    };
    struct tree_node * root = newTreeNode('A');
    root->left = newTreeNode('D');
    root->left->left = newTreeNode('B');
    root->left->right = newTreeNode('E');
    root->left->right->left = newTreeNode('C');
    REQUIRE( compare_trees(root, MaxST(graph, 5)) == 1 );

}
TEST_CASE( "Parte 1.2", "[MaxST]" ) {
    struct tree_node* empty_node = NULL;
    int graph_2[5][5];
    REQUIRE( compare_trees(empty_node, MaxST(graph_2, 0)) == 1 );
}
TEST_CASE( "Parte 1.3", "[MaxST]" ) {
    int graph3[5][5] = {
                        {0, 45, 6, 2, 1},
                        {45, -1, 3, -1, 9},
                        {6, 3, -1, 1, -1},
                        {2, -1, 1, -1, 99},
                        {1, 9, -1, 99, -1}
                    };
    struct tree_node * root = newTreeNode('A');
    root->left = newTreeNode('B');
    root->right = newTreeNode('C');
    root->left->left = newTreeNode('E');
    root->left->left->left = newTreeNode('D');
    REQUIRE( compare_trees(root, MaxST(graph3, 5)) == 1 );
}
TEST_CASE( "Parte 2.1", "[Amigos_Sugeridos]" ) {
    int graph[5][5] = {
                        {-1, 2, -1, 6, -1},
                        {2, -1, 3, 8, 5},
                        {-1, 3, -1, -1, 7},
                        {6, 8, -1, -1, 9},
                        {-1, 5, 7, 9, -1}
                    };
    struct tree_node * root = newTreeNode('A');
    root->left = newTreeNode('D');
    root->left->left = newTreeNode('B');
    root->left->right = newTreeNode('E');
    root->left->right->left = newTreeNode('C');

    struct list_node *rootList =newListNode('D');

    REQUIRE( compare_list(rootList, Amigos_Sugeridos(graph, 5,root,'C')) == 1 );
}
TEST_CASE( "Parte 2.2", "[Amigos_Sugeridos]" ) {
    int graph3[5][5] = {
                        {0, 45, 6, 2, 1},
                        {45, -1, 3, -1, 9},
                        {6, 3, -1, 1, -1},
                        {2, -1, 1, -1, 99},
                        {1, 9, -1, 99, -1}
                    };
    struct tree_node * root = newTreeNode('A');
    root->left = newTreeNode('B');
    root->right = newTreeNode('C');
    root->left->left = newTreeNode('E');
    root->left->left->left = newTreeNode('D');

    struct list_node *rootList =newListNode('C');
    rootList->next=newListNode('D');

    REQUIRE( compare_list(rootList, Amigos_Sugeridos(graph3, 5,root,'B')) == 1 );
}