#ifndef __INSTANCESWIDGET_H__
#define __INSTANCESWIDGET_H__

#include "InstancesModel.h"
#include <QWidget>
#include <QTableView>
#include <QPushButton>

namespace Netlist {
    class CellViewer;
    class Cell;

    class InstancesWidget: public QWidget{
        Q_OBJECT; // Nécessaire pour les Signaux et Slots

        public : 
            // Constructeur 
            InstancesWidget ( QWidget* parent=NULL);

            // Mutateur pour lier le widget à la fenêtre principale
            void setCellViewer (CellViewer*);

            // Accesseur pour obtenir l'index de la ligne sélectionnée (pour le chargement)
            int getSelectedRow () const;

            void setCell (Cell* cell);
        
            void show();
            
        public slots:
            void load ();

        private : 
            CellViewer* cellViewer_;
            InstancesModel* baseModel_;
            QTableView* view_;
            QPushButton* load_;
    };
}

#endif
