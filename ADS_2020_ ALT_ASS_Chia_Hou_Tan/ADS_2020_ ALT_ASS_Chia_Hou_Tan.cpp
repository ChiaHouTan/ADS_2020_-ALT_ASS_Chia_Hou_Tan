// ADS_2020_ ALT_ASS_Chia_Hou_Tan.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <algorithm> 
#include <fstream>      // file stream
#include <string>       // getline(), stoi(), stod()
#include <sstream>      // string stream
#include <string.h> 
#include "Measure.h"
#include <regex>
#include <iomanip> 
using namespace std;



void printAll(vector<Measure>& measureV);
// Read the Fileand Input the Data
void parseLine(const string& str, vector<Measure>& measureV);
void InputFileStream(string filename, vector<Measure>& measureV);
void startMenu();
void byAllRegion(vector<Measure>& measureV);
vector<string> uniqueRegion(vector<Measure>& measureV);
void byOneRegion(vector<Measure>& measureV);
vector<string> uniqueID(vector<Measure>& measureV);
void dateRange(vector<Measure>& measureV);
vector<string> filterHighestTurbine(vector<vector<string>>& resultBefore);
void sortAsc(vector<Measure>& measureV);
void sortDesc(vector<Measure>& measureV);
bool sortByPeakPowerAsc(Measure& a, Measure& b);
bool sortByPeakPowerDesc(Measure& a, Measure& b);
void writeFileByPeakPowerAsc(vector<Measure>& measureV);
void writeFileByPeakPowerDesc(vector<Measure>& measureV);
void writeFileByAllRegion(vector<vector<string>>& allRegion);
void writeFileByOneRegion(string region, vector<vector<string>>& allRegion);
void writeFileDateRange(string startDate, string endDate, vector<vector<string>>& result);


//Main
int main()
{
    time_t start, end;

    time(&start);

    // unsync the I/O of C and C++.
    ios_base::sync_with_stdio(false);

    vector<Measure> measureV;

    string filename;
    cout << "Please enter the input fileName..." << "\n";
    cin >> filename;
    cout << endl;

    InputFileStream(filename, measureV);
      //printAll(measureV);

    bool quit = false;


    while (quit == false) {
        int action;
        startMenu();
        cout << "\nEnter action: (0-6)> " << endl;
        cin >> action;

        switch (action) {

        case 0:
            cout << "Shutting down" << endl;
            quit = true;
            break;
        case 1:
            byAllRegion(measureV);
            break;
        case 2:
            byOneRegion(measureV);
            break;
        case 3:
            dateRange(measureV);
            break;
        case 4:
            sortAsc(measureV);
            break;
        case 5:
            sortDesc(measureV);
            break;
        }

    }

    cout << endl;
    time(&end);
    double time_taken = double(end - start);
    cout << "Time taken by process is : " << fixed
        << time_taken << setprecision(5);
    cout << " sec " << endl;

    
}



void printAll(vector<Measure>& measureV) //testing of printing the vector
{
    cout << "ID \t\t" << "Status \t" << "PeakPower \t" << "MachineTemp\t" << "TempUnits\t" << "WindSpeed\t" << "SpeedUnit\t" << "MewasureDate\t"<< "MeasreTime\t" << "Region" << endl;
    for (int i = 0; i < measureV.size(); i++) {
        cout << measureV.at(i).getID() << "\t"
            << measureV.at(i).getStatus() << "\t"
            << measureV.at(i).getPeakPower() << "\t\t"
            << measureV.at(i).getMachineTemp() << "\t\t"
            << measureV.at(i).getTempUnits() << "\t\t"
            << measureV.at(i).getWindSpeed() << "\t\t"
            << measureV.at(i).getSpeedUnits() << "\t\t"
            << measureV.at(i).getMeasureDate() << "\t"
            << measureV.at(i).getMeasureTime() << " \t"
            << measureV.at(i).getRegion()
            <<endl;


    }
}  

