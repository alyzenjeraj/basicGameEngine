// GameEngine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <Windows.h>

int engWidth = 200;
int engHeight = 100;

float playerPosX = 0;
float playerPosY = 0;
float playerPOV = 0;

int mapWidth = 16;
int mapHeight = 16;

float FOV = 3.1415 / 4.0;

float depth = 16.0;

int main()
{
    wchar_t* engine_screen = new wchar_t[engWidth * engHeight];
    HANDLE gameConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(gameConsole);

    DWORD dWordBytesWritten = 0;

    std::wstring map;

    map += L"################";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"#..............#";
    map += L"################";


    while (1) {

        for (int i = 0; i < engWidth; i++) {
            float rayAngle = (playerPOV - FOV / 2.0) + (i / engWidth) * FOV;

            float distToWall = 0;
            bool hitWall = false;

            float oppAngleX = sin(rayAngle);
            float adjAngleY = cos(rayAngle);

            while (!hitWall && distToWall < depth) {

                distToWall += 0.1;

                int oppTestX = (int)(playerPosX + oppAngleX * distToWall);
                int adjTestY =(int)( playerPosY + adjAngleY * distToWall);

                if (oppTestX < 0 || oppTestX >= mapWidth || adjTestY < 0 || adjTestY >= mapHeight) {

                } else {
                    if (map[adjTestY * mapWidth + oppTestX] == '#') {
                        hitWall = false;
                    }
                }

            }
        }

        engine_screen[engWidth * engHeight - 1] = '\0';

        WriteConsoleOutputCharacter(gameConsole, engine_screen, engWidth * engHeight, { 0,0 }, &dWordBytesWritten);

    }

    

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
