#include <iostream>
#include <vector>
using namespace std;



typedef vector <char> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMatrix; // un type représentant la grille

typedef struct {
    unsigned m_X;
    unsigned m_Y;
} SPlayer;


const char KTokenPlayer = 'O';
const char nourriture = '*';
const char obstacle = '#';
SPlayer FirstPlayer;
void ClearScreen ()
{
    cout << "\033[H\033[2J";
}


const string KReset   ("0");
const string KNoir    ("30");
const string KRouge   ("31");
const string KVert    ("32");
const string KJaune   ("33");
const string KBleu    ("34");
const string KMAgenta ("35");
const string KCyan    ("36");



void Couleur (const string & coul)
{
    cout << "\033[" << coul <<"m";
}





void  ShowMatrix (const CMatrix & Mat)
{



    ClearScreen();
    Couleur(KReset);
    for (unsigned i(0); i < Mat.size(); ++i)
    {

        for (unsigned j(0); j < Mat[i].size(); ++j)
        {
            if(Mat [i][j] == KTokenPlayer)
                Couleur(KBleu);
            cout << Mat [i][j];
            Couleur(KReset);
        }

        cout << endl;
    }

}


void InitMat (CMatrix & Mat, CPosition & PosPlayer1, CPosition & PosPlayer2, char & car){



   for (CVLine & Line : Mat)
   {

       for (char & Cel : Line)
            Cel = car;
       cout << endl;
   }

   Mat [PosPlayer1.first][PosPlayer1.second] = KTokenPlayer1;
   Mat [PosPlayer2.first][PosPlayer2.second] = KTokenPlayer2;
}














int main(int argc, char *argv[])
{


    CMatrix Map(10,CVLine(10));
    InitMat()
    ShowMatrix(Map);





}
