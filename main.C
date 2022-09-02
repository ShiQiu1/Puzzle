#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
void sortMatrixRowByRow(vector<vector<int>> &input)
{
    for(int i = 0; i < input.size(); i++)
        sort(input[i].begin(), input[i].end());
}

bool sortcol( const vector<int>& v1,
               const vector<int>& v2 ) {
    return v1[3] < v2[3];
}

void mapInputToCountMap(vector<vector<int>> input, vector<vector<int>> &output, const int maxNrowForOutput, const int maxNcolumnForOutput)
{
    int sum[maxNcolumnForOutput] = {0};
    
    for (int i = 0; i < maxNrowForOutput-2; i++) {// last row is used to store number of occurance
        int indexForInputCol = 0;
        for (int j = 0; j < maxNcolumnForOutput; j++) {   
            if(j==input[i][indexForInputCol]) {
                output[i][j]=1;
                sum[j]++;
                indexForInputCol++;
            }
        }
    }
    for (int j = 0; j < maxNcolumnForOutput; j++) {// fill last row
        output[maxNrowForOutput-1][j] = j;
        output[maxNrowForOutput-2][j] = sum[j];
    }
    
}

void findSolution(vector<vector<int>> inputMap, const int maxNrowForOutput, const int maxNcolumnForOutput)
{
    // only two possible occurance combinations for 4*6 grid
    // prepare some information
    int maxOccurance = *max_element(inputMap[maxNrowForOutput-2].begin(), inputMap[maxNrowForOutput-2].end());
    vector<int> indexFor1Occurance;
    vector<int> indexFor2Occurance;
    vector<int> indexFor3Occurance;
    
    for (int i = 0; i < maxNcolumnForOutput; i++) {
        if (inputMap[maxNrowForOutput-2][i] == 1) {
            indexFor1Occurance.push_back(i);
        } else if (inputMap[maxNrowForOutput-2][i] == 2) {
            indexFor2Occurance.push_back(i);
        } else if (inputMap[maxNrowForOutput-2][i] == 3) { // no need to look at occurance larger than 4
            indexFor3Occurance.push_back(i);
        }
    }
    
    // 1122 (two unique numbers occur once and two unique numbers occur twice)
    // more than one solution can be shown. Of course, if the input guarantees that the solution is unique, the loop can be stopped once a solution is found
    cout<<"searching occurance possibility 1122"<<"\n";
    if ((maxOccurance>=2)&&(indexFor1Occurance.size()>=2)&&(indexFor2Occurance.size()>=2)) {
        for(int i = 0; i < indexFor1Occurance.size(); i++) {
            for(int j = i+1; j < indexFor1Occurance.size(); j++) {
                for(int m = 0; m < indexFor2Occurance.size(); m++) {
                    for(int n = m+1; n < indexFor2Occurance.size(); n++) {
                        int numberOfSuccess = 0;
                        for(int kthRow = 0; kthRow < 6; kthRow++) {
                            if ((inputMap[kthRow][indexFor1Occurance[i]]+inputMap[kthRow][indexFor1Occurance[j]]+inputMap[kthRow][indexFor2Occurance[m]]+inputMap[kthRow][indexFor2Occurance[n]])!=1) {
                                break; // start next combination once the sum of occurance of each number is not one in each row
                            } else {
                                numberOfSuccess++;
                                if (numberOfSuccess == 6) {
                                    cout<<"find solution: "<<inputMap[maxNrowForOutput-1][indexFor1Occurance[i]]<<", "<<inputMap[maxNrowForOutput-1][indexFor1Occurance[j]]<<", "<<inputMap[maxNrowForOutput-1][indexFor2Occurance[m]]<<", "<<inputMap[maxNrowForOutput-1][indexFor2Occurance[n]]<<"\n";
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 1113 (three unique numbers occur once and one unique numbers occur three times)
    cout<<"searching occurance possibility 1113"<<"\n";
    if ((maxOccurance>=3)&&(indexFor1Occurance.size()>=3)&&(indexFor3Occurance.size()>=1)) {
        for(int i = 0; i < indexFor1Occurance.size(); i++) {
            for(int j = i+1; j < indexFor1Occurance.size(); j++) {
                for(int m = j+1; m < indexFor1Occurance.size(); m++) {
                    for(int n = 0; n < indexFor3Occurance.size(); n++) {
                        int numberOfSuccess = 0;
                        for(int kthRow = 0; kthRow < 6; kthRow++) {
                            if ((inputMap[kthRow][indexFor1Occurance[i]]+inputMap[kthRow][indexFor1Occurance[j]]+inputMap[kthRow][indexFor1Occurance[m]]+inputMap[kthRow][indexFor3Occurance[n]])!=1) {
                                break;
                            } else {
                                numberOfSuccess++;
                                if (numberOfSuccess == 6) {
                                    cout<<"find solution: "<<inputMap[maxNrowForOutput-1][indexFor1Occurance[i]]<<", "<<inputMap[maxNrowForOutput-1][indexFor1Occurance[j]]<<", "<<inputMap[maxNrowForOutput-1][indexFor1Occurance[m]]<<", "<<inputMap[maxNrowForOutput-1][indexFor3Occurance[n]]<<"\n";
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    vector<vector<int>> input
    {
        {10,  6,  7,  9},
        { 2,  1,  0,  7},
        { 0,  9,  8, 11},
        {11,  8,  5,  3},
        { 6,  4,  1, 10},
        { 3,  7, 10,  6}
    };
    
    
    cout<<"Input form:"<<"\n";
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++)
        {
            cout << input[i][j] << " ";
        }    
        cout << "\n";
    }
    
    sortMatrixRowByRow(input);
    // Use of "sort()" for sorting on basis of 4th column in ascending order
    sort(input.begin(), input.end(),sortcol);
    
    const int maxNcolumn = input[input.size()-1][input[0].size()-1]+1; // 0-11, starting from 0
    const int maxNrow = input.size()+2; 

    //vector<vector<int>> vec(maxNrow, vector<int> (maxNcolumn));
    vector<vector<int>> map(maxNrow, vector<int> (maxNcolumn,0));
    
    mapInputToCountMap(input, map, maxNrow, maxNcolumn);
    
    // display the mapping 
    // first 6 rows display the occurance. If the number (in the last row) occurs, 1 is shown. 
    // The 7th row displays the total number of occurance
    // The 8th row displays the number of input (from 0 to whatever the max number shown in the grid). It is sorted for convenience of tracking the index
	cout<<"Display the mapping "<<endl;
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            cout << map[i][j] << " ";
        }    
        cout << "\n";
    }
    
    findSolution(map, maxNrow, maxNcolumn);
    
    return 0;
}
