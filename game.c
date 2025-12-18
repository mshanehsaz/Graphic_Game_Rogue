#include "menu.c"


char **user;

/*
color 1 = yellow
color 2 = blue
color 3 = green
hardness 1 = easy
hardness 2 = normal
hardness 3 = hard
*/


/*
which food 1 = mamooli
which food 2 = magic
which food 3 = great
which food 4 = fased
*/

typedef struct
{
    int x;
    int y;
    int room_i;
    int life_time;
    int type;
}enemy;

typedef struct
{
    int time;
    int count;
}food;

typedef struct
{
    int line;
    int score;
    int gold;
    int color;
    float life_time;
    float hungry_amount;
    int telesm[3];
    food foods[4];
    int main_selah;
    int count_selahs[5];
    int hardness;
    int level;
    int room_i;
    int x;
    int y;
} Player;

typedef struct
{
    int x;
    int y;
}pair;


/*
type 0 = mamooli
type 1 = mamooli
type 2 = mamooli
type 3 = telesm
type 4 = ganj
type 5 = kaboos
*/

/*
door 0 = up
door 1 = right
door 2 = left
door 3 = down
*/
typedef struct
{
        char **map;
        int type;
        pair doors[4];
}room;

room *rooms;
enemy *enemies;
int count_enemy;

char **all_map;

char **map_whithout_tale;

char **map_that_shown;

int speed = 0;




int first_life;

Player player;



void save_score(int makoos)
{
typedef struct {
    char name[100];
    int gold;
    int score;
    int games;
} save;

    FILE *file = fopen("score.txt", "r");

    save play[100];

    int count = 0;
    
    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        sscanf(line, "%s %d %d %d", play[count].name, &play[count].gold, &play[count].score, &play[count].games);
        count ++;
    }
    fclose(file);

    int found = 0;
    for (int i = 0; i < count; i++) 
    {
        if (strcmp(play[i].name, user[0]) == 0) 
        {
            if (makoos)
            {
                play[i].gold -= player.gold;
                play[i].score -= player.score;
                play[i].games -= 1;
                found = 1;
                break;
            }
            play[i].gold += player.gold;
            play[i].score += player.score;
            play[i].games += 1;
            found = 1;
        }
    }

    if (!found && count < 100) 
    {
        strcpy(play[count].name, user[0]);
        play[count].gold = player.gold;
        play[count].score = player.score;
        play[count].games = 1;
        count++;
    }

    file = fopen("score.txt", "w");

    for (int i = 0; i < count; i++) 
    {
        fprintf(file, "%s %d %d %d\n", play[i].name, play[i].gold, play[i].score, play[i].games);
    }
    
    fclose(file);
}

void save_maps()
{
    char file_name[1000];
    strcpy(file_name, "maps/");
    strcat(file_name, user[0]);
    strcat(file_name, ".txt");

    FILE *file = fopen(file_name, "w");

    for (int i = 0; i < LINES - 10; i++)
    {
        for (int j = 0; j < COLS - 2; j++)
        {
            fprintf(file, "%c", all_map[i][j]);
        }
        fprintf(file, "\n");
    }

    for (int i = 0; i < LINES - 10; i++)
    {
        for (int j = 0; j < COLS - 2; j++)
        {
            fprintf(file, "%c", map_that_shown[i][j]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "%d %d %d %d %f %f %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",  player.line,  player.score,  player.gold,  player.color,  player.life_time,  player.hungry_amount, player.telesm[0],  player.telesm[1],  player.telesm[2],  player.foods[0].count,  player.foods[0].time,  player.foods[1].count,  player.foods[1].time,  player.foods[2].count,  player.foods[2].time,  player.foods[3].count,  player.foods[3].time, player.hardness,  player.level,  player.room_i,  player.x,  player.y,  rooms[0].type,  rooms[1].type,  rooms[2].type,  rooms[3].type,  rooms[4].type,  rooms[5].type,  rooms[6].type,  rooms[7].type, enemies[0].life_time, enemies[0].room_i, enemies[0].x, enemies[0].y, enemies[1].life_time, enemies[1].room_i, enemies[1].x, enemies[1].y, enemies[2].life_time, enemies[2].room_i, enemies[2].x, enemies[2].y, enemies[3].life_time, enemies[3].room_i, enemies[3].x, enemies[3].y, enemies[4].life_time, enemies[4].room_i, enemies[4].x, enemies[4].y, enemies[5].life_time, enemies[5].room_i, enemies[5].x, enemies[5].y, count_enemy, enemies[0].type, enemies[1].type, enemies[2].type, enemies[3].type, enemies[4].type, enemies[5].type);
    fclose(file);
}

void load_map()
{
    char file_name[1000];
    char salam;
    strcpy(file_name, "maps/");
    strcat(file_name, user[0]);
    strcat(file_name, ".txt");

    FILE *file = fopen(file_name, "r");

    for (int i = 0; i < LINES - 10; i++)
    {
        fgets(all_map[i], COLS - 1, file);
        fscanf(file, "%c", &salam);
    }

    for (int i = 0; i < LINES - 10; i++)
    {
        fgets(map_that_shown[i], COLS - 1, file);
        fscanf(file, "%c", &salam);
    }

    fscanf(file, "%d %d %d %d %f %f %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &player.line, &player.score, &player.gold, &player.color, &player.life_time, &player.hungry_amount,&player.telesm[0], &player.telesm[1], &player.telesm[2], &player.foods[0].count, &player.foods[0].time, &player.foods[1].count, &player.foods[1].time, &player.foods[2].count, &player.foods[2].time, &player.foods[3].count, &player.foods[3].time, &player.hardness, &player.level, &player.room_i, &player.x, &player.y, &rooms[0].type, &rooms[1].type, &rooms[2].type, &rooms[3].type, &rooms[4].type, &rooms[5].type, &rooms[6].type, &rooms[7].type, &enemies[0].life_time, &enemies[0].room_i, &enemies[0].x, &enemies[0].y, &enemies[1].life_time, &enemies[1].room_i, &enemies[1].x, &enemies[1].y, &enemies[2].life_time, &enemies[2].room_i, &enemies[2].x, &enemies[2].y, &enemies[3].life_time, &enemies[3].room_i, &enemies[3].x, &enemies[3].y, &enemies[4].life_time, &enemies[4].room_i, &enemies[4].x, &enemies[4].y, &enemies[5].life_time, &enemies[5].room_i, &enemies[5].x, &enemies[5].y, &count_enemy, &enemies[0].type, &enemies[1].type, &enemies[2].type, &enemies[3].type, &enemies[4].type, &enemies[5].type);

    fclose(file);
}

void alert(char *message1, char *message2, int number)
{
    for (int i = 2; i < COLS - 1; i++)
    {
        mvprintw(1, i, " ");
        mvprintw(2, i, " ");
        mvprintw(3, i, " ");
    }

    attron(A_BOLD);

    char buffer[256];
    if (number == -1)
    {
        attron(COLOR_PAIR(11));
        snprintf(buffer, sizeof(buffer), "%s", message1);
    }
    else if (number == -2)
    {
        attron(COLOR_PAIR(5));
        snprintf(buffer, sizeof(buffer), "%s", message1);
    }
    else
    {
        attron(COLOR_PAIR(11));
        snprintf(buffer, sizeof(buffer), "%s %d %s", message1, number, message2);
    }

    for (int i = 2; i < strlen(buffer) + 4; i++)
    {
        mvprintw(1, i, " ");
    }
    mvprintw(2, 2, " %s ", buffer);
    for (int i = 2; i < strlen(buffer) + 4; i++)
    {
        mvprintw(3, i, " ");
    }

    attroff(COLOR_PAIR(11));
    attroff(COLOR_PAIR(5));
    attroff(A_BOLD);

    refresh();
}

void food_menu()
{
    int which_case = 1;
    while (1)
    {
        wchar_t emoji1[] = L"🍗";
        wchar_t emoji2[] = L"🪄🍗";
        wchar_t emoji3[] = L"👑🍗";
        clear_and_border();
        mvaddwstr((LINES/2) - 6, (COLS/2) - 30, emoji1);
        mvaddwstr((LINES/2) - 3, (COLS/2) - 13, emoji2);
        mvaddwstr((LINES/2), (COLS/2) - 13, emoji3);
        attron(COLOR_PAIR(77));
        mvprintw(((LINES/2)) - 6, ((COLS/2) - 27) ," 1- YOU HAVE %d ORDINARY FOOD (MAY BE MIXED WITH SPOILED FOOD!) ", (player.foods[0].count + player.foods[3].count));
        mvprintw(((LINES/2)) - 3, ((COLS/2) - 8) ," 2- YOU HAVE %d MAGIC FOOD ", player.foods[1].count);
        mvprintw(((LINES/2)), (COLS/2) - 8 ," 3- YOU HAVE %d GREAT FOOD ", player.foods[2].count);
        attroff(COLOR_PAIR(77));
        attron(COLOR_PAIR(3));
        mvprintw(((LINES/2)) + 3, ((COLS/2) - 14) ," CHOOSE THE FOOD: (1, 2, 3)");
        mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
        attroff(COLOR_PAIR(3));
        refresh();
        for(int ch = getch(); ch != 10; ch = getch())
        {
            if (ch == KEY_UP)
            {
                which_case --;
                if (which_case == 0)
                {
                    which_case = 2;
                }
            }
            if ((ch == KEY_DOWN))
            {
                which_case ++;
                if (which_case == 3)
                {
                    which_case = 1;
                }
            }

            switch (which_case)
            {
            
            case 1:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(79));
                mvprintw(((LINES/2)) + 3, ((COLS/2) - 14) ," CHOOSE THE FOOD: (1, 2, 3)");
                attroff(COLOR_PAIR(79));

                break;

            case 2:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2)) + 3, ((COLS/2) - 14) ," CHOOSE THE FOOD: (1, 2, 3)");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(79));
                mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(79));
                break;

            }
        }
        refresh();
        switch (which_case)
        {
            case 1:
                int which;
                int count;
                move(((LINES/2)) + 3, ((COLS/2) + 16));
                curs_set(true);
                echo();
                refresh();
                if (scanw("%d", &which) == 1 && which >= 1 && which <= 3)
                {
                    if (which == 1)
                    {
                        count = player.foods[0].count + player.foods[3].count;
                    }
                    else 
                    {
                        count = player.foods[which - 1].count;
                    }


                    if (count == 0)
                    {
                        curs_set(false);
                        noecho(); 
                        attron(COLOR_PAIR(5));
                        mvprintw(((LINES/8) - 1), (COLS/2 - 11), "                     " );
                        mvprintw(((LINES/8)), (COLS/2 - 11), " YOU HAVEN'T ENOUGH! " );
                        mvprintw(((LINES/8) + 1), (COLS/2 - 11), "                     " );
                        attroff(COLOR_PAIR(5));
                        refresh();    
                        sleep(3);
                        continue;
                    }
                    else
                    {
                        if (which == 1)
                        {
                            int which_ord_fas = rand()%2;
                            if (which_ord_fas == 0)
                            {
                                player.hungry_amount = 0;
                                player.foods[0].count -= 1;
                                curs_set(false);
                                noecho(); 
                                attron(COLOR_PAIR(11));
                                mvprintw(((LINES/8) - 1), (COLS/2 - 19), "                                     " );
                                mvprintw(((LINES/8)), (COLS/2 - 19), " YOU ARE LUCKY IT WAS ORDINARY FOOD! " );
                                mvprintw(((LINES/8) + 1), (COLS/2 - 19), "                                     " );
                                attroff(COLOR_PAIR(11));
                                refresh();
                                sleep(3);
                            }
                            if (which_ord_fas == 1)
                            {
                                curs_set(false);
                                noecho(); 
                                attron(COLOR_PAIR(5));
                                mvprintw(((LINES/8) - 1), (COLS/2 - 12), "                      " );
                                mvprintw(((LINES/8)), (COLS/2 - 12), " OH! IT WAS DESTROID! " );
                                mvprintw(((LINES/8) + 1), (COLS/2 - 12), "                      " );
                                attroff(COLOR_PAIR(5));
                                refresh();
                                player.life_time -= 1;
                                player.foods[3].count -= 1;
                                sleep(3);
                            }

                        }

                        if (which == 2)
                        {
                                player.hungry_amount = 0;
                                player.foods[1].count -= 1;
                                speed = 25;
                                curs_set(false);
                                noecho(); 
                                attron(COLOR_PAIR(11));
                                mvprintw(((LINES/8) - 1), (COLS/2 - 15), "                            " );
                                mvprintw(((LINES/8)), (COLS/2 - 15), " YUM! MAGIC FOOD! SPEED UP! " );
                                mvprintw(((LINES/8) + 1), (COLS/2 - 15), "                            " );
                                attroff(COLOR_PAIR(11));
                                refresh();
                                sleep(3);
                        }

                        if (which == 3)
                        {
                                player.hungry_amount = 0;
                                player.foods[2].count -= 1;
                                curs_set(false);
                                noecho(); 
                                attron(COLOR_PAIR(11));
                                mvprintw(((LINES/8) - 1), (COLS/2 - 10), "                  " );
                                mvprintw(((LINES/8)), (COLS/2 - 10), " YUM! GREAT FOOD! " );
                                mvprintw(((LINES/8) + 1), (COLS/2 - 10), "                  " );
                                attroff(COLOR_PAIR(11));
                                refresh();
                                sleep(3);
                        }
                    }
                    move(0, 0);
                    curs_set(false);
                    noecho();
                    continue; 
                }
                else
                {
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 15), "                            " );
                    mvprintw(((LINES/8)), (COLS/2 - 15), " PLEASE ENTER CORRECT ITEM! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 15), "                            " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(3);
                    continue;
                }

            case 2:
                return;
        }
    }
}

