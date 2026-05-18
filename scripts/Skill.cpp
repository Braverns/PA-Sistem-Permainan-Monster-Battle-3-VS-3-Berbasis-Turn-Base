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
                cout << ">> ";
            else
                cout << "   ";

            cout << left << setw(28) << menu[i] << " |\n";
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
                    tungguEnter();
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
    cin.ignore(numeric_limits<streamsize>::max(),'\n' );

    cout << "\nNama Skill : ";
    getline(cin, s.nama);

    cout << "Element Skill : ";
    cin >> s.element;

    cout << "Tipe Skill : ";
    cin >> s.tipe;

    cout << "Power Skill : ";
    cin >> s.power;

    if(cin.fail())
    {
        tampilPesan("Input tidak valid!");
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
             << skills[i].id

             << "|"
             << setw(24)
             << skills[i].nama

             << "|"
             << setw(14)
             << skills[i].element

             << "|"
             << setw(14)
             << skills[i].tipe

             << "|"
             << setw(9)
             << skills[i].power

             << "|\n";
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

            cout << "\nNama Baru : ";
            getline(cin, skills[i].nama);

            cout << "Element Baru : ";
            cin >> skills[i].element;

            cout << "Tipe Baru : ";
            cin >> skills[i].tipe;

            cout << "Power Baru : ";
            cin >> skills[i].power;

            if(cin.fail())
            {
                tampilPesan("Input tidak valid!");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            }

            saveSkillCSV(skills, jumlah_skill);
            tampilPesan("Skill berhasil diupdate!");
            return;
        }
    }

    if(!ditemukan)
    {
        tampilPesan("Skill tidak ditemukan!");
    }
}


void deleteSkill(Skill skills[], int &jumlah_skill)
{
    if(jumlah_skill == 0)
    {
        tampilPesan("Belum ada skill!");
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
        tampilPesan("Skill tidak ditemukan!");
        return;
    }

    for(int i = index; i < jumlah_skill - 1;i++)
    {
        skills[i] = skills[i + 1];
    }

    jumlah_skill--;

    saveSkillCSV(skills, jumlah_skill);
    tampilPesan("Skill berhasil dihapus!");
}