void parseLine(string& str, vector<Measure>& measureV) { //read file data then input to the class of vector

    stringstream strStream(str); //create string stream from the string

    string id;
    string status;
    int peakPower;
    double machineTemp;
    string tempUnits;
    double windSpeed;
    string speedUnits;
    string measureDate;
    string measureTime;
    string region;

    try
    {
        string str;

        getline(strStream, id, ',');

        getline(strStream, status, ',');

        getline(strStream, str, ',');
        peakPower = stoi(str);

        getline(strStream, str, ',');
        machineTemp = stod(str);

        getline(strStream, tempUnits, ',');

        getline(strStream, str, ',');
        windSpeed = stod(str);

        getline(strStream, speedUnits, ',');

        getline(strStream, measureDate, ',');

        getline(strStream, measureTime, ',');

        getline(strStream, region, ',');

    }
    catch (std::invalid_argument const& e)
    {
        cout << "Bad input: std::invalid_argument thrown" << '\n';
    }
    catch (std::out_of_range const& e)
    {
        cout << "Integer overflow: std::out_of_range thrown" << '\n';
    }



    Measure m = Measure();
    m = Measure(id, status, peakPower, machineTemp, tempUnits, windSpeed,speedUnits,measureDate,measureTime,region);

    measureV.push_back(m);

}

void InputFileStream(string filename, vector<Measure>& measureV) { //reading file
    time_t startfile, endfile;

    time(&startfile);

    cout << "Reading from comma-delimited text file." << endl;

    string line;
    ifstream inStream(filename); // open file as input file stream

    if (inStream.good())  // if file opened successfully, and not empty
    {
        getline(inStream, line);  //to ignore firstline
        while (getline(inStream, line))   // read a line until false returned , getline() from <string> library
        {
            parseLine(line, measureV);
        }

        inStream.close();

        cout << "Successfully Load from Sales File" << endl;
        cout << endl;
    }
    else
        cout << "Unable to open file, or file is empty.";

    cout << endl;
    time(&endfile);
    double time_taken = double(endfile - startfile);
    cout << "Time taken by input file is : " << fixed
        << time_taken << setprecision(5);
    cout << " sec " << endl << endl;

}

void startMenu() {    //start menu text for option
    cout << "0) Shutting Down" << endl;
    cout << "1) Create All Region Active Record" << endl;
    cout << "2) Create Input Region Active Record" << endl;
    cout << "3) Create Input Date Range Highest Turbine Record" << endl;
    cout << "4) Create Sort By Peak Power Asc Record" << endl;
    cout << "5) Create Sort By Peak Power Desc Record" << endl;
}


//by All Region 
void byAllRegion(vector<Measure>& measureV) {   //to search all active turbine of each region
    vector<string> uniRegion;
    uniRegion = uniqueRegion(measureV);   //using unique to filter all unique value only with no duplicate
    
    vector<vector<string>> allRegion;

    for (int a = 0; a < uniRegion.size(); a++) {
        int totalTurbine = 0;
        int totalPeakPower = 0;
        double totalWindSpeed = 0;
        double averageWindSpeed = 0;
        vector<string> result;

        for (int i = 0; i < measureV.size(); i++) {
            if (measureV.at(i).getStatus() == "Active")
            {
                if (measureV.at(i).getRegion() == uniRegion.at(a))      
                {
                    totalTurbine++;                                                     //looping to calculate total of turbine and use it to get average of windspeed
                    totalPeakPower = totalPeakPower + measureV.at(i).getPeakPower(); 
                    totalWindSpeed = totalWindSpeed + measureV.at(i).getWindSpeed();
                }
            }

        }

        averageWindSpeed = totalWindSpeed / totalTurbine;

        result.push_back(uniRegion.at(a));                      //result is the data of each region with active turbine 
        result.push_back(to_string(totalTurbine));
        result.push_back(to_string(totalPeakPower));
        result.push_back(to_string(averageWindSpeed));

        allRegion.push_back(result);     //then save it to vector of vector of all each region total turbine, total peak power and average wind speed
    }

    //for (int i = 0; i < allRegion.size(); i++) {          //testing code of the allRegion print out
    //    for (int j = 0; j < allRegion[i].size(); j++)
    //        cout << allRegion[i][j] << " ";
    //    cout << endl;
    //}
    writeFileByAllRegion(allRegion);      //lastly write out to html file

   
}

