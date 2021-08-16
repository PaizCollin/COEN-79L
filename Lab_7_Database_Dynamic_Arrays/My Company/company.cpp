// FILE: company.cpp
// CLASS implemented: company (see company.h for documentation)


#include <cassert>
#include "company.h"

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif

namespace coen79_lab7
{
    company::company() {
        this->company_name = "";
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    //creates a new company based on the provided name
    company::company(const std::string& company_name) {
        assert(company_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        this->company_name = company_name;
        this->head_ptr = NULL;
        this->tail_ptr = NULL;
    }
    
    //creates a new company based on the source
    company::company(const company &src) {
        Debug("Company copy constructor..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...
        *this = src;
    }

    //returns a new company with the attributes of the source company
    company& company::operator= (const company &src) {
        Debug("Company assignemnt operator..." << std::endl);

        // COMPLETE THE IMPLEMENTATION...
        if(this == &src) {
            return *this;
        }
        this->company_name = src.company_name;
        list_copy(src.get_head(), head_ptr, tail_ptr);
        return *this;
    }
    
    
    company::~company() {
        list_clear(head_ptr);
    }
    
    
    std::string company::get_name() const {
        return company_name;
    }
    
    const node *company::get_head() const {
        return head_ptr;
    }
    
    const node *company::get_tail() const {
        return tail_ptr;
    }
    
    node* company::get_head() {
        return head_ptr;
    }
    
    node* company::get_tail() {
        return tail_ptr;
    }
    
    void company::print_items() {
        list_print(head_ptr);
    }
    
    //assert that there was a product given
    //inserts a new product into the list of the company obj that activated this function. returns true if inserted, false if product already inserted
    bool company::insert(const std::string& product_name, const float& price) {
        
        assert(product_name.length() > 0);

        if (list_contains_item(head_ptr, product_name)) {
            return false;
        }
        
        if (head_ptr == NULL) {
            // COMPLETE THE IMPLEMENTATION...
            list_init(this->head_ptr, this->tail_ptr, product_name, price);
        }
        else {
            // COMPLETE THE IMPLEMENTATION...
            list_tail_insert(this->tail_ptr, product_name, price);
        }
        
        return true;
    }

    //assert that there was a product name given
    //erase a product from a company's inventory based on the name provided. returns true if deleted, false otherwise
    bool company::erase(const std::string& product_name) {
        assert(product_name.length() > 0);

        // COMPLETE THE IMPLEMENTATION...
        node* precursor = head_ptr;
        node* cursor;
        if(!list_contains_item(this->head_ptr, product_name)) {
            return false;
        }
/*      //different way of doing it, but I like the other way more
        while(precursor->getLink()->get_name() != product_name) {
            precursor = precursor->getLink();
        }
        cursor = precursor->getLink();
        precursor->setLink(cursor->getLink());
        delete cursor;
        return true;
*/
        node* temp = list_search(head_ptr, product_name);
        while(precursor->getLink() != temp) {
            precursor = precursor->getLink();
        }
        precursor->setLink(temp->getLink());
        delete temp;
        return true;
    } 
}
