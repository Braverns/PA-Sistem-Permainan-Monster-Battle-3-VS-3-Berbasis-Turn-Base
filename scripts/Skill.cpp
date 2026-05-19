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
        if (s.nama.length() > 20)
        throw invalid_argument("Nama skill tidak boleh lebih dari 20 karakter!");
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
        if (s.power <= 0)
        throw invalid_argument("Power skill harus lebih dari 0!");
        if (s.power > 999)
        throw invalid_argument("Power skill tidak boleh lebih dari 999!");
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
            setColor(14);
        cout << skills[i].nama;
        resetColor();

        cout << "|"
             << setw(14);
            setColor(15);
        cout << skills[i].element;
        resetColor();

        cout << "|"
             << setw(14);
            setColor(3);
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

    tampilSkillList(skills, jumlah_skill);

    int id;
    bool ditemukan = false;

    cout << "\nMasukkan ID skill: ";
    cin >> id;

    for(int i = 0; i < jumlah_skill; i++)
    {
        if(skills[i].id == id)
        {
            ditemukan = true;

            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            try {
                skills[i].nama = inputClean("Nama Skill : ");
                if (skills[i].nama.empty())
                throw invalid_argument("Nama skill tidak boleh kosong!");
                if (skills[i].nama.length() > 20)
                throw invalid_argument("Nama skill tidak boleh lebih dari 20 karakter!");
    
                cout << "Element Skill\n";
                cout << "1. Fire\n";
                cout << "2. Water\n";
                cout << "3. Earth\n";
                cout << "4. Wind\n";
                cout << "5. Rock\n";
    
                int pilih_element;
                pilih_element = inputAngka("Element Baru : ");
                if(pilih_element == 1)
                skills[i].element = "Fire";
                else if(pilih_element == 2)
                skills[i].element = "Water";
                else if(pilih_element == 3)
                skills[i].element = "Earth";
                else if(pilih_element == 4)
                skills[i].element = "Wind";
                else if(pilih_element == 5)
                skills[i].element = "Rock";
                else
                {
                    tampilPesan("Pilihan element tidak valid!");
                    return;
                }
                if (skills[i].element.empty())
                throw invalid_argument("Element skill tidak boleh kosong!");
    
                 cout << "Tipe Skill\n";
                 cout << "1. Damage\n";
                 cout << "2. Heal\n";
                 cout << "3. AOE\n";
    
                 int pilih_tipe;
                 pilih_tipe = inputAngka("Tipe Baru : ");
                 if(pilih_tipe == 1)
                 skills[i].tipe = "Damage";
                 else if(pilih_tipe == 2)
                 skills[i].tipe = "Heal";
                 else if(pilih_tipe == 3)
                 skills[i].tipe = "AOE";
                 else
                 {
                     tampilPesan("Pilihan tipe tidak valid!");
                     return;
                 }
                 if (skills[i].tipe.empty())
                 throw invalid_argument("Tipe skill tidak boleh kosong!");
    
                skills[i].power = inputAngka("Power Skill : ");
                if (skills[i].power <= 0)
                throw invalid_argument("Power skill harus lebih dari 0!");
                if (skills[i].power > 999)
                throw invalid_argument("Power skill tidak boleh lebih dari 999!");
            }
            catch(const invalid_argument& e)
            {
                tampilPesan(e.what());
                return;
            }


            saveSkillCSV(skills, jumlah_skill);
            tampilPesan("Skill berhasil diupdate!");
            return;
        }
    }

    if(!ditemukan)
    {
        tampilPesan2("Skill tidak ditemukan!");
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

