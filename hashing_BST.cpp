/********************************************************************************************

Name: Kyle Scales    Z#: Z23334750
Course: Data Structures and Algorithm Analysis (COP3530)
Professor: Dr. Lofton Bullard
Due Date: 11/23/2015           Due Time: 5:00pm
Total Points: 100
Assignment 7: BST and Hash Table

Description: This file contains the implementation for the Clients_Info_BST class and the
Client_Address_Book class

Clients_Info_BST is a BST class, while Client_Address_Book is a hash table with each element
being a Clients_Info_BST object. Client_Address_Book holds and maintains an address book.

*********************************************************************************************/
#include <fstream>
#include "hashing_BST.h"

//Description: Default constructor for the Clients_Info_BST class
//Precondition: Object must not currently exist
//Postcondition: Empty BST is created with its root = NULL
Clients_Info_BST::Clients_Info_BST()
{
    root = NULL;
}

//Description: Copy constructor for the Clients_Info_BST class, calls Copy_Aux
//Precondition: Calling object must not currently exist, object being copied must exist
//Postcondition: Calling object is an exact but independent copy of the passed object
Clients_Info_BST::Clients_Info_BST(const Clients_Info_BST & original)
{
    Copy_Aux(root, original.root);
}

//Description: Allows copying to be done recursively
//Precondition: Calling object must not currently exist, object being copied must exist. newtree should be the root of
// the tree being created, and original should be the root of the tree to be copied
//Postcondition: Calling object is an exact but independent copy of the passed object
void Clients_Info_BST::Copy_Aux(BST_Node * & newtree, const BST_Node * original)
{
    if(original != NULL)
    {
        newtree = new BST_Node;
        newtree->firstname = original->firstname;
        newtree->lastname = original->lastname;
        newtree->address = original->address;
        newtree->phone_number = original->phone_number;
        Copy_Aux(newtree->lchild, original->lchild);
        Copy_Aux(newtree->rchild, original->rchild);
    }
    else
        newtree = NULL;
}

//Description: Destructor for the Clients_Info_BST class
//Precondition: Calling object exists
//Postcondition: Memory for calling object is de-allocated
Clients_Info_BST::~Clients_Info_BST()
{
    while(root != NULL)
        Remove(root, root->lastname + " " + root->firstname);
}

//Description: Adds client information into the BST, calls another version of Insert
//Precondition: String passed must be in format of "LastName FirstName Address PhoneNumber" and have > 8 characters
// There must be no spaces within LastName or FirstName and PhoneNumber must be in the form xxx-xxxx
//Postcondition: Node has been inserted into the BST in order
void Clients_Info_BST::Insert(const string & s)
{

    if(s.length() > 8)
        Insert(root, s);
}

//Description: Called by Insert function above, allows insertion to be done recursively
//Precondition: String passed must be in format of "LastName FirstName Address PhoneNumber". There must be no spaces
// within LastName or FirstName and PhoneNumber must be in the form xxx-xxxx
//location_ptr should be the root of the tree in which the item is to be inserted.
//Postcondition: Node has been inserted into the BST in order
void Clients_Info_BST::Insert(BST_Node * & location_ptr, string item)
{
    string temp, last, first, address, phone, lastfirst;

    //parses string to variables
    temp = item;
    phone = temp.substr(temp.length()-8);
    temp.erase(temp.length() - 9);
    last = temp.substr(0, temp.find_first_of(" "));
    temp.erase(0, temp.find_first_of(" ") + 1);
    first = temp.substr(0, temp.find_first_of(" "));
    temp.erase(0, temp.find_first_of(" ") + 1);
    address = temp;
    lastfirst = last + first;

    if(location_ptr == NULL)                        //case for an empty tree
    {

        location_ptr = new BST_Node;
        location_ptr->lastname = last;
        location_ptr->firstname = first;
        location_ptr->address = address;
        location_ptr->phone_number = phone;
        location_ptr->lchild = NULL;
        location_ptr->rchild = NULL;
    }
    else if(lastfirst > (location_ptr->lastname + location_ptr->firstname)) //recursive call with right child if item
                                                                            //to insert is greater
    {
        Insert(location_ptr->rchild,item);
    }
    else if(lastfirst < (location_ptr->lastname + location_ptr->firstname)) //recursive call with left child if item
                                                                            //to insert is less than
    {
        Insert(location_ptr->lchild,item);
    }
    else                                                                    //can not insert if record already exists
    {
        cout << "Can't insert duplicates" << endl;
    }
}

