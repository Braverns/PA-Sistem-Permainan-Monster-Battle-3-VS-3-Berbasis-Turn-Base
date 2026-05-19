#include "global.h"

void tampilActiveTeam(User users[], int current_user)
{
    cout << "\n _______________________________________________________________________________________________________\n";
    cout << "|                                                                                                       |\n";
    cout << "|                                           ACTIVE TEAM                                                 |\n";
    cout << "|_______________________________________________________________________________________________________|\n";

    cout << left
         << setw(9)  << "|Slot"
         << setw(25) << "|Nama"
         << setw(10) << "|HP"
         << setw(10) << "|ATK"
         << setw(10) << "|DEF"
         << setw(10) << "|SPD"
         << setw(18) << "|Type"
         << setw(12) << "|Rarity"
         << "|"
         << endl;

    cout << "|--------|------------------------|---------|---------|---------|---------|-----------------|-----------|\n";

    for(int i = 0; i < 3; i++)
    {
        int idx = users[current_user].active_team[i];

        // SLOT KOSONG
        if(idx == -1)
        {
            cout << "|"
                 << left << setw(8)
                 << i + 1

                 << "|"
                 << setw(24)
                 << "[KOSONG]"

                 << "|"
                 << setw(9)
                 << "-"

                 << "|"
                 << setw(9)
                 << "-"

                 << "|"
                 << setw(9)
                 << "-"

                 << "|"
                 << setw(9)
                 << "-"

                 << "|"
                 << setw(17)
                 << "-"

                 << "|"
                 << setw(11)
                 << "-"

                 << "|\n";
        }

        // ADA MONSTER
        else
        {
            UserMonster m =
            users[current_user]
            .deck
            .monsters[idx];

            cout << "|"
                 << left << setw(8)
                 << i + 1;

            cout << "|"
                 << setw(24);
            setColor(15);
            cout << m.nama;
            resetColor();

            cout << "|"
                 << setw(9);
            setColor(10);
            cout << m.hp;
            resetColor();

            cout << "|"
                 << setw(9);
            setColor(12);
            cout << m.attack;
            resetColor();

            cout << "|"
                 << setw(9);
            setColor(14);
            cout << m.defense;
            resetColor();

            cout << "|"
                 << setw(9);
            setColor(9);
            cout << m.speed;
            resetColor();

            cout << "|"
                 << setw(17);
            setColor(getTypeColor(m.type));
            cout << m.type;
            resetColor();

            cout << "|"
                 << setw(11);
            setColor(getRarityColor(m.rarity));
            cout << m.rarity;
            resetColor();

            cout << "|\n";
        }
    }

    cout << "|________|________________________|_________|_________|_________|_________|_________________|___________|\n";
}

void pilihActiveTeam(User users[], int current_user, int jumlah_user)
{
    if(users[current_user].deck.jumlah < 3)
    {
        tampilPesan("Minimal membutuhkan 3 monster!");
        return;
    }

    int pilihan[3] = {-1, -1, -1};

    for(int i = 0; i < 3; i++)
    {
        pilihan[i] = activeDeckInput(
            users,
            current_user,
            i + 1,
            pilihan
        );

        if(pilihan[i] == -1)
        {
            tampilPesan("Pemilihan team dibatalkan!");
            return;
        }

        bool sama = false;

        for(int j = 0; j < i; j++)
        {
            if(pilihan[i] == pilihan[j])
            {
                sama = true;
            }
        }

        if(sama)
        {
            tampilPesan("Monster tidak boleh sama!");
            i--;
            continue;
        }
    }

    for(int i = 0; i < 3; i++)
    {
        users[current_user].active_team[i] = pilihan[i];
    }

    saveUserCSV(users, jumlah_user);
    saveDeckCSV(users, jumlah_user);

    CLEAR_SCREEN;

    tampilActiveTeam(users, current_user);
    tunggu();
}

