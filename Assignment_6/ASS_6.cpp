//  Zeyu Zhao
//  Xcode on Mac
//  Assignment_6
//
//  Created by zhaozeyu on 24/02/2018.
//  Copyright © 2018 zhaozeyu. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;
class MutualFund{
    string ticker;
    int date[300];
    double close[300];
    string mm;
    string yy;
    string dd;
public:
    void assignTicker(const string& str);
    void readHistoryFile(string);
    void report() const;
};

void MutualFund::assignTicker(const string& str){
    ticker = str;
}

void MutualFund::readHistoryFile(string fn){
    ifstream fin;
    fin.open(fn);
    if(!fin.is_open()){
        cout<<"Fail to open "<<fn<<endl;
        exit(1);
        }
    string* notsure = new string;
    getline(fin, *notsure);
    for(int i = 0; i < 300; i++){
        string nothing;
        getline(fin, nothing);
        size_t pos, pos2;
        pos2 = nothing.rfind(',', nothing.rfind(',', nothing.rfind(',')-1)-1);
        pos = nothing.rfind(',', nothing.rfind(',')-1);
        close[i] = stod(nothing.substr(pos2+1, pos-pos2-1));
        pos = nothing.find(',');
        string data = nothing.substr(0, pos);
        yy = nothing.substr(2,2);
        mm = nothing.substr(5,2);
        dd = nothing.substr(8,2);
        date[i] = 10000 * stoi(yy) + 100 * stoi(mm) + stoi(dd);
    }
    fin.close();
    delete notsure;
}

void MutualFund::report() const{
    double lmin, lmax;
    int start = 0;
    for(int i = 0; i < 300; i++){
        if (date[i] > (date[299]-9999)){
            start = i;
            break;
        }
    }
    lmin = close[start];
    lmax = close[start];
    for(int i = start; i < 300; i++){
        if (lmax < close[i]){
            lmax = close[i];
        }
        if (lmin > close[i]){
            lmin = close[i];
        }
    }
    double ave1, total1, ave2, total2;
    total1 = 0;
    for(int i = 250; i < 300; i++){
        total1 = total1 + close[i];
    }
    ave1 = total1/50;
    total2 = 0;
    for(int i = 100; i < 300; i++){
        total2 = total2 + close[i];
    }
    ave2 = total2/200;
    double Mavg = close[299]-ave2;
    string rec;
    if(Mavg > 5){
        rec = "Sell";
    }
    else if(Mavg < -5){
        rec = "Buy";
    }
    else{
        rec = "Hold";
    }
    cout<<"Fund: "<< ticker<<fixed<<setprecision(2)<<endl<<
    "Analysis Date: "<<mm<<"/"<<dd<<"/"<<yy<<endl<<
    "Latest Close: $"<<close[299]<<endl<<
    "Minimum for the last year = $"<<lmin<<endl<<
    "Maximum for the last year = $"<<lmax<<endl<<
    "50 day moving average = $"<<ave1<<endl<<
    "200 day moving average = $"<<ave2<<endl<<
    "% gain over 200 Day Moving Avg: "<<Mavg<<"%"<<endl<<
    "Recommendation: "<<rec<<endl<<endl;
}
int main(int argc, const char * argv[]) {
    MutualFund vbmfx;
    vbmfx.assignTicker("VTSMX");
    vbmfx.readHistoryFile("VTSMX.csv");  // You may change the input file location.
    vbmfx.report();
    
    MutualFund vtsmx;
    vtsmx.assignTicker("VFINX");
    vtsmx.readHistoryFile("VFINX.csv");
    vtsmx.report();
    return 0;
}
