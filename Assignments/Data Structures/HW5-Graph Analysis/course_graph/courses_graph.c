/* Miguel Cervantes 1002045172 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COURSE_LENGTH 31
#define MAX_FILE_LENGTH 31
#define MAX_LINE_LENGTH 1001
#define MAX_COURSES 51


int ** alloc_2d(int rows, int columns)
{
   int row, col;
   // allocate space to keep a pointer for each row
   int ** table = (int**)calloc(rows , sizeof(int *));

   // VERY IMPORTANT: allocate the space for each row
   for (row = 0; row < rows; row++)
      table[row] = (int*)calloc(columns , sizeof(int));

   return table;
}

void free_2d(int ** array, int rows, int columns)
{
   int row;
   // VERY IMPORTANT: free the space for each row
   for (row = 0; row < rows; row++)
      free(array[row]);

   // free the space with the pointer to each row.
   free(array);
}

// a graph where edges are recorded as a matrix
struct struct_graph
{
   int undirected; // value 1 means it is undirected, value other than 1 means it is directed.
   int N;    // number of vertices
   int ** E;  // edges
};

typedef struct struct_graph * graphPT;

// creates a graphPT with the specified number of vertices 
/* Edit: Added a int adj_matrix parameter in order to intialize edges*/
graphPT newGraph(int N, int undirected, int adj_matrix[MAX_COURSES][MAX_COURSES])
{
   graphPT result = (graphPT)malloc(sizeof(*result));
   result->undirected = undirected;  
   result->N = N;
   result->E = alloc_2d(N,N);   
   
   // initialize edges with passed in adj_matrix
   int i, j;
   for (i = 0; i < N; i++)
   {
      for (j = 0; j < N; j++)
      {
         result->E[i][j] = adj_matrix[i][j];
      }
   }
   
   return result;
}

// deallocates the memory allocated to graph g.
void destroyGraph(graphPT g)
{
   if (g == NULL) return;
   free_2d(g->E, g->N, g->N);
   free(g);
}

/* Fills the adjacency matrix using the passed in file handler, line array for reading in with fgets, the number of courses for iteration purposes,
   the adjancency matrix to fill, and lastly the vertex array that lists each vertex in it's corresponding order 
*/
void fill_adj_matrix(FILE *assign_edges, char line[MAX_LINE_LENGTH], int num_courses, int adj_matrix[MAX_COURSES][MAX_COURSES], char vertex[MAX_COURSES][MAX_COURSE_LENGTH])
{
    int i, j;
    while(fgets(line, MAX_LINE_LENGTH, assign_edges) != NULL) 
    {
        char *token = strtok(line, " \n");
        for(i = 0; i < num_courses; i++)
        {
            if(strcmp(vertex[i], token) == 0)
            {
                token = strtok(NULL, " \n");
                while(token != NULL)
                {
                    for(j = 0; j < num_courses; j++)                   
                    {
                        if(strcmp(vertex[j], token) == 0)
                        {
                            adj_matrix[j][i] = 1;
                            break;
                        }
                    }
                    token = strtok(NULL, " \n");
                }
                break;
            }
        }
    }

}


