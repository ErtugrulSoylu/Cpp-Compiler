#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//This struct makes variables with given typename, name and a value
template <typename T>
struct variable {
    string name;
    T value;
};

//These vectors are stacking given variables
vector<variable<double> > vector_of_doubles;
vector<variable<int> > vector_of_ints;

//Cleans spaces
string line_arranger(string line) {
    int counter = 0;
    string new_line = "";
    while (counter < line.length()) {
        if (line[counter] != ' ') {
            new_line += line[counter];
        }
        counter++;
    }
    return new_line;
}

//This function is for declaring new variables and stacking them in vector of variables
void var_declarer(string var_name, string value, bool is_double) {
    bool is_exist = false;
    if (is_double) {
        for (int i = 0; i < vector_of_doubles.size(); i++) {
            if (vector_of_doubles[i].name == var_name) {
                is_exist = true;
                vector_of_doubles[i].value = stod(value);
            }
        }
        if (!is_exist) {
            variable <double> X;
            X.name = var_name;
            X.value = stod(value);
            vector_of_doubles.push_back(X);
        }
    }
    else {
        for (int i = 0; i < vector_of_ints.size(); i++) {
            if (vector_of_ints[i].name == var_name) {
                is_exist = true;
                vector_of_ints[i].value = stoi(value);
            }
        }
        if (!is_exist) {
            variable <int> X;
            X.name = var_name;
            X.value = stoi(value);
            vector_of_ints.push_back(X);
        }
    }
}

//Returns value of given variable if exist
string var_finder(string var_name) {
    if (var_name[0] == '0' ||
        var_name[0] == '1' ||
        var_name[0] == '2' ||
        var_name[0] == '3' ||
        var_name[0] == '4' ||
        var_name[0] == '5' ||
        var_name[0] == '6' ||
        var_name[0] == '7' ||
        var_name[0] == '8' ||
        var_name[0] == '9') return var_name;
    if(var_name[0] == '-') {
        string act_value = var_finder(var_name.substr(1));
        if(count(act_value.begin(), act_value.end(), '.')) {
            return to_string(-1 * stod(act_value));
        } else{
            return to_string(-1 * stoi(act_value));
        }
        
    }
    for (int i = 0; i < vector_of_doubles.size(); i++) {
        if (vector_of_doubles[i].name == var_name) {
            return to_string(vector_of_doubles[i].value);
        }
    }
    for (int i = 0; i < vector_of_ints.size(); i++) {
        if (vector_of_ints[i].name == var_name) {
            return to_string(vector_of_ints[i].value);
        }
    }
    var_declarer(var_name, "0", false);
    return "0";
}

string division(string left_side, string right_side) {
    left_side = var_finder(left_side);
    right_side = var_finder(right_side);
    string both = left_side + right_side;
    if (count(both.begin(), both.end(), '.') > 0) {
        return to_string(stod(left_side) / stod(right_side));
    }
    else {
        return to_string(stoi(left_side) / stoi(right_side));
    }
}

string multiplication(string left_side, string right_side) {
    left_side = var_finder(left_side);
    right_side = var_finder(right_side);
    string both = left_side + right_side;
    if (count(both.begin(), both.end(), '.') > 0) {
        return to_string(stod(left_side) * stod(right_side));
    }
    else {
        return to_string(stoi(left_side) * stoi(right_side));
    }
}

string addition(string left_side, string right_side) {
    left_side = var_finder(left_side);
    right_side = var_finder(right_side);
    string both = left_side + right_side;
    if (count(both.begin(), both.end(), '.') > 0) {
        return to_string(stod(left_side) + stod(right_side));
    }
    else {
        return to_string(stoi(left_side) + stoi(right_side));
    }
}

string subtraction(string left_side, string right_side) {
    left_side = var_finder(left_side);
    right_side = var_finder(right_side);
    string both = left_side + right_side;
    if (count(both.begin(), both.end(), '.') > 0) {
        return to_string(stod(left_side) - stod(right_side));
    }
    else {
        return to_string(stoi(left_side) - stoi(right_side));
    }
}

