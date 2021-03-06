/*
#############################################################################
# TIE-02200 Ohjelmoinnin peruskurssi, K2018                             #
# Project3: Suku on pahin                                             #
# Project Coder : Oskari Niemela                                       #
# Student Number: 263440                                              #
# File: familytree.cpp                                                #
# Description: contains method definitions for the familytree class       #
#############################################################################
*/

#include "familytree.hh"

// Comparison functions to help with figuring out the tallest/shortest of a lineage
bool cmp_less(const int &a, const int &b)
{
    return a<b;
}
bool cmp_more(const int &a, const int &b)
{
    return a>b;
}

//Constructor
Familytree::Familytree()
{
    //There are no values we need to give default values to, so were not gonna
}

//Destructor
Familytree::~Familytree()
{
    //Go through the map of the people and delete the structs at the end of the pointers
    for(std::map<std::string,Person*>::iterator people = data_.begin();people!=data_.end();people++)
    {
        delete people->second;
    }
}

void Familytree::addNewPerson(const std::string &id, const int &height, std::ostream &output)
{
    //Check if there already is a person with that name in the map
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
    Person* child_ptr=nullptr;
    if(not getPointer(child,child_ptr))
    {
        print_no_id(child,output);
        return;
    }

    Person* father_ptr=nullptr;
    Person* mother_ptr=nullptr;

    if(getPointer(parents.at(0),father_ptr))
    {
        child_ptr->parents_.at(0) = father_ptr;
        father_ptr->children_.push_back(child_ptr);
    }

    if(getPointer(parents.at(1),mother_ptr))
    {
        child_ptr->parents_.at(1) = mother_ptr;
        mother_ptr->children_.push_back(child_ptr);
    }
}

void Familytree::printChildren(const std::string &id, std::ostream &output) const
{
    Person* person_point=nullptr;
    if(not getPointer(id,person_point))
    {
        print_no_id(id,output);
        return;
    }

    // Person pointers get compared with the PersonPtrComp so they
    // get ordered by the Person ids
    Personset children_names;
    get_recursive_level(0,person_point,children_names,person_point->children_);

    print_people(children_names,output,person_point,"children");
}

void Familytree::printParents(const std::string &id, std::ostream &output) const
{
    Person* person_point=nullptr;
    if(not getPointer(id,person_point))
    {
        print_no_id(id,output);
        return;
    }

    Personset parents;

    get_recursive_level(0,person_point,parents,person_point->parents_);

    print_people(parents,output,person_point,"parents");
}

void Familytree::printSiblings(const std::string &id, std::ostream &output) const
{
    Person* person_point=nullptr;
    if(not getPointer(id,person_point))
    {
        print_no_id(id,output);
        return;
    }

    Personset parents;
    get_recursive_level(0,person_point,parents,person_point->parents_);

    Personset sibling;

    // Go through the parents and get all their children into a set.
    for(Person* person_it:parents)
    {
        get_recursive_level(0,person_it,sibling,person_it->children_);
    }

    // Erase the person whose siblings we wish to print, since they cant be their own sibling.
    sibling.erase(person_point);

    print_people(sibling,output,person_point,"siblings");
}

void Familytree::printCousins(const std::string &id, std::ostream &output) const
{
    Person* person_point=nullptr;
    if(not getPointer(id,person_point))
    {
        print_no_id(id,output);
        return;
    }

    //Set up the sets well be needing
    Personset Grandparents;
    Personset ParentsSiblings;

    //Get grandparents
    get_recursive_level(-1,person_point,Grandparents,person_point->parents_);

    //Get grandparents's kids
    for(Person* person_it:Grandparents)
    {
        get_recursive_level(0,person_it,ParentsSiblings,person_it->children_);
    }

    // Erase the parents of the given person from the set, so were left with just the parents siblings.
    if(person_point->parents_.at(0)!=nullptr)
    {
        ParentsSiblings.erase(person_point->parents_.at(0));
    }
    if(person_point->parents_.at(1)!=nullptr)
    {
        ParentsSiblings.erase(person_point->parents_.at(1));
    }

    Personset cousins;

    //Get parents siblings kids
    for(Person* parentsibling:ParentsSiblings)
    {
        get_recursive_level(0,parentsibling,cousins,parentsibling->children_);
    }

    print_people(cousins,output,person_point,"cousins");
}