//Description: Removes node with the Last and First name passed from the BST
//Precondition: String passed must be in format of "LastName FirstName" There must be no spaces within LastName or
// FirstName
//Postcondition: Node has been removed from the BST if it exists, otherwise a message is printed to standard output
void Clients_Info_BST::Remove(const string & s)
{
    Remove(root, s);
}

//Description: Called by Remove function above, allows removal to be done recursively, calls Inorder_Succ
//Precondition: loc_ptr should be the root of the tree where the item is located. String passed must be in format of
// "LastName FirstName" There must be no spaces within LastName or FirstName
//Postcondition: Node has been removed from the BST if it exists, otherwise a message is printed to standard output
void Clients_Info_BST::Remove(BST_Node * & loc_ptr, string item)
{
    if(loc_ptr == NULL)
    {
        cout << "Record not in the tree" << endl;
    }
    else if(item > (loc_ptr->lastname + " " + loc_ptr->firstname))
    {
        Remove(loc_ptr->rchild, item);
    }
    else if(item < (loc_ptr->lastname + " " + loc_ptr->firstname))
    {
        Remove(loc_ptr->lchild, item);
    }
    else
    {
        if(loc_ptr->lchild == NULL && loc_ptr->rchild == NULL)
        {
            BST_Node * removeNode = loc_ptr;
            loc_ptr = NULL;
            delete removeNode;
        }
        else if(loc_ptr->lchild == NULL && loc_ptr->rchild != NULL)
        {
            BST_Node * removeNode = loc_ptr;
            loc_ptr = loc_ptr->rchild;
            delete removeNode;
        }
        else if(loc_ptr->lchild != NULL && loc_ptr->rchild == NULL)
        {
            BST_Node * removeNode = loc_ptr;
            loc_ptr = loc_ptr->lchild;
            delete removeNode;
        }
        else
        {
            BST_Node * inorderSucc = Inorder_Succ(loc_ptr);
            loc_ptr->firstname = inorderSucc->firstname;
            loc_ptr->lastname = inorderSucc->lastname;
            loc_ptr->address = inorderSucc->address;
            loc_ptr->phone_number = inorderSucc->phone_number;
            Remove(loc_ptr->rchild, (inorderSucc->lastname + " " + inorderSucc->firstname));
        }
    }
}

//Description: Called by Remove function above, locates the inorder successor for the node the passed pointer refers to
//Precondition: location should be a pointer to the node for which you want to find the inorder successor
//Postcondition: Returns a pointer to the inorder successor of the node if located, otherwise returns NULL
BST_Node * Clients_Info_BST::Inorder_Succ(BST_Node * location)
{
    BST_Node *loc_fore = location->rchild;
    while(loc_fore->lchild != NULL)
    {
        loc_fore = loc_fore->lchild;
    }
    return loc_fore;
}

