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

        cout << "\n _________________________________\n";
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
                playSFX(L"music/cursor3.wav");

                cursor--;

                if(cursor < 0)
                    cursor = 3;
            }

            // DOWN
            else if(tombol == 80)
            {

                playSFX(L"music/cursor3.wav");

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

    string menu[4] =
    {
    "Read User",
    "Search User",
    "Delete User",
    "Kembali"
    };

    while(true)
    {
        CLEAR_SCREEN;

        cout << "\n _________________________________\n";
        cout << "|           KELOLA USER           |\n";
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

        char tombol = _getch();

        if(tombol == -32)
        {
            tombol = _getch();

            if(tombol == 72)
            {
                cursor--;

                if(cursor < 0)
                    cursor = 3;
            }

            else if(tombol == 80)
            {
                cursor++;

                if(cursor > 3)
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
                    menuSearchUser(users, jumlah_user);
                    break;

                case 2:
                    deleteUser(users, jumlah_user);
                    break;

                case 3:
                    return;
            }
        }
    }
}

void tampilDaftarUser(User users[], int jumlah_user)
{
cout << "\n _________________________________________________________________\n";
cout << "|                           DAFTAR USER                           |\n";
cout << "|_________________________________________________________________|\n";

    cout << left
         << setw(6)  << "| ID"
         << setw(25) << "| Username"
         << setw(15) << "| Gold"
         << setw(20) << "| Jumlah Monster"
         << "|\n";

    cout << "|-----|------------------------|--------------|-------------------|\n";

    for(int i = 0; i < jumlah_user; i++)
    {
        // SKIP ADMIN
        if(users[i].role == "admin")
            continue;

        cout << left
             << setw(6)  << ("| " + to_string(users[i].id))
             << setw(25) << ("| " + users[i].username)
             << setw(15) << ("| " + to_string(users[i].gold))
             << setw(20) << ("| " + to_string(users[i].deck.jumlah))
             << "|\n";
    }

    cout << "|_____|________________________|______________|___________________|\n";
}

void menuSearchUser(User users[], int jumlah_user)
{
    CLEAR_SCREEN;

    int pilih;

    cout << "\n=== MENU SEARCH USER ===\n";
    cout << "1. Cari berdasarkan ID\n";
    cout << "2. Cari berdasarkan Username\n";
    cout << "Pilih: ";
    cin >> pilih;

    if(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        tampilPesan("Menu tidak valid!");
        return;
    }

    // SEARCH BY ID
    if(pilih == 1)
    {
        CLEAR_SCREEN;

        tampilDaftarUser(users, jumlah_user);

        int id;

        cout << "\nMasukkan ID User : ";
        cin >> id;

        if(cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            tampilPesan("Input ID tidak valid!");
            return;
        }

        CLEAR_SCREEN;

        tampilHasilSearchUserID(users, jumlah_user, id);
        tungguEnter();
    }

    // SEARCH BY USERNAME
    else if(pilih == 2)
    {
        CLEAR_SCREEN;

        tampilDaftarUser(users, jumlah_user);

        string nama;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nMasukkan Username : ";
        getline(cin, nama);

        CLEAR_SCREEN;

        tampilHasilSearchUserNama(users, jumlah_user, nama);
        tungguEnter();
    }

    else
    {
        tampilPesan("Menu tidak valid!");
    }
}

void tampilHasilSearchUserID(User users[], int jumlah_user, int id)
{
    bool ditemukan = false;

    for(int i = 0; i < jumlah_user; i++)
    {
        if(users[i].id == id && users[i].role != "admin")
        {
            tampilDetailUser(users[i]);
            ditemukan = true;
            break;
        }
    }

    if(!ditemukan)
    {
        cout << "\n _______________________________________\n";
        cout << "|                                       |\n";
        cout << "|       USER TIDAK DITEMUKAN            |\n";
        cout << "|_______________________________________|\n";
    }
}

void tampilHasilSearchUserNama(User users[], int jumlah_user, string nama)
{
    bool ditemukan = false;

    for(int i = 0; i < jumlah_user; i++)
    {
        if(users[i].username == nama && users[i].role != "admin")
        {
            tampilDetailUser(users[i]);
            ditemukan = true;
            break;
        }
    }

    if(!ditemukan)
    {
        cout << "\n _______________________________________\n";
        cout << "|                                       |\n";
        cout << "|       USER TIDAK DITEMUKAN            |\n";
        cout << "|_______________________________________|\n";
    }
}

