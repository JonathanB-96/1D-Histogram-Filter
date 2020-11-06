//
//  main.cpp
//  Udacity_C++
//
//  Created by Jonathan Buttigieg on 03/11/2020.
//

#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

vector<float> sense(vector<float> probs, string measure, int x, string world[]);
vector<float> move(vector<float> probs, int U);

int main(int argc, const char * argv[]) {
    // insert code here...
    vector<float> p(5,0.2);
    string world[5] = {"green", "red", "red", "green", "green"};
    string measurements[2] = {"red", "green"};
    vector<int> motions(2,1);
    
    

    int i=0;

    int measurements_size = sizeof(measurements) / sizeof(measurements[0]);
    
    for(i=0; i<measurements_size; i++){
        p = sense(p, measurements[i], i, world);
        p = move(p, motions[i]);
    }
    
    for(i=0; i<p.size(); i++){
        cout << p[i] << " ";
    }
    
    cout << endl;
    return 0;
}

vector<float> sense(vector<float> probs, string measure, int x, string world[]){
    
    float pHit = 0.6;
    float pMiss = 0.2;
    vector<float> q;
    int i = 0;
    float sum = 0.0;
    
    for(i=0; i<probs.size(); i++){
        if(world[i] == measure){
            q.push_back(probs[i] * pHit);
        }
        else{
            q.push_back(probs[i] * pMiss);
        }
    }
    sum = accumulate(q.begin(), q.end(), 0.0);

    for(i=0; i<q.size(); i++){
        q[i] = q[i] / sum;
    }
    return q;
}

vector<float> move(vector<float> probs, int U){
    
    float pExact = 0.8;
    float pOvershoot = 0.1;
    float pUndershoot = 0.1;
    float s = 0.0;
    vector<float> q;
    
    for(int i=0; i<probs.size(); i++){
        
        if(i-U < 0){
            s = pExact * probs[(i-U) + probs.size()];
        }
        else{
            s = pExact * probs[(i-U) % probs.size()];
        }
        
        if(i-U-1 < 0){
            s = s + pOvershoot * probs[(i-U-1) + probs.size()];
        }
        else{
            s = s + pOvershoot * probs[(i-U-1) % probs.size()];
        }
        
        if(i-U+1 < 0){
            s = s + pUndershoot * probs[(i-U+1) + probs.size()];
        }
        else{
            s = s + pUndershoot * probs[(i-U+1) % probs.size()];
        }
        q.push_back(s);
    }
    return q;
}
