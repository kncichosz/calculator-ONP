#pragma once

struct elementStruktury {

    char type[4];
    int liczba;
    elementStruktury* nastepny;// adres nastepnego elementu struktury

    elementStruktury(const char* type = "", int liczba = 0)
        :nastepny(nullptr), liczba(liczba) {

        int i = 0;

        //zapisanie chara
        while (type[i] != '\0') {
            this->type[i] = type[i];
            i++;
        }
        this->type[i] = '\0';
    }
};

class Stos
{
    elementStruktury* gora;

public:
    Stos();
    void push(char* znak, int liczba);
    void pop(char* znak, int& liczba);
    void wypiszLiczby();
    int czy_nie_pusta();
    ~Stos();
};

class Kolejka {

    elementStruktury* dol;
    elementStruktury* gora;

public:
    Kolejka();
    void put(char* znak, int liczba);
    int get(elementStruktury& token);
    void wyczysc();
    int czy_nie_pusta();
    ~Kolejka();
};