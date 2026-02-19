// -*- explicit-buffer-name: "Cell.h<M1-MOBJ/7>" -*-

#ifndef __TERM_SHAPE_H__
#define __TERM_SHAPE_H__


#include <iostream>
#include <libxml/xmlreader.h>
#include "Shape.h"
#include "Symbol.h"
#include "Box.h"


namespace Netlist {

  class Term;

  class TermShape : public Shape {
    public:
                        TermShape      (Symbol* owner, Term* term, int x1, int y1, NameAlign align );
      virtual          ~TermShape      ();

      // Accesseurs
      Term* getTerm        () const;
      int               getX1          () const;
      int               getY1          () const;
      NameAlign         getAlign       () const;
      virtual Box       getBoundingBox () const;

      // Méthodes
      virtual void      toXml          ( std::ostream& ) const;
      static  TermShape* fromXml        ( Symbol* owner, xmlTextReaderPtr reader );
    private:
      Term* term_;
      int               x1_, y1_;
      NameAlign         align_;
  };

} 

#endif 