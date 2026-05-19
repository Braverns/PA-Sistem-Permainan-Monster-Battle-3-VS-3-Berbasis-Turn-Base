#include "global.h"

string getRandomRarity()
{
    int roll = rand() % 100;

    if(roll < 70)
        return "Common";

    else if(roll < 95)
        return "Rare";

    else
        return "Epic";
}



int getMonsterByRarity(Monster monsters[], int jumlah_monster, string rarity)
{
    int kandidat[100];
    int jumlah_kandidat = 0;

    for(int i = 0; i < jumlah_monster; i++)
    {
        if(monsters[i].rarity.rarity == rarity)
        {
            kandidat[jumlah_kandidat] = i;
            jumlah_kandidat++;
        }
    }

    // fallback kalau rarity kosong
    if(jumlah_kandidat == 0)
    {
        return rand() % jumlah_monster;
    }

    int random_index = rand() % jumlah_kandidat;

    return kandidat[random_index];
}


void randomSkillMonster(UserMonster &monster, Skill skills[], int jumlah_skill)
{
    int kandidat[100];
    int jumlah_kandidat = 0;

    // ============================
    // FILTER SKILL SESUAI ELEMENT
    // ============================

    for(int i = 0; i < jumlah_skill; i++)
    {
        if(skills[i].element == monster.type)
        {
            kandidat[jumlah_kandidat] = i;
            jumlah_kandidat++;
        }
    }

    // fallback
    if(jumlah_kandidat == 0)
    {
        return;
    }

    // ============================
    // RANDOM 3 SKILL
    // ============================

    for(int i = 0; i < 3; i++)
    {
        int random_index = kandidat[rand() % jumlah_kandidat];
        monster.skills[i] = skills[random_index];
    }
}


void buatKartuMonster(UserMonster monster, string kartu[])
{
    kartu[0] =
    " ____________________ ";

    string nama = monster.nama;

    int padding = 20 - nama.length();
    int kiri = padding / 2;
    int kanan = padding - kiri;

    kartu[1] = "|";

    for(int i = 0; i < kiri; i++)
        kartu[1] += " ";

    kartu[1] += nama;

    for(int i = 0; i < kanan; i++)
        kartu[1] += " ";

    kartu[1] += "|";

    kartu[2] = "|____________________|";

    kartu[3] = "|HP  : " + to_string(monster.hp);
    while(kartu[3].length() < 21)
        kartu[3] += " ";

    kartu[3] += "|";


    kartu[4] = "|ATK : " + to_string(monster.attack);

    while(kartu[4].length() < 21)
        kartu[4] += " ";

    kartu[4] += "|";


    kartu[5] = "|DEF : " + to_string(monster.defense);

    while(kartu[5].length() < 21)
        kartu[5] += " ";

    kartu[5] += "|";

    kartu[6] = "|SPD : " + to_string(monster.speed);

    while(kartu[6].length() < 21)
        kartu[6] += " ";

    kartu[6] += "|";

    kartu[7] = "|S1  : " + monster.skills[0].nama;

    while(kartu[7].length() < 21)
        kartu[7] += " ";

    kartu[7] += "|";

    kartu[8] = "|S2  : " + monster.skills[1].nama;

    while(kartu[8].length() < 21)
        kartu[8] += " ";

    kartu[8] += "|";

    kartu[9] = "|S3  : " + monster.skills[2].nama;

    while(kartu[9].length() < 21)
        kartu[9] += " ";

    kartu[9] += "|";

    kartu[10] = "|TP  : " + monster.type;

    while(kartu[10].length() < 21)
        kartu[10] += " ";

    kartu[10] += "|";

    kartu[11] =
    "|____________________|";


    string rarity = monster.rarity;
    padding = 20 - rarity.length();
    kiri = padding / 2;
    kanan = padding - kiri;

    kartu[12] = "|";

    for(int i = 0; i < kiri; i++)
        kartu[12] += " ";

    kartu[12] += rarity;

    for(int i = 0; i < kanan; i++)
        kartu[12] += " ";

    kartu[12] += "|";


    kartu[13] = "|____________________|";
}


