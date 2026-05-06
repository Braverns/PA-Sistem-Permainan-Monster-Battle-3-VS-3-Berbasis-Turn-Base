#include "global.h"

void menuTidakValid()
{
    cout << "Pilihan tidak valid!\n";

    cout << "\nTekan ENTER untuk kembali...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void logout(int &state)
{
    cout << "Logout berhasil\n";
    state = 0;

    cout << "\nTekan ENTER untuk kembali...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}




// AJIS











// ULUNG
