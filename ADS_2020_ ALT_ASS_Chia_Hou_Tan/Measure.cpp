#include "Measure.h"
#include <iostream>
#include <algorithm>
using namespace std;

Measure::Measure() {
    id ="";
    status ="";
    peakPower = 0;
    machineTemp = 0;
    tempUnits = "";
    windSpeed = 0;
    speedUnits = "";
    measureDate = "";
    measureTime = "";
    region = "";
}

Measure::Measure(string a, string b, int c, double d, string e, double f, string g, string h, string i, string j) {
    this->id = a;
    this->status = b;
    this->peakPower = c;
    this->machineTemp = d;
    this->tempUnits = e;
    this->windSpeed = f;
    this->speedUnits = g;
    this->measureDate = h;
    this->measureTime = i;
    this->region = j;
}

//Getter
string Measure::getID(){return id;}
string Measure::getStatus() { return status; }
int Measure::getPeakPower() { return peakPower; }
double Measure::getMachineTemp() { return machineTemp; }
string Measure::getTempUnits() { return tempUnits; }
double Measure::getWindSpeed() { return windSpeed; }
string Measure::getSpeedUnits() { return speedUnits; }
string Measure::getMeasureDate() { return measureDate; }
string Measure::getMeasureTime() { return measureTime; }
string Measure::getRegion() { return region; }

//Setter
void Measure::setID(string a) { this->id = a; }
void Measure::setStatus(string a) { this->status = a; }
void Measure::setPeakPower(int a) { this->peakPower = a; }
void Measure::setMachineTemp(double a) { this->machineTemp = a; }
void Measure::setTempUnits(string a) { this->tempUnits = a; }
void Measure::setWindSpeed(double a) { this->windSpeed = a; }
void Measure::setSpeedUnits(string a) { this->speedUnits = a; }
void Measure::setMeasureDate(string a) { this->measureDate = a; }
void Measure::setMeasureTime(string a) { this->measureTime = a; }
void Measure::setRegion(string a) { this->region = a; }

//Copy Constructor
Measure::Measure(const Measure& obj) {
    id = obj.id;
    status = obj.status;
    peakPower = obj.peakPower;
    machineTemp = obj.machineTemp;
    tempUnits = obj.tempUnits;
    windSpeed = obj.windSpeed;
    speedUnits = obj.speedUnits;
    measureDate = obj.measureDate;
    measureTime = obj.measureTime;
    region = obj.region;
}

// Overloaded Assignment operator=
void Measure::operator = (const Measure& other)
{
    id = other.id;
    status = other.status;
    peakPower = other.peakPower;
    machineTemp = other.machineTemp;
    tempUnits = other.tempUnits;
    windSpeed = other.windSpeed;
    speedUnits = other.speedUnits;
    measureDate = other.measureDate;
    measureTime = other.measureTime;
    region = other.region;
}

//Destructor
Measure::~Measure() {}