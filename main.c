#include "game.c"


int main()
{
    // wchar_t emoji[] = L"🌍😄🐱‍👤";
    // mvaddwstr(5, 5, emoji);
    setlocale(LC_ALL, "");
    srand(time(0));
    initscr();
    curs_set(false);
    keypad(stdscr, TRUE);
    noecho();
    int which_menu = 0;
    /*
    which_menu = 0   main & first menu
    which_menu = 1   sign up menu
    which_menu = 2   sign in menu
    which_menu = 3   exit
    which_menu = 4   after sign up menu & sign in menu
    which_menu = 5   forgot pass
    which_menu = 6   game setting
    which_menu = 7   account page
    which_menu = 8   score table
    which_menu = 9   new game
    which_menu = 11   uplevel
    which_menu = 10  resume
    ...
    */

    while (1)
    {
        if (which_menu == 0)
        {
            /*
            which_case = 1   sign up menu
            which_case = 2   sign in menu
            which_case = 3   exit
            ...
            */

            int which_case = drawing_first_menu();
            if (which_case == 1)
            {
                which_menu = 1;
            }

            if (which_case == 2)
            {
                which_menu = 2;
            }

            if (which_case == 3)
            {
                which_menu = 3;
            }

        }

        else if (which_menu == 1)
        {
            int which_case = sign_up_menu();
            if (which_case == 0)
            {
                which_menu = 0;
            }
            else if (which_case == 4)
            {
                which_menu = 4;
            }
        }

        else if (which_menu == 2)
        {
            int which_case = sign_in_menu();
            if (which_case == 0)
            {
                which_menu = 0;
            }
            else if(which_case == 5)
            {
                which_menu = 5;
            }
            else if (which_case == 4)
            {
                which_menu = 4;
            }

        }

        else if (which_menu == 3)
        {
            break;
        }

        else if (which_menu == 4)
        {
            int which_case = before_play_menu(which_line_user);
            if (which_case == 7)
            {
                profile();
                which_menu = 4;
            }
            else if (which_case == 0)
            {
                which_menu = 0;
            }
            else if (which_case == 6)
            {
                which_menu = 6;
            }
            else if (which_case == 9)
            {
                which_menu = 9;
            }
            else if (which_case == 8)
            {
                score_table();
                which_menu = 4;
            }
            else if (which_case == 10)
            {
                which_menu = 10;
            }

        }
        
        else if (which_menu == 5)
        {
            int which_case = forgot_pass();
            if (which_case == 2)
            {
                which_menu = 2;
            }
        }

        else if (which_menu == 6)
        {
            int which_case = setting();
            if (which_case = 4)
            {
                which_menu = 4;
            }
        }
        
        else if(which_menu == 9)
        {
            int which_case = new_game(1);
            if (which_case == 4)
            {
                which_menu = 4;
            }
            else if (which_case == 11)
            {
                which_menu = 11;
            }
        }

        else if(which_menu == 11)
        {
            int which_case = new_game(2);
            if (which_case == 4)
            {
                which_menu = 4;
            }
            else if (which_case == 11)
            {
                which_menu = 11;
            }
        }

        else if (which_menu == 10)
        {
            resume();
            which_menu = 4;
        }
    }
    refresh();
    endwin();
    return 0;
}