int activeDeckInput(User users[], int current_user, int slot_ke, int pilihan[])
{
    
    if(users[current_user].deck.jumlah == 0)
    {
        tampilPesan("Deck kosong!");
        return -1;
    }
    
    int pilih = 0;

    while(true)
    {
        clearArea();

        cout << "\n _____________________________________________________________________________________________________\n";
        cout << "|                                                                                                     |\n";
        cout << "|                                         PILIH ACTIVE TEAM SLOT ";
        cout << slot_ke;

        int sisa = 19;

        if(slot_ke >= 10)
            sisa--;

        for(int i = 0; i < sisa; i++)
        {
            cout << " ";
        }

        cout << "                 |\n";
        cout << "|_____________________________________________________________________________________________________|\n";

        cout << left
             << setw(7)  << "|No"
             << setw(25) << "|Nama"
             << setw(10) << "|HP"
             << setw(10) << "|ATK"
             << setw(10) << "|DEF"
             << setw(10) << "|SPD"
             << setw(18) << "|Type"
             << setw(12) << "|Rarity"
             << "|"
             << endl;

        cout << "|------|------------------------|---------|---------|---------|---------|-----------------|-----------|\n";

        rekursifActiveTeamInput(users[current_user].deck.monsters, 0, users[current_user].deck.jumlah, pilih);

        cout << "|______|________________________|_________|_________|_________|_________|_________________|___________|\n";
        
        cout << "\nACTIVE TEAM SAAT INI:\n";
        for(int i = 0; i < 3; i++)
        {
            cout << i + 1 << ". ";

            if(pilihan[i] == -1)
            {
                cout << "[KOSONG]";
            }
            else
            {
                cout << users[current_user]
                .deck
                .monsters[pilihan[i]]
                .nama;
            }

            if(i + 1 == slot_ke)
            {
                cout << "  <== SEDANG DIPILIH";
            }

            cout << endl;
        }

        cout << "\n _________________________________________________\n";
        cout << "|                 CONTROL MENU                   |\n";
        cout << "|________________________________________________|\n";
        cout << "| [UP/DOWN] | Pindah Cursor                      |\n";
        cout << "| [ENTER]   | Pilih Monster                      |\n";
        cout << "| [ESC]     | Kembali / Batal                    |\n";
        cout << "|___________|____________________________________|\n";
        
        char tombol = _getch();

        // ARROW
        if(tombol == -32)
        {
            tombol = _getch();

            // ATAS
            if(tombol == 72)
            {
                pilih--;

                if(pilih < 0)
                {
                    pilih = users[current_user].deck.jumlah - 1;
                }
            }

            // BAWAH
            else if(tombol == 80)
            {
                pilih++;

                if(pilih >= users[current_user].deck.jumlah)
                {
                    pilih = 0;
                }
            }
        }

        // ENTER
        else if(tombol == 13)
        {
            return pilih;
        }

        // ESC
        else if(tombol == 27)
        {
            return -1;
        }
    }
}



void rekursifActiveTeamInput(UserMonster monsters[], int index, int jumlah, int pilih)
{
    if(index >= jumlah)
        return;

    // CURSOR
    if(index == pilih)
    {
        setColor(15);
        cout << "|>>";
    }
    else
    {
        cout << "|  ";
        resetColor();
    }

    cout << left
        << setw(4)  << index + 1;
    cout << "|"
         << setw(24);
    setColor(15);
    cout << monsters[index].nama;
    resetColor();
    cout << "|"
         << setw(9);
    setColor(10);
    cout << monsters[index].hp;
    resetColor();
    cout << "|"
         << setw(9);
    setColor(12);
    cout << monsters[index].attack;
    resetColor();
    cout << "|"
         << setw(9);
    setColor(14);
    cout << monsters[index].defense;
    resetColor();
    cout << "|"
         << setw(9);
    setColor(9);
    cout << monsters[index].speed;
    resetColor();
    cout << "|"
        << setw(17);
    setColor(getTypeColor(monsters[index].type));
    cout << monsters[index].type;
    resetColor();
    cout << "|"
        << setw(11);
    setColor(getRarityColor(monsters[index].rarity));
    cout << monsters[index].rarity;
    resetColor();
    cout << "|\n";

    rekursifActiveTeamInput(monsters, index + 1, jumlah, pilih);
    resetColor();
}

void menuActiveTeam(User users[], int current_user, int jumlah_user)
{
    int cursor = 0;

    string menu[3] =
    {
        "Lihat Active Team",
        "Pilih Active Team",
        "Kembali"
    };

    while(true)
    {
        CLEAR_SCREEN;

        cout << "\n __________________________________\n";
        cout << "|          ACTIVE TEAM            |\n";
        cout << "|_________________________________|\n";

        for(int i = 0; i < 3; i++)
        {
            cout << "| ";

            if(cursor == i)
            {
                setColor(15);
                cout << ">> ";
            }
            else
            {
                resetColor();
                cout << "   ";
            }

            cout << left  << setw(28)
                 << menu[i]
                 << " |\n";

            resetColor();
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
                    cursor = 2;
            }

            // DOWN
            else if(tombol == 80)
            {
                playSFX(L"music/cursor3.wav");

                cursor++;

                if(cursor > 2)
                    cursor = 0;
            }
        }

        // ENTER
        else if(tombol == 13)
        {
            switch(cursor)
            {
                // LIHAT ACTIVE TEAM
                case 0:
                {
                    CLEAR_SCREEN;

                    tampilActiveTeam(users, current_user);
                    tunggu();
                    break;
                }

                // PILIH ACTIVE TEAM
                case 1:
                {
                    pilihActiveTeam(users, current_user, jumlah_user);
                    break;
                }

                // KEMBALI
                case 2:
                {
                    return;
                }
            }
        }

        // ESC
        else if(tombol == 27)
        {
            return;
        }
    }
}