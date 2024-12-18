#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "processing.h"
#include "AVL.h"
using namespace std;

int main()
{
    //create tree
    AVL tree;

	//read in number of commands
    int command_num;
    cin >> command_num;
    cin.ignore(); //bug when command_num was 1

    //iterate through and ensure validation
    for (int i = 0; i < command_num; i++)
    {
        string input;
        getline(cin, input);

        //process command one by one
        cout << processCommand(input, tree) << endl;
    }
	return 0;
}
