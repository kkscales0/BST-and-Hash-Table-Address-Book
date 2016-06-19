/********************************************************************************************

Name: Kyle Scales    Z#: Z23334750
Course: Data Structures and Algorithm Analysis (COP3530)
Professor: Dr. Lofton Bullard
Due Date: 11/23/2015           Due Time: 5:00pm
Total Points: 100
Assignment 7: BST and Hash Table

Description: This file contains the headers for the Clients_Info_BST class and the
Client_Address_Book class.

Clients_Info_BST is a BST class, while Client_Address_Book is a hash table with each element
being a Clients_Info_BST object. Client_Address_Book holds and maintains an address book.

*********************************************************************************************/
#ifndef FINALASSIGNMENT_HASHING_BST_H
#define FINALASSIGNMENT_HASHING_BST_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class BST_Node  //node in a BST-->Holds client information
{
public:

    string lastname, firstname, address, phone_number;

    BST_Node  *lchild, *rchild;

};



class Clients_Info_BST //Binary Search Tree
{
public:

    Clients_Info_BST();//Stores the data in the hash table

    Clients_Info_BST(const Clients_Info_BST & original);//Copy constructor

    ~Clients_Info_BST();//Destructor

    void Insert(const string & s);//Insert adds a new Client's information (into a BST_Node) into the BST

    void Remove(const string & s);//Remove deletes a BST_Node that contains the specified client info from the BST
    // if it is there; otherwise a message is printed stating it was not found

    void Update(string & s);//Update modifies client information in a node given the last and first name if it is in
    // the BST; otherwise prints a message stating so

    void Print( );//Print output a BST, in order, to the display

    void Print(ostream & output);

    BST_Node * Search(const string & s);//Search returns a pointer to the node if found, pointer to NULL otherwise

    void operator=(const Clients_Info_BST & original);

private:

    BST_Node * root;

    //The following private member functions are called by the above public member functions to allow for recursion
    void Insert(BST_Node * & location_ptr, string item);
    void Print(BST_Node * & location_ptr);
    void Print(BST_Node * & location_ptr, ostream & output);
    void Copy_Aux(BST_Node * & newtree, const BST_Node * original);
    BST_Node * Search(BST_Node *, string item);
    BST_Node * Inorder_Succ(BST_Node * location);
    void Remove(BST_Node * & loc_ptr, string item);

};







class Client_Address_Book
{
public:

    Client_Address_Book();//default constructor will read data from input file "client_address_data.txt".

    Client_Address_Book(const Client_Address_Book & original);//Copy Constructor

    ~Client_Address_Book();//Destructor

    void Insert(const string & s);//Insert adds a new Client's information to the hash table

    void Remove(const string & s);//Remove deletes a client from the hash table if it is there; otherwise
    // a message should be printed stating so.

    void Update(string s);//update record

    void Print_BST(const string & s); //Print a BST (cell in hash table) inorder to the screen

    void Print_Hash_Table(); //function will print hash table to the screen

    void Print_Hash_Table_to_File(const string & filename);//function will print hash table to output file

    bool Search(const string & s); //return true if client found; otherwise false

    unsigned int Hash_Function(const string & s); //return the index of the BST in the hash table

private:

    int capacity;

    Clients_Info_BST * hash_table;

};



#endif //FINALASSIGNMENT_HASHING_BST_H
