
#include <cstring>
#include <string>
using namespace std;
#include "Rank.h"

void cargarCadena(char* pal, int tam) {
    int i;
    fflush(stdin);
    for (i = 0; i < tam; i++)
    {
        pal[i] = cin.get();
        if (pal[i] == '\n') break;
    }
    pal[i] = '\0';
    fflush(stdin);
}

Rank::Rank() {
    
}

bool Rank::grabarPlayer(Rank& obj) {
    FILE* pRank;
    pRank = fopen("Ranking.dat", "ab");
    if (pRank == NULL) {
        cout << "NO SE ABRIO" << endl;
        return false;
    }

    bool escribio = fwrite(&obj, sizeof(Rank), 1, pRank);
    fclose(pRank);

    return escribio;
}

void Rank::cargarPlayer() {
    cout << "INGRESE SU NOMBRE " << endl;
    cargarCadena(nombrePlayer, 29);
    grabarPlayer(*this);
}

Rank Rank::leerPlayer(int pos) {
    Rank obj;
    FILE* pRank;
    pRank = fopen("Ranking.dat", "rb");
    if (pRank == NULL) {
        cout << "NO SE ABRIO" << endl;
        return obj;
    }
    fseek(pRank, pos * sizeof obj, SEEK_SET);
    fread(&obj, sizeof obj, 1, pRank);
    fclose(pRank);
    return obj;
}

int Rank::contarRegistros() {
    FILE* pRank;
    pRank = fopen("Ranking.dat", "rb");
    if (pRank == NULL) {
        cout << "NO SE ABRIO" << endl;
        return -1;
    }
    fseek(pRank, 0, SEEK_END);
    int tam = ftell(pRank);
    fclose(pRank);
    return tam / sizeof(Rank);
}

void Rank::mostrarRanking() {
    Rank obj;
    FILE* pRank;
    
    pRank = fopen("Ranking.dat", "rb");
        if (pRank == NULL) {
            cout << "NO SE ABRIO" << endl;
            return;
      }
 
    int cant = obj.contarRegistros();
    for (int i = 0; i < cant; i++) {

        fread(&obj, sizeof obj, 1, pRank);
        cout << obj.nombrePlayer << " " << obj.puntajePlayer << " " << obj.intentos << endl;
    }
    fclose(pRank);
}