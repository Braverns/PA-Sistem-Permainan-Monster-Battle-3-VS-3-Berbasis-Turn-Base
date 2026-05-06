#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

#ifdef _WIN32
#define CLEAR_SCREEN system("cls")
#else
#define CLEAR_SCREEN system("clear")
#endif


struct Monster
{
    struct Status
    {
        int id;
        string nama;
        int hp;
        int attack;
    } status;

    struct Type
    {
        string tipe;
    } type;
};

struct UserMonster
{
    int monster_id;

    string nama;

    int hp;
    int attack;

    string type;   
};


struct User
{
    int id;

    string username;
    string password;
    string role;

    int gold;

    User* next;

    struct Deck
    {
        UserMonster monsters[100];
        int jumlah;
    } deck;
};

void createMonster(Monster monsters[], int &jumlah_monster, int &next_monster_id);
void tampilMonsterList(Monster monsters[], int jumlah_monster);
void tampilMonsterList(Monster monsters[], int jumlah_monster, string judul);
void updateMonster(Monster monsters[], int jumlah_monster);
void deleteMonster(Monster monsters[], int *jumlah_monster);
void logoutAdmin(int &state);
void logout(int &state);

void gachaMonster(User users[], Monster monsters[], int jumlah_monster, int current_user);
void tampilUserDeck(User users[], int current_user);
void tampilUserDeckRekursif(UserMonster monsters[], int index, int jumlah);
void sacrificeMonster(User users[], int current_user);
void deleteMonsterUser(User users[], int current_user);
void logoutUser(int &state);
void menuTidakValid();

void menuHome(int &state, bool &program_jalan);
void daftarUser(User users[], int &jumlah_user, int &state);
bool loginUser(User users[], int jumlah_user, int &current_user, int &state, bool &program_jalan);
void menuAdmin(User users[], Monster monsters[],int &jumlah_monster, int &next_monster_id, int &state);
void menuUser(User users[], Monster monsters[],int &jumlah_monster,int current_user, int &state);

void sortDeckNamaAscending(UserMonster monsters[], int jumlah);
void sortDeckHPDescending(UserMonster monsters[], int jumlah);
void sortDeckIDAscending(UserMonster monsters[], int jumlah);

int binarySearchID(UserMonster monsters[], int jumlah, int id);
int sequentialSearchNama(UserMonster monsters[], int jumlah, string nama);

void menuSort(User users[], int current_user);
void menuSearch(User users[], int current_user);

#endif