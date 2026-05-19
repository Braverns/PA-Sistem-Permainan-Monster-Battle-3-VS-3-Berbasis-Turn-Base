#include "global.h"

int tampilUserDeckInput(User users[], int current_user)
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
        cout << "|                                            USER DECK                                                |\n";
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

        tampilUserDeckRekursifInput(users[current_user].deck.monsters, 0, users[current_user].deck.jumlah, pilih);

        cout << "|______|________________________|_________|_________|_________|_________|_________________|___________|\n";
        cout << "Gold : " << users[current_user].gold << endl;

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
            setColor(15);
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



void tampilUserDeckRekursifInput(UserMonster monsters[], int index, int jumlah, int pilih)
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
        << setw(4)  << index + 1
        << "|"
        << setw(24) << monsters[index].nama
        << "|"
        << setw(9) << monsters[index].hp
        << "|"
        << setw(9) << monsters[index].attack
        << "|"
        << setw(9) << monsters[index].defense
        << "|"
        << setw(9) << monsters[index].speed
        << "|"
        << setw(17) << monsters[index].type
        << "|"
        << setw(11) << monsters[index].rarity
        << "|\n";

    tampilUserDeckRekursifInput(monsters, index + 1, jumlah, pilih);
    resetColor();
}

void tampilUserDeck(User users[], int current_user)
{
    CLEAR_SCREEN;
    cout << "\n ____________________________________________________________________________________________________________\n";
    cout << "|                                                                                                            |\n";
    cout << "|                                               USER DECK                                                    |\n";
    cout << "|____________________________________________________________________________________________________________|\n";

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
                     
    tampilUserDeckRekursif(users[current_user].deck.monsters, 0, users[current_user].deck.jumlah);
                 
    cout << "|______|________________________|_________|_________|_________|_________|_________________|___________|\n";
    cout << "Gold : " << users[current_user].gold << endl;

    tunggu();
}



void tampilUserDeckRekursif(UserMonster monsters[], int index, int jumlah)
{
    if(index >= jumlah)
        return;

    cout << "|"
        << left << setw(6)
        << index + 1

        << "|"
        << setw(24)
        << monsters[index].nama

        << "|"
        << setw(9)
        << monsters[index].hp

        << "|"
        << setw(9)
        << monsters[index].attack

        << "|"
        << setw(9)
        << monsters[index].defense

        << "|"
        << setw(9)
        << monsters[index].speed

        << "|"
        << setw(17)
        << monsters[index].type

        << "|"
        << setw(11)
        << monsters[index].rarity

        << "|\n";

    tampilUserDeckRekursif(monsters, index + 1, jumlah);
}


void copyDeck(UserMonster sumber[], UserMonster tujuan[], int jumlah)
{
    for(int i = 0; i < jumlah; i++)
    {
        tujuan[i] = sumber[i];
    }
}

void filterType(UserMonster monsters[], int &jumlah, string type)
{
    UserMonster temp[30];
    int idx = 0;

    for(int i = 0; i < jumlah; i++)
    {
        if(monsters[i].type == type)
        {
            temp[idx] = monsters[i];
            idx++;
        }
    }

    for(int i = 0; i < idx; i++)
    {
        monsters[i] = temp[i];
    }

    jumlah = idx;
}

void sortDeckAttackDescending(UserMonster monsters[], int jumlah)
{
    for(int i = 0; i < jumlah - 1; i++)
    {
        for(int j = 0; j < jumlah - i - 1; j++)
        {
            if(monsters[j].attack < monsters[j+1].attack)
            {
                UserMonster temp = monsters[j];
                monsters[j] = monsters[j+1];
                monsters[j+1] = temp;
            }
        }
    }
}

void sortDeckDefenseDescending(UserMonster monsters[], int jumlah)
{
    for(int i = 0; i < jumlah - 1; i++)
    {
        for(int j = 0; j < jumlah - i - 1; j++)
        {
            if(monsters[j].defense < monsters[j+1].defense)
            {
                UserMonster temp = monsters[j];
                monsters[j] = monsters[j+1];
                monsters[j+1] = temp;
            }
        }
    }
}

void sortDeckSpeedDescending(UserMonster monsters[], int jumlah)
{
    for(int i = 0; i < jumlah - 1; i++)
    {
        for(int j = 0; j < jumlah - i - 1; j++)
        {
            if(monsters[j].speed < monsters[j+1].speed)
            {
                UserMonster temp = monsters[j];
                monsters[j] = monsters[j+1];
                monsters[j+1] = temp;
            }
        }
    }
}

