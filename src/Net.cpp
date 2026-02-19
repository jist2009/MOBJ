#include "Net.h"
#include "Cell.h" // nécessaire car il appel fonction de cell
#include "Node.h"
#include "Instance.h"
#include <algorithm>
#include "Line.h"
namespace Netlist{

    // constructeur
    Net::Net (Cell* cell, const std::string& name, Term::Type type):
        owner_(cell), name_(name), id_(cell->newNetId()), type_(type), nodes_() 
        {
            if(owner_){
                cell->add(this);
            }
        }

    // destructeur
    Net::~Net () {
        owner_->remove(this);
        for(size_t i=0; i<nodes_.size(); i++){
            nodes_[i] = nullptr;
        }
    }

    // Prédicats et accesseurs
    Cell* Net::getCell() const{
        return owner_;
    }

    const std::string& Net::getName() const{
        return name_;
    }

    unsigned int Net::getId() const{
        return id_;
    }

    Term::Type Net::getType() const{
        return type_;
    }

    const std::vector<Node*> & Net::getNodes () const{
        return nodes_;
    }

    size_t Net::getFreeNodeId() const{ 
        for (size_t i=0; i < nodes_.size(); i++){
            if(nodes_[i] == nullptr){
                return i;
            }
        }
        return nodes_.size();
    }

    // modificateurs
    void Net::add (Node* node){
        if(node){
            size_t id = node->getId();
            if (id == Node::noid){
                id = getFreeNodeId();
                node->setId(id);
            }
            if (id < nodes_.size()){
                if(nodes_[id] != NULL){
                    std::cerr << "Net::add [ERROR] In Net <" << name_
                    << "overwritten." << std::endl;
                    nodes_[id]->setId( Node::noid);
                }
                nodes_[id] = node;
            } else {
                for (size_t i = nodes_.size(); i < id; i++ ){
                    nodes_.push_back(NULL);
                }
                nodes_.push_back(node);
            }
        }
    }
    
    bool Net::remove (Node* node){
        std::vector<Node*>::iterator it = std::find(nodes_.begin(), nodes_.end(), node);
        if (it != nodes_.end()){
            nodes_.erase(it);
            return true;
        }
        return false;
    }


    void Net::toXml(std::ostream& stream) const {
        indent++;
        stream << indent << "<net name=\"" << name_
               << "\" type=\"" << Term::toString(type_)
               << "\"/>" << std::endl;

        indent++;
        for (Node* node : nodes_){
            if(node != nullptr){
                stream << indent;
                node->toXml(stream);
            } 
        }

        for (Line* line : lines_){
            if(line != nullptr){
                line->toXml(stream);
            }
        }
        indent--;
        stream << indent << "</net>" << std::endl;
        indent--;

    }

    Net* Net::fromXml(Cell* owner, xmlTextReaderPtr reader){

        // Première ligne  
        // vérifier si on est bien sur un net
        const xmlChar* tag = xmlTextReaderConstLocalName(reader);
        if (xmlStrcmp(tag, BAD_CAST "net") != 0){
            std::cerr << "[Erreur] Net::fromXml(): expected <net>" << std::endl;
            return nullptr;
        }
        std::string name, type_tmp;
        xmlChar* attr;

        attr = xmlTextReaderGetAttribute(reader, BAD_CAST "name");
        name = xmlCharToString(attr);

        attr = xmlTextReaderGetAttribute(reader, BAD_CAST "type");
        if (attr) {
            type_tmp = (char*) attr; 
            //xmlFree(attr); déjà enlevé dans le XUtil 
        }
        Term::Type type;
        if(type_tmp == "External") type = Term::External;
        else type = Term::Internal;

        Net* net = new Net(owner, name, type);

        const xmlChar* nodeTag = xmlTextReaderConstString( reader, (const xmlChar*)"node");
        const xmlChar* lineTag = xmlTextReaderConstString( reader, (const xmlChar*)"line");
        const xmlChar* netTag = xmlTextReaderConstString( reader, (const xmlChar*)"net");

        if(owner->getInstances().size()==0){
            std::cerr << "ERROR il y a 0 instances dans le cell" << std::endl;
        }
        while(true) {
            int status = xmlTextReaderRead(reader);
            if (status != 1) break;

            switch( xmlTextReaderNodeType(reader)){
                case XML_READER_TYPE_COMMENT:
                case XML_READER_TYPE_WHITESPACE:
                case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
                    continue;
            }

            const xmlChar* nodeName = xmlTextReaderConstLocalName(reader);

            if ( (nodeName == netTag ) && (xmlTextReaderNodeType(reader) ==XML_READER_TYPE_END_ELEMENT))
                break;
            
            // soit node ou line 
            if (XML_READER_TYPE_ELEMENT){
                if (nodeTag == nodeName){
                    Node::fromXml(net, reader);
                } else if (lineTag == nodeName){
                    Line::fromXml(net, reader);
                } else {
                    printf("perdu\n");
                }
                
                
            }
        }
        return net;
    }

    // TME 7 

    void Net::add (Line* line){ if (line) lines_.push_back(line);}

    bool Net::remove(Line* line){
        if(line){
            for (std::vector<Line*>::iterator il = lines_.begin(); il != lines_.end(); ++il ){
                if (*il == line){
                    lines_.erase(il);
                    return true;
                }
            }
        }
        return false;
    }

    Node* Net::getNode(size_t id) const {
        for(Node* node : nodes_){
            if (node)
                if(node->getId() == id) 
                    return node;
        }
        return nullptr;
    }
}