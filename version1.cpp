#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
//Задание
//проверка на std
//проверка на правильность знаков
//проверка на сложность аргумента
//1.наличие
//2.конструкция аргумента
//проверка на правильность конструкции
//


class Scanning {
    string filename;
    string line;
    vector<int> c_in;
    vector<int> c_out;
    vector<string> input;
    vector<string> output;

    void checking_line() {
        ifstream in(filename); // окрываем файл для чтения
        if (in.is_open()) {
            int numbLine = 1;
            while (getline(in, line)) {
                cout <<numbLine<<" "<< line << endl;
                finding(numbLine);
                numbLine++;
            }
            in.close();
        } else
            cout << "Not Opened" << endl;
    }

    void finding(int number) {
        if (line.find("using namespace std;") != string::npos) {
            flag = 1;
        } else if (line.find("cin") != string::npos) {
            outspace();
            c_in.push_back(number);
            input.push_back(line);
        } else if (line.find("cout") != string::npos) {
            outspace();
            c_out.push_back(number);
            output.push_back(line);
        }
    }

    void vecprint(vector<int> vec) {
        for (int i: vec) {
            cout << i << ", ";
        }
    }

    void outspace() {
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
    }

public:
    int flag = 0;

    Scanning(string file) {
        filename = file;
        checking_line();
    }
    int numbers_strok(string type, int position){
        if(type=="cin")
            return c_in[position];
        if(type=="cout")
            return c_out[position];
        else
            return -1;
    }
    vector<string> base(string keyword) {
        if (keyword == "cin") {
            cout << "cin was found in ";
            vecprint(c_in);
            cout << "strokah" << endl;
            return input;
        }
        if (keyword == "cout") {
            cout << "cout was found in ";
            vecprint(c_out);
            cout << "strokah" << endl;
            return output;
        } else {
            cout << "bad keyword" << endl;
            return {};
        }
    }
};

class Console {
    Scanning *general;

    string preposition(string line, string keyword) {
        int nachalo = line.find(keyword);
        if (general->flag == 0) {
            if (line.find("std::") == string::npos)
                cout << "Not using namespase std::" << endl;
            else if (line.find("std::") != nachalo - 5)
                cout << "Error in using namespase std::" << endl;
        }
        line.erase(0, nachalo + keyword.size());
        return line;
    }

    string signs(string line, string keyword) {
        if (line.substr(0, 2) == keyword) {
            line.erase(0, 2);
            if (line.empty()) {
                cout << "Bad expression expected argument" << endl;
                return line;
            }
            line = argument(line,keyword);
        } else {
            cout << "Expected " << keyword << endl;
            line = ";";
        }
        return line;
    }

    string argument(string line, string keyword) {
        if (line[0] == '\"') {
            line = text_in_cout(line,keyword);
        }
        else
            while(line[0] == '*')
                line.erase(0, 1);
            int pos = line.find(keyword);
            if(pos==-1){
                pos = line.find(';');
                if (pos==-1){
                    pos = 0;
                    line = ";";
                    cout << "Not found ;"<<endl;
                }
            }
            string meaning = line.substr(0,pos);
            line.erase(0,pos);
            check(meaning);
            return line;
        }

        string text_in_cout(string line, string keyword){
            if (keyword == "<<") {
                int pos = line.find('\"', 1);
                if (pos != -1) {
                    line.erase(0, pos);
                    if(line.find('\"')!=-1){
                        if(line.find(keyword)==-1)
                            cout<<"Extra \""<<endl;
                        else if(line.find(keyword)>line.find('\"'))
                            cout<<"Extra \" before " << keyword<<endl;
                    }
                }
                else
                    cout << "Not found ending sign \""<<endl;
            }
            else {
                cout << "Incorrect using \"" << endl;
                line = ";";
            }
            return line;
    }
        void check(string argument){
            if(argument.find_first_of("+-=/,*&%?!")!=-1)
                cout<<"Bad argument"<<endl;
            if(argument.empty())
                cout << "Empty argument" << endl;

    }
    string correct(string type, string sign){
        int i =0;
        for (string line: general->base(type)) {
            cout <<"line: "<<general->numbers_strok(type,i)<<endl;
            line = preposition(line, type);
            line = signs(line, sign);
            if(line == "endl" and type == "cin")
                cout<<"Delete endl";
            if(line == ";")
                cout << "No errors";
            i++;
        }
    }
public:
        Console(Scanning & input)
        {
            general = &input;
        }
        void correct_cin() {
        correct("cin",">>");
        }
        void correct_cout() {
            correct("cout","<<");
        }
    };


    int main() {
        string nameline = "hello.txt";
        Scanning Checkin((nameline));
        Console proverca(Checkin);
        proverca.correct_cin();
        proverca.correct_cout();
        return 0;
    }