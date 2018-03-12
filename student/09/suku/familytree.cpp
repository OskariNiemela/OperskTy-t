#include "familytree.hh"

Familytree::Familytree()
{

}

Familytree::~Familytree()
{

}

bool operator<(const Person& a, const Person& b)
{
    return a.id_ < b.id_;
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
    Person* person_point = getPointer(id);

    if(!person_point)
    {
        output<<"error in children"<<std::endl;
        return;
    }

    std::vector<Person*> children_names;

    get_recursive_level_down(0,person_point,children_names);


    if(children_names.size()>0)
    {
        print_people(children_names,output);
    }
    else
    {
        output<<"Error. "<<id<<" has no children"<<std::endl;
    }

}

void Familytree::printParents(const std::string &id, std::ostream &output) const
{
    Person* person_point = getPointer(id);

    if(!person_point)
    {
        output<<"error in children"<<std::endl;
        return;
    }

    std::vector<Person*>::const_iterator parents = person_point->parents_.begin();
    Person const *waht;

    while(parents!=person_point->parents_.end())
    {
        waht = *parents;
        if(waht!=nullptr)
        {
            output<<waht->id_<<std::endl;
        }
        parents++;
    }
}

void Familytree::printSiblings(const std::string &id, std::ostream &output) const
{
    Person* person_point = getPointer(id);

    std::vector<Person*> parents;

    if(!person_point)
    {
        output<<"error in children"<<std::endl;
        return;
    }



    get_recursive_level_up(0,person_point,parents);

    std::vector<Person*> sibling;

    for(std::vector<Person*>::iterator parent = parents.begin();parent!=parents.end();parent++)
    {
        get_recursive_level_down(0,*parent,sibling);
    }

    delete_vec_value(person_point,sibling);

    print_people(sibling,output);


}

void Familytree::printCousins(const std::string &id, std::ostream &output) const
{
    std::vector<Person*> Granma;
    std::vector<Person*> ParentsSiblings;
    std::set<Person*>Parentssib;

    Person* person_point = getPointer(id);

    if(!person_point)
    {
        output<<"error in children"<<std::endl;
        return;
    }

    //Get grandparents
    get_recursive_level_up(1,person_point,Granma);

    //Get grandparents's kids
    for(std::vector<Person*>::iterator parent = Granma.begin();parent!=Granma.end();parent++)
    {
        get_recursive_level_down(0,*parent,ParentsSiblings);
    }

    for(std::vector<Person*>::iterator parentsibling = ParentsSiblings.begin();parentsibling!=ParentsSiblings.end();parentsibling++)
    {
        Parentssib.insert(*parentsibling);
    }


    if(person_point->parents_.at(0)!=nullptr)
    {
        Parentssib.erase(person_point->parents_.at(0));
    }
    if(person_point->parents_.at(1)!=nullptr)
    {
        Parentssib.erase(person_point->parents_.at(1));
    }

    std::vector<Person*> cousins;

    //Get parents siblings kids
    for(std::set<Person*>::iterator parentsibling = Parentssib.begin();parentsibling!=Parentssib.end();parentsibling++)
    {
        get_recursive_level_down(0,*parentsibling,cousins);
    }

    print_people(cousins,output);

}

void Familytree::printTallestInLineage(const std::string &id, std::ostream &output) const
{

}

void Familytree::printShortestInLineage(const std::string &id, std::ostream &output) const
{

}

void Familytree::printGrandChildrenN(const std::string &id, const int n, std::ostream &output) const
{

    Person* person_point = getPointer(id);
    std::vector<Person*> grandDad;

    if(n>0)
    {
        get_recursive_level_down(n,person_point,grandDad);
    }

    print_people(grandDad,output);
}

void Familytree::printGrandParentsN(const std::string &id, const int n, std::ostream &output) const
{
    Person* person_point = getPointer(id);
    std::vector<Person*> grandDad;

    if(n>0)
    {
        get_recursive_level_up(n,person_point,grandDad);
    }

    print_people(grandDad,output);
}

Person *Familytree::getPointer(const std::string &id) const
{
    Person* person_point;
    try
    {
        person_point = data_.at(id);
        return person_point;
    }
    catch(std::out_of_range)
    {
        return nullptr;
    }
}


void Familytree::get_recursive_level_up(int levels, Person* guy, std::vector<Person *> &people) const
{
    if(guy!=nullptr)
    {
        if(levels==0)
        {
            if(guy->parents_.at(0)!=nullptr)
            {
                people.push_back(guy->parents_.at(0));
            }
            if(guy->parents_.at(1)!=nullptr)
            {
                people.push_back(guy->parents_.at(1));
            }

        }
        else
        {
            if(guy->parents_.at(0)!=nullptr)
            {
                get_recursive_level_up(levels-1,guy->parents_.at(0),people);
            }
            if(guy->parents_.at(1)!=nullptr)
            {
                get_recursive_level_up(levels-1,guy->parents_.at(1),people);
            }


        }
    }
}

void Familytree::get_recursive_level_down(int levels, Person *guy, std::vector<Person *> &people) const
{
    if(levels==0)
    {
        if(guy->children_.size()>0)
        {
            people.insert(people.end(),guy->children_.begin(),guy->children_.end());
        }
    }
    else
    {
        if(guy->children_.size()>0)
        {
            for(std::vector<Person*>::const_iterator person_it = guy->children_.begin();person_it!=guy->children_.end();person_it++)
            {
                get_recursive_level_down(levels-1,*person_it,people);
            }
        }
    }
}

void Familytree::print_people(std::vector<Person *> people,std::ostream &output) const
{

    Person const *waht;
    std::set<std::string> names;

    for(std::vector<Person*>::const_iterator person_it = people.begin();person_it!=people.end();person_it++)
    {
        waht = *person_it;
        names.insert(waht->id_);
    }

    for(std::set<std::string>::const_iterator names_it=names.begin();names_it!=names.end();names_it++)
    {
        output<<*names_it<<std::endl;
    }


}

void Familytree::delete_vec_value(Person* value, std::vector<Person *>& people) const
{
    Person const *waht;
    for(std::vector<Person*>::const_iterator vec_value = people.begin();vec_value!=people.end();vec_value++)
    {
        waht = *vec_value;
        if(value->id_ == waht->id_)
        {
            people.erase(vec_value);
            break;
        }
    }
}

bool Familytree::is_name_in(Person *value, std::vector<Person *> &people) const
{
    Person const *waht;
    for(std::vector<Person*>::const_iterator vec_value = people.begin();vec_value!=people.end();vec_value++)
    {
        waht = *vec_value;
        if(value->id_ == waht->id_)
        {
            return true;
        }
    }
    return false;
}

