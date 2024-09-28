#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <stdio.h>

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

using namespace std;
using namespace chrono;
const unsigned int X = 120;
const unsigned int Y = 29;
const unsigned int snowflakeMaxCount = 150;

int random(int min, int max)
{
    max = max + 1;
    return rand() % (max - min) + min  ;
}

void SetSnowflakesSkins(int list[snowflakeMaxCount][3])
{
    for (int i = 0; i < snowflakeMaxCount; i++)
    {
        list[i][2] = random(1, 3);
    }
}

void printSnowflake(int list[snowflakeMaxCount][3], int num)
{
    if (list[num][2] == 1)
    {
        printf("*");
    }
    if (list[num][2] == 2)
    {
        printf("x");
    }
    if (list[num][2] == 3)
    {
        printf("+");
    }

}

void makeFrame()
{

    for (int iy = 0; iy < Y; iy++)
    {
        for (int ix = 0; ix < X; ix++)
        {
            if ((ix != 0 && ix != X - 1) && (iy == 0 || iy == Y - 1))
            {
                cout << (char)205;
            }
            else if ((iy != 0 && iy != Y - 1) && (ix == 0 || ix == X - 1))
            {
                cout << (char)186;
            }
            else if (ix == 0 && iy == 0)
            {
                cout << (char)201;
            }
            else if (ix == X - 1 && iy == 0)
            {
                cout << (char)187;
            }
            else if (ix == X - 1 && iy == Y - 1)
            {
                cout << (char)188;
            }
            else if (ix == 0 && iy == Y - 1)
            {
                cout << (char)200;
            }
            else
            {
                cout << ' ';
            }
        }
        cout << endl;
    }

}

int trySummonSnowflake(int list[snowflakeMaxCount][3], int count)
{
    if (count < snowflakeMaxCount)
    {
        list[count][0] = random(2, X - 1);
        list[count][1] = 2;
        gotoxy(list[count][0], 2);
        printSnowflake(list, count);
        gotoxy(1, 1);
        return count + 1;
    }
    return count;
}

void updateSnowflakes(int list[snowflakeMaxCount][3], int count)
{
    for (int i = 0; i < count; i++)
    {
        if (random(1, 1) == 1)
        {
            gotoxy(list[i][0], list[i][1]);
            if (((list[i][0] < (((X - 29) / 2)) 
                || (list[i][0]   >= (((X - 29) / 2) + 29))) 
                || ((list[i][1] < ((Y - 8) / 2)) 
                || (list[i][1] >= (((Y - 8) / 2) + 4)))) 
                && (((list[i][0] < ((X - 44) / 2)) 
                || (list[i][0] >= (((X - 44) / 2) + 44))) 
                || ((list[i][1] < ((Y) / 2)) 
                || (list[i][1] >= (((Y) / 2) + 4)))))
                printf(" ");
            list[i][1] = list[i][1] + random(0, 1);
            list[i][0] = list[i][0] + random(-1, 1);
            if (list[i][0] == 1)
                list[i][0] = X - 1;
            if (list[i][0] == X)
                list[i][0] = 2;
            if (list[i][1] == Y)
            {
                list[i][1] = 2;
                list[i][0] = random(2, X - 1);
            }
                
        }
        gotoxy(list[i][0], list[i][1]);
        if (((list[i][0] < (((X - 29) / 2)) 
            || (list[i][0] >= (((X - 29) / 2) + 29))) 
            || ((list[i][1] < ((Y - 8) / 2)) 
            || (list[i][1] >= (((Y - 8) / 2) + 4)))) 
            && (((list[i][0] < ((X - 44) / 2)) || (list[i][0] >= (((X - 44) / 2) + 44))) 
            || ((list[i][1] < ((Y) / 2)) 
            || (list[i][1] >= (((Y) / 2) + 4)))))
            printSnowflake(list, i);
    }
    gotoxy(1, Y + 1);
}

void makeSign()
{
    gotoxy(((X - 29) / 2), ((Y - 8) / 2));
    printf(" _  _    _    ___  ___  _  _");
    gotoxy(((X - 29) / 2), ((Y - 8) / 2) + 1);
    printf("| || |  /_\\  | _ \\| _ \\( \\/ ) ");
    gotoxy(((X - 29) / 2), ((Y - 8) / 2) + 2);
    printf("| __ | /(_)\\ | __/| __/ \\  /");
    gotoxy(((X - 29) / 2), ((Y - 8) / 2) + 3);
    printf("|_||_|/_/ \\_\\|_)  |_)   (__)");
    gotoxy(((X - 44) / 2), ((Y - 8) / 2) + 4);
    printf(" _  _  ___  _    _    _  _  ___    _    ___ ");
    gotoxy(((X - 44) / 2), ((Y - 8) / 2) + 5);
    printf("| \\| || __|/ \\/\\/ \\  ( \\/ )| __|  /_\\  | _ \\");
    gotoxy(((X - 44) / 2), ((Y - 8) / 2) + 6);
    printf("|    || _| \\      /   \\  / | _|  /(_)\\ |   /");
    gotoxy(((X - 44) / 2), ((Y - 8) / 2) + 7);
    printf("|_|\\_||___| \\_/\\_/    (__) |___|/_/ \\_\\|_\\_\\");
    gotoxy(1, Y + 1);
}

int main()
{
    
    srand(time(NULL));
    int snowflakeList[snowflakeMaxCount][3] = { 0 };
    int snowflakeCount = 0;

    makeFrame();
    SetSnowflakesSkins(snowflakeList);
    makeSign();

    int intervMillSec = 150;
    int timeDiff = 0, newTime, oldTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() / intervMillSec;
    while (true)
    {
        newTime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() / intervMillSec;
        if (oldTime != newTime)
        {
            timeDiff = newTime - oldTime;
            oldTime = newTime;
            for (; timeDiff > 0; timeDiff--)
            {
                snowflakeCount = trySummonSnowflake(snowflakeList, snowflakeCount);
                updateSnowflakes(snowflakeList, snowflakeCount);

            }
        }
    }
}
