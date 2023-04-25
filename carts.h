typedef struct list{
  int id;
  int point;
  struct list *next;
}list;

list* createl(int id, int point);
void createcards(list *a);
void addcard(list* a, list* card);
int suml(list *a);
bool findl(list* a, int point);
void replace(list* a, int point1, int point2);
list* getl(list* a, int id);
list* getlr(list* a);
void freecards(list *a);
int checkwin(list* a);
void printl(list *a);
void printCard(list *a);
void printLast(list* a);
void printlc(list *a);
void printPoints(list *a, int d);