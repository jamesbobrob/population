/* @(#) money.h          Copymiddle 1991 Adolfo Di Mare  */
/*                                                       */
/*            Yet Another Money C++ Class                */
/*                                                       */
/*   Use freely but acknowledge author and publication.  */
/*    DO NOT SELL IT. The author reserves all rigths!    */

/*                             email: adolfo@di-mare.com */

/* Compiler:                           Borland C++ v 2.0 */
/*                          [should work with Turbo C++] */


#ifndef _money_h
#define _money_h

extern "C" {     // avoid type clashes with the C library
    #include <math.h>    /* floor() */
    #include <float.h>   /* DBL_DIG */
}

#ifndef DBL_DIG
#define DBL_DIG 16
#endif

#ifndef MONEY_DECIMALS       /* number of decimals in */
#define MONEY_DECIMALS  2    /*   any money quantity  */
#endif                       /* don't use parentesis! */

#define __VAL(n)  n               /* 1 level indirection */
#define TENPOW(n) __VAL(1.0e##n)  /* Trick to yield 10^n */


#define MONEY_DIG   DBL_DIG


class money {
public:

    static int    decimals() { return MONEY_DECIMALS;     }
    static int    digits()   { return MONEY_DIG; }
    static double SCALE()
        { return TENPOW(MONEY_DECIMALS); }

    money();              // do nothing constructor
    money(double);        // constructor from double
    money(const money&);  // copy constructor

    money& operator= (const money&);  // copy operator
    money& operator= (double);        // copy from double
    operator double() const;          // convert to double

    int  OK()   const;  // check money's invariant
    void FIX();         // get rid of unwanted decimals


    friend money  operator + (const money&, const money&);
    friend money  operator + (double,       const money&);
    friend money  operator + (const money&, double);
    friend money  operator - (const money&, const money&);
    friend money  operator - (double,       const money&);
    friend money  operator - (const money&, double);

    friend money  operator*  (const money&, double);
    friend money  operator*  (double,       const money&);
    friend double operator/  (const money&, const money&);
    friend money  operator/  (const money&, double);
    friend money  operator%  (const money&, const money&);

    // money  * money  is NOT valid
    // double / money  is INVALID

    friend int operator == (const money&, const money&);
    friend int operator != (const money&, const money&);
    friend int operator <  (const money&, const money&);
    friend int operator >  (const money&, const money&);
    friend int operator <= (const money&, const money&);
    friend int operator >= (const money&, const money&);

    friend int operator == (const money&, double);
    friend int operator != (const money&, double);
    friend int operator <  (const money&, double);
    friend int operator >  (const money&, double);
    friend int operator <= (const money&, double);
    friend int operator >= (const money&, double);

    friend int operator == (double, const money&);
    friend int operator != (double, const money&);
    friend int operator <  (double, const money&);
    friend int operator >  (double, const money&);
    friend int operator <= (double, const money&);
    friend int operator >= (double, const money&);

    money& operator += (const money&);
    money& operator += (double);
    money& operator -= (const money&);
    money& operator -= (double);

    money& operator *= (double);
    money& operator /= (double);

    friend money  operator+ (const money&);
    friend money  operator- (const money&);
    money& operator++();     // prefix
    money& operator--();
    money& operator++(int);  // postfix
    money& operator--(int);
    friend int    operator! (const money&);

    friend money abs(const money&);
    friend money flatten(
         const money& m,
         double cents=0.25, int rounding = 1 /* TRUE */);

protected:         // let users change the class behaviour
    double m_money;
};

// Constructors && assignment
inline money::money() {
// do nothing constructor, for efficiency
}
inline money::money(double d) {
// construct from double
    m_money = d*SCALE();
    FIX();
}
inline money::money(const money& m) {
// copy constructor
    m_money = m.m_money;
}

inline money& money::operator= (const money& m) {
// copy operator
    m_money = m.m_money;
    return *this;
}
inline money& money::operator= (double d) {
// assign from double
    m_money = d*SCALE();
    FIX();
    return *this;
}
inline money::operator double() const {
// convert to double
    return m_money / SCALE();
}

inline int money::OK() const {
// Returns TRUE (1) when the quantity stored
// in *this really corresponds to a money
// quantity.

    money temp;
    temp.m_money = m_money;
    temp.FIX();
    return (
        ( temp.m_money == m_money )
          &&
        ( fabs(m_money) < (TENPOW(DBL_DIG) / SCALE()) )
    );
}

inline void money::FIX() {
// Deletes all decimals digits beyond
// the MONEY_DECIMALS decimal place.
// - If the value is out of range, FIX
//   won't fix it.
    m_money =
        (m_money > 0.0
            ?
                floor(
                    m_money
                     #ifdef MONEY_ROUNDING
                        + 0.5 // 0.49 is also an option...
                     #endif
                 )
            :
                ceil(
                    m_money
                     #ifdef MONEY_ROUNDING
                        - 0.5
                     #endif
                 )
        );
}

// add
inline money operator+ (const money& m, const money& mm) {
    money temp;    // don't mult*SCALE()
    temp.m_money = m.m_money + mm.m_money;
    return temp;
}
inline money operator+ (double d, const money& m) {
    return (money(d)+m);
}
inline money operator+ (const money& m, double d) {
    return (m+money(d));
}

