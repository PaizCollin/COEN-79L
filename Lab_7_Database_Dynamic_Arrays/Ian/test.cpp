/*
This program is made to test the functionality of company database lab.
Three objectives must be met:
1. Testing the positive cases
2. Testing the negative cases
3. Testing the boundary cases

NOTES:
1. Can test the positive cases by providing valid inputs
2. Can test the negative cases by providing invalid inputs
3. Can test the boundary cases by providing boundary values as inputs
*/
#include "database.h"

using namespace std;
using namespace coen79_lab7;

void insertc(database*& db, string cname);
void inserti(database*& db, string cname, string pname, float price);

void erasec(database*& db, string cname);
void erasei(database*& db, string cname, string pname);
void printc(database*& db);
void printi(database*& db, string cname);
void cleardb(database*& db);


int main(int argc, const char * argv[]) {
    cout << "\nTesting Constructor\n";
    database *db0 = new database();
    cout << "\ndb0 Initialized\n";

    cout << "\nTesting insertion of companies\n";
    cout << "================================================================\n";
    insertc(db0, "Apple");
    insertc(db0, "Nvidia");
    printc(db0);

    cout << "\n\n\nTesting insertion of products\n";
    cout << "================================================================\n";
    inserti(db0, "Apple", "iPhone X", 1000.0);
    inserti(db0, "Nvidia", "RTX 3090", 1500.0);
    inserti(db0, "Nvidia", "RTX 3080", 700.0);
    inserti(db0, "Nvidia", "RTX 3070", 500.0);

    printi(db0, "Apple");
    printi(db0, "Nvidia");

    cout << "\n\n\nTesting deletion of products\n";
    cout << "================================================================\n";
    erasei(db0, "Nvidia", "RTX 3080");
    printi(db0, "Nvidia");

    cout << "\n\n\nTesting reserve\n";
    cout << "================================================================\n";
    for(char i = 'A'; i <= 'Z'; i++) {
        string s1(1, i);
        insertc(db0, s1);
    }
    printc(db0);
    
    cout << "\n\n\nTesting deletion of companies\n";
    cout << "================================================================\n";
    for(char i = 'A'; i <= 'Z'; i++) {
        string s2(1, i);
        erasec(db0, s2);
    }
    printc(db0);
    
    cout << "\n\n\nTesting invalid insertion of companies\n";
    cout << "================================================================\n";
    //COMMENTED OUT SO ASSERTS DON'T ABORT THE PROGRAM
    //insertc(db0, "");
    //printc(db0);

    cout << "\n\n\nTesting invalid insertion of products\n";
    cout << "================================================================\n";
    //inserti(db0, "Nvidia", "", 400.0);
    //printi(db0, "Nvidia");

    cout << "\n\n\nTesting invalid deletion of companies\n";
    cout << "================================================================\n";
    //erasec(db0, "");
    //printc(db0);

    cout << "\n\n\nTesting invalid deletion of products\n";
    cout << "================================================================\n";
    //erasei(db0, "Nvidia", "");
    //printi(db0, "Nvidia");

    cout << "\n\n\nTesting the deletion of a non-existent company\n";
    cout << "================================================================\n";
    erasec(db0, "AMD");
    printc(db0);

    cout << "\n\n\nTesting the deletion of a non-existent product\n";
    cout << "================================================================\n";
    erasei(db0, "Nvidia", "RTX 3060 Ti");
    printi(db0, "Nvidia");
    
    //EXTRA TESTING
    
    insertc(db0, "AMD");
    inserti(db0, "AMD", "Ryzen 9 5950X", 700.0);
    inserti(db0, "AMD", "Ryzen 9 5900X", 550.0);
    inserti(db0, "AMD", "Ryzen 7 5800X", 450.0);
    inserti(db0, "AMD", "Ryzen 5 5600X", 350.0);

    insertc(db0, "Intel");
    inserti(db0, "Intel", "i9 11900K", 700.0);

    inserti(db0, "Nvidia", "RTX 3080", 700.0);

    insertc(db0, "Asus");
    inserti(db0, "Asus", "ROG Crosshair VIII Hero", 350.0);
    
    printc(db0);
    printi(db0, "Apple");
    printi(db0, "Nvidia");
    printi(db0, "Intel");
    printi(db0, "AMD");
    printi(db0, "Asus");

    
    inserti(db0, "Apple", "iPhone 12 Pro", 1000.0);
    printi(db0, "Apple");

    erasei(db0, "Apple", "iPhone X");
    printi(db0, "Apple");

    erasec(db0, "Apple");
    erasec(db0, "Nvidia");
    erasec(db0, "AMD");
    erasec(db0, "Intel");
 
    printc(db0);

    insertc(db0, "Intel");
    printc(db0);
    printi(db0, "Intel");

    insertc(db0, "Nvidia");
    printc(db0);
    printi(db0, "Nvidia");

    insertc(db0, "Apple");
    printc(db0);
    printi(db0, "Apple");

    insertc(db0, "AMD");
    printc(db0);
    printi(db0, "AMD");
    

    
    for(char i = 'A'; i <= 'Z'; i++) {
        string s1(1, i);
        insertc(db0, s1);
    }
    printc(db0);
    
    for(char i = 'A'; i <= 'Z'; i++) {
        string s2(1, i);
        erasec(db0, s2);
    }
    printc(db0);

    cout << "\n\n\nTesting deletion of all companies in the database\n";
    cout << "================================================================\n";

    printc(db0);

    erasec(db0, "Nvidia");
    erasec(db0, "AMD");
    erasec(db0, "Intel");
    erasec(db0, "Apple");
    erasec(db0, "Asus");
    printc(db0);

    cout << "\n\n\nReinserting all companies into the database\n";
    cout << "================================================================\n";

    insertc(db0, "AMD");
    insertc(db0, "Intel");
    insertc(db0, "Apple");
    insertc(db0, "Nvidia");
    insertc(db0, "Asus");

    printc(db0);

    cout << "\n\n\nPrinting all items in the database\n";
    cout << "================================================================\n";

    printi(db0, "AMD");
    printi(db0, "Intel");
    printi(db0, "Nvidia");
    printi(db0, "Apple");
    printi(db0, "Asus");
    
}