void tampilDetailUser(User user)
{
    cout << "\n ____________________________________________________________________________________________\n";
    cout << "|                                                                                            |\n";

    // USERNAME
    string nama = user.username;

    int kiri = (92 - nama.length()) / 2;
    int kanan = 92 - nama.length() - kiri;

    cout << "|" 
         << string(kiri, ' ')
         << nama
         << string(kanan, ' ')
         << "|\n";

    cout << "|____________________________________________________________________________________________|\n";

    // GOLD & MONSTER
    cout << "|                                                                                            |\n";

    cout << "| GOLD   : "
         << left << setw(82)
         << user.gold
         << "|\n";

    cout << "| MONSTER: "
         << left << setw(82)
         << user.deck.jumlah
         << "|\n";

    cout << "|____________________________________________________________________________________________|\n";

    // HEADER DECK
    string deck = "DECK";

    int dk_kiri = (92 - deck.length()) / 2;
    int dk_kanan = 92 - deck.length() - dk_kiri;

    cout << "|"
         << string(dk_kiri, ' ')
         << deck
         << string(dk_kanan, ' ')
         << "|\n";

    cout << "|____________________________________________________________________________________________|\n";

    // ACTIVE TEAM
    UserMonster active[3];
    bool ada[3] = {false, false, false};

    for(int i = 0; i < 3; i++)
    {
        int idx = user.active_team[i];

        if(idx != -1 && idx < user.deck.jumlah)
        {
            active[i] = user.deck.monsters[idx];
            ada[i] = true;
        }
    }

    // HP
    cout << "| ";

    for(int i = 0; i < 3; i++)
    {
        if(ada[i])
            cout << left << setw(29) << ("HP  : " + to_string(active[i].hp));
        else
            cout << left << setw(29) << "HP  : -";

        cout << "| ";
    }

    cout << "\n";

    // ATK
    cout << "| ";

    for(int i = 0; i < 3; i++)
    {
        if(ada[i])
            cout << left << setw(29) << ("ATK : " + to_string(active[i].attack));
        else
            cout << left << setw(29) << "ATK : -";

        cout << "| ";
    }

    cout << "\n";

    // DEF
    cout << "| ";

    for(int i = 0; i < 3; i++)
    {
        if(ada[i])
            cout << left << setw(29) << ("DEF : " + to_string(active[i].defense));
        else
            cout << left << setw(29) << "DEF : -";

        cout << "| ";
    }

    cout << "\n";

    // SPD
    cout << "| ";

    for(int i = 0; i < 3; i++)
    {
        if(ada[i])
            cout << left << setw(29) << ("SPD : " + to_string(active[i].speed));
        else
            cout << left << setw(29) << "SPD : -";

        cout << "| ";
    }

    cout << "\n";

    // TYPE
    cout << "| ";

    for(int i = 0; i < 3; i++)
    {
        if(ada[i])
            cout << left << setw(29) << ("TP  : " + active[i].type);
        else
            cout << left << setw(29) << "TP  : -";

        cout << "| ";
    }

    cout << "\n";

    cout << "|______________________________|______________________________|______________________________|\n";

    // MONSTER
    cout << "|";

    for(int i = 0; i < 3; i++)
    {
        string monster;

        if(ada[i])
            monster = active[i].nama;
        else
            monster = "[ EMPTY ]";

        int kiri_mon = (30 - monster.length()) / 2;
        int kanan_mon = 30 - monster.length() - kiri_mon;

        cout << string(kiri_mon, ' ')
             << monster
             << string(kanan_mon, ' ')
             << "|";
    }

    cout << "\n";

    cout << "|______________________________|______________________________|______________________________|\n";
    
}

