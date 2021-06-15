#include <iostream>
#include <vector>

using namespace std;
void merge(vector<int>& input, int start, int mid, int end){

    vector<int> tempL; //copy from start to mid in left array
    vector<int> tempR; //copy form mid+1 to right in tempR array

    int lsize = mid-start+1;
    int rsize = end-mid;

    for(int i=0; i<lsize; i++){
        tempL.push_back(input[i + start]);
    }

    for(int j=0; j<rsize; j++){
        tempR.push_back(input[j + mid + 1]);
    }

    //iterate over tempL and tempR at same time and merge into input while comapring
    int l = 0;
    int r = 0;

    while(l < lsize && r < rsize){
        if(tempL[l] <= tempR[r]){
            input[start++] = tempL[l++];
        }
        else{
            input[start++] = tempR[r++];
        }
    }

    //copy remaining elements of tempL
    while(l < lsize){
        input[start++] = tempL[l++];
    }

    while(r < rsize){
        input[start++] = tempR[r++];
    }

}

void merge_sort(vector<int>& input, int start, int end){
//recursively divide array into mid
    if(start<end){
        int mid = start + (end-start)/2;
        merge_sort(input, start, mid);
        merge_sort(input, mid+1, end);
        merge(input,start, mid, end);
    }
}

int main(){

    cout<<"enter 10 elements to sort "<<endl;
    vector<int> input;
    int n;
    for(int i=0; i<10; i++){
        cin>>n;
        input.push_back(n);
    }
    merge_sort(input, 0, 9);

    cout<<"sorted array is: " <<endl;
    for(int i=0; i<10; i++){
        cout<<input[i] <<" ";
    }
    cout<<endl;
    return 0;
}