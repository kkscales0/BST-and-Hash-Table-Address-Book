#include <iostream>
#include <fstream>
#include "hashing_BST.h"

using namespace std;

int main() {
    //Clients_Info_BST addressbook;
    //addressbook.Insert("Sexy Lady 400 Street East 555-1212");
    //addressbook.Insert("Big Abestos 12 Pond Hop Lane 523-1222");
    //addressbook.Insert("Bunny Pink 903 Ladybug Road 843-1342");
    //addressbook.Insert("Man Money 100000 Billionaire Road 999-9998");

    //addressbook.Print();

    //cout << endl << endl;
    //Clients_Info_BST newbook;
    //newbook = addressbook;
    //newbook.Insert("Bowler Rodney 132 Back Woods Lane 423-1222");

    //addressbook.Print();
    //newbook.Insert("Bones Crack 76 Skeleton Road 453-1221");
    //newbook.Insert("Zane Crazy 7634 Mad House Road 829-1221");
    //newbook.Print();

    //addressbook.Remove("Sexy Lady");
    //newbook.Print();

    /*string a = "7 Zane Crazy 233-3333";
    string b = "5 Bunny Pink Rabbit Blue";
    string c = "6 Big Abestos 1 Big Street";
    newbook.Update(a);
    newbook.Update(b);
    newbook.Update(c);
    newbook.Print();*/




    Client_Address_Book MyBook;
    //MyBook.Remove("Young Andy");
    //MyBook.Print_Hash_Table();
    //MyBook.Print_BST("H");
    MyBook.Insert("Hardy Tim 123 Easy Street 443-4354");
    MyBook.Print_BST("H");
    if(MyBook.Search("Young Andy"))
        cout << "ANDY FOUND";
    else
        cout << "ANDY NOT FOUND";
    MyBook.Remove("Fox Starter");
    //MyBook.Remove("Fox Smart");
    MyBook.Print_BST("F");
    MyBook.Insert("Fanta Orange 444 Soda Pop Lane 333-3332");
    //MyBook.Print_BST("F");
    MyBook.Update("6 Fox Smart 123 Dog Lane");
    //MyBook.Print_BST("D");
    MyBook.Print_BST("F");
    //MyBook.Print_Hash_Table_to_File("testOutput.txt");
    Client_Address_Book Book2 = MyBook;
    //Book2.Print_BST("H");
    Book2.Remove("Harper Fred");
    //Book2.Print_BST("H");
    //MyBook.Print_BST("H");

    return 0;
}