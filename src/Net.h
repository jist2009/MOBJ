#ifndef NETLIST_NET_H
#define NETLIST_NET_H

#include "Term.h"
#include <string>
#include <vector>

namespace Netlist{

    class Cell;
    class Node;


    class Net {
    public : 
        Net (Cell*, const std::string&, Term::Type);
        ~Net ();

        // Prédicats et accesseurs
        Cell* getCell() const;
        const std::string& getName() const;
        unsigned int getId() const;
        Term::Type getType() const;
        const std::vector<Node*>& getNodes () const;
        size_t getFreeNodeId() const;

        // modificateurs
        void add (Node*);
        bool remove (Node*);


        // Exercice 2 
        void toXml(std::ostream& stream) const;
        static Net* fromXml(Cell*, xmlTextReaderPtr);

        // TME7
        inline const std::vector<Line*>& getLines () const;
        void add( Line* line);
        bool remove(Line* line);
        Node* getNode (size_t id) const;

    private :
        Cell* owner_;
        std::string name_;
        unsigned int id_;
        Term::Type type_;
        std::vector<Node*> nodes_;
        // TME7
        std::vector<Line*> lines_;
    };

    inline const std::vector<Line*>& Net::getLines() const 
    { return lines_; }
}

#endif