#include "Term.h"
#include "Net.h"
#include "Instance.h"
#include "Cell.h"
#include "XmlUtil.h"
#include <libxml2/libxml/xmlreader.h>
#include "Node.h"
#include "Point.h"

// Bon j'ai des problèmes dans le code , reprendre le dernnier tp envoyé et chercké la diff
namespace Netlist{
    // Constructeurs
    //vision exterieur
    Term::Term(Cell* cell, const std::string& name, Direction direction):
        owner_((void*)cell), name_(name), direction_(direction),
        type_(External), net_(nullptr), node_(this)
        {
            // on vérifie si le owner_ est différent de null
            if (owner_) cell->add(this);
        }
    //vision intérieur 
    Term::Term(Instance* instance, const Term* modelTerm):
        owner_((void*)instance), 
        name_(modelTerm->getName()),
        direction_(modelTerm->getDirection()),
        type_(Internal), 
        net_(modelTerm->getNet()),
        node_(this) // Appel le constructeur Node(Term*)
        {
            instance->add(this);
        }

    
    // Destructeur 
    // node est lié à vie à un seul Term
    Term::~Term() {
        if(getCell()){
            Cell* owner = getCell();
            owner->remove(this);
        } else{
            Instance* owner = getInstance();
            owner->remove(this);
        }
        setNet(nullptr);
    }
    
    // Prédicats et accesseurs 
    // code présent dans Term.h

    // Modificateurs
    void Term::setNet(Net* net){
        if(net_ == net) {
            return ;
        }
        if(net_){
            net_->remove(&node_);
        } 
        net_ = net;
        if(net_){
            if(net_) net_->add(&node_);
        }
    }

    // name qui est le nom du net
    void Term::setNet(const std::string& name){
        if (!owner_) return ;
        Cell* cell = getCell();
        if (!cell) return;
        Net* net = cell->getNet(name);
        if (net) net_ = net;
    }

    void Term::setPosition(const Point& point) {
        node_.setPosition(point);
    }

    void Term::setPosition(int x, int y) {
        node_.setPosition(x, y);
    }


    std::string Term::toString(Term::Type type){
        switch (type) {
            case External: return "External";
            case Internal: return "Internal";
            default: return "Unknown";
        }
    }

    std::string Term::toString(Direction direction) {
        switch (direction) {
            case In: return "In";
            case Out: return "Out";
            case Inout: return "Inout";
            case Tristate: return "Tristate";
            case Transcv: return "Transcv";
            default: return "Unknown";
        }
    }

    Term::Direction Term::toDirection(std::string str) {
        if (str == "In") return In;
        if (str == "Out") return Out;
        if (str == "Inout") return Inout;
        if (str == "Tristate") return Tristate;
        if (str == "Transcv") return Transcv;
        return In; // Default fallback
    }

    Cell* Term::getOwnerCell() const {
        if(isExternal()){
            return getCell();
        }else {
            return getInstance()->getCell();
        }
    }


    void Term::toXml(std::ostream& stream) const {
        stream << indent << "<term name=\"" << name_
               << "\" direction=\"" << toString(direction_)
               << "\" x=" << node_.getPosition().getX()
               << "\" y=\"" << node_.getPosition().getY()
               << "\"/>"  << std::endl;
    }

    Term* Term::fromXml(Cell* owner, xmlTextReaderPtr reader) {
        
        const xmlChar* tag = xmlTextReaderConstLocalName(reader);
        if (xmlStrcmp(tag, BAD_CAST "term") != 0){
            std::cerr << "[Erreur] Term::fromXml(): expected <term>" << std::endl;
            return nullptr;
        }

        int x = 0, y = 0;

        xmlChar* attr;

        attr = xmlTextReaderGetAttribute(reader, BAD_CAST "name");
        std::string name = xmlCharToString(attr);

        attr = xmlTextReaderGetAttribute(reader, BAD_CAST "direction");
        std::string dirStr = xmlCharToString(attr);
        Direction direction = Term::toDirection(dirStr); 


        if(xmlGetIntAttribute(reader, "x", x)); // la fonction de free pas xmlChar
        if(xmlGetIntAttribute(reader, "y", y));

        Term* term = new Term(owner, name, direction);
        term->setPosition(x,y);

        return term;
    }   



    Term::Type Term::toType(const std::string& s){
        if (s == "Internal") return Internal;
        if (s == "External") return External;
        return Internal;
    }
}