void weapon_menu()
{
    int which_case = 1;
    while (1)
    {
        wchar_t emoji1[] = L"🪓";
        wchar_t emoji2[] = L"🗡️";
        wchar_t emoji3[] = L"🪄";
        wchar_t emoji4[] = L"🏹";
        wchar_t emoji5[] = L"⚔️";
        clear_and_border();
        mvaddwstr((LINES/2) - 6, (COLS/2) - 15, emoji1);
        mvaddwstr((LINES/2) - 4, (COLS/2) - 21, emoji2);
        mvaddwstr((LINES/2) - 2, (COLS/2) - 24, emoji3);
        mvaddwstr((LINES/2), (COLS/2) - 24, emoji4);
        mvaddwstr((LINES/2) + 2, (COLS/2) - 15, emoji5);
        attron(COLOR_PAIR(77));
        mvprintw(((LINES/2)) - 6, ((COLS/2) - 12) ," 1- MACE (CLOSE-RANGE)");
        mvprintw(((LINES/2)) - 4, ((COLS/2) - 18) ," 2- YOU HAVE %d DAGGER (LONG-RANGE)", player.count_selahs[1]);
        mvprintw(((LINES/2)) - 2, (COLS/2) - 21 ," 3- YOU HAVE %d MAGIC WAND  (LONG-RANGE)", player.count_selahs[2]);
        mvprintw(((LINES/2)), (COLS/2) - 21 ," 4- YOU HAVE %d NORMAL ARROW (LONG-RANGE)", player.count_selahs[3]);
        mvprintw(((LINES/2)) + 2, (COLS/2) - 12 ," 5- SWORD (CLOSE-RANGE)");
        attron(COLOR_PAIR(77));
        attron(COLOR_PAIR(3));
        mvprintw(((LINES/2)) + 4, ((COLS/2) - 18) ," CHOOSE THE WEAPON: (1, 2, 3, 4, 5)");
        mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
        attroff(COLOR_PAIR(3));
        refresh();
        for(int ch = getch(); ch != 10; ch = getch())
        {
            if (ch == KEY_UP)
            {
                which_case --;
                if (which_case == 0)
                {
                    which_case = 2;
                }
            }
            if ((ch == KEY_DOWN))
            {
                which_case ++;
                if (which_case == 3)
                {
                    which_case = 1;
                }
            }

            switch (which_case)
            {
            
            case 1:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(79));
                mvprintw(((LINES/2)) + 4, ((COLS/2) - 18) ," CHOOSE THE WEAPON: (1, 2, 3, 4, 5)");
                attroff(COLOR_PAIR(79));

                break;

            case 2:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2)) + 4, ((COLS/2) - 18) ," CHOOSE THE WEAPON: (1, 2, 3, 4, 5)");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(79));
                mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(79));
                break;

            }
        }
        refresh();
        switch (which_case)
        {
            int which;
            case 1:
                int count;
                move(((LINES/2)) + 4, ((COLS/2) + 18));
                curs_set(true);
                echo();
                refresh();
                if (scanw("%d", &which) == 1 && which >= 1 && which <= 5)
                {
                    if (which != 1)
                    {
                        count = player.count_selahs[which - 1];
                        if (count == 0)
                        {

                            curs_set(false);
                            noecho(); 
                            attron(COLOR_PAIR(5));
                            mvprintw(((LINES/8) - 1), (COLS/2 - 11), "                     " );
                            mvprintw(((LINES/8)), (COLS/2 - 11), " YOU HAVEN'T ENOUGH! " );
                            mvprintw(((LINES/8) + 1), (COLS/2 - 11), "                     " );
                            attroff(COLOR_PAIR(5));
                            refresh();    
                            sleep(3);
                            continue;
                        }
                    }

                        if (which == 1)
                        {
                            curs_set(false);
                            noecho(); 
                            attron(COLOR_PAIR(11));
                            mvprintw(((LINES/8) - 1), (COLS/2 - 4), "       " );
                            mvprintw(((LINES/8)), (COLS/2 - 4), " MACE! " );
                            mvprintw(((LINES/8) + 1), (COLS/2 - 4), "       " );
                            attroff(COLOR_PAIR(11));
                            refresh();
                            player.main_selah = 1;
                            sleep(3);
                        }

                        if (which == 2)
                        {
                            curs_set(false);
                            noecho(); 
                            attron(COLOR_PAIR(11));
                            mvprintw(((LINES/8) - 1), (COLS/2 - 5), "         " );
                            mvprintw(((LINES/8)), (COLS/2 - 5), " DAGGER! " );
                            mvprintw(((LINES/8) + 1), (COLS/2 - 5), "         " );
                            attroff(COLOR_PAIR(11));
                            refresh();
                            player.main_selah = 2;
                            sleep(3);
                        }

                        if (which == 3)
                        {
                            curs_set(false);
                            noecho(); 
                            attron(COLOR_PAIR(11));
                            mvprintw(((LINES/8) - 1), (COLS/2 - 7), "             " );
                            mvprintw(((LINES/8)), (COLS/2 - 7), " MAGIC WAND! " );
                            mvprintw(((LINES/8) + 1), (COLS/2 - 7), "             " );
                            attroff(COLOR_PAIR(11));
                            refresh();
                            player.main_selah = 3;
                            sleep(3);
                        }

                        if (which == 4)
                        {
                            curs_set(false);
                            noecho(); 
                            attron(COLOR_PAIR(11));
                            mvprintw(((LINES/8) - 1), (COLS/2 - 8), "               " );
                            mvprintw(((LINES/8)), (COLS/2 - 5), " NORMAL ARROW! " );
                            mvprintw(((LINES/8) + 1), (COLS/2 - 8), "               " );
                            attroff(COLOR_PAIR(11));
                            refresh();
                            player.main_selah = 4;
                            sleep(3);
                        }

                        if (which == 5)
                        {
                            curs_set(false);
                            noecho(); 
                            attron(COLOR_PAIR(11));
                            mvprintw(((LINES/8) - 1), (COLS/2 - 5), "        " );
                            mvprintw(((LINES/8)), (COLS/2 - 5), " SWORD! " );
                            mvprintw(((LINES/8) + 1), (COLS/2 - 5), "        " );
                            attroff(COLOR_PAIR(11));
                            refresh();
                            player.main_selah = 5;
                            sleep(3);
                        }

                    move(0, 0);
                    curs_set(false);
                    noecho();
                    continue; 
                }
                else
                {
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 15), "                            " );
                    mvprintw(((LINES/8)), (COLS/2 - 15), " PLEASE ENTER CORRECT ITEM! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 15), "                            " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(3);
                    continue;
                }

            case 2:
                return;
        }
    }
}

void telesm_menu()
{
    int which_case = 1;
    while (1)
    {
        wchar_t emoji1[] = L"💖";
        wchar_t emoji2[] = L"💥";
        wchar_t emoji3[] = L"⚡";
        clear_and_border();
        mvaddwstr((LINES/2) - 6, (COLS/2) - 17, emoji1);
        mvaddwstr((LINES/2) - 3, (COLS/2) - 17, emoji2);
        mvaddwstr((LINES/2), (COLS/2) - 17, emoji3);
        attron(COLOR_PAIR(77));
        mvprintw(((LINES/2)) - 6, ((COLS/2) - 14) ," 1- YOU HAVE %d HEALTH ENCHANT ", player.telesm[0]);
        mvprintw(((LINES/2)) - 3, ((COLS/2) - 14) ," 2- YOU HAVE %d DAMAGE ENCHANT ", player.telesm[1]);
        mvprintw(((LINES/2)), (COLS/2) - 14 ," 3- YOU HAVE %d SPEED ENCHANT ", player.telesm[2]);
        attron(COLOR_PAIR(77));
        attron(COLOR_PAIR(3));
        mvprintw(((LINES/2)) + 3, ((COLS/2) - 15) ," CHOOSE THE ENCHANT: (1, 2, 3)");
        mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
        attroff(COLOR_PAIR(3));
        refresh();
        for(int ch = getch(); ch != 10; ch = getch())
        {
            if (ch == KEY_UP)
            {
                which_case --;
                if (which_case == 0)
                {
                    which_case = 2;
                }
            }
            if ((ch == KEY_DOWN))
            {
                which_case ++;
                if (which_case == 3)
                {
                    which_case = 1;
                }
            }

            switch (which_case)
            {
            
            case 1:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(79));
                mvprintw(((LINES/2)) + 3, ((COLS/2) - 15) ," CHOOSE THE ENCHANT: (1, 2, 3)");
                attroff(COLOR_PAIR(79));

                break;

            case 2:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2)) + 3, ((COLS/2) - 15) ," CHOOSE THE ENCHANT: (1, 2, 3)");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(79));
                mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(79));
                break;

            }
        }
        refresh();
        switch (which_case)
        {
            case 1:
                int which;
                int count;
                move(((LINES/2)) + 3, ((COLS/2) + 16));
                curs_set(true);
                echo();
                refresh();
                if (scanw("%d", &which) == 1 && which >= 1 && which <= 3)
                {
                    count = player.telesm[which - 1];


                    if (count == 0)
                    {
                        curs_set(false);
                        noecho(); 
                        attron(COLOR_PAIR(5));
                        mvprintw(((LINES/8) - 1), (COLS/2 - 11), "                     " );
                        mvprintw(((LINES/8)), (COLS/2 - 11), " YOU HAVEN'T ENOUGH! " );
                        mvprintw(((LINES/8) + 1), (COLS/2 - 11), "                     " );
                        attroff(COLOR_PAIR(5));
                        refresh();    
                        sleep(3);
                        continue;
                    }
                    else
                    {
                        if (which == 1)
                        {
                                curs_set(false);
                                noecho(); 
                                attron(COLOR_PAIR(11));
                                mvprintw(((LINES/8) - 1), (COLS/2 - 18), "                                   " );
                                mvprintw(((LINES/8)), (COLS/2 - 18), " THE ENCHANT RESTORES YOUR HEALTH! " );
                                mvprintw(((LINES/8) + 1), (COLS/2 - 18), "                                   " );
                                attroff(COLOR_PAIR(11));
                                refresh();
                                player.life_time += 5;
                                player.telesm[0] -= 1;
                                sleep(3);
                        }

                        if (which == 2)
                        {
                                curs_set(false);
                                noecho(); 
                                attron(COLOR_PAIR(11));
                                mvprintw(((LINES/8) - 1), (COLS/2 - 19), "                                     " );
                                mvprintw(((LINES/8)), (COLS/2 - 19), " THE ENCHANT INCREASES YOUR STRENGHT " );
                                mvprintw(((LINES/8) + 1), (COLS/2 - 19), "                                     " );
                                attroff(COLOR_PAIR(11));
                                refresh();
                                player.telesm[1] -= 1;
                                sleep(3);
                        }

                        if (which == 3)
                        {
                            curs_set(false);
                            noecho(); 
                            attron(COLOR_PAIR(11));
                            mvprintw(((LINES/8) - 1), (COLS/2 - 18), "                                  " );
                            mvprintw(((LINES/8)), (COLS/2 - 18), " THE ENCHANT INCREASES YOUR SPEED " );
                            mvprintw(((LINES/8) + 1), (COLS/2 - 18), "                                  " );
                            attroff(COLOR_PAIR(11));
                            refresh();
                            speed = 30;
                            player.telesm[2] -= 1;
                            sleep(3);
                        }
                    }
                    move(0, 0);
                    curs_set(false);
                    noecho();
                    continue; 
                }
                else
                {
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 15), "                            " );
                    mvprintw(((LINES/8)), (COLS/2 - 15), " PLEASE ENTER CORRECT ITEM! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 15), "                            " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(3);
                    continue;
                }

            case 2:
                return;
        }
    }
}

int which_room_is_the_player(int x, int y)
{
    int i = x;
    int j = y; 

    if (i > 5 && i < (LINES - 10)/2 + 5 && j > 1 && j < (COLS - 2)/4)
    {
        return 0;
    }

    else if (i > 5 && i < (LINES - 10)/2 + 5 && j > (COLS - 2)/4 + 1 && j < 2*(COLS - 2)/4 + 1)
    {
        return 1;
    }    
    
    
    else if (i > 5 && i < (LINES - 10)/2 + 5 && j > 2*(COLS - 2)/4 + 1 && j < 3*(COLS - 2)/4 + 1)
    {
        return 2;
    }
    
    else if (i > 5 && i < (LINES - 10)/2 + 5 && j > 3*(COLS - 2)/4 + 1 && j < (COLS - 2) + 1)
    {
        return 3;
    }

    
    else if (i > (LINES - 10)/2 + 5 && i < (LINES - 10) + 5 && j > 1 && j < (COLS - 2)/4 + 1)
    {
        return 4;
    }

    
    else if (i > (LINES - 10)/2 + 5 && i < (LINES - 10) + 5 && j > (COLS - 2)/4 + 1 && j < 2*(COLS - 2)/4 + 1)
    {
        return 5;
    }

    
    else if (i > (LINES - 10)/2 + 5 && i < (LINES - 10) + 5 && j > 2*(COLS - 2)/4 + 1 && j < 3*(COLS - 2)/4 + 1)
    {
        return 6;
    }

    
    else if (i > (LINES - 10)/2 + 5 && i < (LINES - 10) + 5 && j > 3*(COLS - 2)/4 + 1 && j < (COLS - 2) + 1)
    {
        return 7;
    }
}

