#ifndef __INSTANCESMODEL_H__
#define __INSTANCESMODEL_H__

#include <QAbstractTableModel>
#include <vector>
#include <QVariant> 

namespace Netlist {
    class Cell;
    class Instance;

    class InstancesModel : public QAbstractTableModel {
        Q_OBJECT;

        public :
            enum Colonne{
                NAME = 0, // Nom de l'instance
                MASTER = 1, // Nom du Cell (modèle)
                MAX_COLONNE  
            };

            // Constructeur 
            InstancesModel (QObject* parent=NULL);
            // Destructeur 
            ~InstancesModel ();

            InstancesModel* getModel() const;
            void setCell(Cell* cell);

            
            int rowCount(const QModelIndex& parent = QModelIndex()) const override;
            int columnCount(const QModelIndex& parent = QModelIndex()) const override;
            QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
            QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
            Instance* getInstance(int ligne) const;
    
        private:
            Cell* cell_;

    };
}

#endif