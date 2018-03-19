/*
#############################################################################
# TIE-02200 Ohjelmoinnin peruskurssi, K2018                                 #
# Project3: Suku on pahin                                                   #
# File: familytree.h                                                        #
# Description: Familytree-class datastructure                               #
#       Datastructure is populated with Person-structs and provides some    #
#       query-functions.                                                    #
# Notes: * This is a part of an exercise program                            #
#        * Student's aren't allowed to alter public interface!              #
#        * All changes to private side are allowed.                         #
#############################################################################
*/
#ifndef FAMILYTREE_H
#define FAMILYTREE_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <iostream>


// Named constants to improve readability in other modules.
const std::string NO_ID = "";
const int NO_HEIGHT = -1;

bool cmp_less(const int&a, const int&b);
bool cmp_more(const int&a, const int&b);
using compare = bool(*)(const int&,const int&);

// Struct for the persons data.
struct Person
{
    std::string id_ = NO_ID;
    int height_ = NO_HEIGHT;
    std::vector<Person*> parents_{nullptr, nullptr};
    std::vector<Person*> children_;
};


// We supply our own comparator so we can order the pointers correctly in sets
struct PersonPtrComp
{
  bool operator()(const Person* lhs, const Person* rhs) const  {
      return lhs->id_<rhs->id_;
  }
};

using Personmap = std::map<std::string, Person*>;

using Personset = std::set<Person*,PersonPtrComp>;
/*  Class: Familytree
 *  Description: Datastructure for Person-structs
 */
class Familytree
{
public:
    Familytree();
    ~Familytree();

    /* Description: Adds a new Person to the datastructure.
     * Parameters:
     *  Param1: Person's ID string
     *  Param2: Person's height
     *  Param3: Output-stream for error-printing
     * Errormessages:
     *  If person's ID is already in datastructure:
     *      "Error. Person already added."
     */
    void addNewPerson(const std::string& id, const int& height,
                      std::ostream &output);

    /* Description: Prints all stored Persons' IDs and heights
     * Parameters:
     *  Param1: Output-stream for printing
     * Errormessages:
     *  None.
     */
    void printPersons(std::ostream &output) const;



    /*
     * All the following functions have the same error messages:
     *  If ID wasn't found in datastructure:
     *      "Error. <ID> not found."
     *  If the printing list is empty:
     *      "Error. <ID> has no <group's name>."
     * -------------------------------------------------------------------
     */

    /* Description: Adds new parent-child relation
     * Parameters:
     *  Param1: ID of the child
     *  Param2: Vector containing the parents' IDs
     *  Param3: Output-stream for error-printing
     */
    void addRelation(const std::string& child,
                     const std::vector<std::string>& parents,
                     std::ostream& output);

    /* Description: Prints all children for the person.
     * Parameters:
     *  Param1: ID of the person
     *  Param2: Output-stream for printing
     */
    void printChildren(const std::string& id,
                       std::ostream& output) const;

    /* Description: Prints all the parents for the person.
     * Parameters:
     *  Param1: ID of the person
     *  Param2: Output-stream for printing
     */
    void printParents(const std::string& id,
                      std::ostream& output) const;

    /* Description: Prints all siblings for the person.
     *  (Persons who shares a parent)
     * Parameters:
     *  Param1: ID of the person
     *  Param2: Output-stream for printing
     */
    void printSiblings(const std::string& id,
                       std::ostream& output) const;

    /* Description: Prints all the cousins for the person.
     *  (Persons who share same grandparents)
     * Parameters:
     *  Param1: ID of the person
     *  Param2: Output-stream for printing
     */
    void printCousins(const std::string& id,
                      std::ostream& output) const;

    /* Description: Prints the tallest person of the ID's lineage.
     * Parameters:
     *  Param1: ID of the person
     *  Param2: Output-stream for printing
     */
    void printTallestInLineage(const std::string& id,
                               std::ostream& output) const;

    /* Description:
     * Parameters:
     *  Param1: ID of the person
     *  Param2: Output-stream for printing
     */
    void printShortestInLineage(const std::string& id,
                                std::ostream& output) const;


    /* The following functions have additional errormessage:
     *  If Param2's value is less than 1:
     *      "Error. Level can't be less than 1."
     * ---------------------------------------------------------------
     */


    /* Description: Prints the amount of grandchildren in given distance
     *  from the person.
     * Parameters:
     *  Param1: ID of the person
     *  Param2: Distance from the person. (n-1 times "grandness")
     *  Param3: Output-stream for printing
     */
    void printGrandChildrenN(const std::string& id, const int n,
                             std::ostream& output) const;

    /* Description: Prints the amount of grandparents in given distance
     *  from the person.
     * Parameters:
     *  Param1: ID of the person
     *  Param2: Distance from the person. (n-1 times "grandness")
     *  Param3: Output-stream for printing
     */
    void printGrandParentsN(const std::string& id, const int n,
                            std::ostream& output) const;

private:
    // Store all the people in this (std::map<std::string,Person*>) container
    Personmap data_;

    /* The following functions are meant to make project easier.
     * You can implement them if you want and/or create your own.
     * Anyway it would be a good idea to implement more functions
     * to make things easier and to avoid "copy-paste-coding"
     */

    /* Desc: gets the pointer that matches with the given id(name)
     * param0: name of the person we want to find
     * param1: the pointer well make point to the person we want
     *        if we cant find the person make point to nullptr
     *
     * return: returns if we find the given name (returns true)
     *        or if we dont find it (returns false)
     */
    bool getPointer(const std::string& id, Person* &point) const;

    /* Desc: goes recursively levels "down" the family tree, and adds all the children of the people at that level
     *      to the people set.
     *
     * param0: how many levels we want to go "up" or "down" positive numbers go down the children, negative numbers go up the parents
     * param1: pointer to the guy whose family tree were looking at.
     * param2: set where we're gonna gather all the pointers to the people we want to find
     * param3: which group of people (parents or children) to add to the people set, determines which vector of person pointers is added
     *        once the levels hits 0.
     */
    void get_recursive_level(int levels, Person* person, Personset &people, const std::vector<Person *> &people_to_add) const;

    /* Desc: Figures out who is the shortest person starting from the person we're given
     * param0: person whose lineage/height we want to check
     * param1: shortest person we've found so far
     * param2: whether we're searching for the tallest (true) or shortest (false)
     * param3: which is the tallest/shortest generation so far, needed in order to make sure
     *        that were getting the person closest in the lineage to the person we begun to check
     * param4: default value of 1 (the person whose lineage we check is 0) makes sure we know which
     *        generation of kids were looking at, and is used to change height_gen when necessary
     */
    void get_height(Person* person, Person* &height_person, compare comparator, int &height_gen, int current_gen =1) const;

    /* Desc: prints all the people in the set given according to the specifications given
     * param0: set of people we want to print
     * param1: output stream to print the people to
     * param2: the person whose relatives were printing out
     * param3: which relatives were printing out (ex. grandma, children, cousin, etc.)
     * param4: what suffix we want to use (used in printing grandchildren/parents, using the suffix "great-")
     * param5: how many generations away is this (used in printing grandchildren/parents
     */
    void print_people(Personset &people, std::ostream &output, Person *&print_to, std::string what, std::string suffix="", int amount=0) const;

    /* Desc: prints the no ID found error message
     * param0: the id/name of the person
     * param1: outputstream to print the message
     */
    void print_no_id(std::string name,std::ostream &output) const;
};

#endif // FAMILYTREE_H
