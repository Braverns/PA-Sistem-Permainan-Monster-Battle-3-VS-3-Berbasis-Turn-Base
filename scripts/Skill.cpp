#include "global.h"

void menuSkill(Skill skills[], int &jumlah_skill)
{
    int cursor = 0;

    string menu[5] =
    {
        "Create Skill",
        "Read Skill List",
        "Update Skill",
        "Delete Skill",
        "Kembali"
    };

    while(true)
    {
        CLEAR_SCREEN;

        cout << "\n __________________________________\n";
        cout << "|          KELOLA SKILL           |\n";
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
        cout << "\nGunakan UP/DOWN dan ENTER\n";

        char tombol = _getch();

        // ARROW
        if(tombol == -32)
        {
            tombol = _getch();

            // ATAS
            if(tombol == 72)
            {
                cursor--;

                if(cursor < 0)
                    cursor = 4;
            }

            // BAWAH
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
                    createSkill(skills, jumlah_skill);
                    break;

                case 1:
                    CLEAR_SCREEN;
                    tampilSkillList(skills, jumlah_skill);
                    tunggu();
                    break;

                case 2:
                    updateSkill(skills, jumlah_skill);
                    break;

                case 3:
                    deleteSkill(skills, jumlah_skill);
                    break;

                case 4:
                    return;
            }
        }
    }
}


void createSkill(Skill skills[], int &jumlah_skill)
{
    if(jumlah_skill >= 100)
    {
        tampilPesan("Database skill penuh!");
        return;
    }

    Skill s;

    CLEAR_SCREEN;

    cout << "\n __________________________________\n";
    cout << "|          CREATE SKILL           |\n";
    cout << "|_________________________________|\n";
    s.id = jumlah_skill + 1;
    cout << "\nID Skill : " << s.id << endl;

    try {
        s.nama = inputClean("nama skill : ");
        if (s.nama.empty())
        throw invalid_argument("Nama skill tidak boleh kosong!");
        validasiPanjang(s.nama, 20, "Nama skill");
        for(int j = 0; j < jumlah_skill; j++)
            {
                if(skills[j].nama == s.nama)
                throw invalid_argument("Nama skill sudah ada");
            }
    
        cout << "Element Skill\n";
        cout << "1. Fire\n";
        cout << "2. Water\n";
        cout << "3. Earth\n";
        cout << "4. Wind\n";
        cout << "5. Rock\n";

        int pilih_element;
        pilih_element = inputAngka("Pilih Element : ");

        if(pilih_element == 1)
        s.element = "Fire";
        else if(pilih_element == 2)
        s.element = "Water";
        else if(pilih_element == 3)
        s.element = "Earth";
        else if(pilih_element == 4)
        s.element = "Wind";
        else if(pilih_element == 5)
        s.element = "Rock";
        else
        {
            tampilPesan("Pilihan element tidak valid!");
            return;
        }
        if (s.element.empty())
        throw invalid_argument("Element skill tidak boleh kosong!");
    
        cout << "Tipe Skill\n";
        cout << "1. Damage\n";
        cout << "2. Heal\n";
        cout << "3. AOE\n";

        int pilih_tipe;
        pilih_tipe = inputAngka("Pilihan Tipe : ");
        if(pilih_tipe == 1)
        s.tipe = "Damage";
        else if(pilih_tipe == 2)
        s.tipe = "Heal";
        else if(pilih_tipe == 3)
        s.tipe = "AOE";
        else
        {
            tampilPesan("Pilihan tipe tidak valid!");
            return;
        }
        if (s.tipe.empty())
        throw invalid_argument("Tipe skill tidak boleh kosong!");
        
    
        s.power = inputAngka("Power Skill : ");
        validasiRange(s.power, 1, 999, "Power skill");
    }
    catch(const invalid_argument& e)
    {
        tampilPesan(e.what());
        return;
    }


    skills[jumlah_skill] = s;
    jumlah_skill++;

    saveSkillCSV(skills, jumlah_skill);

    tampilPesan("Skill berhasil dibuat!");
}


