#include "global.h"

// run with: 
//          • g++ scripts/*.cpp -o game -lwinmm 
//          • ./game


int main()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut,&cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);

    srand(time(0));

    playBGM(L"music/bgm1.wav");

    User users[100];
    Monster monsters[100];
    Skill skills[100];
    int jumlah_skill = 0;
    
    int jumlah_user = 0;
    int jumlah_monster = 0;

    int next_monster_id = 1;


    loadMonsterCSV(monsters, jumlah_monster);
    loadSkillCSV(skills, jumlah_skill);

    if(jumlah_monster > 0)
    {
        next_monster_id = monsters[jumlah_monster - 1].status.id + 1;
    }

    // LOAD DATABASE
    loadUserCSV(users, jumlah_user);
    loadDeckCSV(users, skills, jumlah_user, jumlah_skill);

    // Kalau belum ada user
    if(jumlah_user == 0)
    {
        users[0].id = 0;
        users[0].username = "admin";
        users[0].password = "123";
        users[0].role = "admin";
        users[0].gold = 0;

        users[0].deck.jumlah = 0;

        for(int i = 0; i < 3; i++)
        {
            users[0].active_team[i] = -1;
        }

        users[0].next = NULL;

        jumlah_user = 1;

        saveUserCSV(users, jumlah_user);
    }

    int state = 0;
    bool program_jalan = true;
    int current_user = -1;

    while(program_jalan)
    {
        switch(state)
        {

            case 0:
            {
                menuHome(state, program_jalan);
                break;
            }

            case 1:
            {
                loginUser(users, jumlah_user, current_user, state, program_jalan);
                break;
            }

            case 2:
            {
                daftarUser(users, jumlah_user, state);
                break;
            }

            case 3:
            {
                menuAdmin(users, monsters, skills, jumlah_user, jumlah_monster, jumlah_skill, next_monster_id, state);
                break;
            }

            case 4:
            {
                menuUser(users, monsters, skills, jumlah_monster, jumlah_skill, jumlah_user, current_user, state);
                break;
            }

        }
    }

    saveMonsterCSV(monsters, jumlah_monster);
    saveUserCSV(users, jumlah_user);
    saveDeckCSV(users, jumlah_user);

    setColor(15);
    tampilPesan("Terima kasih telah bermain Battle Monster!");
    resetColor();
    return 0;
}