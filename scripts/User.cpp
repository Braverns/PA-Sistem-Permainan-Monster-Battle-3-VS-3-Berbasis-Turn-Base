#include "global.h"


void menuUser(User users[], Monster monsters[], int &jumlah_monster, int jumlah_user, int current_user,int &state)
{
    CLEAR_SCREEN;
    int pilih;

    cout << "\n___________________________________\n";
    cout << "|            MENU USER            |\n";
    cout << "|_________________________________|\n";
    cout << "| 1  | Battle                     |\n";
    cout << "| 2  | Active Team                |\n";
    cout << "| 3  | Gacha Monster              |\n";
    cout << "| 4  | Lihat Deck                 |\n";
    cout << "| 5  | Monster List               |\n";
    cout << "| 6  | Sacrifice Monster          |\n";
    cout << "| 7  | Delete Monster             |\n";
    cout << "| 8  | Sort Deck                  |\n";
    cout << "| 9  | Search Deck                |\n";
    cout << "| 0  | Logout                     |\n";
    cout << "|____|____________________________|\n";
    cout << "Pilih: ";

    cin >> pilih;
    if(cin.fail())
    {
        tampilPesan("Menu tidak valid!");
        return;
    }

    switch(pilih)
    {
        case 1:
            battleMenu(users,monsters, jumlah_monster, current_user, jumlah_user);
            break;

        case 2:
            pilihActiveTeam(users, current_user);
            break;

        case 3:
            gachaMonster(users,monsters, jumlah_monster, current_user, jumlah_user);
            break;

        case 4:
            tampilUserDeck(users, current_user);
            break;

        case 5:
        {
            CLEAR_SCREEN;

            if(jumlah_monster == 0)
                tampilPesan("Belum ada monster!");
            else
                tampilMonsterList(monsters, jumlah_monster);

            tungguEnter();

            break;
        }

        case 6:
            sacrificeMonster(users,current_user,jumlah_user);
            break;

        case 7:
            deleteMonsterUser(users, current_user, jumlah_user);
            break;

        case 8:
            menuSort(users, current_user);
            break;

        case 9:
            menuSearch(users, current_user);
            break;

        case 0:
            logout(state);
            break;

        default:
            tampilPesan("Menu tidak valid!");
    }
}


// void gachaMonster(User users[], Monster monsters[],
//                   int jumlah_monster, int current_user)
// {
//     if(jumlah_monster == 0)
//     {
//         tampilPesan("Belum ada monster yang tersedia untuk gacha!");
//         return;
//     }

//     try {
//         if(users[current_user].gold < 100)
//             throw "Gold tidak cukup!";
//     }
//     catch(const char* msg) {
//         tampilPesan(msg);
//         return;
//     }
    
//         if(users[current_user].deck.jumlah >= 30)
//         {
//             tampilPesan("Deck monster penuh!");
//             return;
//         }

//     int random_index = rand() % jumlah_monster;

//     Monster m = monsters[random_index];

//     UserMonster um;

//     um.monster_id = m.status.id;
//     um.nama = m.status.nama;
//     um.hp = m.status.hp;
//     um.attack = m.status.attack;
//     um.defense = m.status.defense;
//     um.speed = m.status.speed;
//     um.type = m.type.tipe;

//     int deck_index = users[current_user].deck.jumlah;

//     users[current_user].deck.monsters[deck_index] = um;

//     users[current_user].deck.jumlah++;

//     users[current_user].gold -= 100;

//     CLEAR_SCREEN;

//     cout << "\n ___________________________________________________\n";
//     cout << "|                                                   |\n";
//     cout << "|                 GACHA BERHASIL!                   |\n";
//     cout << "|___________________________________________________|\n";

//     cout << "| Monster  : " << left << setw(40) << um.nama << "|\n";
//     cout << "| Type     : " << left << setw(40) << um.type << "|\n";
//     cout << "| HP       : " << left << setw(39) << um.hp << "|\n";
//     cout << "| Attack   : " << left << setw(39) << um.attack << "|\n";
//     cout << "| Defense  : " << left << setw(39) << um.defense << "|\n";
//     cout << "| Speed    : " << left << setw(39) << um.speed << "|\n";
//     cout << "|___________________________________________________|\n";

