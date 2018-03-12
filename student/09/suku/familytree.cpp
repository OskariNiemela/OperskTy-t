#include "familytree.hh"

Familytree::Familytree()
{

}

Familytree::~Familytree()
{

}


void Familytree::addNewPerson(const std::string &id, const int &height, std::ostream &output)
{

    if(data_.find(id)==data_.end())
    {
        Person* newPerson = new Person;
        newPerson->id_ = id;
        newPerson->height_= height;
        data_[id] = newPerson;
    }
    else
    {
        output<<"Error. Person already added."<<std::endl;
    }


}

void Familytree::printPersons(std::ostream &output) const
{

}

void Familytree::addRelation(const std::string &child, const std::vector<std::string> &parents, std::ostream &output)
{
    std::map<std::string,Person*>::iterator relations;
    relations = data_.find(child);

    Person* child_ptr=relations->second;

    Person* father_ptr(nullptr);
    relations = data_.find(parents.at(0));
    if(relations!=data_.end())
    {
        father_ptr = relations->second;
    }

    Person* mother_ptr(nullptr);
    relations = data_.find(parents.at(1));
    if(relations !=data_.end())
    {
        mother_ptr= relations->second;
    }

    if(father_ptr!=nullptr)
    {
        child_ptr->parents_.at(0) = father_ptr;
        father_ptr->children_.push_back(child_ptr);
    }

    if(mother_ptr!=nullptr)
    {
        child_ptr->parents_.at(1) = mother_ptr;
        mother_ptr->children_.push_back(child_ptr);
    }
}

void Familytree::printChildren(const std::string &id, std::ostream &output) const
{

}

void Familytree::printParents(const std::string &id, std::ostream &output) const
{

}

void Familytree::printSiblings(const std::string &id, std::ostream &output) const
{

}

void Familytree::printCousins(const std::string &id, std::ostream &output) const
{

}

void Familytree::printTallestInLineage(const std::string &id, std::ostream &output) const
{

}

void Familytree::printShortestInLineage(const std::string &id, std::ostream &output) const
{

}

void Familytree::printGrandChildrenN(const std::string &id, const int n, std::ostream &output) const
{

}

void Familytree::printGrandParentsN(const std::string &id, const int n, std::ostream &output) const
{

}


