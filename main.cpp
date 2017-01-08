#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;



typedef vector <char> CVLine; // un type représentant une ligne de la grille
typedef vector <CVLine> CMatrix; // un type représentant la grille

typedef struct {
    int y;
    int x;
} Position;
Position Player,Taille_matrice;

const char KTokenPlayer = 'O';
const char nourriture = '*';
const char obstacle = '#';




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

CMatrix GenereObstacle(CMatrix Mat){


    fstream fic_niveau;
    fic_niveau.open("niveau",ios_base::in);

    for(CVLine & Line : Mat )
    {
        for(char & car : Line)
        {


            fic_niveau >> car;
        }
    }

    return Mat;


}


void InitMat (CMatrix & Mat,Position & PosPlayer, const char & nourriture){


    Mat = GenereObstacle(Mat); // On modifie la matrice actuel pour copier le contenue du fichier 'niveau'
    for (CVLine & Line : Mat)
    {

       for (char & Cel : Line)
            if(Cel != '#') Cel = nourriture; // On remplace tout ce qui n'est pas des obstacles par de la nourriture

    }

   Mat [PosPlayer.y][PosPlayer.x] = KTokenPlayer; // On place le token du joueur.
}




void taille_fichier(){ // Cherche la taille de la map contenue dans le fichier du niveau

    fstream fic_niveau;
    fic_niveau.open("niveau",ios_base::in);
    unsigned ligne = 0;;
    unsigned colonne = 0;
    string line;
    for(getline(fic_niveau,line); !fic_niveau.eof(); getline(fic_niveau,line))
    {

        for(char & car : line)
        {

            ++colonne;
        }
        ++ligne;
    }
    Taille_matrice.x = (colonne - ligne) / ligne; // nombre de colonne (il faut enlever les 'eof' en trop, qui sont considéres comme des colonnes
    Taille_matrice.y = ligne + 1; // nombre de ligne (rajouter une ligne car l'indice commence a 0);




}


int main(int argc, char *argv[])
{


    taille_fichier(); // renvoie le nombre de colonne et de ligne du fichier 'niveau' afin de créer la bonne taille pour la matrice.
    CMatrix Map(Taille_matrice.y,CVLine(Taille_matrice.x)); // La taille de la matrice dépend de la taille de la map !
    Player.x = 5;
    Player.y = 9;

    InitMat(Map,Player,nourriture); // On initialise la map (obstacle, joueur ..)
    ShowMatrix(Map); // On affiche la Matrice



    /* Suite en développement */


}
