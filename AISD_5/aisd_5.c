#include <stdio.h>
#include <stdlib.h>
#define N 9 //кол-во элементов графа
#define INF 9999 //обозначение бесконечности

//структура графа
struct Graph{
    int matrix[N][N]; //матрица смежности
};

//функция для создания графа
struct Graph* creategraph(int adjacencyMatrix[N][N]){
    //выделение памяти под граф
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    //заполняем входными данными
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            graph->matrix[i][j] = adjacencyMatrix[i][j];
        }
    }
    return graph;//возвращаем указатель на созданный граф
}

// функция для создания копии графа (для использования в других функциях)
struct Graph* copygraph(struct Graph* graph){
//выделяем память под копию графа
    struct Graph* new_graph = (struct Graph*)malloc(sizeof(struct Graph));
    //переписываем значения из основного графа
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            new_graph->matrix[i][j] = graph->matrix[i][j];
        }
    }
    return new_graph;
}

//функция поиска мин элемента
int min(int a, int b){
    return (a < b) ? a : b;
}

//функция для печати пути
void printPath(int start, int end, int path[N][N]) {
    if (path[start][end] == -1) { //если маршрут прямой
        printf("%d", start + 1);
        return;
    }
    //если есть еще элементы, то вызываем рекурсивно и выписываем
    printPath(start, path[start][end], path);
    printf(" -> %d", end + 1);
}

//Алгоритм Флойда
void alg_floyd(struct Graph* graph, int start, int end){
    struct Graph* copy_of_graph = copygraph(graph);
    int path[N][N]; // массив для хранения промежуточных вершин

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(i != j && copy_of_graph->matrix[i][j] != INF){
                path[i][j] = i; // инициализируем промежуточные вершины начальными значениями
            } else {
                path[i][j] = -1; // в остальных случаях -1
            }
        }
    }

    for(int k = 0; k < N; k++){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(copy_of_graph->matrix[i][k] + copy_of_graph->matrix[k][j] < copy_of_graph->matrix[i][j]){
                    copy_of_graph->matrix[i][j] = copy_of_graph->matrix[i][k] + copy_of_graph->matrix[k][j];
                    path[i][j] = path[k][j]; // обновляем промежуточную вершину
                }
            }
        }
    }

    printf("Самый короткий путь из %d в %d по алгоритму Флойда:\n", start+1, end+1);
    if (copy_of_graph->matrix[start][end] != INF) {
        printPath(start, end, path);
        printf("\n");
        printf("Длина пути: %d\n\n", copy_of_graph->matrix[start][end]);
    } else {
        printf("Путь не найден\n");
    }
}


//Алгоритм Дейкстры
void deikstra(struct Graph* graph, int start, int end){
    int dist[N];//массив с кратчайшими расстояниями
    int flag_arr[N]; //массив флагов (обозначает включена ли вершина в кратчайший путь)

    //заполняем бесконечностью расстояния до других вершин (т.к. неизвестны), массив флагов зануляем
    for (int i = 0; i < N; i++) {
        dist[i] = INF, flag_arr[i] = 0;
    }

    dist[start] = 0; //расстояние от стартовой вершины до самой себя равно 0

    for (int j = 0; j < N - 1; j++) {
        int min = INF, min_index;

        //выбираем непосещенную вершину с минимальным значением
        for (int v = 0; v < N; v++)
            if (flag_arr[v] == 0 && dist[v] <= min)
                min = dist[v], min_index = v;

        int u = min_index;
        flag_arr[u] = 1;
        //обновляем расстояние до следующих вершин от U к V
        for (int v = 0; v < N; v++)
            if (!flag_arr[v] && graph->matrix[u][v] && dist[u] != INF && dist[u] + graph->matrix[u][v] < dist[v])
                dist[v] = dist[u] + graph->matrix[u][v];
    }

    printf("Самый короткий путь из %d в %d по алгоритму Дейкстры:\n%d\n", start+1, end+1, dist[end]);
}

int main(void){
    //матрица смежности графа (входные данные)
    int adjacencyMatrix[N][N] = {
        {0, INF, INF, INF, INF, INF, 1,   6,   20},
        {2,   0,   5,   INF, 4,   INF, INF, 3,   INF},
        {INF, INF, 0,   INF, INF, INF, 2,   INF, INF},
        {INF, INF, 5,   0,   INF, INF, INF, INF, 6},
        {INF, INF, INF, INF, 0,   9,   6,   INF, INF},
        {INF, INF, INF, INF, INF, 0,   INF, INF, INF},
        {INF, INF, INF, INF, INF, INF, 0,   4,   INF},
        {INF, INF, INF, INF, 4,   INF, INF, 0,   INF},
        {INF, INF, INF, INF, INF, INF, 1,   INF, 0}
    };

    //спросим какие числа рассматриваем
    int start;
    int end;
    printf("Введите стартовую точку:\n");
    scanf("%d", &start);
    start--;
    printf("Введите конечную точку:\n");
    scanf("%d", &end);
    end--;
    // построить граф
    struct Graph *graph = creategraph(adjacencyMatrix);

    printf("\n\n\n");
    alg_floyd(graph, start, end); //вызываем функцию флойда
    deikstra(graph, start, end); //вызываем функцию дейкстры

    free(graph);//освобождаем память
    return 0;
}