//Description: Updates a record already existing in the BST depending on the string passed
//Precondition: String passed ***MUST*** be one of the following variations, where the number is the option you choose,
// and Last First are the Last & First names of the record you wish to change:
/* (1 Last First NewLast NewFirst NewAddress NewPhone) Changes all information
 * (2 Last First NewLast NewFirst NewAddress) Changes last and first name and address
 * (3 Last First NewAddress NewPhone) Changes address and phone
 * (4 Last First NewLast NewFirst NewPhone) Changes last and first name and phone
 * (5 Last First NewLast NewFirst) Changes last and first name
 * (6 Last First NewAddress) Changes address
 * (7 Last First NewPhone) Changes phone
//Postcondition: Node has been updated according to the choices above, if the node isn't found, a message is printed*/
void Clients_Info_BST::Update(string & s)
{

    int option = stoi(s.substr(0,1));
    s.erase(0,2);
    string last = s.substr(0, s.find_first_of(" "));
    s.erase(0, s.find_first_of(" ") + 1);
    string first = s.substr(0, s.find_first_of(" "));
    s.erase(0, s.find_first_of(" ") + 1);

    string newLast, newFirst, newPhone, newAddress;

    BST_Node * origRecord = Search(last + " " + first);
    if(origRecord == NULL)
    {
        cout << "Record Not Found" << endl;
        return;
    }

    switch(option) {
        case 1: //all fields replaced
            newLast = s.substr(0, s.find_first_of(" "));
            s.erase(0, s.find_first_of(" ") + 1);
            newFirst = s.substr(0, s.find_first_of(" "));
            s.erase(0, s.find_first_of(" ") + 1);
            newPhone = s.substr(s.length()-8);
            s.erase(s.length() - 9);
            newAddress = s;

            Remove(last + " " + first);
            Insert(newLast + " " + newFirst + " " + newAddress + " " + newPhone);
            break;

        case 2: //name and address changed
            newLast = s.substr(0, s.find_first_of(" "));
            s.erase(0, s.find_first_of(" ") + 1);
            newFirst = s.substr(0, s.find_first_of(" "));
            s.erase(0, s.find_first_of(" ") + 1);
            newAddress = s;
            newPhone = origRecord->phone_number;

            Remove(last + " " + first);
            Insert(newLast + " " + newFirst + " " + newAddress + " " + newPhone);
            break;

        case 3: //address and phone changed
            newPhone = s.substr(s.length()-8);
            s.erase(s.length() - 9);
            newAddress = s;

            origRecord->phone_number = newPhone;
            origRecord->address = newAddress;
            break;

        case 4: //name and phone changed
            newLast = s.substr(0, s.find_first_of(" "));
            s.erase(0, s.find_first_of(" ") + 1);
            newFirst = s.substr(0, s.find_first_of(" "));
            s.erase(0, s.find_first_of(" ") + 1);
            newPhone = s;
            newAddress = origRecord->address;

            Remove(last + " " + first);
            Insert(newLast + " " + newFirst + " " + newAddress + " " + newPhone);
            break;

        case 5: //only name changed
            newLast = s.substr(0, s.find_first_of(" "));
            s.erase(0, s.find_first_of(" ") + 1);
            newFirst = s;
            newAddress = origRecord->address;
            newPhone = origRecord->phone_number;

            Remove(last + " " + first);
            Insert(newLast + " " + newFirst + " " + newAddress + " " + newPhone);
            break;

        case 6: //only address changed
            origRecord->address = s;
            break;

        case 7: //only phone changed
            origRecord->phone_number = s;
            break;

        default:
            cout << "Not a valid update option" << endl;
    }

}


//Description: Prints the BST, in order, to standard output, calls Print function below
//Precondition: Calling object must exist
//Postcondition: BST is printed to the screen in order
void Clients_Info_BST::Print( )
{
    Print(root);
}

//Description: Prints the BST, in order, to standard output, allows print to be done recursively
//Precondition: Calling object must exist
//Postcondition: BST is printed to the screen in order
void Clients_Info_BST::Print(BST_Node * & location_ptr)
{
    cout.setf(ios::left, ios::adjustfield);
    if(location_ptr != NULL)
    {
        Print(location_ptr->lchild);
        cout.width(20);
        cout << location_ptr->lastname;
        cout.width(20);
        cout << location_ptr->firstname;
        cout.width(35);
        cout << location_ptr->address;
        cout.width(8);
        cout << location_ptr->phone_number << endl;
        Print(location_ptr->rchild);
    }
}

//Description: Prints the BST to a file in order, calls print helper function below
//Precondition: Calling object exists, file stream has been opened and passed to this function
//Postcondition: The BST has been printed to the file stream in order
void Clients_Info_BST::Print(ostream & output)
{
    Print(root, output);
}

