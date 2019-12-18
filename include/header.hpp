// Copyright 2019 Kirill <your_email>

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
using namespace boost::filesystem;
using boost::filesystem::path;

class account{
    account(){
        _number_of_account = 0; 
        _last_date = 0;
    }
    account(string filename){
        _file_names.push_back(filename);
        set_number_of_accaunt(filename);
        set_last_date(filename);
    }
    void set_number_of_accaunt(string filename){
        string number;
        number.assign(filename, 
                      filename.find("_") + 1, filename.rfind("_") - 1);
        _number_of_account = atoi(number.c_str());              
    }
    void set_last_date(string filename)
    {
        string number;
        number.assign(filename, 
                      filename.rfind("_") + 1, filename.rfind(".") - 1);
        _last_date = atoi(number.c_str()); 
    }
	void print_files(string name){
		for (size_t k = 0; k < _file_names.size(); ++k)
		{
			cout << name << " " << _file_names[k] << endl;		
		}
	}
	void print_account(string name){
		cout << "broker:" << name;
		cout << " account:" << _number_of_account;
		cout << " files:" << _file_names.size();
		cout << " lastdate: " << _last_date << endl;
	}
				
    uint32_t _number_of_account;
    //uint32_t _files_quantity;
    vector <string> _file_names;
    uint32_t _last_date;
};

class broker{
    string name;
    vector <account> _accounts;
};

class my_FTP{
    my_FTP(path &_starting_path){
		starting_path = _starting_path;
        is_this_broker_active = false;
		iterate_it(starting_path);
	}
	void iterate_it(path &p){
        try
        {
            if (exists(p))
            {
                if (is_regular_file(p))
                {
                    string filename = p.filename();
                    string str_that_must_be = string("balance_");
                    if (filename.find(str_that_must_be) != string::npos)
                    {
                        str_that_must_be = string(".old");
                        if (filename.find() == string::npos)
                        {
                            str_that_must_be = string(".txt");
                            if (p.extension() == str_that_must_be)
                            {
                                if (is_this_broker_active)
                                {
                                    
                                } else {
                                    _brokers.push_back(current_broker);
                                    is_this_broker_active = true;
                                    account curr_account(filename);
                                    
                                    _brokers[current_broker]._accounts;
                                }
                                
                            }
                        }
                    }
                } else if (is_directory(p)) {
                    current_broker = p.string();
                    current_broker.erase(0, current_broker.rfind("/")+1);
                    for (directory_entry& x : directory_iterator(p))
                        iterate_it(x.path()); 
                    current_broker = string("");
                } else {
                    cout << p << " exists, ";
                    cout << "but is not a regular file or directory\n";
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
		        _brokers[i]._accounts[j].print_files(_brokers[i].name());
		    }
		}	
	}
	void print_by_account(){
		for (size_t i = 0; i < _brokers.size(); ++i)
	    {
		    for (size_t j = 0; j < _brokers[i]._accounts.size(); ++j)
		    {
		        _brokers[i]._accounts[j].print_account(_brokers[i].name());
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
