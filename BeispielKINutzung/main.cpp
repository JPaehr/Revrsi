#include "../../Dokumente/Revrsi/src/AI/ki_logic.h"

#include <iostream>

using namespace std;

int main(){

    Logic dieLogic(8,8,2);
    dieLogic.setInitStones();

    ki_logic KI(8,8,dieLogic.getFields(),1);

    int x, y;//, a;
    while(1){
        cout << "Aktuelle Spieler ist: " << dieLogic.getAktPlayer() << endl;
        //cin >> a;
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                cout << dieLogic.getFields()[i][j] << " ";
            }
            cout << endl;
        }


        if(dieLogic.getAktPlayer() == 1){
            KI.vectorUpdate(dieLogic.getFields());
            vector<int> koordinaten = KI.KiXY();
            x = koordinaten[0];
            y = koordinaten[1];
            cout << "KI x setzt auf: " << x << endl;
            cout << "KI y setzt auf: " << y << endl;


            dieLogic.setField(x,y);
            //dieLogic.setAktPlayer(2);
        }
        else{
            cout << "x";
            cin >> x;
            cout << "y";
            cin >> y;
            dieLogic.setField(x,y);
        }
    }


    return 0;
}