//     cout << "\nGold tersisa : " << users[current_user].gold << endl;

//     tungguEnter();
// }


void buatKartuMonster(UserMonster monster, string kartu[])
{
    kartu[0] = " ____________________ ";

    kartu[1] = "| " + monster.nama;

    while(kartu[1].length() < 21)
        kartu[1] += " ";

    kartu[1] += "|";

    kartu[2] = "|--------------------|";

    kartu[3] = "| HP  : " + to_string(monster.hp);

    while(kartu[3].length() < 21)
        kartu[3] += " ";

    kartu[3] += "|";

    kartu[4] = "| ATK : " + to_string(monster.attack);

    while(kartu[4].length() < 21)
        kartu[4] += " ";

    kartu[4] += "|";

    kartu[5] = "| DEF : " + to_string(monster.defense);

    while(kartu[5].length() < 21)
        kartu[5] += " ";

    kartu[5] += "|";

    kartu[6] = "| SPD : " + to_string(monster.speed);

    while(kartu[6].length() < 21)
        kartu[6] += " ";

    kartu[6] += "|";

    kartu[7] = "|--------------------|";

    kartu[8] = "| Type: " + monster.type;

    while(kartu[8].length() < 21)
        kartu[8] += " ";

    kartu[8] += "|";

    kartu[9] = "|____________________|";
}


void tampilMultiKartu(UserMonster monsters[], int jumlah)
{
    for(int baris = 0; baris < jumlah; baris += 5)
    {
        int akhir = baris + 5;

        if(akhir > jumlah)
            akhir = jumlah;

        for(int line = 0; line < 10; line++)
        {
            for(int i = baris; i < akhir; i++)
            {
                string kartu[10];

                buatKartuMonster(monsters[i], kartu);

                cout << kartu[line] << " ";
            }

            cout << endl;
        }

        cout << endl;
    }
}


void gachaMonster(User users[], Monster monsters[], int jumlah_monster, int current_user, int jumlah_user)
{
    if(jumlah_monster == 0)
    {
        tampilPesan("Belum ada monster yang tersedia!");
        return;
    }

    CLEAR_SCREEN;

    int jumlah_gacha;

    cout << "\n _______________________________________________________________\n";
    cout << "|                                                               |\n";
    cout << "|                       MENU GACHA MONSTER                      |\n";
    cout << "|                                                               |\n";
    cout << "|                                                               |\n";
    cout << "|                    Harga 1x Gacha : 100 Gold                  |\n";
    cout << "|_______________________________________________________________|\n";
    cout << "Gold Kamu      : "
         << users[current_user].gold
         << "\n";

    cout << "\nJumlah gacha (0-10): ";
    cin >> jumlah_gacha;

    if(cin.fail())
    {
        tampilPesan("Input tidak valid!");
        return;
    }

    if(jumlah_gacha == 0)
    {
        tampilPesan("Gacha dibatalkan!");
        return;
    }

    if(jumlah_gacha < 0 || jumlah_gacha > 10)
    {
        tampilPesan("Jumlah gacha harus 0-10!");
        return;
    }

    int total_harga = jumlah_gacha * 100;

    if(users[current_user].gold < total_harga)
    {
        tampilPesan("Gold tidak cukup!");
        return;
    }

    if(users[current_user].deck.jumlah + jumlah_gacha > 30)
    {
        tampilPesan("Deck monster tidak cukup!");
        return;
    }

    UserMonster hasil_gacha[10];

    for(int i = 0; i < jumlah_gacha; i++)
    {
        int random_index = rand() % jumlah_monster;

        Monster m = monsters[random_index];

        UserMonster um;

        um.monster_id = m.status.id;
        um.nama       = m.status.nama;
        um.hp         = m.status.hp;
        um.attack     = m.status.attack;
        um.defense    = m.status.defense;
        um.speed      = m.status.speed;
        um.type       = m.type.tipe;

        hasil_gacha[i] = um;

        int deck_index = users[current_user].deck.jumlah;

        users[current_user].deck.monsters[deck_index] = um;

        users[current_user].deck.jumlah++;

        users[current_user].gold -= 100;
    }

    CLEAR_SCREEN;


    tampilMultiKartu(hasil_gacha, jumlah_gacha);

    cout << "Gold tersisa : "
         << users[current_user].gold
         << endl;
         
    saveUserCSV(users, jumlah_user);
    saveDeckCSV(users, jumlah_user);

    tungguEnter();
}


