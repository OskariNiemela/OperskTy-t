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
    std::map<std::string,Person*>::const_iterator people;
    people = data_.begin();

    while(people!=data_.end())
    {
        output<<people->first<<", "<<people->second->height_<<std::endl;
        people++;
    }
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

    child_ptr->parents_.at(0) = father_ptr;

    if(father_ptr!=nullptr)
    {

        father_ptr->children_.push_back(child_ptr);
    }

    child_ptr->parents_.at(1) = mother_ptr;
    if(mother_ptr!=nullptr)
    {

        mother_ptr->children_.push_back(child_ptr);
    }

    output<<"What am i supposed to put here ?"<<std::endl;
}

void Familytree::printChildren(const std::string &id, std::ostream &output) const
{
    Person* person_point;
    try
    {
        person_point = data_.at(id);
    }
    catch(std::out_of_range)
    {
        output<<"Error. id not found";
        return;
    }


    std::set<std::string> children_names;

    get_children(person_point,children_names);


    if(children_names.size()>0)
    {
        std::set<std::string>::iterator child;
        child = children_names.begin();

        while(child!=children_names.end())
        {
            output<<*child<<std::endl;
            child++;
        }
    }
    else
    {
        output<<"Error. "<<id<<" has no children"<<std::endl;
    }

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

void Familytree::get_children(const Person* person, std::set<std::string> &children) const
{
    std::vector<Person*>::const_iterator child_it;
    child_it = person->children_.begin();
    Person const *waht;
    while(child_it!=person->children_.end())
    {
        waht = *child_it;
        children.insert(waht->id_);

        child_it++;
    }
}