void tampilMultiKartu(UserMonster monsters[], int jumlah)
{
    for(int baris = 0; baris < jumlah; baris += 5)
    {
        int akhir = baris + 5;

        if(akhir > jumlah)
            akhir = jumlah;

        for(int line = 0; line < 14; line++)
        {
            for(int i = baris; i < akhir; i++)
            {
                string kartu[14];
                buatKartuMonster(monsters[i], kartu);

                int rarityColor =
                getRarityColor(monsters[i].rarity);

                // NAMA
                if(line == 1)
                {
                    string nama = monsters[i].nama;

                    int padding = 20 - nama.length();
                    int kiri = padding / 2;
                    int kanan = padding - kiri;

                    setColor(rarityColor);

                    cout << "|";

                    for(int j = 0; j < kiri; j++)
                        cout << " ";

                    resetColor();

                    setColor(15);
                    cout << nama;
                    resetColor();

                    setColor(rarityColor);

                    for(int j = 0; j < kanan; j++)
                        cout << " ";

                    cout << "|";

                    resetColor();
                }

                // HP
                else if(line == 3)
                {
                    setColor(rarityColor);
                    cout << "|";
                    resetColor();

                    cout << "HP  : ";

                    setColor(10);
                    cout << monsters[i].hp;
                    resetColor();

                    int sisa =
                    14 - to_string(monsters[i].hp).length();

                    for(int j = 0; j < sisa; j++)
                        cout << " ";

                    setColor(rarityColor);
                    cout << "|";
                    resetColor();
                }

                // ATK
                else if(line == 4)
                {
                    setColor(rarityColor);
                    cout << "|";
                    resetColor();

                    cout << "ATK : ";

                    setColor(12);
                    cout << monsters[i].attack;
                    resetColor();

                    int sisa =
                    14 - to_string(monsters[i].attack).length();

                    for(int j = 0; j < sisa; j++)
                        cout << " ";

                    setColor(rarityColor);
                    cout << "|";
                    resetColor();
                }

                // DEF
                else if(line == 5)
                {
                    setColor(rarityColor);
                    cout << "|";
                    resetColor();

                    cout << "DEF : ";

                    setColor(14);
                    cout << monsters[i].defense;
                    resetColor();

                    int sisa =
                    14 - to_string(monsters[i].defense).length();

                    for(int j = 0; j < sisa; j++)
                        cout << " ";

                    setColor(rarityColor);
                    cout << "|";
                    resetColor();
                }

                // SPD
                else if(line == 6)
                {
                    setColor(rarityColor);
                    cout << "|";
                    resetColor();

                    cout << "SPD : ";

                    setColor(9);
                    cout << monsters[i].speed;
                    resetColor();

                    int sisa =
                    14 - to_string(monsters[i].speed).length();

                    for(int j = 0; j < sisa; j++)
                        cout << " ";

                    setColor(rarityColor);
                    cout << "|";
                    resetColor();
                }

                // SKILL 1
                else if(line == 7)
                {
                    setColor(rarityColor);
                    cout << "|";
                    resetColor();

                    cout << "S1  : ";

                    setColor(
                    getTypeColor(
                    monsters[i].skills[0].element));

                    cout << monsters[i].skills[0].nama;
                    resetColor();

                    int sisa =
                    14 -
                    monsters[i].skills[0].nama.length();

                    for(int j = 0; j < sisa; j++)
                        cout << " ";

                    setColor(rarityColor);
                    cout << "|";
                    resetColor();
                }

                // SKILL 2
                else if(line == 8)
                {
                    setColor(rarityColor);
                    cout << "|";
                    resetColor();

                    cout << "S2  : ";

                    setColor(
                    getTypeColor(
                    monsters[i].skills[1].element));

                    cout << monsters[i].skills[1].nama;
                    resetColor();

                    int sisa =
                    14 -
                    monsters[i].skills[1].nama.length();

                    for(int j = 0; j < sisa; j++)
                        cout << " ";

                    setColor(rarityColor);
                    cout << "|";
                    resetColor();
                }

                // SKILL 3
                else if(line == 9)
                {
                    setColor(rarityColor);
                    cout << "|";
                    resetColor();

                    cout << "S3  : ";

                    setColor(getTypeColor(monsters[i].skills[2].element));

                    cout << monsters[i].skills[2].nama;
                    resetColor();

                    int sisa =
                    14 -
                    monsters[i].skills[2].nama.length();

                    for(int j = 0; j < sisa; j++)
                        cout << " ";

                    setColor(rarityColor);
                    cout << "|";
                    resetColor();
                }

                // TYPE
                else if(line == 10)
                {
                    setColor(rarityColor);
                    cout << "|";
                    resetColor();

                    cout << "TP  : ";

                    setColor(getTypeColor(monsters[i].type));
                    cout << monsters[i].type;
                    resetColor();

                    int sisa =
                    14 - monsters[i].type.length();

                    for(int j = 0; j < sisa; j++)
                        cout << " ";

                    setColor(rarityColor);
                    cout << "|";
                    resetColor();
                }

                // RARITY
                else if(line == 12)
                {
                    string rarity = monsters[i].rarity;

                    int padding = 20 - rarity.length();
                    int kiri = padding / 2;
                    int kanan = padding - kiri;

                    setColor(rarityColor);

                    cout << "|";

                    for(int j = 0; j < kiri; j++)
                        cout << " ";

                    cout << rarity;

                    for(int j = 0; j < kanan; j++)
                        cout << " ";

                    cout << "|";

                    resetColor();
                }

                // BORDER
                else
                {
                    setColor(rarityColor);
                    cout << kartu[line];
                    resetColor();
                }

                cout << " ";
            }

            cout << endl;
        }

        cout << endl;
    }
}

