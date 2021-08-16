#include <cctype>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <iomanip>
#include "poly.h"

using namespace std;

namespace coen79_lab5 {

    polynomial::polynomial(double c, unsigned int exponent) {
        if(exponent < MAXIMUM_DEGREE) {
            poly = new double[MAXIMUM_DEGREE];

            for(int i = 0; i < MAXIMUM_DEGREE; i++) {
                poly[i] = 0;
            }

            size = MAXIMUM_DEGREE;
        } else {
            poly = new double[exponent + 1];

            for(int i = 0; i < (exponent + 1); i++) {
                poly[i] = 0;
            }

            size = exponent + 1;
        }

        if(c > 0) {
            poly[exponent] = c;
            current_degree = exponent;
        } else {
            current_degree = 0;
        }
    }

    polynomial::polynomial(const polynomial& source) {
        size = source.size;
        current_degree = source.current_degree;
        poly = new double[size];
        copy(source.poly, source.poly + size, poly);
    }

    polynomial::~polynomial() {
        delete [] poly;
    }

    void polynomial::update_current_degree() {
        int spot = 0;
        for(int i = 0; i < size; i++) {
            if(poly[i] != 0) {
                spot = i;
            }
        }
        
        current_degree = spot;
    }

    void polynomial::reserve(size_t number) {
        double *arraynew;

        if(number <= size) {
            return;
        }

        arraynew = new double[number];
        copy(poly, poly + size, arraynew);
        delete [] poly;
        poly = arraynew;

        for(int i = size; i < number; i++) {
            poly[i] = 0;
        }

        size = number;
    }

