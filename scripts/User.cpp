#include "global.h"


void menuUser(User users[], Monster monsters[], Skill skills[],
    int jumlah_monster, int jumlah_skill, int jumlah_user, int current_user, int &state)
{
    int cursor = 0;

    string menu[9] =
    {
        "Battle",
        "Active Team",
        "Gacha Monster",
        "Lihat Deck",
        "Monster List",
        "Sacrifice Monster",
        "Delete Monster",
        "Search Deck",
        "Logout"
    };

    while(true)
    {
        CLEAR_SCREEN;

        cout << "\n __________________________________\n";
        cout << "|            MENU USER            |\n";
        cout << "|_________________________________|\n";

        for(int i = 0; i < 9; i++)
        {
            cout << "| ";

            if(cursor == i)
            {
                setColor(15);
                cout << ">> ";
            }
            else
            {
                cout << "   ";
                resetColor();
            }

            cout << left << setw(28) << menu[i] << " |\n";
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
                    cursor = 8;
            }

            // DOWN
            else if(tombol == 80)
            {
                playSFX(L"music/cursor3.wav");

                cursor++;

                if(cursor > 8)
                    cursor = 0;
            }
        }

        // ENTER
        else if(tombol == 13)
        {
            switch(cursor)
            {
                case 0:
                    battleMenu(users, monsters, skills, jumlah_monster, jumlah_skill, current_user, jumlah_user);
                    break;

                case 1:
                    pilihActiveTeam(users, current_user, jumlah_user);
                    break;

                case 2:
                    gachaMonster(users, monsters, skills, jumlah_monster, jumlah_skill, current_user, jumlah_user);
                    break;

                case 3:
                    menuLihatDeck(users, current_user);
                    break;

                case 4:
                {
                    CLEAR_SCREEN;

                    if(jumlah_monster == 0)
                        tampilPesan("Belum ada monster!");
                    else
                    {
                        tampilMonsterList(monsters, jumlah_monster);
                        tunggu();
                    }

                    break;
                }

                case 5:
                    sacrificeMonster(users, current_user, jumlah_user);
                    break;

                case 6:
                    deleteMonsterUser(users, current_user, jumlah_user);
                    break;

                case 7:
                    menuSearch(users, current_user);
                    break;

                case 8:
                    logout(state);
                    return;
            }
        }
    }
}


// USER DELETE & SACRIFICE


void sacrificeMonster(User users[], int current_user, int jumlah_user)
{
    if(users[current_user].deck.jumlah < 2)
    {
        cout << "Minimal butuh 2 monster untuk sacrifice\n";
        tunggu();
        return;
    }

    int target = tampilUserDeckInput(users, current_user);

    if(target == -1)
    {
        tampilPesan("Sacrifice dibatalkan!");
        return;
    }

    cout << "\nPilih monster yang akan dikorbankan";
    tungguEnter();

    int korban = tampilUserDeckInput(users, current_user);

    if(korban == -1)
    {
        tampilPesan("Sacrifice dibatalkan!");
        return;
    }

    if(target < 0 || target >= users[current_user].deck.jumlah || korban < 0 || korban >= users[current_user].deck.jumlah || target == korban)
    {
        tampilPesan("Pilihan monster tidak valid!");
        return;
    }

    cout << "\nPilih atribut yang ingin ditingkatkan:\n";
    cout << "1. HP\n";
    cout << "2. Attack\n";
    cout << "3. Defense\n";
    cout << "4. Speed\n";

    int pilih;
    pilih = inputAngka("Pilihan: ");

        if(pilih == 1)
        {
            users[current_user].deck.monsters[target].hp += 1;
            cout << "HP berhasil ditingkatkan\n";
        }
        else if(pilih == 2)
        {
            users[current_user].deck.monsters[target].attack += 1;
            cout << "Attack berhasil ditingkatkan\n";
        }
        else if(pilih == 3)
        {
            users[current_user].deck.monsters[target].defense += 1;
            cout << "Defense berhasil ditingkatkan\n";
        }
        else if(pilih == 4)
        {
            users[current_user].deck.monsters[target].speed += 1;
            cout << "Speed berhasil ditingkatkan\n";
        }
        else
        {
            tampilPesan("Pilihan tidak valid!");
            return;
        }

    for(int i = korban; i < users[current_user].deck.jumlah - 1; i++)
    {
        users[current_user].deck.monsters[i] = users[current_user].deck.monsters[i+1];
    }

    users[current_user].deck.jumlah--;

    for(int i = 0; i < 3; i++)
    {
        users[current_user].active_team[i] = -1;
    }

    saveUserCSV(users, jumlah_user);
    saveDeckCSV(users, jumlah_user);

    cout << "Monster korban berhasil dikorbankan\n";
    tunggu();
}


