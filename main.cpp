//
//  main.cpp
//  project
//
//  Created by Mariam Elsaqa on 11/27/20.
//  Copyright © 2020 None. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <utility>
#include <unordered_map>
#include <iterator>
#include<map>
#include<math.h>
#include<iomanip>
using namespace std;

vector<string> search(string searchword){
ifstream file;
string web[4],key1[4],key2[4],key3[4],k1[4],k2[4],k3[4],k4[4];
vector<string> vec;
file.open("Keyword.csv");
    for (int i =0; i<4 ; i++){
      getline(file, web[i],',');
      getline(file,k1[i],',');
      getline(file,k2[i],',');
      getline(file,k3[i],',');
      getline(file,k4[i],'\n');
      key1[i] = '"'+k1[i]+'"';
      key2[i] = '"'+k2[i]+'"';
      key3[i] = '"'+k3[i]+'"';
}
stringstream ss(searchword);
string word1,word2,word3,w1,w3;
getline(ss, w1,' ');
getline(ss, word2,' ');
getline(ss, w3,' ');
word1= '"'+ w1+'"';
word3= '"'+w3+'"';
for (int i=0;i<4;i++){
  //AND case
if (word2 == "AND" || word2 == "and"){
if((word1 == key1[i] || word1 == key2[i] || word1 == key3[i]) && (word3 == key1[i] || word3 == key2[i] || word3 == key3[i])){
//cout<< j++<<"."<<web[i]<< endl;
vec.push_back(web[i]);
}
}
//keyword with quotes
else if(searchword == key1[i] || searchword == key2[i] || searchword == key3[i]){
//cout<<j++<<"."<< web[i]<< endl;
vec.push_back(web[i]);
}
//OR case
else if (word2 == "OR" || word2 == "or"){
if(word1 == key1[i] || word3 == key1[i] || word1 == key2[i] || word3 == key2[i] ||word1 == key3[i] || word3 == key3[i]){
//cout<<j++<<"."<< web[i]<< endl;
vec.push_back(web[i]);
}
}
//keyword without quotes
else{
  if (w1 == k1[i] || word2 == k1[i] || w1 == k2[i] ||word2 == k2[i] || w1 == k3[i] || word2 == k3[i] ){
    //cout<<j++<<"."<<web[i]<<endl;
    vec.push_back(web[i]);
  }
}
}
return vec;
}

vector<double> CTR(string searchword, int index){
  ifstream file;
  fstream ofile;
  string web[4], numimpressions[4];
  static double impressions[4];
file.open("NumImpressions.csv");
ofile.open("NumImpressions.csv");
    for (int i =0; i<4 ; i++){
      getline(file, web[i],',');
      getline(file,numimpressions[i], '\n');
      //impressions[i] = stoi(numimpressions[i]);
      stringstream imp(numimpressions[i]);
    imp >>impressions[i] ;
    //cout<<impressions[i]<<endl;
    }
  vector<string> v;
v = search(searchword);
for(int i=0;i<v.size();i++){
for (int j=0;j<4;j++){
  if (v[i] == web[j]){
    impressions[j]++;}
}
}
for(int i=0;i<4;i++)
{
  //cout<<impressions[i]<<endl;
  ofile<<web[i]<<","<<impressions[i]<<"\n";
}
ifstream Cfile;
fstream oCfile;
string Cweb[4],Clicks[4];
int numClicks[4];
Cfile.open("NoClicks.csv");
oCfile.open("NoClicks.csv");
for(int i=0;i<4;i++){
  getline(Cfile,Cweb[i],',');
  getline(Cfile,Clicks[i],'\n');
  //numClicks[i] = stoi(Clicks[i]);
stringstream click(Clicks[i]);
    click >>numClicks[i] ;
    //cout<<Clicks[i]<<endl;
}
for(int i=0;i<4;i++){
  if(Cweb[i] == v[index-1]){
    numClicks[i]++;
  }
  oCfile<<Cweb[i]<<","<<numClicks[i]<<"\n";
}
vector<double> ctr;
double c[4];
for(int i=0; i<4;i++){
  c[i]=(numClicks[i]/impressions[i])*100;
  ctr.push_back(c[i]);
}
return ctr;
}

void ctrDisplay(string searchword){
  vector<string> v = search(searchword);
  ifstream file;
  fstream ofile;
  string web[4], numimpressions[4];
  double impressions[4];
file.open("NumImpressions.csv");
ofile.open("NumImpressions.csv");
    for (int i =0; i<4 ; i++){
      getline(file, web[i],',');
      getline(file,numimpressions[i], '\n');
      stringstream imp(numimpressions[i]);
    imp >>impressions[i] ;
    }
ifstream Cfile;
fstream oCfile;
string Cweb[4],Clicks[4];
int numClicks[4];
Cfile.open("NoClicks.csv");
oCfile.open("NoClicks.csv");
for(int i=0;i<4;i++){
  getline(Cfile,Cweb[i],',');
  getline(Cfile,Clicks[i],'\n');
stringstream click(Clicks[i]);
    click >>numClicks[i] ;
}
vector<double> ctr;
double c[4];
for(int i=0; i<4;i++){
  c[i]=(numClicks[i]/impressions[i])*100;
  ctr.push_back(c[i]);
}

unordered_map<string,double> mp;
for(int i=0;i<4;i++){
  mp[Cweb[i]]=ctr[i];
}
  vector<string> res;
      for(int i=0;i<v.size();i++)
    {
    res.push_back(v[i]);
  }
  string temp;
  if(res.size() >1){
  for(int j=0;j<res.size();j++){
       //cout<<mp[v[j]]<<endl;
      if(mp[v[j]] < mp[v[j+1]]){
        //cout<<mp[v[j]]<<endl;
        temp = v[j];
        v[j] = v[j+1];
        v.insert(v.begin()+1, temp);
      }
  }
  for(int i=0;i<res.size();i++){
    cout<<i+1<<"."<<" "<<v[i]<<endl;
    }}
    else{
      for(int i=0;i<v.size();i++){
     cout<<i+1<<"."<<" "<<v.at(i)<<endl;
        }
    }
}

