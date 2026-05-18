#include "global.h"

void menuKelolaMonster(Monster monsters[], int &jumlah_monster, int &next_monster_id)
{
    int cursor = 0;

    string menu[5] =
    {
        "Create Monster",
        "Read Monster List",
        "Update Monster",
        "Delete Monster",
        "Kembali"
    };

    while(true)
    {
        CLEAR_SCREEN;

        cout << "\n __________________________________\n";
        cout << "|         KELOLA MONSTER          |\n";
        cout << "|_________________________________|\n";

        for(int i = 0; i < 5; i++)
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

        // ARROW
        if(tombol == -32)
        {
            tombol = _getch();

            if(tombol == 72)
            {
                cursor--;

                if(cursor < 0)
                    cursor = 4;
            }

            else if(tombol == 80)
            {
                cursor++;

                if(cursor > 4)
                    cursor = 0;
            }
        }

        // ENTER
        else if(tombol == 13)
        {
            switch(cursor)
            {
                case 0:
                    createMonster(monsters, jumlah_monster, next_monster_id);
                    break;

                case 1:
                    CLEAR_SCREEN;
                    tampilMonsterList(monsters, jumlah_monster, "");
                    tungguClear();
                    break;

                case 2:
                    updateMonster(monsters, jumlah_monster);
                    break;

                case 3:
                    deleteMonster(monsters, &jumlah_monster);
                    break;

                case 4:
                    return;
            }
        }
    }
}

void createMonster(Monster monsters[], int &jumlah_monster, int &next_monster_id)
{
    if(jumlah_monster >= 100)
    {
        tampilPesan("Database monster penuh!");
        return;
    }

    Monster m;

    CLEAR_SCREEN;

    cout << "\n __________________________________________________\n";
    cout << "|                                                  |\n";
    cout << "|                 CREATE MONSTER                   |\n";
    cout << "|__________________________________________________|\n";

    cout << "| ID Monster : " << next_monster_id;

    int sisa = 33 - to_string(next_monster_id).length();

    for(int i = 0; i < sisa; i++)
        cout << " ";

    cout << "   |\n";
    cout << "|                                                  |";
    cin.clear();

    cout << "\n| [ Nama Monster ]\n";
    cout << "|> ";
    getline(cin >> ws, m.status.nama);

    cout << "| [ HP Monster ]\n";
    cout << "|> ";
    cin >> m.status.hp;

    cout << "| [ Attack Monster ]\n";
    cout << "|> ";
    cin >> m.status.attack;

    cout << "| [ Defense Monster ]\n";
    cout << "|> ";
    cin >> m.status.defense;

    cout << "| [ Speed Monster ]\n";
    cout << "|> ";
    cin >> m.status.speed;

    cout << "| [ Type Monster ]\n";
    cout << "|> ";
    cin >> m.type.tipe;


    cout << "| [ Rarity Monster ]\n";
    cout << "| 1. Common\n";
    cout << "| 2. Rare\n";
    cout << "| 3. Epic\n";
    cout << "|> ";

    int pilih_rarity;

    cin >> pilih_rarity;

    if(pilih_rarity == 1)
        m.rarity.rarity = "Common";

    else if(pilih_rarity == 2)
        m.rarity.rarity = "Rare";

    else if(pilih_rarity == 3)
        m.rarity.rarity = "Epic";

    else
    {
        tampilPesan("Pilihan rarity tidak valid!");
        return;
    }


    if(cin.fail())
    {
        tampilPesan("Input angka tidak valid!");
        return;
    }

    if(m.status.nama == "")
    {
        tampilPesan("Nama monster tidak boleh kosong!");
        return;
    }

    m.status.id =next_monster_id;
    next_monster_id++;
    monsters[jumlah_monster] = m;
    jumlah_monster++;

    saveMonsterCSV(monsters, jumlah_monster );

    CLEAR_SCREEN;


    cout << "\n _________________________________________________\n";
    cout << "|                                                 |\n";
    cout << "|           MONSTER BERHASIL DIBUAT               |\n";
    cout << "|_________________________________________________|\n";
    cout << "| " << left << setw(47) << ("Nama    : " + m.status.nama) << " |\n";
    cout << "| " << left << setw(47) << ("HP      : " + to_string(m.status.hp)) << " |\n";
    cout << "| " << left << setw(47) << ("Attack  : " + to_string(m.status.attack)) << " |\n";
    cout << "| " << left << setw(47) << ("Defense : " + to_string(m.status.defense)) << " |\n";
    cout << "| " << left << setw(47) << ("Speed   : " + to_string(m.status.speed)) << " |\n";
    cout << "| " << left << setw(47) << ("Type    : " + m.type.tipe) << " |\n";
    cout << "| " << left << setw(47) << ("Rarity  : " + m.rarity.rarity)  << " |\n";
    cout << "|_________________________________________________|\n";
    cout << endl;
    tungguEnter();
}

