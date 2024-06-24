#define _CRT_SECURE_NO_WARNINGS
#include "StrukturyDanych.h"
#include <stdio.h>
#include <string.h>

using namespace std;

Stos::Stos() {

    gora = nullptr;
}

void Stos::push(char* znak, int liczba)
{
    elementStruktury* nowy = new elementStruktury(znak, liczba);

    if (gora == nullptr) {

        gora = nowy;

    }
    else {

        nowy->nastepny = gora;
        gora = nowy;
    }
}

void Stos::pop(char* znak, int& liczba) {

    if (gora != nullptr) {

        strcpy(znak, gora->type);
        liczba = gora->liczba;

        elementStruktury* tmp = gora->nastepny;

        delete gora;
        gora = tmp;

    }
}

void Stos::wypiszLiczby()
{

    if (gora != nullptr) {

        elementStruktury* tmp;
        tmp = gora;
        while (tmp != nullptr) {

            printf("%d ", tmp->liczba);

            tmp = tmp->nastepny;

        }

        printf("\n");

    }

}


int Stos::czy_nie_pusta()
{
    return gora != nullptr;// 1(niepusty) 0(pusty)
}

Stos::~Stos() {}

Kolejka::Kolejka()
{
    dol = nullptr;
    gora = nullptr;
}

void Kolejka::put(char* znak, int liczba) {
    elementStruktury* nowy = new elementStruktury(znak, liczba);

    if (dol == nullptr) {
        dol = nowy;
        gora = nowy;
    }
    else {
        dol->nastepny = nowy;
        dol = nowy;
    }
}

int Kolejka::get(elementStruktury& token) {
    if (gora != nullptr) {
        strcpy(token.type, gora->type);
        token.liczba = gora->liczba;

        elementStruktury* tmp = gora->nastepny;
        delete gora;
        gora = tmp;

        if (gora == nullptr) {
            dol = nullptr;
        }

        return 0;
    }
    else {
        return 1;
    }
}

void Kolejka::wyczysc() {
    while (gora != nullptr) {
        elementStruktury* tmp = gora;
        gora = gora->nastepny;
        delete tmp;
    }
    dol = nullptr;
}

int Kolejka::czy_nie_pusta()
{
    return dol != nullptr;
}


Kolejka::~Kolejka()
{}