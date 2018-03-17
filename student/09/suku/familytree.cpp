/*
#############################################################################
# TIE-02200 Ohjelmoinnin peruskurssi, K2018                             #
# Project3: Suku on pahin                                             #
# Project Coder : Oskari Niemela                                       #
# Student Number: 263440                                              #
# File: familytree.cpp                                                #
# Description: contains methods for the familytree class                 #
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

/* Desc: Adds a new person to our people map
 * param0: id, the name of the new person
 * param1: height, the height to give the new person
 * param2: the output stream we'll use to print any errors
 */
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

/* Desc: prints all the people in our people map
 * param0: output stream to print any errors
 */
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

/* Desc: adds the parent/child relationships to the people
 * param0: name of child
 * param1: name of parent(s)
 * param2: output stream to print any errors
 */
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

/* Desc: prints the children of the given person
 * param0: name of person
 * param1: output stream to print names/errors
 */
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

/* Desc: prints the parents of the given person
 * param0: name of the person
 * param1: output stream to print names/errors
 */
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

/* Desc: prints the siblings of the given person
 * param0: name of the person
 * param1: outputstream to print names/errors
 */
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

/* Desc: prints the cousins of the given person
 * param0: name of the person
 * param1: outputstream to print names/errors
 *
 * Gets the grandparents of the given person, gets all the grandparents children
 * deletes the parents of the given person, then just gets all the children
 * of the parents siblings and prints their names.
 */
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

/* Desc: prints the tallest person starting from the person given and going down the familial relations,
 * param0: name of the person
 * param1: output stream to print names/errors
 */
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

/* Desc: prints the shortest person starting from the person given and going down the familial relations,
 * param0: name of the person
 * param1: output stream to print names/errors
 */
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

/* Desc: prints the great-*(n-1)grandchildren of the given person
 * param0: the name of the person
 * param1: the amount of generations to go down (1=grandchildren, 2=great-grandchildren, etc)
 * param2: output stream to print names/errors
 */
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

/* Desc: prints the great-*(n-1)grandparents of the given person
 * param0: the name of the person
 * param1: the amount of generations to go down (1=grandchildren, 2=great-grandchildren, etc)
 * param2: output stream to print names/errors
 */
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

    get_recursive_level(-n,person_point,grandDad,person_point->parents_);

    print_people(grandDad,output,person_point,"grandparents","great-",n);
}

/* Desc: gets the pointer that matches with the given id(name)
 * param0: name of the person we want to find
 * param1: the pointer well make point to the person we want
 *        if we cant find the person make point to nullptr
 *
 * return: returns if we find the given name (returns true)
 *        or if we dont find it (returns false)
 */
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

/* Desc: goes recursively levels "down" the family tree, and adds all the children of the people at that level
 *      to the people set.
 *
 * param0: how many levels we want to go "up" or "down" positive numbers go down the children, negative numbers go up the parents
 * param1: pointer to the guy whose family tree were looking at.
 * param2: set where we're gonna gather all the pointers to the people we want to find
 * param3: which group of people (parents or children) to add to the people set, determines which vector of person pointers is added
 *        once the levels hits 0.
 */
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

/* Desc: Figures out who is the shortest person starting from the person we're given
 * param0: person whose lineage/height we want to check
 * param1: shortest person we've found so far
 * param2: whether we're searching for the tallest (true) or shortest (false)
 * param3: which is the tallest/shortest generation so far, needed in order to make sure
 *        that were getting the person closest in the lineage to the person we begun to check
 * param4: default value of 1 (the person whose lineage we check is 0) makes sure we know which
 *        generation of kids were looking at, and is used to change height_gen when necessary
 */
void Familytree::get_height(Person *person, Person *&height_person, compare comparator, int &height_gen, int current_gen) const
{

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

/* Desc: prints all the people in the set given according to the specifications given
 * param0: set of people we want to print
 * param1: output stream to print the people to
 * param2: the person whose relatives were printing out
 * param3: which relatives were printing out (ex. grandma, children, cousin, etc.)
 * param4: what suffix we want to use (used in printing grandchildren/parents, using the suffix "great-")
 * param5: how many generations away is this (used in printing grandchildren/parents
 */
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
