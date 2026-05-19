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
        validasiPanjang(m.status.nama, 20, "Nama monster");
        if(m.status.nama.empty())
        throw invalid_argument("Nama monster tidak boleh kosong!");
        for(int j = 0; j < jumlah_monster; j++)
            {
                if(monsters[j].status.nama == m.status.nama)
                throw invalid_argument("Nama monster sudah ada");
            }

        cout << "| [ HP Monster ]\n";
        cout << "|> ";
        m.status.hp = inputAngka("HP Monster : ");
        validasiRange(m.status.hp, 1, 999, "HP");

        cout << "| [ Attack Monster ]\n";
        cout << "|> ";
        m.status.attack = inputAngka("Attack Monster : ");
        validasiRange(m.status.attack, 1, 999, "Attack");

        cout << "| [ Defense Monster ]\n";
        cout << "|> ";
        m.status.defense = inputAngka("Defense Monster : ");
        validasiRange(m.status.defense, 1, 999, "Defense");
    
        cout << "| [ Speed Monster ]\n";
        cout << "|> ";
        m.status.speed = inputAngka("Speed Monster : ");
        validasiRange(m.status.speed, 1, 999, "Speed");
    
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
    cout << "\n _____________________________________________________________________________________________________________\n";
    cout << "|                                                                                                             |\n";
    cout << "|                                                MONSTER LIST                                                 |\n";
    cout << "|_____________________________________________________________________________________________________________|\n";

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

