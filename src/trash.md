
          // --- BOX ---
        if (BoxShape* box = dynamic_cast<BoxShape*>(shape)) {
            Box b = box->getBoundingBox();
            // Transformation en coordonnées écran
            int x = xToScreenX(b.getX1() + pos.getX());
            int y = yToScreenY(b.getY1() + pos.getY());
            int w = xToScreenX(b.getX2() + pos.getX()) - x;
            int h = yToScreenY(b.getY2() + pos.getY()) - y; 
            // Note: Attention au signe de h selon l'orientation de l'axe Y
            painter.drawRect(x, y, w, h);
        }

        // --- LINE ---
        if (LineShape* line = dynamic_cast<LineShape*>(shape)) {
            Box b = line->getBoundingBox();

            int x = xToScreenX(b.getX1() + pos.getX());
            int y = yToScreenY(b.getY1() + pos.getY());
            int w = xToScreenX(b.getX2() + pos.getX()) - x;
            int h = yToScreenY(b.getY2() + pos.getY()) - y;
            painter.drawRect(x, y, w, h);

        }
        // ---TERM---
        if (TermShape* term = dynamic_cast<TermShape*>(shape)){
          int x = xToScreenX(term->getX1() + pos.getX());
          int y = yToScreenY(term->getY1() + pos.getY());
          int size = 4;

          painter.setBrush(Qt::red);
          painter.setPen(Qt::NoPen);
          painter.drawRect(x - size/2, y - size/2, size, size);

          painter.setPen(Qt::black);
          painter.drawText(x + 5, y + 5, QString::fromStdString(term->getTerm()->getName()));
        }






























// -*- explicit-buffer-name: "CellWidget.cpp<M1-MOBJ/8-10>" -*-

#include  <QResizeEvent>
#include  <QPainter>
#include  <QPen>
#include  <QBrush>
#include  <QFont>
#include  <QApplication>
#include  "Term.h"
#include  "Instance.h"
#include  "Symbol.h"
#include  "Shape.h"
#include  "Cell.h"
#include  "Line.h"
#include  "Node.h"
#include  "Net.h"

#include "Symbol.h"
#include "BoxShape.h"
#include "LineShape.h"
#include "TermShape.h"
#include  "CellWidget.h"



namespace Netlist {  

  // affichage dimensions de QRect
  std::ostream& operator<< ( std::ostream& o, const QRect& rect )
  {
    o << "<QRect x:" << rect.x()
      <<       " y:" << rect.y()
      <<       " w:" << rect.width()
      <<       " h:" << rect.height() << ">";
    return o;
  }

  // affichage coordonnées du Qpoint
  std::ostream& operator<< ( std::ostream& o, const QPoint& p )
  { o << "<QRect x:" << p.x() << " y:" << p.y() << ">"; return o; }

  // Constructeur 
  CellWidget::CellWidget ( QWidget* parent )
    : QWidget(parent)
    , cell_  (NULL)
  {
    printf("CellWidget constructeur\n");
    setAttribute    ( Qt::WA_OpaquePaintEvent ); // widget dessine sur toute sa surface , ne dessine pas derrière
    setAttribute    ( Qt::WA_NoSystemBackground ); // empeche l'affichage de l'arrière plan par défaut du système 
    setAttribute    ( Qt::WA_StaticContents ); // contenu fixe <=> modifier la fenêtre ne modifie pas l'écran
    setSizePolicy   ( QSizePolicy::Expanding, QSizePolicy::Expanding );// essaie de prendre toute l'espace disponible 
    setFocusPolicy  ( Qt::StrongFocus ); // permet de recevoir le focus clavier 
    setMouseTracking( true ); // recoit les evenements souris 
  }

  CellWidget::~CellWidget (){}


  void CellWidget::setCell ( Cell* cell ) {
    printf("CellWidget::setCell\n");
    cell_ = cell;
    recenter(); // -> query() 
    printf("New Cell: %s, Viewport: x1=%d, y1=%d, w=%d\n", 
            cell->getName().c_str(), viewport_.getX1(), viewport_.getY1(), viewport_.getWidth());
    repaint();
    update();
  }

// taille minimal 
  QSize  CellWidget::minimumSizeHint () const
  { return QSize(500,500); }

