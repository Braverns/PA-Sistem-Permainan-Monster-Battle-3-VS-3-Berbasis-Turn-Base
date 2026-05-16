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

            tungguEnter();
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

            tungguEnter();
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

                    tampilPesan("Berhasil kabur!");
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
    cout << "\n _________________________________________________________________\n";
    cout << "|                              ENEMY                              |\n";
    cout << "|_________________________________________________________________|\n";

    for(int i = 0; i < 3; i++)
    {
        cout << "|" << left << setw(21) << enemy[i].data.nama;
    }

    cout << "|\n";

    for(int i = 0; i < 3; i++)
    {
        cout << "|_____________________";
    }

    cout << "|\n";

    for(int row = 0; row < 5; row++)
    {
        for(int i = 0; i < 3; i++)
        {
            UserMonster m = enemy[i].data;
            cout << "|";
            switch(row)
            {
                case 0:

                    if(enemy[i].hidup)
                    {
                        cout << left << setw(21) << ("HP  : " + to_string(enemy[i].current_hp));
                    }
                    else
                    {
                        cout << left << setw(21) << "HP  : KO";
                    }

                    break;

                case 1:

                    cout << left<< setw(21) << ("ATK : " + to_string(m.attack));
                    break;

                case 2:

                    cout << left << setw(21) << ("DEF : " + to_string(m.defense));
                    break;

                case 3:

                    cout << left << setw(21) << ("SPD : " + to_string(m.speed));

                    break;

                case 4:

                    cout << left << setw(21) << ("TP  : " + m.type);

                    break;
            }
        }

        cout << "|\n";
    }

    for(int i = 0; i < 3; i++)
    {
        cout << "|_____________________";
    }

    cout << "|\n";

    for(int row = 0; row < 5; row++)
    {
        for(int i = 0; i < 3; i++)
        {
            UserMonster m = player[i].data;
            cout << "|";

            switch(row)
            {
                case 0:
// rapikan
                    if(player[i].hidup)
                    {
                        cout << left << setw(21) << ("HP  : " + to_string(player[i].current_hp));
                    }
                    else
                    {
                        cout << left << setw(21) << "HP  : KO";
                    }

                    break;

                case 1:

                    cout << left << setw(21) << ("ATK : " + to_string(m.attack));
                    break;

                case 2:

                    cout << left << setw(21) << ("DEF : " + to_string(m.defense));
                    break;

                case 3:

                    cout << left << setw(21) << ("SPD : " + to_string(m.speed));
                    break;

                case 4:

                    cout << left << setw(21) << ("TP  : " + m.type);
                    break;
            }
        }

        cout << "|\n";
    }

    for(int i = 0; i < 3; i++)
    {
        cout << "|_____________________";
    }

    cout << "|\n";

    for(int i = 0; i < 3; i++)
    {
        cout << "|" << left << setw(21) << player[i].data.nama;
    }

    cout << "|\n";
    cout << "|_____________________|_____________________|_____________________|\n";
    cout << "|                              PLAYER                             |\n";
    cout << "|_________________________________________________________________|\n";
}



