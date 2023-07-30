//John Mounce CSE3318-002
//This program will take in a file with courses and their prerequisites. 
//It will then make an adj matrix and preform DFS to report which order in which the classes needed to be take.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 30
#define MAX_LINE_LENGTH 1000

enum color
{
    WHITE,
    GRAY,
    BLACK
};

void DFS_visit(int current_vertex, int num_courses, int adj_matrix[][256], int color[], int predecessor[], int res[], int *current_res)
{
    color[current_vertex] = GRAY;
    for (int i = 0; i < num_courses; i++)
    {
        if (adj_matrix[current_vertex][i] == 1)
        {
            if (color[i] == WHITE)
            {
                predecessor[i] = current_vertex;
                DFS_visit(i, num_courses, adj_matrix, color, predecessor, res, current_res);
            }
            else if (color[i] == GRAY)
            {
                printf("There was at least one cycle. There is no possible ordering of the courses.\n\n");
                exit(1);
            }
        }
    }
    color[current_vertex] = BLACK;
    res[(*current_res)++] = current_vertex;
}

void DFS(int adj_matrix[][256], int num_classes, int res[])
{
    int color[num_classes];
    int res_idx = 0;
    int predecessors[num_classes];
    for (int i = 0; i < num_classes; i++)
    {
        color[i] = WHITE;
        predecessors[i] = -1;
    }
    for (int i = 0; i < num_classes; i++)
    {
        if (color[i] == WHITE)
        {
            DFS_visit(i, num_classes, adj_matrix, color, predecessors, res, &res_idx);
        }
    }
}

void reverse_topo_sort(int res[], int size)
{
    int temp;
    for (int i = 0; i < size / 2; i++)
    {
        temp = res[i];
        res[i] = res[size - i - 1];
        res[size - i - 1] = temp;
    }
}

int get_vertex(char *classes[], int num_vertices, char *target)
{
    for (int i = 0; i < num_vertices; i++)
    {
        if (strcmp(classes[i], target) == 0)
        {
            return i;
        }
    }
    classes[num_vertices] = malloc((strlen(target)+1) * sizeof(char));
    strcpy(classes[num_vertices], target);
    return num_vertices;
}

int main()
{
    char input_line[MAX_LINE_LENGTH]; // where we store the current line being read/processed
    char *classes[MAX_LINE_LENGTH];   // where we will store all classes, no duplicates
    char filename[MAX_LENGTH];        // where file name is stored
    char *token;                      // token being used to parse data; blank space and \n

    int num_classes = 0; // total num of classes from file, no duplicate counts
    int pre_req[256][256] = {0};
    // int result[];

    FILE *fp; // file pt for opening and reading from file

    printf("enter file name: "); // gettting file name from user
    scanf("%s", filename);

    fp = fopen(filename, "r"); // open file for reading and check if fp is NULL
    if (fp == NULL)
    {
        printf("File not found, please try again.\n");
        return -1;
    }

    while (fgets(input_line, MAX_LINE_LENGTH, fp) != NULL)
    {
        token = strtok(input_line, " \n");
        if (token != NULL)
        {
            classes[num_classes] = malloc((strlen(token) + 1) * sizeof(char));
            strcpy(classes[num_classes], token);
            num_classes++;
        }
    }
    // go back to top of file
    fseek(fp, 0, 0);

    // start reading from file, collect all classes, no extra spaces, no duplicates.
    // store class names into classes array.
    int i = 0;
    int j;
    while (fgets(input_line, MAX_LINE_LENGTH, fp))
    {
        int class_vertex = -1;
        token = strtok(input_line, " \n"); // tokenize the data based on spaces to seperate a multi-class line

        while (token != NULL)
        {
            int vertex = get_vertex(classes, num_classes, token);
            if (class_vertex == -1)
            {
                class_vertex = vertex;
            }
            else
            {
                pre_req[vertex][class_vertex] = 1;
            }
            token = strtok(NULL, " \n");
        }
    }
    // print classes with vertex
    printf("number of verticies: n = %d\n", num_classes);
    printf("Vertex - course name correspondence\n");
    for (int k = 0; k < num_classes; k++)
    {
        printf("%d - %s\n", k, classes[k]);
    }

    // print adj array
    printf("Adjacency matrix:\n");
    printf("   |");
    for (int k = 0; k < num_classes; k++)
    {
        printf("%4d", k);
    }
    printf("\n");
    // print divider
    for (int k = 0; k < num_classes + 1; k++)
    {
        printf("----");
    }
    printf("\n");
    // print classes in order read in
    for (int k = 0;k < num_classes; k++)
    {
        printf("  %d|", k);
        for (int l = 0; l < num_classes; l++)
        {
            printf("%4d", pre_req[k][l]);
        }
        printf("\n");
    }

    // define result array and call DFS and reverse the order
    int res[num_classes];
    DFS(pre_req, num_classes, res);
    reverse_topo_sort(res, num_classes);
    printf("order in which to take the classes\n");
    for (int k = 0; k < num_classes; k++)
    {
        printf("%d. %s (corresponds with vertex %d)\n", k + 1, classes[res[k]], res[k]);
    }

    // close file and free fp
    for (int k = 0; k < num_classes; k++)
    {
        free(classes[k]);
    }
    fclose(fp);

    return 0;
}
