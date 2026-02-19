#include "Cell.h"
#include "Instance.h"
#include "Term.h"
//#include "Net.h" 
#include <algorithm>
#include "TermShape.h"

namespace Netlist{

    // Constructeur 
    Instance::Instance (Cell* owner, Cell* model, const std::string& name):
        owner_(owner), masterCell_(model), name_(name), terms_(), position_() 
        {
            const std::vector<Term*>& terms = masterCell_->getTerms();
            for (std::vector<Term*>::const_iterator iterm=terms.begin(); iterm != terms.end(); ++iterm){
                new Term(this, *iterm);
            }
            owner_->add(this);
        }
    
    // destructeur 
    Instance::~Instance(){
        owner_->remove(this);
        while (!terms_.empty()){
            Term* term = terms_.back();
            remove(term);
            delete term;

        }
        terms_.clear();
    }

    // Accesseurs 
    const std::string& Instance::getName() const{ return name_;}
    Cell* Instance::getMasterCell() const{ return masterCell_;}
    Cell* Instance::getCell() const{ return owner_;}

    const std::vector<Term*>& Instance::getTerms() const{ 
        return terms_;
    }

    Term* Instance::getTerm (const std::string& name) const{
        for(size_t i=0; i<terms_.size();i++){
            if(terms_[i]->getName() == name)
            return terms_[i]; 
        }
        return nullptr;
    }
    Point Instance::getPosition() const{
        return position_;
    }

    // Modificateurs
    bool Instance::connect (const std::string& name, Net* net){
        Term* term = getTerm(name);
        if (!term) return false;
        term->setNet(net);
        return true;
    }
    
    void Instance::add (Term* term){
        terms_.push_back(term);
    }

    void Instance::remove (Term* term){
        std::vector<Term*>::iterator it = std::find(terms_.begin(), terms_.end(), term);
        if (it != terms_.end()){
            terms_.erase(it);
        }
    }
    
    void Instance::setPosition( const Point& point){
        position_ = point;

        Symbol* symbol = masterCell_->getSymbol();

        if (symbol == nullptr) return;

        for (Term* instanceTerm : terms_){
            
            const std::string& termName = instanceTerm->getName();

            Term* modelTerm = masterCell_->getTerm(termName);

            if(modelTerm == nullptr) return;

            TermShape* termShape = symbol->getTermShape(modelTerm);

            if (termShape != nullptr){
                int shapeX = termShape->getX1();
                int shapeY = termShape->getX1();

                int newX = position_.getX() + shapeX;
                int newY = position_.getY() + shapeY;

                instanceTerm->setPosition(newX, newY);
                
            }
        }
    }

    void Instance::setPosition (int x, int y){
        position_.setX(x);
        position_.setY(y);
    }


    void Instance::toXml(std::ostream& stream) const {
        stream << "<instance name=\"" << name_
               << "\" mastercell=\"" << masterCell_->getName()
               << "\" x=\"" << position_.getX()
               << "\" y=\"" << position_.getY()
               << "\"/>" << std::endl;
    }

    Instance* Instance::fromXml(Cell* owner, xmlTextReaderPtr reader) {

        const xmlChar* tag = xmlTextReaderConstLocalName(reader);
        if (xmlStrcmp(tag, BAD_CAST "instance") != 0){
            std::cerr << "je renvoie l'erreur depuis instance.cpp" << std::endl;
            std::cerr << "[Erreur] instance::fromXml(): expected <instance>" << std::endl;
            return nullptr;
        }
        std::string name;
        std::string mastercellName;
        Cell* mastercell;
        int x=0, y=0;


        xmlChar* attr;

        attr = xmlTextReaderGetAttribute(reader, BAD_CAST "name");
        name = xmlCharToString(attr);

        attr = xmlTextReaderGetAttribute(reader, BAD_CAST "mastercell");
        mastercellName = xmlCharToString(attr);
        std::vector<Cell*>& vecteur = Cell::getAllCells();
        for (Cell* cell : vecteur){
            if(cell->getName() == mastercellName){
                mastercell = cell;
                break;
            }
        } 
        xmlGetIntAttribute(reader, "x", x);
        xmlGetIntAttribute(reader, "y", y);

        Instance* instance = new Instance(owner,mastercell, name);
        instance->setPosition(x,y);

        return instance;
    }
}
