#include "TermShape.h"
#include "Term.h"
#include "Cell.h" // Nécessaire pour Cell::getTerm(name) dans fromXml

using namespace std;

namespace Netlist {

  TermShape::TermShape (Symbol* owner, Term* term, int x1, int y1, NameAlign align )
    : Shape(owner), term_( term ), x1_( x1 ), y1_( y1 ), align_( align ){}

  TermShape::~TermShape (){}

  // Accesseurs
  Term* TermShape::getTerm () const
  { return term_; }

  int TermShape::getX1 () const
  { return x1_; }

  int TermShape::getY1 () const
  { return y1_; }

  Shape::NameAlign TermShape::getAlign () const
  { return align_; }

  // La Bounding Box est simplifiée à un point (le terminal) + la zone de texte du nom
  Box TermShape::getBoundingBox () const
  {
    // C'est une approximation, le tracé du nom du Term est ignoré pour simplifier
    return Box( x1_, y1_, x1_, y1_ );
  }

  void TermShape::toXml ( std::ostream& stream ) const
  {
    stream << indent << "<term name=\"" << term_->getName()
           << "\" x1=\"" << x1_
           << "\" y1=\"" << y1_
           << "\" align=\"" << Shape::toString( align_ ) << "\"/>" << endl;
  }

  TermShape* TermShape::fromXml ( Symbol* owner, xmlTextReaderPtr reader )
  {
      int x1 = 0, y1 = 0;
      NameAlign align = TopRight; 

      const xmlChar* termTag = xmlTextReaderConstString( reader, (const xmlChar*)"term" );
      const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );

      if (termTag != nodeName) {
          cerr << "[ERROR] TermShape::fromXml(): Expecting <term> tag, got <"
               << nodeName << "> (line:"
               << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;
          return NULL;
      }

      xmlChar* attr = xmlTextReaderGetAttribute(reader, BAD_CAST "name");
      std::string termName = xmlCharToString(attr);
     
      if (!xmlGetIntAttribute( reader, "x1", x1)) return nullptr;
      if (!xmlGetIntAttribute( reader, "y1", y1)) return nullptr;
      xmlChar* alignAttr = xmlTextReaderGetAttribute( reader, (const xmlChar*)"align" ) ;
      align = Shape::parseNameAlign( (const char*) alignAttr);
      xmlFree(alignAttr);
      // Conversion du nom du Term en pointeur Term*
      Term* term = owner->getCell()->getTerm( termName );
      if (term == NULL) {
          cerr << "[ERROR] TermShape::fromXml(): Unknown Term name: " << termName << " (line:"
               << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;
          return NULL;
      }

      return new TermShape(owner, term, x1, y1, align );
  }

} // Netlist