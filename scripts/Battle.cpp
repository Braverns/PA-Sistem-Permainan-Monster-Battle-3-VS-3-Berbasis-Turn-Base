#include "global.h"

void battleMenu(User users[], Monster monsters[], Skill skills[], int jumlah_monster, int jumlah_skill, int current_user, int jumlah_user)
{
    stopBGM();
    playBGM(L"music/battle1.wav");

    for(int i = 0; i < 3; i++)
    {
        if(users[current_user].active_team[i] == -1)
        {
            tampilPesan("Silakan pilih active team terlebih dahulu!");
            stopBGM();
            playBGM(L"music/bgm1.wav");
            return;
        }
    }

    BattleMonster player[3];
    BattleMonster enemy[3];

    // PLAYER

    for(int i = 0; i < 3; i++)
    {
        int idx = users[current_user].active_team[i];
        player[i].data = users[current_user].deck.monsters[idx];
        player[i].current_hp = player[i].data.hp;
        player[i].hidup = true;
    }

    // ENEMY

    for(int i = 0; i < 3; i++)
    {
        int random_index = rand() % jumlah_monster;

        Monster m = monsters[random_index];
        enemy[i].data.monster_id = m.status.id;
        enemy[i].data.nama = m.status.nama;
        enemy[i].data.hp = m.status.hp;
        enemy[i].data.attack = m.status.attack;
        enemy[i].data.defense = m.status.defense;
        enemy[i].data.speed = m.status.speed;
        enemy[i].data.type = m.type.tipe;
        enemy[i].data.rarity = m.rarity.rarity;
        randomSkillMonster(enemy[i].data, skills, jumlah_skill);
        enemy[i].current_hp = enemy[i].data.hp;
        enemy[i].hidup = true;
    }

    while(true)
    {

        // CEK WIN
        if(semuaMonsterMati(enemy))
        {
            CLEAR_SCREEN;

            tampilBattleUI(player, enemy);

            cout << "\nKAMU MENANG!\n";
            users[current_user].gold += 200;
            cout << "+200 Gold\n";

            saveUserCSV(users, jumlah_user);

            stopBGM();
            playSFX(L"music/victory.wav");
            Sleep(3000);
            playBGM(L"music/bgm1.wav");

            tunggu();
            return;
        }

        // CEK LOSE
        if(semuaMonsterMati(player))
        {
            CLEAR_SCREEN;

            tampilBattleUI(player, enemy);
            cout << "\nKAMU KALAH!\n";
            users[current_user].gold += 50;
            cout << "+50 Gold\n";

            saveUserCSV(users, jumlah_user);

            stopBGM();
            playSFX(L"music/defeated.wav");
            Sleep(3000);
            playBGM(L"music/bgm1.wav");

            tunggu();
            return;
        }

        TurnUnit turns[6];

        for(int i = 0; i < 3; i++)
        {
            turns[i].player_side = true;
            turns[i].index = i;
            turns[i].speed = player[i].data.speed;
        }

        for(int i = 0; i < 3; i++)
        {
            turns[i + 3].player_side = false;
            turns[i + 3].index = i;
            turns[i + 3].speed = enemy[i].data.speed;
        }

        urutkanTurn(turns, 6);

        for(int i = 0; i < 6; i++)
        {
            if(semuaMonsterMati(enemy) || semuaMonsterMati(player))
            {
                break;
            }

            // PLAYER TURN
            if(turns[i].player_side)
            {
                int idx = turns[i].index;

                if(!player[idx].hidup)
                    continue;

                CLEAR_SCREEN;

                tampilBattleUI(player, enemy);
                cout << "\nCURRENT TURN : " << player[idx].data.nama << endl;

                bool flee = playerAttack(player, enemy, idx);

                if(flee)
                {
                    stopBGM();
                    playBGM(L"music/bgm1.wav");

                    tampilPesan2("Berhasil kabur!");
                    return;
                }
            }

            // ENEMY TURN
            else
            {
                int idx = turns[i].index;

                if(!enemy[idx].hidup)
                    continue;

                CLEAR_SCREEN;

                tampilBattleUI(player, enemy);
                cout << "\nCURRENT TURN : " << enemy[idx].data.nama << endl;

                enemyAttack(enemy, player, idx);
            }
        }
    }
}

