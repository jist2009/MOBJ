#ifndef __SAVECELLDIALOG_H
#define __SAVECELLDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>


class SaveCellDialog : public QDialog {
    Q_OBJECT;

    public :
        SaveCellDialog(QWidget* parent = NULL);
        bool run (QString& name);
        static bool run(QString& name, QWidget* parent = NULL);
        QString getCellName () const;
        void setCellName (QString) ;
    
    private : 
        QLineEdit* lineEdit_;
};

#endif