#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QItemSelectionModel>

#include "Instance.h"
#include "CellViewer.h"
#include "InstancesWidget.h"



namespace Netlist{
    // constructeur 
    InstancesWidget::InstancesWidget(QWidget* parent)
    : QWidget(parent), cellViewer_(NULL), baseModel_(NULL), view_(NULL), load_(NULL)
    {
        printf("InstancesWidget::InstancesWidget\n");
        baseModel_ = new InstancesModel(this);
        view_ = new QTableView(this);
        view_->setModel(baseModel_);
        load_ = new QPushButton("Load", this);

        // Configuration View
        view_->setSelectionBehavior(QAbstractItemView::SelectRows);
        view_->setSelectionMode(QAbstractItemView::SingleSelection);
        view_->horizontalHeader()->setStretchLastSection(true);
        //view_->horizontalHeader()->hide();

        // Layout pour le bouton (Horizontal)
        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->addStretch();
        hLayout->addWidget(load_);
        hLayout->addStretch();

        // Layout Principal (Vertical)
        QVBoxLayout* vLayout = new QVBoxLayout();
        vLayout->addWidget(view_); // Le tableau est en haut et prend l'espace
        vLayout->addLayout(hLayout); // Le bouton est en bas
        
        setLayout(vLayout); // Indispensable

        connect(load_, SIGNAL(clicked()), this, SLOT(load()));
    }
    
    // Mutateur 
    void InstancesWidget::setCellViewer(CellViewer* viewer){
        printf("InstancesWidget::setCellViewer\n");
        // Stocke la référence à la fenêtre principale pour pouvoir appeler ses méthodes(openCell, setCell, etc)
        cellViewer_ = viewer;
    }

    /**
     *  @brief Retourne l'index de la ligne actuellement sélectionnée dans le QTableView
     */
    // je dois donner la ligne actuellement touché 
    // Qobject 
    int InstancesWidget::getSelectedRow() const 
    {
        printf("InstancesWidget::getSelectedRow\n");
        QItemSelectionModel* selectionModel = view_->selectionModel();
        if(selectionModel->hasSelection()){
            QModelIndexList selectedRows = selectionModel->selectedRows();
            
            if(!selectedRows.isEmpty()){
                return selectedRows.first().row();
            }
        }
        return -1;

    }

    void InstancesWidget::show(){
        printf("InstancesWidget::show\n");
        update();
        resize(400,300);
        QWidget::show();
        view_->resizeColumnsToContents();
        
    }
    // Public slot

    void InstancesWidget::load ()
    {
        printf("InstancesWidget::load\n");
        int row = getSelectedRow();

        if (row != -1) {
            Instance* selectedInstance = baseModel_->getInstance(row);

            if (selectedInstance) {
                // 4. Récupère la Master Cell associée à cette Instance
                Cell* masterCell = selectedInstance->getMasterCell();

                if (masterCell) {
                    // 5. Demande au CellViewer de charger et d'afficher cette Master Cell
                    // On appelle setCell sur le CellViewer pour l'afficher dans le CellWidget
                    if (cellViewer_) 
                        cellViewer_->setCell(masterCell); 
                }
            }
        }
        close();
    }

    void InstancesWidget::setCell (Cell* cell){
        printf("InstancesWidget::setCell\n");
        baseModel_->setCell(cell);
        view_->resizeColumnsToContents();
    }
}