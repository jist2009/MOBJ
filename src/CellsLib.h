#ifndef __CELLSLIB_H__
#define __CELLSLIB_H__

#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include "CellsModel.h"


namespace Netlist{
    class CellViewer;
    
    class CellsLib : public QWidget {
        Q_OBJECT

        public : 
            CellsLib(QWidget* parent=NULL);
            inline CellsModel* getBaseModel() const { return baseModel_;};
            void show();
        public slots :
            void load();            
        private :
            CellViewer* cellViewer_;
            CellsModel* baseModel_;
            QTableView* view_;
            QPushButton* load_;
    };
}

#endif