vector<string> uniqueRegion(vector<Measure>& measureV) {     //to get each unique value
    vector<string> v;
    for (int i = 0; i < measureV.size(); i++) {
        v.push_back(measureV.at(i).getRegion());
    }

    sort(v.begin(), v.end());
    auto iter = unique(v.begin(), v.end());
    v.resize(distance(v.begin(), iter));
    return v;
}

//By Region(one) user input
void byOneRegion(vector<Measure>& measureV) {     //to get one region only by user input of total turbine, total peek power and average wind speed, same coding as allRegion but searching for 1 region only
    bool regionCheck = false;
    string region;

    cout << "Please enter a region" << endl;
    cin >> region;
    transform(region.begin(), region.end(), region.begin(), ::toupper);

    vector<string> uniRegion;
    uniRegion = uniqueRegion(measureV);

    vector<vector<string>> allRegion;

    for (int i = 0; i < uniRegion.size(); i++)
    {
        if (uniRegion.at(i) == region)
        {
            regionCheck = true;
                int totalTurbine = 0;
                int totalPeakPower = 0;
                double totalWindSpeed = 0;
                double averageWindSpeed = 0;
                vector<string> result;

                for (int i = 0; i < measureV.size(); i++) {
                    if (measureV.at(i).getStatus() == "Active")
                    {
                        if (measureV.at(i).getRegion() == region)
                        {
                            totalTurbine++;
                            totalPeakPower = totalPeakPower + measureV.at(i).getPeakPower();
                            totalWindSpeed = totalWindSpeed + measureV.at(i).getWindSpeed();
                        }
                    }

                }

                averageWindSpeed = totalWindSpeed / totalTurbine;

                result.push_back(region);
                result.push_back(to_string(totalTurbine));
                result.push_back(to_string(totalPeakPower));
                result.push_back(to_string(averageWindSpeed));

                allRegion.push_back(result);
            
        }
    }

    //for (int i = 0; i < allRegion.size(); i++) {        //testing code of print out the result
    //    for (int j = 0; j < allRegion[i].size(); j++)
    //        cout << allRegion[i][j] << " ";
    //    cout << endl;
    //}

   

    if (regionCheck == false)
    {
        cout << "no such Region exist, please try again" << endl;    //if no such region print the error else write out the html file
    }
    else {
        writeFileByOneRegion(region, allRegion);
    }

}

vector<string> uniqueID(vector<Measure>& measureV) {   //same as unique region but this out is to take out each unique ID from file
    vector<string> v;
    for (int i = 0; i < measureV.size(); i++) {
        v.push_back(measureV.at(i).getID());
    }

    sort(v.begin(), v.end());
    auto iter = unique(v.begin(), v.end());
    v.resize(distance(v.begin(), iter));

    return v;
}


