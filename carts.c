#include <stdbool.h>
#include <stdio.h>

typedef struct list {
  int id;
  int point;
  struct list *next;
} list;

list *createl(int id, int point) {
  list *a = malloc(sizeof(list));
  a->id = id;
  a->point = point;
  a->next = NULL;
  return a;
}

void createcards(list *a) {
  if (a->id < 52) {
    int point = a->id / 4 + 1;
    if (point > 10)
      point = 10;
    else if (point == 1)
      point = 11;
    list *card = createl(a->id + 1, point);
    a->next = card;
    createcards(a->next);
  }
}

void addcard(list *a, list *card) {
  if (a->next != NULL)
    addcard(a->next, card);
  else
    a->next = card;
}

int suml(list *a) {
  if (a->next != NULL)
    return suml(a->next) + a->point;
  return a->point;
}

bool findl(list *a, int point) {
  if (a->point == point)
    return true;
  else if (a->next != NULL)
    return findl(a->next, point);
  return false;
}

void replace(list *a, int point1, int point2) {
  if (a->point == point1)
    a->point = point2;
  else if (a->next != NULL)
    replace(a->next, point1, point2);
}

list *getl(list *a, int id) {
  list *temp = createl(0, 0);
  if (a->next != NULL) {
    if (a->next->id != id)
      temp = getl(a->next, id);
    else {
      temp->id = id;
      temp->point = a->next->point;
      a->next = a->next->next;
    }
  }
  return temp;
}

list *getlr(list *a) {
  list *temp = createl(0, 0);
  srand(time(NULL) * 1000);
  while (temp->point == NULL)
    temp = getl(a, 1 + rand() % 51);
  return temp;
}

void freecards(list *a) {
  if (a->next != NULL)
    freecards(a->next);
  if (a->id == 0)
    a->next = NULL;
  else {
    free(a->next);
  }
}

int checkwin(list *a) {
  int s = suml(a);
  if (s > 21) {
    while (findl(a, 11)) {
      replace(a, 11, 1);
      s = suml(a);
      if (s == 21)
        return 1;
      else if (s < 21)
        return 0;
    }
    return 2;
  } else if (s == 21)
    return 1;
  else
    return 0;
}

void printl(list *a) {
  if (a->id != 0) {
    printf("(%d ", a->id);
    printf("%d)", a->point);
    if (a->next != NULL) {
      printf(", ");
      printl(a->next);
    } else
      printf("\n");
  } else if (a->next != NULL)
    printl(a->next);
  else
    printf("NULL CARTS\n");
}

void printCard(list *a){
  int c = a->id/4;
  if (a->id%4!=0) c++;
  if (c == 1) printf("Туз");
  else if (c == 2) printf("Двойка");
  else if (c == 3) printf("Тройка");
  else if (c == 4) printf("Четвёрка");
  else if (c == 5) printf("Пятёрка");
  else if (c == 6) printf("Шестёрка");
  else if (c == 7) printf("Семёрка");
  else if (c == 8) printf("Восьмёрка");
  else if (c == 9) printf("Девятка");
  else if (c == 10) printf("Десятка");
  else if (c == 11) printf("Валет");
  else if (c == 12) printf("Дама");
  else if (c == 13) printf("Король");
  c = a->id % 4;
  if (c == 0) printf(" ♠");
  else if (c == 1) printf(" ♦");
  else if (c == 2) printf(" ♥");
  else if (c == 3) printf(" ♣");
}

void printLast(list *a){
  if (a->next != NULL) printLast(a->next);
  else printCard(a);
}

void printlc(list *a) {
  if (a->id != 0) {
    printCard(a);
    if (a->next != NULL) {
      printf(", ");
      printlc(a->next);
    }
  }
  else if (a->next != NULL)
    printlc(a->next);
  else
    printf("NULL CARTS\n");
}
void printPoints(list *a, int d){
  if (a->id != 0) {
    printCard(a);
    printf(" (%d)",a->point);
    d+=a->point;
    if (a->next != NULL) {
      printf(", ");
      printPoints(a->next,d);
    }
    else printf(" Сумма = %d\n",d);
  }
  else if (a->next != NULL)
    printPoints(a->next,d);
  else
    printf("NULL CARTS\n");
}