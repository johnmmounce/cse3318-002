#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 30
#define MAX_LINE_LENGTH 1000

struct graph
{
    int edge;
    int color;
    int pred;
};

enum color
{
    WHITE,
    GRAY,
    BLACK
};

void DFS(int adj_matrix[][1024], int num_verticies)
{
    // 1 = white, 2 = gray, 3 = black
    int result[num_verticies];
    int color[] = {1, 2, 3};
    for (int i = 0; i < num_verticies; i++)
    {
    }
}

void DFS_visit(int adj_matrix[][1024], int vertex, int color, int pedecessor)
{
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
    classes[num_vertices] = malloc((strlen(target) + 1) * sizeof(char));
    strcpy(classes[num_vertices], target);
    return num_vertices;
}
void ReverseStringArray(char *strarr[], int n)
{
    char *temp;
    int end = n - 1;
    for (int i = 0; i < end + 1; i++)
    {
        temp = strarr[i];
        strarr[i] = strarr[end];
        strarr[end] = temp;
        end--;
    }
}

int main()
{
    char input_line[MAX_LINE_LENGTH]; // where we store the current line being read/processed
    char *classes[MAX_LINE_LENGTH];   // where we will store all classes, no duplicates
    char filename[MAX_LENGTH];        // where file name is stored
    char *token;                      // token being used to parse data; blank space and \n

    int num_classes = 0; // total num of classes from file, no duplicate counts
    int pre_req[1024][1024] = {0};
    // int result[];

    FILE *fp; // file pt for opening and reading from file

    printf("enter file name: "); // gettting file name from user
    scanf("%s", filename);

    fp = fopen("slides.txt", "r"); // open file for reading and check if fp is NULL
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
    for (int j = 0; j < num_classes; j++)
    {
        printf("%s\n", classes[j]);
    }

    fseek(fp, 0, 0);

    //     // // start reading from file, collect all classes, no extra spaces, no duplicates.
    //     // // store class names into classes array.
        int i = 0;
        int j;
        while (fgets(input_line, MAX_LINE_LENGTH, fp))
        {
            int class_vertex = -1;
            // input_line[strcspn(input_line, "\n")] = '\0'; // remove \n character
            token = strtok(input_line, " \n"); // tokenize the data based on spaces to seperate a multi-class line

            while (token != NULL)
            {
                int vertex = get_vertex(classes, num_classes, token);
                // printf("%s, %d\n", token, vertex);
                if (class_vertex == -1)
                {
                    class_vertex = vertex;
                }
                else
                {
                    pre_req[vertex][class_vertex] = 1;
                    // printf("found prereq: %d  classvertex: %d\n", vertex, class_vertex);
                }
                token = strtok(NULL, " \n");
            }
        }

    //     //sort class array

    //     //enum color prereq_colors[1024][1024] = {WHITE};
    //     // for(int i = 0; i < num_classes; i++){
    //     //     for(int j = 0; j < num_classes; j++){
    //     //         if(pre_req[i][j] == 1){
    //     //         prereq_colors[i][j] = WHITE;
    //     //     }
    //     //     }
    //     // }

    //     // int prereq_pred[1024][1024];
    //     // for(int i = 0; i < num_classes; i++){
    //     //     for(int j = 0; j < num_classes; j++){

    //     //         prereq_pred[i][j] = 0;

    //     //     }
    //     // }

    //     //int d[1024][1024];

    //     // DFS traversal of the graph

        printf("number of verticies: n = %d\n", num_classes);
        printf("Vertex - course name correspondence\n");
        for (int i = 0; i < num_classes; i++)
        {
            printf("%d - %s\n", i, classes[i]);
        }

        // print adj array
        printf("Adjacency matrix:\n");
        printf("    |");
        for (int i = 0; i < num_classes; i++)
        {
            printf("%4d", i);
        }
        printf("\n");
        // print divider
        for (int i = 0; i < num_classes + 1; i++)
        {
            printf("-----");
        }
        printf("\n");
        for (int i = 0; i < num_classes; i++)
        {
            printf("   %d|", i);
            for (int j = 0; j < num_classes; j++)
            {
                printf("%4d", pre_req[i][j]);
            }
            printf("\n");
        }

    //  for (int i = 0; i < num_classes; i++)
    //     {
    //         printf("%d. - %s (corresponds to vertex %d)\n", i + 1, classes[i], i);
    //     }

    //     ReverseStringArray(classes, num_classes);
    //     printf("\n");
    //     printf("\nOrder in which to take courses: \n");
    //     for (int i = 0; i < num_classes; i++)
    //     {
    //         printf("%d. - %s (corresponds to vertex %d)\n", i + 1, classes[i], i);
    //     }

    fclose(fp);

    return 0;
}
