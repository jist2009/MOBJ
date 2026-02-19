#include "CellsModel.h"
#include "Cell.h"

namespace Netlist{
    CellsModel::CellsModel(QObject* parent)
    : QAbstractTableModel(parent){}

    CellsModel::~CellsModel(){}
   
    int CellsModel::rowCount(const QModelIndex& parent) const{
        return Cell::getAllCells().size();
    }

    int CellsModel::columnCount(const QModelIndex& parent) const{
        return 1;
    }

    QVariant CellsModel::headerData(int section, Qt::Orientation orientation, int role) const {
        if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
            if (section == 0) return "Cell";
        }
        return QVariant();
    } 

    QVariant CellsModel::data(const QModelIndex& index, int role) const{
        if(!index.isValid()) return QVariant();

        if (role == Qt::DisplayRole){
            Cell* cell = Cell::getAllCells()[index.row()];
            if (cell) return QString(cell->getName().c_str());            
        }
        return QVariant();
    }
    
    Cell* CellsModel::getCell(int ligne) const{
        if (ligne < 0 || ligne >= (int)Cell::getAllCells().size()) return NULL;
        return Cell::getAllCells()[ligne];
    }

    void CellsModel::update(){
        emit layoutChanged();
    }
}