//Description: Prints the BST to a file in order, called by print above, function allows for use of recursion
//Precondition: Calling object exists, file stream has been opened and passed to this function
//Postcondition: The BST has been printed to the file stream in order
void Clients_Info_BST::Print(BST_Node * & location_ptr, ostream & output)
{
    output.setf(ios::left, ios::adjustfield);
    if(location_ptr != NULL)
    {
        Print(location_ptr->lchild, output);
        output.width(20);
        output << location_ptr->lastname;
        output.width(20);
        output << location_ptr->firstname;
        output.width(35);
        output << location_ptr->address;
        output.width(8);
        output << location_ptr->phone_number << endl;
        Print(location_ptr->rchild, output);
    }
}

//Description: Returns a pointer to the node searched for if it exists in the BST, a pointer to NULL otherwise
// Calls the Search function below to execute the search recursively
//Precondition: Calling object must exist, string passed is in the form "LastName FirstName" with no spaces within
// the first or last name fields
//Postcondition: Returns a pointer to the node if found, returns pointer to NULL otherwise
BST_Node * Clients_Info_BST::Search(const string & s)
{
    return Search(root, s);
}

//Description: Returns a pointer to the node searched for if it exists in the BST, a pointer to NULL otherwise
// Called by the Search function above to execute the search recursively
//Precondition: Calling object must exist, string passed is in the form "LastName FirstName" with no spaces within
// the first or last name fields
//Postcondition: Returns a pointer to the node if found, returns pointer to NULL otherwise
BST_Node * Clients_Info_BST::Search(BST_Node * location_ptr, string item)
{
    if(location_ptr != NULL)
    {
        if((location_ptr->lastname + " " + location_ptr->firstname) == item)
        {
            return location_ptr;
        }
        else if(item < (location_ptr->lastname + " " + location_ptr->firstname))
            return Search(location_ptr->lchild, item);
        else if(item > (location_ptr->lastname + " " + location_ptr->firstname))
            return Search(location_ptr->rchild, item);
    }
    else
        return NULL;
}

void Clients_Info_BST::operator=(const Clients_Info_BST & original)
{
    Copy_Aux(root, original.root);
}


















//Description: Default constructor for the Client_Address_Book class
//Precondition: Object must not currently exist
//Postcondition: capacity is set to 26, a hash table is created with 26 elements, with each element being a
// Clients_Info_BST object. BSTs are populated with data read from "client_address_data.txt"
// Records are inserted using Hash_Function to determine which BST to insert into, and
// the Clients_Info_BST Insert function to insert the records
Client_Address_Book::Client_Address_Book()
{
    capacity = 26;
    hash_table = new Clients_Info_BST[capacity];

    string row;
    ifstream addressData;
    addressData.open ("client_address_data.txt");
    if (addressData.fail())
    {
        cout << "***COULD NOT CONNECT TO FILE***";
        exit(1);
    }
    while(!addressData.eof())
    {
        getline(addressData, row);
        hash_table[Hash_Function(row)].Insert(row);
    }
    addressData.close();
}


//Description: Copy constructor for the Client_Address_Book class
//Precondition: Calling object must not currently exist, object being copied must exist
//Postcondition: Hash table is created with 26 elements, each element being a Clients_Info_BST object.
// Calling object becomes an exact but independent copy of the passed object
Client_Address_Book::Client_Address_Book(const Client_Address_Book & original)
{
    capacity = 26;
    hash_table = new Clients_Info_BST[capacity];

    for(int i = 0; i < capacity; i++)
        hash_table[i] = original.hash_table[i];

}

//Description: Destructor for the Client_Address_Book class
//Precondition: Calling object exists
//Postcondition: Memory for calling object (including BSTs) is de-allocated
Client_Address_Book::~Client_Address_Book()
{
    delete [] hash_table;
}

