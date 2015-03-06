#include <ncurses.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>

using namespace std;

/*
 * Creates the logo at the top of the page
 */
int draw_logo(int mode){
  vector< string > arr;
  int start = 1;
  arr.push_back("    _____             __ ");
  arr.push_back("   / ____|           / _|");
  arr.push_back("  | |     ___  _ __ | |_ ");
  arr.push_back("  | |    / _ \\| '_ \\|  _|");
  arr.push_back("  | |___| (_) | | | | |  ");
  arr.push_back("   \\_____\\___/|_| |_|_|  ");
  for(vector<string>::size_type i = 0; i != arr.size(); i++){
    printw("%s", arr[i].c_str());
    move(start++, 0);
  }
  move(start - 5, 30);
  printw("By: Cody Hiar");
  move(start - 4, 30);
  printw("Ver: Alpha");
  move(start - 3, 30);
  printw("E-mail: codyfh@gmail.com");
  if(mode == 0){
    move(start - 2, 30);
    printw("Mode: ssh");
  } else if(mode == 1){
    move(start - 2, 30);
    printw("Mode: ssh-copy-id");
  }
  return 0;
}


/*
 * function that draw's the borders of the menu
 */
int draw_menu(int start, int &menu_choice, int &sub_choice, bool run_command, int mode){

  //Creating iterators for the master array, it is alphabetical by default
  typedef map<string, map<string, string> >::iterator outer_it;
  typedef map<string, string>::iterator inner_it;

  
  //Master Array of options with their respective commands
  map<string, map<string, string> > m;
  //number of menu options. Easy enough to set. Also add to the or statement about ssh commands
  int length = 3;
  //Files for Editing
  m["Edit File"]["bashrc"] = "vim~/.bashrc";
  m["Edit File"]["gitconfig"] = "vim ~/.gitconfig";
  //SSH to server
  m["SSH Server"]["test"] = "root@test.com -p 22";
  //Setup Options
  m["Setup"]["Vim Bundes Install"] = "vim +PluginInstall +qall";
  m["Setup"]["Set ZSH as shell"] = "chsh -s /bin/zsh";
  m["Setup"]["Brew & Cask Update"] = "brew update && brew upgrade brew-cask && brew cleanup && brew cask cleanup";


  //If enter was pressed execute the command that was selected
  if(run_command){
    int i = 0;
    for(outer_it outer_iter=m.begin(); outer_iter!=m.end(); ++outer_iter) {
      if(i == menu_choice){
        int j = 0;
        for(inner_it inner_iter=outer_iter->second.begin(); inner_iter!=outer_iter->second.end(); ++inner_iter) {
          if(j == sub_choice){
            endwin();
            system("clear");
            //If it's a ssh command make sure it's concatinated properly
            if(menu_choice == 1){
              if(mode == 0){
                std::string one = "ssh ";
                std::string two = inner_iter->second.c_str();
                std::string three = one + two;
                system(three.c_str());
                return 0;
              } else {
                std::string one = "ssh-copy-id ";
                std::string two = inner_iter->second.c_str();
                std::string three = one + two;
                system(three.c_str());
                return 0;
              }
            } else {
              system(inner_iter->second.c_str());
              return 0;
            }
          }
          j++;
        }
      }
      i++;
    }
  }
  

  //Make cursor stay in confines of top level menu
  if(menu_choice == -1){
    menu_choice = length - 1;
  } else if(menu_choice == length){
    menu_choice = 0;
  }

  //Get the length of the sub menu
  //Looping seemed like the easiest way to get things done
  int sub_length = 0;
  int k = 0;
  for(outer_it outer_iter=m.begin(); outer_iter!=m.end(); ++outer_iter) {
    if(k == menu_choice){
      for(inner_it inner_iter=outer_iter->second.begin(); inner_iter!=outer_iter->second.end(); ++inner_iter) {
          sub_length++;
      }
    }
    k++;
  }

  //Setting up variables for drawing
  int x, y;
  getmaxyx(stdscr, y, x);
  int middle_x = x/2;
  draw_logo(mode);


  //Create the Top Bar
  for(int i=0; i<x; i++){
    move(start, i);
    printw("-");
  }

  //Create the Bottom Bar
  for(int i=0; i<x; i++){
    move(start + 2, i);
    printw("-");
  }

  //Create the Middle Bar
  for(int i=start+3; i<y; i++){
    move(i, middle_x);
    printw("|");
    move(i, middle_x+1);
    printw("|");
  }



  //Make cursor stay in the the sub menu
  if(sub_choice == -1){
    sub_choice = sub_length - 1;
  } else if(sub_choice == sub_length){
    sub_choice = 0;
  }

  int x_padding = 3;
  int x_current = x_padding;

  int i = 0;
  for(outer_it outer_iter=m.begin(); outer_iter!=m.end(); ++outer_iter) {
    move(start + 1, x_current);
    printw("%c", '[');
    x_current = x_current +  1;
    move(start + 1, x_current);
    if(i == menu_choice){
      attron(A_REVERSE);
      printw("%s", outer_iter->first.c_str());
      attroff(A_REVERSE);
    } else {
      printw("%s", outer_iter->first.c_str());
    }
    x_current = x_current + outer_iter->first.length();
    move(start + 1, x_current);
    printw("%c", ']');
    x_current = x_current + x_padding;
    if(i == menu_choice){
      int j = 0;
      for(inner_it inner_iter=outer_iter->second.begin(); inner_iter!=outer_iter->second.end(); inner_iter++) {
        move(start + 4 + j, x_padding);
        if(j == sub_choice){
          attron(A_REVERSE);
          printw("%d.) %s", j, inner_iter->first.c_str());
          attroff(A_REVERSE);
        } else {
          printw("%d.) %s", j, inner_iter->first.c_str());
        }
        j++;
      }
    }
    i++;
  }


  return 0;
}


