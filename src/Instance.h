#ifndef NETLIST_INSTANCE_H
#define NETLIST_INSTANCE_H

#include "Cell.h"
#include "Point.h"
#include "XmlUtil.h"
class Term;

namespace Netlist{
    class Instance{
        public :
        // Constructeur 
        Instance (Cell* owner, Cell* model, const std::string&);
        ~Instance();

        // Accesseurs 
        const std::string& getName() const;
        Cell* getMasterCell() const;
        Cell* getCell() const;
        const std::vector<Term*>& getTerms() const;
        Term* getTerm (const std::string&) const;
        Point getPosition() const;

        // Modificateurs
        bool connect (const std::string& name, Net*);
        void add (Term*);
        void remove (Term*);
        void setPosition( const Point&);
        void setPosition (int x, int y);

        // execice 2
        void toXml(std::ostream& stream) const;
        static Instance* fromXml(Cell*, xmlTextReaderPtr);

        private :
        Cell* owner_;
        Cell* masterCell_;
        std::string name_;
        std::vector<Term*> terms_;
        Point position_;
    };
}

#endif