void urutkanTurn(TurnUnit turns[], int jumlah)
{
    for(int i = 0; i < jumlah - 1; i++)
    {
        for(int j = 0; j < jumlah - i - 1; j++)
        {
            bool tukar = false;

            if(turns[j].speed < turns[j+1].speed)
            {
                tukar = true;
            }

            else if(turns[j].speed == turns[j+1].speed)
            {
                if(rand() % 2 == 0)
                {
                    tukar = true;
                }
            }

            if(tukar)
            {
                TurnUnit temp = turns[j];
                turns[j] = turns[j+1];
                turns[j+1] = temp;
            }
        }
    }
}

bool semuaMonsterMati(BattleMonster team[])
{
    for(int i = 0; i < 3; i++)
    {
        if(team[i].hidup)
            return false;
    }

    return true;
}

void tampilBattleUI(BattleMonster player[], BattleMonster enemy[])
{
    // ===== ENEMY SECTION (BORDER MERAH) =====
    setColor(12);
    cout << "\n _________________________________________________________________\n";
    cout << "|                              ENEMY                              |\n";
    cout << "|_________________________________________________________________|\n";
    resetColor();

    // Baris nama enemy
    for(int i = 0; i < 3; i++)
    {
        setColor(12); cout << "|"; resetColor();
        cout << left << setw(21) << enemy[i].data.nama;
    }
    setColor(12); cout << "|\n"; resetColor();

    // Separator atas enemy
    for(int i = 0; i < 3; i++)
    {
        setColor(12); cout << "|_____________________"; resetColor();
    }
    setColor(12); cout << "|\n"; resetColor();

    // Baris stat enemy
    for(int row = 0; row < 5; row++)
    {
        for(int i = 0; i < 3; i++)
        {
            UserMonster m = enemy[i].data;

            // Border kiri
            setColor(12); cout << "|"; resetColor();

            switch(row)
            {
                case 0: // HP
                    cout << "HP  : ";
                    if(enemy[i].hidup)
                    {
                        setColor(10); // Hijau untuk nilai HP
                        cout << left << setw(15) << enemy[i].current_hp;
                    }
                    else
                    {
                        setColor(8); // Abu gelap untuk KO
                        cout << left << setw(15) << "KO";
                    }
                    resetColor();
                    break;

                case 1: // ATK
                    cout << "ATK : ";
                    setColor(12); // Merah untuk nilai Attack
                    cout << left << setw(15) << m.attack;
                    resetColor();
                    break;

                case 2: // DEF
                    cout << "DEF : ";
                    setColor(14); // Kuning untuk nilai Defense
                    cout << left << setw(15) << m.defense;
                    resetColor();
                    break;

                case 3: // SPD
                    cout << "SPD : ";
                    setColor(11); // Cyan untuk nilai Speed
                    cout << left << setw(15) << m.speed;
                    resetColor();
                    break;

                case 4: // TYPE
                    cout << "TP  : ";
                    setColor(getTypeColor(m.type)); // Warna sesuai tipe
                    cout << left << setw(15) << m.type;
                    resetColor();
                    break;
            }
        }
        setColor(12); cout << "|\n"; resetColor();
    }

    // Separator bawah enemy
    for(int i = 0; i < 3; i++)
    {
        setColor(12); cout << "|_____________________"; resetColor();
    }
    setColor(12); cout << "|\n"; resetColor();

    // ===== PLAYER SECTION (BORDER HIJAU) =====

    // Separator atas player
    for(int i = 0; i < 3; i++)
    {
        setColor(10); cout << "|_____________________"; resetColor();
    }
    setColor(10); cout << "|\n"; resetColor();

    // Baris stat player
    for(int row = 0; row < 5; row++)
    {
        for(int i = 0; i < 3; i++)
        {
            UserMonster m = player[i].data;

            // Border kiri
            setColor(10); cout << "|"; resetColor();

            switch(row)
            {
                case 0: // HP
                    cout << "HP  : ";
                    if(player[i].hidup)
                    {
                        setColor(10); // Hijau untuk nilai HP
                        cout << left << setw(15) << player[i].current_hp;
                    }
                    else
                    {
                        setColor(8); // Abu gelap untuk KO
                        cout << left << setw(15) << "KO";
                    }
                    resetColor();
                    break;

                case 1: // ATK
                    cout << "ATK : ";
                    setColor(12); // Merah untuk nilai Attack
                    cout << left << setw(15) << m.attack;
                    resetColor();
                    break;

                case 2: // DEF
                    cout << "DEF : ";
                    setColor(14); // Kuning untuk nilai Defense
                    cout << left << setw(15) << m.defense;
                    resetColor();
                    break;

                case 3: // SPD
                    cout << "SPD : ";
                    setColor(11); // Cyan untuk nilai Speed
                    cout << left << setw(15) << m.speed;
                    resetColor();
                    break;

                case 4: // TYPE
                    cout << "TP  : ";
                    setColor(getTypeColor(m.type)); // Warna sesuai tipe
                    cout << left << setw(15) << m.type;
                    resetColor();
                    break;
            }
        }
        setColor(10); cout << "|\n"; resetColor();
    }

    // Separator bawah player
    for(int i = 0; i < 3; i++)
    {
        setColor(10); cout << "|_____________________"; resetColor();
    }
    setColor(10); cout << "|\n"; resetColor();

    // Baris nama player
    for(int i = 0; i < 3; i++)
    {
        setColor(10); cout << "|"; resetColor();
        cout << left << setw(21) << player[i].data.nama;
    }
    setColor(10); cout << "|\n"; resetColor();

    setColor(10);
    cout << "|_____________________|_____________________|_____________________|\n";
    cout << "|                              PLAYER                             |\n";
    cout << "|_________________________________________________________________|\n";
    resetColor();
}


