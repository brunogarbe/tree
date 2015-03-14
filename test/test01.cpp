#include "unit_test.hpp"
#include "tree.hpp"

#include <string>
#include <vector>
#include <functional>
#include <tuple>
#include <utility>
#include <iostream>
#include <random>
#include <functional>
#include <algorithm>
#include <chrono>
using namespace std;

#define MAX_ROW_1 50
#define MAX_COLUMN_1 50
#define MAX_ROW_2 100
#define MAX_COLUMN_2 100


// ##########################################################################################################
//{ Constructors

template <typename T>
static void test_tree_default_constructor()
{
	ext::tree<T> tb;

	VERIFY(tb.size() == 0);
	VERIFY(tb.empty() == true);
	VERIFY(tb.data() == nullptr);	
}
REGISTER("ext::table default constructor", test_tree_default_constructor<int> );
REGISTER("ext::table default constructor", test_tree_default_constructor<std::string> );

/*
template <typename T, unsigned int TR, unsigned int TC>
static void test_table_fill_constructor()
{
	T val = T();

	ext::table<T> tb(TR, TC);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);

	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);

	VERIFY(tb.data() != nullptr);

	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			VERIFY(tb(i,j) == val);
		}
}
REGISTER("table fill constructor with default", (test_table_fill_constructor<int,5,5>) );
REGISTER("table fill constructor with default", (test_table_fill_constructor<int,MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table fill constructor with default", (test_table_fill_constructor<int,MAX_ROW_2,MAX_COLUMN_2>) );
REGISTER("table fill constructor with default", (test_table_fill_constructor<std::string,5,5>) );
REGISTER("table fill constructor with default", (test_table_fill_constructor<std::string,MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table fill constructor with default", (test_table_fill_constructor<std::string,MAX_ROW_2,MAX_COLUMN_2>) );


template <unsigned int TR, unsigned int TC>
static void test_table_fill_constructor_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);


    std::uniform_int_distribution<> dis(1, 10);

	int val = dis(gen);

	ext::table<int> tb(TR, TC, val);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);

	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);

	VERIFY(tb.data() != nullptr);

	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			VERIFY(tb(i,j) == val);
		}
}
REGISTER("table fill constructor with int", (test_table_fill_constructor_int<5,5>) );
REGISTER("table fill constructor with int", (test_table_fill_constructor_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table fill constructor with int", (test_table_fill_constructor_int<MAX_ROW_2,MAX_COLUMN_2>) );


template <unsigned int TR, unsigned int TC>
static void test_table_copy_constructor_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);


    std::uniform_int_distribution<> dis(1, 10);

	//int val = ;

	ext::table<int> source(TR, TC);

	VERIFY(source.num_of_rows() == TR);
	VERIFY(source.num_of_columns() == TC);
	VERIFY(source.size() == TR*TC);
	VERIFY(source.capacity() >= TR*TC);
	VERIFY(source.empty() == false);
	VERIFY(source.data() != nullptr);

	for(int i = 0; i < source.num_of_rows(); i++)
		for(int j = 0; j < source.num_of_columns(); j++)
		{
			source(i,j) = dis(gen);
		}

	ext::table<int> target(source);

	VERIFY(target.num_of_rows() == TR);
	VERIFY(target.num_of_columns() == TC);
	VERIFY(target.size() == TR*TC);
	VERIFY(target.capacity() >= TR*TC);
	VERIFY(target.empty() == false);
	VERIFY(target.data() != nullptr);

	for(int i = 0; i < target.num_of_rows(); i++)
		for(int j = 0; j < target.num_of_columns(); j++)
		{
			VERIFY(target(i,j) == source(i,j));
		}
}
REGISTER("table copy constructor with int", (test_table_copy_constructor_int<5,5>) );
REGISTER("table copy constructor with int", (test_table_copy_constructor_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table copy constructor with int", (test_table_copy_constructor_int<MAX_ROW_2,MAX_COLUMN_2>) );

//}


// ##########################################################################################################
//{ Copy assignment

template <unsigned int TR, unsigned int TC>
static void test_table_copy_assign_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);


    std::uniform_int_distribution<> dis(1, 10);

	//int val = ;

	ext::table<int> source(TR, TC);

	VERIFY(source.num_of_rows() == TR);
	VERIFY(source.num_of_columns() == TC);
	VERIFY(source.size() == TR*TC);
	VERIFY(source.capacity() >= TR*TC);
	VERIFY(source.empty() == false);
	VERIFY(source.data() != nullptr);

	for(int i = 0; i < source.num_of_rows(); i++)
		for(int j = 0; j < source.num_of_columns(); j++)
		{
			source(i,j) = dis(gen);
		}

	ext::table<int> target = source;

	VERIFY(target.num_of_rows() == TR);
	VERIFY(target.num_of_columns() == TC);
	VERIFY(target.size() == TR*TC);
	VERIFY(target.capacity() >= TR*TC);
	VERIFY(target.empty() == false);
	VERIFY(target.data() != nullptr);

	for(int i = 0; i < target.num_of_rows(); i++)
		for(int j = 0; j < target.num_of_columns(); j++)
		{
			VERIFY(target(i,j) == source(i,j));
		}
}
REGISTER("table copy assign with int", (test_table_copy_assign_int<5,5>) );
REGISTER("table copy assign with int", (test_table_copy_assign_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table copy assign with int", (test_table_copy_assign_int<MAX_ROW_2,MAX_COLUMN_2>) );

//}


// ##########################################################################################################
//{ Capacity

template <unsigned int TR, unsigned int TC>
static void test_table_resize_row_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(1, 10);

	int val1 = dis(gen);
	int val2 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.resize(2*TR, TC, val2);

	VERIFY(tb.num_of_rows() == 2*TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == 2*TR*TC);
	VERIFY(tb.capacity() >= 2*TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	for(int i = 0; i < tb.num_of_rows()/2; i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			VERIFY(tb(i,j) == val1);
		}
	
	for(int i = tb.num_of_rows()/2; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			VERIFY(tb(i,j) == val2);
		}
	
}
REGISTER("table resize_row with int", (test_table_resize_row_int<5,5>) );
REGISTER("table resize_row with int", (test_table_resize_row_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table resize_row with int", (test_table_resize_row_int<MAX_ROW_2,MAX_COLUMN_2>) );

template <unsigned int TR, unsigned int TC>
static void test_table_resize_column_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(1, 10);

	int val1 = dis(gen);
	int val2 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.resize(TR, 2*TC, val2);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == 2*TC);
	VERIFY(tb.size() == 2*TR*TC);
	VERIFY(tb.capacity() >= 2*TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns()/2; j++)
		{
			VERIFY(tb(i,j) == val1);
		}
	
	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = tb.num_of_columns()/2; j < tb.num_of_columns(); j++)
		{
			VERIFY(tb(i,j) == val2);
		}
	
}
REGISTER("table resize_column with int", (test_table_resize_column_int<5,5>) );
REGISTER("table resize_column with int", (test_table_resize_column_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table resize_column with int", (test_table_resize_column_int<MAX_ROW_2,MAX_COLUMN_2>) );


template <unsigned int TR, unsigned int TC>
static void test_table_resize_both_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(1, 10);

	int val1 = dis(gen);
	int val2 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.resize(2*TR, 2*TC, val2);

	VERIFY(tb.num_of_rows() == 2*TR);
	VERIFY(tb.num_of_columns() == 2*TC);
	VERIFY(tb.size() == 4*TR*TC);
	VERIFY(tb.capacity() >= 4*TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	for(int i = 0; i < tb.num_of_rows()/2; i++)
		for(int j = 0; j < tb.num_of_columns()/2; j++)
		{
			VERIFY(tb(i,j) == val1);
		}
	
	for(int i = 0; i < tb.num_of_rows()/2; i++)
		for(int j = tb.num_of_columns()/2; j < tb.num_of_columns(); j++)
		{
			VERIFY(tb(i,j) == val2);
		}
	
	for(int i = tb.num_of_rows()/2; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns()/2; j++)
		{
			VERIFY(tb(i,j) == val2);
		}

	for(int i = tb.num_of_rows()/2; i < tb.num_of_rows(); i++)
		for(int j = tb.num_of_columns()/2; j < tb.num_of_columns(); j++)
		{
			VERIFY(tb(i,j) == val2);
		}
}
REGISTER("table resize_both with int", (test_table_resize_both_int<5,5>) );
REGISTER("table resize_both with int", (test_table_resize_both_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table resize_both with int", (test_table_resize_both_int<MAX_ROW_2,MAX_COLUMN_2>) );


template <unsigned int TR, unsigned int TC>
static void test_table_decrease_row_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(1, 10);

	int val1 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.resize(TR/2, TC);

	VERIFY(tb.num_of_rows() == TR/2);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == (TR/2)*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			VERIFY(tb(i,j) == val1);
		}
}
REGISTER("table decrease_row with int", (test_table_decrease_row_int<5,5>) );
REGISTER("table decrease_row with int", (test_table_decrease_row_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table decrease_row with int", (test_table_decrease_row_int<MAX_ROW_2,MAX_COLUMN_2>) );


template <unsigned int TR, unsigned int TC>
static void test_table_decrease_column_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(1, 10);

	int val1 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.resize(TR, TC/2);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC/2);
	VERIFY(tb.size() == TR*(TC/2));
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			VERIFY(tb(i,j) == val1);
		}
}
REGISTER("table decrease_column with int", (test_table_decrease_column_int<5,5>) );
REGISTER("table decrease_column with int", (test_table_decrease_column_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table decrease_column with int", (test_table_decrease_column_int<MAX_ROW_2,MAX_COLUMN_2>) );



template <unsigned int TR, unsigned int TC>
static void test_table_decrease_both_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(1, 10);

	int val1 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.resize(TR/2, TC/2);

	VERIFY(tb.num_of_rows() == TR/2);
	VERIFY(tb.num_of_columns() == TC/2);
	VERIFY(tb.size() == (TR/2)*(TC/2));
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			VERIFY(tb(i,j) == val1);
		}
}
REGISTER("table decrease_both with int", (test_table_decrease_both_int<5,5>) );
REGISTER("table decrease_both with int", (test_table_decrease_both_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table decrease_both with int", (test_table_decrease_both_int<MAX_ROW_2,MAX_COLUMN_2>) );


template <unsigned int TR, unsigned int TC>
static void test_table_reserve_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(1, 10);

	int val1 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.reserve(2*TR, 2*TC);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= 4*TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);
}
REGISTER("table reserve with int", (test_table_reserve_int<5,5>) );
REGISTER("table reserve with int", (test_table_reserve_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table reserve with int", (test_table_reserve_int<MAX_ROW_2,MAX_COLUMN_2>) );

//}


// ##########################################################################################################
//{ Modifiers

template <unsigned int TR, unsigned int TC>
static void test_table_assign_both_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);
	int m = std::min(TR, TC);
    std::uniform_int_distribution<> dis(0, m-1);

	int val1 = dis(gen);
	int val2 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.assign(val2);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			VERIFY(tb(i,j) == val2);
		}
}
REGISTER("table assign_both with int", (test_table_assign_both_int<5,5>) );
REGISTER("table assign_both with int", (test_table_assign_both_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table assign_both with int", (test_table_assign_both_int<MAX_ROW_2,MAX_COLUMN_2>) );


template <unsigned int TR, unsigned int TC>
static void test_table_assign_row_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(0, TR-1);

	int val1 = dis(gen);
	int val2 = dis(gen);
	int val3 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.assign_row(val3, val2);

	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			if(i == val3)
				VERIFY(tb(i,j) == val2);
			else
				VERIFY(tb(i,j) == val1);
		}
}
REGISTER("table assign_row with int", (test_table_assign_row_int<5,5>) );
REGISTER("table assign_row with int", (test_table_assign_row_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table assign_row with int", (test_table_assign_row_int<MAX_ROW_2,MAX_COLUMN_2>) );


template <unsigned int TR, unsigned int TC>
static void test_table_assign_column_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(0, TC-1);

	int val1 = dis(gen);
	int val2 = dis(gen);
	int val3 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.assign_column(val3, val2);

	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			if(j == val3)
				VERIFY(tb(i,j) == val2);
			else
				VERIFY(tb(i,j) == val1);
		}
}
REGISTER("table assign_column with int", (test_table_assign_column_int<5,5>) );
REGISTER("table assign_column with int", (test_table_assign_column_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table assign_column with int", (test_table_assign_column_int<MAX_ROW_2,MAX_COLUMN_2>) );



template <unsigned int TR, unsigned int TC>
static void test_table_push_back_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(0, TC-1);

	int val1 = dis(gen);
	int val2 = dis(gen);
	//int val3 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.push_back(val2);

	VERIFY(tb.num_of_rows() == TR+1);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == (TR+1)*TC);
	VERIFY(tb.capacity() >= (TR+1)*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);


	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			if(i == tb.num_of_rows()-1)
				VERIFY(tb(i,j) == val2);
			else
				VERIFY(tb(i,j) == val1);
		}
}
REGISTER("table push_back with int", (test_table_push_back_int<5,5>) );
REGISTER("table push_back with int", (test_table_push_back_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table push_back with int", (test_table_push_back_int<MAX_ROW_2,MAX_COLUMN_2>) );


template <unsigned int TR, unsigned int TC>
static void test_table_pop_back_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(0, TC-1);

	int val1 = dis(gen);
	//int val2 = dis(gen);
	//int val3 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.pop_back();

	VERIFY(tb.num_of_rows() == TR-1);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == (TR-1)*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);


	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			VERIFY(tb(i,j) == val1);
		}
}
REGISTER("table pop_back with int", (test_table_pop_back_int<5,5>) );
REGISTER("table pop_back with int", (test_table_pop_back_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table pop_back with int", (test_table_pop_back_int<MAX_ROW_2,MAX_COLUMN_2>) );



template <unsigned int TR, unsigned int TC>
static void test_table_insert_row_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(0, TR);

	int val1 = dis(gen);
	int val2 = dis(gen);
	int val3 = dis(gen);

	//std::cout << "# " << val3 << std::endl;
	
	ext::table<int> tb(TR, TC, val1);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.insert_row(val3, val2);

	VERIFY(tb.num_of_rows() == TR+1);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == (TR+1)*TC);
	VERIFY(tb.capacity() >= (TR+1)*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			if(i == val3)
				VERIFY(tb(i,j) == val2);
			else
				VERIFY(tb(i,j) == val1);
		}
}
REGISTER("table insert_row with int", (test_table_insert_row_int<5,5>) );
REGISTER("table insert_row with int", (test_table_insert_row_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table insert_row with int", (test_table_insert_row_int<MAX_ROW_2,MAX_COLUMN_2>) );


template <unsigned int TR, unsigned int TC>
static void test_table_insert_column_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(0, TC);

	int val1 = dis(gen);
	int val2 = dis(gen);
	int val3 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.insert_column(val3, val2);

	//std::cout << tb << std::endl;

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC+1);
	VERIFY(tb.size() == TR*(TC+1));
	VERIFY(tb.capacity() >= TR*(TC+1));
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			if(j == val3)
				VERIFY(tb(i,j) == val2);
			else
				VERIFY(tb(i,j) == val1);
		}
}
REGISTER("table insert_column with int", (test_table_insert_column_int<5,5>) );
REGISTER("table insert_column with int", (test_table_insert_column_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table insert_column with int", (test_table_insert_column_int<MAX_ROW_2,MAX_COLUMN_2>) );



template <unsigned int TR, unsigned int TC>
static void test_table_remove_row_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(0, TR-1);

	int val1 = dis(gen);
	int val2 = dis(gen);
	int val3 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	for(int j = 0; j < tb.num_of_columns(); j++)
	{
		tb(val3,j) = val2;
	}

	//std::cout << tb << std::endl;
	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.remove_row(val3);

	VERIFY(tb.num_of_rows() == TR-1);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == (TR-1)*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			VERIFY(tb(i,j) == val1);
		}
}
REGISTER("table remove_row with int", (test_table_remove_row_int<5,5>) );
REGISTER("table remove_row with int", (test_table_remove_row_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table remove_row with int", (test_table_remove_row_int<MAX_ROW_2,MAX_COLUMN_2>) );


template <unsigned int TR, unsigned int TC>
static void test_table_remove_column_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(0, TC-1);

	int val1 = dis(gen);
	int val2 = dis(gen);
	int val3 = dis(gen);

	
	//std::cout << "$ " << val3 << std::endl;
	
	ext::table<int> tb(TR, TC, val1);

	for(int i = 0; i < tb.num_of_rows(); i++)
	{
		tb(i,val3) = val2;
	}

	//std::cout << tb << std::endl;

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.remove_column(val3);

	//std::cout << tb << std::endl;

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC-1);
	VERIFY(tb.size() == TR*(TC-1));
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
		{
			VERIFY(tb(i,j) == val1);
		}
}
REGISTER("table remove_column with int", (test_table_remove_column_int<5,5>) );
REGISTER("table remove_column with int", (test_table_remove_column_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table remove_column with int", (test_table_remove_column_int<MAX_ROW_2,MAX_COLUMN_2>) );


template <unsigned int TR, unsigned int TC>
static void test_table_clear_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(0, TC-1);

	int val1 = dis(gen);
	int val2 = dis(gen);
	int val3 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	for(int i = 0; i < tb.num_of_rows(); i++)
	{
		tb(i,val3) = val2;
	}

	VERIFY(tb.num_of_rows() == TR);
	VERIFY(tb.num_of_columns() == TC);
	VERIFY(tb.size() == TR*TC);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == false);
	VERIFY(tb.data() != nullptr);

	tb.clear();

	VERIFY(tb.num_of_rows() == 0);
	VERIFY(tb.num_of_columns() == 0);
	VERIFY(tb.size() == 0);
	VERIFY(tb.capacity() >= TR*TC);
	VERIFY(tb.empty() == true);
	VERIFY(tb.data() != nullptr);

}
REGISTER("table clear with int", (test_table_clear_int<5,5>) );
REGISTER("table clear with int", (test_table_clear_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table clear with int", (test_table_clear_int<MAX_ROW_2,MAX_COLUMN_2>) );


//}



// ##########################################################################################################
//{ Iterators

template <unsigned int TR, unsigned int TC>
static void test_table_rows_iterator_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(0, TC-1);

	int val1 = dis(gen);
	int val2 = dis(gen);
	int val3 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	int counter = 0;
	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
	{
		tb(i,j) = counter;
		counter++;
	}
	
	ext::row_iterator<ext::table<int>> it2(&tb, 0);
	
	for(auto it = it2.begin(); it != it2.end(); ++it)
	{
		cout << *it << endl;
	}
	
	for(auto& it : tb.rows(1))
	{
		cout << it << endl;
	}
	
}
REGISTER("table rows_iterator with int", (test_table_rows_iterator_int<5,5>) );
REGISTER("table rows_iterator with int", (test_table_rows_iterator_int<MAX_ROW_1,MAX_COLUMN_1>) );
REGISTER("table rows_iterator with int", (test_table_rows_iterator_int<MAX_ROW_2,MAX_COLUMN_2>) );


// ##########################################################################################################
//{ STL algorithms

template <unsigned int TR, unsigned int TC>
static void test_table_stl_copy_int()
{
	// only one
	std::random_device rd;
	uint32_t seed_val = rd();
	std::mt19937 gen;

	// every time
	gen.seed(seed_val);

    std::uniform_int_distribution<> dis(0, TC-1);

	int val1 = dis(gen);
	int val2 = dis(gen);
	int val3 = dis(gen);

	ext::table<int> tb(TR, TC, val1);

	int counter = 0;
	for(int i = 0; i < tb.num_of_rows(); i++)
		for(int j = 0; j < tb.num_of_columns(); j++)
	{
		tb(i,j) = counter;
		counter++;
	}
	
	ext::row_iterator<ext::table<int>> it2(&tb, 0);
	
	for(auto it = it2.begin(); it != it2.end(); ++it)
	{
		cout << *it << endl;
	}
	
	for(auto& it : tb.rows(1))
	{
		cout << it << endl;
	}

	std::vector<int> myvector (TR);
	std::copy (tb.rows().begin(), tb.rows().end(), myvector.begin() );
	
	for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
	    std::cout << ' ' << *it;

}
REGISTER("table stl copy int", (test_table_stl_copy_int<5,5>) );
//REGISTER("table clear with int", (test_table_clear_int<MAX_ROW_1,MAX_COLUMN_1>) );
//REGISTER("table clear with int", (test_table_clear_int<MAX_ROW_2,MAX_COLUMN_2>) );

*/
//}

// ##########################################################################################################
//{ Main

unit_test_abstract* unit_test_abstract::mts_ptr = nullptr;

int main(int argc, char *argv[])
{
	int failed = 0;
	int sucess = 0;

	for(auto test : Singleton<unit_test_collection>::instance()->tests)
	{
		test->set_default();
		bool ret = test->run();

		if(ret == true)
		{
			cout << Color(AC_GREEN, AC_BOLD) << "[---PASSED---] " << Color();
			sucess++;
		}
		else
		{
			cout << Color(AC_RED, AC_BOLD) << "[---FAILED---] " << Color();
			failed++;
		}

		cout << test->name << " (" << test->function_name << ")" << endl;

		for(auto msg : test->mt_messages)
		{
			cout << msg << endl;
		}
	}

	cout << Color(AC_WHITE, AC_BOLD) << "[--Summary:--] " << Color();
	cout << "Success: " << sucess << " ";
	cout << "Failed: " << failed << endl;

	return 0;
}

//}
