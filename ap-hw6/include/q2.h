#ifndef Q2_H
#define Q2_H

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<regex>
#include<vector>

namespace q2
{
/////////////////////////////////////////////////////////////////////////////////////////////
    struct Patient
    {
        std::string name;
        size_t age;
        size_t smokes;
        size_t area_q;
        size_t alkhol;
    };
/////////////////////////////////////////////////////////////////////////////////////////////
    static std::vector<Patient> read_file(std::string filename)
    {
        std::ifstream file(filename);
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string txt = buffer.str();
        std::regex pattern(R"((\w+)\ ?,(\w+)\ ?,(\d+)\,(\d+)\,(\d+)\,(\d+))");
        std::smatch match;
        std::vector<Patient> Patients{};

        while(std::regex_search(txt, match, pattern))
        {
            std::string first_name = match[1]; 
            std::string last_name = match[2];
            std::string name = first_name + " " + last_name;
            size_t age = std::stoi(match[3]);
            size_t smokes = std::stoi(match[4]);
            size_t area_q = std::stoi(match[5]);
            size_t alkhol = std::stoi(match[6]);
            Patients.push_back(Patient{ name, age, smokes, area_q, alkhol });
            txt = match.suffix().str();
        }
        return Patients;
    }
/////////////////////////////////////////////////////////////////////////////////////////////
    static bool comparison(Patient& a, Patient& b)
    {
        return 3*(a.age) + 5*(a.smokes) + 2*(a.area_q) + 4*(a.alkhol) > 3*(b.age) + 5*(b.smokes) + 2*(b.area_q) + 4*(b.alkhol); 
    }
/////////////////////////////////////////////////////////////////////////////////////////////
    static void sort(std::vector<Patient>& patients)
    {
        std::sort(patients.begin(), patients.end(), comparison);
    }
}

#endif //Q2_H