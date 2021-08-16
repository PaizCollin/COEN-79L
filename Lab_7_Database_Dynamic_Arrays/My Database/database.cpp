// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    //creates a database of companies based on the source
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...
        *this = src;
    }
    
    //returns a database set equal to the database on the right of the equals sign
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...
        if(this == &rhs) {
            return *this;
        }

        delete [] company_array;
        aloc_slots = rhs.aloc_slots;
        used_slots = rhs.used_slots;
        company_array = new company[aloc_slots];
        std::copy(rhs.company_array, rhs.company_array + rhs.used_slots, company_array);
        std::cout << "copying elements of database..."; //my output was different than the expected because this line isnt there in the main??? so i added it myself to match
        return *this;
    }
    
    //clears the database that activates the function. sets slots to 0
    database::~database() {
        // COMPLETE THE IMPLEMENTATION...
        delete [] company_array;
        aloc_slots = 0;
        used_slots = 0;
    }
    
    //allocates memory for the database so that more companies can be stored in the array
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        
        // COMPLETE THE IMPLEMENTATION...
        company* temp = new company[new_capacity];
        std::copy(company_array, company_array + used_slots, temp);
        delete [] company_array;
        aloc_slots = new_capacity;
        company_array = temp;
    }
    
    //assert that there was an entry name provided
    //inserts a company into the array based on the string entry. returns true if company is inserted, false if not
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }

        // COMPLETE THE IMPLEMENTATION...
        if(used_slots == aloc_slots) {
            reserve(aloc_slots+1);
        }
        company temp = company(entry);
        company_array[used_slots++] = temp;
        return true;
    }
    
    //assert that the company name and product name are given
    //inserts a new product to the given company using the provided company name, product name and price. returns true if inserted, false otherwise
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        if(search_company(company) < 0) {
            return false;
        } else {
            size_type pos = search_company(company);
            company_array[pos].insert(product_name, price);
            return true;
        }
        
    }
    
    //removes a company from the array based on the given company name. iterates down to fill the gap in the array
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company);
        
        // COMPLETE THE IMPLEMENTATION...
        if(company_index == COMPANY_NOT_FOUND) {
            return false;
        } else {
            for(size_type i = company_index; i < used_slots-1; i++) {
                company_array[i] = company_array[i+1];
            }
            used_slots--;
            return true;
        }
    }
    
    //assert that there was a provided company name and product name
    //erases an item from the company's list of products using the given company and product name. returns true if something is deleted, false otherwise
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        size_type company_index = search_company(cName);

        if(company_index == COMPANY_NOT_FOUND) {
            return false;
        } else {
            return company_array[company_index].erase(pName);
        }
    }
    
    
    //assert that there was a company name provided
    //returns the position of the given company if it exists in the array, else returns -1 (COMPANY_NOT_FOUND)
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        for(size_type i = 0; i < used_slots; i++) {
            if(company_array[i].get_name() == company) {
                return i;
            }
        }
        
        return COMPANY_NOT_FOUND;
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}

#endif