//This is a recursive function that calls itself to find value of a given string
//Process priority is '(' > '/' > '*' > '-' > '+'
string calculator(string line) {
    if (count(line.begin(), line.end(), '(') > 0) {
        string parentheses_with_brackets = line.substr(line.find_last_of('('), line.substr(line.find_last_of('(')).find_first_of(')') + 1);
        string parentheses = parentheses_with_brackets.substr(1, parentheses_with_brackets.size() - 2);
        return calculator(line.replace(line.find(parentheses_with_brackets), parentheses_with_brackets.length(), calculator(parentheses)));
    }
    else if (count(line.begin(), line.end(), '/') > 0) {
        int counter = line.find_first_of('/');
        while (counter > 0 && line[counter - 1] != '-' && line[counter - 1] != '+' && line[counter - 1] != '*') {
            counter--;
        }
        string left_side = line.substr(counter, line.find_first_of('/') - counter);
        int left_side_index = counter;
        counter = line.find_first_of('/');
        if(line[counter + 1] == '-') counter++;
        while (counter < line.length() - 1 && line[counter + 1] != '*' && line[counter + 1] != '+' && line[counter + 1] != '/' && line[counter + 1] != '-') {
            counter++;
        }
        string right_side = line.substr(line.find_first_of('/') + 1, counter - line.find_first_of('/'));
        return calculator(line.replace(left_side_index, left_side.length() + right_side.length() + 1, division(left_side, right_side)));
    }
    else if (count(line.begin(), line.end(), '*') > 0) {
        int counter = line.find_first_of('*');
        while (counter > 0 && line[counter - 1] != '-' && line[counter - 1] != '+' && line[counter - 1] != '/') {
            counter--;
        }
        string left_side = line.substr(counter, line.find_first_of('*') - counter);
        int left_side_index = counter;
        counter = line.find_first_of('*');
        if(line[counter + 1] == '-') counter++;
        while (counter < line.length() - 1 && line[counter + 1] != '*' && line[counter + 1] != '+' && line[counter + 1] != '/' && line[counter + 1] != '-') {
            counter++;
        }
        string right_side = line.substr(line.find_first_of('*') + 1, counter - line.find_first_of('*'));
        return calculator(line.replace(left_side_index, left_side.length() + right_side.length() + 1, multiplication(left_side, right_side)));
    }
    else if (count(line.begin(), line.end(), '-') > 0 && line[0] != '-') {
        int counter = line.find_first_of('-');
        while (counter > 0 && line[counter - 1] != '+' && line[counter - 1] != '*' && line[counter - 1] != '/') {
            counter--;
        }
        string left_side = line.substr(counter, line.find_first_of('-') - counter);
        int left_side_index = counter;
        counter = line.find_first_of('-');
        while (counter < line.length() - 1 && line[counter + 1] != '*' && line[counter + 1] != '+' && line[counter + 1] != '/' && line[counter + 1] != '-') {
            counter++;
        }
        string right_side = line.substr(line.find_first_of('-') + 1, counter - line.find_first_of('-'));
        return calculator(line.replace(left_side_index, left_side.length() + right_side.length() + 1, subtraction(left_side, right_side)));
    }
    else if (count(line.begin(), line.end(), '+') > 0) {
        int counter = line.find_first_of('+');
        while (counter > 0 && line[counter - 1] != '-' && line[counter - 1] != '*' && line[counter - 1] != '/') {
            counter--;
        }
        string left_side = line.substr(counter, line.find_first_of('+') - counter);
        int left_side_index = counter;
        counter = line.find_first_of('+');
        while (counter < line.length() - 1 && line[counter + 1] != '*' && line[counter + 1] != '+' && line[counter + 1] != '/' && line[counter + 1] != '-') {
            counter++;
        }
        string right_side = line.substr(line.find_first_of('+') + 1, counter - line.find_first_of('+'));
        return calculator(line.replace(left_side_index, left_side.length() + right_side.length() + 1, addition(left_side, right_side)));
    }
    else {
        if(line[0] == '-') return multiplication("-1", line.substr(1));
        return line;
    }
}

