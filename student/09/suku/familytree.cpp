#include "familytree.hh"

Familytree::Familytree()
{

}

Familytree::~Familytree()
{
    for(std::map<std::string,Person*>::iterator people = data_.begin();people!=data_.end();people++)
    {
        delete people->second;
    }
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

    std::set<Person*> children_names;

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

    std::set<Person*> parents;

    if(!person_point)
    {
        output<<"error in children"<<std::endl;
        return;
    }



    get_recursive_level_up(0,person_point,parents);

    std::set<Person*> sibling;

    for(std::set<Person*>::iterator parent = parents.begin();parent!=parents.end();parent++)
    {
        get_recursive_level_down(0,*parent,sibling);
    }


    print_people(sibling,output);


}

void Familytree::printCousins(const std::string &id, std::ostream &output) const
{
    std::set<Person*> Granma;
    std::set<Person*> ParentsSiblings;


    Person* person_point = getPointer(id);

    if(!person_point)
    {
        output<<"error in children"<<std::endl;
        return;
    }

    //Get grandparents
    get_recursive_level_up(1,person_point,Granma);

    //Get grandparents's kids
    for(std::set<Person*>::iterator parent = Granma.begin();parent!=Granma.end();parent++)
    {
        get_recursive_level_down(0,*parent,ParentsSiblings);
    }


    if(person_point->parents_.at(0)!=nullptr)
    {
        ParentsSiblings.erase(person_point->parents_.at(0));
    }
    if(person_point->parents_.at(1)!=nullptr)
    {
        ParentsSiblings.erase(person_point->parents_.at(1));
    }

    std::set<Person*> cousins;

    //Get parents siblings kids
    for(std::set<Person*>::iterator parentsibling = ParentsSiblings.begin();parentsibling!=ParentsSiblings.end();parentsibling++)
    {
        get_recursive_level_down(0,*parentsibling,cousins);
    }

    print_people(cousins,output);

}

void Familytree::printTallestInLineage(const std::string &id, std::ostream &output) const
{
    Person* person_point = getPointer(id);
    Person* tallest_in_lineage = person_point;

    get_tallest(person_point,tallest_in_lineage);


    if(tallest_in_lineage==person_point)
    {
        output<<"With the height of "<< person_point->height_<<", "<< person_point->id_ << " is the tallest person in his/her lineage."<<std::endl;
    }
    else
    {
        output<<"With the height of "<<tallest_in_lineage->height_<<", ";
        output<< tallest_in_lineage->id_<< " is the tallest person in "<<person_point->id_<<"'s lineage."<<std::endl;
    }
}

void Familytree::printShortestInLineage(const std::string &id, std::ostream &output) const
{
    Person* person_point = getPointer(id);
    Person* shortest_in_lineage = person_point;

    get_shortest(person_point,shortest_in_lineage);

    if(shortest_in_lineage==person_point)
    {
        output<<"With the height of "<< person_point->height_<<", "<< person_point->id_ << " is the shortest person in his/her lineage."<<std::endl;
    }
    else
    {
        output<<"With the height of "<<shortest_in_lineage->height_<<", ";
        output<< shortest_in_lineage->id_<< " is the shortest person in "<<person_point->id_<<"'s lineage."<<std::endl;
    }
}

void Familytree::printGrandChildrenN(const std::string &id, const int n, std::ostream &output) const
{

    Person* person_point = getPointer(id);
    std::set<Person*> grandDad;

    if(n>0)
    {
        get_recursive_level_down(n,person_point,grandDad);
    }

    print_people(grandDad,output);
}

void Familytree::printGrandParentsN(const std::string &id, const int n, std::ostream &output) const
{
    Person* person_point = getPointer(id);
    std::set<Person*> grandDad;

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


void Familytree::get_recursive_level_up(int levels, Person* guy, std::set<Person *> &people) const
{
    if(guy!=nullptr)
    {
        if(levels==0)
        {
            if(guy->parents_.at(0)!=nullptr)
            {
                people.insert(guy->parents_.at(0));
            }
            if(guy->parents_.at(1)!=nullptr)
            {
                people.insert(guy->parents_.at(1));
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

void Familytree::get_recursive_level_down(int levels, Person *guy, std::set<Person *> &people) const
{
    if(levels==0)
    {
        if(guy->children_.size()>0)
        {
            people.insert(guy->children_.begin(),guy->children_.end());
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

void Familytree::get_tallest(Person *person, Person *&tallest) const
{
    if(person->height_ > tallest->height_)
    {
        tallest = person;
    }


    if(person->children_.size()>0)
    {
        for(std::vector<Person*>::const_iterator person_it = person->children_.begin();person_it!=person->children_.end();person_it++)
        {
            get_tallest(*person_it,tallest);
        }
    }


}

void Familytree::get_shortest(Person *person, Person *&shortest) const
{
    if(person->height_ < shortest->height_)
    {
        shortest = person;
    }


    if(person->children_.size()>0)
    {
        for(std::vector<Person*>::const_iterator person_it = person->children_.begin();person_it!=person->children_.end();person_it++)
        {
            get_shortest(*person_it,shortest);
        }
    }
}

void Familytree::print_people(std::set<Person *> people,std::ostream &output) const
{
    Person* waht;
    for(std::set<Person*>::const_iterator person = people.begin();person!=people.end();person++)
    {
        waht = *person;
        output<<waht->id_<<std::endl;
    }

}



