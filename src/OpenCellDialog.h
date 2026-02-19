#ifndef __OPENCELLDIALOG_H__
#define __OPENCELLDIALOG_H__

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>

namespace Netlist{
    class OpenCellDialog : public QDialog {
        Q_OBJECT;

        public :
            // constructeur 
            OpenCellDialog(QWidget* parent = NULL);
            // destructeur
            ~OpenCellDialog();

            bool run (QString& name);
            static bool run(QString& name, QWidget* parent = NULL);
            QString getCellName () const;
            void setCellName (QString) ;

        private : 
            QLineEdit* lineEdit_;
            // Méthode interne pour construire l'interface
            void setup();
    };

}
#endif