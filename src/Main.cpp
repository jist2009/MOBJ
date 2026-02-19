#include <QApplication>
#include "CellViewer.h"
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
using namespace std;

#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"

int main(int argc, char* argv[]){

    using namespace Netlist;

    QApplication* qa = new QApplication(argc, argv);
    /*cout << "Chargement des modeles..." << endl;
    Cell::load( "vdd" );
    Cell::load( "gnd" );
    Cell::load( "TransistorN" );
    Cell::load( "TransistorP" );
    Netlist::Cell::load( "and2" );
    Cell::load( "or2" );
    Cell::load( "xor2" );
    Cell::load( "halfadder" );
*/
    CellViewer* viewer = new CellViewer();
    viewer->show();

    return qa->exec();
}