void deleteUser(User users[], int &jumlah_user)
{
    CLEAR_SCREEN;

    if(jumlah_user <= 1)
    {
        tampilPesan("Tidak ada user yang bisa dihapus!");
        return;
    }

    int index = tampilUserInput(users, jumlah_user);

    if(index == -1)
    {
        tampilPesan("Delete user dibatalkan!");
        return;
    }

    if(index == -2)
    {
        CLEAR_SCREEN;

        tampilDaftarUser(users, jumlah_user);

        cout << "\n1. Cari berdasarkan ID\n";
        cout << "2. Cari berdasarkan Username\n";

        int pilih = inputAngka("Pilih : ");

        // ID
        if(pilih == 1)
        {
            int id = inputAngka("Masukkan ID : ");

            for(int i = 0; i < jumlah_user; i++)
            {
                if(users[i].id == id && users[i].role != "admin")
                {
                    
                    index = i;
                    break;
                }
            }
        }

        // USERNAME
        else if(pilih == 2)
        {
            string nama = inputClean("Masukkan Username : ");

            for(int i = 0; i < jumlah_user; i++)
            {
                if(users[i].username == nama && users[i].role != "admin")
                {
                    index = i;
                    break;
                }
            }
        }

        if(index == -1)
        {
            tampilPesan("User tidak ditemukan!");
            return;
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

int cursor = 0;

string pilihan[2] =
{
    "YA",
    "TIDAK"
};

while(true)
{
    CLEAR_SCREEN;

    cout << "\n ____________________________________________________________\n";
    cout << "|                                                            |\n";
    cout << "|                  KONFIRMASI DELETE USER                    |\n";
    cout << "|____________________________________________________________|\n";
    cout << "|                                                            |\n";
    cout << "| Username : " << left << setw(48) << users[index].username << "|\n";
    cout << "| Gold     : " << left << setw(48) << users[index].gold << "|\n";
    cout << "| Monster  : " << left << setw(48) << users[index].deck.jumlah << "|\n";
    cout << "|____________________________________________________________|\n";

    cout << "\n __________________________________\n";
    cout << "|                                  |\n";
    cout << "|     YAKIN HAPUS USER INI?        |\n";
    cout << "|__________________________________|\n";

    for(int i = 0; i < 2; i++)
    {
        cout << "| ";

        if(cursor == i)
            cout << ">> ";
        else
            cout << "   ";

        cout << left << setw(30) << pilihan[i] << "|\n";
    }

    cout << "|__________________________________|\n";
    cout << "\nGunakan UP/DOWN dan ENTER\n";

    char tombol = _getch();

    // ARROW
    if(tombol == -32)
    {
        tombol = _getch();

        // UP
        if(tombol == 72)
        {
            playSFX(L"music/cursor3.wav");

            cursor--;

            if(cursor < 0)
                cursor = 1;
        }

        // DOWN
        else if(tombol == 80)
        {
            playSFX(L"music/cursor3.wav");

            cursor++;

            if(cursor > 1)
                cursor = 0;
        }
    }

    // ENTER
    else if(tombol == 13)
    {
        switch(cursor)
        {
            case 0: 
            {
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
                return;
            }

            case 1: // TIDAK
            {
                tampilPesan("Delete user dibatalkan!");
                return;
            }
        }
    }

    // ESC 
    else if(tombol == 27)
    {
        tampilPesan("Delete user dibatalkan!");
        return;
    }
}
}

int tampilUserInput(User users[], int jumlah_user)
{
    int pilih = 0;

    while(users[pilih].role == "admin")
    {
        pilih++;
    }

    while(true)
    {
        clearArea();

        cout << "\n ___________________________________________________________________\n";
        cout << "|                                                                   |\n";
        cout << "|                           DAFTAR USER                             |\n";
        cout << "|___________________________________________________________________|\n";

        cout << left
             << setw(7)  << "|No"
             << setw(25) << "|Username"
             << setw(15) << "|Gold"
             << setw(20) << "|Jumlah Monster"
             << "|\n";

        cout << "|------|------------------------|--------------|-------------------|\n";

        tampilUserRekursifInput(users, 0, jumlah_user, pilih);

        cout << "|______|________________________|______________|___________________|\n";

        cout << "\n ________________________________________________\n";
        cout << "|                 CONTROL MENU                  |\n";
        cout << "|________________________________________________|\n";
        cout << "| [UP/DOWN] | Pindah Cursor                     |\n";
        cout << "| [ENTER]   | Delete User                       |\n";
        cout << "| [SPACE]   | Input ID / Username               |\n";
        cout << "| [ESC]     | Kembali                           |\n";
        cout << "|___________|___________________________________|\n";

        char tombol = _getch();

        // ARROW
        if(tombol == -32)
        {
            tombol = _getch();

            // UP
            if(tombol == 72)
            {
                do
                {
                    pilih--;

                    if(pilih < 0)
                        pilih = jumlah_user - 1;

                } while(users[pilih].role == "admin");
            }

            // DOWN
            else if(tombol == 80)
            {
                do
                {
                    pilih++;

                    if(pilih >= jumlah_user)
                        pilih = 0;

                } while(users[pilih].role == "admin");
            }
        }

        // ENTER
        else if(tombol == 13)
        {
            // skip admin
            if(users[pilih].role == "admin")
            {
                tampilPesan("Admin tidak bisa dihapus!");
                continue;
            }

            return pilih;
        }

        // SPACE
        else if(tombol == 32)
        {
            return -2;
        }

        // ESC
        else if(tombol == 27)
        {
            return -1;
        }
    }
}

void tampilUserRekursifInput(User users[], int index, int jumlah_user, int pilih)
{
    if(index >= jumlah_user)
        return;

    if(users[index].role != "admin")
    {
        if(index == pilih)
            cout << "|>>";
        else
            cout << "|  ";

        cout << left
             << setw(4)  << index + 1
             << "|"
             << setw(24) << users[index].username
             << "|"
             << setw(14) << users[index].gold
             << "|"
             << setw(19) << users[index].deck.jumlah
             << "|\n";
    }

    tampilUserRekursifInput(users, index + 1, jumlah_user, pilih);
}