// -*- explicit-buffer-name: "CellWidget.h<M1-MOBJ/8-10>" -*-

#ifndef NETLIST_CELL_WIDGET_H
#define NETLIST_CELL_WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QPoint>
class QPainter;
#include "Point.h"
#include "Box.h"


namespace Netlist {

  class Cell;
  class Term;
  class NodeTerm;
  class BoxShape;
  class LineShape;
  class TermShape;

  class CellWidget : public QWidget {
      Q_OBJECT;
    public:
                      CellWidget         ( QWidget* parent=NULL ); // constructeur 
      virtual        ~CellWidget         (); // destructeur 
              void    setCell            ( Cell* ); // changement de Cell
      inline  Cell*   getCell            () const; // obtenir la Cell
      inline  int     xToScreenX         ( int x ) const; // coordonnée réelle -> coordonnée écran
      inline  int     yToScreenY         ( int y ) const; // coordonnée réelle -> coordonnée écran

      inline  QRect   boxToScreenRect    ( const Box& ) const; // Box -> QRect pour l'affichage sur l'écran
      inline  QPoint  pointToScreenPoint ( const Point& ) const; // Point -> QPoint 
      inline  int     screenXToX         ( int x ) const; // voir la case x dans l'écran
      inline  int     screenYToY         ( int y ) const; // voir la case y dans l'écran 
      inline  Box     screenRectToBox    ( const QRect& ) const; // QRect -> Box
      inline  Point   screenPointToPoint ( const QPoint& ) const; // QPoint -> Point
      
      
      virtual QSize   minimumSizeHint    () const;  // taille minimal 
      virtual void    resizeEvent        ( QResizeEvent* ); // modifier la taille de fenêtre 


      void drawBoxShape(BoxShape*, QPainter&, Point);
      void drawLineShape(LineShape*, QPainter&, Point);
      void drawTermShape(TermShape*, QPainter&, Point);
      void drawTerm(Term* term, QPainter& painter);

    protected:
      virtual void    paintEvent         ( QPaintEvent* ); // dessiner la cell
      virtual void    keyPressEvent      ( QKeyEvent* ) override; // réaction des touches de clavier
      void query(Box& box) const;
      void recenter();
    public slots:
              void    goLeft             ();
              void    goRight            ();
              void    goUp               ();
              void    goDown             ();
    private:
      Cell* cell_;
      Box   viewport_;
  };

  // Rajouter les autres fonctions inline 

  inline Cell* CellWidget::getCell () const { return cell_; }
  //inline  int  CellWidget::xToScreenX(int x ) const { return x - viewport_.getX1();}
  //inline  int     CellWidget::yToScreenY( int y ) const {return viewport_.getY2() - y;}

  inline int CellWidget::xToScreenX(int x) const {
    // (width() - viewport_.getWidth()) / 2  <-- C'est la marge pour centrer
    int offset = (width() - viewport_.getWidth()) / 2;
    return (x - viewport_.getX1()) + offset;
  }

  inline int CellWidget::yToScreenY(int y) const {
    int offset = (height() - viewport_.getHeight()) / 2;
    return (viewport_.getY2() - y) + offset;
  }
  
  inline  QRect   CellWidget::boxToScreenRect ( const Box& box ) const {
    int x = xToScreenX(box.getX1());
    int y = yToScreenY(box.getY2());
    int w = box.getX2() - box.getX1();
    int h = box.getY2() - box.getY1();
    return QRect(x,y,w,h);
  }

  inline  QPoint  CellWidget::pointToScreenPoint ( const Point& p) const {
    return QPoint ( xToScreenX(p.getX()), yToScreenY(p.getY()));
  }

  inline  int     CellWidget::screenXToX         ( int x ) const { return x + viewport_.getX1();}
  inline  int     CellWidget::screenYToY         ( int y ) const { return viewport_.getY2() - y;}

  inline Box CellWidget::screenRectToBox(const QRect& rect) const {
    int x1 = screenXToX( rect.left() );
    int x2 = screenXToX( rect.right() );
    
    // ATTENTION : Le bas du rectangle écran (y + height) 
    // correspond au y1 (minimum) du monde VLSI.
    int y1 = screenYToY( rect.bottom() ); 
    int y2 = screenYToY( rect.top() );    

    return Box(x1, y1, x2, y2);
  }
  
  inline  Point   CellWidget::screenPointToPoint ( const QPoint&  point) const {
      int x = screenXToX(point.x());
      int y = screenYToY(point.y());
      return Point(x, y);  }
}  // Netlist namespace.

#endif  // NETLIST_CELL_WIDGET_H


/*
l'écran d'affichage commence par le haut (0,0)

Question 1 de moi : pour la fonction xToScreenX, si x < X1 ? c dangereux car en dehors de l'écran 
--> c normal , il peut dessiner en dehors de l'écran et n'afficher que sur l'écran
*/