void updating_room_that_shown(int which_dir)
{
    if (which_dir == 0)
    {
        int x = player.x  - 5;
        int y = player.y - 2;
        while (map_whithout_tale[x][y] != '$') 
        {
            map_that_shown[x][y] = map_whithout_tale[x][y];
            y ++;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
        y --;
        while (map_whithout_tale[x][y] != '$') 
        {
            map_that_shown[x][y] = map_whithout_tale[x][y];
            y --;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
        x ++;
        while (map_whithout_tale[x][y] != '$')
        {
            int j = y;
            map_that_shown[x][j] = map_whithout_tale[x][j];
            j++;
            while (map_whithout_tale[x][j] != '|' && map_whithout_tale[x][j] != '+' && map_whithout_tale[x][j] != '>')
            {
                map_that_shown[x][j] = map_whithout_tale[x][j];
                j++;
            }
            map_that_shown[x][j] = map_whithout_tale[x][j];
            x++;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
        y ++;
        while (map_whithout_tale[x][y] != '$') 
        {
            map_that_shown[x][y] = map_whithout_tale[x][y];
            y ++;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
    }
    
    else if (which_dir == 1)
    {
        int x = player.x  - 6;
        int y = player.y - 3;
        while (map_whithout_tale[x][y] != '$') 
        {
            map_that_shown[x][y] = map_whithout_tale[x][y];
            x ++;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
        x --;
        while (map_whithout_tale[x][y] != '$') 
        {
            map_that_shown[x][y] = map_whithout_tale[x][y];
            x --;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
        y --;
        while (map_whithout_tale[x][y] != '$')
        {
            int i = x;
            map_that_shown[i][y] = map_whithout_tale[i][y];
            i++;
            while (map_whithout_tale[i][y] != '-' && map_whithout_tale[i][y] != '+'&& map_whithout_tale[i][y] != '>')
            {
                map_that_shown[i][y] = map_whithout_tale[i][y];
                i++;
            }
            map_that_shown[i][y] = map_whithout_tale[i][y];
            y --;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
        x ++;
        while (map_whithout_tale[x][y] != '$') 
        {
            map_that_shown[x][y] = map_whithout_tale[x][y];
            x ++;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
    }

    else if (which_dir == 3)
    {
        int x = player.x - 7;
        int y = player.y - 2;
        while (map_whithout_tale[x][y] != '$') 
        {
            map_that_shown[x][y] = map_whithout_tale[x][y];
            y ++;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
        y --;
        while (map_whithout_tale[x][y] != '$') 
        {
            map_that_shown[x][y] = map_whithout_tale[x][y];
            y --;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
        x --;
        while (map_whithout_tale[x][y] != '$')
        {
            int j = y;
            map_that_shown[x][j] = map_whithout_tale[x][j];
            j++;
            while (map_whithout_tale[x][j] != '|' && map_whithout_tale[x][j] != '+' && map_whithout_tale[x][j] != '>')
            {
                map_that_shown[x][j] = map_whithout_tale[x][j];
                j++;
            }
            map_that_shown[x][j] = map_whithout_tale[x][j];
            x --;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
        y ++;
        while (map_whithout_tale[x][y] != '$') 
        {
            map_that_shown[x][y] = map_whithout_tale[x][y];
            y ++;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
    }
    
    else if (which_dir == 2)
    {
        int x = player.x - 6;
        int y = player.y - 1;
        while (map_whithout_tale[x][y] != '$') 
        {
            map_that_shown[x][y] = map_whithout_tale[x][y];
            x ++;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
        x --;
        while (map_whithout_tale[x][y] != '$') 
        {
            map_that_shown[x][y] = map_whithout_tale[x][y];
            x --;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
        y ++;
        while (map_whithout_tale[x][y] != '$')
        {
            int i = x;
            map_that_shown[i][y] = map_whithout_tale[i][y];
            i++;
            while (map_whithout_tale[i][y] != '-' && map_whithout_tale[i][y] != '+' && map_whithout_tale[i][y] != '>')
            {
                map_that_shown[i][y] = map_whithout_tale[i][y];
                i++;
            }
            map_that_shown[i][y] = map_whithout_tale[i][y];
            y++;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y];
        x ++;
        while (map_whithout_tale[x][y] != '$') 
        {
            map_that_shown[x][y] = map_whithout_tale[x][y];
            x ++;
        }
        map_that_shown[x][y] = map_whithout_tale[x][y]; 
    }

    player.room_i = which_room_is_the_player(player.x, player.y);
    if (rooms[player.room_i].type == 0 || rooms[player.room_i].type == 1 || rooms[player.room_i].type == 2)
    {
        alert("You Are Now In A Ordinary Room!", "", -1);
    }

    else if (rooms[player.room_i].type == 3)
    {
        alert("You Are Now In A Telesm Room!", "", -1);
    }

    else if (rooms[player.room_i].type == 4)
    {
        alert("Bravo!! You Are Now In The Ganj Room!", "", -1);
    }

}

void updating_ways_that_shown(int i, int j)
{
    if (all_map[i - 6][j - 2] == '#')
    {
        map_that_shown[i - 6][j - 2] = '#';
    }

    if (all_map[i - 5][j - 2] == '#')
    {
        map_that_shown[i - 5][j - 2] = '#';
    }
    if (all_map[i - 7][j - 2] == '#')
    {
        map_that_shown[i - 7][j - 2] = '#';
    }
    if (all_map[i - 6][j - 1] == '#')
    {
        map_that_shown[i - 6][j - 1] = '#';
    }
    if (all_map[i - 6][j - 3] == '#')
    {
        map_that_shown[i - 6][j - 3] = '#';
    }

}

void add_to_main_map(int i)
{
    int row, col;
    switch (i) 
    {
    case 0:
        row = 0;
        col = 0;
        break;

    case 1:
        row = 0;
        col = (COLS - 2) / 4;
        break;

    case 2:
        row = 0;
        col = 2 * (COLS - 2) / 4;
        break;

    case 3:
        row = 0;
        col = 3 * (COLS - 2) / 4;
        break;

    case 4:
        row = ((LINES - 10) / 2);
        col = 0;
        break;

    case 5:
        row = ((LINES - 10) / 2);
        col = (COLS - 2) / 4;
        break;

    case 6:
        row = ((LINES - 10) / 2);
        col = 2 * (COLS - 2) / 4 ;
        break;

    case 7:
        row = (LINES - 10) / 2;
        col = 3 * (COLS - 2) / 4;
        break;

    }

    for (int k = 0; k < ((LINES - 10) / 2); k++) 
    {
        for (int j = 0; j < ((COLS - 2) / 4); j++) 
        {
            all_map[row + k][col + j] = rooms[i].map[k][j];
        }
    }
}

void connect_plus(int x1, int y1, int dir1, int x2, int y2, int dir2)
{
    srand(time(0));

    switch (dir1)
    {
    case 0:
        x1 --;
        break;

    case 1:
        y1 ++;
        break;
        
    case 2:
        y1 --;
        break;

    case 3:
        x1 ++;
        break;
    }

    switch (dir2)
    {
    case 0:
        x2 --;
        break;

    case 1:
        y2 ++;
        break;
        
    case 2:
        y2 --;
        break;

    case 3:
        x2 ++;
        break;
    }

    while (x1 != x2 || y1 != y2) 
    {
        int turn = rand() % 2;

        if (all_map[x1][y1] == ' ')
        {
            all_map[x1][y1] = '#';
        }
        
        if (turn && x1 != x2)
        {
            x1 += (x1 < x2) ? 1 : -1;
        } 
        else if(y1 != y2)
        {
            y1 += (y1 < y2) ? 1 : -1;
        } 
    }
    all_map[x1][y1] = '#';
}

void connect_room()
{
    int which_arr = rand()%4;

    switch (which_arr)
    {
    case 0:
        connect_plus(rooms[0].doors[1].x, rooms[0].doors[1].y, 1,
                    rooms[1].doors[2].x, rooms[1].doors[2].y, 2);

        connect_plus(rooms[0].doors[3].x, rooms[0].doors[3].y, 3,
                    rooms[4].doors[0].x, rooms[4].doors[0].y, 0);  
        
        connect_plus(rooms[1].doors[1].x, rooms[1].doors[1].y, 1,
                    rooms[2].doors[2].x, rooms[2].doors[2].y, 2);
        
        connect_plus(rooms[2].doors[1].x, rooms[2].doors[1].y, 1,
                    rooms[3].doors[2].x, rooms[3].doors[2].y, 2);
        
        connect_plus(rooms[3].doors[3].x, rooms[3].doors[3].y, 3,
                    rooms[7].doors[0].x, rooms[7].doors[0].y, 0);
        
        connect_plus(rooms[5].doors[1].x, rooms[5].doors[1].y, 1,
                    rooms[6].doors[2].x, rooms[6].doors[2].y, 2);
        
        connect_plus(rooms[6].doors[1].x, rooms[6].doors[1].y, 1,
                    rooms[7].doors[2].x, rooms[7].doors[2].y, 2); 
        break;

        case 1:
        connect_plus(rooms[0].doors[1].x, rooms[0].doors[1].y, 1,
                    rooms[1].doors[2].x, rooms[1].doors[2].y, 2); 

        connect_plus(rooms[1].doors[3].x, rooms[1].doors[3].y, 3,
                    rooms[5].doors[0].x, rooms[5].doors[0].y, 0);
        
        connect_plus(rooms[1].doors[1].x, rooms[1].doors[1].y, 1,
                    rooms[2].doors[2].x, rooms[2].doors[2].y, 2);
        
        connect_plus(rooms[2].doors[3].x, rooms[2].doors[3].y, 3,
                    rooms[6].doors[0].x, rooms[6].doors[0].y, 0);
        
        connect_plus(rooms[3].doors[3].x, rooms[3].doors[3].y, 3,
                    rooms[7].doors[0].x, rooms[7].doors[0].y, 0);
        
        connect_plus(rooms[4].doors[1].x, rooms[4].doors[1].y, 1,
                    rooms[5].doors[2].x, rooms[5].doors[2].y, 2);
        
        connect_plus(rooms[6].doors[1].x, rooms[6].doors[1].y, 1,
                    rooms[7].doors[2].x, rooms[7].doors[2].y, 2); 
        break;

        case 2:
        connect_plus(rooms[0].doors[1].x, rooms[0].doors[1].y, 1,
                    rooms[1].doors[2].x, rooms[1].doors[2].y, 2);

        connect_plus(rooms[0].doors[3].x, rooms[0].doors[3].y, 3,
                    rooms[4].doors[0].x, rooms[4].doors[0].y, 0);  

        connect_plus(rooms[1].doors[3].x, rooms[1].doors[3].y, 3,
                    rooms[5].doors[0].x, rooms[5].doors[0].y, 0);
        
        connect_plus(rooms[2].doors[1].x, rooms[2].doors[1].y, 1,
                    rooms[3].doors[2].x, rooms[3].doors[2].y, 2);
        
        connect_plus(rooms[2].doors[3].x, rooms[2].doors[3].y, 3,
                    rooms[6].doors[0].x, rooms[6].doors[0].y, 0);
        
        connect_plus(rooms[3].doors[3].x, rooms[3].doors[3].y, 3,
                    rooms[7].doors[0].x, rooms[7].doors[0].y, 0);
        
        connect_plus(rooms[5].doors[1].x, rooms[5].doors[1].y, 1,
                    rooms[6].doors[2].x, rooms[6].doors[2].y, 2);

        break;
        
        case 3:

        connect_plus(rooms[0].doors[3].x, rooms[0].doors[3].y, 3,
                    rooms[4].doors[0].x, rooms[4].doors[0].y, 0);  

        connect_plus(rooms[1].doors[3].x, rooms[1].doors[3].y, 3,
                    rooms[5].doors[0].x, rooms[5].doors[0].y, 0);
        
        connect_plus(rooms[2].doors[3].x, rooms[2].doors[3].y, 3,
                    rooms[6].doors[0].x, rooms[6].doors[0].y, 0);
        
        connect_plus(rooms[3].doors[3].x, rooms[3].doors[3].y, 3,
                    rooms[7].doors[0].x, rooms[7].doors[0].y, 0);
        
        connect_plus(rooms[4].doors[1].x, rooms[4].doors[1].y, 1,
                    rooms[5].doors[2].x, rooms[5].doors[2].y, 2);
        
        connect_plus(rooms[5].doors[1].x, rooms[5].doors[1].y, 1,
                    rooms[6].doors[2].x, rooms[6].doors[2].y, 2);
        
        connect_plus(rooms[6].doors[1].x, rooms[6].doors[1].y, 1,
                    rooms[7].doors[2].x, rooms[7].doors[2].y, 2); 
        break;
    
    
    }
         
}

void clear_and_border2()
{
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(LINES - 1, COLS - 1, "#");
    mvprintw(0, 0, "#");
    mvprintw(LINES -1 , 0, "#");
    mvprintw(0, COLS - 1, "#");
    for (int i =  1 ; i < LINES - 1; i++)
    {
        mvprintw(i, 0, "|");   
    }
    for (int i = 1 ; i < LINES - 1; i++)
    {
        mvprintw(i, COLS - 1, "|");   
    }
    for (int i = 1 ; i < COLS - 1; i++)
    {
        mvprintw(0, i, "*"); 
        mvprintw(4, i, "*");  
    }
    for (int i = 1 ; i < COLS - 1 ; i++)
    {
        mvprintw(LINES - 1, i, "*");  
        mvprintw(LINES - 5, i, "*");  
    }
    refresh();
}

void adding_doors(int i, int firstx, int firsty, int width, int height)
{
    switch (i)
    {
    case 0:
        rooms[i].doors[1].x = (rand()%(height-3)) + firstx + 1;
        rooms[i].doors[1].y = firsty + width;
        all_map[rooms[i].doors[1].x][rooms[i].doors[1].y] = '+';

        rooms[i].doors[3].y = (rand()%(width-3)) + firsty + 1;
        rooms[i].doors[3].x = firstx + height;
        all_map[rooms[i].doors[3].x][rooms[i].doors[3].y] = '+';
        break;
    
    case 1:
        rooms[i].doors[1].x = (rand()%(height-3)) + firstx + 1;
        rooms[i].doors[1].y = firsty + width + (COLS - 2)/4;
        all_map[rooms[i].doors[1].x][rooms[i].doors[1].y] = '+';

        rooms[i].doors[2].x = (rand()%(height-3)) + firstx + 1;
        rooms[i].doors[2].y = firsty + (COLS - 2)/4;
        all_map[rooms[i].doors[2].x][rooms[i].doors[2].y] = '+';

        rooms[i].doors[3].y = (rand()%(width-3)) + firsty + (COLS - 2)/4 + 1;
        rooms[i].doors[3].x = firstx + height;
        all_map[rooms[i].doors[3].x][rooms[i].doors[3].y] = '+';
        break;

    case 2:
        rooms[i].doors[1].x = (rand()%(height-3)) + firstx + 1;
        rooms[i].doors[1].y = firsty + width + 2*(COLS - 2)/4;
        all_map[rooms[i].doors[1].x][rooms[i].doors[1].y] = '+';

        rooms[i].doors[2].x = (rand()%(height-3)) + firstx + 1;
        rooms[i].doors[2].y = firsty + 2*(COLS - 2)/4;
        all_map[rooms[i].doors[2].x][rooms[i].doors[2].y] = '+';

        rooms[i].doors[3].y = (rand()%(width-3)) + firsty + 1 + 2*(COLS - 2)/4;
        rooms[i].doors[3].x = firstx + height;
        all_map[rooms[i].doors[3].x][rooms[i].doors[3].y] = '+';
        break;
    case 3:

        rooms[i].doors[2].x = (rand()%(height-3)) + firstx + 1;
        rooms[i].doors[2].y = firsty + 3*(COLS - 2)/4;
        all_map[rooms[i].doors[2].x][rooms[i].doors[2].y] = '+';

        rooms[i].doors[3].y = (rand()%(width-3)) + firsty + 1 + 3*(COLS - 2)/4;
        rooms[i].doors[3].x = firstx + height;
        all_map[rooms[i].doors[3].x][rooms[i].doors[3].y] = '+';
        break;
    case 4:
        rooms[i].doors[1].x = (rand()%(height-3)) + firstx + 1 + (LINES - 10)/2;
        rooms[i].doors[1].y = firsty + width;
        all_map[rooms[i].doors[1].x][rooms[i].doors[1].y] = '+';
        rooms[i].doors[0].y = (rand()%(width-3)) + firsty + 1;
        rooms[i].doors[0].x = firstx + (LINES - 10)/2;
        all_map[rooms[i].doors[0].x][rooms[i].doors[0].y] = '+';
        break;
    case 5:
        rooms[i].doors[1].x = (rand()%(height-3)) + firstx + 1 + (LINES - 10)/2;
        rooms[i].doors[1].y = firsty + width + (COLS - 2)/4;
        all_map[rooms[i].doors[1].x][rooms[i].doors[1].y] = '+';

        rooms[i].doors[2].x = (rand()%(height-3)) + firstx + 1 + (LINES - 10)/2;
        rooms[i].doors[2].y = firsty + (COLS - 2)/4;
        all_map[rooms[i].doors[2].x][rooms[i].doors[2].y] = '+';

        rooms[i].doors[0].y = (rand()%(width-3)) + firsty + 1 + (COLS - 2)/4;
        rooms[i].doors[0].x = firstx + (LINES - 10)/2;
        all_map[rooms[i].doors[0].x][rooms[i].doors[0].y] = '+';
        break;
    case 6:
        rooms[i].doors[1].x = (rand()%(height-3)) + firstx + 1 + (LINES - 10)/2;
        rooms[i].doors[1].y = firsty + width + 2*(COLS - 2)/4;
        all_map[rooms[i].doors[1].x][rooms[i].doors[1].y] = '+';

        rooms[i].doors[2].x = (rand()%(height-3)) + firstx + 1 + (LINES - 10)/2;
        rooms[i].doors[2].y = firsty + 2*(COLS - 2)/4;
        all_map[rooms[i].doors[2].x][rooms[i].doors[2].y] = '+';

        rooms[i].doors[0].y = (rand()%(width-3)) + firsty + 1 + 2*(COLS - 2)/4;
        rooms[i].doors[0].x = firstx + (LINES - 10)/2;
        all_map[rooms[i].doors[0].x][rooms[i].doors[0].y] = '+';
        break;
    case 7:
        rooms[i].doors[2].x = (rand()%(height-3)) + firstx + 1 + (LINES - 10)/2;
        rooms[i].doors[2].y = firsty + 3*(COLS - 2)/4;
        all_map[rooms[i].doors[2].x][rooms[i].doors[2].y] = '+';

        rooms[i].doors[0].y = (rand()%(width-3)) + firsty + 1 + 3*(COLS - 2)/4;
        rooms[i].doors[0].x = firstx + (LINES - 10)/2;
        all_map[rooms[i].doors[0].x][rooms[i].doors[0].y] = '+';
        break;
    }
}

void adding_stairs()
{
    if (player.level == 4)
    {
        return;
    }
    srand(time(0));
    int room_stair = rand()%8;
    while (room_stair == player.room_i)
    {
        room_stair = rand()%8;
    }

    switch (room_stair)
    {
    case 0:
        for (int i = 0; i < (LINES - 10)/2; i++)
        {
            for (int j = 0; j < (COLS - 2)/4; j++)
            {
                if (all_map[i][j] == '-' && all_map[i][j + 2] == '-')
                {
                    for (int k = i; k >= 0; k--)
                    {
                        all_map[k][j + 2] = '>';
                        if (k == 0)
                        {
                            all_map[k][j + 2] = '?';
                        }
                    }
                    return;
                }
            }
        }
        break;
    
    case 1:
        for (int i = 0; i < (LINES - 10)/2; i++)
        {
            for (int j = (COLS - 2)/4; j < 2*(COLS - 2)/4; j++)
            {
                if (all_map[i][j] == '-' && all_map[i][j + 2] == '-')
                {
                    for (int k = i; k >= 0; k--)
                    {
                        all_map[k][j + 2] = '>';
                        if (k == 0)
                        {
                            all_map[k][j + 2] = '?';
                        }
                    }
                    return;
                }
            }
        }
        break;

    case 2:
        for (int i = 0; i < (LINES - 10)/2; i++)
        {
            for (int j = 2*(COLS - 2)/4; j < 3*(COLS - 2)/4; j++)
            {
                if (all_map[i][j] == '-' && all_map[i][j + 2] == '-')
                {
                    for (int k = i; k >= 0; k--)
                    {
                        all_map[k][j + 2] = '>';
                        if (k == 0)
                        {
                            all_map[k][j + 2] = '?';
                        }
                    }
                    return;
                }
            }
        }
        break;

    case 3:
        for (int i = 0; i < (LINES - 10)/2; i++)
        {
            for (int j = 3*(COLS - 2)/4; j < (COLS - 2); j++)
            {
                if (all_map[i][j] == '-' && all_map[i][j + 2] == '-')
                {
                    for (int k = i; k >= 0; k--)
                    {
                        all_map[k][j + 2] = '>';
                        if (k == 0)
                        {
                            all_map[k][j + 2] = '?';
                        }
                    }
                    return;
                }
            }
        }
        break;

    case 4:
        for (int i = (LINES - 10) - 1; i > (LINES - 10)/2; i--)
        {
            for (int j = 0; j < (COLS - 2)/4; j++)
            {
                if (all_map[i][j] == '-' && all_map[i][j + 2] == '-')
                {
                    for (int k = i; k < (LINES - 10); k++)
                    {
                        all_map[k][j + 2] = '>';
                        if (k == ((LINES - 10) - 1))
                        {
                            all_map[k][j + 2] = '?';
                        }
                    }
                    return;
                }
            }
        }
        break;

    case 5:
        for (int i = (LINES - 10) - 1; i > (LINES - 10)/2; i--)
        {
            for (int j = (COLS - 2)/4; j < 2*(COLS - 2)/4; j++)
            {
                if (all_map[i][j] == '-' && all_map[i][j + 2] == '-')
                {
                    for (int k = i; k < (LINES - 10); k++)
                    {
                        all_map[k][j + 2] = '>';
                        if (k == ((LINES - 10) - 1))
                        {
                            all_map[k][j + 2] = '?';
                        }
                    }
                    return;
                }
            }
        }
        break;
    case 6:
        for (int i = (LINES - 10) - 1; i > (LINES - 10)/2; i--)
        {
            for (int j = 2*(COLS - 2)/4; j < 3*(COLS - 2)/4; j++)
            {
                if (all_map[i][j] == '-' && all_map[i][j + 2] == '-')
                {
                    for (int k = i; k < (LINES - 10); k++)
                    {
                        all_map[k][j + 2] = '>';
                        if (k == ((LINES - 10) - 1))
                        {
                            all_map[k][j + 2] = '?';
                        }
                    }
                    return;
                }
            }
        }
        break;
    case 7:
        for (int i = (LINES - 10) - 1; i > (LINES - 10)/2; i--)
        {
            for (int j = 3*(COLS - 2)/4; j < (COLS - 2); j++)
            {
                if (all_map[i][j] == '-' && all_map[i][j + 2] == '-')
                {
                    for (int k = i; k < (LINES - 10); k++)
                    {
                        all_map[k][j + 2] = '>';
                        if (k == ((LINES - 10) - 1))
                        {
                            all_map[k][j + 2] = '?';
                        }
                    }
                    return;
                }
            }
        }
        break;
    
    }

    
}

void map()
{
    map_whithout_tale = (char **) malloc ((LINES - 10)*sizeof(char *));
    for (int i = 0; i < (LINES - 10); i++)
    {
        map_whithout_tale[i] = (char *) malloc((COLS - 2) * sizeof(char));
        for (int j = 0; j < (COLS - 2); j++)
        {
            map_whithout_tale[i][j] = ' ';
        }
    }  

    map_that_shown = (char **) malloc ((LINES - 10)*sizeof(char *));
    for (int i = 0; i < (LINES - 10); i++)
    {
        map_that_shown[i] = (char *) malloc((COLS - 2) * sizeof(char));
        for (int j = 0; j < (COLS - 2); j++)
        {
            map_that_shown[i][j] = ' ';
        }
    }  

    all_map = (char **) malloc ((LINES - 10)*sizeof(char *));
    for (int i = 0; i < (LINES - 10); i++)
    {
        all_map[i] = (char *) malloc((COLS - 2) * sizeof(char));
        for (int j = 0; j < (COLS - 2); j++)
        {
            all_map[i][j] = ' ';
        }
    }  
    rooms = (room *) malloc(9 * sizeof(room));
    enemies = (enemy *) malloc(6 * sizeof(enemy));
    count_enemy = 0;




    for (int i = 0; i<8; i++)
    {
        if (i == 2 && player.level == 4)
        {
            int height = rand()%7 + 4;
            int width = rand()%13 + 6;

            rooms[i].map = (char **) malloc(((LINES - 10)/2)*sizeof(char *));
            for (int j = 0; j<((LINES - 10)/2); j++)
            {
                rooms[i].map[j] = (char *) malloc(((COLS - 2)/4)*sizeof(char));
                for (int k = 0; k < ((COLS - 2)/4); k++)
                {
                    rooms[i].map[j][k] = ' ';
                }
            }

            int firstx = rand()%((LINES - 10)/8) + 1;
            int firsty = rand()%((COLS - 2)/8) + 1;


            if (firstx + height < ((LINES - 10)/2) && firsty + width < ((COLS - 2)/4)) 
            {
            } 
            else 
            {
                i --;
                continue;
            }


            for (int k = 1; k < width; k++)
            {
                rooms[i].map[firstx][firsty + k] = '-';
            }

            for (int k = 1; k < width; k++)
            {
                rooms[i].map[firstx + height][firsty + k] = '-';
            }

            for (int k = 1; k < height; k++)
            {
                rooms[i].map[firstx + k][firsty] = '|';
            }

            for (int k = 1; k < height; k++)
            {
                rooms[i].map[firstx + k][firsty + width] = '|';
            }   
            rooms[i].map[firstx][firsty] = '$';
            rooms[i].map[firstx + height][firsty] = '$';
            rooms[i].map[firstx][firsty + width] = '$';
            rooms[i].map[firstx + height][firsty + width] = '$';

            for (int k = firstx + 1; k < firstx + height; k++)
            {
                for (int j = firsty + 1; j <  firsty + width; j++)
                {
                    rooms[i].map[k][j] = '.';
                }
            }

            add_to_main_map(i);
            adding_doors(i, firstx, firsty, width, height);
            rooms[i].type = 4;
        }
        else 
        {
            //دو مورد از ۴ حالتی که میتونه بیاد باید اتاق معمولی باشه یعنی اگه ۰ یا ۱ یا ۲ بود معمولی 
            rooms[i].type = rand()%4;
    
            if (rooms[i].type == 1 || rooms[i].type == 0 || rooms[i].type == 2)
            {
                int height = rand()%7 + 4;
                int width = rand()%13 + 6;

                rooms[i].map = (char **) malloc(((LINES - 10)/2)*sizeof(char *));
                for (int j = 0; j<((LINES - 10)/2); j++)
                {
                    rooms[i].map[j] = (char *) malloc(((COLS - 2)/4)*sizeof(char));
                    for (int k = 0; k < ((COLS - 2)/4); k++)
                    {
                        rooms[i].map[j][k] = ' ';
                    }
                }

                int firstx = rand()%((LINES - 10)/8) + 1;
                int firsty = rand()%((COLS - 2)/8) + 1;


                if (firstx + height < ((LINES - 10)/2) && firsty + width < ((COLS - 2)/4)) 
                {
                } 
                else 
                {
                    i --;
                    continue;
                }


                for (int k = 1; k < width; k++)
                {
                    rooms[i].map[firstx][firsty + k] = '-';
                }

                for (int k = 1; k < width; k++)
                {
                    rooms[i].map[firstx + height][firsty + k] = '-';
                }

                for (int k = 1; k < height; k++)
                {
                    rooms[i].map[firstx + k][firsty] = '|';
                }

                for (int k = 1; k < height; k++)
                {
                    rooms[i].map[firstx + k][firsty + width] = '|';
                }   
                rooms[i].map[firstx][firsty] = '$';
                rooms[i].map[firstx + height][firsty] = '$';
                rooms[i].map[firstx][firsty + width] = '$';
                rooms[i].map[firstx + height][firsty + width] = '$';

                for (int k = firstx + 1; k < firstx + height; k++)
                {
                    for (int j = firsty + 1; j <  firsty + width; j++)
                    {
                        rooms[i].map[k][j] = '.';
                    }
                }

                add_to_main_map(i);
                adding_doors(i, firstx, firsty, width, height);
            }

            else if (rooms[i].type == 3)
            {
                int height = rand()%7 + 4;
                int width = rand()%13 + 6;

                rooms[i].map = (char **) malloc(((LINES - 10)/2)*sizeof(char *));
                for (int j = 0; j<((LINES - 10)/2); j++)
                {
                    rooms[i].map[j] = (char *) malloc(((COLS - 2)/4)*sizeof(char));
                    for (int k = 0; k < ((COLS - 2)/4); k++)
                    {
                        rooms[i].map[j][k] = ' ';
                    }
                }

                int firstx = rand()%((LINES - 10)/8) + 1;
                int firsty = rand()%((COLS - 2)/8) + 1;


                if (firstx + height < ((LINES - 10)/2) && firsty + width < ((COLS - 2)/4)) 
                {
                } 
                else 
                {
                    i --;
                    continue;
                }


                for (int k = 1; k < width; k++)
                {
                    rooms[i].map[firstx][firsty + k] = '-';
                }

                for (int k = 1; k < width; k++)
                {
                    rooms[i].map[firstx + height][firsty + k] = '-';
                }

                for (int k = 1; k < height; k++)
                {
                    rooms[i].map[firstx + k][firsty] = '|';
                }

                for (int k = 1; k < height; k++)
                {
                    rooms[i].map[firstx + k][firsty + width] = '|';
                }   
                rooms[i].map[firstx][firsty] = '$';
                rooms[i].map[firstx + height][firsty] = '$';
                rooms[i].map[firstx][firsty + width] = '$';
                rooms[i].map[firstx + height][firsty + width] = '$';

                for (int k = firstx + 1; k < firstx + height; k++)
                {
                    for (int j = firsty + 1; j <  firsty + width; j++)
                    {
                        rooms[i].map[k][j] = '.';
                    }
                }

                add_to_main_map(i);
                adding_doors(i, firstx, firsty, width, height);
            }

            else if (rooms[i].type == 5)
            {
                //kaboos
            }
        }
    }   
}

void print_all_map()
{
    move(6, 2);
    for (int i = 0; i < LINES - 10; i++)
    {
        for (int j = 0; j < COLS - 2; j++)
        {
            if (map_whithout_tale[i][j] == 'B')
            {
                attron(COLOR_PAIR(40));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(40));
                refresh();
                continue;
            }

            if (map_whithout_tale[i][j] == 'D')
            {
                attron(COLOR_PAIR(75));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(75));
                refresh();
                continue;
            }
            if (map_whithout_tale[i][j] == 'F')
            {
                attron(COLOR_PAIR(76));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(76));
                refresh();
                continue;
            }
            if (map_whithout_tale[i][j] == 'G')
            {
                attron(COLOR_PAIR(77));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(77));
                refresh();
                continue;
            }
            if (map_whithout_tale[i][j] == 'S')
            {
                attron(COLOR_PAIR(78));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(78));
                refresh();
                continue;
            }
            if (map_whithout_tale[i][j] == 'U')
            {
                attron(COLOR_PAIR(79));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(79));
                refresh();
                continue;
            }

            if (map_whithout_tale[i][j] == '2')
            {
                attron(COLOR_PAIR(76));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(76));
                refresh();
                continue;
            }
            if (map_whithout_tale[i][j] == '3')
            {
                attron(COLOR_PAIR(77));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(77));
                refresh();
                continue;
            }
            if (map_whithout_tale[i][j] == '4')
            {
                attron(COLOR_PAIR(78));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(78));
                refresh();
                continue;
            }
            if (map_whithout_tale[i][j] == '5')
            {
                attron(COLOR_PAIR(79));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(79));
                refresh();
                continue;
            }
            if (map_whithout_tale[i][j] == 'H')
            {
                attron(COLOR_PAIR(53));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(53));
                refresh();
                continue;
            }
            if (map_whithout_tale[i][j] == 'J')
            {
                attron(COLOR_PAIR(54));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(54));
                refresh();
                continue;
            }
            if (map_whithout_tale[i][j] == 'V')
            {
                attron(COLOR_PAIR(55));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(55));
                refresh();
                continue;
            }
            if (map_whithout_tale[i][j] == 'A')
            {
                attron(COLOR_PAIR(63));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(63));
                refresh();
                continue;
            }
            if (map_whithout_tale[i][j] == 'O')
            {
                attron(COLOR_PAIR(64));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(64));
                refresh();
                continue;
            }
            if (map_whithout_tale[i][j] == 'M')
            {
                attron(COLOR_PAIR(65));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(65));
                refresh();
                continue;
            }
    
            if (map_whithout_tale[i][j] == '>' || map_whithout_tale[i][j] == '?')
            {
                attron(COLOR_PAIR(42));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(42));
                refresh();
                continue;
            }

            if (map_whithout_tale[i][j] == '#')
            {
                attron(COLOR_PAIR(41));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(41));
                refresh();
                continue;
            }

            if (map_whithout_tale[i][j] == 'C')
            {
                attron(COLOR_PAIR(16));
                printw("%c", map_whithout_tale[i][j]);
                attroff(COLOR_PAIR(16));
                continue;
            }
            if (map_whithout_tale[i][j] == 'o')
            {
                printw("%c", map_whithout_tale[i][j]);
                continue;
            }
            attron(COLOR_PAIR(15));
            printw("%c", map_whithout_tale[i][j]);
            attroff(COLOR_PAIR(15));
        }
        move(6 + i + 1, 2);
    }
    refresh(); 
}

