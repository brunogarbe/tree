#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include <iosfwd>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <tuple>
#include <utility>
#include <stdexcept>

#if defined(_WIN32)
#include <Windows.h>

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))

// Change POSIX C SOURCE version for pure c99 compilers
#if !defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE < 200112L
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#include <unistd.h>	// POSIX flags
#include <time.h>	// clock_gettime(), time()
#include <sys/time.h>	// gethrtime(), gettimeofday()
#include <sys/resource.h>
#include <sys/times.h>

#if defined(__MACH__) && defined(__APPLE__)
#include <mach/mach.h>
#include <mach/mach_time.h>
#endif

#else
#error "Unable to define timers for an unknown OS."
#endif

#include <stdio.h>
#include <math.h>

// *******************************************************************************************
// COLOR FUNCTIIONS

// Advanced Console Library (Core Header - advconsole.h)
// by Jeff Weiner
// http://tilde.planet-nebula.com/projects/advconsole/
//

// Color Functions
enum AC_COLOR
{
    AC_BLACK,
    AC_RED,
    AC_GREEN,
    AC_YELLOW,
    AC_BLUE,
    AC_MAGENTA,
    AC_CYAN,
    AC_WHITE,
    AC_DEFAULT
};
enum AC_COLORLAYER
{
    AC_FOREGROUND,
    AC_BACKGROUND
};
enum AC_COLORWEIGHT
{
    AC_NORMAL,
    AC_BOLD
};
class Color
{
private:
    const AC_COLOR c;
    const AC_COLORLAYER l;
    const AC_COLORWEIGHT w;

public:
    Color(AC_COLOR color = AC_DEFAULT, AC_COLORLAYER layer = AC_FOREGROUND, AC_COLORWEIGHT weight = AC_NORMAL);
    Color(AC_COLOR color, AC_COLORWEIGHT weight);
    AC_COLOR getColor() const;
    AC_COLORLAYER getLayer() const;
    AC_COLORWEIGHT getWeight() const;
};
std::ostream& operator<<(std::ostream& o, const Color& c);

// Color Functions
Color::Color(AC_COLOR color, AC_COLORLAYER layer, AC_COLORWEIGHT weight)
    : c(color), l(layer), w(weight)
{}
Color::Color(AC_COLOR color, AC_COLORWEIGHT weight)
    : c(color), l(AC_FOREGROUND), w(weight)
{}
AC_COLOR Color::getColor() const
{
    return c;
}
AC_COLORLAYER Color::getLayer() const
{
    return l;
}
AC_COLORWEIGHT Color::getWeight() const
{
    return w;
}

