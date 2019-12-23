// Copyright 2019 Your name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>
#include <string>
using std::cout;
using std::vector;
using std::string;
using std::endl;
//using namespace boost::filesystem;
using boost::filesystem::path;
using boost::filesystem::directory_iterator;
using boost::filesystem::directory_entry;
using boost::filesystem::filesystem_error;

class account{
public:
    account(){
        _number_of_account = 0;
        _last_date = 0;
    }
    explicit account(string &filename){
        _file_names.push_back(filename);
        set_number_of_accaunt(filename);
        set_last_date(filename);
    }
    void set_number_of_accaunt(string &filename){
        string number;
        number.assign(filename,
                      filename.find("_") + 1, filename.rfind("_") - 1);
        _number_of_account = atoi(number.c_str());
    }
    void set_last_date(string &filename)
    {
        string number;
        number.assign(filename,
                      filename.rfind("_") + 1, filename.rfind(".") - 1);
        _last_date = atoi(number.c_str());
    }
    void print_files(string &name){
        for (size_t k = 0; k < _file_names.size(); ++k)
        {
            cout << name << " " << _file_names[k] << endl;
        }
    }
    void print_account(string &name){
        cout << "broker:" << name;
        cout << " account:" << _number_of_account;
        cout << " files:" << _file_names.size();
        cout << " lastdate: " << _last_date << endl;
    }

public:
    uint32_t _number_of_account;
    //uint32_t _files_quantity;
    vector <string> _file_names;
    uint32_t _last_date;
};

class broker{
public:
    explicit broker(string &_name){
        name = _name;
    }
    void add_account(account &new_account){
        bool done = false;
        if (_accounts.size() == 0)
        {
            _accounts.push_back(new_account);
        } else {
            for (size_t i = 0; i < _accounts.size(); ++i)
            {
                if (_accounts[i]._number_of_account ==
                    new_account._number_of_account)
                {
                    _accounts[i]._file_names.push_back(
                                          new_account._file_names[0]);
                    if (_accounts[i]._last_date < new_account._last_date)
                    {
                        _accounts[i]._last_date = new_account._last_date;
                    }
                    done = true;
                    break;
                }
            }
        }
        if (!done)
        {
            _accounts.push_back(new_account);
        }
    }
    string name;
    vector <account> _accounts;
};

class my_FTP{
public:
    explicit my_FTP(path &_starting_path){
        starting_path = _starting_path;
        is_this_broker_active = false;
        iterate_it(starting_path);
        print_all();
        cout << endl;
        print_by_account();
    }
    void iterate_it(path &p){
        try
        {
            if (exists(p))
            {
                if (is_regular_file(p))
                {
                    string name_of_file = p.filename().string();
                    if (name_of_file.find("balance_") != string::npos)
                    {
                        if (name_of_file.find(".old") == string::npos)
                        {
                            string str_that_must_be = string(".txt");
                            if (p.extension().string() == str_that_must_be)
                            {
                                if (is_this_broker_active)
                                {
                                    account curr_account(name_of_file);
                                    _brokers[_brokers.size() - 1].add_account(
                                                          curr_account);
                                } else {
                                    broker current(current_broker);
                                    _brokers.push_back(current);
                                    is_this_broker_active = true;
                                    account curr_account(name_of_file);
                                    _brokers[_brokers.size() - 1].add_account(
                                                          curr_account);
                                }
                            }
                        }
                    }
                } else if (is_directory(p)) {
                    current_broker = p.string();
                    current_broker.erase(0, current_broker.rfind("/")+1);
                    for (directory_entry& x : directory_iterator(p))
                    {
                        path sm_path = x.path();
                        iterate_it(sm_path);
                    }
                    is_this_broker_active = false;
                    current_broker = string("");
                } else {
                    cout << p << " exists, ";
                    cout << "but is a symlink\n";
                }
            } else {
                cout << p << " does not exist\n";
            }
        } catch (const filesystem_error& ex) {
            cout << ex.what() << '\n';
        }
    }
    void print_all(){
        for (size_t i = 0; i < _brokers.size(); ++i)
        {
            for (size_t j = 0; j < _brokers[i]._accounts.size(); ++j)
            {
                _brokers[i]._accounts[j].print_files(_brokers[i].name);
            }
        }
    }
    void print_by_account(){
        for (size_t i = 0; i < _brokers.size(); ++i)
        {
            for (size_t j = 0; j < _brokers[i]._accounts.size(); ++j)
            {
                _brokers[i]._accounts[j].print_account(_brokers[i].name);
            }
        }
    }

private:
    vector <broker> _brokers;
    path starting_path;
    string current_broker;
    bool is_this_broker_active;
};







#endif // INCLUDE_HEADER_HPP_