void which_user(int line_user)
{
    FILE *file_account_password;
    file_account_password = fopen("accounts_passwords.txt", "r");
    char line[300];
    player.line = line_user;
    user = (char **) malloc(3 * sizeof(char *));
    for (int j = 0; j < 3; j++)
    {
        *(user + j) = (char *) malloc(100*sizeof(char));
    }

    do
    {
        fgets(line, sizeof(line), file_account_password);
        line[strcspn(line, "\n")] = '\0';
        sscanf(line, "%s %s %s", user[0], user[1], user[2] );
        line_user--;
    } while (line_user != 0);
}

int before_play_menu(int line)
{
    if (line == -1)
    {
        player.line = -1;
    }
    else
    {
        which_user(line);
    }
    clear_and_border();
    int which_case = 1;
    while (1)
    {
        clear_and_border();
        attron(COLOR_PAIR(3));
        mvprintw(((LINES/2) - 8), (COLS/2) - 6," NEW GAME ");
        mvprintw(((LINES/2)) - 5, ((COLS/2) - 5) ," RESUME ");
        mvprintw(((LINES/2)) - 2, ((COLS/2) - 5) ," SETTING ");
        mvprintw(((LINES/2)) + 1, ((COLS/2) - 7) ," SCORE TABLE ");
        mvprintw(((LINES/2) + 4), ((COLS/2) - 5) ," PROFILE ");
        mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
        attroff(COLOR_PAIR(3));
        refresh();
        for(int ch = getch(); ch != 10; ch = getch())
        {
            if (ch == KEY_UP)
            {
                which_case --;
                if (which_case == 0)
                {
                    which_case = 6;
                }
            }
            if ((ch == KEY_DOWN))
            {
                which_case ++;
                if (which_case == 7)
                {
                    which_case = 1;
                }
            }

            switch (which_case)
            {
            
            case 1:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 5) ," RESUME ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 5) ," SETTING ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 7) ," SCORE TABLE ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 5) ," PROFILE ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2) - 8), (COLS/2) - 6," NEW GAME ");
                attroff(COLOR_PAIR(4));

                break;

            case 2:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 8), (COLS/2) - 6," NEW GAME ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 5) ," SETTING ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 7) ," SCORE TABLE ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 5) ," PROFILE ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 5) ," RESUME ");
                attroff(COLOR_PAIR(4));
                break;

            case 3:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 8), (COLS/2) - 6," NEW GAME ");
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 5) ," RESUME ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 7) ," SCORE TABLE ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 5) ," PROFILE ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 5) ," SETTING ");
                attroff(COLOR_PAIR(4));
                break;

            case 4:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 8), (COLS/2) - 6," NEW GAME ");
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 5) ," RESUME ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 5) ," SETTING ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 5) ," PROFILE ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 7) ," SCORE TABLE ");
                attroff(COLOR_PAIR(4));
                break;

            case 5:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 8), (COLS/2) - 6," NEW GAME ");
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 5) ," RESUME ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 5) ," SETTING ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 7) ," SCORE TABLE ");
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2) + 4), ((COLS/2) - 5) ," PROFILE ");
                attroff(COLOR_PAIR(4));
                break;

            case 6:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 8), (COLS/2) - 6," NEW GAME ");
                mvprintw(((LINES/2)) - 5, ((COLS/2) - 5) ," RESUME ");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 5) ," SETTING ");
                mvprintw(((LINES/2)) + 1, ((COLS/2) - 7) ," SCORE TABLE ");
                mvprintw(((LINES/2) + 4), ((COLS/2) - 5) ," PROFILE ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) + 7, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(4));
                break;

            }
        }
        refresh();

        switch (which_case)
        {
            case 1:
                return 9;

            case 2:
                if (player.line == -1)
                {
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 13), "                        " );
                    mvprintw(((LINES/8)), (COLS/2 - 13), " YOU HAVEN'T SAVED GAME " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 13), "                        " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(2);
                    continue;
                }
                else 
                {
                    return 10;
                }

            case 3:
                return 6;

            case 4:
                return 8;  

            case 5:
                return 7;

            case 6:
                return 0;
        }
    }
}