int pilihTarget(BattleMonster player[], BattleMonster enemy[], string attacker_name)
{
    int cursor = 0;

    while(true)
    {
        CLEAR_SCREEN;

        tampilBattleUI(player, enemy);

        cout << "\n ___________________________________\n";

        string teks = attacker_name + " MENYERANG";
        int width = 35;
        int padding = width - teks.length();

        if(padding < 0)
            padding = 0;

        int kiri = padding / 2;
        int kanan = padding - kiri;

        cout << "|";

        for(int i = 0; i < kiri; i++)
            cout << " ";

        cout << teks;

        for(int i = 0; i < kanan; i++)
            cout << " ";

        cout << "|\n";
        cout << "|___________________________________|\n";

        for(int i = 0; i < 3; i++)
        {
            cout << "| ";

            if(cursor == i)
            {
                setColor(15);
                cout << ">> ";
                cout << left << setw(30) << enemy[i].data.nama;
                resetColor();
            }
            else
            {
                cout << "   ";
                cout << left << setw(30) << enemy[i].data.nama;
            }

            cout << " |\n";
        }

        cout << "|___________________________________|\n";

        cout << "\n ________________________\n";
        cout << "|      CONTROL MENU      |\n";
        cout << "|                        |\n";
        cout << "| [ENTER] PILIH TARGET   |\n";
        cout << "| [ESC]   FLEE           |\n";
        cout << "|________________________|\n";

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
                    cursor = 2;
            }

            // DOWN
            else if(tombol == 80)
            {
                cursor++;

                if(cursor > 2)
                    cursor = 0;
            }
        }

        // ENTER
        else if(tombol == 13)
        {
            if(enemy[cursor].hidup)
            {
                return cursor;
            }
        }

        // ESC
        else if(tombol == 27)
        {
            return -1;
        }
    }
}

