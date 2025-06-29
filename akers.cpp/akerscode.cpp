#include<bits/stdc++.h>
#include<vector>
using namespace std;
class akersArray{
    private:
        vector<string> row;
        vector<string> column;
        vector<vector<int>> Aarr;
        vector<int> inputs;
    public:
        akersArray(vector<string> minterms, vector<string> maxterms, vector<int> input){
            row = minterms;
            column = maxterms;
            Aarr = vector<vector<int>>(minterms.size() , vector<int> (maxterms.size(), 0));
            inputs = input;
        }

        void construct(){
            

            for(int i = 0; i < Aarr.size(); i++){
                for(int j = 0; j < Aarr[i].size(); j++){
                    string minterm = row[i];
                    string maxterm = column[j];
                    cout << minterm << " ";
                    cout << maxterm << " " << endl;

                    for(int k = 0; k < minterm.size(); k++){
                        if( (minterm[k] == '1' && maxterm[k] == '0')){
                            Aarr[i][j] = inputs[k];
                            cout << "Input to be  entered " << inputs[k] << endl;
                            break;
                        }else if((minterm[k] == '0' && maxterm[k] == '1')){
                            cout << "Not Input to be  entered " << inputs[k] << endl;
                            Aarr[i][j] = (inputs[k] == 1 ? 0 : 1);
                            break;
                        }
                    }
                }
            }
        }

        void display(){
            for(int i = 0; i < Aarr.size(); i++){
                for(int j = 0; j < Aarr[i].size(); j++){
                    cout << Aarr[i][j] << " ";
                }
                cout << endl;
            }
        }
        
        
        int solve(){
            int i = 0;
            int j = 0;
            
            while(i < row.size() && j < column.size()){
                if(Aarr[i][j] == 1){
                    j++;
                }else{
                    i++;
                }
            }
            
            if(i >= row.size()){
                return 0;
            }else{
                return 1;
            }
        }
};


int main(){
    vector<string> minterms = {"000", "011", "100"};
    vector<string> maxterms = {"010", "101", "111"};
    cout << minterms[0].size() << endl;
    vector<int> inputs {0,1,1};
    
    akersArray a(minterms, maxterms, inputs);
    a.construct();
    a.display();
    cout << a.solve();
    
}