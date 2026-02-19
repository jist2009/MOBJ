#ifndef __CELLSMODEL_H__
#define __CELLSMODEL_H__

#include <QAbstractTableModel>
#include <vector>

namespace Netlist{
    class Cell;

    class CellsModel : public QAbstractTableModel{
        Q_OBJECT;
        public :
        
            CellsModel(QObject* parent=NULL);
            ~CellsModel();
            
            int rowCount(const QModelIndex& parent = QModelIndex()) const override;
            int columnCount(const QModelIndex& parent = QModelIndex()) const override;
            QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
            QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const ;
            Cell* getCell(int ligne) const;
        
        public slots:    
            void update();

        private : 
            std::vector<Cell*> cells_;
    };
}

#endif
