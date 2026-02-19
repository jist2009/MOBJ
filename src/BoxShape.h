// -*- explicit-buffer-name: "Cell.h<M1-MOBJ/7>" -*-

#ifndef NETLIST_BOXSHAPE_H
#define NETLIST_BOXhSHAPE_H

#include <iostream>
#include <libxml/xmlreader.h>
#include "Box.h"
#include "Shape.h"


namespace Netlist {

    class BoxShape : public Shape {
        public : 

            BoxShape(Symbol* owner, const Box&);
            virtual ~BoxShape();

            // Accesseurs 
            virtual Box getBoundingBox() const;

            // Méthodes 
            virtual void toXml(std::ostream&) const;
            static BoxShape* fromXml (Symbol* , xmlTextReaderPtr);

        private : 
            Symbol* owner_;
            Box box_;
        }; 
}

#endif 