/* Prints out the adjacency matrix*/
void print_adj_matrix(int num_courses, int adj_matrix[MAX_COURSES][MAX_COURSES]) 
{
    int i, j;
    printf("Adjacency matrix:\n");
    printf("    |");
    for(i = 0; i < num_courses; i++)
    {
        printf("%4d", i);
    }
    
    printf("\n-----");
    for (i = 0; i < num_courses; i++)
    {
        printf("----");
    }
    printf("\n");
    
    for(i = 0; i < num_courses; i++)
    {
        printf("%4d|", i);
        for(j = 0; j < num_courses; j++)
        {
            printf("%4d", adj_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}

/* Implements the DFS_visit psedocode + revised with an integer array and index value to track vertices for topological sorting*/

int DFS_visit(graphPT G, int u, char **color, int *pred, int *res, int *index)
{
    color[u] = "GREY";

    int y;
    for (y = 0; y < G->N; y++)
    {
        if(G->E[u][y])
        {
            if(strcmp(color[y], "WHITE") == 0)
            {
                pred[y] = u;
                if (DFS_visit(G, y, color, pred, res, index))
                {
                    return 1;
                }
            }
            else if(strcmp(color[y], "GREY") == 0)
            {
                return 1;
            }

        }
    }
    color[u] = "BLACK";
    res[(*index)++] = u;

    return 0;
}

/* Implements DFS algorithm along with the passed in res int array to track vertices in reverse topological order*/
int DFS(graphPT G, int *res)
{
    char **color = (char **)malloc(G->N * sizeof(char *));
    int *pred = (int *)malloc(G->N * sizeof(int));
    int index = 0;

    int u;
    for (u  = 0; u < G->N; u++) {
        color[u] = "WHITE";
        pred[u] = -1;
    }

    for (u = 0; u < G->N; u++) {
        if (strcmp(color[u], "WHITE") == 0) {
            if (DFS_visit(G, u, color, pred, res, &index)) {
                free(color);
                free(pred);
                return 1;
            }
        }
    }

    free(color);
    free(pred);

    return 0;
} 



int main()
{
    char file_name[MAX_FILE_LENGTH];
    char line[MAX_LINE_LENGTH];
    char vertex[MAX_COURSES][MAX_COURSE_LENGTH];
    int num_courses = 0;
    int adj_matrix[MAX_COURSES][MAX_COURSES] = {0};


    printf("Enter filename: ");
    scanf("%s", file_name);

    /* Opens the input file. If it fails to open, it prints an error message and exits. */ 
    FILE *input_file = fopen(file_name, "r");
    if(input_file == NULL)
    {
        printf("Could not open file %s. Exit\n\n", file_name);
        printf("Failed to read from file. Program will terminate.\n");
        return 0;
    }

    /* Read in first course name from each line until reaching EOF. Also increments variable num_courses to keep track of the # of courses.*/
    while(fgets(line, MAX_LINE_LENGTH, input_file) != NULL) 
    {
        sscanf(line, " %s", vertex[num_courses]);
        num_courses++;
    }
    
    /* Prints out # of vertices and the vertex they correspond to. Despite the output, the graph isn't created until
       much later so that the adjacency matrix may be used to initialize the corresponding edges (Line 254)
    */
    printf("Number of vertices in built graph:  N = %d\n", num_courses);
    int i, j;
    printf("Vertex - course name correspondence\n");
    for(i = 0; i < num_courses; i++)
    {
        printf("%d - %s\n", i, vertex[i]);
    }
    printf("\n");
    fclose(input_file);

    /* Opens the input file a second time to assign edges and calls functions fill_adj_matrix() to fill the adjacency matrix, and 
       print_adj_matrix() to print the adjacency matrix 
    */
    FILE *assign_edges = fopen(file_name, "r");
    fill_adj_matrix(assign_edges, line, num_courses, adj_matrix, vertex);
    fclose(assign_edges);
    print_adj_matrix(num_courses, adj_matrix);

    /* Creates a new graph using the number of courses, a 0 to indicate a directed graph, and the adj_matrix to initalize edges*/
    graphPT G = newGraph(num_courses, 0, adj_matrix);
    int res[G->N];

    /* Call DFS and sets its return value to the variable cycle. If a cycle is found, cycle = 1, else cycle = 0
       Additionally, the res array is passed into DFS to detemine the vertices for topological sorting
    */
    int cycle = DFS(G, res);

    /* Handles cases for the return value of DFS. If there is no cycle it prints the topological order of the vertices
       by printing the array in reverse order.
    */
    if(cycle)
    {
        printf("There was at least one cycle. There is no possible ordering of the courses.\n\n");
    }
    else
    {
        j = 0;
        printf("Order in which to take courses: \n");
        for (int i = G->N - 1; i >= 0; i--)
        {
            printf("%d. - %s (corresponds to graph vertex %d)\n", j, vertex[res[i]], res[i]);
            j++;
        }
        printf("\n");
    }

    /* Call destroy graph to free memory before exiting */
    destroyGraph(G);

    return 0;
}