//By Date Range
void dateRange(vector<Measure>& measureV) {     //search the data between range of date
    string startDate;
    string endDate;
    cout << "Please enter the start date...(dd/mm/yyyy)" << endl;  //only around 1/1/2021, cannot be 01/01/2021 and cant put out error if wrong date(e.g 15345) because of date is string
    cin >> startDate;
    cout << "Please enter the end date...(dd/mm/yyyy)" << endl;
    cin >> endDate;

    vector<string> uniRegion;
    uniRegion = uniqueRegion(measureV);

    vector<string> uniID;
    uniID = uniqueID(measureV);

    vector<vector<string>>result;

    for (int a = 0; a < uniRegion.size(); a++) {      //first looping for unique region cause record require the higest turbine each region
        vector<vector<string>> resultBefore;

        for (int c = 0; c < uniID.size(); c++)   //then search for each unique ID loop
        {
            int totalTurbine = 0;
            int totalPeakPower = 0;
             double totalMachineTemp = 0;
            double averageMachineTemp = 0;
            double averagePeakPower = 0;
            vector<string> dateRangeData;

            for (int b = 0; b < measureV.size(); b++)
            {
                        if(measureV.at(b).getRegion() == uniRegion.at(a) && measureV.at(b).getID() == uniID.at(c)) //then as code show to check is the data is the same region as first loop and same id as second loop
                        { 
                            if (measureV.at(b).getMeasureDate() >= startDate && measureV.at(b).getMeasureDate() <= endDate) //then check is the date in range
                            {
                                 /*cout << measureV.at(b).getID() << endl;
                                 cout << measureV.at(b).getRegion() << endl;*/
                                 totalTurbine++;
                                 totalPeakPower = totalPeakPower + measureV.at(b).getPeakPower();
                                 totalMachineTemp = totalMachineTemp + measureV.at(b).getMachineTemp();    //id do get the total turbine, total peak power and total machine temp of each id and  each region
                            }
                            
                        }
             }
            if (totalTurbine != 0)    //check is turbine id more than 0 so wont cause error of being no data can search
            {
                averagePeakPower = totalPeakPower / totalTurbine;
                averageMachineTemp = totalMachineTemp / totalTurbine;       //then calculate each average of the data neeed for record
                dateRangeData.push_back(uniID.at(c));
                dateRangeData.push_back(to_string(averagePeakPower));
                dateRangeData.push_back(to_string(averageMachineTemp));    
                dateRangeData.push_back(uniRegion.at(a));
                resultBefore.push_back(dateRangeData);                    //then add to the vector of all unique ID data with same region
            }
            
        }
        result.push_back(filterHighestTurbine(resultBefore));    //finally filter the all unique ID with same Region inside the region loop to get highest turbine with average peek power spend
                                                                //result will including all highest turbine with average peek power each region
        
    }
    if (result.empty())
    {
        cout << "Data had not been found or wrong date inout" << endl;
    }else {
       /* for (int j = 0; j < result.size(); j++) {
                for (int k = 0; k < result[j].size(); k++)
                {
                    cout << result[j][k] << " ";
                }
                cout << endl;
            }*/
        writeFileDateRange(startDate, endDate, result);
    }
   



}

vector<string> filterHighestTurbine(vector<vector<string>>& resultBefore) {  //as saying above, this is to get the highest average peek power by compare each of peek power as i know I save average peek on vector[1]
    string x = "";
    vector<string> highest;
    for (int i = 0; i < resultBefore.size(); i++) {
        if(resultBefore[i][1] > x)
            { 
            
            x = resultBefore[i][1];
            highest.clear();
            for (int j = 0; j < resultBefore[i].size(); j++)
            {
                highest.push_back(resultBefore[i][j]);
            }
        
        }
    }

    return highest;

}

//BY Peek Power Sort
void sortAsc(vector<Measure>& measureV) {    
    sort(measureV.begin(), measureV.end(), sortByPeakPowerAsc);
    //printAll(measureV);
    writeFileByPeakPowerAsc(measureV);
}

void sortDesc(vector<Measure>& measureV) {
    sort(measureV.begin(), measureV.end(), sortByPeakPowerDesc);
   // printAll(measureV);
    writeFileByPeakPowerDesc(measureV);
}

//bool sort
bool sortByPeakPowerAsc(Measure& a, Measure& b) //function to sort peakPower Asc
{
    return (a.getPeakPower() < b.getPeakPower());
}

bool sortByPeakPowerDesc(Measure& a, Measure& b) //function to sort peakPower Asc
{
    return (a.getPeakPower() > b.getPeakPower());
}



