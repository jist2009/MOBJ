#include "InstancesModel.h"
#include <Qt>
#include <QString>
#include "Cell.h"
#include "Instance.h"

namespace Netlist {
    
    InstancesModel::InstancesModel(QObject* parent)
    : QAbstractTableModel(parent), cell_(NULL){
    }

    InstancesModel::~InstancesModel(){}

    int InstancesModel::rowCount(const QModelIndex& parent) const
    {
        if(parent.isValid()) return 0;
        if (not cell_) return 0;
        return cell_->getInstances().size();
    }

    int InstancesModel::columnCount(const QModelIndex& parent) const 
    {
        return MAX_COLONNE;
    }

    QVariant InstancesModel::data(const QModelIndex& index, int role) const 
    {
        if(!index.isValid()) 
            return QVariant();

        // 1. onn ne s'intéresse qu'au rôle d'affichage (texte)
        if (role != Qt::DisplayRole)
            return QVariant();
        
        // 2. récuperer l'Instance correspondant à la ligne 
        const std::vector<Instance*>& instances = cell_->getInstances();
        int row = index.row();

        if (row < 0 || row >= (int)instances.size())
            return QVariant();
        
        Instance* instance = instances[row];

        // 3. On retourne la donnée en fonction de la colonne
        switch (index.column()){
            case NAME:
                return QString::fromStdString(instance->getName());
            case MASTER:
                return QString::fromStdString(instance->getMasterCell()->getName());
            default:
                QVariant();
        }
        
        return QVariant();
    }

    QVariant InstancesModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (orientation == Qt::Vertical) 
            return QVariant(); // Pas d'en tête pour les lignes
        
        if (role != Qt::DisplayRole)
            return QVariant();
        
        // Titres des colonnes horizontales
        switch ((section)){
            case NAME:
                return "Instance Name";
            case MASTER:
                return "Master Cell";
            default:
                return QVariant();
        }    
    }

    void InstancesModel::setCell(Cell* cell){
        beginResetModel();
        cell_ = cell;
        endResetModel();
        cell->toXml(std::cout);
    }

    Instance* InstancesModel::getInstance(int ligne) const {
        if (cell_ == NULL || ligne < 0 || ligne >= (int)cell_->getInstances().size())
            return NULL;
        
        const std::vector<Instance*>& instances = cell_->getInstances();        
        return instances[ligne];
    }
}

// je ne comprends pas QVariant()