int pilihTarget( BattleMonster player[], BattleMonster enemy[], string attacker_name)
{
    int cursor = 0;

    while(true)
    {
        CLEAR_SCREEN;

        tampilBattleUI(player, enemy);

        cout << "\n ___________________________________\n";
        cout << "| ";
        cout << left << setw(33) << (attacker_name + " MENYERANG");
        cout << "|\n";
        cout << "|___________________________________|\n";

        for(int i = 0; i < 3; i++)
        {
            cout << "| ";

            if(cursor == i)
                cout << ">> ";
            else
                cout << "   ";

            cout << left << setw(30) << enemy[i].data.nama;
            cout << "|\n";
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

        cout << "\n _________________________________________________\n";
        cout << "|                     SKILL                       |\n";
        cout << "|_________________________________________________|\n";
        cout << "| NAME           | ELEMENT | TIPE   | POWER      |\n";
        cout << "|________________|_________|_________|____________|\n";

        for(int i = 0; i < 3; i++)
        {
            Skill s = monster.skills[i];

            cout << "| ";

            if(cursor == i)
                cout << ">> ";
            else
                cout << "   ";

            cout << left
            << setw(13)
            << s.nama

            << "| "
            << setw(8)
            << s.element

            << "| "
            << setw(8)
            << s.tipe

            << "| "
            << setw(10)
            << s.power

            << "|\n";
        }

        cout << "|_________________________________________________|\n";

        cout << "\n ________________________\n";
        cout << "|      CONTROL MENU      |\n";
        cout << "|                        |\n";
        cout << "| [ENTER] SELECT SKILL   |\n";
        cout << "| [ESC]   KEMBALI        |\n";
        cout << "|________________________|\n";

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
    int damage =(attacker.attack + skill.power) - target.defense;

    float multiplier = getTypeMultiplier( skill.element, target.type);

    damage = damage * multiplier;

    if(damage < 1)
    {
        damage = 1;
    }

    return damage;
}

bool playerAttack(BattleMonster player[], BattleMonster enemy[], int attacker)
{
    while(true)
    {
        // PILIH TARGET

        int target = pilihTarget( player, enemy, player[attacker].data.nama);

        // FLEE
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

        // PILIH SKILL

        int skill_index = pilihSkill(player, enemy, player[attacker].data);

        // ESC = kembali target
        if(skill_index == -1)
        {
            continue;
        }

        Skill skill = player[attacker].data.skills[skill_index];

        int damage = hitungDamage(player[attacker].data, enemy[target].data, skill);
        enemy[target].current_hp -= damage;

        if(enemy[target].current_hp <= 0)
        {
            enemy[target].current_hp = 0;
            enemy[target].hidup = false;
        }

        float multiplier = getTypeMultiplier(skill.element, enemy[target].data.type);

        CLEAR_SCREEN;

        tampilBattleUI(player, enemy);

        cout << "\n _______________________________________________________________\n";
        cout << "| ";
        string teks = player[attacker].data.nama + " MENYERANG " +enemy[target].data.nama;
        cout << left << setw(61) << teks;
        cout << "|\n";
        cout << "|                                                               |\n";

        if(multiplier > 1.0f)
        {
            cout << "|                     SUPER EFEKTIF                             |\n";
        }
        else
        {
            cout << "|                                                               |\n";
        }

        string dmg = to_string(damage) + " DAMAGE";
        cout << "|";
        cout << setw(35) << " ";
        cout << left << setw(28) << dmg;
        cout << "|\n";
        cout << "|_______________________________________________________________|\n";

        if(!enemy[target].hidup)
        {
            cout << "\n" << enemy[target].data.nama << " KO!\n";
        }

        Sleep(2500);
        return false;
    }
}


void enemyAttack(BattleMonster enemy[], BattleMonster player[], int attacker)
{
    int target;

    // RANDOM TARGET
    do
    {
        target = rand() % 3;
    }
    while(!player[target].hidup);

    int random_skill = rand() % 3;
    Skill skill = enemy[attacker].data.skills[random_skill];
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

    cout << "\n _______________________________________________________________\n";
    cout << "| ";
    string teks = enemy[attacker].data.nama + " MENYERANG " + player[target].data.nama;
    cout << left << setw(61)<< teks;
    cout << "|\n";
    cout << "|                                                               |\n";

    if(multiplier > 1.0f)
    {
        cout << "|                     SUPER EFEKTIF                             |\n";
    }
    else
    {
        cout << "|                                                               |\n";
    }

    string dmg = to_string(damage) + " DAMAGE";
    cout << "|";
    cout << setw(35) << " ";
    cout << left << setw(28) << dmg;
    cout << "|\n";
    cout << "|_______________________________________________________________|\n";

    if(!player[target].hidup)
    {
        cout << "\n" << player[target].data.nama << " KO!\n";
    }

    Sleep(3000);
}

