#include"game_func.h"



const int screen_height = 30;
const int screen_width = 40;

COORD cursor_pos;

int enemY_pos = 4;
int playerY_pos = screen_height - 8;
int playerX_pos = (screen_width / 2) - 2;

int score = 0;
bool game_over = false;

int p = ((rand() % 5) + 1);

int i, j;

char playerCar[5][4] = { ' ','*','*',' ',
					 '\xDB','\xB0','\xB0','\xDB',
						' ','\xC9','\xBB',' ',
					 '\xDB','\xB0','\xB0','\xDB',
						 ' ','\xC0','\xD9',' ' };

char enemyCar[4][4] = { '\xDB','*','*','\xDB',
						   ' ','*','*',' ',
						'\xDB','*','*','\xDB',
						' ','\x5C','\x2F',' ' };


void gotoxy(int x, int y)
{
	cursor_pos.X = x;
	cursor_pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor_pos);
}

void draw_bord()
{
	for (i = 0; i < screen_height; i++)
	{
		gotoxy(0, i);
		if (i % 2 == 0)
		{
			std::cout << "\xB1";
		}
		else
		{
			std::cout << ' ';
		}

		gotoxy(screen_width, i);
		if (i % 2 == 0)
		{
			std::cout << "\xB1";
		}
		else
		{
			std::cout << ' ';
		}

		gotoxy(screen_width / 2, i);
		std::cout << '|';

		gotoxy(screen_width + 1, i);
		std::cout << '|';

		gotoxy(screen_width + 30, i);
		std::cout << '|';
	}

	for (j = 0; j < screen_width + 31; j++)
	{
		gotoxy(j, 0);
		std::cout << '*';

		gotoxy(j, screen_height);
		std::cout << '*';
	}

	// draw menu

	gotoxy(screen_width + 10, 5);
	std::cout << "***********";
	gotoxy(screen_width + 10, 6);
	std::cout << " CAR GAME";
	gotoxy(screen_width + 10, 7);
	std::cout << "***********";
	gotoxy(screen_width + 10, 12);
	std::cout << " score : " << score;
	gotoxy(screen_width + 10, 15);
	std::cout << "[E] to move left";
	gotoxy(screen_width + 10, 16);
	std::cout << "[R] to move right";

}


void draw_enemy()
{
	// draw enemy car

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			gotoxy(j + (screen_width / p) - 5, i + enemY_pos);
			std::cout << enemyCar[i][j];

			// collision with player car

			if (playerX_pos + 4 == j + (screen_width / p) - 5 || (playerX_pos == j + (screen_width / p) - 5))
			{
				if ((i + enemY_pos) == playerY_pos)
				{
					game_over = true;
				}
			}
		}
	}

	Sleep(70);

	// erase enemy car

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			gotoxy(j + (screen_width / p) - 5, i + enemY_pos);
			std::cout << " ";
		}
	}

}



void draw_playerCar()
{
	// draw player car

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 4; j++)
		{
			gotoxy(j + playerX_pos, i + playerY_pos);
			std::cout << playerCar[i][j];
		}
	}

	Sleep(70);

	// erase player car

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 4; j++)
		{
			gotoxy(j + playerX_pos, i + playerY_pos);
			std::cout << " ";
		}
	}

	// collision with the Pavement

	if (playerX_pos < 2 || playerX_pos > screen_width - 5)
	{
		game_over = true;
	}

}


void input()
{
	if (_kbhit())
	{
		char p = _getch();

		if (p == 'e')
		{
			playerX_pos -= 2;
		}

		else if (p == 'r')
		{
			playerX_pos += 2;
		}
	}
}

void reset_enemyPos()
{
	if (i + enemY_pos > screen_height - 4)
	{
		p = ((rand() % 4) + 1);

		enemY_pos = 3;

		// update score
		score++;
	}
}


void gameOver()
{
	system("cls");

	std::cout << "\n\n\t\t*******************************\n";
	std::cout << "\t\t***                         ***\n";
	std::cout << "\t\t*        GAME OVER            *\n";
	std::cout << "\t\t***                         ***\n";
	std::cout << "\t\t*******************************\n\n";
}


void run_game()
{
	srand((unsigned)time(NULL));

	while (!game_over)
	{
		draw_bord();

		draw_playerCar();

		draw_enemy();

		input();

		reset_enemyPos();

		enemY_pos += 2;
	}

	gameOver();
}
