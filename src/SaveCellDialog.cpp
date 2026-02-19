#include "SaveCellDialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

SaveCellDialog::SaveCellDialog(QWidget* parent)
    : QDialog(parent), lineEdit_(nullptr)
    {
        // Configuration de l'interface utilisateur 
        setWindowTitle("SaveCell");

        QLabel* label = new QLabel();
        label->setText("Enter Cell Name");

        // Champ de texte pour le nom de la Cell
        lineEdit_ = new QLineEdit();
        QLabel* nameLabel = new QLabel(tr("Cell Name:"));
        lineEdit_->setMinimumWidth(400);

        // Boutons 
        QPushButton* okButton = new QPushButton();
        okButton->setText("OK");
        okButton->setDefault(true);
        QPushButton* cancelButton = new QPushButton();
        cancelButton->setText("cancel");

        // Widget
        QHBoxLayout* hLayout = new QHBoxLayout();
        hLayout->addStretch();
        hLayout->addWidget(okButton);
        hLayout->addStretch();
        hLayout->addWidget(cancelButton);
        hLayout->addStretch();

        QVBoxLayout* vLayout = new QVBoxLayout();        
        vLayout->addWidget(label);
        vLayout->addStretch();
        vLayout->addWidget(lineEdit_);
        vLayout->addStretch();
        vLayout->addLayout(hLayout);
        setLayout(vLayout);
        vLayout->setSizeConstraint(QLayout::SetFixedSize);

        connect(okButton, SIGNAL(clickeed()), this, SLOT(accept()));
        connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    }

    bool SaveCellDialog::run(QString& name){
        if(exec() == QDialog::Accepted){
            // L'utilisateur a cliqué sur OK (ou appuyé sur Entrée)
            // récupère le nom de saisi
            name = getCellName();

            if (name.isEmpty()){
                return false;
            }
            return true;
        }
        // L(utilisateur a cliqué sur Annuler 
        return false;
    }

    // Version statique 
    bool SaveCellDialog::run(QString& name, QWidget* parent) {
    // 1. Création du dialogue sur la pile (ou avec 'new' puis 'delete later')
    // Utiliser la pile est plus simple ici.
        SaveCellDialog dialog(parent); 
        
        // 2. Exécution du dialogue
        if (dialog.exec() == QDialog::Accepted) {
            
            name = dialog.getCellName();
            
            if (name.isEmpty()) {
                return false;
            }
            
            return true;
        }
            
        // Sortie de scope: 'dialog' est détruite automatiquement
        return false;
}
    
    QString SaveCellDialog::getCellName() const {
        return lineEdit_->text();
    }

    void SaveCellDialog::setCellName(QString name){
        lineEdit_->setText(name);
    } 

    