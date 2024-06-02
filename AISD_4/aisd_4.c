#include <stdio.h>
#include <stdlib.h>

typedef struct Lnode{
    int data;//данные
    struct Lnode *next;//указатель на следующий элемент
} spisok;

//функция вывода списка на экран списка
void print_list(spisok* head){
    spisok* ptr = head;
    int cnt = 0;
    while(ptr != NULL){
        printf("%d элемент - %d\n", cnt++, ptr->data);
        ptr = ptr->next;
    }
}

//функция добавления узла в список
spisok* add_node(spisok* head, int data){
    spisok* newn = (spisok*)malloc(sizeof(spisok));//создаем новый узел с выделением памяти
    spisok* curr = head;//переменная для прохождения по всем элементам списка

    //проверка на успешное выделение памяти
    if(newn == NULL){
        printf("Allocation error\n");
        exit(1);
    }

    newn->data = data;//вписываем данные
    newn->next = NULL;//ставим окончние узла

    //проверка на пустой список
    if(head == NULL){
        return newn;
    }

    //проходим по всему списку, пока не дойдем до последнего и выставляем новый узел
    while(curr -> next != NULL){
        curr = curr->next;
    }

    curr->next = newn;
    return head;
}

//функция удаления узла из списка (указатель на голову списка, на текущий узел и на предыдущий узел)
void delete_node(spisok** head, spisok* current, spisok* prev){
    //проверка на пустой список
    if (*head == NULL || current == NULL)
        return;
    //если нужно удалить элемент, который является началом списка
    if (*head == current)
        *head = current->next;
    else
        prev->next = current->next;

    free(current);
}

void remove_duplicates(spisok* head){
    spisok* ptr1 = head;//внешний указатель
    spisok* ptr2;//внутренний указатель
    spisok* dup;//указатель для хранения адреса дубликата

    while(ptr1 != NULL && ptr1->next != NULL){
        ptr2 = ptr1;
        while(ptr2->next != NULL){
            //если нашли дубликат
            if(ptr1->data == ptr2->next->data){
                dup = ptr2->next;//устанавливаем указатель на дубликат
                ptr2->next = ptr2->next->next;
                delete_node(&head, dup, ptr2);//удаляем дубликат
            }
            else{
                ptr2 = ptr2->next;//если нет, то перемещаемся к следующему узлу
            }
        }
        ptr1 = ptr1->next;
    }
}

//функция удаления всего списка
spisok *delete_all(spisok *head){
    while(head != NULL){
        spisok* p = head;
        head = head -> next;
        free(p);
    }
    return NULL;
}

int main(void){
    int i;
    spisok* head = NULL;

    printf("Вводите значения для списка\n");
    int data;
    while(scanf("%d", &data) == 1){
        head = add_node(head, data);
    }
    printf("\n");

    printf("Исходный список:\n");
    print_list(head);
    printf("\n");

    remove_duplicates(head);
    printf("Список после удаления дубликатов:\n");
    print_list(head);
    printf("\n");

    delete_all(head);
    printf("Список успешно удален\n");

    return 0;
}
