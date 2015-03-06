#include "conf.h"

int main(){
  
  initscr();
  noecho();
  keypad(stdscr, true);
  int c, menu_choice = 0, sub_choice = 0, start = 7, mode = 0;
  draw_menu(start, menu_choice, sub_choice, false, mode);
  curs_set(0);
  //27 is escape key
  while((c=getch())!=27){
    //tab to activate ssh-copy-id mode
    if(c == 9){
      clear();
      if(mode == 0){
        mode = 1;
      } else if(mode == 1) {
        mode = 0;
      }
      draw_menu(start, menu_choice, sub_choice, false, mode);
    }
    //Numbers for selecting options in list, 1 - 9 only
    if(c >= 48 && c <=57){
      clear();
      sub_choice = c - 48;
      draw_menu(start, menu_choice, sub_choice, false, mode);
    }
    //Moving left with J
    if(c == 104){
      menu_choice--;
      clear();
      sub_choice = 0;
      draw_menu(start, menu_choice, sub_choice, false, mode);
    } 
    //Moving right with ;
    if(c == 108){
      menu_choice++;
      clear();
      sub_choice = 0;
      draw_menu(start, menu_choice, sub_choice, false, mode);
    } 
    //Moving down with j
    if(c == 106){
      sub_choice++;
      clear();
      draw_menu(start, menu_choice, sub_choice, false, mode);
    } 
    //Moving up with k
    if(c == 107){
      sub_choice--;
      clear();
      draw_menu(start, menu_choice, sub_choice, false, mode);
    } 
    //Hitting enter to execute command
    if(c == 10){
      draw_menu(start, menu_choice, sub_choice, true, mode);
      return 0;
    }
    //For Debugging Purposes
    //move(50,0);
    //printw("Keycode: %d, and the character: %c", c, c);
    //move(26,0);
    //printw("Menu: %d, Sub: %d", menu_choice, sub_choice);
    //move(10,0);
  }
  endwin();
  system("clear");
  return 0;
}



