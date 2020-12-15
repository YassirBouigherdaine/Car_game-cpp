#pragma once
#include<iostream>
#include<Windows.h>
#include<time.h>
#include<conio.h>






void gotoxy(int, int);

void draw_bord();

void draw_Fenemy();           // drawing first enemy

void draw_Senemy();           // drawing second enemy

void draw_playerCar();

void input();

void reset_enemyPos();

void run_game();