void updateMonster(Monster monsters[], int jumlah_monster)
{
    if(jumlah_monster == 0)
    {
        tampilPesan("Belum ada monster!");
        return;
    }

    int index = pilihMonsterUpdate(monsters, jumlah_monster);

    if(index == -1)
    {
        tampilPesan("Update dibatalkan!");
        return;
    }

    string menu[7] =
    {
        "Nama",
        "HP",
        "Attack",
        "Defense",
        "Speed",
        "Type",
        "Rarity"
    };

    bool pilih_update[7] =
    {
        false, false, false,
        false, false, false,
        false
    };

    int cursor = 0;

    while(true)
    {
        CLEAR_SCREEN;

        cout << "\n ______________________________________________________\n";
        cout << "|                                                      |\n";
        cout << "|                 UPDATE MONSTER                       |\n";
        cout << "|______________________________________________________|\n";

        cout << "| Nama    : ";
        cout << left << setw(43);
        setColor(15);
        cout << monsters[index].status.nama;
        resetColor();
        cout << "|\n";

        cout << "| HP      : ";
        cout << left << setw(43);
        setColor(10);
        cout << monsters[index].status.hp;
        resetColor();
        cout << "|\n";

        cout << "| Attack  : ";
        cout << left << setw(43);
        setColor(12);
        cout << monsters[index].status.attack;
        resetColor();
        cout << "|\n";

        cout << "| Defense : ";
        cout << left << setw(43);
        setColor(14);
        cout << monsters[index].status.defense;
        resetColor();
        cout << "|\n";

        cout << "| Speed   : ";
        cout << left << setw(43);
        setColor(9);
        cout << monsters[index].status.speed;
        resetColor();
        cout << "|\n";

        cout << "| Type    : ";
        cout << left << setw(43);
        setColor(getTypeColor(monsters[index].type.tipe));
        cout << monsters[index].type.tipe;
        resetColor();
        cout << "|\n";

        cout << "| Rarity  : ";
        cout << left << setw(43);
        setColor(getRarityColor(monsters[index].rarity.rarity));
        cout << monsters[index].rarity.rarity;
        resetColor();
        cout << "|\n";

        cout << "|______________________________________________________|\n";

        for(int i = 0; i < 7; i++)
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
            }

            if(pilih_update[i])
            {
                setColor(10);
                cout << "[X] ";
            }
            else
            {
                resetColor();
                cout << "[ ] ";
            }

            cout << left
                 << setw(46)
                 << menu[i]
                 << "|\n";

            resetColor();
        }

        cout << "|______________________________________________________|\n";

        cout << "\n _________________________________________________\n";
        cout << "|                 CONTROL MENU                   |\n";
        cout << "|________________________________________________|\n";
        cout << "| [UP/DOWN] | Pindah Cursor                      |\n";
        cout << "| [SPACE]   | Pilih Update                       |\n";
        cout << "| [ENTER]   | Konfirmasi Update                  |\n";
        cout << "| [ESC]     | Kembali                            |\n";
        cout << "|___________|____________________________________|\n";

        char tombol = _getch();

        // ARROW
        if(tombol == -32)
        {
            tombol = _getch();

            // UP
            if(tombol == 72)
            {
                cursor--;

                if(cursor < 0)
                    cursor = 6;
            }

            // DOWN
            else if(tombol == 80)
            {
                cursor++;

                if(cursor > 6)
                    cursor = 0;
            }
        }

        // SPACE
        else if(tombol == 32)
        {
            pilih_update[cursor] = !pilih_update[cursor];
        }

        // ENTER
        else if(tombol == 13)
        {
            bool ada_pilihan = false;

            for(int i = 0; i < 7; i++)
            {
                if(pilih_update[i])
                {
                    ada_pilihan = true;
                }
            }

            if(!ada_pilihan)
            {
                tampilPesan("Pilih minimal 1 field!");
                continue;
            }

            Monster temp = monsters[index];

            try
            {
                // NAMA
                if(pilih_update[0])
                {
                    cout << "\nNama Lama : " << temp.status.nama;
                    cout << "\nNama Baru : ";

                    string nama_baru = inputClean("");

                    validasiPanjang(nama_baru, 20, "Nama monster");

                    if(nama_baru.empty())
                    {
                        throw invalid_argument("Nama monster tidak boleh kosong!");
                    }

                    for(int i = 0; i < jumlah_monster; i++)
                    {
                        if(i == index)
                            continue;

                        if(monsters[i].status.nama == nama_baru)
                        {
                            throw invalid_argument("Nama monster sudah digunakan!");
                        }
                    }

                    temp.status.nama = nama_baru;
                }

                // HP
                if(pilih_update[1])
                {
                    cout << "\nHP Lama : " << temp.status.hp;
                    cout << "\nHP Baru : ";

                    temp.status.hp = inputAngka("");
                    validasiRange(temp.status.hp, 1, 999, "HP");
                }

                // ATTACK
                if(pilih_update[2])
                {
                    cout << "\nAttack Lama : " << temp.status.attack;
                    cout << "\nAttack Baru : ";

                    temp.status.attack = inputAngka("");
                    validasiRange(temp.status.attack, 1, 999, "Attack");
                }

                // DEFENSE
                if(pilih_update[3])
                {
                    cout << "\nDefense Lama : " << temp.status.defense;
                    cout << "\nDefense Baru : ";

                    temp.status.defense = inputAngka("");
                    validasiRange(temp.status.defense, 1, 999, "Defense");
                }

                // SPEED
                if(pilih_update[4])
                {
                    cout << "\nSpeed Lama : " << temp.status.speed;
                    cout << "\nSpeed Baru : ";

                    temp.status.speed = inputAngka("");

                    validasiRange(temp.status.speed, 1, 999, "Speed");
                }

                // TYPE
                if(pilih_update[5])
                {
                    cout << "\nType Lama : " << temp.type.tipe;
                    cout << "\n";
                    cout << "1. Fire\n";
                    cout << "2. Water\n";
                    cout << "3. Earth\n";
                    cout << "4. Wind\n";
                    cout << "5. Rock\n";

                    int pilih = inputAngka("Pilih Type Baru : ");

                    if(pilih == 1)
                        temp.type.tipe = "Fire";

                    else if(pilih == 2)
                        temp.type.tipe = "Water";

                    else if(pilih == 3)
                        temp.type.tipe = "Earth";

                    else if(pilih == 4)
                        temp.type.tipe = "Wind";

                    else if(pilih == 5)
                        temp.type.tipe = "Rock";

                    else
                    {
                        throw invalid_argument("Pilihan type tidak valid!");
                    }
                }

                // RARITY
                if(pilih_update[6])
                {
                    cout << "\nRarity Lama : " << temp.rarity.rarity;
                    cout << "\n";
                    cout << "1. Common\n";
                    cout << "2. Rare\n";
                    cout << "3. Epic\n";

                    int pilih = inputAngka("Pilih Rarity Baru : ");

                    if(pilih == 1)
                        temp.rarity.rarity = "Common";

                    else if(pilih == 2)
                        temp.rarity.rarity = "Rare";

                    else if(pilih == 3)
                        temp.rarity.rarity = "Epic";

                    else
                    {
                        throw invalid_argument(
                            "Pilihan rarity tidak valid!"
                        );
                    }
                }

                monsters[index] = temp;
                saveMonsterCSV(monsters, jumlah_monster);
                tampilPesan("Monster berhasil diupdate!");

                return;
            }
            catch(const invalid_argument& e)
            {
                tampilPesan(e.what());
                return;
            }
        }

        // ESC
        else if(tombol == 27)
        {
            tampilPesan("Update dibatalkan!");
            return;
        }
    }
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