/*
This function returns result of given boolean line
like => IF A+B < C THEN C ELSE B
If true, returns C, else returns B
*/
string boolean_process(string line) {
    if(line.find("<=") != std::string::npos) {
        string left_side = line.substr(2, line.find("<=") - 2);
        string right_side = line.substr(line.find("<=") + 2, line.find("THEN") - line.find("<=") - 2);
        if(stod(var_finder(calculator(left_side))) <= stod(var_finder(calculator(right_side)))) {
            return line.substr(line.find("THEN") + 4,  line.find("ELSE") - line.find("THEN") - 4);
        } else {
            return line.substr(line.find("ELSE") + 4);
        }
    }
    else if(line.find(">=") != std::string::npos) {
        string left_side = line.substr(2, line.find(">=") - 2);
        string right_side = line.substr(line.find(">=") + 2, line.find("THEN") - line.find(">=") - 2);
        if(stod(var_finder(calculator(left_side))) >= stod(var_finder(calculator(right_side)))) {
            return line.substr(line.find("THEN") + 4,  line.find("ELSE") - line.find("THEN") - 4);
        } else {
            return line.substr(line.find("ELSE") + 4);
        }
    }
    else if(line.find("!=") != std::string::npos) {
        string left_side = line.substr(2, line.find("!=") - 2);
        string right_side = line.substr(line.find("!=") + 2, line.find("THEN") - line.find("!=") - 2);
        if(stod(var_finder(calculator(left_side))) != stod(var_finder(calculator(right_side)))) {
            return line.substr(line.find("THEN") + 4,  line.find("ELSE") - line.find("THEN") - 4);
        } else {
            return line.substr(line.find("ELSE") + 4);
        }
    }
    else if(line.find("==") != std::string::npos) {
        string left_side = line.substr(2, line.find("==") - 2);
        string right_side = line.substr(line.find("==") + 2, line.find("THEN") - line.find("==") - 2);
        if(stod(var_finder(calculator(left_side))) == stod(var_finder(calculator(right_side)))) {
            return line.substr(line.find("THEN") + 4,  line.find("ELSE") - line.find("THEN") - 4);
        } else {
            return line.substr(line.find("ELSE") + 4);
        }
    }
    else if(line.find("<") != std::string::npos) {
        string left_side = line.substr(2, line.find("<") - 2);
        string right_side = line.substr(line.find("<") + 1, line.find("THEN") - line.find("<") - 1);
        if(stod(var_finder(calculator(left_side))) < stod(var_finder(calculator(right_side)))) {
            return line.substr(line.find("THEN") + 4,  line.find("ELSE") - line.find("THEN") - 4);
        } else {
            return line.substr(line.find("ELSE") + 4);
        }
    }
    else if(line.find(">") != std::string::npos) {
        string left_side = line.substr(2, line.find(">") - 2);
        string right_side = line.substr(line.find(">") + 1, line.find("THEN") - line.find(">") - 1);
        if(stod(var_finder(calculator(left_side))) > stod(var_finder(calculator(right_side)))) {
            return line.substr(line.find("THEN") + 4,  line.find("ELSE") - line.find("THEN") - 4);
        } else {
            return line.substr(line.find("ELSE") + 4);
        }
    }
    return 0;
}
int main() {
    bool end = false;
    int num = 0;
    while(true) {
        num++;
        string chl = "Challenge" + to_string(num);
        ifstream input(chl + ".inp");
        if(input.is_open() == false) return 0;
        ofstream output(chl + ".out", fstream::out);
        string line, var = "";
        int counter;
        bool is_double;
        string left_side, right_side, result;

        //While loop for getting given lines from .inp
        while (getline(input, line)) {
            is_double = false;
            line = line_arranger(line);
            if (line.substr(0, 3) == "OUT") {
                for (int i = 0; i < vector_of_doubles.size(); i++) {
                    if (vector_of_doubles[i].name == line.substr(3)) {
                        output << vector_of_doubles[i].value;
                    }
                }
                for (int i = 0; i < vector_of_ints.size(); i++) {
                    if (vector_of_ints[i].name == line.substr(3)) {
                        output << vector_of_ints[i].value;
                    }
                }
            }
            if(line.substr(0, 4) == "LOOP") {
                int number_pos = line.find("TIMES") + 5;
                counter = stoi(var_finder(calculator(line.substr(number_pos))));
                line = line.substr(4, line.find("TIMES") - 4);
            } else {
                counter = 1;
            }
            for(int i = counter; counter > 0; counter--) {
                right_side = line.substr(line.find('=') + 1);
                if(right_side.find("IF") != std::string::npos) {
                    right_side = boolean_process(right_side);
                }
                result = var_finder(calculator(right_side));
                if (count(line.begin(), line.end(), '=') > 0) {
                    left_side = line.substr(0, line.find_first_of('='));
                }
                if (count(result.begin(), result.end(), '.') == 1) {
                    is_double = true;
                }
                var_declarer(left_side, result, is_double);
            }
        }
        vector_of_doubles.clear();
        vector_of_ints.clear();
    }
    return 0;
}