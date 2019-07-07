#include <stdio.h>
#include <stdlib.h>

//----------------------------estructuras---------------------------
typedef struct tree_node {
   char data;
   struct tree_node *left;
   struct tree_node *right;
}tree_node;

//-------------------------variables globales-----------------------
//creando raiz
tree_node* raiz;
//labels
char labels[5] = {'A', 'B','C','D','E'};
//matriz de adyacencia
int graph[5][5] = {
                          {-1, 2, -1, 6, -1},
                          {2, -1, 3, 8, 5},
                          {-1, 3, -1, -1, 7},
                          {6, 8, -1, -1, 9},
                          {-1, 5, 7, 9, -1}
                      };
int cantidad_nodos;
int enlaces[25][3];
int max, origen, destino;
int bandera=0;
int T[5]={-1,-1,-1,-1,-1};

//-----------------------prototipos de funciones------------------
void crear_enlaces();
void buscar_max();
void insert_node(char origen, char destino);
void aumentar();
void pre_order(tree_node* raiz);
int ifNodeExists(tree_node* node, char key, char destino);

//--------------------------------MAIN-------------------------------
int main()
{
  //crear el primer nodo de forma arbitraria, parte con A
  raiz = (tree_node*)malloc(sizeof(tree_node*));
  raiz->data='A';

  //cantidad de nodos en el arbol=1
  cantidad_nodos=1;
  T[0]=0;

  //crea matriz de enlaces, ve que nodo incluir, o bien si esta vacia
  crear_enlaces();
  buscar_max();
  if(max==0)
  {
    raiz=NULL;
    return 0;
  }
  insert_node(labels[origen], labels[destino]);
  pre_order(raiz);
  printf("\n\n");
  //aquí ya tiene A y D

  for(int n=0; n<3;n++)
  {
    aumentar();
    pre_order(raiz);
    printf("\n\n");
  }
}//------------------------FIN DE MAIN-----------------------------

//--------------------------crear enlaces---------------------------
void crear_enlaces()
{
  //matriz que contendra todos los enlaces
  for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            enlaces[i][j]=-1;
        }
    }

  //recorriendo graph para llenar matriz enlaces
  int z=0;
  for(int i=0;i<5;i++)
  {
    for(int j=0; j<5; j++)
    {
      if(graph[i][j]!=-1)
      {
        enlaces[z][0]=i;
        enlaces[z][1]=j;
        enlaces[z][2]=graph[i][j];
        z++;
      }
    }
  }
  /*
  //displaying matriz enlaces completa
      for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                printf("%d\t", enlaces[i][j]);
            }
            printf("\n");
        }*/
}

//-----------------------buscar max--------------------------------
void buscar_max()
{
  max=0;
  origen=-1;
  destino=-1;
  for (int i = 0; i < 25; i++)
    {
      if(enlaces[i][0]==(cantidad_nodos-1))
      {
        if(enlaces[i][2]>max)
        {
          max=enlaces[i][2];
          origen=enlaces[i][0];
          destino=enlaces[i][1];
        }
      }
    }
  printf("Maximo es: %d, desde nodo %c hacia nodo %c\n", max,  labels[origen], labels[destino]);
}

//------------------------insert node------------------------------
void insert_node(char origen, char destino)
{
  printf("Funcion insertando nodo: origen %c, destino %c\n", origen, destino);

  //caso en que el origen es la raiz
  if(raiz->data==origen)
  {
    if(raiz->left==NULL)
    {
      raiz->left=(tree_node*)malloc(sizeof(tree_node*));
      raiz->left->data=destino;
    }
    else
    {
      raiz->right=(tree_node*)malloc(sizeof(tree_node*));
      raiz->right->data=destino;
    }
  }
  //sino debe recorrer el arbol hasta que encuentre el nodo
  else 
  { 
   ifNodeExists(raiz,origen, destino);
  }
}

//---------------------------aumentar-------------------------------
void aumentar()
{
  cantidad_nodos++;
  T[cantidad_nodos-1]=destino;

      //borrar enlaces con nodos ya incluidos
      for(int i=0; i<25;i++)
      {
        for(int t=0; t<(cantidad_nodos); t++)
        {
          if(enlaces[i][1]==T[t])
          {
            enlaces[i][0]=-1;
            enlaces[i][1]=-1;
            enlaces[i][2]=-1;
          }
        }
      }
      /*
      //displaying matriz enlaces
      for (int i = 0; i < 25; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                printf("%d\t", enlaces[i][j]);
            }
            printf("\n");
        }*/
        
      //busca el maximo de las combinaciones disponibles
      max=0;
      origen=-1;
      destino=-1;
      for (int i = 0; i < 25; i++)
        {
          for(int t=0; t<(cantidad_nodos);t++)
          {
            if(enlaces[i][0]==T[t])
            {
              if(enlaces[i][2]>max)
              {
                max=enlaces[i][2];
                origen=enlaces[i][0];
                destino=enlaces[i][1];
              }
            }
          }
        }
      printf("Maximo es: %d, desde nodo %c hacia nodo %c\n", max,  labels[origen], labels[destino]);

      insert_node(labels[origen], labels[destino]);
}

//--------------------------pre-order--------------------------------
void pre_order(tree_node* raiz)
{
    if(raiz == NULL)
    {
      return;
    }
    printf("[%c]", raiz->data);
    pre_order(raiz->left);
    pre_order(raiz->right);
}

int ifNodeExists(tree_node* node, char key, char destino)
{ 
    if (node == NULL) 
        return 0; 
  
    if (node->data == key) 
    {
      if(node->left==NULL)
      {
        node->left=(tree_node*)malloc(sizeof(tree_node*));
        node->left->data=destino;
      }
      else
      {
        node->right=(tree_node*)malloc(sizeof(tree_node*));
        node->right->data=destino;
      }
       return 1; 
    }

    /* then recur on left sutree */
    int res1 = ifNodeExists(node->left, key, destino); 
  
    /* now recur on right subtree */
    int res2 = ifNodeExists(node->right, key, destino); 
  
    return res1 || res2; 
} 