void score_table()
{
    clear_and_border();
    typedef struct {
    char name[100];
    int gold;
    int score;
    int games;
    } save;

    FILE *file = fopen("score.txt", "r");

    save play[100];

    int count = 0;
    
    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        sscanf(line, "%s %d %d %d", play[count].name, &play[count].gold, &play[count].score, &play[count].games);
        count ++;
    }
    fclose(file);

    if (player.line == -1)
    {
        strcpy(play[count].name, "GUEST");
        play[count].gold = player.gold;
        play[count].score = player.score;
        play[count].games = 1;
        count ++;
    }

    if (count == 0)
    {
        curs_set(false);
        noecho(); 
        attron(COLOR_PAIR(5));
        mvprintw(((LINES/8) - 1), (COLS/2 - 10), "                   " );
        mvprintw(((LINES/8)), (COLS/2 - 10), " NOBODY PLAYED YET " );
        mvprintw(((LINES/8) + 1), (COLS/2 - 10), "                   " );
        attroff(COLOR_PAIR(5));
        refresh();
        sleep(2);
        return;
    }

    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (play[i].score < play[j].score)
            {
                save temp = play[i];
                play[i] = play[j];
                play[j] = temp;
            }
        }
    }

    int which_page = 1;
    int max_which_page = ((count - 1)/3) + 1;
    int count_copy = count;
    
    for (int ch = 'e'; ch != 'q'; ch = getch())
    {
        if (ch == KEY_DOWN)
        { 
            which_page ++;
            if (which_page > max_which_page)
            {
                which_page = 1;
            }
        }


        int i = which_page;

        clear_and_border();
        if (i == 1)
        {
            if (count_copy > 0)
            {
            wchar_t emoji[] = L"🥇";
            mvaddwstr((LINES/2) - 4, (COLS/4) + 3, emoji);
            attron(COLOR_PAIR(101));
            mvprintw((LINES/2) - 4, (COLS/4) + 7, " %d- %s GOLD: %d SCORE: %d GAME: %d (GOAT!) ", 3*(i - 1) + 1, play[3*(i - 1)].name, play[3*(i - 1)].gold, play[3*(i - 1)].score, play[3*(i - 1)].games);
            attroff(COLOR_PAIR(101));
            count_copy --;
            }


            if (count_copy > 0)
            {
            wchar_t emoji1[] = L"🥈";
            mvaddwstr((LINES/2), (COLS/4) + 3, emoji1);
            attron(COLOR_PAIR(102));
            mvprintw((LINES/2), (COLS/4) + 7, " %d- %s GOLD: %d SCORE: %d GAME: %d (HOTSHOT!) ", 3*(i - 1) + 2, play[3*(i - 1) + 1].name, play[3*(i - 1) + 1].gold, play[3*(i - 1) + 1].score, play[3*(i - 1) + 1].games);
            attroff(COLOR_PAIR(102));
            count_copy --;
            }


            if (count_copy > 0)
            {
            wchar_t emoji2[] = L"🥉";
            mvaddwstr((LINES/2) + 4, (COLS/4) + 3, emoji2);
            attron(COLOR_PAIR(103));
            mvprintw((LINES/2) + 4, (COLS/4) + 7, " %d- %s GOLD: %d SCORE: %d GAME: %d (ACE!) ", 3*(i - 1) + 3, play[3*(i - 1) + 2].name, play[3*(i - 1) + 2].gold, play[3*(i - 1) + 2].score, play[3*(i - 1) + 2].games);
            attroff(COLOR_PAIR(103));
            count_copy --;
            }


            refresh();
        }
        if (i != 1)
        {
            if (count_copy > 0)
            {
                attron(COLOR_PAIR(11));
                mvprintw((LINES/2) - 4, (COLS/4) + 7, " %d- %s GOLD: %d SCORE: %d GAME: %d ", 3*(i - 1) + 1, play[3*(i - 1)].name, play[3*(i - 1)].gold, play[3*(i - 1)].score, play[3*(i - 1)].games);
                attroff(COLOR_PAIR(11));
                count_copy --;
            }


            if (count_copy > 0)
            {
            attron(COLOR_PAIR(11));
            mvprintw((LINES/2), (COLS/4) + 7, " %d- %s GOLD: %d SCORE: %d GAME: %d ", 3*(i - 1) + 2, play[3*(i - 1) + 1].name, play[3*(i - 1) + 1].gold, play[3*(i - 1) + 1].score, play[3*(i - 1) + 1].games);
            attroff(COLOR_PAIR(11));
            count_copy --;
            }


            if (count_copy > 0)
            {
            attron(COLOR_PAIR(11));
            mvprintw((LINES/2) + 4, (COLS/4) + 7, " %d- %s GOLD: %d SCORE: %d GAME: %d ", 3*(i - 1) + 3, play[3*(i - 1) + 2].name, play[3*(i - 1) + 2].gold, play[3*(i - 1) + 2].score, play[3*(i - 1) + 2].games);
            attroff(COLOR_PAIR(11));
            count_copy --;
            }


            refresh();
        }

    if (count_copy == 0)
    {
        count_copy = count;
    }
    }
}

