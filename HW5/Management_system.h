//
// Created by ELON HADAD on 20/01/2023.
//

#ifndef EX_05_MANAGEMENT_SYSTEM_H
#define EX_05_MANAGEMENT_SYSTEM_H
#include "Graph.h"
#include <sstream>
#include <stdexcept>


class Management_system {

public:
    Management_system();
    Management_system(const Management_system& m);
    Management_system& operator=(const Management_system& m);
    void read_files(const string& file);
    void write_file(const string& str);
    void user_interface();
    static bool validate(const string& str);
    static bool validate_integer(const string& str, const string& file);
    virtual ~Management_system()=default;

private:
    Graph* graph;
};


#endif //EX_05_MANAGEMENT_SYSTEM_H