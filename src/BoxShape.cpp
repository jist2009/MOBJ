#include "BoxShape.h"
#include "Symbol.h"
#include "XmlUtil.h"

namespace Netlist {

    BoxShape::BoxShape(Symbol* owner, const Box& box)
        : Shape(owner), owner_(owner), box_(box)
        { if(owner_!= NULL) owner_->add(this);}
    
    BoxShape::~BoxShape(){
          if(owner_ != NULL) owner_->remove(this);}

    Box BoxShape::getBoundingBox() const 
    {
        return box_;
    }

    void BoxShape::toXml ( std::ostream& stream ) const
    {
        stream << indent << "<box x1=\"" << box_.getX1()
                << "\" y1=\"" << box_.getY1()
                << "\" x2=\"" << box_.getX2()
                << "\" y2=\"" << box_.getY2() << "\"/>" << std::endl;
    }

    BoxShape* BoxShape::fromXml( Symbol* owner, xmlTextReaderPtr reader)
    {
        int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

        const xmlChar* boxTag = xmlTextReaderConstString( reader, (const xmlChar*)"box");
        const xmlChar* nodeName = xmlTextReaderConstLocalName(reader);

        if (boxTag != nodeName) {
            std::cerr << "[ERROR] BoxShape::fromXml(): Expecting <box> tag, got <"
                << nodeName << "> (line:"
                << xmlTextReaderGetParserLineNumber(reader) << ")." << std::endl;
            return NULL;
        }

        if (!xmlGetIntAttribute( reader, "x1", x1)) return nullptr;
        if (!xmlGetIntAttribute( reader, "y1", y1)) return nullptr;
        if (!xmlGetIntAttribute( reader, "x2", x2)) return nullptr;
        if (!xmlGetIntAttribute( reader, "y2", y2)) return nullptr;
        

        return new BoxShape(owner, Box( x1, y1, x2, y2 ) );
    }
}