void resetPrimaryFilter(DeckFilter &filter)
{
    filter.recent  = false;
    filter.nama    = false;
    filter.hp      = false;
    filter.attack  = false;
    filter.defense = false;
    filter.speed   = false;
    filter.id      = false;
}

void menuLihatDeck(User users[], int current_user)
{
    if(users[current_user].deck.jumlah == 0)
    {
        tampilPesan("Deck kosong!");
        return;
    }

    DeckFilter filter;

    filter.recent  = true;
    filter.nama    = false;
    filter.hp      = false;
    filter.attack  = false;
    filter.defense = false;
    filter.speed   = false;
    filter.type    = false;
    filter.id      = false;

    string selected_type = "";

    string type_list[5] =
    {
        "Fire",
        "Water",
        "Earth",
        "Wind",
        "Rock"
    };

    int type_cursor = 0;
    bool pilih_type_mode = false;
    int cursor = 0;

    string menu[8] =
    {
        "Recent",
        "Nama",
        "HP",
        "Attack",
        "Defense",
        "Speed",
        "Type",
        "ID"
    };

    while(true)
    {
        clearArea();

        cout << "\n ______________________________________\n";
        cout << "|         FILTER DECK MONSTER          |\n";
        cout << "|______________________________________|\n";

        for(int i = 0; i < 8; i++)
        {
            bool aktif = false;

            switch(i)
            {
                case 0: aktif = filter.recent;  break;
                case 1: aktif = filter.nama;    break;
                case 2: aktif = filter.hp;      break;
                case 3: aktif = filter.attack;  break;
                case 4: aktif = filter.defense; break;
                case 5: aktif = filter.speed;   break;
                case 6: aktif = filter.type;    break;
                case 7: aktif = filter.id;      break;
            }

            cout << "| ";

            if(!pilih_type_mode && cursor == i)
                cout << ">> ";
            else
                cout << "   ";

            if(aktif)
                cout << "[x] ";
            else
                cout << "[ ] ";

            cout << left << setw(28) << menu[i] << "  |\n";
        }

        cout << "|______________________________________|\n";

        if(filter.type)
        {
            cout << "\n ______________________________________\n";
            cout << "|             PILIH TYPE              |\n";
            cout << "|_____________________________________|\n";

            for(int i = 0; i < 5; i++)
            {
                cout << "| ";

                if(pilih_type_mode && type_cursor == i)
                {
                    cout << ">> ";
                }
                else
                {
                    cout << "   ";
                }

                if(selected_type == type_list[i])
                {
                    cout << "[x] ";
                }
                else
                {
                    cout << "[ ] ";
                }

                cout << left << setw(27) << type_list[i] << "  |\n";
            }

            cout << "|_____________________________________|\n";
        }

        cout << "\n ______________________________________\n";

        if(pilih_type_mode)
        {
            cout << "| ENTER  | Pilih Type                 |\n";
            cout << "| ESC    | Kembali ke Filter          |\n";
        }
        else
        {
            cout << "| ENTER  | Toggle Filter              |\n";
            cout << "| SPACE  | Tampilkan Deck             |\n";
            cout << "| ESC    | Kembali                    |\n";
        }
        cout << "|_____________________________________|\n";

        string active_filter = "";

        if(filter.recent)
            active_filter += "Recent ";

        if(filter.nama)
            active_filter += "Nama ";

        if(filter.hp)
            active_filter += "HP ";

        if(filter.attack)
            active_filter += "Attack ";

        if(filter.defense)
            active_filter += "Defense ";

        if(filter.speed)
            active_filter += "Speed ";

        if(filter.id)
            active_filter += "ID ";

        if(filter.type)
        {
            if(selected_type != "")
            {
                active_filter += "+ Type(" + selected_type + ")";
            }
            else
            {
                active_filter += "+ Type(?)";
            }
        }

        cout << "\n ______________________________________\n";
        cout << "|            FILTER AKTIF              |\n";
        cout << "|______________________________________|\n";
        cout << "| " << left << setw(36) << active_filter << " |\n";
        cout << "|______________________________________|\n";
        
        char tombol = _getch();

        // ARROW
        if(tombol == -32)
        {
            tombol = _getch();

            // ATAS
            if(tombol == 72)
            {
                // MODE PILIH TYPE
                if(pilih_type_mode)
                {
                    type_cursor--;

                    if(type_cursor < 0)
                        type_cursor = 4;
                }

                // MODE FILTER
                else
                {
                    cursor--;

                    if(cursor < 0)
                        cursor = 7;
                }
            }

            // BAWAH
            else if(tombol == 80)
            {
                // MODE PILIH TYPE
                if(pilih_type_mode)
                {
                    type_cursor++;

                    if(type_cursor > 4)
                        type_cursor = 0;
                }

                // MODE FILTER
                else
                {
                    cursor++;

                    if(cursor > 7)
                        cursor = 0;
                }
            }
        }

        // ENTER
        else if(tombol == 13)
        {
            if(pilih_type_mode)
            {
                selected_type = type_list[type_cursor];
                pilih_type_mode = false;
                continue;
            }

            // reset primary filter
            if(cursor != 6 && cursor != 7)
            {
                resetPrimaryFilter(filter);
                filter.type = false;
                selected_type = "";
            }

            switch(cursor)
            {
                case 0:
                {
                    filter.recent = !filter.recent;
                    break;
                }

                case 1:
                {
                    filter.nama = !filter.nama;
                    break;
                }

                case 2:
                {
                    filter.hp = !filter.hp;
                    break;
                }

                case 3:
                {
                    filter.attack = !filter.attack;
                    break;
                }

                case 4:
                {
                    filter.defense = !filter.defense;
                    break;
                }

                case 5:
                {
                    filter.speed = !filter.speed;
                    break;
                }

                case 6:
                {
                    // TYPE hanya secondary
                    if(filter.recent  || filter.nama    || filter.hp      || filter.attack  || filter.defense || filter.speed)
                    {
                        filter.type = !filter.type;

                        if(filter.type)
                        {
                            pilih_type_mode = true;
                        }

                        // reset type saat dimatikan
                        if(!filter.type)
                        {
                            selected_type = "";
                            type_cursor = 0;
                        }
                    }
                    else
                    {
                        tampilPesan("Type harus digabung " "dengan filter lain!");
                    }

                    break;
                }

                case 7:
                {
                    filter.id = !filter.id;

                    if(filter.id)
                    {
                        resetPrimaryFilter(filter);
                        filter.id = true;
                        filter.type = false;
                        selected_type = "";
                    }

                    break;
                }
            }
        }

        // SPACE = APPLY
        else if(tombol == 32)
        {
            if(!filter.recent &&!filter.nama && !filter.hp && !filter.attack && !filter.defense && !filter.speed && !filter.id)
            {
                tampilPesan("Pilih minimal 1 filter!");
                continue;
            }

            UserMonster hasil[30];

            int jumlah = users[current_user].deck.jumlah;

            copyDeck(users[current_user].deck.monsters, hasil, jumlah);

            // MODE SORT
            int mode_sort = 0;

            if(filter.nama)
                mode_sort = 1;

            else if(filter.hp)
                mode_sort = 2;

            else if(filter.attack)
                mode_sort = 3;

            else if(filter.defense)
                mode_sort = 4;

            else if(filter.speed)
                mode_sort = 5;

            else if(filter.id)
                mode_sort = 6;

            // APPLY SORT
            switch(mode_sort)
            {
                case 1:
                    sortDeckNamaAscending(hasil, jumlah);
                    break;

                case 2:
                    sortDeckHPDescending(hasil, jumlah);
                    break;

                case 3:
                    sortDeckAttackDescending(hasil, jumlah);
                    break;

                case 4:
                    sortDeckDefenseDescending(hasil, jumlah);
                    break;

                case 5:
                    sortDeckSpeedDescending(hasil, jumlah);
                    break;

                case 6:
                    sortDeckIDAscending(hasil, jumlah);
                    break;
            }

            // TYPE FILTER
            if(filter.type)
            {
        
                if(selected_type == "")
                {
                    tampilPesan("Pilih type terlebih dahulu!");
                    continue;
                }

                filterType(hasil, jumlah, selected_type);
            }

            CLEAR_SCREEN;

            cout << "\n _____________________________________________________________________________________________________\n";
            cout << "|                                                                                                     |\n";
            cout << "|                                            USER DECK                                                |\n";
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

            tampilUserDeckRekursif(hasil, 0, jumlah);

            cout << "|______|________________________|_________|_________|_________|_________|_________________|___________|\n";
            cout << "\nTotal Monster : " << jumlah << endl;

            tunggu();
        }

        // ESC
        else if(tombol == 27)
        {
            // keluar dari mode pilih type
            if(pilih_type_mode)
            {
                pilih_type_mode = false;
            }

            // keluar menu
            else
            {
                return;
            }
        }
    }
}

