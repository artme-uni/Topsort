#include <stdio.h>
#include <stdlib.h>

typedef struct edge
{
    int begin;
    int end;
} edge;

int cnt = 0;

int painting(edge *graph, int vert_number, int cnt_vert, int cnt_edge, int *colors, int *stack)
{
    if (colors[vert_number] == 1)
        return 1;
    colors[vert_number] = 1;

    for (int i = 0; i < cnt_vert; i++)
    {
        if (graph[i].begin == vert_number && colors[graph[i].end] != 2)
        {
            if (painting(graph, graph[i].end, cnt_vert, cnt_edge, colors, stack) == 1)
                return 1;
        }
    }
    stack[cnt++] = vert_number;
    colors[vert_number] = 2;

    return 0;
}

int main()
{
    int cnt_vert;
    int cnt_edge;

    scanf("%d", &cnt_vert);
    if (cnt_vert < 0 || cnt_vert > 1000)
    {
        printf("bad number of vertices\n");
        return 1;
    }

    scanf("%d", &cnt_edge);
    if (cnt_edge < 0 || cnt_edge > ((cnt_vert) * (cnt_vert + 1)) / 2)
    {
        printf("bad number of edges\n");
        return 1;
    }

    edge *graph = calloc(sizeof(edge), cnt_edge);
    for (int i = 0; i < cnt_edge; i++)
    {
        scanf("%d %d", &graph[i].begin, &graph[i].end);

        if (graph[i].begin < 1 || graph[i].begin > cnt_vert ||
              graph[i].end < 1 || graph[i].end > cnt_vert)
        {
            printf("bad vertex\n");
            free(graph);
            return 0;
        }
    }

    int *colors = calloc(sizeof(int), cnt_vert + 1);
    int *stack = calloc(sizeof(int), cnt_vert);


    for (int i = 1; i <= cnt_vert; ++i)
    {
        if (colors[i] == 0)
        {
            if (painting(graph, i, cnt_vert, cnt_edge, colors, stack) == 1)
            {
                printf("impossible to sort\n");

                free(graph);
                free(colors);
                free(stack);
                return 0;
            }
        }
    }

    for (int i = cnt - 1; i >= 0; i--)
    {
        printf("%d ", stack[i]);
    }
    printf("\n");

    free(graph);
    free(colors);
    free(stack);
    return 0;
}