#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QItemSelectionModel>

#include "CellsLib.h"
#include "CellViewer.h"

namespace Netlist{
    CellsLib::CellsLib(QWidget* parent)
    : QWidget(parent), cellViewer_(NULL), baseModel_(NULL), view_(NULL), load_(NULL)
    {
        // 1. initialisation des composants 
        baseModel_ = new CellsModel(this);
        view_ = new QTableView(this);
        view_->setModel(baseModel_);
        load_ = new QPushButton("load", this);

        // 2. Configuration du tableau (QTableView)
        view_->setSelectionBehavior(QAbstractItemView::SelectRows);
        view_->setSelectionMode(QAbstractItemView::SingleSelection);

        view_->horizontalHeader()->setStretchLastSection(true);
        view_->verticalHeader()->hide();
        QVBoxLayout* vLayout = new QVBoxLayout();

        // 3. Mise en Page (Layout)

        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->addStretch();
        hLayout->addWidget(view_);
        hLayout->addWidget(load_);
        hLayout->addStretch();

        vLayout->addLayout(hLayout);
        setLayout(vLayout);

        // 4. Connexions

        connect(load_, SIGNAL(clicked()), this, SLOT(load()));
    }

    void CellsLib::show(){
        baseModel_->update();
        resize(400,300);
        QWidget::show();
    }

    // public slots

    void CellsLib::load()
    {
        int row = view_->currentIndex().row();
        if (row < 0) return; 

        Cell* cell = baseModel_->getCell(row);
        if (cell){
            close();
        }
    }
}