//Description: Inserts a record into the Client_Address_Book object. BST inserted into is determined by the
// Hash_Function, once BST to insert into is identified, Clients_Info_BST's Insert function is used to insert
//Precondition: String passed must be in format of "LastName FirstName Address PhoneNumber". There must be no spaces
// within LastName or FirstName and PhoneNumber must be in the form xxx-xxxx. All fields must be given.
//Postcondition: Node has been inserted into the corresponding BST, in order
void Client_Address_Book::Insert(const string & s)
{
    hash_table[Hash_Function(s)].Insert(s);
}

//Description: Removes record from the Client_Address_Book object. BST removed from is determined by the Hash_Function
// and removal is handled by Clients_Info_BST's Remove function
//Precondition: String passed must be in format of "LastName FirstName" There must be no spaces within
// LastName or FirstName
//Postcondition: Node has been removed from the BST if it exists, otherwise a message is printed to standard output
void Client_Address_Book::Remove(const string & s)
{
    hash_table[Hash_Function(s)].Remove(s);
}

//Description: Updates a record already existing in the hash table depending on the string passed. This function
// uses the Clients_Info_BST class's Search, Remove, and Insert functions to locate the node to update, remove it, and
//re-insert the updated record
//Precondition: String passed ***MUST*** be one of the following variations, where the number is the option you choose,
// and Last First are the Last & First names of the record you wish to change:
/* (1 Last First NewLast NewFirst NewAddress NewPhone) Changes all information
 * (2 Last First NewLast NewFirst NewAddress) Changes last and first name and address
 * (3 Last First NewAddress NewPhone) Changes address and phone
 * (4 Last First NewLast NewFirst NewPhone) Changes last and first name and phone
 * (5 Last First NewLast NewFirst) Changes last and first name
 * (6 Last First NewAddress) Changes address
 * (7 Last First NewPhone) Changes phone
//Postcondition: Node has been updated according to the choices above, if the node isn't found, a message is printed*/
void Client_Address_Book::Update(string s)
{
    int option = stoi(s.substr(0,1));
    s.erase(0,2);
    string last = s.substr(0, s.find_first_of(" "));
    s.erase(0, s.find_first_of(" ") + 1);
    string first = s.substr(0, s.find_first_of(" "));
    s.erase(0, s.find_first_of(" ") + 1);

    string newLast, newFirst, newPhone, newAddress;

    BST_Node * origRecord = hash_table[Hash_Function(last)].Search(last + " " + first);
    if(origRecord == NULL)
    {
        cout << "Record Not Found" << endl;
        return;
    }

    switch(option) {
        case 1: //all fields replaced
            newLast = s.substr(0, s.find_first_of(" "));
            s.erase(0, s.find_first_of(" ") + 1);
            newFirst = s.substr(0, s.find_first_of(" "));
            s.erase(0, s.find_first_of(" ") + 1);
            newPhone = s.substr(s.length() - 8);
            s.erase(s.length() - 9);
            newAddress = s;

            Remove(last + " " + first);
            Insert(newLast + " " + newFirst + " " + newAddress + " " + newPhone);
            break;

        case 2: //name and address changed
            newLast = s.substr(0, s.find_first_of(" "));
            s.erase(0, s.find_first_of(" ") + 1);
            newFirst = s.substr(0, s.find_first_of(" "));
            s.erase(0, s.find_first_of(" ") + 1);
            newAddress = s;
            newPhone = origRecord->phone_number;

            Remove(last + " " + first);
            Insert(newLast + " " + newFirst + " " + newAddress + " " + newPhone);
            break;

        case 3: //address and phone changed
            newPhone = s.substr(s.length() - 8);
            s.erase(s.length() - 9);
            newAddress = s;

            origRecord->phone_number = newPhone;
            origRecord->address = newAddress;
            break;

        case 4: //name and phone changed
            newLast = s.substr(0, s.find_first_of(" "));
            s.erase(0, s.find_first_of(" ") + 1);
            newFirst = s.substr(0, s.find_first_of(" "));
            s.erase(0, s.find_first_of(" ") + 1);
            newPhone = s;
            newAddress = origRecord->address;

            Remove(last + " " + first);
            Insert(newLast + " " + newFirst + " " + newAddress + " " + newPhone);
            break;

        case 5: //only name changed
            newLast = s.substr(0, s.find_first_of(" "));
            s.erase(0, s.find_first_of(" ") + 1);
            newFirst = s;
            newAddress = origRecord->address;
            newPhone = origRecord->phone_number;

            Remove(last + " " + first);
            Insert(newLast + " " + newFirst + " " + newAddress + " " + newPhone);
            break;

        case 6: //only address changed
            origRecord->address = s;
            break;

        case 7: //only phone changed
            origRecord->phone_number = s;
            break;

        default:
            cout << "Not a valid update option" << endl;
    }
}

