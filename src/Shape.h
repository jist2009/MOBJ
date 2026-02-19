// -*- explicit-buffer-name: "Cell.h<M1-MOBJ/7>" -*-

#ifndef NETLIST_SHAPE_H
#define NETLIST_SHAPE_H

#include <iostream>
#include  <libxml/xmlreader.h>


namespace Netlist {
    
    class Symbol;
    class Box;

    class Shape {

        public : 
            // Types
            enum NameAlign {  TopLeft=1, TopRight, BottomLeft, BottomRight};

            //constructeur 
                    Shape(Symbol* owner);
            virtual ~Shape();

            // Accesseurs 
            virtual Box getBoundingBox() const = 0;

            // Méthodes
            virtual void toXml(std::ostream&) const = 0;
            static Shape* fromXml (Symbol* owner, xmlTextReaderPtr reader);

        protected : 
            Symbol* owner_;
            static NameAlign parseNameAlign (const std::string&);
            static std::string toString (NameAlign);
        };
}

#endif 