void tampilMonsterList(Monster monsters[], int jumlah_monster)
{
    cout << "\n ___________________________________________________________________________________________________________\n";
    cout << "|                                                                                                           |\n";
    cout << "|                                               MONSTER LIST                                                |\n";
    cout << "|___________________________________________________________________________________________________________|\n";

    cout << left
         << setw(5)  << "|ID"
         << setw(25) << "|Nama"
         << setw(11) << "|HP"
         << setw(11) << "|ATK"
         << setw(11) << "|DEF"
         << setw(11) << "|SPD"
         << setw(22) << "|Type"
         << setw(12) << "|Rarity"
         << "|"
         << endl;

    cout << "|----|------------------------|----------|----------|----------|----------|---------------------|-----------|\n";

    for(int i = 0; i < jumlah_monster; i++)
    {
        cout << "|"
             << left << setw(4)
             << monsters[i].status.id

             << "|"
             << setw(24)
             << monsters[i].status.nama

             << "|"
             << setw(10)
             << monsters[i].status.hp

             << "|"
             << setw(10)
             << monsters[i].status.attack

             << "|"
             << setw(10)
             << monsters[i].status.defense

             << "|"
             << setw(10)
             << monsters[i].status.speed

             << "|"
             << setw(21)
             << monsters[i].type.tipe

             << "|"
             << setw(11)
             << monsters[i].rarity.rarity

             << "|\n";
    }

    cout << "|____|________________________|__________|__________|__________|__________|_____________________|___________|\n";
}

void tampilMonsterList(Monster monsters[], int jumlah_monster, string judul)
{
    cout << "\n" << judul << "\n";
    tampilMonsterList(monsters, jumlah_monster);
}

void updateMonster( Monster monsters[], int jumlah_monster)
{
    if(jumlah_monster == 0)
    {
        tampilPesan("Belum ada monster untuk diupdate!");
        return;
    }

    tampilMonsterList(monsters, jumlah_monster);

    int id;
    bool ditemukan = false;

    cout << "\nMasukkan ID monster yang ingin diupdate: ";
    cin >> id;

    for(int i = 0; i < jumlah_monster; i++)
    {
        if(monsters[i].status.id == id)
        {
            ditemukan = true;
            
            cout << "\nUPDATE MONSTER\n\n";
            cout << "Nama Baru    : ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            getline(cin, monsters[i].status.nama);

            cout << "HP Baru      : ";
            cin >> monsters[i].status.hp;

            cout << "Attack Baru  : ";
            cin >> monsters[i].status.attack;

            cout << "Defense Baru : ";
            cin >> monsters[i].status.defense;

            cout << "Speed Baru   : ";
            cin >> monsters[i].status.speed;

            cout << "Type Baru    : ";
            cin >> monsters[i].type.tipe;


            cout << "\nPilih Rarity Baru\n";
            cout << "1. Common\n";
            cout << "2. Rare\n";
            cout << "3. Epic\n";
            cout << "Pilih : ";

            int pilih_rarity;

            cin >> pilih_rarity;

            if(pilih_rarity == 1)
                monsters[i].rarity.rarity = "Common";

            else if(pilih_rarity == 2)
                monsters[i].rarity.rarity = "Rare";

            else if(pilih_rarity == 3)
                monsters[i].rarity.rarity = "Epic";

            else
            {
                tampilPesan("Pilihan rarity tidak valid!");
                return;
            }

            cout << "\nMonster berhasil diupdate\n";

            saveMonsterCSV(monsters, jumlah_monster);
        }
    }

    if(!ditemukan)
    {
        tampilPesan("ID monster tidak ditemukan!");
        return;
    }

    tungguEnter();
}

void deleteMonster(Monster monsters[], int *jumlah_monster)
{
    if(*jumlah_monster == 0)
    {
        tampilPesan("Belum ada monster untuk dihapus!");
        return;
    }

    tampilMonsterList(monsters, *jumlah_monster);

    int id;
    int index = -1;

    cout << "\nMasukkan ID monster yang ingin dihapus: ";

    cin >> id;

    for(int i = 0; i < *jumlah_monster; i++)
    {
        if(monsters[i].status.id == id)
        {
            index = i;
        }
    }

    if(index == -1)
    {
        tampilPesan("ID monster tidak ditemukan!");
        return;
    }

    for(int i = index; i < *jumlah_monster - 1;i++)
    {
        monsters[i] = monsters[i + 1];
    }

    (*jumlah_monster)--;

    saveMonsterCSV(monsters, *jumlah_monster);

    tampilPesan("Monster berhasil dihapus");
}