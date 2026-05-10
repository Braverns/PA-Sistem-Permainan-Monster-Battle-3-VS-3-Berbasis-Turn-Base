#include "global.h"

bool semuaMonsterMati(BattleMonster team[])
{
    for(int i = 0; i < 3; i++)
    {
        if(team[i].hidup)
            return false;
    }

    return true;
}

void tampilBattleTeam(BattleMonster team[], string judul)
{
    cout << "\n========== "
         << judul
         << " ==========\n";

    for(int i = 0; i < 3; i++)
    {
        cout << i + 1 << ". "
             << team[i].data.nama
             << " | HP: "
             << team[i].current_hp;

        if(!team[i].hidup)
        {
            cout << " [KO]";
        }

        cout << endl;
    }
}

void battleMenu(
    User users[],
    Monster monsters[],
    int jumlah_monster,
    int current_user,
    int jumlah_user
)
{
    // cek active team
    for(int i = 0; i < 3; i++)
    {
        if(users[current_user].active_team[i] == -1)
        {
            tampilPesan(
                "Silakan pilih active team terlebih dahulu!"
            );

            return;
        }
    }

    BattleMonster player[3];
    BattleMonster enemy[3];

    // setup player team
    for(int i = 0; i < 3; i++)
    {
        int idx =
        users[current_user].active_team[i];

        player[i].data =
        users[current_user].deck.monsters[idx];

        player[i].current_hp =
        player[i].data.hp;

        player[i].hidup = true;
    }

    // setup enemy team
    for(int i = 0; i < 3; i++)
    {
        int random_index =
        rand() % jumlah_monster;

        Monster m =
        monsters[random_index];

        enemy[i].data.monster_id =
        m.status.id;

        enemy[i].data.nama =
        m.status.nama;

        enemy[i].data.hp =
        m.status.hp;

        enemy[i].data.attack =
        m.status.attack;

        enemy[i].data.defense =
        m.status.defense;

        enemy[i].data.speed =
        m.status.speed;

        enemy[i].data.type =
        m.type.tipe;

        enemy[i].current_hp =
        enemy[i].data.hp;

        enemy[i].hidup = true;
    }

    // battle loop
    while(true)
    {
        CLEAR_SCREEN;

        tampilBattleTeam(player, "PLAYER TEAM");

        tampilBattleTeam(enemy, "ENEMY TEAM");

        // cek win lose
        if(semuaMonsterMati(enemy))
        {
            cout << "\nKAMU MENANG!\n";

            users[current_user].gold += 200;

            cout << "+200 Gold\n";

            saveUserCSV(users, jumlah_user);

            tungguEnter();

            return;
        }

        if(semuaMonsterMati(player))
        {
            cout << "\nKAMU KALAH!\n";

            users[current_user].gold += 50;

            cout << "+50 Gold\n";

            saveUserCSV(users, jumlah_user);

            tungguEnter();

            return;
        }

        TurnUnit turns[6];

        // PLAYER TURN UNIT
        for(int i = 0; i < 3; i++)
        {
            turns[i].player_side = true;
            turns[i].index = i;
            turns[i].speed =
            player[i].data.speed;
        }

        // ENEMY TURN UNIT
        for(int i = 0; i < 3; i++)
        {
            turns[i + 3].player_side = false;
            turns[i + 3].index = i;
            turns[i + 3].speed =
            enemy[i].data.speed;
        }

        // URUTKAN BERDASARKAN SPEED
        urutkanTurn(turns, 6);

        cout << "\nTURN ORDER\n";

        for(int i = 0; i < 6; i++)
        {
            if(turns[i].player_side)
            {
                cout << "[PLAYER] ";
                cout << player[turns[i].index]
                        .data.nama;
            }
            else
            {
                cout << "[ENEMY] ";
                cout << enemy[turns[i].index]
                        .data.nama;
            }

            cout << " (SPD: "
                << turns[i].speed
                << ")\n";
        }

        cout << endl;

        // SEMUA MONSTER MENDAPAT GILIRAN
        for(int i = 0; i < 6; i++)
        {
            // STOP kalau battle selesai
            if(semuaMonsterMati(enemy) ||
            semuaMonsterMati(player))
            {
                break;
            }

            // PLAYER SIDE
            if(turns[i].player_side)
            {
                int idx = turns[i].index;

                // skip kalau mati
                if(!player[idx].hidup)
                    continue;

                CLEAR_SCREEN;

                tampilBattleTeam(
                    player,
                    "PLAYER TEAM"
                );

                tampilBattleTeam(
                    enemy,
                    "ENEMY TEAM"
                );

                cout << "\nGiliran "
                    << player[idx].data.nama
                    << endl;

                playerAttack(
                    player,
                    enemy,
                    idx
                );
            }

            // ENEMY SIDE
            else
            {
                int idx = turns[i].index;

                // skip kalau mati
                if(!enemy[idx].hidup)
                    continue;

                CLEAR_SCREEN;

                tampilBattleTeam(
                    player,
                    "PLAYER TEAM"
                );

                tampilBattleTeam(
                    enemy,
                    "ENEMY TEAM"
                );

                cout << "\nGiliran Enemy "
                    << enemy[idx].data.nama
                    << endl;

                enemyAttack(
                    enemy,
                    player,
                    idx
                );
            }
        }

        tungguEnter();
    }
}

void urutkanTurn(
    TurnUnit turns[],
    int jumlah
)
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

            else if(turns[j].speed ==
                    turns[j+1].speed)
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

void playerAttack(
    BattleMonster player[],
    BattleMonster enemy[],
    int attacker
)
{
    int target;

    cout << "\nPilih target enemy: ";
    cin >> target;

    target--;

    if(target < 0 ||
       target >= 3 ||
       !enemy[target].hidup)
    {
        tampilPesan("Target tidak valid!");
        return;
    }

    int damage =
    player[attacker].data.attack
    -
    enemy[target].data.defense;

    if(damage < 1)
        damage = 1;

    enemy[target].current_hp -= damage;

    cout << "\n"
         << player[attacker].data.nama
         << " menyerang "
         << enemy[target].data.nama
         << " sebesar "
         << damage
         << " damage!\n";

    if(enemy[target].current_hp <= 0)
    {
        enemy[target].current_hp = 0;

        enemy[target].hidup = false;

        cout << enemy[target].data.nama
             << " KO!\n";
    }

    tungguEnter();
}

void enemyAttack(
    BattleMonster enemy[],
    BattleMonster player[],
    int attacker
)
{
    int target;

    do
    {
        target = rand() % 3;
    }
    while(!player[target].hidup);

    int damage =
    enemy[attacker].data.attack
    -
    player[target].data.defense;

    if(damage < 1)
        damage = 1;

    player[target].current_hp -= damage;

    cout << "\nEnemy "
         << enemy[attacker].data.nama
         << " menyerang "
         << player[target].data.nama
         << " sebesar "
         << damage
         << " damage!\n";

    if(player[target].current_hp <= 0)
    {
        player[target].current_hp = 0;

        player[target].hidup = false;

        cout << player[target].data.nama
             << " KO!\n";
    }

    tungguEnter();
}