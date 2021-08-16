#include "poly.h"
#include <cassert>
#include <cmath>
#include <climits>
#include <iostream>
#include <iomanip>
using namespace std; 

namespace coen79_lab4
{

    //constructor
    //pre: exponent is less than or equal to the max degree allowed
    //post: new polynomial is created using the provided exponent and coefficient values
    polynomial::polynomial(double c, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        clear();
        poly[exponent] = c;        
        current_degree = exponent;
    }

    //post: sets the current degree to the highest degree poly
    void polynomial::update_current_degree() {
        int spot = 0;
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {
            if(poly[i] != 0) {
                spot = i;
            }
        }
        current_degree = spot;
    }

    //pre: exponent is less than or equal to the max degree allowed
    //post: sets a new coefficient to the poly equation at the given exponent value
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        poly[exponent] = coefficient;
        update_current_degree();
    }

    //pre: exponent is less than or equal to the max degree allowed
    //post: adds to the coefficient of the given exponent value by the provided amount
    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        poly[exponent] += amount;
        update_current_degree();
    }

    //post: clears the entire polynomial eq
    void polynomial::clear( ) {
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {
            poly[i] = 0;
        }
        update_current_degree();
    }

    //pre: the degree of the polynomial must be less than the max degree
    //post: returns a polynomial that is the antiderivative of the current polynomial
    polynomial polynomial::antiderivative( ) const {
        assert(degree( ) < MAXIMUM_DEGREE);
        polynomial newPoly;
        for(int i = 0; i < MAXIMUM_DEGREE - 1; i++) {
            newPoly.poly[i+1] = poly[i]/(i+1);
        }
        newPoly.poly[0] = 0;
        newPoly.update_current_degree();
        return newPoly;
    }

    //post: returns the coefficient of the poly with the proivded exponent value
    double polynomial::coefficient(unsigned int exponent) const {
        if(exponent > MAXIMUM_DEGREE) {
            return 0;
        } else {
            return poly[exponent];
        }
    }

    //post: evaluates the antiderivative of the polynomial between two values
    double polynomial::definite_integral(double x0, double x1) const {
        polynomial newPoly = antiderivative();
        return newPoly.eval(x0) - newPoly.eval(x1);
    }

    //post: returns the current degree
    unsigned int polynomial::degree( ) const {
        return current_degree;
    }

    //post: returns the derivative of the polynomial equation
    polynomial polynomial::derivative( ) const {
        polynomial newPoly;
        for(int i = 0; i < MAXIMUM_DEGREE - 1; i++) {
            newPoly.poly[i] = poly[i+1]*(i+1);
        }
        newPoly.update_current_degree();
        return newPoly;
    }

    //post: returns the value of the polynomial given a specific value for the variable x
    double polynomial::eval(double x) const {
        double sum = 0;
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {
            sum += (pow(x, i) * poly[i]);
        }
        return sum;
    }

    //post: returns true if the current degree is 0 (poly eq is empty or a constant value), and false otherwise
    bool polynomial::is_zero( ) const {
        return (poly[current_degree] == poly[0]);
    }

    //post: returns the next exponent that is larger than the provided exponent, if there is one, else returns 0
    unsigned int polynomial::next_term(unsigned int e) const {
        for(int i = e+1; i < MAXIMUM_DEGREE; i++) {
            if(poly[i] > 0) {
                return i;
            }
        }
        return 0;
    }

    //post: returns the previous exponene that is less than the provided exponent, else returns the max int value
    unsigned int polynomial::previous_term(unsigned int e) const {
        for(int i = e-1; i > 0; i--) {
            if(poly[i] > 0) {
                return i;
            }
        }
        return UINT_MAX;
    }

    //post returns the value of the polynomial given the value of variable x
    double polynomial::operator( ) (double x) const {
        return eval(x);
    }
    
    //post: returns the summation of two polynomials, by overloading the + operator 
    polynomial operator +(const polynomial& p1, const polynomial& p2) {
        polynomial newPoly;

        for(int i = 0; i < polynomial::MAXIMUM_DEGREE; i++) {
            newPoly.add_to_coef(p1.coefficient(i) + p2.coefficient(i), i);
        }
        newPoly.update_current_degree();
        return newPoly;
    }

    //post: returns the difference between the two polynomials, by oerloading the - operator
    polynomial operator -(const polynomial& p1, const polynomial& p2) {
        polynomial newPoly;

        for(int i = 0; i < polynomial::MAXIMUM_DEGREE; i++) {
            newPoly.add_to_coef(p1.coefficient(i) - p2.coefficient(i), i);
        }
        newPoly.update_current_degree();
        return newPoly;
    }

    //post: returns the product of the two polynomials, by overloading the * operator
    polynomial operator *(const polynomial& p1, const polynomial& p2) {
        assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
        polynomial newPoly;
        int i, j;

        for(i = 0; i <= p1.degree(); i++) {
                for(j = 0; j <= p2.degree(); j++) {
                    newPoly.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i+j);
                }
        }
        //newPoly.update_current_degree();
        return newPoly;
    }

    //post: returns the polynomial equation in the proper format by overloading the << operator for the use of cout
    std::ostream& operator << (std::ostream& out, const polynomial& p) {
        unsigned int i = p.degree();
		streamsize ss = out.precision();
		out << fixed;
		out << setprecision(1);
		for (int i = p.degree(); i >= 0; i--) {
			if (p.degree() == 0) {
				cout << p.coefficient(i);
			}
			else if (p.coefficient(i) != 0) {
				if (i == p.degree()) {
					if (i > 1) {
						out << p.coefficient(i) << "x^" << i << " ";
                    }
					else if (i == 1) {
                        out << p.coefficient(i) << "x ";
                    }
					else if (i == 0) {
						out << p.coefficient(i) << " ";
                    }

				}
				else if (i < p.degree() && i > 1) {
					if (p.coefficient(i) < 0) {
						out << "- " << p.coefficient(i)*-1;
                    }
					else {
						out << "+ " << p.coefficient(i);
                    }
					out << "x^" << i << " ";
				}
				else if (i == 1) {
					if (p.coefficient(i) < 0) {
						out << "- " << p.coefficient(i) * -1;
                    }
					else {
						out << "+ " << p.coefficient(i);
                    }
					out << "x ";
				}
				else if (i == 0) {
					if (p.coefficient(i) < 0) {
						out << "- " << p.coefficient(i) * -1;
                    }
					else {
						out << "+ " << p.coefficient(i);
                    }
				}
			}
		}
		out << setprecision(ss);
		return out;
    }

}