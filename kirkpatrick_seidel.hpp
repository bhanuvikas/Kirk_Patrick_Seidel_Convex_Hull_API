#include <bits/stdc++.h>
using namespace std;
class kirkpatrick_bridge_builder{
    //! this class helps in building upper bridge and lower bridge using kirk patrick seidel algorithm
    private:
        double A;
        vector<pair<double,double>>initial_points;
        pair<pair<double,double>,pair<double,double>> upperBridge(vector<pair<double,double>>S){
            //! upper bridge builder function
            vector<pair<int,int>> lines,small,large,equal;
            vector<pair<double,double>>candidates;
            double K;
            cout<<"************************** "<<S.size()<<endl;
            if(S.size()==2){
                sort(S.begin(),S.end());
                return make_pair(S[0],S[1]);
            }
            lines = pairPoints(S);
            if(S.size()%2!=0)candidates.push_back(S[S.size()-1]);
            cout<<"pair points done\n";
            vector<double>slopes;
            // adding line slopes to slopes
            for(auto it : lines){
                int f=it.first,s=it.second;
                cout<<S[f].first<<" "<<S[f].second<<endl;
                cout<<S[s].first<<" "<<S[s].second<<endl;
                if(S[f].first==S[s].first){
                    if(S[f].second>S[s].second)candidates.push_back(S[f]);
                    else candidates.push_back(S[s]);  
                }
                else{
                    double slp=(S[f].second-S[s].second)/(S[f].first-S[s].first);
                    cout<<slp<<" "<<s<<"  +++++++++++++\n";
                    slopes.push_back(slp);
                }
            }
            if(slopes.size()==0)return upperBridge(candidates);
            K = medianSlope(slopes);
            cout<<"slope done"<<endl;
            cout<<K<<" ----slope\n";
            for(auto it : lines){
                int f=it.first,s=it.second;
                //***************************************what happens to points if their slope NAN
                if(S[f].first==S[s].first)continue;
                double temp = (S[f].second-S[s].second)/(S[f].first-S[s].first);
                if(temp<K)small.push_back(it);
                else if(temp==K){
                    equal.push_back(it);
                }
                else{
                    large.push_back(it);
                }
            }
            vector<pair<double,double>>MAX;
            double height=INT_MIN;
            for(auto it:S){
                double temp = it.second-K*it.first;
                if(temp>height){
                    MAX.clear();
                    MAX.push_back(it);
                    height = temp;
                }
                else if(temp==height){
                    MAX.push_back(it);
                }
            }
            sort(MAX.begin(),MAX.end());
            pair<double,double>pK,pM;
            pK = MAX[0];
            pM= MAX[MAX.size()-1];
            cout<<pK.first<<" "<<pK.second<<"-------\n";
            cout<<pM.first<<" "<<pM.second<<"-------\n";
            //step 8
            if(pK.first<=A&&pM.first>A)return make_pair(pK,pM);
            // step 9
            else if(pM.first<=A){
                for(auto it:large){
                    cout<<S[it.first].first<<" removed "<<S[it.first].second<<endl;
                    candidates.push_back(S[it.second]);
                }
                for(auto it:equal){
                    cout<<S[it.first].first<<" removed "<<S[it.first].second<<endl;
                    candidates.push_back(S[it.second]);
                }
                for(auto it:small){
                    candidates.push_back(S[it.first]);
                    candidates.push_back(S[it.second]);
                }
            }
            // step 10
            else if(pK.first>A){
                for(auto it:small){
                    cout<<S[it.second].first<<" removed "<<S[it.second].second<<endl;
                    candidates.push_back(S[it.first]);
                }
                for(auto it:equal){
                    cout<<S[it.second].first<<" removed "<<S[it.second].second<<endl;
                    candidates.push_back(S[it.first]);
                }
                for(auto it:large){
                    candidates.push_back(S[it.first]);
                    candidates.push_back(S[it.second]);
                }
            }
            return upperBridge(candidates);
        }
        double medianSlope(vector<double>slopes){
            //! find median slope among the given vector slopes
            cout<<"enetred median slopes "<<slopes.size()<<endl;
            sort(slopes.begin(),slopes.end());
            int sz = slopes.size();
            for(auto it:slopes)cout<<it<<endl;
            if(sz%2==0){
                return (slopes[sz/2]+slopes[sz/2-1])/2;
            }
            return slopes[slopes.size()/2];
        }
        vector<pair<int,int>> pairPoints(vector<pair<double,double>>points){
            //! selects n/2 points from n points and makes n/2 lines
            vector<pair<int,int>> lines;
            for(int i=0;i<points.size()-1;i+=2){
                if(points[i].first<=points[i+1].first)lines.push_back(make_pair(i,i+1));
                else lines.push_back(make_pair(i+1,i));
            }
            cout<<"printing lines"<<endl;
            for(auto it: lines){
                cout<<it.first<<" "<<it.second<<endl;
            }
            return lines;
        }
        pair<pair<double,double>,pair<double,double>> lowerBridge(vector<pair<double,double>>S){
            //! lower bridge builder function
            vector<pair<int,int>> lines,small,large,equal;
            vector<pair<double,double>>candidates;
            double K;
            cout<<"************************** "<<S.size()<<endl;
            if(S.size()==2){
                sort(S.begin(),S.end());
                return make_pair(S[0],S[1]);
            }
            lines = pairPoints(S);
            if(S.size()%2!=0)candidates.push_back(S[S.size()-1]);
            cout<<"pair points done\n";
            vector<double>slopes;
            // adding line slopes to slopes
            for(auto it : lines){
                int f=it.first,s=it.second;
                cout<<S[f].first<<" "<<S[f].second<<endl;
                cout<<S[s].first<<" "<<S[s].second<<endl;
                if(S[f].first==S[s].first){
                    if(S[f].second>S[s].second)candidates.push_back(S[s]);
                    else candidates.push_back(S[f]);  
                }
                else{
                    double slp=(S[f].second-S[s].second)/(S[f].first-S[s].first);
                    cout<<slp<<" "<<s<<"  +++++++++++++\n";
                    slopes.push_back(slp);
                }
            }
            if(slopes.size()==0)return lowerBridge(candidates);
            K = medianSlope(slopes);
            cout<<"slope done"<<endl;
            cout<<K<<" ----slope\n";
            for(auto it : lines){
                int f=it.first,s=it.second;
                //***************************************what happens to points if their slope NAN
                if(S[f].first==S[s].first)continue;
                double temp = (S[f].second-S[s].second)/(S[f].first-S[s].first);
                if(temp<K)small.push_back(it);
                else if(temp==K){
                    equal.push_back(it);
                }
                else{
                    large.push_back(it);
                }
            }
            vector<pair<double,double>>MAX;
            double height=INT_MAX;
            for(auto it:S){
                double temp = it.second-K*it.first;
                if(temp<height){
                    MAX.clear();
                    MAX.push_back(it);
                    height = temp;
                }
                else if(temp==height){
                    MAX.push_back(it);
                }
            }
            sort(MAX.begin(),MAX.end());
            pair<double,double>pK,pM;
            pK = MAX[0];
            pM= MAX[MAX.size()-1];
            cout<<pK.first<<" "<<pK.second<<"-------\n";
            cout<<pM.first<<" "<<pM.second<<"-------\n";
            //step 8
            if(pK.first<=A&&pM.first>A)return make_pair(pK,pM);
            // step 9
            else if(pM.first<=A){
                for(auto it:small){
                    cout<<S[it.first].first<<" removed "<<S[it.first].second<<endl;
                    candidates.push_back(S[it.second]);
                }
                for(auto it:equal){
                    cout<<S[it.first].first<<" removed "<<S[it.first].second<<endl;
                    candidates.push_back(S[it.second]);
                }
                for(auto it:large){
                    candidates.push_back(S[it.first]);
                    candidates.push_back(S[it.second]);
                }
            }
            // step 10
            else if(pK.first>A){
                for(auto it:large){
                    cout<<S[it.second].first<<" removed "<<S[it.second].second<<endl;
                    candidates.push_back(S[it.first]);
                }
                for(auto it:equal){
                    cout<<S[it.second].first<<" removed "<<S[it.second].second<<endl;
                    candidates.push_back(S[it.first]);
                }
                for(auto it:small){
                    candidates.push_back(S[it.first]);
                    candidates.push_back(S[it.second]);
                }
            }
            return lowerBridge(candidates);
        }
    public:
        kirkpatrick_bridge_builder(vector<pair<double,double>>S,double L){
            //! constructor of kirkpatrick bridge builder
            A=L;
            cout<<"In bridge finder the median line is "<<A<<endl;
            initial_points = S;
        }
        pair<pair<double,double>,pair<double,double>> getUpperBridge(){
            //! returns upper bridge to caller
            return upperBridge(initial_points);
        }
        pair<pair<double,double>,pair<double,double>> getLowerBridge(){
            // ! returns lower bridge to caller
            return lowerBridge(initial_points);
        }

};
class kirkpatrick_seidel{
    //! this class helps in building convex hull using kirk parick seidel algorithm
    private:
        ofstream Fout;
        set<pair<double,double>>upperhull;
        set<pair<double,double>>lowerhull;
        set<pair<double,double>>convexhull;
        vector<pair<double,double>> points;
        void convexHullGenerator(){
            //! this is the builder function of convex hull which calls required functions in a order suggested by the algorithm
            pair<double,double>pUmin,pUmax,pLmin,pLmax;
            pair<pair<double,double>,pair<double,double>>temp=pointUpperFinder();
            pUmin=temp.first;
            pUmax=temp.second;
            temp=pointLowerFinder();
            pLmin=temp.first;
            pLmax=temp.second;
            vector<pair<double,double>>T;
            T=pointsInRange(pUmin,pUmax);
            cout<<"printing points in range\n";
            for(auto it:T){
                cout<<it.first<<" "<<it.second<<endl;
            }
            upperhull = genUpperHull(pUmin,pUmax,T);
            T=pointsInRange(pLmin,pLmax);
            Fout<<endl;
            cout<<"\n\n***************,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.,.***************************\n\n";
            lowerhull = genLowerHull(pLmin,pLmax,T);
        }
        set<pair<double,double>>genUpperHull(pair<double,double>pmin,pair<double,double>pmax,vector<pair<double,double>>T){
            //!  upper hull builder function
            vector<pair<double,double>>Tleft,Tright;
            set<pair<double,double>> left_hull,right_hull;
            if(T.size()<=2){
                left_hull.insert(T.begin(),T.end());
                sort(T.begin(),T.end());
                Fout<<T[0].first<<" "<<T[0].second<<endl;
                Fout<<T[1].first<<" "<<T[1].second<<endl;
                return left_hull;
            }
            double A = medianFinder(T);
            for(int i=0;i<T.size();i++){
                if(T[i].first<A)Tleft.push_back(T[i]);
                else if(T[i].first>A)Tright.push_back(T[i]);
            }
            pair<double,double>pL,pR;
            kirkpatrick_bridge_builder obj(T,A);
            pair<pair<double,double>,pair<double,double>> temp=obj.getUpperBridge();
            pL=temp.first;
            pR=temp.second;
            cout<<"printing points given by upper bridge "<<pL.first<<" "<<pL.second<<endl;
            cout<<"printing points given by upper bridge "<<pR.first<<" "<<pR.second<<endl;

            Fout<<pL.first<<" "<<pL.second<<endl;
            Fout<<pR.first<<" "<<pR.second<<endl;
            
            Tleft = qualifiedPoints(pmin,pL,false,Tleft,pL);
            //printer(Tleft);
            Tright = qualifiedPoints(pR,pmax,false,Tright,pR);
            left_hull=genUpperHull(pmin,pL,Tleft);
            right_hull = genUpperHull(pR,pmax,Tright);
            left_hull.insert(right_hull.begin(),right_hull.end());
            
            return left_hull;
        }
        void printer(vector<pair<double,double>>T){
            //! prints the vector passed to it
            for(auto it: T){
                cout<<it.first<<" "<<it.second<<" testing"<<endl;
            }
        }
        vector<pair<double,double>> qualifiedPoints(pair<double,double>left,pair<double,double>right,bool needed,vector<pair<double,double>>T,pair<double,double>otherpoint){
           //! Tleft,Tright generator
            set<pair<double,double>> qpts;
            vector<pair<double,double>>Tnew;
            bool check=false;
            for(int i=0;i<T.size();i++){
                if(T[i]==left||T[i]==right)continue;
                if(orientation(left,right,T[i],needed)==needed)Tnew.push_back(T[i]);
            }
            Tnew.push_back(left);
            Tnew.push_back(right);
            return Tnew;
        }
        bool orientation(pair<double,double>p1,pair<double,double>p2,pair<double,double>p3,bool needed){
            //! returns true if clockwise and vice versa
            // points on the line are considered true
            // returns true if on the p3 is on the line or clockwise 
            cout<<"p1 "<<p1.first<<" "<<p1.second<<endl;
            cout<<"p2 "<<p2.first<<" "<<p2.second<<endl;
            cout<<"orientation start "<<p3.first<<" "<<p3.second<<endl;
            double val = (p2.second - p1.second) * (p3.first - p2.first) - 
              (p2.first - p1.first) * (p3.second - p2.second); 
            double cool=0.0;
            if(val>=cool)cout<<"clockwise "<<endl;
            else cout<<"anti clockwise"<<endl;
            if (val == cool) return !needed;  // colinear 
            return (val > cool)? true: false; // clock or counterclock wise
        }
        double medianFinder(vector<pair<double,double>>T){
            //! finds the median line which divides the plane into two equal sets of points 
            sort(T.begin(),T.end());
            int sz = T.size();
            if(sz%2==0){
                return (T[sz/2].first + T[sz/2-1].first)/2;
            }
            return T[sz/2].first;
        }
        set<pair<double,double>>genLowerHull(pair<double,double>pmin,pair<double,double>pmax,vector<pair<double,double>>T){
            //! lower hull builder function
            vector<pair<double,double>>Tleft,Tright;
            set<pair<double,double>> left_hull,right_hull;
            if(T.size()<=2){
                left_hull.insert(T.begin(),T.end());
                sort(T.begin(),T.end());
                Fout<<T[0].first<<" "<<T[0].second<<endl;
                Fout<<T[1].first<<" "<<T[1].second<<endl;
                return left_hull;
            }
            double A = medianFinder(T);
            for(int i=0;i<T.size();i++){
                if(T[i].first<A)Tleft.push_back(T[i]);
                else if(T[i].first>A)Tright.push_back(T[i]);
            }
            pair<double,double>pL,pR;
            kirkpatrick_bridge_builder obj(T,A);
            pair<pair<double,double>,pair<double,double>> temp=obj.getLowerBridge();
            pL=temp.first;
            pR=temp.second;
            cout<<"printing points given by lower bridge "<<pL.first<<" "<<pL.second<<endl;
            cout<<"printing points given by lower bridge "<<pR.first<<" "<<pR.second<<endl;
            
            Fout<<pL.first<<" "<<pL.second<<endl;
            Fout<<pR.first<<" "<<pR.second<<endl;

            Tleft = qualifiedPoints(pmin,pL,true,Tleft,pL);
            Tright = qualifiedPoints(pR,pmax,true,Tright,pR);
            left_hull=genLowerHull(pmin,pL,Tleft);
            right_hull = genLowerHull(pR,pmax,Tright);
            left_hull.insert(right_hull.begin(),right_hull.end());
            
            return left_hull;
        }
        vector<pair<double,double>>pointsInRange(pair<double,double>left,pair<double,double>right){
            //! returns a vector of points qualifying the condiion left< points <right
            vector<pair<double,double>> T;
            for(int i=0;i<points.size();i++){
                if(points[i].first>left.first&&points[i].first<right.first)T.push_back(points[i]);
            }
            T.push_back(left);
            T.push_back(right);
            return T;
        }
        pair<pair<double,double>,pair<double,double>> pointUpperFinder(){
            //! pumin,pumax finder
            pair<double,double>pUmin=points[0],pUmax=points[0];
            for(int i=1;i<points.size();i++){
                pair<double,double>temp=points[i];
                if(temp.first<pUmin.first)pUmin=temp;
                else if(temp.first==pUmin.first&&temp.second>pUmin.second)pUmin=temp;

                if(temp.first>pUmax.first)pUmax=temp;
                else if(temp.first==pUmax.first&&temp.second>pUmax.second)pUmax=temp;
            }
            return make_pair(pUmin,pUmax);
        }
        pair<pair<double,double>,pair<double,double>> pointLowerFinder(){
            //! plmin,plmaX FINDER
            pair<double,double>pLmin=points[0],pLmax=points[0];
            for(int i=1;i<points.size();i++){
                pair<double,double>temp=points[i];
                if(temp.first<pLmin.first)pLmin=temp;
                else if(temp.first==pLmin.first&&temp.second<pLmin.second)pLmin=temp;

                if(temp.first>pLmax.first)pLmax=temp;
                else if(temp.first==pLmax.first&&temp.second<pLmax.second)pLmax=temp;
            }
            return make_pair(pLmin,pLmax);
        }
    public:
        kirkpatrick_seidel(vector<pair<double,double>> Points){
            //! constructor of kirk_patrick_seidel class
            points=Points;
            int n=points.size();
            if(n<2)return;
            cout<<"reached calling convexhull gen"<<endl;
            Fout.open("bridge_points.txt");
            convexHullGenerator();
        }
        set<pair<double,double>> getConvexhull(){
            //! gives points on convex hull
            return convexhull;
        }
        set<pair<double,double>> getUpperhull(){
            //! gives points on upper hull
            return upperhull;
        }
        set<pair<double,double>> getLowerhull(){
            //! gives points on lower hull
            return lowerhull;
        }
};
