#ifndef NETLIST_TERM_H
#define NETLIST_TERM_H

#include "Node.h"
#include "XmlUtil.h"
#include <libxml2/libxml/xmlreader.h>


namespace Netlist {

    class Instance ;
    class Cell;
    class Net;
    class Point;

    class Term{
    public :
    
    enum Type {Internal=1, External=2};
    enum Direction {In=1, Out=2, Inout=3, Tristate=4, Transcv=5, Unknown=6};

    //Constructeur 
    //Term peut appartenir à une cell ou à une Instance -> type_ sera déduite du constructeur appelé
    // Si le connecteur appartient à une Cell -> type= External, Instance -> type = Internal
    Term( Cell* , const std::string& name, Direction); 
    Term( Instance*, const Term* modelTerm);
   
    // Destructeur 
    ~Term();

    // Prédicats et accesseurs
    inline bool isInternal () const;
    inline bool isExternal () const;
    inline const std::string& getName() const;
    inline Node* getNode();
    inline Net* getNet() const;
    inline Cell* getCell() const;
    // Renvoie la Cell propriétaire : 
    // - soit celle directement si term externe 
    // - soit celle de l'instance si interne
    inline Cell* getOwnerCell() const;
    inline Instance* getInstance() const;
    inline Direction getDirection() const;
    inline Point getPosition() const;
    inline Type getType() const;

    // Modificateurs
    void setNet (Net*);
    void setNet (const std::string&);
    inline void setDirection(Direction);
    void setPosition(const Point&);
    void setPosition(int x,int y);

    static std::string toString(Type);
    static std::string toString(Direction);
    static Direction toDirection(std::string);

    void toXml(std::ostream& stream) const ;
    static Term* fromXml(Cell*, xmlTextReaderPtr);
    static Type toType(const std::string&);
    
    private : 
    void* owner_;
    std::string name_;
    Direction direction_;
    Type type_;
    Net* net_;
    NodeTerm node_;
    };



    // Prédicats et accesseurs
    inline  bool Term::isInternal () const  { return type_ == Internal; };
    inline  bool Term::isExternal () const { return type_ == External; };
    inline  const std::string& Term::getName() const {return name_; } ;
    inline Node* Term::getNode() { return &node_;};
    inline Net* Term::getNet() const { return net_; };
    // a mieux comprendre et voir d'autre solutions
    inline Cell* Term::getCell() const {return (type_==External) ? static_cast<Cell*>(owner_) : nullptr;};
    inline Instance* Term::getInstance() const { return (type_ == Internal) ? static_cast<Instance*>(owner_) : nullptr; };
    inline Term::Direction Term::getDirection() const {return direction_; };
    inline Point Term::getPosition() const { return node_.getPosition(); };
    inline Term::Type Term::getType() const { return type_;};

    // Modificateur
    inline void Term::setDirection(Direction direction) { direction_ = direction;}
}

#endif // NETLIST_TERM_H