void profile()
{
    clear_and_border();
    while (1)
    {
        if (player.line == -1)
        {
            attron(COLOR_PAIR(11));
            mvprintw(((LINES/2) - 6), (COLS/2) - 5,"        ");
            mvprintw(((LINES/2) - 5), (COLS/2) - 5," GUEST! ");
            mvprintw(((LINES/2)) - 4, (COLS/2) - 5,"        ");
            attroff(COLOR_PAIR(11));
            attron(COLOR_PAIR(11));
            mvprintw(((LINES/2)) -1, ((COLS/2) - 6) ," SCORE: %d ", player.score);
            attroff(COLOR_PAIR(11));
            attron(COLOR_PAIR(5));
            mvprintw(((LINES/2)) + 2, ((COLS/2) - 10) ,"                   ");
            mvprintw(((LINES/2)) + 3, ((COLS/2) - 10) ," PRESS Q TO LEAVE! ");
            mvprintw(((LINES/2)) + 4, ((COLS/2) - 10) ,"                   ");
            attroff(COLOR_PAIR(5));
            refresh();
        }
        
        else
        {
            attron(COLOR_PAIR(11));
            mvprintw(((LINES/2) - 8), (COLS/2) - (6 + (strlen(user[0])/2))," USERNAME: %s ", user[0]);
            mvprintw(((LINES/2)) - 4, ((COLS/2) - (6 + (strlen(user[1])/2))) ," PASSWORD: %s ", user[1]);
            mvprintw(((LINES/2)), ((COLS/2) - (4 + (strlen(user[2])/2))) ," EMAIL: %s ", user[2]);
            mvprintw(((LINES/2)) + 4, ((COLS/2) - 5) ," SCORE: %d ", player.score);
            attroff(COLOR_PAIR(11));
            attron(COLOR_PAIR(5));
            mvprintw(((LINES/2)) + 7, ((COLS/2) - 10) ,"                   ");
            mvprintw(((LINES/2)) + 8, ((COLS/2) - 10) ," PRESS Q TO LEAVE! ");
            mvprintw(((LINES/2)) + 9, ((COLS/2) - 10) ,"                   ");
            attroff(COLOR_PAIR(5));
            refresh();
        }
        char ch = getch();
        if (ch == 'q')
        {
            break;
        }
    }
}

int setting()
{
    int which_case = 1;
    while (1)
    {
        clear_and_border();
        if(player.hardness != 0)
        {
            mvprintw(((LINES/2) - 6), (COLS/2) + 28, "%d", player.hardness); 
            refresh();
        }
        if(player.color != 0)
        {
            mvprintw(((LINES/2)) - 2, ((COLS/2) + 28), "%d", player.color); 
            refresh();
        }


        attron(COLOR_PAIR(3));
        mvprintw(((LINES/2) - 6), (COLS/2) - 26," CHOOSE THE HARDNESS: (1: ESAY, 2: NORMAL, 3: HARD)");
        mvprintw(((LINES/2)) - 2, ((COLS/2) - 26) ," CHOOSE THE COLOR: (1: YELLOW, 2: BLUE, 3: GREEN) ");
        mvprintw(((LINES/2)) + 2, ((COLS/2) - 14) ," CHOOSE THE SONG: (1, 2, 3) ");
        mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
        attroff(COLOR_PAIR(3));
        refresh();
        for(int ch = getch(); ch != 10; ch = getch())
        {
            if (ch == KEY_UP)
            {
                which_case --;
                if (which_case == 0)
                {
                    which_case = 4;
                }
            }
            if ((ch == KEY_DOWN))
            {
                which_case ++;
                if (which_case == 5)
                {
                    which_case = 1;
                }
            }

            switch (which_case)
            {
            
            case 1:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 26) ," CHOOSE THE COLOR: (1: YELLOW, 2: BLUE, 3: GREEN) ");
                mvprintw(((LINES/2)) + 2, ((COLS/2) - 14) ," CHOOSE THE SONG: (1, 2, 3) ");
                mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2) - 6), (COLS/2) - 26," CHOOSE THE HARDNESS: (1: ESAY, 2: NORMAL, 3: HARD)");
                attroff(COLOR_PAIR(4));

                break;

            case 2:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 6), (COLS/2) - 26," CHOOSE THE HARDNESS: (1: ESAY, 2: NORMAL, 3: HARD)");
                mvprintw(((LINES/2)) + 2, ((COLS/2) - 14) ," CHOOSE THE SONG: (1, 2, 3) ");
                mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 26) ," CHOOSE THE COLOR: (1: YELLOW, 2: BLUE, 3: GREEN) ");
                attroff(COLOR_PAIR(4));
                break;

            case 3:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 6), (COLS/2) - 26," CHOOSE THE HARDNESS: (1: ESAY, 2: NORMAL, 3: HARD)");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 26) ," CHOOSE THE COLOR: (1: YELLOW, 2: BLUE, 3: GREEN) ");
                mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) + 2, ((COLS/2) - 14) ," CHOOSE THE SONG: (1, 2, 3) ");
                attroff(COLOR_PAIR(4));
                break;

            case 4:
                attron(COLOR_PAIR(3));
                mvprintw(((LINES/2) - 6), (COLS/2) - 26," CHOOSE THE HARDNESS: (1: ESAY, 2: NORMAL, 3: HARD)");
                mvprintw(((LINES/2)) - 2, ((COLS/2) - 26) ," CHOOSE THE COLOR: (1: YELLOW, 2: BLUE, 3: GREEN) ");
                mvprintw(((LINES/2)) + 2, ((COLS/2) - 14) ," CHOOSE THE SONG: (1, 2, 3) ");
                attroff(COLOR_PAIR(3));
                attron(COLOR_PAIR(4));
                mvprintw(((LINES/2)) + 6, ((COLS/2) - 4) ," BACK ");
                attroff(COLOR_PAIR(4));
                break;

            }
        }
        refresh();

        switch (which_case)
        {
            case 1:
                move(((LINES/2) - 6), (COLS/2) + 28);
                curs_set(true);
                echo();
                refresh();
                if (scanw("%d", &player.hardness) == 1 && player.hardness <= 3 && player.hardness >= 1)
                {
                    move(0, 0);
                    curs_set(false);
                    noecho();
                    continue; 
                }
                else
                {
                    player.hardness = 0;
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 15), "                            " );
                    mvprintw(((LINES/8)), (COLS/2 - 15), " PLEASE ENTER CORRECT ITEM! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 15), "                            " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(3);
                    attron(COLOR_PAIR(100));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 15), "                            " );
                    mvprintw(((LINES/8)), (COLS/2 - 15), " PLEASE ENTER CORRECT ITEM! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 15), "                            " );
                    attroff(COLOR_PAIR(100));
                    continue;
                }

            case 2:
                move(((LINES/2) - 2), (COLS/2) + 28);
                curs_set(true);
                echo();
                refresh();
                if (scanw("%d", &player.color) == 1 && player.color <= 3 && player.color >= 1)
                {
                    move(0, 0);
                    curs_set(false);
                    noecho();
                    continue; 
                }
                else
                {
                    player.color = 0;
                    curs_set(false);
                    noecho(); 
                    attron(COLOR_PAIR(5));
                    mvprintw(((LINES/8) - 1), (COLS/2 - 15), "                            " );
                    mvprintw(((LINES/8)), (COLS/2 - 15), " PLEASE ENTER CORRECT ITEM! " );
                    mvprintw(((LINES/8) + 1), (COLS/2 - 15), "                            " );
                    attroff(COLOR_PAIR(5));
                    refresh();
                    sleep(3);
                    continue;
                }

            case 3:
                break;

            case 4:
                return 4;
        }
    }
}

void elemnts_under_board()
{
    attron(A_BOLD);
    attron(COLOR_PAIR(11));
    for (int i = 2; i < COLS - 2; i++)
    {
        mvprintw(LINES - 4, i, " ");
    }
    for (int i = 2; i < COLS - 2; i++)
    {
        mvprintw(LINES - 3, i, " ");
    }

    mvprintw(LINES - 3, 2, " Level: %d ", player.level);
    mvprintw(LINES - 3, (COLS/5) + 2, " Gold: %d ", player.gold);
    mvprintw(LINES - 3, 2*(COLS/5) + 2, " Hit: ");
    attroff(COLOR_PAIR(11));

    attron(COLOR_PAIR(5));
    for (int i = 0; i < first_life; i++)
    {
            mvprintw(LINES - 3, 2*(COLS/5) + 8 + i," ");
    }
    for (int i = 0; i < player.life_time; i++)
    {
        mvprintw(LINES - 3, 2*(COLS/5) + 8 + i,"#");
    }
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(11));
    mvprintw(LINES - 3, 3*(COLS/5) + 2, " Hunger: ");
    attroff(COLOR_PAIR(11));

    attron(COLOR_PAIR(5));
    for (int i = 0; i < 20; i++)
    {
            mvprintw(LINES - 3, 3*(COLS/5) + 12 + i," ");
    }
    for (int i = 0; i < player.hungry_amount; i++)
    {
        mvprintw(LINES - 3, 3*(COLS/5) + 12 + i,"#");
    }
    attroff(COLOR_PAIR(5));

    attron(COLOR_PAIR(11));
    mvprintw(LINES - 3, 4*(COLS/5) + 2, " Weapon: ");
    switch (player.main_selah)
    {
    case 1:
        wchar_t emoji[] = L"🪓";
        mvaddwstr(LINES - 3, 4*(COLS/5) + 11, emoji);
        break;
    
    case 2:
        wchar_t emoji1[] = L"🗡️";
        mvaddwstr(LINES - 3, 4*(COLS/5) + 11, emoji1);
        break;

    case 3:
        wchar_t emoji2[] = L"🪄";
        mvaddwstr(LINES - 3, 4*(COLS/5) + 11, emoji2);
        break;

    case 4:
        wchar_t emoji3[] = L"🏹";
        mvaddwstr(LINES - 3, 4*(COLS/5) + 11, emoji3);
        break;

    case 5:
        wchar_t emoji4[] = L"⚔️";
        mvaddwstr(LINES - 3, 4*(COLS/5) + 11, emoji4);
        break;

    }

    for (int i = 2; i < COLS - 2; i++)
    {
        mvprintw(LINES - 2, i, " ");
    }
    attroff(COLOR_PAIR(11));
    attroff(A_BOLD);

    refresh();
}

void copy_map()
{
    for (int i = 0; i < LINES - 10; i++)
    {
        for (int j = 0; j < COLS - 2; j++)
        {
            if (all_map[i][j] != '^')
            {
                map_whithout_tale[i][j] = all_map[i][j];
            }
            else
            {
                map_whithout_tale[i][j] = '.';
            }
        }
    }
}

void elements_on_map()
{
    srand(time(0));
    for (int i = 0; i < LINES - 10; i++)
    {
        for (int j = 0; j < COLS - 2; j++)
        {
            int roomi = which_room_is_the_player(i, j);
            int gold;
            int black_gold;
            int food;
            int telesm;
            int sotoon;
            int enemy;
            int selah;

            if (rooms[roomi].type == 4)
            {
                black_gold = rand()%40;
                gold = rand()%10;
                telesm = 1;
                enemy = 1;
            }

            if (rooms[roomi].type == 3)
            {
                black_gold = rand()%160;
                gold = rand()%40;
                telesm = rand()%70;
                enemy = 1;
            }

            else 
            {
                gold = rand()%40;
                black_gold = rand()%160;
                telesm = rand()%120;
                enemy = rand()%50;
            }

            sotoon = rand()%40;
            food = rand()%80;
            selah = rand()%120;

            int tale_random;
            switch (player.hardness)
            {
            case 1:
                tale_random = 70;
                break;
            
            case 2:
                tale_random = 60;
                break;

            case 3:
                tale_random = 50;
                break;
            }

            int tale = rand()%tale_random;

            if (all_map[i][j] == '.' && !sotoon)
            {
                all_map[i][j] = 'o';
            }

            if (all_map[i][j] == '.' && !gold)
            {
                all_map[i][j] = 'C';
            }

            if (all_map[i][j] == '.' && !tale)
            {
                all_map[i][j] = '^';
            }

            if (all_map[i][j] == '.' && !black_gold)
            {
                all_map[i][j] = 'B';
            }

            if (all_map[i][j] == '.' && !selah)
            {
                //dagger 0
                //Magic 1
                //arrow 3
                //sword 4
                int which_food = rand()%4;
                
                if (which_food == 0)
                {
                    all_map[i][j] = '2';
                }
                
                if (which_food == 1)
                {
                    all_map[i][j] = '3';
                }

                if (which_food == 2)
                {
                    all_map[i][j] = '4';
                }

                if (which_food == 3)
                {
                    all_map[i][j] = '5';
                }
            }


            if (count_enemy < 6)
            {
                if (all_map[i][j] == '.' && !enemy)
                {
                    //deamon 0
                    //monster 1
                    //giant 2
                    //snake 3
                    //undeed 4
                    int which_food = rand()%5;
                    
                    if (which_food == 0)
                    {
                        all_map[i][j] = 'D';
                        enemies[count_enemy].life_time = 5;
                        enemies[count_enemy].x = i + 6;
                        enemies[count_enemy].y = j + 2;
                        enemies[count_enemy].type = 1;
                        enemies[count_enemy].room_i = which_room_is_the_player(i + 5, j + 1);
                        count_enemy ++;
                    }
                    
                    if (which_food == 1)
                    {
                        all_map[i][j] = 'F';
                        enemies[count_enemy].life_time = 10;
                        enemies[count_enemy].x = i + 6;
                        enemies[count_enemy].y = j + 2;
                        enemies[count_enemy].type = 2;
                        enemies[count_enemy].room_i = which_room_is_the_player(i + 5, j + 1);
                        count_enemy ++;
                    }

                    if (which_food == 2)
                    {
                        all_map[i][j] = 'G';
                        enemies[count_enemy].life_time = 15;
                        enemies[count_enemy].x = i + 6;
                        enemies[count_enemy].type = 3;
                        enemies[count_enemy].y = j + 2;
                        enemies[count_enemy].room_i = which_room_is_the_player(i + 5, j + 1);
                        count_enemy ++;
                    }

                    if (which_food == 3)
                    {
                        all_map[i][j] = 'S';
                        enemies[count_enemy].life_time = 20;
                        enemies[count_enemy].x = i + 6;
                        enemies[count_enemy].type = 4;
                        enemies[count_enemy].y = j + 2;
                        enemies[count_enemy].room_i = which_room_is_the_player(i + 5, j + 1);
                        count_enemy ++;
                    }

                    if (which_food == 4)
                    {
                        all_map[i][j] = 'U';
                        enemies[count_enemy].life_time = 30;
                        enemies[count_enemy].x = i + 6;
                        enemies[count_enemy].type = 5;
                        enemies[count_enemy].y = j + 2;
                        enemies[count_enemy].room_i = which_room_is_the_player(i + 5, j + 1);
                        count_enemy ++;
                    }
                    count_enemy ++;
                }

            }       

            if (all_map[i][j] == '.' && !food)
            {
                //ordinary 0 1 
                //fased 2
                //aala 3
                //magic 4
                int which_food = rand()%5;
                
                if (which_food == 0 || which_food == 1 || which_food == 2)
                {
                    all_map[i][j] = 'O';
                }
                
                if (which_food == 3)
                {
                    all_map[i][j] = 'A';
                }

                if (which_food == 4)
                {
                    all_map[i][j] = 'M';
                }
            }

            if (all_map[i][j] == '.' && !telesm)
            {
                //Health 0 
                //fased 1
                //aala 2
                int which_food = rand()%3;
                
                if (which_food == 0)
                {
                    all_map[i][j] = 'H';
                }
                
                if (which_food == 1)
                {
                    all_map[i][j] = 'J';
                }

                if (which_food == 2)
                {
                    all_map[i][j] = 'V';
                }
            }

        }
    }

}