void tampilUserDeck(User users[], int current_user)
{
    CLEAR_SCREEN;
    cout << "\n _____________________________________________________________________________________________\n";
    cout << "|                                                                                             |\n";
    cout << "|                                        USER DECK                                            |\n";
    cout << "|_____________________________________________________________________________________________|\n";

    cout << left
         << setw(7)  << "|No"
         << setw(25) << "|Nama"
         << setw(10) << "|HP"
         << setw(10) << "|ATK"
         << setw(10) << "|DEF"  
         << setw(10) << "|SPD"
         << setw(22) << "|Type"
         << "|"
         << endl;

    cout << "|------|------------------------|---------|---------|---------|---------|---------------------|\n";

    tampilUserDeckRekursif(
        users[current_user].deck.monsters,
        0,
        users[current_user].deck.jumlah
    );
                 
    cout << "|______|________________________|_________|_________|_________|_________|_____________________|\n";
    cout << "Gold : " << users[current_user].gold << endl;

    tungguEnter();
}



void tampilUserDeckRekursif(UserMonster monsters[], int index, int jumlah)
{
    if(index >= jumlah)
        return;

    cout << "|"
         << left << setw(6)  << index + 1
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
         << setw(21) << monsters[index].type
         << "|\n";

    tampilUserDeckRekursif(monsters, index + 1, jumlah);
}


void sacrificeMonster(User users[], int current_user, int jumlah_user)
{
    if(users[current_user].deck.jumlah < 2)
    {
        cout << "Minimal butuh 2 monster untuk sacrifice\n";

        tungguEnter();

        return;
    }

    tampilUserDeck(users, current_user);

    int target;
    int korban;

    cout << "\nPilih monster yang akan ditingkatkan : ";
    cin >> target;

    cout << "Pilih monster yang akan dikorbankan  : ";
    cin >> korban;

    target--;
    korban--;

    if(target < 0 || target >= users[current_user].deck.jumlah ||
       korban < 0 || korban >= users[current_user].deck.jumlah ||
       target == korban)
    {
        tampilPesan("Pilihan monster tidak valid!");
        return;
    }

    cout << "\nPilih atribut yang ingin ditingkatkan:\n";
    cout << "1. HP\n";
    cout << "2. Attack\n";

    int pilih;

    cout << "Pilih: ";
    cin >> pilih;

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
    else
    {
        tampilPesan("Pilihan tidak valid!");
        return;
    }

    for(int i = korban; i < users[current_user].deck.jumlah - 1; i++)
    {
        users[current_user].deck.monsters[i] =
        users[current_user].deck.monsters[i+1];
    }

    users[current_user].deck.jumlah--;

    for(int i = 0; i < 3; i++)
    {
        users[current_user].active_team[i] = -1;
    }

    saveUserCSV(users, jumlah_user);
    saveDeckCSV(users, jumlah_user);

    cout << "Monster korban berhasil dikorbankan\n";

    tungguEnter();
}


