#include "global.h"

void menuUser(User users[], Monster monsters[],int &jumlah_monster,int current_user, int &state)
{
    CLEAR_SCREEN;
    int pilih;

    cout << "\n___________________________________\n";
    cout << "|            MENU USER            |\n";
    cout << "|_________________________________|\n";
    cout << "| 1  | Gacha Monster              |\n";
    cout << "| 2  | Lihat Monster List         |\n";
    cout << "| 3  | Lihat Deck                 |\n";
    cout << "| 4  | Sacrifice Monster          |\n";
    cout << "| 5  | Delete Monster             |\n";
    cout << "| 6  | Sort Menu                  |\n";
    cout << "| 7  | Search Menu                |\n";
    cout << "| 0 | Logout                     |\n";
    cout << "|____|____________________________|\n";
    cout << "Pilih: ";

    cin >> pilih;

    if(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input harus angka!\n";

        cout << "\nTekan ENTER untuk melanjutkan...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return;
    }

    switch(pilih)
    {
        case 1:
            gachaMonster(users, monsters, jumlah_monster, current_user);
            break;

        case 2:
            if(jumlah_monster == 0)
            {
                cout << "Belum ada monster\n";

                cout << "\nTekan ENTER untuk kembali...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();

                break;
            }

            tampilMonsterList(monsters, jumlah_monster);

            cout << "\nTekan ENTER untuk kembali...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            break;

        case 3:
        {
            CLEAR_SCREEN;
            if(users[current_user].deck.jumlah == 0)
            {
                cout << "Deck masih kosong\n";

                cout << "\nTekan ENTER untuk kembali...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();

                break;
            }

            tampilUserDeck(users, current_user);

            cout << "\nTekan ENTER untuk kembali...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            break;
        }

        case 4:
            sacrificeMonster(users, current_user);
            break;

        case 5:
            deleteMonsterUser(users, current_user);
            break;


        // case 6
        case 7:
        {
            CLEAR_SCREEN;

            if(users[current_user].deck.jumlah == 0)
            {
                cout << "Deck kosong\n";

                cout << "\nTekan ENTER untuk kembali...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }

            sortDeckNamaAscending(users[current_user].deck.monsters, users[current_user].deck.jumlah);

            tampilUserDeck(users, current_user);

            cout << "\n(Disorting berdasarkan Nama A-Z)\n";

            cout << "\nTekan ENTER untuk kembali...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }

        case 8:
        {
            CLEAR_SCREEN;

            if(users[current_user].deck.jumlah == 0)
            {
                cout << "Deck kosong\n";

                cout << "\nTekan ENTER untuk kembali...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }

            sortDeckHPDescending(users[current_user].deck.monsters, users[current_user].deck.jumlah);

            tampilUserDeck(users, current_user);

            cout << "\n(Disorting berdasarkan HP Descending)\n";

            cout << "\nTekan ENTER untuk kembali...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }

        case 9:
        {
            CLEAR_SCREEN;

            if(users[current_user].deck.jumlah == 0)
            {
                cout << "Deck kosong\n";

                cout << "\nTekan ENTER untuk kembali...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }

            sortDeckIDAscending(users[current_user].deck.monsters, users[current_user].deck.jumlah);

            tampilUserDeck(users, current_user);

            cout << "\n(Disorting berdasarkan ID Ascending)\n";

            cout << "\nTekan ENTER untuk kembali...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            break;
        }

        case 10:
        {
            CLEAR_SCREEN;

            if(users[current_user].deck.jumlah == 0)
            {
                cout << "Deck kosong\n";

                cout << "\nTekan ENTER untuk kembali...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }

            cout << "\n_______________________________\n";
            cout << "|   SEARCH MONSTER BY ID      |\n";
            cout << "|_____________________________|\n";

            sortDeckIDAscending(users[current_user].deck.monsters,
                                users[current_user].deck.jumlah);

            int id;
            cout << "Masukkan ID monster: ";
            cin >> id;

            int index = binarySearchID(
                users[current_user].deck.monsters,
                users[current_user].deck.jumlah,
                id
            );

            if(index != -1)
            {
                cout << "\n__________________________________________________________________________\n";
                cout << "|                                                                        |\n";
                cout << "|                        HASIL PENCARIAN MONSTER                         |\n";
                cout << "|________________________________________________________________________|\n";

                cout << left
                    << setw(7)  << "|No"
                    << setw(25) << "Nama"
                    << setw(10) << "HP"
                    << setw(10) << "ATK"
                    << setw(21) << "Type"
                    << "|"
                    << endl;

                cout << "|------------------------------------------------------------------------|\n";

                cout << "|"
                    << left << setw(6)  << index + 1
                    << setw(25) << users[current_user].deck.monsters[index].nama
                    << setw(10) << users[current_user].deck.monsters[index].hp
                    << setw(10) << users[current_user].deck.monsters[index].attack
                    << setw(21) << users[current_user].deck.monsters[index].type
                    << "|\n";

                cout << "|________________________________________________________________________|\n";
            }
            else
            {
                cout << "\nMonster tidak ditemukan\n";
            }

            cout << "\nTekan ENTER untuk kembali...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            break;
        }

        case 11:
        {
            CLEAR_SCREEN;

            if(users[current_user].deck.jumlah == 0)
            {
                cout << "Deck kosong\n";

                cout << "\nTekan ENTER untuk kembali...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                break;
            }

            cout << "\n_______________________________\n";
            cout << "|   SEARCH MONSTER BY NAMA    |\n";
            cout << "|_____________________________|\n";

            string nama;
            cout << "Masukkan nama monster: ";
            cin >> nama;

            bool ditemukan = false;
            int jumlah_ditemukan = 0;

            cout << "\n__________________________________________________________________________\n";
            cout << "|                                                                        |\n";
            cout << "|                        HASIL PENCARIAN MONSTER                         |\n";
            cout << "|________________________________________________________________________|\n";

            cout << left
                << setw(7)  << "|No"
                << setw(25) << "Nama"
                << setw(10) << "HP"
                << setw(10) << "ATK"
                << setw(21) << "Type"
                << "|"
                << endl;

            cout << "|------------------------------------------------------------------------|\n";

            for(int i = 0; i < users[current_user].deck.jumlah; i++)
            {
                if(users[current_user].deck.monsters[i].nama == nama)
                {
                    ditemukan = true;
                    jumlah_ditemukan++;

                    cout << "|"
                        << left << setw(6)  << i + 1
                        << setw(25) << users[current_user].deck.monsters[i].nama
                        << setw(10) << users[current_user].deck.monsters[i].hp
                        << setw(10) << users[current_user].deck.monsters[i].attack
                        << setw(21) << users[current_user].deck.monsters[i].type
                        << "|\n";
                }
            }

            if(!ditemukan)
            {
                cout << "|                        MONSTER TIDAK DITEMUKAN                         |\n";
            }

            cout << "|________________________________________________________________________|\n";

            if(ditemukan)
            {
                cout << "\n(" << jumlah_ditemukan << " monster ditemukan)\n";
            }

            cout << "\nTekan ENTER untuk kembali...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            break;
        }

        case 0:
            logout(state);
            break;

        default:
            menuTidakValid();
    }
}



void gachaMonster(User users[], Monster monsters[],
                  int jumlah_monster, int current_user)
{
    if(jumlah_monster == 0)
    {
        cout << "Belum ada monster untuk digacha\n";

        cout << "\nTekan ENTER untuk kembali...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        return;
    }

    try {
        if(users[current_user].gold < 100)
            throw "Gold tidak cukup!";
    }
    catch(const char* msg) {
        cout << msg << endl;

        cout << "\nTekan ENTER untuk kembali...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        return;
    }
    
        if(users[current_user].deck.jumlah >= 100)
        {
            cout << "Deck monster penuh\n";

            cout << "\nTekan ENTER untuk kembali...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            return;
        }

    int random_index = rand() % jumlah_monster;

    Monster m = monsters[random_index];

    UserMonster um;

    um.monster_id = m.status.id;
    um.nama = m.status.nama;
    um.hp = m.status.hp;
    um.attack = m.status.attack;
    um.type = m.type.tipe;

    int deck_index = users[current_user].deck.jumlah;

    users[current_user].deck.monsters[deck_index] = um;

    users[current_user].deck.jumlah++;

    users[current_user].gold -= 100;

    cout << "\n=== GACHA BERHASIL ===\n";
    cout << "Monster       : " << um.nama << "\n";
    cout << "HP            : " << um.hp << "\n";
    cout << "Attack        : " << um.attack << "\n";
    cout << "Gold tersisa: " << users[current_user].gold << "\n";

    cout << "\nTekan ENTER untuk kembali...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


void tampilUserDeck(User users[], int current_user)
{
    cout << "\n__________________________________________________________________________\n";
    cout << "|                                                                        |\n";
    cout << "|                               USER DECK                                |\n";
    cout << "|________________________________________________________________________|\n";

    cout << left
         << setw(7)  << "|No"
         << setw(25) << "Nama"
         << setw(10) << "HP"
         << setw(10) << "ATK"
         << setw(21) << "Type"
         << "|"
         << endl;

    cout << "|------------------------------------------------------------------------|\n";

    tampilUserDeckRekursif(
        users[current_user].deck.monsters,
        0,
        users[current_user].deck.jumlah
    );

    cout << "|________________________________________________________________________|\n";
    cout << "Gold : " << users[current_user].gold << endl;
}



void tampilUserDeckRekursif(UserMonster monsters[], int index, int jumlah)
{
    if(index >= jumlah)
        return;

    cout << "|"
         << left << setw(6)  << index + 1
         << setw(25) << monsters[index].nama
         << setw(10) << monsters[index].hp
         << setw(10) << monsters[index].attack
         << setw(21) << monsters[index].type
         << "|\n";

    tampilUserDeckRekursif(monsters, index + 1, jumlah);
}


void sacrificeMonster(User users[], int current_user)
{
    if(users[current_user].deck.jumlah < 2)
    {
        cout << "Minimal butuh 2 monster untuk sacrifice\n";

        cout << "\nTekan ENTER untuk kembali...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

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
        cout << "Pilihan tidak valid\n";

        cout << "\nTekan ENTER untuk kembali...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

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
        cout << "Pilihan tidak valid\n";

        cout << "\nTekan ENTER untuk kembali...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        return;
    }

    for(int i = korban; i < users[current_user].deck.jumlah - 1; i++)
    {
        users[current_user].deck.monsters[i] =
        users[current_user].deck.monsters[i+1];
    }

    users[current_user].deck.jumlah--;

    cout << "Monster korban berhasil dikorbankan\n";

    cout << "\nTekan ENTER untuk kembali...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}


void deleteMonsterUser(User users[], int current_user)
{
    if(users[current_user].deck.jumlah == 0)
    {
        cout << "Deck kosong\n";

        cout << "\nTekan ENTER untuk kembali...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

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
        cout << msg << endl;

        cout << "\nTekan ENTER untuk kembali...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

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

    cout << "\nTekan ENTER untuk kembali...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
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

int sequentialSearchNama(UserMonster *monsters, int jumlah, string nama)
{
    for(int i = 0; i < jumlah; i++)
    {
        if(monsters[i].nama == nama)
            return i;
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
            sortDeckNamaAscending(users[current_user].deck.monsters,
                                  users[current_user].deck.jumlah);
            break;

        case 2:
            sortDeckHPDescending(users[current_user].deck.monsters,
                                 users[current_user].deck.jumlah);
            break;

        case 3:
            sortDeckIDAscending(users[current_user].deck.monsters,
                                users[current_user].deck.jumlah);
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

    if(users[current_user].deck.jumlah == 0)
    {
        cout << "Deck kosong\n";
        return;
    }

    if(pilih == 1)
    {
        sortDeckIDAscending(users[current_user].deck.monsters,
                            users[current_user].deck.jumlah);

        int id;
        cout << "Masukkan ID: ";
        cin >> id;

        int index = binarySearchID(
            users[current_user].deck.monsters,
            users[current_user].deck.jumlah,
            id
        );

        if(index != -1)
            cout << "Ditemukan: " << users[current_user].deck.monsters[index].nama << endl;
        else
            cout << "Tidak ditemukan\n";
    }
    else if(pilih == 2)
    {
        string nama;
        cout << "Masukkan nama: ";
        cin >> nama;

        int index = sequentialSearchNama(
            users[current_user].deck.monsters,
            users[current_user].deck.jumlah,
            nama
        );

        if(index != -1)
            cout << "Ditemukan: " << users[current_user].deck.monsters[index].nama << endl;
        else
            cout << "Tidak ditemukan\n";
    }
}





// AJIS











// ULUNG