void random_first_map()
{
    int which_map = rand()%8;
    int row, col;
    switch (which_map) 
    {
    case 0:
        row = 0;
        col = 0;
        break;

    case 1:
        row = 0;
        col = (COLS - 2) / 4;
        break;

    case 2:
        row = 0;
        col = 2 * (COLS - 2) / 4;
        break;

    case 3:
        row = 0;
        col = 3 * (COLS - 2) / 4;
        break;

    case 4:
        row = ((LINES - 10) / 2);
        col = 0;
        break;

    case 5:
        row = ((LINES - 10) / 2);
        col = (COLS - 2) / 4;
        break;

    case 6:
        row = ((LINES - 10) / 2);
        col = 2 * (COLS - 2) / 4 ;
        break;

    case 7:
        row = (LINES - 10) / 2;
        col = 3 * (COLS - 2) / 4;
        break;

    }
    int okey = 0;
    for (int i = row; i < row + (LINES - 10)/2; i++)
    {
        for (int j = col; j < col + (COLS - 2)/4; j++)
        {
            if (map_whithout_tale[i][j] != ' ' && map_whithout_tale[i][j] != '#')
            {
                map_that_shown[i][j] = map_whithout_tale[i][j];

                if (!okey && all_map[i][j] == '.')
                {
                    player.x = i + 6;
                    player.y = j + 2;
                    okey ++;
                }
            }
        }
    }

    player.room_i = which_room_is_the_player(player.x, player.y);
    if (rooms[player.room_i].type == 0 || rooms[player.room_i].type == 1 || rooms[player.room_i].type == 2)
    {
        alert("You Are Now In A Ordinary Room!", "", -1);
    }

    else if (rooms[player.room_i].type == 3)
    {
        alert("You Are Now In A Telesm Room!", "", -1);
    }
}

void print_map()
{
    move(6, 2);
    for (int i = 0; i < LINES - 10; i++)
    {
        for (int j = 0; j < COLS - 2; j++)
        {
            if (map_that_shown[i][j] == '#')
            {
                attron(COLOR_PAIR(41));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(41));
                refresh();
                continue;
            }
            if (map_that_shown[i][j] == 'D')
            {
                attron(COLOR_PAIR(75));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(75));
                refresh();
                continue;
            }
            if (map_that_shown[i][j] == 'F')
            {
                attron(COLOR_PAIR(76));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(76));
                refresh();
                continue;
            }
            if (map_that_shown[i][j] == 'G')
            {
                attron(COLOR_PAIR(77));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(77));
                refresh();
                continue;
            }
            if (map_that_shown[i][j] == 'S')
            {
                attron(COLOR_PAIR(78));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(78));
                refresh();
                continue;
            }
            if (map_that_shown[i][j] == 'U')
            {
                attron(COLOR_PAIR(79));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(79));
                refresh();
                continue;
            }


            if (map_that_shown[i][j] == '2')
            {
                attron(COLOR_PAIR(76));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(76));
                refresh();
                continue;
            }
            if (map_that_shown[i][j] == '3')
            {
                attron(COLOR_PAIR(77));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(77));
                refresh();
                continue;
            }
            if (map_that_shown[i][j] == '4')
            {
                attron(COLOR_PAIR(78));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(78));
                refresh();
                continue;
            }
            if (map_that_shown[i][j] == '5')
            {
                attron(COLOR_PAIR(79));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(79));
                refresh();
                continue;
            }
            if (map_that_shown[i][j] == 'H')
            {
                attron(COLOR_PAIR(53));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(53));
                refresh();
                continue;
            }
            if (map_that_shown[i][j] == 'J')
            {
                attron(COLOR_PAIR(54));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(54));
                refresh();
                continue;
            }
            if (map_that_shown[i][j] == 'V')
            {
                attron(COLOR_PAIR(55));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(55));
                refresh();
                continue;
            }
            if (map_that_shown[i][j] == 'A')
            {
                attron(COLOR_PAIR(63));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(63));
                refresh();
                continue;
            }
            if (map_that_shown[i][j] == 'O')
            {
                attron(COLOR_PAIR(64));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(64));
                refresh();
                continue;
            }
            if (map_that_shown[i][j] == 'M')
            {
                attron(COLOR_PAIR(65));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(65));
                refresh();
                continue;
            }
    

            if (map_that_shown[i][j] == 'B')
            {
                attron(COLOR_PAIR(40));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(40));
                continue;
            }

            if (map_that_shown[i][j] == '>' || map_that_shown[i][j] == '?')
            {
                attron(COLOR_PAIR(42));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(42));
                refresh();
                continue;
            }

            if (map_that_shown[i][j] == 'C')
            {
                attron(COLOR_PAIR(16));
                printw("%c", map_that_shown[i][j]);
                attroff(COLOR_PAIR(16));
                continue;
            }
            if (map_that_shown[i][j] == 'o')
            {
                printw("%c", map_that_shown[i][j]);
                continue;
            }
            attron(COLOR_PAIR(15));
            printw("%c", map_that_shown[i][j]);
            attroff(COLOR_PAIR(15));
        }
        move(6 + i + 1, 2);
    }
    refresh(); 
}

void enemies_move()
{
    srand(time(0));
    int pa_x;
    int pa_y;
    for (int i = 0; i < count_enemy; i++)
    {
        if (enemies[i].room_i == player.room_i && map_that_shown[enemies[i].x - 6][enemies[i].y - 2] != ' ' && (enemies[i].type == 3 || enemies[i].type == 4 || enemies[i].type == 5))
        {
            if (abs(enemies[i].x - player.x) <= 1 && abs(enemies[i].y - player.y) <= 1) 
            {
                player.life_time -= 1;
                alert("An Enemy Damaged You!","", -2 );
                elemnts_under_board();
            }
            else 
            {
                int random = rand()%2;
                pa_x = enemies[i].x;
                pa_y = enemies[i].y;

                if (random)
                {
                    if (player.x > enemies[i].x && all_map[enemies[i].x - 5][enemies[i].y - 2] == '.')
                    {
                        enemies[i].x += 1;
                    }
                    else if (player.x < enemies[i].x && all_map[enemies[i].x - 7][enemies[i].y - 2] == '.')
                    {
                        enemies[i].x -= 1;
                    }
                }

                else 
                {
                    if (player.y > enemies[i].y && all_map[enemies[i].x - 6][enemies[i].y - 1] == '.')
                    {
                        enemies[i].y += 1;
                    }
                    else if (player.y < enemies[i].y && all_map[enemies[i].x - 6][enemies[i].y - 3] == '.')
                    {
                        enemies[i].y -= 1;
                    }
                }
                if (enemies[i].type == 3)
                {
                    all_map[enemies[i].x - 6][enemies[i].y - 2] = 'G';
                    map_that_shown[enemies[i].x - 6][enemies[i].y - 2] = 'G';
                    map_whithout_tale[enemies[i].x - 6][enemies[i].y - 2] = 'G';


                }

                else if (enemies[i].type == 4)
                {
                    all_map[enemies[i].x - 6][enemies[i].y - 2] = 'S';
                    map_whithout_tale[enemies[i].x - 6][enemies[i].y - 2] = 'S';
                    map_that_shown[enemies[i].x - 6][enemies[i].y - 2] = 'S';
                }

                else
                {
                    all_map[enemies[i].x - 6][enemies[i].y - 2] = 'U';
                    map_whithout_tale[enemies[i].x - 6][enemies[i].y - 2] = 'U';
                    map_that_shown[enemies[i].x - 6][enemies[i].y - 2] = 'U';
                }



                if (pa_x != enemies[i].x || pa_y != enemies[i].y)
                {
                    all_map[pa_x - 6][pa_y - 2] = '.';
                    map_whithout_tale[pa_x - 6][pa_y - 2] = '.';
                    map_that_shown[pa_x - 6][pa_y - 2] = '.';
                }
                print_map();
                refresh();
            }

        }
        else if (enemies[i].room_i == player.room_i && map_that_shown[enemies[i].x - 6][enemies[i].y - 2] != ' ')
        {
            if (abs(enemies[i].x - player.x) <= 1 && abs(enemies[i].y - player.y) <= 1) 
            {
                player.life_time -= 1;
                alert("An Enemy Damaged You!","", -2 );
                elemnts_under_board();
            } 
        }
    }
}

void damage()
{
    for (int i = 0; i < count_enemy; i++)
    {
        if (abs(enemies[i].x - player.x) <= 1 && abs(enemies[i].y - player.y) <= 1) 
        {
            switch (player.main_selah)
            {
            case 1:
                enemies[i].life_time -= 5;
                break;
            
            case 2:
                enemies[i].life_time -= 12;
                player.count_selahs[1] -= 1;
                break;

            case 3:
                enemies[i].life_time -= 15;
                player.count_selahs[2] -= 1;
                break;

            case 4:
                enemies[i].life_time -= 5;
                player.count_selahs[3] -= 1;
                break;

            case 5:
                enemies[i].life_time -= 10;
                break;
            }
            alert("YOU Damaged An Enemy!","", -1 );
            elemnts_under_board();
            if (enemies[i].life_time <= 0)
            {
                alert("YOU Killed An Enemy!","", -1 );
                all_map[enemies[i].x - 6][enemies[i].y - 2] = '.';
                map_that_shown[enemies[i].x - 6][enemies[i].y - 2] = '.';
                map_whithout_tale[enemies[i].x - 6][enemies[i].y - 2] = '.';
                for (int j = i; j < count_enemy - 1; j++)
                {
                    enemies[j] = enemies[j + 1];
                }
                count_enemy --;
                player.score += 2;
                print_map();
                refresh();
            }
        }
    }
}

