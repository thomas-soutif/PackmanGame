#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <ncurses.h>
using namespace std;

/* Package à installer : libncurses5-dev (sudo apt-get install libncurses5-dev)
    Compilation préconisée : g++ -std=c++11 main.cpp -lncurses
*/

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
const char KVide = ' ';
string nom_map;


int Key;


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
            if(Mat [i][j] == KTokenPlayer){
                Couleur(KJaune);
                cout << Mat [i][j];
            }
            else if( Mat[i][j] == obstacle){
                Couleur(KRouge);
                cout << Mat [i][j];
            }
            else if (Mat[i][j] == 'B'){

                Couleur(KBleu);
                cout << "#";
            }
            else
                cout << Mat[i][j];
            Couleur(KReset);
        }

        cout << endl;
    }

}

CMatrix GenereObstacle(CMatrix & Mat){


    fstream fic_niveau;
    fic_niveau.open(nom_map,ios_base::in);

    for(CVLine & Line : Mat )
    {
        for(char & car : Line)
        {


            fic_niveau >> car;
        }
    }
    fic_niveau.close();
    return Mat;


}


void InitMat (CMatrix & Mat,Position & PosPlayer, const char & nourriture){


    Mat = GenereObstacle(Mat); // On modifie la matrice actuel pour copier le contenue du fichier 'niveau'
    for (CVLine & Line : Mat)
    {

       for (char & Cel : Line)

            if (Cel == 'B') Cel = 'B'; // On laisse le B (code couleur)
            else if(Cel == '_') Cel = nourriture; // On remplace tout ce qui n'est pas des obstacles par de la nourriture

    }

   Mat [PosPlayer.y][PosPlayer.x] = KTokenPlayer; // On place le token du joueur.
}




void taille_fichier(){ // Cherche la taille de la map contenue dans le fichier nom_map

    fstream fic_niveau;
    fic_niveau.open(nom_map,ios_base::in);
    if(!fic_niveau.is_open()) { cout << "Erreur : La map n'a pas pu être charger (vérifier si le fichier existe)"; exit(1);}
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


    fic_niveau.close();

}

void waiting(float temps)
{
    clock_t arrivee=clock()+(temps*CLOCKS_PER_SEC);
    while(clock()< arrivee);


}


bool IsObstacle(CMatrix & Mat,string mov){
    bool is = false;



    if(mov == "top")
    {
        if (Mat[Player.y - 1][Player.x] == obstacle || Mat[Player.y - 1][Player.x] == 'B' ) is = true;

    }
    else if(mov == "bottom")
    {
        if (Mat[Player.y + 1][Player.x] == obstacle || Mat[Player.y + 1][Player.x] == 'B' ) is = true;
    }
    else if(mov == "left")
    {
        if (Mat[Player.y][Player.x - 1] == obstacle || Mat[Player.y][Player.x - 1] == 'B' ) is = true;
    }
    else if(mov == "right")
    {
        if (Mat[Player.y][Player.x + 1] == obstacle || Mat[Player.y][Player.x + 1] == 'B' ) is = true;
    }

    return is;


}

void Deplacement_joueur(CMatrix & Mat,int KeyInput)
{


    if(KeyInput > 0 ) Key = KeyInput;
    switch(Key)
    {
    case 122: // 'z'
        if (IsObstacle(Mat,"top")) break;
        Player.y = Player.y - 1;
        Mat[Player.y][Player.x] = KTokenPlayer;
        Mat[Player.y+1][Player.x] = KVide;
        break;

    case 115: // 's'
        if (IsObstacle(Mat,"bottom")) break;
        Player.y = Player.y + 1;
        Mat[Player.y][Player.x] = KTokenPlayer;
        Mat[Player.y -1][Player.x] = KVide;
        break;

    case 113: // 'q'
        if (IsObstacle(Mat,"left")) break;
        Player.x = Player.x - 1;
        Mat[Player.y][Player.x] = KTokenPlayer;
        Mat[Player.y][Player.x + 1] = KVide;
        break;
    case 100: // 'd'
        if (IsObstacle(Mat,"right")) break;
        Player.x = Player.x + 1;
        Mat[Player.y][Player.x] = KTokenPlayer;
        Mat[Player.y][Player.x - 1] = KVide;
        break;

    }

    waiting(0.1);



}





void Menu(){

    ClearScreen();
    cout << "PackMan version 1.5" << endl;
    cout << " 1 : Jouer en solo" << endl;
    cout << " 2 : Jouer en Multijoueur (non disponible)" << endl;
    cout << " 3 : Quitter" << endl;




}

int main(int argc, char *argv[])
{

    Menu();
    int choix;
    cout << "Votre choix ? : ";
    cin >> choix;

    if(choix == 1 )
    {
        nom_map = "google_map";
    }
    else exit(0);




    taille_fichier(); // renvoie le nombre de colonne et de ligne du fichier nomp_map afin de créer la bonne taille pour la matrice.
    CMatrix Map(Taille_matrice.y,CVLine(Taille_matrice.x)); // La taille de la matrice dépend de la taille de la map !
    Player.x = 5;
    Player.y = 8;

    InitMat(Map,Player,nourriture); // On initialise la map (obstacle, joueur ..)


    while(true)

	{

        initscr();
        nodelay(stdscr,TRUE);
        cbreak();
        noecho();
        int KeyInput = getch(); // on récupere la saisie clavier
        Deplacement_joueur(Map,KeyInput);
        endwin();
        ShowMatrix(Map);

	}













    ShowMatrix(Map); // On affiche la Matrice



    /* Suite en développement */


}