int pilihSkill(BattleMonster player[], BattleMonster enemy[], UserMonster monster)
{
    int cursor = 0;

    while(true)
    {
        CLEAR_SCREEN;

        tampilBattleUI(player, enemy);

        string teks = monster.nama + " MENGGUNAKAN SKILL";

        int width = 70;
        int padding = width - teks.length();

        if(padding < 0)
            padding = 0;

        int kiri = padding / 2;
        int kanan = padding - kiri;

        cout << "\n ______________________________________________________________________\n";
        cout << "|";

        for(int i = 0; i < kiri; i++)
            cout << " ";

        cout << teks;

        for(int i = 0; i < kanan; i++)
            cout << " ";

        cout << "|\n";

        cout << "|______________________________________________________________________|\n";
        cout << "|    | NAME                 | ELEMENT     | TIPE        | POWER        |\n";
        cout << "|____|______________________|_____________|_____________|______________|\n";

        for(int i = 0; i < 3; i++)
        {
            Skill s = monster.skills[i];

            cout << "| ";

            // Cursor: putih jika dipilih
            if(cursor == i)
            {
                setColor(15);
                cout << ">>";
                resetColor();
            }
            else
            {
                cout << "  ";
            }

            cout << " | ";

            // Nama skill: putih jika dipilih, default jika tidak
            if(cursor == i) setColor(15);
            cout << left << setw(21) << s.nama;
            resetColor();

            cout << "| ";

            // Element: warna sesuai tipe elemen
            setColor(getTypeColor(s.element));
            cout << left << setw(12) << s.element;
            resetColor();

            cout << "| ";

            // Tipe skill: Damage=merah, Heal=hijau, AOE=kuning
            if(s.tipe == "Damage")      setColor(12);
            else if(s.tipe == "Heal")   setColor(10);
            else if(s.tipe == "AOE")    setColor(14);
            cout << left << setw(12) << s.tipe;
            resetColor();

            cout << "| ";

            // Power: cyan
            setColor(11);
            cout << left << setw(13) << s.power;
            resetColor();

            cout << "|\n";
            cout << "|____|______________________|_____________|_____________|______________|\n";
        }

        cout << "\n ___________________________\n";
        cout << "|       CONTROL MENU        |\n";
        cout << "|                           |\n";
        cout << "| [UP/DOWN] MOVE CURSOR     |\n";
        cout << "| [ENTER]   SELECT SKILL    |\n";
        cout << "| [ESC]     KEMBALI         |\n";
        cout << "|___________________________|\n";

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
                    cursor = 2;
            }

            // DOWN
            else if(tombol == 80)
            {
                cursor++;

                if(cursor > 2)
                    cursor = 0;
            }
        }

        // ENTER
        else if(tombol == 13)
        {
            return cursor;
        }

        // ESC
        else if(tombol == 27)
        {
            return -1;
        }
    }
}

float getTypeMultiplier(string attack_type, string target_type)
{
    if(attack_type == "Fire" && target_type == "Earth")
    {
        return 1.5f;
    }

    if(attack_type == "Water" && target_type == "Fire")
    {
        return 1.5f;
    }

    if(attack_type == "Earth" && target_type == "Rock")
    {
        return 1.5f;
    }

    // WIND > EARTH
    if(attack_type == "Wind" && target_type == "Earth")
    {
        return 1.5f;
    }

    // ROCK > WIND
    if(attack_type == "Rock" && target_type == "Wind")
    {
        return 1.5f;
    }

    return 1.0f;
}

int hitungDamage(UserMonster attacker, UserMonster target, Skill skill)
{
    int damage = (attacker.attack + skill.power) - target.defense;

    float multiplier = getTypeMultiplier(skill.element, target.type);

    damage = damage * multiplier;

    if(damage < 1)
    {
        damage = 1;
    }

    return damage;
}

void printBattleTextLine(string text)
{
    int width = 63;

    int padding = width - text.length();

    if(padding < 0)
        padding = 0;

    int kiri = padding / 2;
    int kanan = padding - kiri;

    cout << "|";

    for(int i = 0; i < kiri; i++)
        cout << " ";

    cout << text;

    for(int i = 0; i < kanan; i++)
        cout << " ";

    cout << "|\n";
}


