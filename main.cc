//
//  main.cc
//  troll.cc
//
//  Created by Guest User on 2014-07-25.
//
//
#include "yoo.cc"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int tp = 0;

int main(){
    for(int i = 0; i < 5;i++){
        while(true){
            if(floor.at(track_point) == '.'){
                check_around(i,track_point);
            }
            else
                if(out_of_tile){
                    break;
                }
                else{
                    track_point++;
                }
        }
        for(int i = 80; i < 1896; i++){
            if(floor.at(i) == '.'){
                tp = i;
                break;
            }
            else{i++;}
        }
        sort(chamber[i].begin(),chamber[i].end());
        cout << "chamber " << i << " has " << chamber[i].size() << " elements.";
        track_point = tp;
    }
    

    

    cout<<"chamber1 = { ";
    for(int i=0; i < chamber[0].size();i++){
        cout<<chamber[0][i]<<',';}
    cout<<'}'<<endl;
    
    cout<<"chamber2 = { ";
    for(int i=0; i < chamber[1].size();i++){
        cout<<chamber[1][i]<<',';}
    cout<<'}'<<endl;
    cout<<"chamber3 = { ";
    for(int i=0; i < chamber[2].size();i++){
        cout<<chamber[2][i]<<',';}
    cout<<'}'<<endl;
    cout<<"chamber4 = { ";
    for(int i=0; i < chamber[3].size();i++){
        cout<<chamber[3][i]<<',';}
    cout<<'}'<<endl;
    cout<<"chamber5 = { ";
    for(int i=0; i < chamber[4].size();i++){
        cout<<chamber[4][i]<<',';}
    cout<<'}'<<endl;
    cout<<endl;
    

}