void insertc(database*& db, string cname) {
    cout << "\nTesting the insertion of a new company\n";
    if(db->insert_company(cname) > 0) {
        cout << "\n" << cname << " Inserted in the database\n";
    } else {
        cout << "\nCompany " << cname << " is already in the database!\n";
    }
}

void inserti(database*& db, string cname, string pname, float price) {
    cout << "\nTesting the insertion of a new product\n";
    if(db->insert_item(cname, pname, price) > 0) {
        cout << "\n" << pname << ", " << price << " Inserted in company " << cname << "\n";
    } else {
        cout << "\nThe insertion of product " << pname << ", " << price << " in company " << cname << " has failed\n";
    }
}

void erasec(database*& db, string cname) {
    cout << "\nTesting the erasure of company " << cname << " from the database\n";
    if(db->erase_company(cname) > 0) {
        cout << "\n" << cname << " has been erased from the database\n";
    } else {
        cout << "\n" << cname << " was not found in the database\n";
    }
}

void erasei(database*& db, string cname, string pname) {
    cout << "\nTesting the erasure of item " << pname << " from company " << cname << "\n";
    if(db->erase_item(cname, pname) > 0) {
        cout << "\n" << pname << " has been erased from the company " << cname << "\n";
    } else {
        cout << "\nEither company " << cname << " or product " << pname << " could not be found\n";
    }
}

void printc(database*& db) {
    cout << "\nPrinting all companies in the database\n";
    db->print_companies();
}

void printi(database*& db, string cname) {
    cout << "\nPrinting the list of products in company " << cname << "\n";
    if(db->print_items_by_company(cname) < 0) {
        cout << "\nCompany " << cname << " was not found in the database\n";
    }
}

void cleardb(database*& db) {
    cout << "\nClearing the database of all items\n";
    db->~database();
    cout << "\nDatabase is cleared\n";
}