void tampilSkillList(Skill skills[], int jumlah_skill)
{
    cout << "\n ______________________________________________________________________\n";
    cout << "|                                                                      |\n";
    cout << "|                            SKILL LIST                                |\n";
    cout << "|______________________________________________________________________|\n";

    cout << left
         << setw(6)  << "|ID"
         << setw(25) << "|Nama"
         << setw(15) << "|Element"
         << setw(15) << "|Tipe"
         << setw(10) << "|Power"
         << "|"
         << endl;

    cout << "|-----|------------------------|--------------|--------------|---------|\n";

    for(int i = 0; i < jumlah_skill; i++)
    {
        cout << "|"
             << left << setw(5)
             << skills[i].id;

        cout << "|"
             << setw(24);
            setColor(15);
        cout << skills[i].nama;
        resetColor();

        cout << "|"
             << setw(14);
        setColor(getTypeColor(skills[i].element));
        cout << skills[i].element;
        resetColor();

        cout << "|"
             << setw(14);
        setColor(getTypeSkillColor(skills[i].tipe));
        cout << skills[i].tipe;
        resetColor();

        cout << "|"
             << setw(9);
            setColor(12);
        cout << skills[i].power;
        resetColor();

        cout << "|\n";
    }

    cout << "|_____|________________________|______________|______________|_________|\n";
}

// =====================================
// UPDATE SKILL
// =====================================

void updateSkill(Skill skills[], int jumlah_skill)
{
    if(jumlah_skill == 0)
    {
        tampilPesan("Belum ada skill!");
        return;
    }

    int index =
    pilihSkillUpdate(
        skills,
        jumlah_skill
    );

    if(index == -1)
    {
        tampilPesan("Update dibatalkan!");
        return;
    }

    string menu[4] =
    {
        "Nama",
        "Element",
        "Tipe",
        "Power"
    };

    bool pilih_update[4] =
    {
        false,
        false,
        false,
        false
    };

    int cursor = 0;

    while(true)
    {
        CLEAR_SCREEN;

        cout << "\n _________________________________________________\n";
        cout << "|                                                 |\n";
        cout << "|                 UPDATE SKILL                    |\n";
        cout << "|_________________________________________________|\n";

        cout << "| Nama    : ";
        cout << left << setw(38);
        setColor(15);
        cout << skills[index].nama;
        resetColor();
        cout << "|\n";

        cout << "| Element : ";
        cout << left << setw(38);
        setColor(getTypeColor(skills[index].element));
        cout << skills[index].element;
        resetColor();
        cout << "|\n";

        cout << "| Tipe    : ";
        cout << left << setw(38);
        setColor(getTypeSkillColor(skills[index].tipe));
        cout << skills[index].tipe;
        resetColor();
        cout << "|\n";

        cout << "| Power   : ";
        cout << left << setw(38);
        setColor(12);
        cout << skills[index].power;
        resetColor();
        cout << "|\n";

        cout << "|_________________________________________________|\n";

        for(int i = 0; i < 4; i++)
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
                 << setw(41)
                 << menu[i]
                 << "|\n";

            resetColor();
        }

        cout << "|_________________________________________________|\n";

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

            if(tombol == 72)
            {
                cursor--;

                if(cursor < 0)
                    cursor = 3;
            }

            else if(tombol == 80)
            {
                cursor++;

                if(cursor > 3)
                    cursor = 0;
            }
        }

        // SPACE
        else if(tombol == 32)
        {
            pilih_update[cursor] =
            !pilih_update[cursor];
        }

        // ENTER
        else if(tombol == 13)
        {
            bool ada_pilihan = false;

            for(int i = 0; i < 4; i++)
            {
                if(pilih_update[i])
                    ada_pilihan = true;
            }

            if(!ada_pilihan)
            {
                tampilPesan("Pilih minimal 1 field!");
                continue;
            }


            Skill temp = skills[index];

            try
            {
                // NAMA
                if(pilih_update[0])
                {
                    cout << "\nNama Lama : " << temp.nama;
                    cout << "\nNama Baru : ";

                    string nama_baru = inputClean("");
                    validasiPanjang(nama_baru, 20, "Nama skill");

                    if(nama_baru.empty())
                    {
                        throw invalid_argument("Nama skill tidak boleh kosong!");
                    }

                    for(int i = 0; i < jumlah_skill; i++)
                    {
                        if(i == index)
                            continue;

                        if(skills[i].nama == nama_baru)
                        {
                            throw invalid_argument("Nama skill sudah digunakan!");
                        }
                    }

                    temp.nama = nama_baru;
                }

                // ELEMENT
                if(pilih_update[1])
                {
                    cout << "\nElement Lama : " << temp.element;
                    cout << "\n";
                    cout << "1. Fire\n";
                    cout << "2. Water\n";
                    cout << "3. Earth\n";
                    cout << "4. Wind\n";
                    cout << "5. Rock\n";

                    int pilih = inputAngka("Pilih Element Baru : ");

                    if(pilih == 1)
                        temp.element = "Fire";

                    else if(pilih == 2)
                        temp.element = "Water";

                    else if(pilih == 3)
                        temp.element = "Earth";

                    else if(pilih == 4)
                        temp.element = "Wind";

                    else if(pilih == 5)
                        temp.element = "Rock";

                    else
                    {
                        throw invalid_argument("Pilihan element tidak valid!");
                    }
                }

                // TIPE
                if(pilih_update[2])
                {
                    cout << "\nTipe Lama : " << temp.tipe;
                    cout << "\n";
                    cout << "1. Damage\n";
                    cout << "2. Heal\n";
                    cout << "3. AOE\n";

                    int pilih = inputAngka("Pilih Tipe Baru : ");

                    if(pilih == 1)
                        temp.tipe = "Damage";

                    else if(pilih == 2)
                        temp.tipe = "Heal";

                    else if(pilih == 3)
                        temp.tipe = "AOE";

                    else
                    {
                        throw invalid_argument("Pilihan tipe tidak valid!");
                    }
                }

                // POWER
                if(pilih_update[3])
                {
                    cout << "\nPower Lama : " << temp.power;
                    cout << "\nPower Baru : ";

                    temp.power = inputAngka("");
                    validasiRange(temp.power, 1, 999, "Power skill");
                }

                skills[index] = temp;

                saveSkillCSV(skills, jumlah_skill);

                tampilPesan("Skill berhasil diupdate!");

                return;
            }
            catch(const invalid_argument& e)
            {
                tampilPesan(e.what());
                return;
            }
        }


        else if(tombol == 27)
        {
            tampilPesan("Update dibatalkan!");
            return;
        }
    }
}


