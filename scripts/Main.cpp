#include "global.h"

// g++ *.cpp -o game

int main()
{
    srand(time(0));

    User users[100];
    Monster monsters[100];

    int jumlah_user = 0;
    int jumlah_monster = 0;

    int next_monster_id = 1;


    loadMonsterCSV(monsters, jumlah_monster);


    if(jumlah_monster > 0)
    {
        next_monster_id =
        monsters[jumlah_monster - 1].status.id + 1;
    }

    // LOAD DATABASE
    loadUserCSV(users, jumlah_user);

    loadDeckCSV(users, jumlah_user);

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
                menuAdmin(users, monsters, jumlah_monster, next_monster_id, state);
                break;
            }

            case 4:
            {
                menuUser(users, monsters, jumlah_monster, jumlah_user, current_user, state);
                break;
            }

        }
    }

    saveMonsterCSV(monsters, jumlah_monster);
    saveUserCSV(users, jumlah_user);
    saveDeckCSV(users, jumlah_user);

    tampilPesan("Terima kasih telah bermain Battle Monster!");
    return 0;
}