#ifndef __CELLVIEWER_H__
#define __CELLVIEWER_H__

#include <QMainWindow>
#include "SaveCellDialog.h"
#include "InstancesWidget.h"
#include "CellWidget.h"

namespace Netlist{
  class Cell;
  class CellsLib;

  class CellViewer : public QMainWindow {
      Q_OBJECT;
    public:
                        CellViewer          ( QWidget* parent=NULL );
      virtual          ~CellViewer          ();
              Cell*     getCell             () const;
      inline  CellsLib* getCellsLib         () const;  // TME9+.
    public slots:
              void      setCell             ( Cell* );
              void      saveCell            ();
              void      openCell            ();
              void      showCellsLib        ();  // TME9+.
              void      showInstancesWidget ();  // TME9+.
    private:
      CellWidget*      cellWidget_;
      CellsLib*        cellsLib_;         // TME9+.
      InstancesWidget* instancesWidget_;  // TME9+.
      SaveCellDialog*  saveCellDialog_;
  };

  inline CellsLib* CellViewer::getCellsLib() const {return cellsLib_;}
}

#endif