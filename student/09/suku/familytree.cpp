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
        std::shared_ptr<Person> newPerson(new Person);
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


