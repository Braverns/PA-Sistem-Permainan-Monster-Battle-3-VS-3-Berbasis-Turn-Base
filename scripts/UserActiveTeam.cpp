#include "global.h"

void tampilActiveTeam(
    User users[],
    int current_user
)
{
    cout << "\n _____________________________________________________________________________________________________________________\n";
    cout << "|                                                                                                                     |\n";
    cout << "|                                                ACTIVE TEAM MONSTER                                                 |\n";
    cout << "|_____________________________________________________________________________________________________________________|\n";

    for(int i = 0; i < 3; i++)
    {
        int idx =
        users[current_user]
        .active_team[i];

        cout << i + 1 << ". ";

        if(idx == -1)
        {
            cout << "[KOSONG]\n";
        }
        else
        {
            UserMonster m =
            users[current_user]
            .deck.monsters[idx];

            cout
            << m.nama

            << " | HP: "
            << m.hp

            << " | Type: "
            << m.type

            << " | Rarity: "
            << m.rarity

            << endl;
        }
    }
}

void pilihActiveTeam(User users[], int current_user, int jumlah_user)
{
    if(users[current_user].deck.jumlah < 3)
    {
        tampilPesan("Minimal membutuhkan 3 monster!");
        return;
    }


    int pilihan[3];

    cout << "\n ________________________________________________\n";
    cout << "|                                                |\n";
    cout << "|           PILIH ACTIVE TEAM (3 MONSTER)        |\n"; 
    cout << "|                                                |\n";
    cout << "|________________________________________________|\n";

    for(int i = 0; i < 3; i++)
    {
        cout << "\nPilih monster untuk slot "
            << i + 1;

        tungguEnter();

        pilihan[i] = tampilUserDeckInput(users, current_user);

        if(pilihan[i] == -1)
        {
            tampilPesan("Pemilihan team dibatalkan!");
            return;
        }

        if(cin.fail())
        {
            tampilPesan("Input tidak valid!");
            return;
        }

        if(pilihan[i] < 0 ||
           pilihan[i] >= users[current_user].deck.jumlah)
        {
            tampilPesan("Index monster tidak valid!");
            return;
        }

        for(int j = 0; j < i; j++)
        {
            if(pilihan[i] == pilihan[j])
            {
                tampilPesan("Monster tidak boleh sama!");
                return;
            }
        }
    }

    for(int i = 0; i < 3; i++)
    {
        users[current_user].active_team[i] = pilihan[i];
    }

    saveUserCSV(users, jumlah_user);

    CLEAR_SCREEN;

    cout << "Active team berhasil disimpan!\n";

    tampilActiveTeam(users, current_user);

    tungguEnter();
}