void deleteMonsterUser(User users[],int current_user,int jumlah_user)
{
    if(users[current_user].deck.jumlah == 0)
    {
        tampilPesan("Deck kosong!");
        return;
    }

    int pilih = tampilUserDeckInput(users, current_user);

    if(pilih == -1)
    {
        tampilPesan("Delete dibatalkan!");
        return;
    }

    try {
        if(pilih < 0 || pilih >= users[current_user].deck.jumlah)
            throw "Index monster tidak valid!";
    }
    catch(const char* msg) {
        tampilPesan(msg);
        return;
    }

    cout << users[current_user].deck.monsters[pilih].nama << " dihapus dari deck\n";

    for(int i = pilih; i < users[current_user].deck.jumlah - 1; i++)
    {
        users[current_user].deck.monsters[i] = users[current_user].deck.monsters[i+1];
    }

    users[current_user].deck.jumlah--;
    users[current_user].gold += 50;

    cout << "+50 gold diterima\n";
    cout << "Gold sekarang: " << users[current_user].gold << "\n";

    for(int i = 0; i < 3; i++)
    {
        users[current_user].active_team[i] = -1;
    }

    saveUserCSV(users, jumlah_user);
    saveDeckCSV(users, jumlah_user);

    tunggu();
}


// SORT & SEARCH


void sortDeckNamaAscending(UserMonster monsters[], int jumlah)
{
    for(int i = 0; i < jumlah - 1; i++)
    {
        for(int j = 0; j < jumlah - i - 1; j++)
        {
            if(monsters[j].nama > monsters[j+1].nama)
            {
                UserMonster temp = monsters[j];
                monsters[j] = monsters[j+1];
                monsters[j+1] = temp;
            }
        }
    }
}

void sortDeckHPDescending(UserMonster monsters[], int jumlah)
{
    for(int i = 0; i < jumlah - 1; i++)
    {
        for(int j = 0; j < jumlah - i - 1; j++)
        {
            if(monsters[j].hp < monsters[j+1].hp)
            {
                UserMonster temp = monsters[j];
                monsters[j] = monsters[j+1];
                monsters[j+1] = temp;
            }
        }
    }
}

void sortDeckIDAscending(UserMonster monsters[], int jumlah)
{
    for(int i = 0; i < jumlah - 1; i++)
    {
        for(int j = 0; j < jumlah - i - 1; j++)
        {
            if(monsters[j].deck_id > monsters[j+1].deck_id)
            {
                UserMonster temp = monsters[j];
                monsters[j] = monsters[j+1];
                monsters[j+1] = temp;
            }
        }
    }
}

int interpolationSearchID(UserMonster *monsters, int jumlah, int target_id)
{
    int left = 0, right = jumlah - 1;

    while(left <= right &&
          target_id >= monsters[left].deck_id &&
          target_id <= monsters[right].deck_id)
    {
        // Hindari pembagian nol
        if(monsters[right].deck_id == monsters[left].deck_id)
        {
            if(monsters[left].deck_id == target_id) return left;
            else return -1;
        }

        // Rumus interpolasi
        int pos = left + ((target_id - monsters[left].deck_id) * (right - left))
                        / (monsters[right].deck_id - monsters[left].deck_id);

        if(monsters[pos].deck_id == target_id)
            return pos;
        else if(monsters[pos].deck_id < target_id)
            left = pos + 1;
        else
            right = pos - 1;
    }

    return -1;
}

void menuSearch(User users[], int current_user)
{
    CLEAR_SCREEN;
    
    cout << "\n=== MENU SEARCH ===\n";
    cout << "1. Cari berdasarkan ID\n";
    cout << "2. Cari berdasarkan Nama\n";
    cout << "0. Kembali\n";
    
    int input;

    input = inputAngka("pilihan: ");
    if(cin.fail())
    {
        tampilPesan2("Menu tidak valid!");
        return;
    }

    if(users[current_user].deck.jumlah == 0)
    {
        tampilPesan2("Deck kosong!");
        return;
    }

    CLEAR_SCREEN;
    tampilUserDeck(users, current_user);
    // id
    if(input == 1)
    {

        sortDeckIDAscending(users[current_user].deck.monsters, users[current_user].deck.jumlah);

        int id;
        id = inputAngka("Masukkan ID: ");

        CLEAR_SCREEN;

        int index = interpolationSearchID(users[current_user].deck.monsters, users[current_user].deck.jumlah, id);

        tampilHasilSearchID(users[current_user].deck.monsters, index);
        tunggu();
    }

    // nama
    else if(input == 2)
    {

        string nama;
        nama = inputClean("Masukkan Nama: ");

        CLEAR_SCREEN;

        tampilHasilSearchNama(users[current_user].deck.monsters, users[current_user].deck.jumlah, nama);
        tunggu();
    }
    else if(input == 0)
    {
        return;
    }
    else
    {
        tampilPesan("Menu tidak valid!");
        return;
    }

}

