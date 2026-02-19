#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QApplication>
#include "OpenCellDialog.h"
#include "SaveCellDialog.h"
#include "Cell.h"
#include "CellWidget.h"
#include "CellViewer.h"
#include "CellsLib.h"

namespace Netlist{
    // Existence de CellWidget
    // Mais pas encore pour CellsLib et InstancesWidget

    // Constructeur 
    CellViewer::CellViewer(QWidget* parent)
    : QMainWindow(parent)
    , cellWidget_(NULL)
    , cellsLib_(NULL)
    , instancesWidget_(NULL)
    , saveCellDialog_(NULL)
    {
        //1. Création et configuration du Widget Central (la zone de dessin)
        cellWidget_ = new CellWidget();
        setCentralWidget(cellWidget_);
        resize(1800, 1600);
        setWindowTitle(tr("TME810"));

        // 2. Création et configuration du dialogue de sauvegarde (réutilisable)
        saveCellDialog_ = new SaveCellDialog(this);
        cellsLib_ = new CellsLib(this);
        instancesWidget_ = new InstancesWidget(this);

        // 3. Configuration de la fenêtre et des menus

        // Configuration des Menus
        QMenu* fileMenu = menuBar()-> addMenu(tr("&File"));

        // Action Open 
        QAction* openAction = fileMenu->addAction(tr("&Open..."), this, SLOT(openCell()));
        openAction->setShortcut(QKeySequence::Open);
    
        // Action Save
        QAction* saveAction = fileMenu->addAction(tr("&Save..."), this, SLOT(saveCell()));
        saveAction->setShortcut(QKeySequence::Save);

        // Action Close
        QAction* closeAction = fileMenu->addAction(tr("&Close"), this, SLOT(close()));
        closeAction->setShortcut(QKeySequence::Close);

        // Action Quit
        QAction* quitAction = fileMenu->addAction(tr("&Quit"), qApp, SLOT(quit()));
        quitAction->setShortcut(QKeySequence::Quit);

        QMenu* viewMenu = menuBar()->addMenu("&View");
        connect(viewMenu->addAction("&Cells Library"), SIGNAL(triggered()), this, SLOT(showCellsLib()));
        connect(viewMenu->addAction("&Show Instances"), SIGNAL(triggered()), this, SLOT(showInstancesWidget()));

    }

    CellViewer::~CellViewer()
    {
        // Qt gère la destruction de la plupart des enfants (cellWidget_, saveCellDialog_)
        // car ils ont "this" comme parent, mais c'est toujours bien d'être explicite
        delete saveCellDialog_; // si il n'est pas enfant du viewer il faut le delete
        // Les autres membres sont gérés par QMainWindow 
    }

    Cell* CellViewer::getCell() const{
        if (cellWidget_)
            return cellWidget_->getCell();
        return NULL;
    }

    // ==================================
    // SLOTS PUBLICS
    // ==================================

    void CellViewer::setCell(Cell* cell) {
        cellWidget_->setCell(cell);
        instancesWidget_->setCell(cell);
        // Si CellsLib a un besoin spécifique de sélection, le mettre ici aussi
    }
    void CellViewer::saveCell() {
        // Implémentation du slot Save

        QString name;
        if (SaveCellDialog::run(name, this)){
            Cell* currentCell = getCell();
            if(currentCell)
                currentCell->setName(name.toStdString()); // MAJ du nom
            
        }
    }

    void CellViewer::openCell()
    {
        // Implementation du slot Open
        QString name;
        if(OpenCellDialog::run(name, this)){
            std::string stdName = name.toStdString();
            Cell* cell = Cell::getCell(stdName);

            if (not cell){
                cell = Cell::load(stdName);
            }

            if (cell){
                setCell(cell);
                showInstancesWidget();
                std::cout << "Cellule" << stdName << "affichée" << std::endl;
            } else {
                std::cerr << "Erreur de chargement de " << stdName << std::endl;
            }

            // Emission du signal pour la synchronisation
            // emit cellLoaded();
        }
    }

    // affichage des liste de cell
    void CellViewer::showCellsLib() {
        if (cellsLib_){
            QPoint center = this->geometry().center();
            cellsLib_->move(center.x() - cellsLib_->width()/2 - 200, 
                            center.y() - cellsLib_->height()/2 -200);
            cellsLib_->show(); 
            cellsLib_->raise();
        }
    }

    // affichage des liste de instance
    void CellViewer::showInstancesWidget(){
        if(instancesWidget_){
            instancesWidget_->move(this->geometry().center() - instancesWidget_->rect().center());
            instancesWidget_->show();
            instancesWidget_->raise();
        }
    }

}