// substract
inline money operator- (const money& m, const money& mm) {
    money temp;
    temp.m_money = m.m_money - mm.m_money;
    return temp;
}
inline money operator- (double d, const money& m) {
    return (money(d)-m);
}
inline money operator- (const money& m, double d) {
    return (m-money(d));
}

// multiply
inline money operator* (const money& m, double d) {
    money temp;
    temp.m_money = m.m_money * d; // don't mult by SCALE()
    temp.FIX();    // this could be delayed...
    return temp;
}
inline money operator* (double d, const money& m) {
    return (m*d);
}

// divide
inline double operator/ (const money& m, const money& mm) {
    return m.m_money / mm.m_money;
}
inline money  operator/ (const money& m, double d) {
    money temp;
    temp.m_money = m.m_money / d;
    temp.FIX();    // this could be delayed...
    return temp;
}
inline money operator%  (const money& m, const money& mm) {
    money temp;
    temp.m_money = fmod(m.m_money, mm.m_money);
    temp.FIX();    // this could be delayed...
    return temp;
}

// compare
inline int operator  == (const money& m, const money& mm) {
    return m.m_money ==  mm.m_money;
}
inline int operator  != (const money& m, const money& mm) {
    return m.m_money !=  mm.m_money;
}
inline int operator  <  (const money& m, const money& mm) {
    return m.m_money <   mm.m_money;
}
inline int operator  >  (const money& m, const money& mm) {
    return m.m_money >   mm.m_money;
}
inline int operator  <= (const money& m, const money& mm) {
    return m.m_money <=  mm.m_money;
}
inline int operator  >= (const money& m, const money& mm) {
    return m.m_money >=  mm.m_money;
}

inline int operator  == (const money& m, double mm) {
    return m.m_money == mm;
//  return m.m_money == (money)mm;  // take a pick !!!
/*
    A decission that you should make is whether this
    equality comparison requires the double quantity
    to  be  promoted  to  a money item.  The  direct
    comparison   is   more   transparent,   so it is
    prefered in here.
*/
}
inline int operator  != (const money& m, double mm) {
    return !(m == mm);
}
inline int operator  <  (const money& m, double mm) {
    return m.m_money <  mm;
}
inline int operator  >  (const money& m, double mm) {
    return m.m_money >  mm;
}
inline int operator  <= (const money& m, double mm) {
    return m.m_money <= mm;
}
inline int operator  >= (const money& m, double mm) {
    return m.m_money >= mm;
}

inline int operator  == (double m, const money& mm) {
    return  (mm == m);
}
inline int operator  != (double m, const money& mm) {
    return !(mm == m);
}
inline int operator  <  (double m, const money& mm) {
    return         m <  mm.m_money;
}
inline int operator  >  (double m, const money& mm) {
    return         m >  mm.m_money;
}
inline int operator  <= (double m, const money& mm) {
    return         m <= mm.m_money;
}
inline int operator  >= (double m, const money& mm) {
    return         m >= mm.m_money;
}

inline money& money::operator += (const money& m) {
    m_money += m.m_money;
    return *this;
}
inline money& money::operator += (double d) {
    m_money += d*SCALE();
    FIX();
    return *this;
}
inline money& money::operator -= (const money& m) {
    m_money -= m.m_money;
    return *this;
}
inline money& money::operator -= (double d) {
    m_money -= d*SCALE();
    FIX();
    return *this;
}
inline money& money::operator *= (double d) {
    m_money *= d;
    FIX();
    return *this;
}
inline money& money::operator /= (double d) {
    m_money /= d;
    FIX();
    return *this;
}

// unary op's
inline money operator+(const money& m) {
    return m;
}
inline money operator-(const money& m) {
    money temp;
    temp.m_money = -m.m_money;
    return temp;
}
inline money& money::operator++() {
    m_money += SCALE();
    #if (MONEY_DECIMALS<0)
        FIX(); // avoid problems because of
    #endif     // the representation of 10^-n
    return *this;
}
inline money& money::operator--() {
    m_money -= SCALE();
    #if (MONEY_DECIMALS<0)
        FIX();
    #endif
    return *this;
}

inline money& money::operator++(int) {
    return ++(*this);
}

inline money& money::operator--(int) {
    return --(*this);
}
inline int operator!(const money& m) {
    return m.m_money == 0.0;
}

inline money abs(const money& m) {
    money temp;
    temp.m_money = fabs(m.m_money);
    return temp;
}

money flatten(const money& m, double cents, int rounding) {
// Returns a money data item where the cents are
// rounded modulo "cents". In this way cents can
// be stripped of money items when the currency
// does not have all the coins required to pay
// every posible quantity.
    money temp;
    double c = floor(fabs(cents*money::SCALE())); // cents
    double r = fmod(m.m_money, c);            // remainder
    temp.m_money =
        (!rounding || (2.0* r <= c)
            ? m.m_money - r
            : m.m_money - r + c
        );
    return temp;
}

/* Avoid name space overcrowding */
#undef __VAL
#undef TENPOW /* jic: Just In Case! */

#endif  /* _money_h */
