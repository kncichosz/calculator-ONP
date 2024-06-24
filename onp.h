#pragma once
#include <iostream>
#include <string.h>
#include "StrukturyDanych.h"

using namespace std;

int czy_cyfra(const char znak) {

    return (znak >= '0' && znak <= '9');

}

int nadaj_priorytet(const char znak) {

    if (znak == '+' || znak == '-') {
        return 2;
    }
    else if (znak == '*' || znak == '/') {
        return 3;
    }
    else if (znak == 'I') {
        return 4;
    }
    else if (znak == 'N') {
        return 5;
    }
    else if (znak == 'M') {

        return 6;
    }
    else if (znak == '(') {
        return 7;
    }
    else if (znak == ',') {
        return 1;
    }

    return 0;

}

void putONP(Kolejka& onp, char* znak, int& przecinki) {

    if (znak[0] == ',') {
        przecinki++;
    }
    else if (znak[0] == 'M') {
        onp.put(znak, przecinki);
        printf("%s%d  ", znak, przecinki);
        przecinki = 1;
    }
    else if (znak[0] == 'I') {
        onp.put(znak, 0);
        printf("%s  ", znak);
        przecinki = 1;
    }
    else {
        onp.put(znak, 0);
        printf("%s  ", znak);
    }

}

void ONPCalc(Kolejka onp);

void ONPConv() {

    char znak[4], top[4], item[4];
    int priorytet, liczba, przecinki = 1; 

    Kolejka onp;
    Stos stack;

    while (true) {

        cin >> znak;
        liczba = 0;

        if (znak[0] == '.') {
            break;
        }

        if (czy_cyfra(znak[0])) {
            liczba = atoi(znak) + 0;
            znak[0] = '\0';
            onp.put(znak, liczba);
            printf("%d  ", liczba);
        }
        else if ((znak[0] == 'I')) {
            stack.push(znak, liczba);
        }
        else if (znak[0] == 'N') {
            stack.push(znak, liczba);
        }
        else if ((znak[0] == 'M')) {
            stack.push(znak, liczba);
        }
        else if (znak[0] == '(') {
            stack.push(znak, liczba);
        }
        else if (znak[0] == ')') {

            while (stack.czy_nie_pusta()) {

                stack.pop(znak, liczba);
                if (znak[0] == '(') {

                    break;
                }
                else {

                    putONP(onp, znak, przecinki);

                }
            }
        }
        else {
            priorytet = nadaj_priorytet(znak[0]);
            while (stack.czy_nie_pusta()) {

                stack.pop(top, liczba);

                if (top[0] == '(' || top[0] == ',' || nadaj_priorytet(top[0]) < priorytet) {
                    stack.push(top, liczba);
                    break;
                }

                putONP(onp, top, przecinki);

            }

            stack.push(znak, liczba);

        }

    }

    while (stack.czy_nie_pusta()) {

        stack.pop(item, liczba);

        putONP(onp, item, przecinki);

    }

    printf("\n");

    ONPCalc(onp);

}

elementStruktury obliczenia(char* type, int* liczby, int argumenty) {

    char tab[4];
    int liczba;
    tab[0] = '\0';

    if (type[0] == '+') {
        return elementStruktury(tab, liczby[1] + liczby[0]);
    }
    else if (type[0] == '-') {
        return elementStruktury(tab, liczby[1] - liczby[0]);
    }
    else if (type[0] == '*') {
        return elementStruktury(tab, liczby[1] * liczby[0]);
    }
    else if (type[0] == '/') {
        if (liczby[0] == 0) {
            tab[0] = 'E';
            tab[1] = '\0';
            return elementStruktury(tab, liczby[0]);
        }
        else {
            return elementStruktury(tab, liczby[1] / liczby[0]);
        }
    }
    else if (type[0] == 'N') {
        return elementStruktury(tab, -liczby[0]);
    }
    else if (type[0] == 'I') {
        if (liczby[2] > 0) {
            return elementStruktury(tab, liczby[1]);
        }
        else {
            return elementStruktury(tab, liczby[0]);
        }
    }
    else if (!strcmp(type, "MAX")) {
        liczba = liczby[0];
        for (int i = 1; i < argumenty; i++) {
            if (liczba < liczby[i]) {
                liczba = liczby[i];
            }
        }
        return elementStruktury(tab, liczba);
    }
    else if (!strcmp(type, "MIN")) {
        liczba = liczby[0];
        for (int i = 1; i < argumenty; i++) {
            if (liczba > liczby[i]) {
                liczba = liczby[i];
            }
        }
        return elementStruktury(tab, liczba);
    }
    else {
        return elementStruktury(tab, 0);
    }
}

int liczbaArgumentow(char type, int liczba) {
    switch (type)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        return 2;
        break;
    case 'N':
        return 1;
        break;
    case 'I':
        return 3;
        break;
    case 'M':
        return liczba;
        break;
    default:
        return 0;
        break;
    }
}

void ONPCalc(Kolejka onp) {

    Stos stack;
    int argumenty = 0, liczbyTab[50] = { 0 };
    elementStruktury token;
    elementStruktury op1;
    elementStruktury wynik;

    while (true) {

        if (onp.get(token)) {
            break;
        }

        if (token.type[0] == '\0') {
            stack.push(token.type, token.liczba);
        }
        else {
            if (token.type[0] == 'M') {
                printf("%s%d ", token.type, token.liczba);
            }
            else {
                printf("%s ", token.type);
            }
            stack.wypiszLiczby();
            argumenty = liczbaArgumentow(token.type[0], token.liczba);
            for (int i = 0; i < argumenty; i++) {

                stack.pop(op1.type, op1.liczba);
                liczbyTab[i] = op1.liczba;

            }

            wynik = obliczenia(token.type, liczbyTab, argumenty);

            if (wynik.type[0] == 'E') {

                onp.wyczysc();
            }

            stack.push(wynik.type, wynik.liczba);

        }

    }

    stack.pop(wynik.type, wynik.liczba);

    if (wynik.type[0] == 'E') {
        printf("ERROR\n");
    }
    else {
        printf("%d\n", wynik.liczba);
    }

}