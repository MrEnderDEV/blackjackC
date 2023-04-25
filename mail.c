#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "carts.h"

int main(void) {
  int com;
  int windil;
  int winplay;
  list *cards = createl(0, 0);
  list *diler = createl(0, 0);
  list *player = createl(0, 0);
  while (com != 2) {
    system("clear");
    printf("Ввыберите действие:\nНачать игру - 1\nЗакончить игру - 2\nВведите действие: ");
    scanf("%d", &com);
    while (com == 1) {
      system("clear");
      createcards(cards);
      addcard(player, getlr(cards));
      addcard(player, getlr(cards));
      addcard(diler, getlr(cards));
      addcard(diler, getlr(cards));
      windil = checkwin(diler);
      winplay = checkwin(player);
      if ((winplay == 1) && (windil == 1)) {
        printf("Карты Дилера: ");
        printPoints(diler,0);
        printf("Ваши карты: ");
        printPoints(player,0);
        printf("\nУ Вас и у дилера одинаковое количество очков. Ничья");
      }
      else if ((winplay == 1) && (windil == 0)) {
        printf("Карты Дилера: ");
        printPoints(diler,0);
        printf("Ваши карты: ");
        printPoints(player,0);
        printf("\nУ Вас 21 очко. Ваша победа");
      }
      else if ((winplay == 0) && (windil == 1)) {
        printf("Карты Дилера: ");
        printPoints(diler,0);
        printf("Ваши карты: ");
        printPoints(player,0);
        printf("\nУ Дилера 21 очко. Победа Дилера");
      }
      else {
        while (winplay == 0) {
          printf("Карты Дилера: ");
          printCard(diler->next);
          printf(", *\nВаши карты: ");
          printlc(player);
          printf("\n\nВыберите действие:\nДобавить одну карту - 1\nНичего не "
                 "брать - 2\nВведите команду: ");
          scanf("%d", &com);
          system("clear");
          if (com == 2)
            break;
          addcard(player, getlr(cards));
          winplay = checkwin(player);
        }
        printf("Карты Дилера: ");
        printPoints(diler,0);
        printf("Ваши карты: ");
        printPoints(player,0);
        sleep(2);
        if (winplay == 2)
          printf("\nУ Вас больше 21 очка. Победа Дилера");
        else{
          windil = suml(diler);
          while (windil < 17) {
            system("clear");
            addcard(diler, getlr(cards));
            windil = suml(diler);
            if (windil>21){
              replace(diler, 11, 1);
              windil = suml(diler);
            }
            printf("Диллер взял карту: ");
            printLast(diler);
            printf("\n\nКарты Дилера: ");
            printPoints(diler,0);
            printf("Ваши карты: ");
            printPoints(player,0);
            sleep(2);
          }
          system("clear");
          printf("Карты Дилера: ");
          printPoints(diler,0);
          printf("Ваши карты: ");
          printPoints(player,0);
          if (winplay == 1) {
            if (windil != 21)
              printf("\nУ Вас ровно 21 очко. Ваша победа");
            else
              printf("\nУ Вас и у Дилера одинаковое количество очков. Ничья");
          }
          else {
            if (windil > 21)
              printf("\nУ Дилера больше 21 очка. Ваша победа");
            else if (windil == 21)
              printf("\nУ Дилера 21 очко. Победа Дилера");
            else {
              winplay = suml(player);
              if (windil > winplay)
                printf("\nУ Дилера больше очков чем у Вас. Победа Дилера");
              else if (windil < winplay)
                printf("\nУ Вас больше очков чем у Дилера. Ваша победа");
              else
                printf("\nУ Вас и у Дилера одинаковое количество очков. Ничья");
            }
          }
        }
      }
      printf("\n\nВыберите действие:\nНачать заново - 1\nВыйти в главное меню "
             "- 2\nВведите команду: ");
      scanf("%d", &com);
      freecards(cards);
      freecards(player);
      freecards(diler);
    }
  }
  system("clear");
  printf("Выход.......");
  return 0;
}
