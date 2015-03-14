#ifndef EXT_TREE_UTILITIES_HPP
#define EXT_TREE_UTILITIES_HPP

#include <algorithm>
#include "tree.hpp"
using namespace ext;

std::string remove_letter_easy( std::string str, char c )
{
    str.erase( std::remove( str.begin(), str.end(), c ), str.end() ) ;
    return str ;
}


template<typename t_type, class t_allocator = std::allocator<t_type> >
tree<t_type, t_allocator>* load_tree_file(string filename)
{
    tree<t_type, t_allocator>* ts = new tree<t_type, t_allocator>;

    ifstream myReadFile;
    myReadFile.open("../test/out.txt");
    string line;

    if (myReadFile.is_open())
    {
        vector<typename tree<t_type, t_allocator>::node_pointer> v (100, nullptr);

        std::string str;
        while (std::getline(myReadFile, str))
        {
            int count = 0;
for(char& c : str)
            {
                if(c == '\t')
                    count++;
            }
            if(count == 0)
            {
                typename tree<t_type, t_allocator>::node_pointer node_f = ts->set_root(str);
                v[0] = node_f;
            }
            else if(count > 0)
            {
                tree<string>::node_pointer node_temp = ts->add_node(v[count-1], remove_letter_easy(str, '\t'));
                v[count] = node_temp;
            }
        }
    }
    myReadFile.close();

    return ts;
}


template<typename t_type, class t_allocator = std::allocator<t_type> >
void save_tree_file(string filename, tree<t_type, t_allocator>* np_tree)
{
    //tree<t_type, t_allocator>* ts = new tree<t_type, t_allocator>;

    ofstream myFile;
    myFile.open(filename);
    //string line;

    if (myFile.is_open())
    {
        //vector<typename tree<t_type, t_allocator>::node_pointer> v (100, nullptr);

        // preorder iterator
        preorder_iterator<string> it(np_tree);
        preorder_iterator<string> it_begin(np_tree);
        preorder_iterator<string> it_end(np_tree);

        it_begin = np_tree->mv_root;
        it_end = np_tree->mv_dummy_end;

        for(it = np_tree->mv_root; it != np_tree->mv_dummy_end; ++it)
        {
            for(int i = 0; i < np_tree->depth(it.mv_position); i++)
            {
                myFile << "\t";
            }
            myFile << *it << endl;
        }


    }

    myFile.close();

    //return ts;
}

#endif
