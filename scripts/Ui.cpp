#include "global.h"
#include <windows.h>

void menuTidakValid()
{
    CLEAR_SCREEN;
    cout << "Pilihan tidak valid!\n";
    
    cout << "\nTekan ENTER untuk kembali...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void tampilPesan(string pesan)
{
    CLEAR_SCREEN;

    int panjangPesan = pesan.length();

    int lebarBox = panjangPesan + 10;

    if(lebarBox < 40)
        lebarBox = 40;

    cout << "\n ";


    for(int i = 2; i < lebarBox; i++)
    {
        cout << "_";
    }

    cout << endl;


    cout << "|";

    for(int i = 0; i < lebarBox - 2; i++)
    {
        cout << " ";
    }

    cout << "|\n";

    int sisa = lebarBox - 2 - panjangPesan;

    int kiri = sisa / 2;
    int kanan = sisa - kiri;

    cout << "|";

    for(int i = 0; i < kiri; i++)
        cout << " ";

    cout << pesan;

    for(int i = 0; i < kanan; i++)
        cout << " ";

    cout << "|\n";

    cout << "|";

    for(int i = 0; i < lebarBox - 2; i++)
    {
        cout << " ";
    }

    cout << "|\n";

    cout << "|";

    for(int i = 0; i < lebarBox - 2; i++)
        cout << "_";

    cout << "|\n";
    
    tungguEnter();
}

void logout(int &state)
{
    CLEAR_SCREEN;
    cout << " _____________________________________________\n";
    cout << "|                                             |\n";
    cout << "|               Logout Berhasil               |\n";
    cout << "|                                             |\n";
    cout << "|_____________________________________________|\n";
    state = 0;

    tungguEnter();
}

void tungguEnter()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nTekan ENTER untuk kemballi...";
    cin.get();
}

void tunggu()
{
    cout << "\nTekan ENTER untuk kemballi...";
    cin.get();
}
void tungguClear()
{
    cin.clear();
    cout << "\nTekan ENTER untuk kemballi...";
    cin.get();
}   

void gotoXY(int x, int y)
{
    COORD coord;

    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearArea()
{
    gotoXY(0,0);

    for(int i = 0; i < 50; i++)
    {
        cout << string(120, ' ') << endl;
    }

    gotoXY(0,0);
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetColor()
{
    setColor(7);
}

int getRarityColor(string rarity)
{
    if(rarity == "Common")
        return 7;

    if(rarity == "Rare")
        return 9;

    if(rarity == "Epic")
        return 5;

    if(rarity == "Legendary")
        return 14;

    return 7;
}

void menuSetting()
{
    while(true)
    {
        CLEAR_SCREEN;

        cout << "\n __________________________________\n";
        cout << "|            SETTING              |\n";
        cout << "|_________________________________|\n";
        cout << "| 1 | Volume Audio                |\n";
        cout << "| 0 | Kembali                     |\n";
        cout << "|___|_____________________________|\n";

        cout << "\nPilih: ";

        int pilih;
        cin >> pilih;

        if(cin.fail())
        {
            tampilPesan("Input tidak valid!");
            return;
        }

        switch(pilih)
        {
            case 1:
            {
                int volume;

                cout << "\nVolume (0-100): ";
                cin >> volume;

                setVolume(volume);

                tampilPesan("Volume berhasil diubah!");

                break;
            }

            case 0:
                return;

            default:
                tampilPesan("Menu tidak valid!");
        }
    }
}


// AJIS











// ULUNG
