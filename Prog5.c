#include <stdio.h>
#include <limits.h>

int minKey(int key[], int visited[], int V)
{
    int min = INT_MAX, minIndex = -1;
    for (int i = 0; i < V; i++)
        if (!visited[i] && key[i] < min)
            min = key[i], minIndex = i;
    return minIndex;
}

void primMST(int graph[100][100], int V)
{
    int parent[100], key[100], visited[100] = {0};
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX;
    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minKey(key, visited, V);
        visited[u] = 1;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && !visited[v] && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    int total = 0;
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
    {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
        total += graph[i][parent[i]];
    }
    printf("Total weight of MST: %d\n", total);
}

int main()
{
    int V, E, u, v, w, graph[100][100] = {0};
    printf("Enter number of vertices: ");
    scanf("%d", &V);
    printf("Enter number of edges: ");
    scanf("%d", &E);
    printf("Enter the edges (u v w):\n");
    for (int i = 0; i < E; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }
    primMST(graph, V);
    return 0;
}
