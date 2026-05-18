#include "global.h"

void menuAdmin(User users[], Monster monsters[], Skill skills[],
    int &jumlah_user, int &jumlah_monster, int &jumlah_skill, int &next_monster_id, int &state)
{
    int cursor = 0;

    string menu[4] =
    {
        "Kelola Monster",
        "Kelola Skill",
        "Kelola User",
        "Logout"
    };

    while(true)
    {
        CLEAR_SCREEN;

        cout << "\n __________________________________\n";
        cout << "|           MENU ADMIN            |\n";
        cout << "|_________________________________|\n";

        for(int i = 0; i < 4; i++)
        {
            cout << "| ";

            if(cursor == i)
                cout << ">> ";
            else
                cout << "   ";

            cout << left << setw(28) << menu[i] << " |\n";
        }

        cout << "|_________________________________|\n";
        cout << "\nGunakan UP/DOWN dan ENTER\n";

        char tombol = _getch();

        // ARROW
        if(tombol == -32)
        {
            tombol = _getch();

            // UP
            if(tombol == 72)
            {
                cursor--;

                if(cursor < 0)
                    cursor = 3;
            }

            // DOWN
            else if(tombol == 80)
            {
                cursor++;

                if(cursor > 3)
                    cursor = 0;
            }
        }

        // ENTER
        else if(tombol == 13)
        {
            switch(cursor)
            {
                case 0:
                    menuKelolaMonster(
                        monsters,
                        jumlah_monster,
                        next_monster_id
                    );
                    break;

                case 1:
                    menuSkill(skills, jumlah_skill);
                    break;

                case 2:
                    menuKelolaUser(
                        users,
                        jumlah_user
                    );
                    break;

                case 3:
                    logout(state);
                    return;
            }
        }
    }
}

void menuKelolaUser(User users[], int &jumlah_user)
{
    int cursor = 0;

    string menu[3] =
    {
        "Read User",
        "Delete User",
        "Kembali"
    };

    while(true)
    {
        CLEAR_SCREEN;

        cout << "\n __________________________________\n";
        cout << "|           KELOLA USER           |\n";
        cout << "|_________________________________|\n";

        for(int i = 0; i < 3; i++)
        {
            cout << "| ";

            if(cursor == i)
                cout << ">> ";
            else
                cout << "   ";

            cout << left << setw(28) << menu[i] << " |\n";
        }

        cout << "|_________________________________|\n";

        char tombol = _getch();

        if(tombol == -32)
        {
            tombol = _getch();

            if(tombol == 72)
            {
                cursor--;

                if(cursor < 0)
                    cursor = 2;
            }

            else if(tombol == 80)
            {
                cursor++;

                if(cursor > 2)
                    cursor = 0;
            }
        }

        else if(tombol == 13)
        {
            switch(cursor)
            {
                case 0:
                    CLEAR_SCREEN;
                    tampilDaftarUser(users, jumlah_user);
                    tungguClear();
                    break;

                case 1:
                    deleteUser(users, jumlah_user);
                    break;

                case 2:
                    return;
            }
        }
    }
}

void tampilDaftarUser(User users[], int jumlah_user)
{
    cout << "\n ____________________________________________________________\n";
    cout << "|                        DAFTAR USER                         |\n";
    cout << "|____________________________________________________________|\n";

    cout << left
         << setw(6)  << "| ID"
         << setw(25) << "| Username"
         << setw(15) << "| Role"
         << setw(15) << "| Gold"
         << "|\n";

    cout << "|-----|------------------------|--------------|--------------|\n";

    for(int i = 0; i < jumlah_user; i++)
    {
        cout << left
             << setw(6)  << ("| " + to_string(users[i].id))
             << setw(25) << ("| " + users[i].username)
             << setw(15) << ("| " + users[i].role)
             << setw(15) << ("| " + to_string(users[i].gold))
             << "|\n";
    }

    cout << "|_____|________________________|______________|______________|\n";
}

void deleteUser(User users[], int &jumlah_user)
{
    CLEAR_SCREEN;
    if(jumlah_user <= 1)
    {
        tampilPesan("Tidak ada user yang bisa dihapus!");
        return;
    }

    tampilDaftarUser(users, jumlah_user);

    int id;
    int index = -1;

    cout << "\nMasukkan ID user yang ingin dihapus : ";
    cin >> id;

    for(int i = 0; i < jumlah_user; i++)
    {
        if(users[i].id == id)
        {
            index = i;
        }
    }

    if(index == -1)
    {
        tampilPesan("User tidak ditemukan!");
        return;
    }

    if(users[index].role == "admin")
    {
        tampilPesan("Admin tidak bisa dihapus!");
        return;
    }

    for(int i = index; i < jumlah_user - 1; i++)
    {
        users[i] = users[i + 1];
    }

    jumlah_user--;

    for(int i = 0; i < jumlah_user - 1; i++)
    {
        users[i].next = &users[i + 1];
    }

    if(jumlah_user > 0)
    {
        users[jumlah_user - 1].next = NULL;
    }

    saveUserCSV(users, jumlah_user);
    saveDeckCSV(users, jumlah_user);

    tampilPesan("User berhasil dihapus!");
}

