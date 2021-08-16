#include "database.h"

using namespace coen79_lab7;

int main(int argc, const char * argv[]) {

    //positive tests
    //1
    database db1;

    //2
    db1.insert_company("C1");
    db1.insert_company("C2");
    db1.insert_company("C3");

    //3
    db1.print_companies();

    //4
    database db2(db1);
    db2.print_companies();

    //5
    database db3 = db1;
    db3.print_companies();

    //6
    db1.insert_item("C1", "1", 1.00);

    //7
    db1.print_items_by_company("C1");

    //8
    db1.insert_item("C1", "2", 2.00);
    db1.insert_item("C1", "3", 3.00);
    db1.insert_item("C1", "4", 4.00);
    db1.insert_item("C1", "5", 5.00);
    db1.erase_item("C1", "3");
    db1.print_items_by_company("C1");

    //9
    db1.erase_item("C1", "1");
    db1.print_items_by_company("C1");

    //10
    db1.erase_item("C1", "5");
    db1.print_items_by_company("C1");

    //11
    db2.insert_company("C4");
    db2.insert_company("C5");
    db2.erase_company("C3");
    db2.print_companies();

    //12
    db2.erase_company("C1");
    db2.print_companies();

    //13
    db2.erase_company("C5");
    db2.print_companies();

    //14
    cout << db1.search_company("C1") << endl;

    //negative tests
    //1
    database db4(2345);

    //2
    database db5(db6);

    //3
    database db5 = db6;

    //4
    database db7;
    db7.print_companies();

    //5
    db7.print_items_by_company("C1", "1");

    //6
    db7.insert_company("");

    //7
    db7.insert_company("C1");
    db7.insert_item("C1", "", 0);

    //8
    if(db7.erase_company("C2") == true) {
        cout << "deleted" << endl;
    } else {
        cout << "no company to delete" << endl;
    }

    //9
    if(db7.erase_item("C2", "NO") == true) {
        cout << "deleted" << endl;
    } else {
        cout << "no item to delete" << endl;
    }

    //10
    db7.erase_item("", "");

    //11
    cout << db1.search_company("NOCOMPANY") << endl;

    //12
    cout << db1.search_company("") << endl;

    //boundary tests
    //1
    db1.insert_item("C1", "MAX", 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368);
    db1.print_items_by_company("C1");

    //2
    db1.insert_item("C1", "MAX", 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368 + 1);
    db1.print_items_by_company("C1");
    
}