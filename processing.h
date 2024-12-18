//
// Created by Tyler on 9/14/2024.
//
#ifndef PROJECT1_PROCESSING_H
#define PROJECT1_PROCESSING_H
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "AVL.h"
using namespace std;

//to ensure call is valid
bool isCommandValid(string& command_function)
{
    //returns true if valid
    return (command_function == "insert" || command_function == "remove" || command_function == "search"
            || command_function == "printInorder" || command_function == "printPreorder" ||
            command_function == "printPostorder" || command_function == "printLevelCount"
            || command_function == "removeInorder");
}
//to ensure name is valid
bool isNameValid(string& name)
{
    bool validity = true;

    //loop through string checking constraints
    for (char c : name)
    {
        if (!isalpha(c) && c != ' ')
        {
            validity = false;
            break;
        }
    }
    return validity;
}
//to ensure id is valid
bool isIdValid(string& id)
{
    //link for all_of explanation: https://cplusplus.com/reference/algorithm/all_of/
    return (id.size() == 8 && all_of(id.begin(), id.end(), ::isdigit));
}
//process the given commands
string processCommand(const string& input, AVL& tree)
{
    if (input.empty())
    {
        return "unsuccessful";
    }

    //ensure function call is valid
    string command_function = input.substr(0, input.find(' '));
    if (!isCommandValid(command_function))
    {
        return "unsuccessful";
    }

    //check respective commands
    if (command_function == "insert")
    {
        //extract the next step for validation
        string next_input = input.substr(input.find(' ') + 1);
        string in_quotes = next_input.substr(next_input.find('"'));
        string potential_name = in_quotes.substr(1, in_quotes.rfind('"') - 1);

        //validate name
        if (!isNameValid(potential_name))
        {
            return "unsuccessful";
        }

        //validate id
        string potential_id = next_input.substr(next_input.rfind(' ') + 1);
        if (!isIdValid(potential_id))
        {
            return "unsuccessful";
        }

        //create id for tree, then insert using the root
        int id = stoi(potential_id);
        tree.setRoot(tree.insert(tree.getRoot(), id, potential_name));
    }

    else if (command_function == "remove")
    {
        string next_input = input.substr(input.find(' ') + 1);

        if (!isIdValid(next_input))
        {
            return "unsuccessful";
        }

        else
        {
            int potential_id = stoi(next_input);
            tree.setRoot(tree.remove(tree.getRoot(), potential_id));
        }
    }

    else if (command_function == "search")
    {
        string next_input = input.substr(input.find(' ') + 1);

        //if search name, validate name
        if (next_input.front() == '"')
        {
            string in_quotes = next_input.substr(next_input.find('"'));
            string potential_name = in_quotes.substr(1, in_quotes.size() - 2);

            if (!isNameValid(potential_name) || tree.getRoot() == nullptr)
            {
                return "unsuccessful";
            }

            else
            {
                tree.searchName(tree.getRoot(), potential_name);
            }
        }

        //else validate search id
        else
        {
            if (!isIdValid(next_input))
            {
                return "unsuccessful";
            }

            else
            {
                tree.searchID(tree.getRoot(), stoi(next_input));
            }
        }
    }

    else if (command_function == "removeInorder")
    {
        string next_input = input.substr(input.find(' ') + 1);

        //ensure that the next_input is a valid integer
        try
        {
            int N = stoi(next_input);
            if (N < 0) return "unsuccessful";
            tree.setRoot(tree.removeInorder(tree.getRoot(), N));
        }

        catch (invalid_argument&) {return "unsuccessful";}
    }

    else if (command_function == "printInorder")
    {
        tree.printInorder();
    }

    else if (command_function == "printPreorder")
    {
        tree.printPreorder();
    }

    else if (command_function == "printPostorder")
    {
        tree.printPostorder();
    }

    else if (command_function == "printLevelCount")
    {
        tree.printLevelCount();
    }

    return "";
}

#endif //PROJECT1_PROCESSING_H