void deleteSkill(Skill skills[], int &jumlah_skill)
{
    if(jumlah_skill == 0)
    {
        tampilPesan2("Belum ada skill!");
        return;
    }

    tampilSkillList(skills, jumlah_skill);

    int id;
    int index = -1;

    cout << "\nMasukkan ID skill: ";
    cin >> id;

    for(int i = 0; i < jumlah_skill; i++)
    {
        if(skills[i].id == id)
        {
            index = i;
        }
    }

    if(index == -1)
    {
        tampilPesan2("Skill tidak ditemukan!");
        return;
    }

    for(int i = index; i < jumlah_skill - 1;i++)
    {
        skills[i] = skills[i + 1];
    }

    jumlah_skill--;

    saveSkillCSV(skills, jumlah_skill);
    tampilPesan2("Skill berhasil dihapus!");
}

int pilihSkillUpdate(Skill skills[], int jumlah_skill)
{
    if(jumlah_skill == 0)
    {
        tampilPesan("Belum ada skill!");
        return -1;
    }

    int pilih = 0;

    while(true)
    {
        CLEAR_SCREEN;

        cout << "\n ______________________________________________________________________\n";
        cout << "|                                                                      |\n";
        cout << "|                          PILIH SKILL UPDATE                          |\n";
        cout << "|______________________________________________________________________|\n";

        cout << left
             << setw(7)  << "|No"
             << setw(25) << "|Nama"
             << setw(15) << "|Element"
             << setw(15) << "|Tipe"
             << setw(10) << "|Power"
             << "|\n";

        cout << "|------|------------------------|--------------|--------------|---------|\n";

        tampilSkillRekursifInput(
            skills,
            0,
            jumlah_skill,
            pilih
        );

        cout << "|______|________________________|______________|______________|_________|\n";

        cout << "\n _________________________________________________\n";
        cout << "|                 CONTROL MENU                   |\n";
        cout << "|________________________________________________|\n";
        cout << "| [UP/DOWN] | Pindah Cursor                      |\n";
        cout << "| [ENTER]   | Pilih Skill                        |\n";
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
                    pilih = jumlah_skill - 1;
            }

            // DOWN
            else if(tombol == 80)
            {
                pilih++;

                if(pilih >= jumlah_skill)
                    pilih = 0;
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

void tampilSkillRekursifInput(
    Skill skills[],
    int index,
    int jumlah,
    int pilih
)
{
    if(index >= jumlah)
        return;

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
    cout << skills[index].nama;
    resetColor();

    cout << "|"
         << setw(14);

    setColor(
        getTypeColor(
            skills[index].element
        )
    );

    cout << skills[index].element;
    resetColor();

    cout << "|"
         << setw(14);

    setColor(
        getTypeSkillColor(
            skills[index].tipe
        )
    );

    cout << skills[index].tipe;
    resetColor();

    cout << "|"
         << setw(9);

    setColor(12);
    cout << skills[index].power;
    resetColor();

    cout << "|\n";

    tampilSkillRekursifInput(
        skills,
        index + 1,
        jumlah,
        pilih
    );
}