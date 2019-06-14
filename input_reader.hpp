#include <bits/stdc++.h>
using namespace std;
class input_reader{
    //! this class helps with taking input in different ways like user input etc 
    private:
        vector<pair<double,double>> points;
        int N;
    public:
        input_reader(int n){
            N=0;
            /*for(int i=0;i<n;i++){
                //adds points
            }*/
        }
        void addPoint(double x,double y){
            //! this function helps in adding the given point to input
            // adds point(x,y) to pints
            points.push_back(make_pair(x,y));
            N++;
        }
        void addPoint(int n){
            //! adds n new user inputted points
            double x,y;
            for(int i=0;i<n;i++){
                cout<<"enter point coordinates\n";
                cin>>x>>y;
                points.push_back(make_pair(x,y));
                N++;
            }
        }
        vector<pair<double,double>> getPoints(){
            //! gives points to the caller
            return points;
        }
        int getPointsSize(){
            //! gives no of points in data to caller
            return N;
        }
};