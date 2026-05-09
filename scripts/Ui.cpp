#include "global.h"

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


// AJIS











// ULUNG