  // modifie la taille de fenêtre 
  void  CellWidget::resizeEvent ( QResizeEvent* event )
  { repaint(); }


  // PROTECTED 
  // dessine la cell
  void  CellWidget::paintEvent ( QPaintEvent* event )
  {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    if (not cell_) return;

    for (Instance* inst : cell_->getInstances()){
      Point pos = inst->getPosition();
      Symbol* symbol = inst->getMasterCell()->getSymbol();
      if (not symbol) continue;

      for (Shape* shape : symbol->getShapes()){
          // --- BOX ---
        if (BoxShape* box = dynamic_cast<BoxShape*>(shape)) {
            Box b = box->getBoundingBox();
            // Transformation en coordonnées écran
            int x = xToScreenX(b.getX1() + pos.getX());
            int y = yToScreenY(b.getY1() + pos.getY());
            int w = xToScreenX(b.getX2() + pos.getX()) - x;
            int h = yToScreenY(b.getY2() + pos.getY()) - y; 
            // Note: Attention au signe de h selon l'orientation de l'axe Y
            painter.drawRect(x, y, w, h);
        }

        // --- LINE ---
        if (LineShape* line = dynamic_cast<LineShape*>(shape)) {
            Box b = line->getBoundingBox();

            int x = xToScreenX(b.getX1() + pos.getX());
            int y = yToScreenY(b.getY1() + pos.getY());
            int w = xToScreenX(b.getX2() + pos.getX()) - x;
            int h = yToScreenY(b.getY2() + pos.getY()) - y;
            painter.drawRect(x, y, w, h);

        }
        // ---TERM---
        if (TermShape* term = dynamic_cast<TermShape*>(shape)){
          int x = xToScreenX(term->getX1() + pos.getX());
          int y = yToScreenY(term->getY1() + pos.getY());
          int size = 4;

          painter.setBrush(Qt::red);
          painter.setPen(Qt::NoPen);
          painter.drawRect(x - size/2, y - size/2, size, size);

          painter.setPen(Qt::black);
          painter.drawText(x + 5, y + 5, QString::fromStdString(term->getTerm()->getName()));
        }
      }
    }
  }

  // réaction des touches du clavier 
  void  CellWidget::keyPressEvent(QKeyEvent* event){
    switch (event->key()){
      case Qt::Key_Left: goLeft(); break;
      case Qt::Key_Right: goRight(); break;
      case Qt::Key_Up: goUp(); break;
      case Qt::Key_Down: goDown(); break;
      default:
        QWidget::keyPressEvent(event); // Important pour propager les autres touches
    }
  }

  void CellWidget::goLeft(){
    printf("CellWidget::goLeft\n");
    viewport_.translate(-20, 0);
    update();
  }

  void CellWidget::goRight(){
    printf("CellWidget::goRIght\n");
    viewport_.translate(20, 0);
    update();
  }

  void CellWidget::goUp(){
    printf("CellWidget::goUp\n");
    viewport_.translate(0, 20);
    update();
  }

  void CellWidget::goDown(){
    printf("CellWidget::goDown\n");
    viewport_.translate(0, -20);
    update();
  }

  void CellWidget::query(Box& box) const {
    printf("CellWidget::query\n");
    if(!cell_) return;
    box = Box();

    Symbol* sym = cell_->getSymbol();
    if (sym){
      printf("la cellule actuel %s possède un symbole que je dois afficher\n", cell_->getName().c_str());
      box.merge(sym->getBoundingBox());
    }

    for (Instance* inst : cell_->getInstances()){
      Symbol* instSym = inst->getMasterCell()->getSymbol();
      if (instSym){
        Box instBox = inst->getMasterCell()->getSymbol()->getBoundingBox();
        instBox.translate(inst->getPosition().getX(), inst->getPosition().getY());
        box.merge(instBox);
      }
    }
  }

  void CellWidget::recenter(){
    printf("CellWidget::recenter\n");
    Box box;
    query(box);
    viewport_ = box;
    update();

  }
  
}  // Netlist namespace.
