



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
    setAttribute    ( Qt::WA_OpaquePaintEvent ); // widget dessine sur toute sa surface , ne dessine pas derrière
    setAttribute    ( Qt::WA_NoSystemBackground ); // empeche l'affichage de l'arrière plan par défaut du système 
    setAttribute    ( Qt::WA_StaticContents ); // contenu fixe <=> modifier la fenêtre ne modifie pas l'écran
    setSizePolicy   ( QSizePolicy::Expanding, QSizePolicy::Expanding );// essaie de prendre toute l'espace disponible 
    setFocusPolicy  ( Qt::StrongFocus ); // permet de recevoir le focus clavier 
    setMouseTracking( true ); // recoit les evenements souris 
  }

  CellWidget::~CellWidget (){}


  void CellWidget::setCell ( Cell* cell ) {
    cell_ = cell;
    repaint(); // appel paintEvent 
    recenter();
  }

// taille minimal 
  QSize  CellWidget::minimumSizeHint () const
  { return QSize(500,500); }

  // modifie la taille de fenêtre 
  void  CellWidget::resizeEvent ( QResizeEvent* event )
  { 
    const QSize size = event->size();
    viewport_.setX2(viewport_.getX1() + size.width()); //TODO il faut des majuscules ou pas
    viewport_.setY1(viewport_.getY2() - size.height());
    repaint(); 
  }


  // PROTECTED 
  // dessine la cell
  void  CellWidget::paintEvent ( QPaintEvent* event )
  {
    printf("CellWIdget::paintEvent\n");
    QPainter painter(this);
    painter.fillRect(rect(), Qt::white);
    if (not cell_) return;

    // 1. DESSINER LE SYMBOLE DE LA CELLULE ELLE-MÊME (ex: pour xor2, vdd)
    Symbol* selfSymbol = cell_->getSymbol();
    if (selfSymbol) {
        for (Shape* shape : selfSymbol->getShapes()) {
            // Ici, la position est (0,0) car c'est la cellule de base
            if (BoxShape* box   = dynamic_cast<BoxShape*>(shape))  drawBoxShape(box, painter, Point(0,0));
            if (LineShape* line = dynamic_cast<LineShape*>(shape)) drawLineShape(line, painter, Point(0,0));
            if (TermShape* term = dynamic_cast<TermShape*>(shape)) drawTermShape(term, painter, Point(0,0));
        }
    }
    /*    
    
    Il affiche la masterCell des instances du cell
    mais je dois continuer avec la fenêtre de instancesWidget que je n'ai pas eu le temps de faire
    
    for (Instance* inst : cell_->getInstances()){
      Point pos = inst->getPosition();
      Symbol* symbol = inst->getMasterCell()->getSymbol();
      if (not symbol) continue;

      // 1. Dessiner les instances
      for (Shape* shape : symbol->getShapes()){
        if (BoxShape* box  = dynamic_cast<BoxShape*>(shape))  
            drawBoxShape(box, painter, pos);
        if (LineShape* line = dynamic_cast<LineShape*>(shape)) 
            drawLineShape(line, painter, pos);
        if (TermShape* term = dynamic_cast<TermShape*>(shape)) 
            drawTermShape(term, painter, pos);      
      }

      // 2. Dessiner les terminaux de la cellule elle meme 
      for (Term* term : cell_->getTerms()){
        drawTerm(term, painter);
      }
    }
    */
  }

  void CellWidget::drawBoxShape(BoxShape* boxShape, QPainter& painter, Point p){
    Box box = boxShape->getBoundingBox();
    box.translate(p);
    QRect rect = boxToScreenRect(box);
    painter.drawRect(rect);
    return;
  }

  void CellWidget::drawLineShape(LineShape* lineShape, QPainter& painter, Point p){
    int x1 = lineShape->getX1();
    int y1 = lineShape->getY1();
    int x2 = lineShape->getX2();
    int y2 = lineShape->getY2();

    x1 += p.getX();
    y1 += p.getY();
    x2 += p.getX();
    y2 += p.getY();

    QPoint p1(xToScreenX(x1), yToScreenY(y1));
    QPoint p2(xToScreenX(x2), yToScreenY(y2));
    painter.drawLine(p1, p2);
  }




    // Dessine un terminal d'une instance (internal)
    void CellWidget::drawTermShape(TermShape* termShape, QPainter& painter, Point position){
        int x = position.getX();
        int y = position.getY();
        Term* term = termShape->getTerm();
        QString text = QString::fromStdString(term->getName());

        painter.setPen(QPen(Qt::red));
        int width = 10;

        QPoint p(xToScreenX(x + termShape->getX1()), yToScreenY(y + termShape->getY1())); //TODO ça marche c'etait ça avant
        //QPoint p(xToScreenX(x) + termShape->getX(), yToScreenY(y) + termShape->getY()); //céest cassé ça 
        QRect rect = QRect(p.x() - (width/2), p.y() - (width/2), width, width);
        // QPainter::fillRect(rect, Qt::red);
        // fillRect(rect, Qt::red);
        painter.setBrush(Qt::red); // Définit le remplissage en rouge
        painter.setPen(QPen(Qt::black, 1)); // Contour noir très fin
        painter.drawRect(rect); // Dessine le rectangle plein + contour
        painter.setBrush(Qt::NoBrush); // Reset pour ne pas remplir les formes suivantes par erreur

        // TODO trouver comment dessiner une rectangle plein
        painter.drawRect(rect);

        // const QRect rectangle = QRect(p.x(), p.y(), 100, 50);
        // QRect boundingRect;
        // painter.drawText(rectangle, 0, text, &boundingRect);

        QFont font = QFont();
        font.setPixelSize(10);
        painter.setFont(font);
        painter.drawText(p.x() - 10, p.y() - 10, text);

    }

    // Dessine un terminal d'une cellule (external)
    void CellWidget::drawTerm(Term* term, QPainter& painter){
        QString text = QString::fromStdString(term->getName());
        Point position = term->getPosition();
        int x = xToScreenX(position.getX());
        int y = yToScreenY(position.getY());
        printf("Term: %-5s | Monde: [%4d,%4d] | Ecran: [%4d,%4d]\n", 
        
        term->getName().c_str(), 
        position.getX(), position.getY(), 
        x, y);
        int width = 20;
        Term::Direction dir = term->getDirection();
        QFont font = QFont();
        font.setPixelSize(10);

        painter.setFont(font);
        painter.setPen(QPen(Qt::red));

        if (dir == Term::Direction::In){
            QPoint points1[5] = {
                    QPoint(x-(width/2), y-(width/2)),
                    QPoint(x, y-(width/2)),
                    QPoint(x+(width/2), y),
                    QPoint(x, y+(width/2)),
                    QPoint(x-width/2, y+(width/2))
            };
            painter.drawPolygon(points1, 5, Qt::OddEvenFill);
        }
        else if (dir == Term::Direction::Out){
            QPoint points2[5] = {
                QPoint(x-(width/2), y),
                QPoint(x, y-(width/2)),
                QPoint(x+(width/2), y-(width/2)),
                QPoint(x+(width/2), y+(width/2)),
                QPoint(x, y+(width/2))
            };
            painter.drawPolygon(points2, 5, Qt::WindingFill);
        }
        painter.drawText(x - 10, y - 10, text);
    }


  void CellWidget::goLeft(){
    printf("position %d %d %d %d\n",viewport_.getX1(),viewport_.getY1(), viewport_.getX2(), viewport_.getY2());
    viewport_.translate(-20, 0);
    repaint();
  }

  void CellWidget::goRight(){
    printf("position %d %d %d %d\n",viewport_.getX1(),viewport_.getY1(), viewport_.getX2(), viewport_.getY2());
    viewport_.translate(20, 0);
    repaint();
  }

  void CellWidget::goUp(){
    printf("position %d %d %d %d\n",viewport_.getX1(),viewport_.getY1(), viewport_.getX2(), viewport_.getY2());
    viewport_.translate(0, 20);
    repaint();
  }

  void CellWidget::goDown(){
    printf("position %d %d %d %d\n",viewport_.getX1(),viewport_.getY1(), viewport_.getX2(), viewport_.getY2());
    viewport_.translate(0, -20);
    repaint();
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


  void CellWidget::query(Box& box) const {
    if(!cell_) return;
    box = Box(); // boite vide 

    // 1. Inclure 
    Symbol* sym = cell_->getSymbol();
    if (sym){
      printf("la cellule actuel %s possède un symbole que je dois afficher\n", cell_->getName().c_str());
      box.merge(sym->getBoundingBox());
    }

    // 2. Inclure les terminaux 
    for (Term* term : cell_->getTerms()){
      box.merge(Box(term->getPosition().getX(), term->getPosition().getY(), 
                    term->getPosition().getX(), term->getPosition().getY()));
    }

    // 3. Inclure toutes les instances
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
    
    if (box.isEmpty()) {
        // Si le circuit est vide, on met une vue par défaut
        viewport_ = Box(0, 0, 500, 500);
    } else {
        // On ajoute une petite marge de 10% autour du circuit
        box.inflate(10); 
        viewport_ = box;
    }
    
    update(); // Demande à Qt de redessiner le widget

  }
  
}  // Netlist namespace.