    //DONT KNOW IF IT WORKS
    void polynomial::trim() {
        update_current_degree();
        double *arraynew;

        if(current_degree < size) {
            arraynew = new double[current_degree];
            copy(poly, poly + size, arraynew);
            delete [] poly;
            size = current_degree;
        }
    }

    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        if(exponent < size) {
            poly[exponent] = coefficient;
        } else {
            reserve(exponent + 1);
            poly[exponent] = coefficient;
        }
        update_current_degree();
    }

    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        if(exponent < size) {
            poly[exponent] += amount;
        } else {
            reserve(exponent + 1);
            poly[exponent] += amount;
        }

        update_current_degree();
    }

    void polynomial::clear() {
        for(int i = 0; i < size; i++) {
            poly[i] = 0;
        }

        current_degree = 0;
    }

    polynomial& polynomial::operator =(const polynomial& source) {
        double *arraynew;

        if(this == &source) {
            return *this;
        }

        if(size != source.size) {
            arraynew = new double[source.size];
            delete [] poly;
            poly = arraynew;
            size = source.size;
        }

        current_degree = source.current_degree;
        copy(source.poly, source.poly + size, poly);
        return *this;
    }

    //DONT KNOW IF IT WORKS
    polynomial& polynomial::operator =(double c) {
        double *arraynew;
        arraynew = new double[MAXIMUM_DEGREE];
        delete [] poly;
        poly = arraynew;
        size = MAXIMUM_DEGREE;

        for(int i = 0; i < MAXIMUM_DEGREE ; i++) {
            if(i == 0) {
                assign_coef(c, 0);
            }
            assign_coef(0, i);
        }

        current_degree = 0;
        return *this;
    }

    polynomial polynomial::antiderivative() const {
        polynomial newPoly;

        for(int i = 0; i < size; i++) {
            newPoly.poly[i + 1] = poly[i]/(i+1);
        }

        newPoly.poly[0] = 0;
        newPoly.update_current_degree();
        return newPoly;
    }

    double polynomial::coefficient(unsigned int exponent) const {
        if(exponent <= current_degree) {
            return poly[exponent];
        } else {
            return 0;
        }
    }

    double polynomial::definite_integral(double x0, double x1) const {
        polynomial newPoly = antiderivative();
        return (newPoly.eval(x0) - newPoly.eval(x1));
    }

    polynomial polynomial::derivative() const {
        polynomial newPoly(0, size);

        if(current_degree > 0) {
            for(int i = 0; i < (size - 1); i++) {
                newPoly.poly[i] = poly[i + 1] * (i + 1);
            }
        } else {
            newPoly.poly[0] = 0;
        }

        newPoly.update_current_degree();
        return newPoly;
    }

    double polynomial::eval(double x) const {
        double sum = 0;
        
        for(unsigned int i = 0; i < size; i++) {
            if(i == 0) {
                sum += poly[i];
            } else {
                sum += (pow(x, i) * poly[i]);
            }
        }

        return sum;
    }

    bool polynomial::is_zero() const {
        return (poly[current_degree] == poly[0]);
    }

    unsigned int polynomial::next_term(unsigned int e) const {
        for(unsigned int i = (e + 1); i < size; i++) {
            if(poly[i] != 0) {
                return i;
            }
        }

        return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const {
        if(e == 0) {
            return UINT_MAX;
        }

        if(e > size) {
            e = size;
        }

        for(int i = (e - 1); i >= 0; i--) {
            if(poly[i] != 0) {
                return i;
            }
        }

        return UINT_MAX;
    }

    polynomial operator +(const polynomial& p1, const polynomial& p2) {
        polynomial newPoly;
        double coef;

        if(p1.degree() < p2.degree()) {
            for(int i = 0; i < (p1.degree() + 1); i++) {
                coef = p1.coefficient(i) + p2.coefficient(i);
                newPoly.assign_coef(coef, i);
            }

            for(int j = (p1.degree() + 1); j < (p2.degree() + 1); j++) {
                coef = p2.coefficient(j);
                newPoly.assign_coef(coef, j);
            }
        } else {
            for(int i = 0; i < (p2.degree() + 1); i++) {
                coef = p1.coefficient(i) + p2.coefficient(i);
                newPoly.assign_coef(coef, i);
            }

            for(int j = (p2.degree() + 1); j < (p1.degree() + 1); j++) {
                coef = p1.coefficient(j);
                newPoly.assign_coef(coef, j);
            }
        }

        return newPoly;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) {
        polynomial newPoly;
        double coef;

        if(p1.degree() < p2.degree()) {
            for(int i = 0; i < (p1.degree() + 1); i++) {
                coef = p1.coefficient(i) - p2.coefficient(i);
                newPoly.assign_coef(coef, i);
            }

            for(int j = (p1.degree() + 1); j < (p2.degree() + 1); j++) {
                coef = -p2.coefficient(j);
                newPoly.assign_coef(coef, j);
            }
        } else {
            for(int i = 0; i < (p2.degree() + 1); i++) {
                coef = p1.coefficient(i) - p2.coefficient(i);
                newPoly.assign_coef(coef, i);
            }

            for(int j = (p2.degree() + 1); j < (p1.degree() + 1); j++) {
                coef = -p1.coefficient(j);
                newPoly.assign_coef(coef, j);
            }
        }

        return newPoly;
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2){
        double coef;
        int highestdeg = (p1.degree() + 1) * (p2.degree() + 1);
        polynomial newPoly(0, highestdeg);

        for(int i = 0; i <= p1.degree(); i++) {
            for(int j = 0; j <= p2.degree(); j++) {
                if(p1.coefficient(i) != 0 && p2.coefficient(j) != 0) {
                    coef = p1.coefficient(i) * p2.coefficient(j);
                    newPoly.add_to_coef(coef, (i + j));
                }
            }
        }

        return newPoly;
    }

    std::ostream& operator << (std::ostream& out, const polynomial& p) {
        unsigned int i = p.degree();
        streamsize ss = out.precision();
        out << fixed;
        out << setprecision(1);
        for (int i = p.degree(); i >= 0; i--) {
            if (p.degree() == 0) {
                cout << p.coefficient(i);
            } else if (p.coefficient(i) != 0) {
                if (i == p.degree()) {
                    if (i > 1) {
                        out << p.coefficient(i) << "x^" << i << " ";
                    } else if (i == 1) {
                        out << p.coefficient(i) << "x ";
                    } else if (i == 0) {
                        out << p.coefficient(i) << " ";
                    }
                } else if (i < p.degree() && i > 1) {
                    if (p.coefficient(i) < 0) {
                        out << "- " << p.coefficient(i)*-1;
                    } else {
                        out << "+ " << p.coefficient(i);
                    }
                    out << "x^" << i << " ";
                } else if (i == 1) {
                    if (p.coefficient(i) < 0) {
                        out << "- " << p.coefficient(i) * -1;
                    } else {
                        out << "+ " << p.coefficient(i);
                    }
                    out << "x ";
                } else if (i == 0) {
                    if (p.coefficient(i) < 0) {
                        out << "- " << p.coefficient(i) * -1;
                    } else {
                        out << "+ " << p.coefficient(i);
                    }
                }
            }
        }

        out << setprecision(ss);
        return out;
    }

}