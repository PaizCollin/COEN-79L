#include <iostream>
#include "sequence.h"

using namespace std;
using namespace coen79_lab6;

void printSequence(sequence &s) {
	sequence seq(s);
	seq.start();

	// Loop to print the sequence.
	while(seq.is_item()) {
		cout << seq.current() << " ";
		seq.advance();
	}
	cout << endl;
}

//NODE
int main() {

    //positive tests
    node *my_list = NULL;
    node *head;
    node *tail;
    list_head_insert(my_list, 2);
    list_head_insert(my_list, 1);
    list_head_insert(my_list, 0);
    list_head_insert(my_list, 0);
    list_print(my_list);

    //1
    cout << list_occurrences(my_list, 0) << endl;

    //2
    list_insert_at(my_list, 2, 5);
    list_print(my_list);

    //3
    list_remove_at(my_list, 3);
    list_print(my_list);

    //4
    list_remove_dups(my_list);
    list_print(my_list);

    //5
    cout << list_occurrences(my_list, 0) << endl;

    //6
    list_insert_at(my_list, 3, 3);
    list_insert_at(my_list, 4, 4);
    list_print(list_copy_segment(my_list, 1, 3));

    //7
    list_piece(my_list,NULL,head,tail);
    list_print(head);

    //negative tests
    node *my_list2 = NULL;
    node *head2;
    node *tail2;

    //1
    cout << list_occurrences(my_list2, 0) << endl;

    //2
    list_insert_at(my_list2, 2, 100);
    list_print(my_list2);

    //3
    list_remove_at(my_list2, 3);
    list_print(my_list2);

    //4
    list_remove_dups(my_list2);
    list_print(my_list2);

    //5
    list_piece(my_list2,NULL,head2,tail2);
    list_print(head2);

    //6
    list_print(list_copy_segment(my_list, 1, 4));


}

//UNCOMMENT THE FOLLOWING TO TEST THE SEQ
//SEQUENCE
/*int main() {
    node *my_list = NULL;
    //positive tests
    
    //1
    sequence seq1, seq2; 

    //2, 3, 4
    seq1.attach(1);
    seq1.attach(2);
    seq1.attach(4);
    seq1.insert(3);
    printSequence(seq1);

    //5
    seq1.start();
    if(seq1.is_item()) {
        cout << "there is an item" << endl;
    } else {
        cout << "there is no item" << endl;
    }

    //6
    seq1.advance();
    seq1.advance();
    seq1.advance();
    if(seq1.is_item()) {
        cout << "there is an item" << endl;
    } else {
        cout << "there is no item" << endl;
    }

    //7
    seq1.advance();
    if(seq1.is_item()) {
        cout << "there is an item" << endl;
    } else {
        cout << "there is no item" << endl;
    }

    //8
    seq1.start();
    seq1.advance();
    cout << seq1.current() << endl;
    seq1.remove_current();
    printSequence(seq1);

    //9
    seq1.start();
    cout << seq1.current() << endl;
    seq1.remove_current();
    printSequence(seq1);

    //10
    seq1.end();
    cout << seq1.current() << endl;
    seq1.remove_current();
    printSequence(seq1);

    //11
    seq2 = seq1;
    printSequence(seq2);
    
    //12
    seq2.attach(0);
    cout << seq2.size() << endl;

    //negative tests
    sequence seq3, seq4;

    //1
    sequence seq5(seq6);

    //2
    seq3.advance();

    //3
    seq3.start();
    seq3.end();

    //4
    seq3.insert("hello");

    //5
    seq3.attach("hello");

    //6
    seq3 = seq6;
    
    //7
    seq3.remove_current();

    //boundary tests

    //1
    seq3.insert(179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368);
    printSequence(seq3);

    //2
    seq3.attach(179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368);
    printSequence(seq3);


} */