int player_move(int x_pa, int y_pa, int g_on_off)
{
    player.hungry_amount += 0.0675;
    print_map();

    if (g_on_off == 1)
    {
        goto whith_g_key;
    }

    if (all_map[player.x - 6][player.y - 2] == '^')
    {
        map_that_shown[player.x - 6][player.y - 2] = '^';
        player.x = x_pa;
        player.y = y_pa;
        print_map();
        player.life_time --;
    }

    if (map_that_shown[player.x - 6][player.y - 2] == 'C')
    {
        int random;
        switch (player.hardness)
        {
        case 1:
            random = 40;
            break;
        
        case 2:
            random = 30;
            break;

        case 3:
            random = 20;
            break;
        }

        // int random;
        // switch (which_room)
        // {
        // case 1:
        //     random = 40;
        //     break;
        
        // case 2:
        //     random = 30;
        //     break;

        // case 3:
        //     random = 20;
        //     break;
        // }

        int gold = rand()%random;
        alert("You've got", "Gold!", gold);
        player.gold += gold;
        player.score += gold;
        map_that_shown[player.x - 6][player.y - 2] = '.';
        map_whithout_tale[player.x - 6][player.y - 2] = '.';
        all_map[player.x - 6][player.y - 2] = '.';
        print_map();
    }

    if (map_that_shown[player.x - 6][player.y - 2] == 'B')
    {
        int random;
        switch (player.hardness)
        {
        case 1:
            random = 120;
            break;
        
        case 2:
            random = 90;
            break;

        case 3:
            random = 60;
            break;
        }

        // int random;
        // switch (which_room)
        // {
        // case 1:
        //     random = 40;
        //     break;
        
        // case 2:
        //     random = 30;
        //     break;

        // case 3:
        //     random = 20;
        //     break;
        // }

        int gold = rand()%random + 20;
        alert("You've got", "Black Gold!", gold);
        player.gold += gold;
        player.score += gold;
        map_that_shown[player.x - 6][player.y - 2] = '.';        
        map_whithout_tale[player.x - 6][player.y - 2] = '.';
        all_map[player.x - 6][player.y - 2] = '.';

        print_map();
    }

    if (all_map[player.x - 6][player.y - 2] == '#')
    {
        updating_ways_that_shown(player.x, player.y);
        print_map();
        if (all_map[player.x - 5][player.y - 2] == '+' && map_that_shown[player.x - 5][player.y - 2] != '+')
        {
            updating_room_that_shown(0);
        }

        if (all_map[player.x - 6][player.y - 3] == '+' && map_that_shown[player.x - 6][player.y - 3] != '+')
        {
            updating_room_that_shown(1);
        }

        if (all_map[player.x - 6][player.y - 1] == '+'&& map_that_shown[player.x - 6][player.y - 1] != '+')
        {
            updating_room_that_shown(2);
        }

        if (all_map[player.x - 7][player.y - 2] == '+' && map_that_shown[player.x - 7][player.y - 2] != '+')
        {
            updating_room_that_shown(3);
        }
    }

    if (all_map[player.x - 6][player.y - 2] == '+')
    {
            updating_ways_that_shown(player.x, player.y);
            print_map();
    }

    if (all_map[player.x - 6][player.y - 2] == '>')
    {
        map_that_shown[player.x - 6][player.y - 2] = all_map[player.x - 6][player.y - 2];
        print_map;
    }

    if (all_map[player.x - 6][player.y - 2] == '?')
    {
        player.level += 1;
        return 2;
    }

    if (all_map[player.x - 6][player.y - 2] == 'o')
    {
        player.x = x_pa;
        player.y = y_pa;
    } 

    if (all_map[player.x - 6][player.y - 2] == 'H')
    {
        player.telesm[0] += 1;
        alert("You've got A Health Enchant!", "", -1);
        map_that_shown[player.x - 6][player.y - 2] = '.';
        map_whithout_tale[player.x - 6][player.y - 2] = '.';
        all_map[player.x - 6][player.y - 2] = '.';
        print_map();
    }

    if (all_map[player.x - 6][player.y - 2] == 'J')
    {
        player.telesm[1] += 1;
        alert("You've got A Damage Enchant!", "", -1);
        map_that_shown[player.x - 6][player.y - 2] = '.';
        map_whithout_tale[player.x - 6][player.y - 2] = '.';
        all_map[player.x - 6][player.y - 2] = '.';
        print_map();
    }

    if (all_map[player.x - 6][player.y - 2] == 'V')
    {
        player.telesm[2] += 1;
        alert("You've got A Speed Enchant!", "", -1);
        map_that_shown[player.x - 6][player.y - 2] = '.';
        map_whithout_tale[player.x - 6][player.y - 2] = '.';
        all_map[player.x - 6][player.y - 2] = '.';
        print_map();
    }

    if (all_map[player.x - 6][player.y - 2] == 'O')
    {
        int what = rand()%2;
        if (what == 0)
        {
            player.foods[0].count += 1;
            alert("You've got Some Ordinary Food! (But It Could Be A Lie!)", "", -1);
            map_that_shown[player.x - 6][player.y - 2] = '.';
            map_whithout_tale[player.x - 6][player.y - 2] = '.';
            all_map[player.x - 6][player.y - 2] = '.';
            print_map();
        }

        else if (what == 1)
        {
            player.foods[3].count += 1;
            alert("You've got Some Ordinary Food! (But It Could Be A Lie!)", "", -1);
            map_that_shown[player.x - 6][player.y - 2] = '.';
            map_whithout_tale[player.x - 6][player.y - 2] = '.';
            all_map[player.x - 6][player.y - 2] = '.';
            print_map();
        }
    }

    if (all_map[player.x - 6][player.y - 2] == 'M')
    {
            player.foods[1].count += 1;
            alert("You've got Some Magic Food!", "", -1);
            map_that_shown[player.x - 6][player.y - 2] = '.';
            map_whithout_tale[player.x - 6][player.y - 2] = '.';
            all_map[player.x - 6][player.y - 2] = '.';
            print_map();
    }

    if (all_map[player.x - 6][player.y - 2] == 'A')
    {
            player.foods[2].count += 1;
            alert("You've got Some Great Food!", "", -1);
            map_that_shown[player.x - 6][player.y - 2] = '.';
            map_whithout_tale[player.x - 6][player.y - 2] = '.';
            all_map[player.x - 6][player.y - 2] = '.';
            print_map();
    }

    if (all_map[player.x - 6][player.y - 2] == '2')
    {
        player.count_selahs[1] += 10;
        alert("You've got 10 Dragger!", "", -1);
        map_that_shown[player.x - 6][player.y - 2] = '.';
        map_whithout_tale[player.x - 6][player.y - 2] = '.';
        all_map[player.x - 6][player.y - 2] = '.';
        print_map();
    }

    if (all_map[player.x - 6][player.y - 2] == '3')
    {
        player.count_selahs[2] += 8;
        alert("You've got 8 Magic Wand!", "", -1);
        map_that_shown[player.x - 6][player.y - 2] = '.';
        map_whithout_tale[player.x - 6][player.y - 2] = '.';
        all_map[player.x - 6][player.y - 2] = '.';
        print_map();
    }

    if (all_map[player.x - 6][player.y - 2] == '4')
    {
        player.count_selahs[3] += 20;
        alert("You've got 20 Normal Arrow!", "", -1);
        map_that_shown[player.x - 6][player.y - 2] = '.';
        map_whithout_tale[player.x - 6][player.y - 2] = '.';
        all_map[player.x - 6][player.y - 2] = '.';
        print_map();
    }

    if (all_map[player.x - 6][player.y - 2] == '5')
    {
        player.count_selahs[4] = 1;
        alert("You've got Sword!", "", -1);
        map_that_shown[player.x - 6][player.y - 2] = '.';
        map_whithout_tale[player.x - 6][player.y - 2] = '.';
        all_map[player.x - 6][player.y - 2] = '.';
        print_map();
    }


















    whith_g_key:

    if (all_map[player.x - 6][player.y - 2] == '$' || all_map[player.x - 6][player.y - 2] == '|' || all_map[player.x - 6][player.y - 2] == '-' || all_map[player.x - 6][player.y - 2] == ' ')
    {
        player.x = x_pa;
        player.y = y_pa;
    }
    
    int color;
    switch (player.color)
    {
    case 1:
        color = 31;
        break;
    
    case 2:
        color = 32;
        break;

    case 3:
        color = 33;
        break;
    }
    elemnts_under_board();
    attron(COLOR_PAIR(color));
    mvprintw(player.x, player.y, "@");
    attroff(COLOR_PAIR(color));
    refresh();
    return 1;

}

int new_game(int new)
{
    if (new == 2)
    {
        clear_and_border2();
        elemnts_under_board();
        map();
        connect_room();
        elements_on_map();
        copy_map();
        alert("LEVEL UPS! YOU ARE NOW IN LEVEL", "", player.level);
        sleep(3);
        random_first_map();
        adding_stairs();
        copy_map();
        player_move(0, 0, 0);
    }

    if (new == 1)
    {
        if (player.color > 3 || player.color < 1)
        {
            player.color = 1;
        }
        if (player.hardness > 3 || player.hardness < 1)
        {
            player.hardness = 1;
        }
        if (player.hardness == 1)
        {
            player.life_time = 25;
            player.hungry_amount = 0;
        }
        else if (player.hardness == 2)
        {
            player.life_time = 21;
            player.hungry_amount = 2;
        }
        else if (player.hardness == 3)
        {
            player.life_time = 17; 
            player.hungry_amount = 4;  
        }
        first_life = player.life_time;
        player.level = 1;
        player.gold = 0;
        player.score = 0;
        player.main_selah = 1;

        for (int j = 0; j < 4; j++)
        {
            player.foods[j].count = 0;
            player.foods[j].time = 30;
            player.count_selahs[j+1] = 0;
        }

        for (int j = 0; j < 3; j++)
        {
            player.telesm[j] = 0;
        }
        clear_and_border2();
        elemnts_under_board();
        map();
        for (int i = 0; i < 6; i++)
        {
            enemies[i].life_time = 0;
            enemies[i].x = 0;
            enemies[i].y = 0;
            enemies[i].room_i = 0;
        }
        connect_room();
        elements_on_map();
        copy_map();
        random_first_map();
        adding_stairs();
        copy_map();
        player_move(0, 0, 0);
        refresh();
    }   

    int ganj_room = 0;
    int m_on_off = 0;
    int g_on_off = 0;
    for(int ch = getch(); ch != 'q'; ch = getch())
    {
        player.room_i = which_room_is_the_player(player.x, player.y);
        enemies_move();
        if (speed)
        {
            speed --;
        }
        if (ganj_room == 10)
        {
            attron(COLOR_PAIR(11));
            mvprintw((LINES/2) - 2, (COLS/2) - 8, "                                      ");
            mvprintw((LINES/2) - 1 , (COLS/2) - 8, "           CONGRATULATIONS!           ");
            mvprintw((LINES/2), (COLS/2) - 8, "                                      ");
            mvprintw((LINES/2) + 1, (COLS/2) - 8, " YOU WON! I HOPE YOU ENJOYED THE GAME ");
            mvprintw((LINES/2) + 2, (COLS/2) - 8, "                                      ");
            attroff(COLOR_PAIR(11));
            refresh();
            sleep(3);
            break;
        }
        if (rooms[player.room_i].type == 4)
        {
            ganj_room ++;
        }
        if (player.hungry_amount < 5 && player.life_time < 25)
        {
            player.life_time += 0.0675;
        }

        if (player.hungry_amount > 17)
        {
            player.life_time -= 0.0675;
        }

        if (player.life_time <= 0)
        {
            attron(COLOR_PAIR(5));
            mvprintw((LINES/2) - 2, (COLS/2) - 8, "               ");
            mvprintw((LINES/2) - 1 , (COLS/2) - 8, "   YOU DIED!   ");
            mvprintw((LINES/2), (COLS/2) - 8, "               ");
            mvprintw((LINES/2) + 1, (COLS/2) - 8, " GAME IS OVER! ");
            mvprintw((LINES/2) + 2, (COLS/2) - 8, "               ");
            attroff(COLOR_PAIR(5));
            refresh();
            sleep(3);
            break;
        }
        int up;
        switch(ch)
        {
            case (56):
                player.x --;
                up = player_move(player.x + 1, player.y, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                if(speed)
                {
                    player.x --;
                }
                up = player_move(player.x + 1, player.y, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                g_on_off = 0;
                break;

            case (54):
                player.y ++;
                up = player_move(player.x, player.y - 1, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                if(speed)
                {
                    player.y ++;
                }
                up = player_move(player.x, player.y - 1, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                g_on_off = 0;
                break;

            case (52):
                player.y --;
                up = player_move(player.x, player.y + 1, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                if(speed)
                {
                    player.y --;
                }
                up = player_move(player.x, player.y + 1, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                g_on_off = 0;
                break;

            case (50):
                player.x ++;
                up = player_move(player.x - 1, player.y, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                if(speed)
                {
                    player.x ++;
                }
                up = player_move(player.x - 1, player.y, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                g_on_off = 0;
                break;

            case (51):
                player.x ++;
                player.y ++;
                up = player_move(player.x - 1, player.y - 1, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                if(speed)
                {
                    player.y ++;
                    player.x ++;
                }
                up = player_move(player.x - 1, player.y - 1, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                g_on_off = 0;
                break;

            case (49):
                player.x ++;
                player.y --;
                up = player_move(player.x - 1, player.y + 1, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                if(speed)
                {
                    player.y --;
                    player.x ++;
                }
                up = player_move(player.x - 1, player.y + 1, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                g_on_off = 0;
                break;

            case (55):
                player.x --;
                player.y --;
                up = player_move(player.x + 1, player.y + 1, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                if(speed)
                {
                    player.y --;
                    player.x --;
                }
                up = player_move(player.x + 1, player.y + 1, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                g_on_off = 0;
                break;

            case (57):
                player.x --;
                player.y ++;
                up = player_move(player.x + 1, player.y - 1, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                if(speed)
                {
                    player.y ++;
                    player.x --;
                }
                up = player_move(player.x + 1, player.y - 1, g_on_off);
                if (up == 2)
                {
                    return 11;
                }
                g_on_off = 0;
                break;

            case ('m'):
                if (m_on_off == 0)
                {
                    print_all_map();
                    m_on_off = 1;
                }
                else
                {
                    clear_and_border2();
                    elemnts_under_board();
                    m_on_off = 0; 
                    up = player_move(player.x, player.y, g_on_off);
                    if (up == 2)
                    {
                        return 11;
                    }
                }
                break;


            case ('g'):
                g_on_off = 1;
                break;

            case ('f'):
                food_menu();
                clear_and_border2();
                elemnts_under_board();
                up = player_move(player.y, player.y, 0);
                break;

            case ('w'):
                weapon_menu();
                clear_and_border2();
                elemnts_under_board();
                up = player_move(player.y, player.y, 0);
                break;

            case ('t'):
                telesm_menu();
                clear_and_border2();
                elemnts_under_board();
                up = player_move(player.y, player.y, 0);
                break;

            case (32):
                damage();
                elemnts_under_board();
                up = player_move(player.y, player.y, 0);
                break;
        }
    }

    if (player.line != -1)
    {
        save_score(0);
    }

    if (player.line == -1 || (player.room_i == 2 && player.level == 4) || player.life_time == 0)
    {
        return 4;
    }

    save_maps();

    return 4;

}

void resume()
{
    which_user(which_line_user);
    map_whithout_tale = (char **) malloc ((LINES - 10)*sizeof(char *));
    for (int i = 0; i < (LINES - 10); i++)
    {
        map_whithout_tale[i] = (char *) malloc((COLS - 2) * sizeof(char));
        for (int j = 0; j < (COLS - 2); j++)
        {
            map_whithout_tale[i][j] = ' ';
        }
    }  

    map_that_shown = (char **) malloc ((LINES - 10)*sizeof(char *));
    for (int i = 0; i < (LINES - 10); i++)
    {
        map_that_shown[i] = (char *) malloc((COLS - 2) * sizeof(char));
        for (int j = 0; j < (COLS - 2); j++)
        {
            map_that_shown[i][j] = ' ';
        }
    }  

    all_map = (char **) malloc ((LINES - 10)*sizeof(char *));
    for (int i = 0; i < (LINES - 10); i++)
    {
        all_map[i] = (char *) malloc((COLS - 2) * sizeof(char));
        for (int j = 0; j < (COLS - 2); j++)
        {
            all_map[i][j] = ' ';
        }
    }  
    rooms = (room *) malloc(9 * sizeof(room));
    enemies = (enemy *) malloc(6 * sizeof(enemy));
    count_enemy = 0;





    load_map();

    save_score(1);

    copy_map();

    clear_and_border2();

    elemnts_under_board();

    player_move(0, 0, 0);

    new_game(0);

}