//Write File to Html
void writeFileByPeakPowerAsc(vector<Measure>& measureV) {
    ofstream MyFile("byPeakPowerAsc.html");

    MyFile << "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>" << "\n" <<
        "<html>" << "\n" <<
        "<head>" << "\n" <<
        "<meta http - equiv = 'content-type' content = 'text/html; charset=utf-8'>" << "\n" <<
        "<meta name = 'generator' content = 'PSPad editor, www.pspad.com'>" << "\n" <<
        "<title>" << "By PeakPower Asc Records" << "</title>" << "\n" <<
        "<style>" <<
        "table{" << "\n" <<
        "margin-top: 10px;" << "\n" <<
        "width: 90 %;" << "\n" <<
        "}" << "\n" <<
        "tr:nth-child(even) { background-color: #f2f2f2; }" << "\n" <<
        "th{" << "\n" <<
        "background-color: #99FFFF;" << "\n" <<
        "}" << "\n" <<
        ".center{" << "\n" <<
        " margin-left: auto;" << "\n" <<
        "margin-right: auto;" << "\n" <<
        "}" <<
        "</style>" << "\n" <<
        " </head>" << "\n" <<
        " <body>" << "\n" <<
        "<h1>By PeakPower Asc Records</h1>" << "\n" <<
        "<table class = 'center' cellpadding='5'>" << "\n" <<
        "<tr>" << "\n" <<
        "<th>ID</th>" << "\n" <<
        "<th>PeakPower</th>" << "\n" <<
        "<th>WindSpeed</th>" << "\n" <<
        "<th>MeasureDate</th>" << "\n" <<
        "<th>MeasureTime</th>" << "\n" <<
        "<th>Region</th>" << "\n" <<
        "</tr>" << "\n";

    for (int i = 0; i < measureV.size(); i++) {

        string id = measureV.at(i).getID();
        int peakPower = measureV.at(i).getPeakPower();
        double windSpeed = measureV.at(i).getWindSpeed();
        string measureDate = measureV.at(i).getMeasureDate();
        string measureTime = measureV.at(i).getMeasureTime();
        string region = measureV.at(i).getRegion();

        MyFile <<
            "<tr>" << "\n" <<
            "<td>" << id << "</td>" << "\n" <<
            "<td>" << peakPower << "</td>" << "\n" <<
            "<td>" << windSpeed << "</td>" << "\n" <<
            "<td>" << measureDate << "</td>" << "\n" <<
            "<td>" << measureTime << "</td>" << "\n" <<
            "<td>" << region << "</td>" << "\n" <<
            "</tr>" << "\n";
    }

    MyFile <<
        " </table>" << "\n" <<

        "</body>" << "\n" <<
        "</html>";


    // Close the file
    MyFile.close();

    cout << "File Write out Successfully" << endl << endl;
}

void writeFileByPeakPowerDesc(vector<Measure>& measureV) {
    ofstream MyFile("byPeakPowerDesc.html");

    MyFile << "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>" << "\n" <<
        "<html>" << "\n" <<
        "<head>" << "\n" <<
        "<meta http - equiv = 'content-type' content = 'text/html; charset=utf-8'>" << "\n" <<
        "<meta name = 'generator' content = 'PSPad editor, www.pspad.com'>" << "\n" <<
        "<title>" << "By PeakPower Desc Records" << "</title>" << "\n" <<
        "<style>" <<
        "table{" << "\n" <<
        "margin-top: 10px;" << "\n" <<
        "width: 90 %;" << "\n" <<
        "}" << "\n" <<
        "tr:nth-child(even) { background-color: #f2f2f2; }" << "\n" <<
        "th{" << "\n" <<
        "background-color: #99FFFF;" << "\n" <<
        "}" << "\n" <<
        ".center{" << "\n" <<
        " margin-left: auto;" << "\n" <<
        "margin-right: auto;" << "\n" <<
        "}" <<
        "</style>" << "\n" <<
        " </head>" << "\n" <<
        " <body>" << "\n" <<
        "<h1>By PeakPower Desc Records</h1>" << "\n" <<
        "<table class = 'center' cellpadding='5'>" << "\n" <<
        "<tr>" << "\n" <<
        "<th>ID</th>" << "\n" <<
        "<th>PeakPower</th>" << "\n" <<
        "<th>WindSpeed</th>" << "\n" <<
        "<th>MeasureDate</th>" << "\n" <<
        "<th>MeasureTime</th>" << "\n" <<
        "<th>Region</th>" << "\n" <<
        "</tr>" << "\n";

        for (int i = 0; i < measureV.size(); i++) {

            string id = measureV.at(i).getID();
            int peakPower = measureV.at(i).getPeakPower();
            double windSpeed = measureV.at(i).getWindSpeed();
            string measureDate = measureV.at(i).getMeasureDate();
            string measureTime = measureV.at(i).getMeasureTime();
            string region = measureV.at(i).getRegion();

            MyFile <<
                "<tr>" << "\n" <<
                "<td>" << id << "</td>" << "\n" <<
                "<td>" << peakPower << "</td>" << "\n" <<
                "<td>" << windSpeed << "</td>" << "\n" <<
                "<td>" << measureDate << "</td>" << "\n" <<
                "<td>" << measureTime << "</td>" << "\n" <<
                "<td>" << region << "</td>" << "\n" <<
                "</tr>" << "\n";
        }
        
        MyFile <<
        " </table>" << "\n" <<

        "</body>" << "\n" <<
        "</html>";


    // Close the file
    MyFile.close();

    cout << "File Write out Successfully" << endl << endl;
}

