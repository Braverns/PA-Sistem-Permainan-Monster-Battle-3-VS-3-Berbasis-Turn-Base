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
                    tunggu();
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
    try {

        cout << "\n| [ Nama Monster ]\n";
        cout << "|> ";
        m.status.nama = inputClean("Nama Monster : ");
        if(m.status.nama.empty())
        throw invalid_argument("Nama monster tidak boleh kosong!");
        if(m.status.nama.length() > 20)
        throw invalid_argument("Nama monster tidak boleh lebih dari 20 karakter!");
        for(int j = 0; j < jumlah_monster; j++)
            {
                if(monsters[j].status.nama == m.status.nama)
                throw invalid_argument("Nama monster sudah ada");
            }

        cout << "| [ HP Monster ]\n";
        cout << "|> ";
        m.status.hp = inputAngka("HP Monster : ");
        if(m.status.hp <= 0)
        throw invalid_argument("HP harus lebih dari 0!");
        if(m.status.hp > 999)
        throw invalid_argument("HP tidak boleh lebih dari 999!");
    
        cout << "| [ Attack Monster ]\n";
        cout << "|> ";
        m.status.attack = inputAngka("Attack Monster : ");
         if(m.status.attack <= 0)
        throw invalid_argument("Attack harus lebih dari 0!");
        if(m.status.attack > 999)
        throw invalid_argument("Attack tidak boleh lebih dari 999!");

    
        cout << "| [ Defense Monster ]\n";
        cout << "|> ";
        m.status.defense = inputAngka("Defense Monster : ");
         if(m.status.defense <= 0)
        throw invalid_argument("Defense harus lebih dari 0!");
        if(m.status.defense > 999)
        throw invalid_argument("Defense tidak boleh lebih dari 999!");
    
        cout << "| [ Speed Monster ]\n";
        cout << "|> ";
        m.status.speed = inputAngka("Speed Monster : ");
        if(m.status.speed <= 0)
        throw invalid_argument("Speed harus lebih dari 0!");
        if(m.status.speed > 999)
        throw invalid_argument("Speed tidak boleh lebih dari 999!");
    
        cout << "| [ Type Monster ]\n";
        cout << "| 1. Fire\n";
        cout << "| 2. Water\n";
        cout << "| 3. Earth\n";
        cout << "| 4. Wind\n";
        cout << "| 5. Rock\n";
        cout << "|> ";

        int pilih_type;

        pilih_type = inputAngka("Pilih Type Monster : ");
        if(pilih_type == 1)
        m.type.tipe = "Fire";
        else if(pilih_type == 2)
        m.type.tipe = "Water";
        else if(pilih_type == 3)
        m.type.tipe = "Earth";
        else if(pilih_type == 4)
        m.type.tipe = "Wind";
        else if(pilih_type == 5)
        m.type.tipe = "Rock";
        else
        {
            tampilPesan("Pilihan type tidak valid!");
            return;
        }
        
        cout << "| [ Rarity Monster ]\n";
        cout << "| 1. Common\n";
        cout << "| 2. Rare\n";
        cout << "| 3. Epic\n";
        cout << "|> ";
    
        int pilih_rarity;
    
        pilih_rarity = inputAngka("Pilih Rarity Monster : ");
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
        
        validasiCreateMonster(m.status.nama, to_string(m.status.hp), to_string(m.status.attack), to_string(m.status.defense), to_string(m.status.speed), m.type.tipe, to_string(pilih_rarity));
        
    }catch(const invalid_argument& e)
    {
        tampilPesan(e.what());
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
    tunggu();
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
             << monsters[i].status.id;

        cout << "|"
             << setw(24);
                setColor(15);
        cout << monsters[i].status.nama;
        resetColor();
             
        cout << "|"
             << setw(10);
        setColor(10);
        cout << monsters[i].status.hp;
        resetColor();

        setColor(12);
        cout << "|"
             << setw(10)
             << monsters[i].status.attack;
        resetColor();

        cout << "|"
        << setw(10);
        setColor(14);
        cout << monsters[i].status.defense;
        resetColor();

        cout << "|"
             << setw(10);
        setColor(9);
        cout << monsters[i].status.speed;
        resetColor();

        cout << "|"
             << setw(21);
        setColor(getTypeColor(monsters[i].type.tipe));
        cout << monsters[i].type.tipe;
        resetColor();

        cout << "|"
             << setw(11);
        setColor(getRarityColor(monsters[i].rarity.rarity));
        cout << monsters[i].rarity.rarity;
        resetColor();

        cout << "|\n";
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

            try {

                string nama_baru = inputClean("Nama Baru : ");
                    if(nama_baru.length() > 20)
                        throw invalid_argument("Nama monster tidak boleh lebih dari 20 karakter!");
                    for(int j = 0; j < jumlah_monster; j++)
                    {
                        if(monsters[j].status.id == id) continue;
     
                        if(monsters[j].status.nama == nama_baru)
                            throw invalid_argument("Nama monster sudah dipakai!");
                    }
                    monsters[i].status.nama = nama_baru;

                monsters[i].status.hp = inputAngka("HP Baru : ");
                if(monsters[i].status.hp <= 0)
                    throw invalid_argument("HP harus lebih dari 0!");
                if(monsters[i].status.hp > 999)
                    throw invalid_argument("HP tidak boleh lebih dari 999!");
    
                monsters[i].status.attack = inputAngka("Attack Baru : ");
                 if(monsters[i].status.attack <= 0)
                    throw invalid_argument("Attack harus lebih dari 0!");
                if(monsters[i].status.attack > 999)
                    throw invalid_argument("Attack tidak boleh lebih dari 999!");
    
                monsters[i].status.defense = inputAngka("Defense Baru : ");
                if(monsters[i].status.defense <= 0)
                    throw invalid_argument("Defense harus lebih dari 0!");
                if(monsters[i].status.defense > 999)
                    throw invalid_argument("Defense tidak boleh lebih dari 999!");
    
                monsters[i].status.speed = inputAngka("Speed Baru : ");
                if(monsters[i].status.speed <= 0)
                    throw invalid_argument("Speed harus lebih dari 0!");
                if(monsters[i].status.speed > 999)
                    throw invalid_argument("Speed tidak boleh lebih dari 999!");
    
                cout << "\nPilih Type Baru :\n";
                cout << "1. Fire\n";
                cout << "2. Water\n";
                cout << "3. Earth\n";
                cout << "4. Wind\n";
                cout << "5. Rock\n";
                
                int pilih_type;

                pilih_type = inputAngka("Pilihan : ");
                if(pilih_type == 1)
                    monsters[i].type.tipe = "Fire";
                else if(pilih_type == 2)
                    monsters[i].type.tipe = "Water";
                else if(pilih_type == 3)
                    monsters[i].type.tipe = "Earth";
                else if(pilih_type == 4)
                    monsters[i].type.tipe = "Wind";
                else if(pilih_type == 5)
                    monsters[i].type.tipe = "Rock";
                else
                {
                    tampilPesan("Pilihan type tidak valid!");
                    return;
                }
    
                cout << "\nPilih Rarity Baru :\n";
                cout << "1. Common\n";
                cout << "2. Rare\n";
                cout << "3. Epic\n";
    
                int pilih_rarity;
    
                pilih_rarity = inputAngka("Pilih Rarity Monster : ");

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
            }
            catch(const invalid_argument& e)
            {
                tampilPesan2(e.what());
                return;
            }

            cout << "\nMonster berhasil diupdate\n";

            saveMonsterCSV(monsters, jumlah_monster);
        }
    }

    if(!ditemukan)
    {
        tampilPesan2("ID monster tidak ditemukan!");
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

    id = inputAngka("\nMasukkan ID monster yang ingin dihapus: ");

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