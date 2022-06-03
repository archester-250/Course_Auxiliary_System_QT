#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int edges[200][200];    
int distance[200];          
int visited[200];       

int dijkstra(int n, int m)
{
    for (int i = 1; i <= n; i++) {              
        int index = -1;                        
        distance[1] = 0;                            
        for (int j = 1; j <= n; j++) {          
            if (!visited[j] && (index == -1 || distance[j] < distance[index])) {                 
                index = j;
            }
        }

        visited[index] = 1;                     
        for (int j = 1; j <= n; j++) {
            if (distance[index] + edges[index][j] < distance[j]) { 
                distance[j] = distance[index] + edges[index][j];
            }
        }
    }

    if (distance[n] == 0x3f3f3f3f) {  //如果没有到n点的路径，则返回-1
        return -1;
    }
    return distance[n];
}

// int main()
// {
//     memset(edges, 0x3f, sizeof(edges));
//     int n, m;

//     scanf("%d %d", &n, &m);
//     for (int i = 0; i < m; i++) {
//         int start, end, d;
//         scanf("%d %d %d", &start, &end, &d);
//         edges[start][end] = edges[start][end] > d ? d : edges[start][end];  
//     }

//     memset(distance, 0x3f, sizeof(distance));  
//     memset(visited, 0, sizeof(visited)); // 初始化所有的点都没有被踢出
//     printf("%d\n", dijkstra(n, m));
//     return 0;
// }
