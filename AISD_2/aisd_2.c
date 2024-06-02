#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//интерфейсы функций
void first(int i, int j, int N, int tmp, int* array, int min_index);
void second(int *array, int left, int right, int N, int tmp, int min_index);
void array_paste(int i, int *array_1, int *array_2, int *array_3, int N);
void win_paint(int *array, int i, int N);
//основная функция
int main(void){

    int i = 0;
    int tmp = 0; //временная переменная для перестановки элементов
    int N = 20; //здесь указываем количество элементов массива
    int j = 0;
    int left = 0; //левый элемент массива для Быстрой сортировки
    int right = N - 1; //правый элемент массива для Быстрой сортировки
    int min_index = 0; //индекс минимального элемента для сортировки Выборкой

    //объявляем три массива
    int array_1[20]; //заполненный рандомно
    int array_2[20]; //заполненный в порядке возрастания
    int array_3[20]; //заполненный в порядке убывания


    //вызываем первую сортировку
    printf("ПЕРВАЯ СОРТИРОВКА: \n");
    printf("\n");
    array_paste(i, array_1, array_2, array_3, N); //создаем массивы
    printf("\n");
    first(i, j, N, tmp, array_1, min_index);
    win_print(array_1, i, N);
    check_array(array_1, i, N);
    first(i, j, N, tmp, array_2, min_index);
    win_print(array_2, i, N);
    check_array(array_2, i, N);
    first(i, j, N, tmp, array_3, min_index);
    win_print(array_3, i, N);
    check_array(array_3, i, N);
    printf("\n");


    //вызываем вторую сортировку
    printf("ВТОРАЯ СОРТИРОВКА: \n");
    printf("\n");
    array_paste(i, array_1, array_2, array_3, N); //создаем массивы
    printf("\n");
    second(array_1, left, right, N, tmp, min_index);
    win_print(array_1, i, N);
    check_array(array_1, i, N);
    second(array_2, left, right, N, tmp, min_index);
    win_print(array_2, i, N);
    check_array(array_2, i, N);
    second(array_3, left, right, N, tmp, min_index);
    win_print(array_3, i, N);
    check_array(array_3, i, N);
    return 0;
}

//функция сортировки "Выбором" (минимальный эл-т ставим в самое начало)
void first(int i, int j, int N, int tmp, int* array, int min_index){
    for(i = 0; i < (N - 1); i++){
        min_index = i;
        for(j = i + 1; j < N; j++){
            if(array[j] < array[min_index])
            min_index = j;
        }
        tmp = array[i];
        array[i] = array[min_index];
        array[min_index] = tmp;
    }
}

//функция сортировки "Быстрая" (элементы делятся на подгруппы)
void second(int *array, int left, int right, int N, int tmp, int min_index)
{
    int i = left, j = right; //начальный и конечный символы массива
    int middle = array[(left + right) / 2]; //опорный элемент

    while (i <= j)
    {
        while (array[i] < middle)
            i++;
        while (array[j] > middle)
            j--;
        if (i <= j)
        {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
            i++;
            j--;
        }
    }

    if (left < j)
        second(array, left, j, N, tmp, min_index);
    if (i < right)
        second(array, i, right, N, tmp, min_index);

}
 //функция для заполнения массивов (рандомно, по возрастанию и по убыванию)
void array_paste(int i, int *array_1, int *array_2, int *array_3, int N){
    srand(time(NULL)); // Инициализация генератора случайных чисел

    //рандомное заполнение

    for (i = 0; i < N; i++) {
        array_1[i] = rand() % 100;  // Заполнение случайным числом от 0 до 99
    }
    printf("Random array:\n");
    for (int i = 0; i < N; i++)
        printf("%d ", array_1[i]);
    printf("\n");

    //заполнение в порядке возрастания
    int count = 0;
    for (i = 0; i < N; i++){
        array_2[i] = count;
        count++;
    }
    printf("Increasing array:\n");
    for (int i = 0; i < N; i++)
        printf("%d ", array_2[i]);
    printf("\n");

    //заполнение в порядке убывания
    int count_2 = 19;
    for (i = 0; i < N; i++){
        array_3[i] = count_2;
        count_2--;
    }
    printf("Decreasing array:\n");
    for (int i = 0; i < N; i++)
        printf("%d ", array_3[i]);
    printf("\n");

}
//функция для выводы сообщения о том, что массив отсортирован
void win_print(int *array, int i, int N){
    printf("Отсортированный массив:\n");
    for (int i = 0; i < N; i++)
        printf("%d ", array[i]);
    printf("\n");
}

//функция для проверки корректности отсортированного массива
void check_array(int *array, int i, int N){
    int flag = 0;
    for(i = 0; i < N-1; i++){
        if(array[i] <= array[i+1])
            continue;
        else
            flag = 1;
    }
    if(flag == 0)
        printf("TRUE SORT\n");
    else
        printf("FALSE SORT\n");
}