void tampilHasilSearchID(UserMonster monsters[], int index)
{
    cout << "\n _________________________________________________________________________________________________________\n";
    cout << "|                                                                                                         |\n";
    cout << "|                                         HASIL PENCARIAN MONSTER                                         |\n";
    cout << "|_________________________________________________________________________________________________________|\n";

    cout << left
         << setw(7)  << "|No"
         << setw(25) << "|Nama"
         << setw(10) << "|HP"
         << setw(10) << "|ATK"
         << setw(10) << "|DEF"
         << setw(10) << "|SPD"
         << setw(22) << "|Type"
         << setw(12) << "|Rarity"
         << "|"
         << endl;

    cout << "|------|------------------------|---------|---------|---------|---------|---------------------|-----------|\n";

    if(index != -1)
    {
        cout << "|"
             << left << setw(6)
             << index + 1;

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
             << setw(21);
        setColor(getTypeColor(monsters[index].type));
        cout << monsters[index].type;
        resetColor();

        cout << "|"
             << setw(11);
        setColor(getRarityColor(monsters[index].rarity));
        cout << monsters[index].rarity;
        resetColor();

        cout << "|\n";
    }
    else
    {
        cout << "|                                                                                                         |\n";
        cout << "|                                      MONSTER TIDAK DITEMUKAN                                            |\n";
        cout << "|                                                                                                         |\n";
    }

    cout << "|______|________________________|_________|_________|_________|_________|_____________________|___________|\n";
}

void tampilHasilSearchNama(UserMonster monsters[], int jumlah, string nama)
{
    bool ditemukan = false;

    cout << "\n _________________________________________________________________________________________________________\n";
    cout << "|                                                                                                         |\n";
    cout << "|                                        HASIL PENCARIAN MONSTER                                          |\n";
    cout << "|_________________________________________________________________________________________________________|\n";

    cout << left
         << setw(7)  << "|No"
         << setw(25) << "|Nama"
         << setw(10) << "|HP"
         << setw(10) << "|ATK"
         << setw(10) << "|DEF"
         << setw(10) << "|SPD"
         << setw(22) << "|Type"
         << setw(12) << "|Rarity"
         << "|"
         << endl;

    cout << "|------|------------------------|---------|---------|---------|---------|---------------------|-----------|\n";

    for(int i = 0; i < jumlah; i++)
    {
        if(monsters[i].nama == nama)
        {
            ditemukan = true;

            cout << "|"
                 << left << setw(6)
                 << i + 1;

            cout << "|"
                 << setw(24);
            setColor(15);
            cout << monsters[i].nama;
            resetColor();

            cout << "|"
                 << setw(9);
            setColor(10);
            cout << monsters[i].hp;
            resetColor();

            cout << "|"
                 << setw(9);
            setColor(12);
            cout << monsters[i].attack;
            resetColor();

            cout << "|"
                 << setw(9);
            setColor(14);
            cout << monsters[i].defense;
            resetColor();

            cout << "|"
                 << setw(9);
            setColor(9);
            cout << monsters[i].speed;
            resetColor();

            cout << "|"
                 << setw(21);
            setColor(getTypeColor(monsters[i].type));
            cout << monsters[i].type;
            resetColor();

            cout << "|"
                 << setw(11);
            setColor(getRarityColor(monsters[i].rarity));
            cout << monsters[i].rarity;
            resetColor();

            cout << "|\n";
        }
    }

    if(!ditemukan)
    {
        cout << "|                                                                                                         |\n";
        cout << "|                                     MONSTER TIDAK DITEMUKAN                                             |\n";
        cout << "|                                                                                                         |\n";
    }

    cout << "|______|________________________|_________|_________|_________|_________|_____________________|___________|\n";
}



// AJIS











// ULUNG
