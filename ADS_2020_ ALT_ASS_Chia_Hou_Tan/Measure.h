#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Measure
{
private:
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

public:
    //Constructors
    Measure();
    Measure(string, string, int, double, string, double, string, string, string, string);
    
    //Getter
    string getID();
    string getStatus();
    int getPeakPower();
    double getMachineTemp();
    string getTempUnits();
    double getWindSpeed();
    string getSpeedUnits();
    string getMeasureDate();
    string getMeasureTime();
    string getRegion();

    //Setter
    void setID(string);
    void setStatus(string);
    void setPeakPower(int);
    void setMachineTemp(double);
    void setTempUnits(string);
    void setWindSpeed(double);
    void setSpeedUnits(string);
    void setMeasureDate(string);
    void setMeasureTime(string);
    void setRegion(string);

    //Copy Constructor
    Measure(const Measure&);

    // Overloaded Assignment operator=
    void operator = (const Measure&);

    ~Measure();
};

