#include "Shape.h"
#include "Symbol.h"
#include "BoxShape.h"
#include "LineShape.h"
#include "TermShape.h"

using namespace std;

namespace Netlist {

    Shape::Shape (Symbol* owner)
    : owner_(owner)
    {
        if (owner_ != nullptr) { // <--- AJOUTER CETTE VÉRIFICATION
            owner_->add(this);
        } else {
            // Optionnel : gérer l'erreur, par exemple, jeter une exception.
            std::cerr << "ERREUR FATALE: Tentative de construire une Shape sans Symbol propriétaire." << std::endl;
        }
    }

    Shape::~Shape (){
        owner_->remove(this);
    }

    Shape::NameAlign Shape::parseNameAlign ( const std::string& str )
    {
        if (str == "top_left")     return TopLeft;
        if (str == "top_right")    return TopRight;
        if (str == "bottom_left")  return BottomLeft;
        if (str == "bottom_right") return BottomRight;
        return TopLeft; // Valeur par défaut si non reconnue
    }

    std::string Shape::toString ( NameAlign align )
    {
        switch (align) {
            case TopLeft:     return "top_left";
            case TopRight:    return "top_right";
            case BottomLeft:  return "bottom_left";
            case BottomRight: return "bottom_right";
        }
        return "";
    }

    // Factory Method 
    Shape* Shape::fromXml ( Symbol* owner, xmlTextReaderPtr reader )
    {
        const xmlChar* boxTag
            = xmlTextReaderConstString( reader, (const xmlChar*)"box" );
        //const xmlChar* ellipseTag
        //    = xmlTextReaderConstString( reader, (const xmlChar*)"ellipse" );
        //const xmlChar* arcTag
        //    = xmlTextReaderConstString( reader, (const xmlChar*)"arc" );
        const xmlChar* lineTag
            = xmlTextReaderConstString( reader, (const xmlChar*)"line" );
        const xmlChar* termTag
            = xmlTextReaderConstString( reader, (const xmlChar*)"term" );
        const xmlChar* nodeName
            = xmlTextReaderConstLocalName( reader );

        Shape* shape = NULL;
        if (boxTag == nodeName){
            shape = BoxShape::fromXml( owner, reader );

        }
        // if (ellipseTag == nodeName)
        //   shape = EllipseShape::fromXml( owner, reader );
        // if (arcTag == nodeName)
        //   shape = ArcShape::fromXml( owner, reader );
        if (lineTag == nodeName){
            shape = LineShape::fromXml( owner, reader );
        
        }
        if (termTag == nodeName){
            shape = TermShape::fromXml( owner, reader );

        }
        if (shape == NULL)
            cerr << "[ERROR] Unknown or misplaced tag <" << nodeName << "> (line:"
                << xmlTextReaderGetParserLineNumber(reader) << ")." << endl;

    return shape;
    }

}