void writeFileByAllRegion(vector<vector<string>>& allRegion) {
    ofstream MyFile("byRegionActive.html");

    MyFile << "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>" << "\n" <<
        "<html>" << "\n" <<
        "<head>" << "\n" <<
        "<meta http - equiv = 'content-type' content = 'text/html; charset=utf-8'>" << "\n" <<
        "<meta name = 'generator' content = 'PSPad editor, www.pspad.com'>" << "\n" <<
        "<title>" << "By Region Active Records" << "</title>" << "\n" <<
        "<style>" <<
        "table{" << "\n" <<
        "margin-top: 10px;" << "\n" <<
        "width: 90 %;" << "\n" <<
        "}" << "\n" <<
        "tr:nth-child(even) { background-color: #f2f2f2; }" << "\n" <<
        "th{" << "\n" <<
        "background-color: #99FFFF;" << "\n" <<
        "}" << "\n" <<
        ".center{" << "\n" <<
        " margin-left: auto;" << "\n" <<
        "margin-right: auto;" << "\n" <<
        "}" <<
        "</style>" << "\n" <<
        " </head>" << "\n" <<
        " <body>" << "\n" <<
        "<h1>By Region Active Records</h1>" << "\n" <<
        "<table class = 'center' cellpadding='5'>" << "\n" <<
        "<tr>" << "\n" <<
        "<th>Region</th>" << "\n" <<
        "<th>Total Turbines</th>" << "\n" <<
        "<th>Total Peak Power</th>" << "\n" <<
        "<th>Average Wind Speed</th>" << "\n" <<
        "</tr>" << "\n";

    for (int i = 0; i < allRegion.size(); i++) {
        MyFile <<
            "<tr>" << "\n";
        for (int j = 0; j < allRegion[i].size(); j++)
        {
            MyFile <<
                "<td>" << allRegion[i][j] << "</td>" << "\n";
         }
        MyFile <<
        "</tr>" << "\n";

     }

    MyFile <<
        " </table>" << "\n" <<

        "</body>" << "\n" <<
        "</html>";


    // Close the file
    MyFile.close();

    cout << "File Write out Successfully" << endl << endl;
}