void Familytree::printTallestInLineage(const std::string &id, std::ostream &output) const
{
    Person* person_point=nullptr;
    if(not getPointer(id,person_point))
    {
        print_no_id(id,output);
        return;
    }

    Person* tallest_in_lineage = person_point;
    int tallest_gen =0;
    if(person_point->children_.size()>0)
    {
        // finds the tallest person from the person given and makes tallest_in_lineage point to it
        get_height(person_point,tallest_in_lineage,cmp_more,tallest_gen);
    }

    // Two options with different printouts: either the given person is the tallest or someone else is.
    if(tallest_gen == 0)
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
    Person* person_point=nullptr;
    if(not getPointer(id,person_point))
    {
        print_no_id(id,output);
        return;
    }

    Person* shortest_in_lineage = person_point;
    int shortest_gen = 0;
    if(person_point->children_.size()>0)
    {
        //Finds the shortest person from lineage and makes shortest_in_lineage point to it
        get_height(person_point,shortest_in_lineage,cmp_less,shortest_gen);
    }

    // Either the given person is the shortest or its someone else, these require different printouts
    if(shortest_gen==0)
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
    if(n<=0)
    {
        output<<"Error. Level can't be less than 1."<<std::endl;
        return;
    }

    Person* person_point=nullptr;
    if(not getPointer(id,person_point))
    {
        print_no_id(id,output);
        return;
    }

    Personset grandDad;

    get_recursive_level(n,person_point,grandDad,person_point->children_);

    print_people(grandDad,output,person_point,"grandchildren","great-",n);
}

void Familytree::printGrandParentsN(const std::string &id, const int n, std::ostream &output) const
{
    if(n<=0)
    {
        output<<"Error. Level can't be less than 1."<<std::endl;
        return;
    }

    Person* person_point=nullptr;
    if(not getPointer(id,person_point))
    {
        print_no_id(id,output);
        return;
    }

    Personset grandDad;

    // -n since we're going "up" the family tree by n generations
    get_recursive_level(-n,person_point,grandDad,person_point->parents_);

    print_people(grandDad,output,person_point,"grandparents","great-",n);
}

bool Familytree::getPointer(const std::string &id, Person* &point) const
{
    try
    {
        point = data_.at(id);
        return true;
    }
    catch(std::out_of_range)
    {
        point = nullptr;
        return false;
    }
}

void Familytree::get_recursive_level(int levels, Person *person, Personset &people, const std::vector<Person*> &people_to_add) const
{
    // If we're at the level we want to be
    if(levels==0)
    {
        // If the person we're checking has children, add them to the set
        for(Person* person_it:people_to_add)
        {
            if(person_it!=nullptr)
            {
                people.insert(person_it);
            }
        }
    }
    else
    {
        // Since positive levels means we're going up, we need to iterate through the children of the person
        // and also provide the childrens children as the reference vector
        if(levels>0)
        {
            for(Person* person_it:person->children_)
            {
                if(person_it!=nullptr)
                {
                    get_recursive_level(levels-1,person_it,people,person_it->children_);
                }
            }
        }
        // If the levels are not positive, and not 0 then we go through the persons parents and provide their parents parents as
        // the vector of people we need to take into our set.
        else
        {
            for(Person* person_it:person->parents_)
            {
                if(person_it!=nullptr)
                {
                    get_recursive_level(levels+1,person_it,people,person_it->parents_);
                }
            }
        }

    }
}

void Familytree::get_height(Person *person, Person *&height_person, compare comparator, int &height_gen, int current_gen) const
{
    // Comparator is automatically the one we want since its provided as a parameter for this function. The other options is that the persons
    // height that we're currently checking is the same as the height_person who is the shortest/tallest, and if the person we're checking
    // is from an older generation, we change the height_person to point to the current person being checked.
    if(comparator(person->height_, height_person->height_)||((current_gen<height_gen)&&(person->height_==height_person->height_)))
    {
        height_person = person;
        height_gen = current_gen;
    }

    // call this function on all the children of the person we're checking (if any found)
    if(person->children_.size()>0)
    {
        for(Person* person_it:person->children_)
        {
            get_height(person_it,height_person,comparator,height_gen,current_gen+1);
        }
    }
}


void Familytree::print_people(Personset &people, std::ostream &output, Person* &print_to, std::string what, std::string suffix, int amount) const
{
    int suffix_amount=0;
    if(suffix!="")
    {
        //The first of the suffixes is replaced with the word grand in grandparent and grandchildren
        //so well delete one of them before beginning the print
        suffix_amount = amount-1;
    }

    // We couldn't find any relatives for this person
    if(people.size()==0)
    {
        output<<print_to->id_<<" has no ";

        // Print the appropriate amount of suffixes (ex. great-great-great-grandmother), it there is a suffix given
        while(suffix_amount>0)
        {
           output<<suffix;
           suffix_amount--;
        }

        output<<what<<"."<<std::endl;
        return;
    }

    output<<print_to->id_<<" has "<<people.size()<<" ";

    // While this code is repeated twice, the prints before and after it are different, and I dont think
    // making a new function for 3 lines of code is really necessary so I repeated it here.
    while(suffix_amount>0)
    {
       output<<suffix;
       suffix_amount--;
    }
    output<<what<<":"<<std::endl;

    for(Person* person:people)
    {
        output<<person->id_<<std::endl;
    }

}

void Familytree::print_no_id(std::string name, std::ostream &output) const
{
   output<<"Error. "<<name<<" not found."<<std::endl;
}
