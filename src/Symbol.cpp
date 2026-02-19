// -*- explicit-buffer-name: "Box.cpp<M1-MOBJ/7>" -*-

#include "Symbol.h"
#include "Shape.h"
#include <algorithm> // pour std::find
#include "TermShape.h"
#include "Cell.h"

namespace Netlist {

    Symbol::Symbol(Cell* owner)
    : owner_(owner), shapes_() // le vecteur est créer automatiquement 
    {}

    Symbol::~Symbol(){
        // Il est mauvais de coder   for(Shape* shape : shapes_) remove(shape);
        for (Shape* shape: shapes_)
            delete shape;
    }

    Cell* Symbol::getCell() const{
        return owner_;
    }

    Box Symbol::getBoundingBox() const {
        Box b;
        for(size_t i=0; i<shapes_.size() ; i++){
            b.merge(shapes_[i]->getBoundingBox());
        }
        return b;
    }

    void Symbol::add(Shape* shape){
        std::vector<Shape*>::iterator ishape = std::find(shapes_.begin(), shapes_.end(), shape); 
        if (ishape == shapes_.end())
            shapes_.push_back(shape);
    }

    void Symbol::remove(Shape* shape){
        std::vector<Shape*>::iterator it = std::find(shapes_.begin(), shapes_.end(), shape);
        if (it != shapes_.end()){
            shapes_.erase(it);
        }
    }

    TermShape* Symbol::getTermShape( Term* modelTerm) const
    {
        for(Shape* shape : shapes_){
            TermShape* termShape = dynamic_cast<TermShape*>(shape);

            if(termShape!= nullptr){
                if(termShape->getTerm() == modelTerm){
                    return termShape;
                }
            }
        }
        return nullptr;
    }

    Point Symbol::getTermPosition( Term* modelTerm) const
    {
        TermShape* termShape = getTermShape(modelTerm);

        if(termShape != nullptr){
            return Point(termShape->getX1(), termShape->getY1());
        }
        return Point(0,0);
    }

    void Symbol::toXml(std::ostream& stream) const{
        stream << indent++ << "<symbol>\n";
        for(Shape* shape : shapes_){
            shape->toXml(stream);
        }
        stream << --indent << "</symbol>\n";

    }
    
    Symbol* Symbol::fromXml(Cell* owner, xmlTextReaderPtr reader){
        
        const xmlChar* tag = xmlTextReaderConstLocalName(reader);
        if (xmlStrcmp(tag, BAD_CAST "symbol") != 0){
            std::cerr << "[Erreur] Symbol::fromXml(): expected <symbol>" << std::endl;
            return nullptr;
        }

        Symbol* symbol = owner->getSymbol();
        

        const xmlChar* symbolTag = xmlTextReaderConstString( reader, (const xmlChar*)"symbol");

        while(true) {
            int status = xmlTextReaderRead(reader);
            if (status != 1) break;
            
            const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );

            switch( xmlTextReaderNodeType(reader)){
                case XML_READER_TYPE_COMMENT:
                case XML_READER_TYPE_WHITESPACE:
                case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
                    continue;

                case XML_READER_TYPE_END_ELEMENT:
                    if( nodeName == symbolTag)
                        goto fin;
                    break;
                
                case XML_READER_TYPE_ELEMENT:
                    if(Shape::fromXml(symbol, reader)){
                        continue;
                    }else {
                        break ;
                    }
                    break;                
            }
        }
        fin:
        return symbol;

    }

}