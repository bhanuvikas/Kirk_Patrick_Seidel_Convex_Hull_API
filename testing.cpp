#include <bits/stdc++.h>
#include"input_reader.hpp"
#include"kirkpatrick_seidel.hpp"
using namespace std;
int main(){
    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin);
    #endif
    //! main function which calls the required classes to generate convex hull using kirk patrick seidel algorithm
    vector<pair<double,double>>points;
    input_reader obj(1);
    
   
    int cnt;
    cin>>cnt;
    obj.addPoint(cnt);
    points = obj.getPoints();
    for(auto it:points){
        cout<<it.first<<" "<<it.second<<endl;
    }
    ofstream fout;
    fout.open ("output.txt");
    kirkpatrick_seidel obj2(points);
    set<pair<double,double>>upper = obj2.getUpperhull();
    cout<<"upper hull"<<endl;
    for(auto it:upper){
        fout<<it.first<<" "<<it.second<<endl;
    }
    set<pair<double,double>>lower = obj2.getLowerhull();
    cout<<"Lower Hull"<<endl;
    vector<pair<double,double>>low;
    for(auto it:lower){
        low.push_back(it);
        //cout<<it.first<<" "<<it.second<<endl;
    }
    fout<<endl;
    reverse(low.begin(),low.end());
    for(auto it:low){
        fout<<it.first<<" "<<it.second<<endl;
    }
    fout<<upper.begin()->first<<" "<<upper.begin()->second<<endl;
    fout.close();
}