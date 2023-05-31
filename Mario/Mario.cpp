#include <fstream>
#include <thread>
#include <cwchar>
#include <iostream>
#include <curses.h> 
#include <windows.h>
#include <string> 
#include <time.h>
#include <future>

int selectedlevel;
int life;
int points;
int best[4];

using namespace std;
using namespace std::this_thread;


#define GRASS_PAIR     1
#define EMPTY_PAIR     1
#define SKY_PAIR     2
#define SPIKE_PAIR  3
#define PLATFORM_PAIR    4
#define PLAYER_SKY_PAIR    5
#define CLOUD_PAIR    6
#define BUSH_PAIR    7
#define FLOOR_PAIR 8
#define POINT_PAIR 9
#define WOOD_PAIR 10
#define PLAYER_BUSH_PAIR 11
#define PLAYER_WOOD_PAIR 12
#define PLAYER_CLOUD_PAIR 13
#define MENU_PAIR 14
#define RED_PAIR 15
#define WHITE_PAIR 16
#define BLACK_PAIR 17
#define YELLOW_PAIR 18
#define BROWN_PAIR 19


void hidecursor() { HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);   CONSOLE_CURSOR_INFO info;   info.dwSize = 100;   info.bVisible = FALSE;   SetConsoleCursorInfo(consoleHandle, &info); }
void Menu();
void get_color();
void MoveCharUp(WINDOW* win, int& y, int& x, char tab[][15], int& count);
void MoveCharRight(WINDOW* win, int y, int& x, char tab[][15], int& count);
void MoveCharUpRight(WINDOW* win, int& y, int& x, char tab[][15], int& count);
void MoveCharUpLeft(WINDOW* win, int& y, int& x, char tab[][15], int& count);
void MoveCharLeft(WINDOW* win, int y, int& x, char tab[][15], int& count);
void DrawBlock(WINDOW* win, int x, int y, char block);
void ShowFireworks1(int x, int y)
{
	get_color();
	mvaddstr(y - 1, x, "  - ");
	mvaddstr(y, x, " -+- ");
	mvaddstr(y + 1, x, "  - ");

}
void ShowFireworks2(int x, int y)
{
	get_color();
	mvaddstr(y - 2, x, " --- ");
	mvaddstr(y - 1, x, "-+++-");
	mvaddstr(y, x, "-+#+-");
	mvaddstr(y + 1, x, "-+++-");
	mvaddstr(y + 2, x, " --- ");
}
void ShowFireworks3(int x, int y)
{
	get_color();
	mvaddstr(y - 2, x, " +++ ");
	mvaddstr(y - 1, x, "++#++");
	mvaddstr(y, x, "+# #+");
	mvaddstr(y + 1, x, "++#++");
	mvaddstr(y + 2, x, " +++ ");
}
void ShowFireworks4(int x, int y)
{
	get_color();
	mvaddstr(y - 2, x, "  #  ");
	mvaddstr(y - 1, x, "## ##");
	mvaddstr(y, x, "#   #");
	mvaddstr(y + 1, x, "## ##");
	mvaddstr(y + 2, x, "  #  ");
}
void ShowFireworks5(int x, int y)
{
	get_color();
	mvaddstr(y - 2, x, " # # ");
	mvaddstr(y - 1, x, "#   #");
	mvaddstr(y, x, "     ");
	mvaddstr(y + 1, x, "#   #");
	mvaddstr(y + 2, x, " # # ");
}
void get_color(void)
{
	chtype bold = (rand() % 2) ? A_BOLD : A_NORMAL;
	attrset(COLOR_PAIR(rand() % 8) | bold);
}
short color_table[] =
{
	COLOR_RED, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN,
	COLOR_RED, COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE
};
void PlayMusic()
{
	while (1)
	{
		Beep(330, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(330, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(330, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(330, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(392, 100); this_thread::sleep_for(chrono::milliseconds(700));
		Beep(196, 100); this_thread::sleep_for(chrono::milliseconds(700));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(262, 300); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(196, 300); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(164, 300); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(220, 300); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(246, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(233, 200);
		Beep(220, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(196, 100); this_thread::sleep_for(chrono::milliseconds(150));
		Beep(330, 100); this_thread::sleep_for(chrono::milliseconds(150));
		Beep(392, 100); this_thread::sleep_for(chrono::milliseconds(150));
		Beep(440, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(349, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(392, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(330, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(294, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(247, 100); this_thread::sleep_for(chrono::milliseconds(500));
		Beep(262, 300); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(196, 300); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(164, 300); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(220, 300); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(246, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(233, 200);
		Beep(220, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(196, 100); this_thread::sleep_for(chrono::milliseconds(150));
		Beep(330, 100); this_thread::sleep_for(chrono::milliseconds(150));
		Beep(392, 100); this_thread::sleep_for(chrono::milliseconds(150));
		Beep(440, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(349, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(392, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(330, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(294, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(247, 100); this_thread::sleep_for(chrono::milliseconds(900));
		Beep(392, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(370, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(349, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(311, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(330, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(207, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(220, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(220, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(294, 100); this_thread::sleep_for(chrono::milliseconds(500));
		Beep(392, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(370, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(349, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(311, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(330, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(523, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(523, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(523, 100); this_thread::sleep_for(chrono::milliseconds(1100));
		Beep(392, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(370, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(349, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(311, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(330, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(207, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(220, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(220, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(294, 100); this_thread::sleep_for(chrono::milliseconds(500));
		Beep(311, 300); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(296, 300); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(262, 300); this_thread::sleep_for(chrono::milliseconds(1300));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(294, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(330, 200); this_thread::sleep_for(chrono::milliseconds(50));
		Beep(262, 200); this_thread::sleep_for(chrono::milliseconds(50));
		Beep(220, 200); this_thread::sleep_for(chrono::milliseconds(50));
		Beep(196, 100); this_thread::sleep_for(chrono::milliseconds(700));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(294, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(330, 100); this_thread::sleep_for(chrono::milliseconds(700));
		Beep(440, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(392, 100); this_thread::sleep_for(chrono::milliseconds(500));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(262, 100); this_thread::sleep_for(chrono::milliseconds(100));
		Beep(294, 100); this_thread::sleep_for(chrono::milliseconds(300));
		Beep(330, 200); this_thread::sleep_for(chrono::milliseconds(50));
		Beep(262, 200); this_thread::sleep_for(chrono::milliseconds(50));
		Beep(220, 200); this_thread::sleep_for(chrono::milliseconds(50));
		Beep(196, 100); this_thread::sleep_for(chrono::milliseconds(700));
	}
}
void PlayIntroMusic()
{

	Beep(330, 100);  this_thread::sleep_for(chrono::milliseconds(100));
	Beep(330, 100);  this_thread::sleep_for(chrono::milliseconds(300));
	Beep(330, 100);  this_thread::sleep_for(chrono::milliseconds(300));
	Beep(262, 100);  this_thread::sleep_for(chrono::milliseconds(100));
	Beep(330, 100);  this_thread::sleep_for(chrono::milliseconds(300));
	Beep(392, 100);  this_thread::sleep_for(chrono::milliseconds(700));
	Beep(196, 100);  this_thread::sleep_for(chrono::milliseconds(700));
	Beep(196, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(262, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(330, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(392, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(523, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(660, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(784, 100);  this_thread::sleep_for(chrono::milliseconds(575));
	Beep(660, 100);  this_thread::sleep_for(chrono::milliseconds(575));
	Beep(207, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(262, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(311, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(415, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(523, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(622, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(830, 100);  this_thread::sleep_for(chrono::milliseconds(575));
	Beep(622, 100);  this_thread::sleep_for(chrono::milliseconds(575));
	Beep(233, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(294, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(349, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(466, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(587, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(698, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(932, 100);  this_thread::sleep_for(chrono::milliseconds(575));
	Beep(932, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(932, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(932, 100);  this_thread::sleep_for(chrono::milliseconds(125));
	Beep(1046, 675);
}
void ShowFireworks()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 1; j < 12; j++)
		{
			ShowFireworks1(j * 9, 2);
			ShowFireworks1(j * 9, 22);
		}
		this_thread::sleep_for(chrono::milliseconds(50));
		refresh();
		for (int j = 1; j < 12; j++)
		{
			ShowFireworks2(j * 9, 2);
			ShowFireworks2(j * 9, 22);
		}
		this_thread::sleep_for(chrono::milliseconds(50));
		refresh();
		for (int j = 1; j < 12; j++)
		{
			ShowFireworks3(j * 9, 2);
			ShowFireworks3(j * 9, 22);
		}
		this_thread::sleep_for(chrono::milliseconds(50));
		refresh();
		for (int j = 1; j < 12; j++)
		{
			ShowFireworks4(j * 9, 2);
			ShowFireworks4(j * 9, 22);
		}
		this_thread::sleep_for(chrono::milliseconds(50));
		refresh();
		for (int j = 1; j < 12; j++)
		{
			ShowFireworks5(j * 9, 2);
			ShowFireworks5(j * 9, 22);
		}
		this_thread::sleep_for(chrono::milliseconds(50));
		refresh();

	}
	for (int j = 1; j < 12; j++)
	{
		ShowFireworks3(j * 9, 2);
		ShowFireworks3(j * 9, 22);
	}
	refresh();
}
void GameFinished(WINDOW* win)
{
	char e;
	//thread musicthread(PlayFinishMusic);
	int i;
	if (has_colors())
		start_color();

	for (i = 0; i < 8; i++)
		init_pair(i, color_table[i], COLOR_BLACK);
	//werase(win);

	box(win, 0, 0);
	wattron(win, COLOR_PAIR(PLAYER_CLOUD_PAIR));
	mvwaddstr(win, 4, 35, "YOU WON");
	mvwaddstr(win, 7, 32, "YOUR SCORE: ");
	mvwaddch(win, 7, 43, ((char)points + 48));
	mvwaddstr(win, 13, 23, "Press any key to go back to menu");
	wattroff(win, COLOR_PAIR(PLAYER_CLOUD_PAIR));
	wrefresh(win);

	//musicthread.join();

	if (points > best[selectedlevel])
	{
		thread fireworkthread(ShowFireworks);
		best[selectedlevel] = points;
		mvwaddstr(win, 2, 30, " NEW BEST SCORE!");
		wrefresh(win);
		ofstream wyj("score.txt");
		for (int i = 1; i < 4; i++)
		{
			wyj << best[i] << " ";
		}
		fireworkthread.join();
	}
	
	timeout(30000);
	Sleep(1000);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	
	getch();
	erase();
	endwin();
	
	
	Menu();
}
void GameOver(WINDOW* win)
{
	//werase(win);

	box(win, 0, 0);
	mvwaddstr(win, 2, 35, "You Lost!");
	mvwaddstr(win, 4, 33, "YOUR SCORE: ");
	mvwaddch(win, 4, 45, ((char)points + 48));
	mvwaddstr(win, 13, 23, "Press any key to go back to menu");
	wrefresh(win);
	Sleep(1000);

	timeout(30000);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	getch();
	erase();
	endwin();
	Menu();
	life = 0;

}
bool DetectCollision(WINDOW* win, int y, int x, char tab[][15], int count)
{

	if (tab[count - 80 + x][y] == 'O')
	{
		return true;
	}
	if (tab[count - 80 + x][y] == '@')
	{
		Sleep(400);
		GameFinished(win);
	}

	if (tab[count - 80 + x][y] == '*')
	{
		Beep(1568, 200);
		Sleep(400);
		tab[count - 80 + x][y] = ' ';
		points++;

		wattron(win, COLOR_PAIR(FLOOR_PAIR));
		mvwaddch(win, 13, 46, (char)points + 48);
		wattroff(win, COLOR_PAIR(FLOOR_PAIR));
	}

	if (tab[count - 80 + x][y] == 'X')
	{
		Sleep(400);
		GameOver(win);
	}
	return false;
}
void DrawPlayer(WINDOW* win, int x, int y, char background)
{
	if (background == 'C')
	{
		wattron(win, COLOR_PAIR(PLAYER_CLOUD_PAIR));
		mvwaddch(win, x, y, A_ALTCHARSET | 223);
		wattroff(win, COLOR_PAIR(PLAYER_CLOUD_PAIR));
	}
	else
	{
		if (background == 'W')
		{
			wattron(win, COLOR_PAIR(PLAYER_WOOD_PAIR));
			mvwaddch(win, x, y, A_ALTCHARSET | 223);
			wattroff(win, COLOR_PAIR(PLAYER_WOOD_PAIR));
		}
		else
		{
			if (background == ' ')
			{
				wattron(win, COLOR_PAIR(PLAYER_SKY_PAIR));
				mvwaddch(win, x, y, A_ALTCHARSET | 223);
				wattroff(win, COLOR_PAIR(PLAYER_SKY_PAIR));
			}
			else
			{
				if (background == 'B')
				{
					wattron(win, COLOR_PAIR(PLAYER_BUSH_PAIR));
					mvwaddch(win, x, y, A_ALTCHARSET | 223);
					wattroff(win, COLOR_PAIR(PLAYER_BUSH_PAIR));
				}
				else
				{
					wattron(win, COLOR_PAIR(PLAYER_SKY_PAIR));
					mvwaddch(win, x, y, A_ALTCHARSET | 223);
					wattroff(win, COLOR_PAIR(PLAYER_SKY_PAIR));
				}
			}
		}
	}
}
void DrawBlock(WINDOW* win, int x, int y, char block)
{
	if (block == 'T')
	{
		wattron(win, COLOR_PAIR(GRASS_PAIR));
		mvwaddch(win, x, y, ACS_CKBOARD);
		wattroff(win, COLOR_PAIR(GRASS_PAIR));
	}
	else
	{
		if (block == 'O')
		{
			wattron(win, COLOR_PAIR(PLATFORM_PAIR));
			mvwaddch(win, x, y, ACS_CKBOARD);
			wattroff(win, COLOR_PAIR(PLATFORM_PAIR));
		}
		else
		{
			if (block == 'X')
			{
				wattron(win, COLOR_PAIR(SPIKE_PAIR));
				mvwaddch(win, x, y, ACS_DIAMOND);
				wattroff(win, COLOR_PAIR(SPIKE_PAIR));
			}
			else
			{
				if (block == 'C')
				{
					wattron(win, COLOR_PAIR(CLOUD_PAIR));
					mvwaddch(win, x, y, 'C');
					wattroff(win, COLOR_PAIR(CLOUD_PAIR));
				}
				else
				{
					if (block == 'B')
					{
						wattron(win, COLOR_PAIR(BUSH_PAIR));
						mvwaddch(win, x, y, 'B');
						wattroff(win, COLOR_PAIR(BUSH_PAIR));
					}
					else
					{
						if (block == 'F')
						{
							wattron(win, COLOR_PAIR(FLOOR_PAIR));
							mvwaddch(win, x, y, A_ALTCHARSET | 175);
							wattroff(win, COLOR_PAIR(FLOOR_PAIR));
						}
						else
						{
							if (block == '*')
							{
								wattron(win, COLOR_PAIR(POINT_PAIR));
								mvwaddch(win, x, y, '*');
								wattroff(win, COLOR_PAIR(POINT_PAIR));
							}
							else
							{
								if (block == 'W')
								{
									wattron(win, COLOR_PAIR(POINT_PAIR));
									mvwaddch(win, x, y, ACS_CKBOARD);
									wattroff(win, COLOR_PAIR(POINT_PAIR));
								}
								else
								{
									wattron(win, COLOR_PAIR(SKY_PAIR));
									mvwaddch(win, x, y, block);
									wattroff(win, COLOR_PAIR(SKY_PAIR));
								}
							}
						}
					}
				}
			}
		}
	}
}
void DrawMap(WINDOW* win, char tab[][15], int count)
{
	int i, j;
	if (count == 80)
	{
		for (i = 0; i < 15; i++)
		{
			for (j = 0; j <= 80; j++)
			{
				DrawBlock(win, i, j, tab[j][i]);
			}
		}
	}
	wrefresh(win);
}
void MoveMap(WINDOW* win, char tab[][15], int& count)
{
	count++;
	int i;
	if (count < 495)
	{
		for (i = 0; i <= 15; i++)
		{
			mvwdelch(win, i, 0);
		}
		for (i = 0; i < 15; i++)
		{

			DrawBlock(win, i, 80, tab[count][i]);
		}
	}
	
	wattron(win, COLOR_PAIR(FLOOR_PAIR));
	mvwaddstr(win, 13, 33, "YOUR POINTS: ");
	mvwaddch(win, 13, 46, (char)points + 48);
	wattroff(win, COLOR_PAIR(FLOOR_PAIR));
	DrawBlock(win, 13, 32, 'T');
}
void MoveCharUpLeft(WINDOW* win, int& y, int& x, char tab[][15], int& count)
{
	int i;
	char key;
	for (i = 0; i < 6; i++)
	{
		if (DetectCollision(win, y - 1, x - 1, tab, count) == true)
		{
			break;
		}
		MoveCharLeft(win, y, x, tab, count);
		y = y - 1;
		DrawPlayer(win, y, x, tab[count - 80 + x][y]);
		DrawBlock(win, y + 1, x, tab[count - 80 + x][y + 1]);
		wrefresh(win);
		Sleep(20);
	}
	while (y < 11)
	{
		if (DetectCollision(win, y + 1, x - 1, tab, count) == true)
		{
			break;
		}
		MoveCharLeft(win, y, x, tab, count);
		y = y + 1;
		DrawPlayer(win, y, x, tab[count - 80 + x][y]);
		DrawBlock(win, y - 1, x, tab[count - 80 + x][y - 1]);
		wrefresh(win);
		Sleep(20);
	}
}
void MoveCharUpRight(WINDOW* win, int& y, int& x, char tab[][15], int& count)
{
	int i;
	char key;
	for (i = 0; i < 6; i++)
	{
		if (DetectCollision(win, y - 1, x + 1, tab, count) == true)
		{
			break;
		}
		MoveCharRight(win, y, x, tab, count);
		y = y - 1;
		DrawPlayer(win, y, x, tab[count - 80 + x][y]);
		DrawBlock(win, y + 1, x, tab[count - 80 + x][y + 1]);
		wrefresh(win);
		Sleep(20);
	}
	while (y < 11)
	{
		if (DetectCollision(win, y + 1, x + 1, tab, count) == true)
		{
			break;
		}
		MoveCharRight(win, y, x, tab, count);
		y = y + 1;
		DrawPlayer(win, y, x, tab[count - 80 + x][y]);
		DrawBlock(win, y - 1, x, tab[count - 80 + x][y - 1]);
		wrefresh(win);
		Sleep(20);
	}
}
void MoveCharRight(WINDOW* win, int y, int& x, char tab[][15], int& count)
{
	char key;
	if (DetectCollision(win, y, x + 1, tab, count) == true)
	{
		return;
	}
	if (x < 20 || count>495)
	{
		x = x + 1;
	}
	else
	{
		MoveMap(win, tab, count);
	}
	DrawPlayer(win, y, x, tab[count - 80 + x][y]);
	DrawBlock(win, y, x - 1, tab[count - 80 + x - 1][y]);
	Sleep(10);
}
void MoveCharLeft(WINDOW* win, int y, int& x, char tab[][15], int& count)
{
	char key;
	if (x > 3)
	{
		if (count >= 495)
		{
			count--;
		}
		if (DetectCollision(win, y, x - 1, tab, count) == true)
		{
			return;
		}
		x = x - 1;
		DrawPlayer(win, y, x, tab[count - 80 + x][y]);
		DrawBlock(win, y, x + 1, tab[count - 80 + x + 1][y]);
		Sleep(10);
	}
}
void CharFalling(WINDOW* win, int& y, int& x, char tab[][15], int& count)
{
	char key;
	while (y < 11)
	{
		if (DetectCollision(win, y + 1, x, tab, count) == true)
		{
			break;
		}
		timeout(3);
		move(0, 0); key = getch();
		if (key == 'd')
		{
			if (DetectCollision(win, y + 1, x + 1, tab, count) == true)
			{
				break;
			}
			MoveCharRight(win, y, x, tab, count);
		}
		if (key == 'a')
		{
			if (DetectCollision(win, y + 1, x - 1, tab, count) == true)
			{
				break;
			}
			MoveCharLeft(win, y, x, tab, count);
		}
		y = y + 1;
		DrawPlayer(win, y, x, tab[count - 80 + x][y]);
		DrawBlock(win, y - 1, x, tab[count - 80 + x][y - 1]);
		wrefresh(win);
		Sleep(10);
	}
}
void MoveCharUp(WINDOW* win, int& y, int& x, char tab[][15], int& count)
{
	int i;
	char key;
	for (i = 0; i < 6; i++)
	{
		if (DetectCollision(win, y - 1, x, tab, count) == true)
		{
			break;
		}
		timeout(3);
		move(0, 0); 
		key = getch();
		if (key == 'd')
		{
			if (DetectCollision(win, y - 1, x + 1, tab, count) == true)
			{
				break;
			}
			MoveCharRight(win, y, x, tab, count);
		}
		if (key == 'a')
		{
			if (DetectCollision(win, y - 1, x - 1, tab, count) == true)
			{
				break;
			}
			MoveCharLeft(win, y, x, tab, count);
		}
		y = y - 1;
		DrawPlayer(win, y, x, tab[count - 80 + x][y]);
		DrawBlock(win, y + 1, x, tab[count - 80 + x][y + 1]);
		wrefresh(win);
		Sleep(10);
	}
	while (y < 11)
	{
		if (DetectCollision(win, y + 1, x, tab, count) == true)
		{
			break;
		}
		timeout(3);
		move(0, 0); key = getch();
		if (key == 'd')
		{
			if (DetectCollision(win, y + 1, x + 1, tab, count) == true)
			{
				break;
			}
			MoveCharRight(win, y, x, tab, count);
		}
		if (key == 'a')
		{
			if (DetectCollision(win, y + 1, x - 1, tab, count) == true)
			{
				break;
			}
			MoveCharLeft(win, y, x, tab, count);
		}
		y = y + 1;
		DrawPlayer(win, y, x, tab[count - 80 + x][y]);
		DrawBlock(win, y - 1, x, tab[count - 80 + x][y - 1]);
		wrefresh(win);
		Sleep(10);
	}
}
void Gameplay()
{
	char tab[1000][15];
	string mapname = "MAP";
	mapname = mapname + (char)(selectedlevel + 48);
	mapname = mapname + ".txt";
	ifstream wej(mapname);
	int count = 80;
	char key;
	int i, j = 0;

	for (i = 0; i < 3; i++)
	{
		wej >> tab[j][i];
	}
	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 494; j++)
		{
			wej >> tab[j][i];
			if (tab[j][i] == '_')
			{
				tab[j][i] = ' ';
			}
		}
	}

	initscr(); // rozpocznij tryb curses
	refresh();
	int yChar = 11, xChar = 14;
	int xMax, yMax;
	getmaxyx(stdscr, yMax, xMax);

	WINDOW* win = newwin(15, 81, yMax / 2 - 10, yMax / 2);
	wrefresh(win);
	use_default_colors();
	start_color();
	init_pair(1, ((4, 2), 2), COLOR_GREEN);
	init_pair(2, COLOR_CYAN, COLOR_BLUE);
	init_pair(3, 4, COLOR_BLUE);
	init_pair(4, COLOR_YELLOW, COLOR_MAGENTA);
	init_pair(5, COLOR_MAGENTA, COLOR_BLUE);
	init_pair(6, COLOR_WHITE, COLOR_WHITE);
	init_pair(7, COLOR_GREEN, ((4 | 2), 2));
	init_pair(8, COLOR_YELLOW, COLOR_GREEN);
	init_pair(9, COLOR_YELLOW, COLOR_BLUE);
	init_pair(10, COLOR_MAGENTA, COLOR_BLUE);
	init_pair(11, COLOR_MAGENTA, COLOR_GREEN);
	init_pair(12, COLOR_MAGENTA, COLOR_YELLOW);
	init_pair(13, COLOR_MAGENTA, COLOR_WHITE);
	// thread ostthread(PlayMusic);  //THREAD
	DrawMap(win, tab, count);
	points = 0;
	wattron(win, COLOR_PAIR(FLOOR_PAIR));
	mvwaddstr(win, 13, 33, "YOUR POINTS: ");
	mvwaddch(win, 13, 46, (char)points + 48);
	wattroff(win, COLOR_PAIR(FLOOR_PAIR));

	life = 1;

	DrawPlayer(win, yChar, xChar, ' ');
	while (life == 1)
	{
		if (DetectCollision(win, yChar + 1, xChar, tab, count) == false)
		{
			CharFalling(win, yChar, xChar, tab, count);
			wrefresh(win);
		}
		move(0, 0);
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		key = getch(); // poczekaj na nacisniecie klawisza
		if (key == 'd')
		{
			MoveCharRight(win, yChar, xChar, tab, count);
			wrefresh(win);
		}
		if (key == 'w')
		{
			//yChar = yChar-1;
			MoveCharUp(win, yChar, xChar, tab, count);
			wrefresh(win);
		}
		if (key == 'e')
		{
			MoveCharUpRight(win, yChar, xChar, tab, count);
			wrefresh(win);

		}
		if (key == 'a')
		{
			MoveCharLeft(win, yChar, xChar, tab, count);
			wrefresh(win);
		}
		if (key == 'q')
		{
			MoveCharUpLeft(win, yChar, xChar, tab, count);
			wrefresh(win);
		}
	}
	endwin(); // zakoncz tryb curses
	Menu();
}
void DrawMario(WINDOW *win5, int jx, int jy, char imagejump[][17], int direction)
{
	int i, j;
	char c;
	werase(win5);
	wbkgd(win5, YELLOW_PAIR);
	if(direction==0)
	for (i = 0; i < 14; i++)
	{
		for (j = 0; j < 17; j++)
		{
			c = imagejump[i][j];

			if (c == 'B')
			{
				wattron(win5, COLOR_PAIR(BLACK_PAIR));
				mvwaddch(win5, jy + i, jx + j, ' ');
				wattroff(win5, COLOR_PAIR(BLACK_PAIR));
			}
			if (c == 'G')
			{
				wattron(win5, COLOR_PAIR(SKY_PAIR));
				mvwaddch(win5, jy + i, jx + j, ' ');
				wattroff(win5, COLOR_PAIR(SKY_PAIR));
			}
			if (c == 'R')
			{
				wattron(win5, COLOR_PAIR(RED_PAIR));
				mvwaddch(win5, jy + i, jx + j, ' ');
				wattroff(win5, COLOR_PAIR(RED_PAIR));
			}
			if (c == 'Y')
			{
				wattron(win5, COLOR_PAIR(YELLOW_PAIR));
				mvwaddch(win5, jy + i, jx + j, ' ');
				wattroff(win5, COLOR_PAIR(YELLOW_PAIR));
			}
		}
	}
	else
	{
		jx = jx + 15;
		for (i = 0; i < 14; i++)
		{
			for (j = 0; j < 17; j++)
			{
				c = imagejump[i][j];

				if (c == 'B')
				{
					wattron(win5, COLOR_PAIR(BLACK_PAIR));
					mvwaddch(win5, jy + i, jx - j, ' ');
					wattroff(win5, COLOR_PAIR(BLACK_PAIR));
				}
				if (c == 'G')
				{
					wattron(win5, COLOR_PAIR(SKY_PAIR));
					mvwaddch(win5, jy + i, jx - j, ' ');
					wattroff(win5, COLOR_PAIR(SKY_PAIR));
				}
				if (c == 'R')
				{
					wattron(win5, COLOR_PAIR(RED_PAIR));
					mvwaddch(win5, jy + i, jx - j, ' ');
					wattroff(win5, COLOR_PAIR(RED_PAIR));
				}
				if (c == 'Y')
				{
					wattron(win5, COLOR_PAIR(YELLOW_PAIR));
					mvwaddch(win5, jy + i, jx - j, ' ');
					wattroff(win5, COLOR_PAIR(YELLOW_PAIR));
				}
			}
		}
	}
	wrefresh(win5);

}

void Menu()
{
	char key;
	int selected = 1;
	int x, y;
	int xMax, yMax;
	int i, j;
	char c;
	initscr(); // rozpocznij tryb curses
	refresh();
	getmaxyx(stdscr, yMax, xMax);
	WINDOW* win3 = newwin(20, 81, yMax / 2 - 10, yMax / 2);
	wrefresh(win3);

	
	start_color();
	init_pair(5, COLOR_MAGENTA, COLOR_BLUE);
	init_pair(14, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLUE);
	init_pair(15, COLOR_RED, COLOR_RED);
	init_pair(16, COLOR_BLACK, COLOR_WHITE);
	init_pair(17, COLOR_BLACK, COLOR_BLACK);
	init_pair(18, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(19, COLOR_YELLOW, (COLOR_YELLOW | COLOR_RED));
	
	wattron(win3, COLOR_PAIR(PLAYER_SKY_PAIR));
	box(win3, 2, 4);
	wattroff(win3, COLOR_PAIR(PLAYER_SKY_PAIR));
	
	int selectedlv = selectedlevel;
	wattron(win3, COLOR_PAIR(MENU_PAIR));
	mvwaddstr(win3, 4, 33, "Start the game");
	mvwaddstr(win3, 7, 33, "Choose level");
	mvwaddstr(win3, 10, 33, "Close the game");
	mvwaddch(win3, selected * 3+1, 47, '<');
	wattroff(win3, COLOR_PAIR(MENU_PAIR));

	
	wrefresh(win3);

	ifstream wej2("mariojump.txt");

	int jx=1, jy=1;

	char imagejump[14][17];
	for (i = 0; i < 14; i++)
	{
		for (j = 0; j < 16; j++)
		{
			wej2 >> imagejump[i][j];
		}
	}
	WINDOW* win5 = newwin(16, 18, yMax / 2 - 8, yMax / 2 + 3);
	WINDOW* win6 = newwin(16, 18, yMax / 2 - 8, yMax / 2 + 60);
	//wrefresh(win5);
		DrawMario(win5, 1, 1, imagejump,0);
	DrawMario(win6, 1, 1, imagejump, 1);

	while (1)
	{
		
		move(0, 0);
		key = getch();

		if (key == '\n')
		{
			if (selected == 1)
			{
				endwin();
				Gameplay();
			}
			if (selected == 2)
			{
				werase(win3);
				wattron(win3, COLOR_PAIR(PLAYER_SKY_PAIR));
				box(win3, 2, 4);
				wattroff(win3, COLOR_PAIR(PLAYER_SKY_PAIR));
				wattron(win3, COLOR_PAIR(MENU_PAIR));
				mvwaddstr(win3, 2, 20, "Best Score:");
				mvwaddch(win3, 4, 25, best[1]+48);
				mvwaddch(win3, 7, 25, best[2]+48);
				mvwaddch(win3, 10, 25, best[3]+48);
				mvwaddstr(win3, 4, 34, "Easy Level");
				mvwaddstr(win3, 7, 33, "Medium Level");
				mvwaddstr(win3, 10, 34, "Hard level");
				mvwaddch(win3, selectedlv * 3+1, 47, '<');
				wattroff(win3, COLOR_PAIR(MENU_PAIR));
				wrefresh(win3);
				while (1)
				{
					move(0, 0);
					key = getch();

					if (key == '\n')
					{
						if (selectedlv == 1)
						{
							selectedlevel = 1;
							mvwaddch(win3, selectedlv * 3+1, 47, ' ');
							break;
						}
						if (selectedlv == 2)
						{
							selectedlevel = 2;
							mvwaddch(win3, selectedlv * 3+1, 47, ' ');
							break;
						}
						if (selectedlv == 3)
						{
							selectedlevel = 3;
							mvwaddch(win3, selectedlv * 3+1, 47, ' ');
							break;
						}
					}
					if (key == 'w')
					{
						mvwaddch(win3, selectedlv * 3+1, 47, ' ');
						selectedlv--;
					}
					if (key == 's')
					{
						mvwaddch(win3, selectedlv * 3+1, 47, ' ');
						selectedlv++;
					}
					if (selectedlv == 0)
					{
						selectedlv = 3;
					}
					if (selectedlv > 3)
					{
						selectedlv = 1;
					}
					wattron(win3, COLOR_PAIR(MENU_PAIR));
					mvwaddch(win3, selectedlv * 3+1, 47, '<');
					wattroff(win3, COLOR_PAIR(MENU_PAIR));
					wrefresh(win3);
				}
				DrawMario(win5, 1, 1, imagejump, 0);
				DrawMario(win6, 1, 1, imagejump, 1);
				wattron(win3, COLOR_PAIR(PLAYER_SKY_PAIR));
				box(win3, 2, 4);
				wattroff(win3, COLOR_PAIR(PLAYER_SKY_PAIR));
				wattron(win3, COLOR_PAIR(MENU_PAIR));
				mvwaddstr(win3, 4, 33, "Start the game");
				mvwaddstr(win3, 7, 33, "Choose level");
				mvwaddstr(win3, 10, 33, "Close the game");
				mvwaddch(win3, selected * 3+1, 47, '<');
				wattroff(win3, COLOR_PAIR(MENU_PAIR));
				mvwaddstr(win3, 2, 20, "           ");
				mvwaddch(win3, 4, 25, ' ');
				mvwaddch(win3, 7, 25, ' ');
				mvwaddch(win3, 10, 25, ' ');
				wrefresh(win3);
				DrawMario(win5, 1, 1, imagejump, 0);
				DrawMario(win6, 1, 1, imagejump, 1);
			}
			if (selected == 3)
			{
				//erase();
				endwin();
				cout << "Thank you for playing!";
				Sleep(9000);
				exit;
			}
		}
		if (key == 'w')
		{
			mvwaddch(win3, selected * 3+1, 47, ' ');
			selected--;
		}
		if (key == 's')
		{
			mvwaddch(win3, selected * 3+1, 47, ' ');
			selected++;
		}
		if (selected == 0)
		{
			selected = 3;
		}
		if (selected > 3)
		{
			selected = 1;
		}
		wattron(win3, COLOR_PAIR(MENU_PAIR));
		mvwaddch(win3, selected * 3+1, 47, '<');
		wattroff(win3, COLOR_PAIR(MENU_PAIR));
		wrefresh(win3);
	}

}
void ShowIntro()
{
	int x=2, y=5;
	int xMax, yMax;

	char image[16][13];

	ifstream wej("mario.txt");
	int i, j = 0;

	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 12; j++)
		{
			wej >> image[i][j];
		}
	}

	ifstream wej2("mariojump.txt");

	char imagejump[14][17];
	for (i = 0; i < 14; i++)
	{
		for (j = 0; j < 16; j++)
		{
			wej2 >> imagejump[i][j];
		}
	}

	char c;

	initscr(); // rozpocznij tryb curses
	refresh();
	getmaxyx(stdscr, yMax, xMax);
	WINDOW* win4 = newwin(22, 81, yMax / 2 - 10, yMax / 2);
	
	start_color();

	init_pair(2, COLOR_BLUE, COLOR_BLUE);
	init_pair(15, COLOR_RED, COLOR_RED);
	init_pair(16, COLOR_BLACK, COLOR_WHITE);
	init_pair(17, COLOR_BLACK, COLOR_BLACK);
	init_pair(18, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(19, COLOR_YELLOW, (COLOR_YELLOW|COLOR_RED));
	Sleep(300);
	for (x = 2; x < 70; x++)
	{
		if (x > 6 && x < 10)
		{
			y--;
		}
		if (x > 9 && x < 13)
		{
			y++;
			if(y==5)
			{
				x++;
			}
		}
		if (x > 30 && x < 36)
		{
			y--;
		}
		if (x > 35 && x < 41)
		{
			y++;
			if (y == 5)
			{
				x++;
			}
		}
		if (x > 55 && x < 61)
		{
			y--;
		}
		if (x > 60 && x < 66)
		{
			y++;
			if (y == 5)
			{
				x++;
			}
		}

		werase(win4);
		wbkgdset(win4, YELLOW_PAIR);
		box(win4, 2, 4);
		if (y < 5)
		{
			for (i = 0; i < 14; i++)
			{
				for (j = 0; j < 17; j++)
				{
					c = imagejump[i][j];

					if (c == 'B')
					{
						wattron(win4, COLOR_PAIR(BLACK_PAIR));
						mvwaddch(win4, y + i, x + j, ' ');
						wattroff(win4, COLOR_PAIR(BLACK_PAIR));
					}
					if (c == 'G')
					{
						wattron(win4, COLOR_PAIR(SKY_PAIR));
						mvwaddch(win4, y + i, x + j, ' ');
						wattroff(win4, COLOR_PAIR(SKY_PAIR));
					}
					if (c == 'R')
					{
						wattron(win4, COLOR_PAIR(RED_PAIR));
						mvwaddch(win4, y + i, x + j, ' ');
						wattroff(win4, COLOR_PAIR(RED_PAIR));
					}
					if (c == 'Y')
					{
						wattron(win4, COLOR_PAIR(YELLOW_PAIR));
						mvwaddch(win4, y + i, x + j, ' ');
						wattroff(win4, COLOR_PAIR(YELLOW_PAIR));
					}
				}
		}
		}
		else
		{
			for (i = 0; i < 16; i++)
			{
				for (j = 0; j < 13; j++)
				{
					c = image[i][j];

					if (c == 'B')
					{
						wattron(win4, COLOR_PAIR(BLACK_PAIR));
						mvwaddch(win4, y + i, x + j, ' ');
						wattroff(win4, COLOR_PAIR(BLACK_PAIR));
					}
					if (c == 'G')
					{
						wattron(win4, COLOR_PAIR(SKY_PAIR));
						mvwaddch(win4, y + i, x + j, ' ');
						wattroff(win4, COLOR_PAIR(SKY_PAIR));
					}
					if (c == 'R')
					{
						wattron(win4, COLOR_PAIR(RED_PAIR));
						mvwaddch(win4, y + i, x + j, ' ');
						wattroff(win4, COLOR_PAIR(RED_PAIR));
					}
					if (c == 'Y')
					{
						wattron(win4, COLOR_PAIR(YELLOW_PAIR));
						mvwaddch(win4, y + i, x + j, ' ');
						wattroff(win4, COLOR_PAIR(YELLOW_PAIR));
					}
				}
			}
		}
		wrefresh(win4);
		Sleep(100);
		wclear(win4);
	}
	wclear(win4);
	x = x + 7;
	for (x = x; x > 64; x--)
	{
		werase(win4);
		for (i = 0; i < 16; i++)
		{
			for (j = 0; j < 13; j++)
			{
				c = image[i][j];

				if (c == 'B')
				{
					wattron(win4, COLOR_PAIR(BLACK_PAIR));
					mvwaddch(win4, y + i, x - j, ' ');
					wattroff(win4, COLOR_PAIR(BLACK_PAIR));
				}
				if (c == 'G')
				{
					wattron(win4, COLOR_PAIR(SKY_PAIR));
					mvwaddch(win4, y + i, x - j, ' ');
					wattroff(win4, COLOR_PAIR(SKY_PAIR));
				}
				if (c == 'R')
				{
					wattron(win4, COLOR_PAIR(RED_PAIR));
					mvwaddch(win4, y + i, x - j, ' ');
					wattroff(win4, COLOR_PAIR(RED_PAIR));
				}
				if (c == 'Y')
				{
					wattron(win4, COLOR_PAIR(YELLOW_PAIR));
					mvwaddch(win4, y + i, x - j, ' ');
					wattroff(win4, COLOR_PAIR(YELLOW_PAIR));
				}
			}
		}
		wrefresh(win4);
		Sleep(100);
		
	}
	wrefresh(win4);
	Sleep(400);
	string slowo = "Welcome to Mario!";
	string slowo2 = "Game done by Ryszard Rutkowski";
	attron(COLOR_PAIR(WHITE_PAIR));
	for (i = 0; i < 30; i++)
	{
		Sleep(90);
		if (i < 17)
		{
			mvaddch(10, 30 + i, slowo[i]);
		}
		mvaddch(15, 24 + i, slowo2[i]);
		refresh();
	}
	attroff(COLOR_PAIR(WHITE_PAIR));

	Sleep(900);
	attron( COLOR_PAIR(WHITE_PAIR));
	mvaddstr( 24, 43, "Press any key to continue");
	attroff( COLOR_PAIR(WHITE_PAIR));
	wrefresh(win4);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	timeout(100000);
	getch();
	endwin();
}

int main()
{
	ifstream wej("score.txt");
	
	for (int i = 1; i < 4; i++)
	{
		wej >> best[i];
	}
	selectedlevel = 1;
	hidecursor();
	
	thread musicthread(PlayIntroMusic);
	ShowIntro();
	musicthread.join();
	future<void> backgroundthread = std::async(std::launch::async, PlayMusic);
	
	Menu();
	Gameplay();
	return 0;
}