void gachaMonster(User users[], Monster monsters[], Skill skills[],
    int jumlah_monster, int jumlah_skill, int current_user, int jumlah_user)
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
    cout << "|                    Harga 1x Gacha : 100 Gold                  |\n";
    cout << "|_______________________________________________________________|\n";

    cout << "Gold Kamu : " << users[current_user].gold << "\n";
    cout << "pilih 0 untuk membatalkan gacha\n";
    try {
        jumlah_gacha = inputAngka("Masukkan jumlah gacha (1-10): ");
        validasiUserGacha(jumlah_gacha);
        if(jumlah_gacha == 0)
        {
            tampilPesan("Gacha dibatalkan!");
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
    }
    catch(const invalid_argument& e) {
        tampilPesan(e.what());
        return;
    }

    UserMonster hasil_gacha[10];

    for(int i = 0; i < jumlah_gacha; i++)
    {
        string rarity = getRandomRarity();
        int random_index = getMonsterByRarity(monsters, jumlah_monster, rarity);

        Monster m = monsters[random_index];
        UserMonster um;

        um.deck_id = users[current_user].next_deck_id;
        users[current_user].next_deck_id++;

        um.monster_id = m.status.id;
        um.nama = m.status.nama;
        um.hp = m.status.hp;
        um.attack = m.status.attack;
        um.defense = m.status.defense;
        um.speed = m.status.speed;
        um.type = m.type.tipe;
        um.rarity = m.rarity.rarity;
        randomSkillMonster(um, skills, jumlah_skill);
        hasil_gacha[i] = um;

        int deck_index =users[current_user].deck.jumlah;

        users[current_user].deck.monsters[deck_index] = um;
        users[current_user].deck.jumlah++;
        users[current_user].gold -= 100;
    }

    CLEAR_SCREEN;
    tampilMultiKartu(hasil_gacha, jumlah_gacha);
    cout << "Gold tersisa : " << users[current_user].gold << endl;

    saveUserCSV(users, jumlah_user);
    saveDeckCSV(users, jumlah_user);

    tunggu();
}