void display(string answer, int choice){
  vector<string> vec;
  vector<double> ctr;
  cout<<"Search results:"<<endl;
  ctrDisplay(answer);
        /*vec = search(answer);
        for(int i=0;i<vec.size();i++){
          cout<<i+1<<"."<<" "<<vec.at(i)<<endl;
        }*/
        cout<<"Would you like to"<<endl;
        cout<<"1. Choose a webpage to open"<<endl;
        cout<<"2. New search"<<endl;
        cout<<"3. Exit"<<endl;
        cout<<"Type in your choice"<<endl;
        cin>> choice;
        if(choice > 0 && choice <4){
        if (choice == 3) {
            exit(1);
        }
        else if(choice == 1){
            cout<<"enter the number of webpage you want to open"<<endl;
            cin>>choice;
            ctr = CTR(answer,choice);
            /*for(int i=0;i<ctr.size();i++){
              cout<<ctr[i]<<endl;
            }*/
            for(int i=0;i<vec.size();i++){
              if (choice == i+1){
           cout<< "You're now viewing "<<vec[i]<<endl;}}
            cout<<"Would you like to"<<endl;
            cout<< "1. Back to search results"<<endl;
            cout<<"2. New Search"<<endl;
            cout<<"3. Exit"<<endl;
            cout<<"Type in your choice"<<endl;
            cin>>choice;
            if (choice>0 && choice <4){
                if (choice == 3) {
                    exit(1);
                }
                else if (choice == 2){
        cout<<"What do you want to search about (data, structures,complexity, machine, learning, programming, algorithms, data structures)"<<endl;
      cin.ignore();
      getline(cin,answer);
      cin.clear();
       display(answer,choice);
                }else{
                  display(answer, choice);
                }
            }else{
                cout<<"Not valid choice"<<endl;
            }
        }
            else{
        cout<<"What do you want to search about (data, structures,complexity, machine, learning, programming, algorithms, data structures)"<<endl;
      cin.ignore();
      getline(cin,answer);
      cin.clear();
       display(answer,choice);
            }
        }
        else{
          cout<<"Not Valid Answer"<<endl;
        }
}

void PageRank(string src[], string des[]){
  double PR[4] = {0.25, 0.25, 0.25, 0.25};
  double nrPR[4]={0.85,0.85,0.85,0.85};
  int C[4]; //counters
  unordered_map<string,string> mp;
    ifstream file;
  fstream ofile;
  string web[4], numimpressions[4];
  static double impressions[4];
file.open("NumImpressions.csv");
ofile.open("NumImpressions.csv");
    for (int i =0; i<4 ; i++){
      getline(file, web[i],',');
      getline(file,numimpressions[i], '\n');
      //impressions[i] = stoi(numimpressions[i]);
      stringstream imp(numimpressions[i]);
    imp >>impressions[i] ;
    //cout<<impressions[i]<<endl;
    }
    ifstream Cfile;
fstream oCfile;
string Cweb[4],Clicks[4];
int numClicks[4];
Cfile.open("NoClicks.csv");
oCfile.open("NoClicks.csv");
for(int i=0;i<4;i++){
  getline(Cfile,Cweb[i],',');
  getline(Cfile,Clicks[i],'\n');
stringstream click(Clicks[i]);
    click >>numClicks[i] ;
}
vector<double> ctr;
double c[4];
for(int i=0; i<4;i++){
  c[i]=(numClicks[i]/impressions[i])*100;
  ctr.push_back(c[i]);
}
   //connecting vertices in a map
  for(int i =0;i<7;i++){
    mp[src[i]] = des[i];
  }
  for(int i=0;i<7;i++){
      if(src[i] == "www.test1.com"){
      C[0]++;
    }
    if(src[i] == "www.test2.com"){
      C[1]++;
    }
    if(src[i] == "www.test3.com"){
      C[2]++;
    }
    if(src[i] == "www.test4.com"){
      C[3]++;
    }}
    for(int i=0;i<4;i++){
    if(mp[src[i]] == des[i]){
    PR[i] = PR[i]/C[i];
    nrPR[i] = 0.4 * nrPR[i] +((1-(0.1*impressions[i])/(1+0.1*impressions[i]))*nrPR[i]+((0.1*impressions[i])/(1+0.1*impressions[i]))*ctr[i])*0.6;
    }
}
}

void mapping(){
ifstream file;
file.open("WebGraph.csv");
string src[7],des[7];
for(int i =0;i<7;i++){
  getline(file,src[i],',');
  getline(file, des[i],'\n');
}
      PageRank (src, des);
}


int main(){
 int choice=0;
    string answer;
    cout<<"Welcome !"<<endl;
    cout<<"What would you like to do?"<<endl;
    cout<<"1. New Search"<<endl;
    cout<< "2. Exit"<<endl;

    cout<<"Type in your choice: "<<endl;
    cin>>choice;

    if (choice <3 && choice >0){
    if(choice == 2)
        exit(1);
    else{
      cout<<"What do you want to search about (data, structures,complexity, machine, learning, programming, algorithms, data structures)"<<endl;
      cin.ignore();
      getline(cin,answer);
      cin.clear();
       display(answer,choice);
    }}
    else{
        cout<< "Not Valid choice"<<endl;
      }
        
    return 0;
}