//Description: Prints all records in the Address Book that begin with the first letter of the string passed,
// in order, to standard output, calls Clients_Info_BST's Print function
//Precondition: Calling object must exist
//Postcondition: BST containing records is printed to the screen in order, with column headers
void Client_Address_Book::Print_BST(const string & s)
{
    cout.setf(ios::left, ios::adjustfield);
    cout.width(20);
    cout << "LAST NAME";
    cout.width(20);
    cout << "FIRST NAME";
    cout.width(35);
    cout << "ADDRESS";
    cout.width(8);
    cout << "PHONE NUMBER" << endl;
    hash_table[Hash_Function(s)].Print();
}

//Description: Prints all records in the Address Book, in order, to standard output,
// calls Clients_Info_BST's Print function
//Precondition: Calling object must exist
//Postcondition: BST containing records is printed to the screen in order, with column headers
void Client_Address_Book::Print_Hash_Table()
{
    cout.setf(ios::left, ios::adjustfield);
    cout.width(20);
    cout << "LAST NAME";
    cout.width(20);
    cout << "FIRST NAME";
    cout.width(35);
    cout << "ADDRESS";
    cout.width(8);
    cout << "PHONE NUMBER" << endl;
    for(int i = 0; i < capacity; i++)
        hash_table[i].Print();
}

//Description: Prints all records in the Address Book, in order, to the filename passed as an argument
// calls Clients_Info_BST's Print function
//Precondition: Calling object must exist
//Postcondition: BST containing records is printed to the file, with column headers, file is created if it doesnt
// currently exist
void Client_Address_Book::Print_Hash_Table_to_File(const string & filename)
{
    ofstream outputFile;
    outputFile.open(filename);
    if (outputFile.fail())
    {
        cout << "***COULD NOT CONNECT TO FILE***";
        exit(1);
    }

    outputFile.setf(ios::left, ios::adjustfield);
    outputFile.width(20);
    outputFile << "LAST NAME";
    outputFile.width(20);
    outputFile << "FIRST NAME";
    outputFile.width(35);
    outputFile << "ADDRESS";
    outputFile.width(8);
    outputFile << "PHONE NUMBER" << endl;

    for(int i = 0; i < capacity; i++)
        hash_table[i].Print(outputFile);
}

//Description: Returns True if the record searched for is found in the Address Book, False otherwise. Calls
//Clients_Info_BST's Search function to locate the record.
//Precondition: Calling object must exist, string passed is in the form "LastName FirstName" with no spaces within
// the first or last name fields
//Postcondition: Returns True if the record searched for is found in the Address Book, False otherwise.
bool Client_Address_Book::Search(const string & s)
{
    if(hash_table[Hash_Function(s)].Search(s) == NULL)
        return 0;
    else
        return 1;
}

//Description: Hash function that returns an integer representing the index to where a record will be located
// in the hash table, using the first letter of the string passed
//Precondition: Calling object must exist
//Postcondition: Returns an integer representing the index to where a record will be located in the hash table,
// using the first letter of the string passed
unsigned int Client_Address_Book::Hash_Function(const string & s) //return the index of the BST in the hash table..last name must come first in string
{
    return (s[0] - 65);
}