void writeFileByOneRegion(string region, vector<vector<string>>& allRegion) {
    ofstream MyFile("byOneRegionActive.html");

    MyFile << "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>" << "\n" <<
        "<html>" << "\n" <<
        "<head>" << "\n" <<
        "<meta http - equiv = 'content-type' content = 'text/html; charset=utf-8'>" << "\n" <<
        "<meta name = 'generator' content = 'PSPad editor, www.pspad.com'>" << "\n" <<
        "<title>" << "By " << region << " Region Active Records" << "</title>" << "\n" <<
        "<style>" <<
        "table{" << "\n" <<
        "margin-top: 10px;" << "\n" <<
        "width: 90 %;" << "\n" <<
        "}" << "\n" <<
        "tr:nth-child(even) { background-color: #f2f2f2; }" << "\n" <<
        "th{" << "\n" <<
        "background-color: #99FFFF;" << "\n" <<
        "}" << "\n" <<
        ".center{" << "\n" <<
        " margin-left: auto;" << "\n" <<
        "margin-right: auto;" << "\n" <<
        "}" <<
        "</style>" << "\n" <<
        " </head>" << "\n" <<
        " <body>" << "\n" <<
        "<h1>By "<< region <<" Region Active Records</h1>" << "\n" <<
        "<table class = 'center' cellpadding='5'>" << "\n" <<
        "<tr>" << "\n" <<
        "<th>Region</th>" << "\n" <<
        "<th>Total Turbines</th>" << "\n" <<
        "<th>Total Peak Power</th>" << "\n" <<
        "<th>Average Wind Speed</th>" << "\n" <<
        "</tr>" << "\n";

    for (int i = 0; i < allRegion.size(); i++) {
        MyFile <<
            "<tr>" << "\n";
        for (int j = 0; j < allRegion[i].size(); j++)
        {
            MyFile <<
                "<td>" << allRegion[i][j] << "</td>" << "\n";
        }
        MyFile <<
            "</tr>" << "\n";

    }

    MyFile <<
        " </table>" << "\n" <<

        "</body>" << "\n" <<
        "</html>";


    // Close the file
    MyFile.close();

    cout << "File Write out Successfully" << endl << endl;
}

void writeFileDateRange(string startDate, string endDate, vector<vector<string>>& result) {
    ofstream MyFile("HighestTurbineEachRegion.html");

    MyFile << "<!DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'>" << "\n" <<
        "<html>" << "\n" <<
        "<head>" << "\n" <<
        "<meta http - equiv = 'content-type' content = 'text/html; charset=utf-8'>" << "\n" <<
        "<meta name = 'generator' content = 'PSPad editor, www.pspad.com'>" << "\n" <<
        "<title>" << "By Region Active Records" << "</title>" << "\n" <<
        "<style>" <<
        "table{" << "\n" <<
        "margin-top: 10px;" << "\n" <<
        "width: 90 %;" << "\n" <<
        "}" << "\n" <<
        "tr:nth-child(even) { background-color: #f2f2f2; }" << "\n" <<
        "th{" << "\n" <<
        "background-color: #99FFFF;" << "\n" <<
        "}" << "\n" <<
        ".center{" << "\n" <<
        " margin-left: auto;" << "\n" <<
        "margin-right: auto;" << "\n" <<
        "}" <<
        "</style>" << "\n" <<
        " </head>" << "\n" <<
        " <body>" << "\n" <<
        "<h1>Highest Turbine Each Region Records From " << startDate << " to " << endDate << "</h1>" << "\n" <<
        "<table class = 'center' cellpadding='5'>" << "\n" <<
        "<tr>" << "\n" <<
        "<th>ID</th>" << "\n" <<
        "<th>Average Peak Power</th>" << "\n" <<
        "<th>Average Machine Temp</th>" << "\n" <<
        "<th>Region</th>" << "\n" <<
        "</tr>" << "\n";

    for (int i = 0; i < result.size(); i++) {
        MyFile <<
            "<tr>" << "\n";
        for (int j = 0; j < result[i].size(); j++)
        {
            MyFile <<
                "<td>" << result[i][j] << "</td>" << "\n";
        }
        MyFile <<
            "</tr>" << "\n";

    }

    MyFile <<
        " </table>" << "\n" <<

        "</body>" << "\n" <<
        "</html>";


    // Close the file
    MyFile.close();

    cout << "File Write out Successfully" << endl <<endl;
}
