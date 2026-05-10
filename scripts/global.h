#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>
using namespace std;

#ifdef _WIN32
#define CLEAR_SCREEN system("cls")
#else
#define CLEAR_SCREEN system("clear")
#endif

struct Skill
{
    string nama;
    int power;
    string effect;
};


struct Monster
{
    struct Status
    {
        int id;

        string nama;
        int hp;
        int attack;
        int defense;
        int speed;
    } status;

    struct Type
    {
        string tipe;
    } type;

    Skill skills[3];
};


struct UserMonster
{
    int monster_id; 

    string nama;
    int hp;
    int attack;
    int defense;
    int speed;
    string type;   
};


struct BattleMonster
{
    UserMonster data;
    int current_hp;
    bool hidup;
};

struct TurnUnit
{
    bool player_side;
    int index;
    int speed;
};

struct User
{
    int id;

    string username;
    string password;
    string role;
    int gold;

    User* next;

    int active_team[3];
    struct Deck
    {
        UserMonster monsters[30];
        int jumlah;
    } deck;
};


// ADMIN
void menuAdmin(User users[], Monster monsters[],int &jumlah_monster, int &next_monster_id, int &state);
void createMonster(Monster monsters[], int &jumlah_monster, int &next_monster_id);
void tampilMonsterList(Monster monsters[], int jumlah_monster);
void tampilMonsterList(Monster monsters[], int jumlah_monster, string judul);
void updateMonster(Monster monsters[], int jumlah_monster);
void deleteMonster(Monster monsters[], int *jumlah_monster);


//LOGIN
void menuHome(int &state, bool &program_jalan);
void daftarUser(User users[], int &jumlah_user, int &state);
bool loginUser(User users[], int jumlah_user, int &current_user, int &state, bool &program_jalan);


// UI
void menuTidakValid();
void logout(int &state);
void tampilPesan(string pesan);
void tungguEnter();
void tunggu();

// USER
void menuUser(User users[], Monster monsters[], int &jumlah_monster, int jumlah_user, int current_user,int &state);
void gachaMonster(User users[], Monster monsters[], int jumlah_monster, int current_user, int jumlah_user);
void buatKartuMonster(UserMonster monster, string kartu[]);
void tampilMultiKartu(UserMonster monsters[], int jumlah);
void tampilUserDeck(User users[], int current_user);
void tampilUserDeckRekursif(UserMonster monsters[], int index, int jumlah);
void sacrificeMonster(User users[], int current_user, int jumlah_user);
void deleteMonsterUser(User users[],int current_user,int jumlah_user);
void pilihActiveTeam(User users[], int current_user);
void tampilActiveTeam(User users[], int current_user);


// BATTLE
void battleMenu(User users[],Monster monsters[],int jumlah_monster,int current_user,int jumlah_user);
void tampilBattleTeam(BattleMonster team[],string judul);
bool semuaMonsterMati(BattleMonster team[]);
void urutkanTurn(TurnUnit turns[], int jumlah);
void playerAttack(BattleMonster player[], BattleMonster enemy[], int attacker);
void enemyAttack(BattleMonster enemy[], BattleMonster player[],int attacker);

// SEARCH & SORT
void sortDeckNamaAscending(UserMonster monsters[], int jumlah);
void sortDeckHPDescending(UserMonster monsters[], int jumlah);
void sortDeckIDAscending(UserMonster monsters[], int jumlah);

int binarySearchID(UserMonster monsters[], int jumlah, int id);

void menuSort(User users[], int current_user);
void menuSearch(User users[], int current_user);

void tampilHasilSearchID(UserMonster monsters[], int index);
void tampilHasilSearchNama(UserMonster monsters[], int jumlah, string nama);

// DATABASE
void loadMonsterCSV(Monster monsters[], int &jumlah);
void saveMonsterCSV(Monster monsters[], int jumlah);
void loadUserCSV(User users[], int &jumlah);
void saveUserCSV(User users[], int jumlah);
void loadDeckCSV(User users[], int jumlah_user);
void saveDeckCSV(User users[], int jumlah_user);
#endif