bool playerAttack(BattleMonster player[], BattleMonster enemy[], int attacker)
{
    while(true)
    {
        // PILIH SKILL
        int skill_index =
        pilihSkill(
            player,
            enemy,
            player[attacker].data
        );

        // ESC = kembali
        if(skill_index == -1)
        {
            continue;
        }

        Skill skill =
        player[attacker].data.skills[skill_index];


        // HEAL
        if(skill.tipe == "Heal")
        {
            int heal_target =
            pilihTargetHeal(
                player,
                enemy,
                player[attacker].data.nama
            );

            // ESC = kembali pilih skill
            if(heal_target == -1)
            {
                continue;
            }

            player[heal_target].current_hp += skill.power;

            // LIMIT MAX HP
            if(player[heal_target].current_hp >
               player[heal_target].data.hp)
            {
                player[heal_target].current_hp =
                player[heal_target].data.hp;
            }

            CLEAR_SCREEN;

            tampilBattleUI(player, enemy);

            // ===== NOTIF HEAL (HIJAU) =====
            setColor(10);
            cout << "\n _______________________________________________________________\n";

            string teks =
            player[attacker].data.nama +
            " HEAL " +
            player[heal_target].data.nama;

            printBattleTextLine(teks);

            printBattleTextLine("");

            string heal =
            "+" + to_string(skill.power) + " HP";

            printBattleTextLine(heal);

            cout << "|_______________________________________________________________|\n";
            resetColor();

            Sleep(2500);

            return false;
        }


        // AREA OF EFFECT
        else if(skill.tipe == "AOE")
        {
            CLEAR_SCREEN;

            tampilBattleUI(player, enemy);

            // ===== NOTIF AOE (MERAH) =====
            setColor(12);
            cout << "\n _______________________________________________________________\n";

            string teks =
            player[attacker].data.nama +
            " MENGGUNAKAN " +
            skill.nama;

            printBattleTextLine(teks);

            printBattleTextLine("");

            for(int i = 0; i < 3; i++)
            {
                if(enemy[i].hidup)
                {
                    int damage =
                    hitungDamage(
                        player[attacker].data,
                        enemy[i].data,
                        skill
                    );

                    enemy[i].current_hp -= damage;

                    if(enemy[i].current_hp <= 0)
                    {
                        enemy[i].current_hp = 0;
                        enemy[i].hidup = false;
                    }

                    string dmg =
                    enemy[i].data.nama +
                    " -" +
                    to_string(damage) +
                    " HP";

                    printBattleTextLine(dmg);
                }
            }

            cout << "|_______________________________________________________________|\n";
            resetColor();

            Sleep(3000);

            return false;
        }


        // DAMAGE SINGLE TARGET
        else
        {
            int target =
            pilihTarget(
                player,
                enemy,
                player[attacker].data.nama
            );

            // ESC = flee
            if(target == -1)
            {
                CLEAR_SCREEN;

                tampilBattleUI(player, enemy);

                cout << "\nMencoba kabur...\n";

                Sleep(1500);

                int flee = rand() % 100;

                if(flee < 5)
                {
                    cout << "\nBERHASIL KABUR!\n";

                    Sleep(2000);

                    return true;
                }
                else
                {
                    cout << "\nGAGAL KABUR!\n";

                    Sleep(2000);

                    return false;
                }
            }

            int damage =
            hitungDamage(
                player[attacker].data,
                enemy[target].data,
                skill
            );

            enemy[target].current_hp -= damage;

            if(enemy[target].current_hp <= 0)
            {
                enemy[target].current_hp = 0;
                enemy[target].hidup = false;
            }

            float multiplier =
            getTypeMultiplier(
                skill.element,
                enemy[target].data.type
            );

            CLEAR_SCREEN;

            tampilBattleUI(player, enemy);

            // ===== NOTIF DAMAGE SINGLE (MERAH) =====
            setColor(12);
            cout << "\n _______________________________________________________________\n";

            string teks =
            player[attacker].data.nama +
            " MENYERANG " +
            enemy[target].data.nama;

            printBattleTextLine(teks);

            printBattleTextLine("");

            if(multiplier > 1.0f)
            {
                printBattleTextLine("SUPER EFEKTIF");
            }
            else
            {
                printBattleTextLine("");
            }

            string dmg =
            to_string(damage) + " DAMAGE";

            printBattleTextLine(dmg);

            cout << "|_______________________________________________________________|\n";
            resetColor();

            if(!enemy[target].hidup)
            {
                cout << "\n"
                     << enemy[target].data.nama
                     << " KO!\n";
            }

            Sleep(2500);

            return false;
        }
    }
}


