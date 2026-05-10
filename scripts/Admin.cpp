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
    cout << "| 0 | Logout                     |\n";
    cout << "|___|____________________________|\n";
    cout << "Pilih: ";

    cin >> pilih;

    if(cin.fail())
    {
        tampilPesan("Pilihan tidak valid!");
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
                tampilPesan("Belum ada monster untuk ditampilkan!");
                break;
            }

            tampilMonsterList(monsters, jumlah_monster, "DATABASE MONSTER");

            tungguEnter();
            break;

        case 3:
            updateMonster(monsters, jumlah_monster);
            break;

        case 4:
            deleteMonster(monsters, &jumlah_monster);
            break;

        case 0:
            logout(state);
            break;

        default:
            tampilPesan("Pilihan tidak valid!");
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

    cout << "\nCREATE MONSTER\n\n";

    cout << "Nama monster    : ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, m.status.nama);

    cout << "HP monster      : ";
    cin >> m.status.hp;

    cout << "Attack monster  : ";
    cin >> m.status.attack;

    cout << "Defense monster : ";
    cin >> m.status.defense;

    cout << "Speed monster   : ";
    cin >> m.status.speed;

    cout << "Type monster    : ";
    cin >> m.type.tipe;

    m.status.id = next_monster_id;
    next_monster_id++;

    monsters[jumlah_monster] = m;

    jumlah_monster++;
    saveMonsterCSV(monsters, jumlah_monster);

    tampilPesan("Monster berhasil dibuat");
}

void tampilMonsterList(Monster monsters[], int jumlah_monster)
{
    cout << "\n _______________________________________________________________________________________________\n";
    cout << "|                                                                                               |\n";
    cout << "|                                         MONSTER LIST                                          |\n";
    cout << "|_______________________________________________________________________________________________|\n";

    cout << left 
         << setw(5)  << "|ID"
         << setw(25) << "|Nama"
         << setw(11) << "|HP"
         << setw(11) << "|ATK"
         << setw(11) << "|DEF"
         << setw(11) << "|SPD"
         << setw(22) << "|Type"
         << "|"
         << endl;

    cout << "|----|------------------------|----------|----------|----------|----------|---------------------|\n";

    for(int i = 0; i < jumlah_monster; i++)
    {
        cout << "|"
             << left << setw(4)  << monsters[i].status.id
             << "|"
             << setw(24) << monsters[i].status.nama
             << "|"
             << setw(10) << monsters[i].status.hp
             << "|"
             << setw(10) << monsters[i].status.attack
             << "|"
             << setw(10) << monsters[i].status.defense
             << "|"
             << setw(10) << monsters[i].status.speed
             << "|"
             << setw(21) << monsters[i].type.tipe
             << "|\n";
    }

    cout << "|____|________________________|__________|__________|__________|__________|_____________________|\n";
}



void tampilMonsterList(Monster monsters[], int jumlah_monster, string judul)
{
    cout << "\n" << judul << "\n";

    cout << "\n _______________________________________________________________________________________________\n";
    cout << "|                                                                                               |\n";
    cout << "|                                         MONSTER LIST                                          |\n";
    cout << "|_______________________________________________________________________________________________|\n";

    cout << left 
         << setw(5)  << "|ID"
         << setw(25) << "|Nama"
         << setw(11) << "|HP"
         << setw(11) << "|ATK"
         << setw(11) << "|DEF"
         << setw(11) << "|SPD"
         << setw(22) << "|Type"
         << "|"
         << endl;

    cout << "|----|------------------------|----------|----------|----------|----------|---------------------|\n";

    for(int i = 0; i < jumlah_monster; i++)
    {
        cout << "|"
             << left << setw(4)  << monsters[i].status.id
             << "|"
             << setw(24) << monsters[i].status.nama
             << "|"
             << setw(10) << monsters[i].status.hp
             << "|"
             << setw(10) << monsters[i].status.attack
             << "|"
             << setw(10) << monsters[i].status.defense
             << "|"
             << setw(10) << monsters[i].status.speed
             << "|"
             << setw(21) << monsters[i].type.tipe
             << "|\n";
    }
                                                                                   
    cout << "|____|________________________|__________|__________|__________|__________|_____________________|\n";
}




void updateMonster(Monster monsters[], int jumlah_monster)
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

            cout << "Monster berhasil diupdate\n";
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

    for(int i = index; i < *jumlah_monster - 1; i++)
    {
        monsters[i] = monsters[i + 1];
    }

    (*jumlah_monster)--;
    saveMonsterCSV(monsters, *jumlah_monster);

    tampilPesan("Monster berhasil dihapus");
}






// AJIS











// ULUNG