void deleteMonsterUser(User users[],int current_user,int jumlah_user)
{
    if(users[current_user].deck.jumlah == 0)
    {
        tampilPesan("Deck kosong!");
        return;
    }

    tampilUserDeck(users, current_user);

    int pilih;

    cout << "\nPilih monster yang ingin dihapus: ";
    cin >> pilih;

    pilih--;

    try {
        if(pilih < 0 || pilih >= users[current_user].deck.jumlah)
            throw "Index monster tidak valid!";
    }
    catch(const char* msg) {
        tampilPesan(msg);
        return;
    }

    cout << users[current_user].deck.monsters[pilih].nama
         << " dihapus dari deck\n";

    for(int i = pilih; i < users[current_user].deck.jumlah - 1; i++)
    {
        users[current_user].deck.monsters[i] =
        users[current_user].deck.monsters[i+1];
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

    tungguEnter();
}

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
            if(monsters[j].monster_id > monsters[j+1].monster_id)
            {
                UserMonster temp = monsters[j];
                monsters[j] = monsters[j+1];
                monsters[j+1] = temp;
            }
        }
    }
}

int binarySearchID(UserMonster *monsters, int jumlah, int target_id)
{
    int left = 0, right = jumlah - 1;

    while(left <= right)
    {
        int mid = (left + right) / 2;

        if(monsters[mid].monster_id == target_id)
            return mid;
        else if(monsters[mid].monster_id < target_id)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

void menuSort(User users[], int current_user)
{
    CLEAR_SCREEN;

    int pilih;

    cout << "\n=== MENU SORT ===\n";
    cout << "1. Nama (A-Z)\n";
    cout << "2. HP (Desc)\n";
    cout << "3. ID (Asc)\n";
    cout << "Pilih: ";
    cin >> pilih;

    if(users[current_user].deck.jumlah == 0)
    {
        cout << "Deck kosong\n";
        return;
    }

    switch(pilih)
    {
        case 1:
            sortDeckNamaAscending(users[current_user].deck.monsters, users[current_user].deck.jumlah);
            break;

        case 2:
            sortDeckHPDescending(users[current_user].deck.monsters, users[current_user].deck.jumlah);
            break;

        case 3:
            sortDeckIDAscending(users[current_user].deck.monsters, users[current_user].deck.jumlah);
            break;

        default:
            cout << "Pilihan tidak valid\n";
            return;
    }

    tampilUserDeck(users, current_user);

}

void menuSearch(User users[], int current_user)
{
    CLEAR_SCREEN;

    int pilih;

    cout << "\n=== MENU SEARCH ===\n";
    cout << "1. Cari berdasarkan ID\n";
    cout << "2. Cari berdasarkan Nama\n";
    cout << "Pilih: ";
    cin >> pilih;

    if(cin.fail())
    {
        tampilPesan("Menu tidak valid!");
        return;
    }

    if(users[current_user].deck.jumlah == 0)
    {
        tampilPesan("Deck kosong!");
        return;
    }

    // id
    if(pilih == 1)
    {
        CLEAR_SCREEN;

        sortDeckIDAscending(users[current_user].deck.monsters, users[current_user].deck.jumlah);

        int id;
        cout << "Masukkan ID: ";
        cin >> id;

        CLEAR_SCREEN;

        int index = binarySearchID(users[current_user].deck.monsters, users[current_user].deck.jumlah, id);

        tampilHasilSearchID(users[current_user].deck.monsters, index);
        tungguEnter();
    }

    // nama
    else if(pilih == 2)
    {
        CLEAR_SCREEN;

        string nama;
        cout << "Masukkan nama: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, nama);

        CLEAR_SCREEN;

        tampilHasilSearchNama(users[current_user].deck.monsters, users[current_user].deck.jumlah, nama);
        tunggu();
    }

    else
    {
        tampilPesan("Menu tidak valid!");
        return;
    }

}

void tampilHasilSearchID(UserMonster monsters[], int index)
{
    cout << "\n _____________________________________________________________________________________________\n";
    cout << "|                                                                                             |\n";
    cout << "|                                   HASIL PENCARIAN MONSTER                                   |\n";
    cout << "|_____________________________________________________________________________________________|\n";

    cout << left
         << setw(7)  << "|No"
         << setw(25) << "|Nama"
         << setw(10) << "|HP"
         << setw(10) << "|ATK"
         << setw(10) << "|DEF"
         << setw(10) << "|SPD"
         << setw(22) << "|Type"
         << "|"
         << endl;

    cout << "|------|------------------------|---------|---------|---------|---------|---------------------|\n";

    if(index != -1)
    {
        cout << "|"
             << left << setw(6)  << index + 1
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
             << setw(21) << monsters[index].type
             << "|\n";
    }
    else
    {
        cout << "|                                                                                             |\n";
        cout << "|                                MONSTER TIDAK DITEMUKAN                                      |\n";
        cout << "|                                                                                             |\n";
    }

    cout << "|______|________________________|_________|_________|_________|_________|_____________________|\n";

}

void tampilHasilSearchNama(UserMonster monsters[], int jumlah, string nama)
{
    bool ditemukan = false;
    int count = 0;

    cout << "\n _____________________________________________________________________________________________\n";
    cout << "|                                                                                             |\n";
    cout << "|                                   HASIL PENCARIAN MONSTER                                   |\n";
    cout << "|_____________________________________________________________________________________________|\n";

    cout << left
         << setw(7)  << "|No"
         << setw(25) << "|Nama"
         << setw(10) << "|HP"
         << setw(10) << "|ATK"
         << setw(10) << "|DEF"
         << setw(10) << "|SPD"
         << setw(22) << "|Type"
         << "|"
         << endl;

    cout << "|------|------------------------|---------|---------|---------|---------|---------------------|\n";

    for(int i = 0; i < jumlah; i++)
    {
        if(monsters[i].nama == nama)
        {
            ditemukan = true;
            count++;

            cout << "|"
                 << left << setw(6)  << i + 1
                 << "|"
                 << setw(24) << monsters[i].nama
                 << "|"
                 << setw(9) << monsters[i].hp
                 << "|"
                 << setw(9) << monsters[i].attack
                 << "|"
                 << setw(9) << monsters[i].defense
                 << "|"
                 << setw(9) << monsters[i].speed
                 << "|"
                 << setw(21) << monsters[i].type
                 << "|\n";
        }
    }

    if(!ditemukan)
    {
        cout << "|                                                                                             |\n";
        cout << "|                                MONSTER TIDAK DITEMUKAN                                      |\n";
        cout << "|                                                                                             |\n";
    }

    cout << "|______|________________________|_________|_________|_________|_________|_____________________|\n";

}


void tampilActiveTeam(User users[], int current_user)
{
    cout << "\n ____________________________________________________________________________________________________\n";
    cout << "|                                                                                                    |\n";
    cout << "|                                      ACTIVE TEAM MONSTER                                           |\n";
    cout << "|____________________________________________________________________________________________________|\n";

    for(int i = 0; i < 3; i++)
    {
        int idx = users[current_user].active_team[i];

        cout << i + 1 << ". ";

        if(idx == -1)
        {
            cout << "[KOSONG]\n";
        }
        else
        {
            cout
            << users[current_user]
               .deck.monsters[idx]
               .nama

            << " (HP: "

            << users[current_user]
               .deck.monsters[idx]
               .hp

            << ")\n";
        }
    }
}

void pilihActiveTeam(User users[], int current_user)
{
    if(users[current_user].deck.jumlah < 3)
    {
        tampilPesan("Minimal membutuhkan 3 monster!");
        return;
    }

    tampilUserDeck(users, current_user);

    int pilihan[3];

    cout << "\n ________________________________________________\n";
    cout << "|                                                |\n";
    cout << "|           PILIH ACTIVE TEAM (3 MONSTER)        |\n"; 
    cout << "|                                                |\n";
    cout << "|________________________________________________|\n";

    for(int i = 0; i < 3; i++)
    {
        cout << "Pilih monster slot "
             << i + 1
             << " : ";

        cin >> pilihan[i];

        pilihan[i]--;

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

    CLEAR_SCREEN;

    cout << "Active team berhasil disimpan!\n";

    tampilActiveTeam(users, current_user);

    tungguEnter();
}

// AJIS











// ULUNG
