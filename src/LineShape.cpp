#include "LineShape.h"
#include "Symbol.h"
#include <algorithm> 
#include "XmlUtil.h"


namespace Netlist {

  LineShape::LineShape (Symbol* owner, int x1, int y1, int x2, int y2 )
    : Shape(owner), x1_( x1 ), y1_( y1 ), x2_( x2 ), y2_( y2 )
    {}

  LineShape::~LineShape ()
  {}

  Box LineShape::getBoundingBox () const
  {
    return Box( std::min(x1_, x2_), std::min(y1_, y2_), std::max(x1_, x2_), std::max(y1_, y2_) );
  }

  void LineShape::toXml ( std::ostream& stream ) const
  {
    stream  << indent << "<line x1=\"" << x1_
           << "\" y1=\"" << y1_
           << "\" x2=\"" << x2_
           << "\" y2=\"" << y2_ << "\"/>" << std::endl;
  }

  LineShape* LineShape::fromXml ( Symbol* owner, xmlTextReaderPtr reader )
  {
      int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

      const xmlChar* lineTag
          = xmlTextReaderConstString( reader, (const xmlChar*)"line" );
      const xmlChar* nodeName
          = xmlTextReaderConstLocalName( reader );

      if (lineTag != nodeName) {
          std::cerr << "[ERROR] LineShape::fromXml(): Expecting <line> tag, got <"
               << nodeName << "> (line:"
               << xmlTextReaderGetParserLineNumber(reader) << ")." << std::endl;
          return NULL;
      }

        if (!xmlGetIntAttribute( reader, "x1", x1)) return nullptr;
        if (!xmlGetIntAttribute( reader, "y1", y1)) return nullptr;
        if (!xmlGetIntAttribute( reader, "x2", x2)) return nullptr;
        if (!xmlGetIntAttribute( reader, "y2", y2)) return nullptr;
        

      return new LineShape(owner, x1, y1, x2, y2 );
  }

} 