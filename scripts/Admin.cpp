#include "global.h"



void menuAdmin(User users[], Monster monsters[],int &jumlah_monster, int &next_monster_id, int &state)
{
    CLEAR_SCREEN;

    int pilih;

    cout << "\n__________________________________\n";
    cout << "|           MENU ADMIN           |\n";
    cout << "|________________________________|\n";
    cout << "| 1 | Create Monster             |\n";
    cout << "| 2 | Read Monster List          |\n";
    cout << "| 3 | Update Monster             |\n";
    cout << "| 4 | Delete Monster             |\n";
    cout << "| 5 | Read Permintaan User       |\n";
    cout << "| 6 | Logout                     |\n";
    cout << "|___|____________________________|\n";
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
            createMonster(monsters, jumlah_monster, next_monster_id);
            break;

        case 2:
            if(jumlah_monster == 0)
            {
                cout << "Belum ada monster\n";

                cout << "\nTekan ENTER untuk melanjutkan...";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();

                break;
            }

            tampilMonsterList(monsters, jumlah_monster, "DATABASE MONSTER");

            cout << "\nTekan ENTER untuk melanjutkan...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();

            break;

        case 3:
            updateMonster(monsters, jumlah_monster);
            break;

        case 4:
            deleteMonster(monsters, &jumlah_monster);
            break;

        // case 5
        case 6:
            logout(state);
            break;

        default:
            menuTidakValid();
    }
}

void createMonster(Monster monsters[], int &jumlah_monster, int &next_monster_id)
{
    if(jumlah_monster >= 100)
    {
        cout << "Database monster penuh!\n";

        cout << "\nTekan ENTER untuk melanjutkan...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        return;
    }

    Monster m;

    cout << "\nCREATE MONSTER\n\n";

    cout << "Nama monster   : ";
    cin.ignore();
    getline(cin, m.status.nama);

    cout << "HP monster     : ";
    cin >> m.status.hp;

    cout << "Attack monster : ";
    cin >> m.status.attack;

    cout << "Type monster   : ";
    cin >> m.type.tipe;

    m.status.id = next_monster_id;
    next_monster_id++;

    monsters[jumlah_monster] = m;

    jumlah_monster++;

    cout << "Monster berhasil dibuat\n";

    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void tampilMonsterList(Monster monsters[], int jumlah_monster)
{
    cout << "\n__________________________________________________________________________\n";
    cout << "|                                                                        |\n";
    cout << "|                               MONSTER LIST                             |\n";
    cout << "|________________________________________________________________________|\n";

    cout << left 
         << setw(5)  << "|ID"
         << setw(25) << "Nama"
         << setw(11) << "HP"
         << setw(11) << "ATK"
         << setw(21) << "Type"
         << "|"
         << endl;

    cout << "|------------------------------------------------------------------------|\n";

    for(int i = 0; i < jumlah_monster; i++)
    {
        cout << "|"
             << left << setw(4)  << monsters[i].status.id
             << ""
             << setw(25) << monsters[i].status.nama
             << ""
             << setw(11) << monsters[i].status.hp
             << ""
             << setw(11) << monsters[i].status.attack
             << ""
             << setw(21) << monsters[i].type.tipe
             << "|\n";
    }

    cout << "|________________________________________________________________________|\n";
}



void tampilMonsterList(Monster monsters[], int jumlah_monster, string judul)
{
    cout << "\n" << judul << "\n";

    cout << "\n__________________________________________________________________________\n";
    cout << "|                                                                        |\n";
    cout << "|                               MONSTER LIST                             |\n";
    cout << "|________________________________________________________________________|\n";

    cout << left 
         << setw(5)  << "|ID"
         << setw(25) << "Nama"
         << setw(11) << "HP"
         << setw(11) << "ATK"
         << setw(21) << "Type"
         << "|"
         << endl;

    cout << "|------------------------------------------------------------------------|\n";

    for(int i = 0; i < jumlah_monster; i++)
    {
        cout << "|"
             << left << setw(4)  << monsters[i].status.id
             << ""
             << setw(25) << monsters[i].status.nama
             << ""
             << setw(11) << monsters[i].status.hp
             << ""
             << setw(11) << monsters[i].status.attack
             << ""
             << setw(21) << monsters[i].type.tipe
             << "|\n";
    }

    cout << "|________________________________________________________________________|\n";
}




void updateMonster(Monster monsters[], int jumlah_monster)
{
    if(jumlah_monster == 0)
    {
        cout << "Belum ada monster\n";

        cout << "\nTekan ENTER untuk melanjutkan...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

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

            cout << "Nama baru   : ";
            cin >> monsters[i].status.nama;

            cout << "HP baru     : ";
            cin >> monsters[i].status.hp;

            cout << "Attack baru : ";
            cin >> monsters[i].status.attack;

            cout << "Type baru   : ";
            cin >> monsters[i].type.tipe;

            cout << "Monster berhasil diupdate\n";
        }
    }

    if(!ditemukan)
    {
        cout << "ID monster tidak ditemukan\n";
    }

    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}



void deleteMonster(Monster monsters[], int *jumlah_monster)
{
    if(*jumlah_monster == 0)
    {
        cout << "Belum ada monster\n";

        cout << "\nTekan ENTER untuk melanjutkan...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

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
        cout << "Monster tidak ditemukan\n";

        cout << "\nTekan ENTER untuk melanjutkan...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();

        return;
    }

    for(int i = index; i < *jumlah_monster - 1; i++)
    {
        monsters[i] = monsters[i + 1];
    }

    (*jumlah_monster)--;

    cout << "Monster berhasil dihapus\n";

    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}






// AJIS











// ULUNG
