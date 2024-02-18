#include <iostream>
#include <fstream>
#include <string>
#include <vector>


//Задание
//проверка на std
//проверка на правильность знаков
//проверка на сложность аргумента
//1.наличие
//2.конструкция аргумента
//проверка на правильность конструкции cin-cout

//Не проверяю
//инициализированность переменных
//если два подряд на одной строке(там должен быть разделяющая ; тут переводчик строк
using namespace std;

class Scanning {
    string filename;
    string line;
    vector<string> input;
    vector<string> output;

    void finding(int number) {
        if (line.find("using namespace std;") != string::npos) {
            flag = 1;
        }else if (line.find("cin") != string::npos) {
            outspace();
            c_in.push_back(number);
            input.push_back(line);
        }else if (line.find("cout") != string::npos) {
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
    void checkingLines() {
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

protected:
    vector<int> c_in;
    vector<int> c_out;
    int flag = 0;
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
public:
    Scanning(string file):filename(file){
        checkingLines();
    }


};
//
class Console: protected Scanning{
    string preposition(string line, string keyword) {
        int nachalo = line.find(keyword);
        if (flag == 0) {
            if (line.find("std::") == string::npos)
                cout << "Not using namespase std::" << endl;
            else if (line.find("std::") != nachalo - 5)
                cout << "Error in using namespase std::" << endl;
        }
        line.erase(0, nachalo + keyword.size());
        return line;
    }

    string signs(string line, string keyword,int flag) {
        if (line.substr(0, 2) == keyword) {
            line.erase(0, 2);
            if (line.empty()) {
                cout << "Bad expression expected argument" << endl;
                return line;
            }
            line = argument(line,keyword,++flag);
        } else if(flag==0){
            cout << "Expected " << keyword << endl;
            line = "-";
        }
        return line;
    }
    string textArgument(string line, string keyword){
        if (keyword == "<<") {
            int pos = line.find('\"', 1);
            if (pos != -1)
                line.erase(0, pos+1);
            else
                cout << "Not found ending sign \""<<endl;
        }
        else {
            cout << "Incorrect using \" in cin" << endl;
            line = ";";
        }
        return line;
    }
    string argument(string line, string keyword, int flag) {
        if (line[0] == '\"') {
            line = textArgument(line,keyword);
            return line;
        }
        else
            while(line[0] == '*')
                line.erase(0, 1);
        int pos = line.find(keyword);
        if(pos==-1){
            pos = line.find(';');
            if (pos==-1){
                pos = line.size();
                //line = ";";
                cout << "Not found ;"<<endl;
            }
        }
        string meaning = line.substr(0,pos);
        line.erase(0,pos);
        line = check(meaning, line);
        line = signs(line, keyword, flag);
        return line;
    }
    string check(string argument, string line){
        //string types[8] = {"+", "-", "=", "/", ",", "*", "&", "?"};
        if(argument.find_first_of("+-=/,*&%?!")!=-1) {
            cout << "Bad argument" << endl;
            line = "-;";
        }
        if(argument.empty()) {
            cout << "Empty argument" << endl;
            line = "-;";
        }
        return line;
    }
    string correct(string line, string keyword, int &number){
        cout <<"line: ";
        line = preposition(line, keyword);
        if(keyword=="cin") {
            cout<<c_in[number]<<endl;
            line = signs(line, ">>", 0);
        }
        else {
            cout<<c_out[number]<<endl;
            line = signs(line, "<<", 0);
        }
        number++;
        if(line[0]==';')
            cout<<"No Errors"<<endl;
        return line;
    }
public:
    Console(string file) : Scanning(file) {}

    void correctCin() {
        int i =0;
        for (string line: base("cin")) {
            line = correct(line,"cin",i);
            if(line.find("endl;")==0)
                cout<<"Delete endl"<<endl;
        }
    }
    void correctCout() {
        int i =0;
        for (string line: base("cout")) {
            line = correct(line,"cout",i);
            if(line[0]=='\"') {
                cout << "Too many \"" << endl;
            }
        }
    }
};


int main() {
    string nameline = "Examples.txt";
    Console proverca(nameline);
    cout<<endl;
    proverca.correctCin();
    proverca.correctCout();
    return 0;
}