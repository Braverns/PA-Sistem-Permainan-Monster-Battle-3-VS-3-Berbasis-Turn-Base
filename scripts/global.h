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
#include <conio.h>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

using namespace std;

#ifdef _WIN32
#define CLEAR_SCREEN system("cls")
#else
#define CLEAR_SCREEN system("clear")
#endif

struct Skill
{
    int id;
    string nama;
    string element;
    string tipe;
    int power;
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

    struct Rarity
    {
        string rarity;
    } rarity;
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
    string rarity;  
    Skill skills[3];
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

struct DeckFilter
{
    bool recent;
    bool nama;
    bool hp;
    bool attack;
    bool defense;
    bool speed;
    bool type;
    bool id;
};

struct Rarity
{
    string rarity;
};

// ADMIN
void menuAdmin(User users[], Monster monsters[], Skill skills[],
    int &jumlah_user, int &jumlah_monster, int &jumlah_skill, int &next_monster_id, int &state);
void tampilDaftarUser(User users[], int jumlah_user);
void deleteUser(User users[], int &jumlah_user);
void menuKelolaUser(User users[], int &jumlah_user);
void menuSearchUser(User users[], int jumlah_user);
void tampilDetailUser(User user);
void tampilHasilSearchUserID(User users[], int jumlah_user, int id);
void tampilHasilSearchUserNama(User users[], int jumlah_user, string nama);


// ADMIN MONSTER
void menuKelolaMonster(Monster monsters[], int &jumlah_monster, int &next_monster_id);
void createMonster(Monster monsters[], int &jumlah_monster, int &next_monster_id);
void tampilMonsterList(Monster monsters[], int jumlah_monster);
void tampilMonsterList(Monster monsters[], int jumlah_monster, string judul);
void updateMonster(Monster monsters[], int jumlah_monster);
void deleteMonster(Monster monsters[], int *jumlah_monster);
void tampilDaftarUser(User users[], int jumlah_user);
void deleteUser(User users[], int &jumlah_user);
void menuKelolaMonster(Monster monsters[], int &jumlah_monster, int &next_monster_id);
void menuKelolaUser(User users[], int &jumlah_user);
void menuSearchUser(User users[], int jumlah_user);
void searchUserByID(User users[], int jumlah_user);
void searchUserByNama(User users[], int jumlah_user);
void tampilDetailUser(User user);
void tampilHasilSearchUserID(User users[], int jumlah_user, int id);
void tampilHasilSearchUserNama(User users[], int jumlah_user, string nama);


// SKILL
void menuSkill(Skill skills[], int &jumlah_skill);
void createSkill(Skill skills[], int &jumlah_skill);
void tampilSkillList(Skill skills[], int jumlah_skill);
void updateSkill(Skill skills[], int jumlah_skill);
void deleteSkill(Skill skills[], int &jumlah_skill);

//LOGIN
void menuHome(int &state, bool &program_jalan);
void daftarUser(User users[], int &jumlah_user, int &state);
bool loginUser(User users[], int jumlah_user, int &current_user, int &state, bool &program_jalan);


// UI
void menuTidakValid();
void logout(int &state);
void tampilPesan(string pesan);
void tampilPesan2(string pesan);
void tungguEnter();
void tungguClear();
void tunggu();
void gotoXY(int x, int y);
void clearArea();
void setColor(int color);
void resetColor();
int getRarityColor(string rarity);
void menuSetting();
string inputClean(string label);
int inputAngka(string label);
void validasiDaftarUser(const string& username, const string& password);
void validasiLogin(const string& username, const string& password);
void validasiCreateMonster(const string& nama_str, const string& hp_str, const string& attack_str, const string& defense_str, const string& speed_str, const string& type_str, const string& rarity_str);
void validasiUserGacha(const string& jumlah_str);

// USER
void menuUser(User users[], Monster monsters[], Skill skills[],
    int jumlah_monster,int jumlah_skill, int jumlah_user, int current_user, int &state);
void sacrificeMonster(User users[], int current_user, int jumlah_user);
void deleteMonsterUser(User users[],int current_user,int jumlah_user);

// USER ACTIVE TEAM
void pilihActiveTeam(User users[], int current_user, int jumlah_user);
void tampilActiveTeam(User users[], int current_user);
int activeDeckInput(User users[], int current_user, int slot_ke, int pilihan[]);
void rekursifActiveTeamInput(UserMonster monsters[], int index, int jumlah, int pilih);


// USER DECK
int tampilUserDeckInput(User users[], int current_user);
void tampilUserDeckRekursifInput(UserMonster monsters[], int index, int jumlah, int pilih);
void tampilUserDeck(User users[], int current_user);
void tampilUserDeckRekursif(UserMonster monsters[], int index, int jumlah);
void menuLihatDeck(User users[], int current_user);
void copyDeck(UserMonster sumber[], UserMonster tujuan[], int jumlah);
void filterType(UserMonster monsters[], int &jumlah, string type);
void sortDeckAttackDescending(UserMonster monsters[], int jumlah);
void sortDeckDefenseDescending(UserMonster monsters[], int jumlah);
void sortDeckSpeedDescending(UserMonster monsters[], int jumlah);
void resetPrimaryFilter(DeckFilter &filter);

// USER GACHA
void gachaMonster(User users[], Monster monsters[], Skill skills[],
    int jumlah_monster, int jumlah_skill, int current_user, int jumlah_user);
void buatKartuMonster(UserMonster monster, string kartu[]);
void tampilMultiKartu(UserMonster monsters[], int jumlah);
string getRandomRarity();
int getMonsterByRarity(Monster monsters[], int jumlah_monster, string rarity);
void randomSkillMonster(UserMonster &monster, Skill skills[], int jumlah_skill);


// BATTLE
void battleMenu(User users[], Monster monsters[], Skill skills[],
    int jumlah_monster, int jumlah_skill, int current_user, int jumlah_user);
bool semuaMonsterMati(BattleMonster team[]);
void urutkanTurn(TurnUnit turns[], int jumlah);
bool playerAttack(BattleMonster player[], BattleMonster enemy[], int attacker);
void tampilBattleUI(BattleMonster player[], BattleMonster enemy[]);
int pilihTarget(BattleMonster player[], BattleMonster enemy[], string attacker_name);
int pilihSkill(BattleMonster player[], BattleMonster enemy[], UserMonster monster);
float getTypeMultiplier(string attack_type, string target_type);
int hitungDamage(UserMonster attacker, UserMonster target, Skill skill);
void enemyAttack(BattleMonster enemy[], BattleMonster player[], int attacker);
void printBattleTextLine(string text);


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
void loadDeckCSV(User users[], Skill skills[], int jumlah_user, int jumlah_skill);
void loadMonsterCSV(Monster monsters[], int &jumlah);
void loadUserCSV(User users[], int &jumlah);
void saveUserCSV(User users[], int jumlah);
void saveDeckCSV(User users[], int jumlah_user);
void saveMonsterCSV(Monster monsters[], int jumlah);
void loadSkillCSV(Skill skills[], int &jumlah);
void saveSkillCSV(Skill skills[], int jumlah);
Skill cariSkillByID(Skill skills[], int jumlah_skill, int id);


// MUSIC
void playBGM(const wchar_t path[]);
void stopBGM();
void playSFX(const wchar_t path[]);
void setVolume(int volume);

#endif