#if defined(_WIN32)
// Color Functions
std::ostream& operator<<(std::ostream& o, const Color& c)
{
    static WORD wCurrentColor = 0;

    WORD wColor = 0;
    AC_COLOR color = c.getColor();
    if (color == AC_DEFAULT)
    {
        // Possibly not the best way to handle this...
        if (c.getLayer() == AC_FOREGROUND)
            color = AC_WHITE;
        else
            color = AC_BLACK;
    }
    switch (color)
    {
    case AC_BLACK:
        wColor = 0;
        break;
    case AC_RED:
        wColor = FOREGROUND_RED;
        break;
    case AC_GREEN:
        wColor = FOREGROUND_GREEN;
        break;
    case AC_YELLOW:
        wColor = FOREGROUND_RED | FOREGROUND_GREEN;
        break;
    case AC_BLUE:
        wColor = FOREGROUND_BLUE;
        break;
    case AC_MAGENTA:
        wColor = FOREGROUND_RED | FOREGROUND_BLUE;
        break;
    case AC_CYAN:
        wColor = FOREGROUND_GREEN | FOREGROUND_BLUE;
        break;
    case AC_WHITE:
    case AC_DEFAULT:
    default:
        wColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        break;
    }
    if (c.getWeight() == AC_BOLD)
        wColor |= FOREGROUND_INTENSITY;
    if (c.getLayer() == AC_BACKGROUND)
        wColor <<= 4;	// Shift if necessary...

    if (c.getLayer() == AC_BACKGROUND)
        wCurrentColor &= (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    else
        wCurrentColor &= (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
    wCurrentColor |= wColor;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wCurrentColor);
    return o;
}

#elif defined(__unix__) || defined(__unix) || defined(unix) || (defined(__APPLE__) && defined(__MACH__))
// Color Functions
std::ostream& operator<<(std::ostream& o, const Color& c)
{
    static int lastForeground = 0;
    static int lastBackground = 0;

    if (c.getLayer() == AC_BACKGROUND)
        lastBackground = (c.getColor() != AC_DEFAULT ? 40 + c.getColor() : 0);
    else
        lastForeground = (c.getColor() != AC_DEFAULT ? 30 + c.getColor() : 0);

    bool bold = (c.getLayer() == AC_FOREGROUND ? (c.getWeight() == AC_BOLD) : false);
    o << "\033[" << (bold ? 1 : 0) << ';' << lastForeground;
    if (lastBackground != 0)	// If we don't incldue this, it resets everything...
        o << ';' << lastBackground;
    return (o << 'm');
}
#else
#error "Unable to define COLORS for an unknown OS."
#endif
// *******************************************************************************************

#define INTERNAL_CATCH_UNIQUE_NAME_LINE2( name, line ) name##line
#define INTERNAL_CATCH_UNIQUE_NAME_LINE( name, line ) INTERNAL_CATCH_UNIQUE_NAME_LINE2( name, line )
#define INTERNAL_CATCH_UNIQUE_NAME( name ) INTERNAL_CATCH_UNIQUE_NAME_LINE( name, __COUNTER__ )

#define REGISTER(FunctionDesc, FunctionName)\
        namespace{ \
           unit_test<> INTERNAL_CATCH_UNIQUE_NAME( TESTE )(FunctionDesc, #FunctionName, FunctionName);\
        }

// Assertions
#define mu_check(test) MU__SAFE_BLOCK(\
	minunit_assert++;\
	if (!(test)) {\
		snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %s", __func__, __FILE__, __LINE__, #test);\
		minunit_status = 1;\
		return;\
	} else {\
		printf(".");\
	}\
)

#define mu_fail(message) MU__SAFE_BLOCK(\
	minunit_assert++;\
	snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %s", __func__, __FILE__, __LINE__, message);\
	minunit_status = 1;\
	return;\
)

#define mu_assert(test, message) MU__SAFE_BLOCK(\
	minunit_assert++;\
	if (!(test)) {\
		snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %s", __func__, __FILE__, __LINE__, message);\
		minunit_status = 1;\
		return;\
	} else {\
		printf(".");\
	}\
)

#define mu_assert_int_eq(expected, result) MU__SAFE_BLOCK(\
	minunit_assert++;\
	int minunit_tmp_e = (expected);\
	int minunit_tmp_r = (result);\
	if (minunit_tmp_e != minunit_tmp_r) {\
		snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %d expected but was %d", __func__, __FILE__, __LINE__, minunit_tmp_e, minunit_tmp_r);\
		minunit_status = 1;\
		return;\
	} else {\
		printf(".");\
	}\
)


#define mu_assert_double_eq(expected, result) MU__SAFE_BLOCK(\
	minunit_assert++;\
	double minunit_tmp_e = (expected);\
	double minunit_tmp_r = (result);\
	if (fabs(minunit_tmp_e-minunit_tmp_r) > MINUNIT_EPSILON) {\
		snprintf(minunit_last_message, MINUNIT_MESSAGE_LEN, "%s failed:\n\t%s:%d: %g expected but was %g", __func__, __FILE__, __LINE__, minunit_tmp_e, minunit_tmp_r);\
		minunit_status = 1;\
		return;\
	} else {\
		printf(".");\
	}\
)




#define SAFE_BLOCK(block) do {\
	block\
} while(0)

// Assertions
#define VERIFY(test) SAFE_BLOCK(\
	if (!(test)) {\
		unit_test_abstract::add_ref_message(__FILE__, __LINE__, #test);\
		unit_test_abstract::add_verify();\
		throw(unit_test_exception("verify"));\
	}\
)

template <typename T>
class Singleton
{
private:
    // Singleton class instance:
    static T* mv_instance;
    // Copy constructor:
    Singleton<T>(const Singleton& source)
    {}

protected:
    // Constructor:
    Singleton<T>()
    {}

    // Destructor:
    virtual ~Singleton<T>()
    {}

public:
    static T* instance()
    {
        if (mv_instance == nullptr)
            mv_instance = new T;

//					ASSERT(_instance != 0);

        return mv_instance;
    }

    static void destroyInstance()
    {
        if (mv_instance)
            delete mv_instance;
        mv_instance = nullptr;
    }
};

//! static class member initialisation.
template <typename T> T* Singleton<T>::mv_instance = nullptr;
//}




class unit_test_exception : public std::exception
{
public:
    explicit unit_test_exception()
    { }

    explicit unit_test_exception(const char* message):
        msg_(message)
    {}

    explicit unit_test_exception(const std::string& message):
        msg_(message)
    {}

    virtual ~unit_test_exception() throw () {}

    virtual const char* what() const throw()
    {
        return msg_.c_str();
    }

protected:
    std::string msg_;
};

// forward declaration
class unit_test_abstract;

class unit_test_collection: public Singleton<unit_test_collection>
{
public:
    void add_test(unit_test_abstract* ptr)
    {
        tests.push_back(ptr);
    }

public:
    std::vector<unit_test_abstract*> tests;
};

class unit_test_abstract
{
public:
    unit_test_abstract(std::string n_name, std::string n_func)
        : name(n_name), function_name(n_func), mt_verify_counter(0)
    {
        Singleton<unit_test_collection>::instance()->add_test(this);
    }

    virtual bool run() = 0;

    static void add_message(std::string str)
    {
        if(unit_test_abstract::mts_ptr != nullptr)
        {
            (*unit_test_abstract::mts_ptr).mt_messages.push_back(str);
        }
    }

    static void add_ref_message(const char* filename, int line, std::string str)
    {
        if(unit_test_abstract::mts_ptr != nullptr)
        {
            std::string ret;
            ret += filename;
            ret += "(" + std::to_string(line) + "): ";
            ret += str;
            (*unit_test_abstract::mts_ptr).mt_messages.push_back(ret);
        }
    }

    static void add_verify()
    {
        if(unit_test_abstract::mts_ptr != nullptr)
        {
            (*unit_test_abstract::mts_ptr).mt_verify_counter++;
        }
    }

public:
    void set_default()
    {
        mts_ptr = this;
    }

public:
    static unit_test_abstract* mts_ptr;// = nullptr;
    std::vector<std::string> mt_messages;
    unsigned int mt_verify_counter;

public:
    std::string name;
    std::string function_name;
};

template <typename... Arguments>
class unit_test : public unit_test_abstract
{
public:
    unit_test(std::string n_name, std::string n_func, std::function<void(Arguments...)> n_test)
        : unit_test_abstract(n_name, n_func), mv_test(n_test)
    {}

    bool run()
    {
        try
        {
            mv_test();
        }
        catch(const unit_test_exception& error)
        {
            //std::cout << "BINGO" << std::endl;
            return false;
        }
        catch(...)
        {
            unit_test_abstract::add_message("unespected throw exception.");
			//unit_test_abstract::add_message(" " + typeid(person).name() << std::endl;
            //std::cout << "UBINGO" << std::endl;
            return false;
        }

        if(mt_verify_counter != 0)
        {
            return false;
        }

        return true;
    }


public:
    std::string mv_args;

public:
    std::function<void(Arguments...)> mv_test;
};


#endif // __MINUNIT_H__
