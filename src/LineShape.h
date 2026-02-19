// -*- explicit-buffer-name: "Cell.h<M1-MOBJ/7>" -*-

#ifndef NETLIST_LINESHAPE_H
#define NETLIST_LINESHAPE_H

#include <iostream>
#include <libxml/xmlreader.h>
#include "Box.h"
#include "Shape.h"
#include "Line.h"

namespace Netlist {

    class LineShape : public Shape {
        public :
            LineShape(Symbol* owner, int x1, int y1, int x2, int y2);
            virtual ~LineShape();
            
            // Accesseurs 
            virtual Box getBoundingBox() const;
            inline int getX1();
            inline int getY1();
            inline int getX2();
            inline int getY2();
            // Méthodes 
            virtual void toXml( std::ostream& ) const;
            static LineShape* fromXml (Symbol* owner, xmlTextReaderPtr reader);
        private :
            int x1_, y1_, x2_, y2_;
    };

    inline int LineShape::getX1(){return x1_;}
    inline int LineShape::getY1(){return y1_;}
    inline int LineShape::getX2(){return x2_;}
    inline int LineShape::getY2(){return y2_;}
}

#endif