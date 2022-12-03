// https://stackoverflow.com/a/10473315
#pragma once
#include <stdio.h>
#include <conio.h>

class CharacterHelper {
public:
    static void fetchCharacterCodes() 
    {
        int ch;

        while ((ch = _getch()) != 27) /* 27 = Esc key */
        {
            printf("0x%02x", ch);
            if (ch == 0 || ch == 224)
                printf(", 0x%02x", _getch());
            printf("\n");
        }

        printf("ESC %d\n", ch);
    }
};