int pilihMonsterUpdate(Monster monsters[], int jumlah_monster)
{
    if(jumlah_monster == 0)
    {
        tampilPesan("Belum ada monster!");
        return -1;
    }

    int pilih = 0;

    while(true)
    {
        clearArea();

        cout << "\n _____________________________________________________________________________________________________________\n";
        cout << "|                                                                                                             |\n";
        cout << "|                                            PILIH MONSTER UPDATE                                             |\n";
        cout << "|_____________________________________________________________________________________________________________|\n";

        cout << left
             << setw(7)  << "|No"
             << setw(25) << "|Nama"
             << setw(11) << "|HP"
             << setw(11) << "|ATK"
             << setw(11) << "|DEF"
             << setw(11) << "|SPD"
             << setw(22) << "|Type"
             << setw(12) << "|Rarity"
             << "|\n";

        cout << "|------|------------------------|----------|----------|----------|----------|---------------------|-----------|\n";

        tampilMonsterRekursifInput(
            monsters,
            0,
            jumlah_monster,
            pilih
        );

        cout << "|______|________________________|__________|__________|__________|__________|_____________________|___________|\n";

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

            // UP
            if(tombol == 72)
            {
                pilih--;

                if(pilih < 0)
                {
                    pilih = jumlah_monster - 1;
                }
            }

            // DOWN
            else if(tombol == 80)
            {
                pilih++;

                if(pilih >= jumlah_monster)
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

void tampilMonsterRekursifInput(Monster monsters[], int index,int jumlah,int pilih)
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
     << setw(4)
     << index + 1;

    cout << "|"
         << setw(24);

    setColor(15);
    cout << monsters[index].status.nama;
    resetColor();

    cout << "|"
         << setw(10);

    setColor(10);
    cout << monsters[index].status.hp;
    resetColor();

    cout << "|"
         << setw(10);

    setColor(12);
    cout << monsters[index].status.attack;
    resetColor();

    cout << "|"
         << setw(10);

    setColor(14);
    cout << monsters[index].status.defense;
    resetColor();

    cout << "|"
         << setw(10);

    setColor(9);
    cout << monsters[index].status.speed;
    resetColor();

    cout << "|"
         << setw(21);

    setColor(
        getTypeColor(
            monsters[index].type.tipe
        )
    );

    cout << monsters[index].type.tipe;
    resetColor();

    cout << "|"
         << setw(11);

    setColor(
        getRarityColor(
            monsters[index].rarity.rarity
        )
    );

    cout << monsters[index].rarity.rarity;
    resetColor();

    cout << "|\n";

    tampilMonsterRekursifInput(monsters, index + 1, jumlah, pilih);

    resetColor();
}