void enemyAttack(BattleMonster enemy[], BattleMonster player[], int attacker)
{
    int random_skill = rand() % 3;

    Skill skill = enemy[attacker].data.skills[random_skill];

    // HEAL
    if(skill.tipe == "Heal")
    {
        int heal_target;

        // cari target hidup random
        do
        {
            heal_target = rand() % 3;
        }
        while(!enemy[heal_target].hidup);

        enemy[heal_target].current_hp += skill.power;

        // LIMIT MAX HP
        if(enemy[heal_target].current_hp >
           enemy[heal_target].data.hp)
        {
            enemy[heal_target].current_hp =
            enemy[heal_target].data.hp;
        }

        CLEAR_SCREEN;

        tampilBattleUI(player, enemy);
        setColor(10);

        cout << "\n _______________________________________________________________\n";

        string teks = enemy[attacker].data.nama + " MENGGUNAKAN " + skill.nama;

        printBattleTextLine(teks);
        printBattleTextLine("");

        string heal = enemy[heal_target].data.nama + " +" + to_string(skill.power) + " HP";
        printBattleTextLine(heal);

        cout << "|_______________________________________________________________|\n";

        resetColor();
        Sleep(2500);

        return;
    }

    // AREA OF EFFECT
    else if(skill.tipe == "AOE")
    {
        CLEAR_SCREEN;

        tampilBattleUI(player, enemy);
        setColor(12);

        cout << "\n _______________________________________________________________\n";

        string teks = enemy[attacker].data.nama + " MENGGUNAKAN " + skill.nama;

        printBattleTextLine(teks);
        printBattleTextLine("");

        for(int i = 0; i < 3; i++)
        {
            if(player[i].hidup)
            {
                int damage = hitungDamage(enemy[attacker].data, player[i].data, skill);

                player[i].current_hp -= damage;

                if(player[i].current_hp <= 0)
                {
                    player[i].current_hp = 0;
                    player[i].hidup = false;
                }

                string dmg = player[i].data.nama + " -" + to_string(damage) + " HP";

                printBattleTextLine(dmg);
            }
        }

        cout << "|_______________________________________________________________|\n";

        resetColor();
        Sleep(3000);

        return;
    }

    // DAMAGE SINGLE TARGET
    int target;

    do
    {
        target = rand() % 3;
    }
    while(!player[target].hidup);

    int damage = hitungDamage(enemy[attacker].data, player[target].data, skill);

    player[target].current_hp -= damage;

    if(player[target].current_hp <= 0)
    {
        player[target].current_hp = 0;
        player[target].hidup = false;
    }

    float multiplier = getTypeMultiplier(skill.element, player[target].data.type);

    CLEAR_SCREEN;

    tampilBattleUI(player, enemy);
    setColor(12);

    cout << "\n _______________________________________________________________\n";

    string teks = enemy[attacker].data.nama + " MENYERANG " + player[target].data.nama;

    printBattleTextLine(teks);
    printBattleTextLine("");

    if(multiplier > 1.0f)
    {
        printBattleTextLine("SUPER EFEKTIF");
    }
    else
    {
        printBattleTextLine("");
    }

    string dmg = to_string(damage) + " DAMAGE";

    printBattleTextLine(dmg);

    cout << "|_______________________________________________________________|\n";

    resetColor();

    if(!player[target].hidup)
    {
        cout << "\n"
             << player[target].data.nama
             << " KO!\n";
    }

    Sleep(3000);
}

int pilihTargetHeal(BattleMonster player[], BattleMonster enemy[], string healer_name)
{
    int cursor = 0;

    while(true)
    {
        CLEAR_SCREEN;

        tampilBattleUI(player, enemy);

        cout << "\n ___________________________________\n";

        string teks = healer_name + " HEAL TARGET";

        int width = 35;
        int padding = width - teks.length();

        if(padding < 0)
            padding = 0;

        int kiri = padding / 2;
        int kanan = padding - kiri;

        cout << "|";

        for(int i = 0; i < kiri; i++)
            cout << " ";

        cout << teks;

        for(int i = 0; i < kanan; i++)
            cout << " ";

        cout << "|\n";

        cout << "|___________________________________|\n";

        for(int i = 0; i < 3; i++)
        {
            cout << "| ";

            if(cursor == i)
            {
                setColor(15);
                cout << ">> ";
                cout << left << setw(30) << player[i].data.nama;
                resetColor();
            }
            else
            {
                cout << "   ";
                cout << left << setw(30) << player[i].data.nama;
            }

            cout << " |\n";
        }

        cout << "|___________________________________|\n";

        cout << "\n ___________________________\n";
        cout << "|       CONTROL MENU        |\n";
        cout << "|                           |\n";
        cout << "| [UP/DOWN] MOVE CURSOR     |\n";
        cout << "| [ENTER]   PILIH TARGET    |\n";
        cout << "| [ESC]     KEMBALI         |\n";
        cout << "|___________________________|\n";

        char tombol = _getch();

        if(tombol == -32)
        {
            tombol = _getch();

            // UP
            if(tombol == 72)
            {
                cursor--;

                if(cursor < 0)
                    cursor = 2;
            }

            // DOWN
            else if(tombol == 80)
            {
                cursor++;

                if(cursor > 2)
                    cursor = 0;
            }
        }

        // ENTER
        else if(tombol == 13)
        {
            if(player[cursor].hidup)
            {
                return cursor;
            }
        }

        // ESC
        else if(tombol == 27)
        {
            return -1;
        }
    }
}