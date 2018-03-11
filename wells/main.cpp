#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
//#include <array>
#include "Hungarian.h"
#include "well.h"
#include "house.h"

using namespace std;

void printVector(vector<vector<double>> &v);
inline vector<string> splitString(string str, char splitter);
inline double distance(House *h, Well *w);


int main()
{
    const clock_t begin_time = clock();

    vector<House*> vctHouse;
    vector<Well*> vctWell;

    string str = "";
    int numberOfConnections = 0;
    int numberOfHouses = 0;
    int numberOfWells = 0;

    ifstream infile;
    /// there should be a Data.txt file in folder with .exe(or what ever)
    infile.open ("Data.txt");

    /// Reads Data.txt and assigns houses and wells their values and appends them to respective vectors
    while(infile >> str) // To get you all the lines.
    {
        vector<string> line = splitString(str, ';');

        if(str[0] == '%'){
            cout << "Number of wells : " << line[4] << endl;
            cout << "Number of house : " << line[2] << endl;
            cout << endl << endl;
            numberOfWells = stoi(line[4]);
            numberOfHouses = stoi(line[2]);
            numberOfConnections = numberOfHouses / numberOfWells;
        }
        else if(str[0] == 'H'){

            House *h = new House(std::stoi(line[1]),std::stoi(line[2]),line[3]);
            vctHouse.push_back(h);

        }else if(str[0] == 'W'){
            Well *w = new Well(std::stoi(line[1]),std::stoi(line[2]),line[3],numberOfConnections);
            vctWell.push_back(w);
        }else{
            cout << "Wrong type of input.\tinput : " << str <<endl;
        }
    }

    infile.close();


    unsigned int x = numberOfHouses;
    unsigned int y = numberOfWells;


    vector< vector<double> > matrix;
    /// 2d matrix is created here
    for(unsigned int i = 0; i < x; i++){
        vector<double> rowValue;
        vector<double> row;

        for(unsigned int j = 0; j < y; j++){
            rowValue.push_back(distance(vctHouse[i],vctWell[j]));
        }

        for(int n = 0; n < numberOfConnections; n++){
            for_each(rowValue.begin(),rowValue.end(),[&row](double d){

                row.push_back(d);
            });
        }
        matrix.push_back(row);
    }


    printVector(matrix);


    HungarianAlgorithm HungAlgo;
    vector<int> assignment;

    double cost = HungAlgo.Solve(matrix, assignment);

    for (unsigned int x = 0; x < matrix.size(); x++){
        std::cout << x << "," << assignment[x] % numberOfWells << "\t";
    }

    for (unsigned int x = 0; x < matrix.size(); x++){
        //std::cout << x << "," << assignment[x] % numberOfWells << "\t";
        cout << vctWell[assignment[x]% numberOfWells]->getTag() << " " << vctHouse[x]->getTag() << endl;
    }
    /// save results to output.txt
    ofstream myfile ("output.txt");
    if (myfile.is_open())
    {
        myfile << "%;h;" << to_string(numberOfHouses) << ";w;" <<  to_string(numberOfWells) << ";" << to_string(cost) << endl;
        for (unsigned int x = 0; x < matrix.size(); x++){
            //std::cout << x << "," << assignment[x] % numberOfWells << "\t";
            //cout <<vctWell[assignment[x]% numberOfWells]->getTag() << ";" << vctHouse[x]->getTag() << ";" << to_string(distance(vctHouse[assignment[x]% numberOfWells],vctWell[x])) << endl;
            //cout << vctWell[assignment[x]% numberOfWells]->getTag() << " " << vctHouse[x]->getTag() << endl;
            myfile <<vctWell[assignment[x]% numberOfWells]->getTag() << ";" << vctHouse[x]->getTag() << ";" << to_string( matrix[x][assignment[x]]) << endl; //distance(vctHouse[assignment[x]% numberOfWells],vctWell[x])) << endl;

        }

        myfile.close();
    }


    std::cout << "\ncost: " << cost << std::endl;
    // assignment is well
    // x is houses

    std::cout << float( clock () - begin_time ) /  CLOCKS_PER_SEC << endl;


    return 0;
}

/// prints given double matrix vector(s)
void printVector(vector<vector<double>> &v){
    for_each(v.begin(),v.end(),[](vector<double> vd){
        for_each(vd.begin(),vd.end(),[](double d){
            cout << d << "\t";
        });
        cout << endl;
    });
}
/// Splits give string by givin splitter
/// return: vector of splitted string peaces
inline vector<string> splitString(string str, char splitter) {

    vector<string> datas;
    string tmp = "";
    for(unsigned int i = 0; i < str.length(); i++){
        char c = str[i];

        if(c == splitter){
            datas.push_back(tmp);
            tmp = "";
            continue;
        }

        tmp += c;

    }

    return datas;

}
/// Euclidean distance between well and house
inline double distance(House *h, Well *w){

    int hX = h->getX();
    int hY = h->getY();

    int wX = w->getX();
    int wY = w->getY();

    return sqrt(pow(hX - wX,2) + pow(hY - wY,2));

}

