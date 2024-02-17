#include <vector> 
#include <iostream>
#include <climits>
#include <chrono>
using namespace std;

//Stocks1
void maxProfit_1(vector<vector<int > > prices){
    auto start = chrono::steady_clock::now();
    // Initializing 2d vector for storing the buyday , sellday indices of respective stock
    vector<vector<int > > maximum(prices.size(), vector<int> (4,0));
    //Initializing variables to store the indices for the output
    int buyDay = 0, sellDay = 0, stock = 0;
        int maxProfit = 0;

        // ith loop is running for m stocks
    for(int i=0; i< prices.size(); i++){
        //jth loop is to check within each stock for different days i.e n
        for(int j=0 ; j<prices[i].size()-1; j++){
            //kth loop is iterate after ith index in the array to get the all possible combination of buy and sell stock profit
            for(int k = j+1; k< prices[i].size(); k++){
                // currProfit will give the maximum profit for each stock
                int currProfit = prices[i][k] - prices[i][j];
                // maxProfit will store the maximum profit among all the stocks we calculated the currprofit
                if(currProfit > maxProfit){
                    // if we get currProfit i.e any transactions profit to be greater than our current maxProfit, we will update our maxProfit and store the indices respectively.
                    maxProfit = currProfit;
                    // as ith loop is for stocks, i is keeping track of which stock is running currently which yields max profit and then we will store i in stock variable
                    stock = i;
                    //jth loop is for buyDay and kth for sellDay so it's storing the indices in the respective variable
                    buyDay = j;
                    sellDay = k;
                }
               
                
            }
        }
    }
// printing the stock, buyDay and sellDay
  cout<<stock+1<<" "<< buyDay+1<<" "<<sellDay+1;
   auto end = chrono::steady_clock::now();
    auto diff = end - start;
    //  cout << chrono::duration <double, micro> (diff).count() << " micros" << endl;
   
}
// Stocks2
void maxProfit_2(vector<vector<int > > prices,int n){
    auto start = chrono::steady_clock::now();
     // Initializing 2d vector for storing the buyday , sellday indices of respective stock with their profit
     vector<vector<int > > maximum(prices.size(), vector<int> (n,0));
       //Initializing variables to store the indices for the output
     int stock =0;
     int buyDay =0;
     int sellDay = 0;
     // ith loop is running for m stocks
     for(int i=0; i<prices.size(); i++){
        // currStock will take first stock's first day value and assume it to be minimum for now as it represents the buyDay and we have to minimize the value of buyDay inorder to get maximum profit
         int currStock = prices[i][0];
         //jth loop is to check within each stock for different days i.e n
         for(int j=0; j<prices[i].size(); j++){
            // while iterating through different days prices of stocks, if we get another value which is minimum from our currStock, we will update currStock with that value, as we want to minimize our buyDay value
             if(prices[i][j]<currStock){
                 currStock = prices[i][j];
                 //we keep track of which stock and for what indices it yields the minimum buyDay value
                 stock = i;
                 buyDay = j;
             }
             //the maximum[i][0] is storing max profit for each stock i.e ith at 0th index in the maximum vector
             //
             if((prices[i][j] - currStock) > maximum[i][0]){
                 maximum[i][0] = prices[i][j] - currStock;
                 sellDay = j;
                 maximum[i][1] = stock;
                 maximum[i][2] = buyDay;
                 maximum[i][3] = sellDay;
             }
         }
     }
     
    cout<< maximum[0][1]+1<<" "<<maximum[0][2] + 1<<" "<<maximum[0][3]+1;
    //  cout<<"Buy day: "<< maximum[0][2] + 1<<" ";
    //  cout<<"Sell day: "<< maximum[0][3]+1<<" ";
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    //  cout << chrono::duration <double, micro> (diff).count() << " micros" << endl;
}

//Stocks 3a
int profit3a[100];
int minB=0,count=0;
int overAllMax3a,buyDay3a=-1,sellDay3a=-1,stock3a=-1;
int maxProfit_3a(vector<int> prices, int n , int m){
    // Initialize the profit array to store the max value instead of computing again in iteration

 // if we have reached the n = 1, we update our profit array 
                if(n==1)
            {   
                profit3a[n]=max(0,profit3a[n]=prices[n]-prices[n-1]);
                // overAllMax is the final max value, if we get a values greater than overAllMax from profit[n], we update  buyDay indices and overAllMax
                if(profit3a[n]>overAllMax3a)
                {
                    
                    buyDay3a =n-1;
                }
                overAllMax3a=max(overAllMax3a,profit3a[n]);
                
               // if the max value we get as 0 for n=1, we keep track of cheapest day in minB
                
                if(profit3a[n]==0){
                    minB = n;
                   
                }
                else minB = 0;
                return profit3a[n];
            }
            else
            {   
                // if we are selling after buying, we keep track of the current profit we got and recursively call our findMax function for next stock in order to perform a transaction to check the max profit
                profit3a[n]=max(0,maxProfit_3a(prices,n-1,m)+prices[n]-prices[n-1]);
                
                if(profit3a[n]==0){
                    minB = n;
                    
                }
                // overAllMax is the final max value, if we get a values greater than overAllMax from profit[n], we update  buyDay indices and overAllMax
                if(profit3a[n]>overAllMax3a)
                {
               // we keep track of sellDay indices and the stock 
                    buyDay3a=minB;
                    sellDay3a=n;
                    stock3a=m;
                }
            overAllMax3a=max(overAllMax3a,profit3a[n]);
            
                return profit3a[n];
            }


}

//Stocks 3b
void maxProfit_3b( vector<vector<int > > &prices, int m, int n)
    {
        auto start = chrono::steady_clock::now();

        // Initialize the variables 
        int buyDay = 1;
        int sellDay = 1; 
        int maxtotal = 0, maxprofit = 0, buyMin = 1, sellMax = 1, stock = 0;
        // Initialize the profit array to store the max value instead of computing again in iteration
        int profit[n];
        profit[0] = 0;
          // jth loop is running for m stocks
        for(int j=0; j<m;j++){
            maxtotal = 0;
            buyDay = 1;
            sellDay = 1;
            //ith loop is to check within each stock for different days i.e n
              for (int i = 1; i < n; i++) {
            // we keep looking for transaction that gives max profit in our prices vector and compare it with the profit values that we are storing in the profit array
                profit[i] = max(0, profit[i - 1] + (prices[j][i] - prices[j][i - 1]));
                
                if((prices[j][i]-prices[j][i-1]<0) && (profit[i]==0)){
                   // if we get the min buyDay that gives max profit, we store buyDay indices
                    buyDay = i+1;
                   
                }
                
                if (maxtotal < profit[i]) {
                     // if we get the max sellDay that gives max profit, we store sellDay indices
                    sellDay = i + 1;
                    
                }
                // we compute the max profit, in maxTotal variable by comparing profit values from each stock n days
                maxtotal = max(maxtotal, profit[i]);
                

            }

             if (maxtotal > maxprofit) {
                buyMin = buyDay;
                sellMax= sellDay;
                stock = j + 1;
            }
            // finally after getting maxtotal, we compare it with our maxprofit that stores the final profit for buyDay and sellDay
            maxprofit = max(maxprofit, maxtotal);
        }
// print the stock, buyDay and sellDay indices
       cout<<stock  <<" "<<buyMin<<" "<<sellMax;
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    //  cout << chrono::duration <double, micro> (diff).count() << " micros" << endl;
    }
//Stocks 4

// Declare a class with initialized values as maxProfit and output vector
class SubClass{
public:
int maxProfit;
vector<vector<int> > output;
 void subClass(int maxProfit, vector<vector<int> > output) {
        maxProfit = maxProfit;
        output = output;
        
    }
};

class MaxProfit{
public:

SubClass maxprofit_4(vector<vector<int > > prices, int day, int k, bool isBuy,int stock, int buyDay,vector<vector<int> > output){
    int maxProfit = 0;
    vector<vector<int> > finalOutput;

        if((day >= prices[0].size()) || (k == 0))
            return {maxProfit, output};

        if(isBuy) {
            // if isBuy is true that means we buy the stock and currently we keep one stock
            SubClass maxAns = maxprofit_4(prices, day + 1, k, isBuy, stock, buyDay, output);

            int profit = maxAns.maxProfit;
             vector<vector<int> >  currentOutput = maxAns.output;
            // if we get another profit which is greater than maxProfit, we update our maxProfit variable and finalOutput
            if(profit > maxProfit) {
                maxProfit = profit;
                finalOutput = currentOutput;
            }

            // we look for days to sell the stock that we hold now
            int diff = prices[stock][day] - prices[stock][buyDay];

            vector<vector<int> > modifiedOutput = output;

            vector<int> temp;
            temp.push_back(stock);
            temp.push_back(buyDay);
            temp.push_back(day);
            modifiedOutput.push_back(temp);
        // call the function again to compute for k transaction
            maxAns= maxprofit_4(prices, day, k - 1, false, 0, 0, modifiedOutput);
            profit = maxAns.maxProfit;
            currentOutput = maxAns.output;
            profit += diff;
            if(profit > maxProfit) {
                maxProfit = profit;
                finalOutput = currentOutput;
            }
        }
        else {
            // We look for conflicting intervals and eliminate those, and choose the combinations which gives max profit
            vector<vector<int> > outputcopy = output;
            SubClass helperRes = maxprofit_4(prices, day + 1, k, false, 0, 0, outputcopy);
            int profit = helperRes.maxProfit;
            vector<vector<int> > currentOutput = helperRes.output;

            if(profit > maxProfit) {
                maxProfit = profit;
                finalOutput = currentOutput;
            }

            // ith loop is for buying stocks for each m stocks given
            for (int i=0; i<prices.size(); i++) {
                helperRes = maxprofit_4(prices, day + 1, k, true, i, day, outputcopy);
                profit = helperRes.maxProfit;
                currentOutput = helperRes.output;

                if(profit > maxProfit) {
                    maxProfit = profit;
                    finalOutput = currentOutput;
                }
            }
        }
        // we return the maxprofit and finalOutput which consists of buyDay, sell Day indices and stock
         return {maxProfit, finalOutput};
        

}

};

//Stocks 5

void maxProfit_5(vector<vector<int > > prices,int n, int k){
    
   auto start = chrono::steady_clock::now();
   //Initializing the profit vector
    vector<vector<int> > profit(k+1, vector<int> (n,0));
    
    for(int t=1; t<k+1; t++){                   // Loop for k+1 transactions
        for(int m=0; m<prices.size(); m++){     // Loop for m stocks
            for(int j=1;j<n;j++){               // Loop for n days
                for(int l=0;l<j;l++){           // Loop for n-1 days 
                //Comparing all the possible profits and assigning the maximum profit for tth transaction and jth day
                    profit[t][j] = max(max(profit[t][j],profit[t][j-1]),prices[m][j]+profit[t-1][l]-prices[m][l]);
                }
            }
        }
    }

//Initialzing a stack to store stock number, buy day, sell day
vector<int> stack;
int i = profit.size() - 1;
int j = profit[0].size() - 1;
 while(true) {
    int flag=0;
    // Reaches the end of the profit table
    if(i == 0 || j == 0) {
        break;
    }
    // Checks if the stock has been sold on jth day by comparing with previous day. If same stock hasn't been sold on jth day and decrements j by 1
    if (profit[i][j] == profit[i][j-1]) {
        
        j = j - 1;
    } 
    else {
        // Stock sold on jth day therefore pushes into the stack
        stack.push_back(j+1);
        // For loop to find which stock has been bought and sold
        for(int l=0; l<prices.size();l++) {
            // Initializing maxDiff to find which stock and on what day it has been bought on
            int maxDiff = profit[i][j] - prices[l][j];
            // Running for loop for all the previous days
                for (int k = j-1; k >= 0; k--) {
                // Match has been found if condition satisfies 
                if (profit[i-1][k] - prices[l][k] == maxDiff) {
                    i = i - 1;
                    j = k;
                    stack.push_back(j+1); // Pushing the buyday
                    stack.push_back(l+1); // Pushing the sellday
                    flag=1;
        }if(flag==1)break;
            }if(flag==1)break;
            
        
                
        }
    }
    }
        // Using this bracket of code to print the required output
        int c = stack.size()/3;
        while(c>0){
            int v1 = stack.back();
            stack.pop_back();
            int v2 = stack.back();
            stack.pop_back();
            int v3= stack.back();
            stack.pop_back();
         cout<<v1 <<" "<<v2 <<" "<<v3 <<" ";
            // cout<<"stock "<<v1<<" ";
            // cout<<"BuyDay "<<v2<<" ";
            // cout<<"sellDay "<<v3<<" ";
            cout<<endl;
            c--;
            
        }

 auto end = chrono::steady_clock::now();
    auto diff = end - start;
    //  cout << chrono::duration <double, micro> (diff).count() << " micros" << endl;
}

//Stocks 6a

void maxProfit_6a(vector<vector<int > > prices,int n, int k){

    auto start = chrono::steady_clock::now();
  //Initializing the profit vector  
  vector<vector<int> > profit(k+1, vector<int> (n,0));
  for(int t = 1; t < k+1; t++){                 // Loop for k+1 transactions
    // Creating a vector to store the maximum possible profit given by a stock and previous transaction's profit
    vector<int> mtf(prices.size(),INT_MIN); 
      for(int m = 0 ; m< prices.size(); m++){        // Loop for m stocks
          for(int j = 1; j < prices[0].size(); j++){ // Loop for n days
              // Calculating and assining maximum possible profit given by the mth stock and previous transaction's profit 
              mtf[m] = max(mtf[m],profit[t-1][j-1] - prices[m][j-1]);
              //Comparing all the possible profits and assigning the maximum profit for tth transaction and jth day
              profit[t][j] = max(max(profit[t][j],profit[t][j-1]),prices[m][j] + mtf[m]);
          }
      }
  }
  



//Initialzing a stack to store stock number, buy day, sell day
vector<int> stack;
int i = profit.size() - 1;
int j = profit[0].size() - 1;
 while(true) {
    int flag=0;
    // Reaches the end of the profit table
    if(i == 0 || j == 0) {
        break;
    }
    // Checks if the stock has been sold on jth day by comparing with previous day. If same stock hasn't been sold on jth day and decrements j by 1
    if (profit[i][j] == profit[i][j-1]) {
        
        j = j - 1;
    } 
    else {
        // Stock sold on jth day therefore pushes into the stack
        stack.push_back(j+1);
        // For loop to find which stock has been bought and sold
        for(int l=0; l<prices.size();l++) {
            // Initializing maxDiff to find which stock and on what day it has been bought on
            int maxDiff = profit[i][j] - prices[l][j];
            // Running for loop for all the previous days
                for (int k = j-1; k >= 0; k--) {
                // Match has been found if condition satisfies 
                if (profit[i-1][k] - prices[l][k] == maxDiff) {
                    i = i - 1;
                    j = k;
                    stack.push_back(j+1); // Pushing the buyday
                    stack.push_back(l+1); // Pushing the sellday
                    flag=1;
        }if(flag==1)break;
            }if(flag==1)break;
            
        
                
        }
    }
    }
        // Using this bracket of code to print the required output
        int c = stack.size()/3;
        while(c>0){
            int v1 = stack.back();
            stack.pop_back();
            int v2 = stack.back();
            stack.pop_back();
            int v3= stack.back();
            stack.pop_back();
         cout<<v1<<" "<<v2<<" "<<v3<<" ";
            // cout<<"stock "<<v1<<" ";
            // cout<<"BuyDay "<<v2<<" ";
            // cout<<"sellDay "<<v3<<" ";
            cout<<endl;
            c--;
            
        }

 auto end = chrono::steady_clock::now();
    auto diff = end - start;
    //  cout << chrono::duration <double, micro> (diff).count() << " micros" << endl;
}


    //Stock 6b
    void maxProfit_6b(vector<vector<int > > prices,int n, int k){

    auto start = chrono::steady_clock::now();
  //Initializing the profit vector  
  vector<vector<int> > profit(k+1, vector<int> (n,0));
  for(int t = 1; t < k+1; t++){                 // Loop for k+1 transactions
    // Creating a vector to store the maximum possible profit given by a stock and previous transaction's profit
    vector<int> mtf(prices.size(),INT_MIN); 
      for(int m = 0 ; m< prices.size(); m++){        // Loop for m stocks
          for(int j = 1; j < prices[0].size(); j++){ // Loop for n days
              // Calculating and assining maximum possible profit given by the mth stock and previous transaction's profit 
              mtf[m] = max(mtf[m],profit[t-1][j-1] - prices[m][j-1]);
              //Comparing all the possible profits and assigning the maximum profit for tth transaction and jth day
              profit[t][j] = max(max(profit[t][j],profit[t][j-1]),prices[m][j] + mtf[m]);
          }
      }
  }
  



//Initialzing a stack to store stock number, buy day, sell day
vector<int> stack;
int i = profit.size() - 1;
int j = profit[0].size() - 1;
 while(true) {
    int flag=0;
    // Reaches the end of the profit table
    if(i == 0 || j == 0) {
        break;
    }
    // Checks if the stock has been sold on jth day by comparing with previous day. If same stock hasn't been sold on jth day and decrements j by 1
    if (profit[i][j] == profit[i][j-1]) {
        
        j = j - 1;
    } 
    else {
        // Stock sold on jth day therefore pushes into the stack
        stack.push_back(j+1);
        // For loop to find which stock has been bought and sold
        for(int l=0; l<prices.size();l++) {
            // Initializing maxDiff to find which stock and on what day it has been bought on
            int maxDiff = profit[i][j] - prices[l][j];
            // Running for loop for all the previous days
                for (int k = j-1; k >= 0; k--) {
                // Match has been found if condition satisfies 
                if (profit[i-1][k] - prices[l][k] == maxDiff) {
                    i = i - 1;
                    j = k;
                    stack.push_back(j+1); // Pushing the buyday
                    stack.push_back(l+1); // Pushing the sellday
                    flag=1;
        }if(flag==1)break;
            }if(flag==1)break;
            
        
                
        }
    }
    }
        // Using this bracket of code to print the required output
        int c = stack.size()/3;
        while(c>0){
            int v1 = stack.back();
            stack.pop_back();
            int v2 = stack.back();
            stack.pop_back();
            int v3= stack.back();
            stack.pop_back();
         cout<<v1<<" "<<v2<<" "<<v3<<" ";
            // cout<<"stock "<<v1<<" ";
            // cout<<"BuyDay "<<v2<<" ";
            // cout<<"sellDay "<<v3<<" ";
            cout<<endl;
            c--;
            
        }

 auto end = chrono::steady_clock::now();
    auto diff = end - start;
    //  cout << chrono::duration <double, micro> (diff).count() << " micros" << endl;
}

void read1(){
  // Declaring 2d vectore to store the input values
    vector<vector<int > > prices;
    // m is the number of stocks, n is the indices of each days for each stock
    int m, n;

    // cout<< "Enter m and n"<<endl;
    // Taking m and n input from the user
    cin>> m >> n;
    // loop for m days to take values
    for(int i=0 ; i<m ; i++){
        // cout<<"Enter stock prices"<<endl;
        vector<int> row;
        int temp;
        // take each days values i.e n
        for(int j=0; j<n; j++){
            cin>> temp;
            row.push_back(temp);
        }
        // push each 1d vector into prices vector
        prices.push_back(row);
    }
//  call the function for bruteforce approach
maxProfit_1(prices);
}

void read2(){
  vector<vector<int > > prices;
    
    int m, n;

    // cout<< "Enter m and n"<<endl;
    cin>> m >> n;
    for(int i=0 ; i<m ; i++){
        // cout<<"Enter stock prices"<<endl;
        vector<int> row;
        int temp;
        for(int j=0; j<n; j++){
            cin>> temp;
            row.push_back(temp);
        }
        prices.push_back(row);
    }

maxProfit_2(prices,n);
}
void read3a(){
           auto start = chrono::steady_clock::now();
    vector<vector<int > > prices;
    
    int m, n;

    // cout<< "Enter m and n"<<endl;
    cin>> m >> n ;
    for(int i=0 ; i<m ; i++){
        // cout<<"Enter stock prices"<<endl;
        vector<int> row;
        int temp;
        for(int j=0; j<n; j++){
            cin>> temp;
            row.push_back(temp);
        }
        prices.push_back(row);
    }
        // if(n<2) return 0;
        // vector<vector<int> > v(n+1,vector<int>(2,-1));
       
    
   
     for (int i = 0; i < m; i++) {
                maxProfit_3a(prices[i], n- 1, i);
            }
   
   // print the stock, buyDay and sellDay indices
  cout<<stock3a+1<<" "<<buyDay3a+1<<" "<<sellDay3a+1;

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    //  cout << chrono::duration <double, micro> (diff).count() << " micros" << endl;
}
void read3b(){
    vector<vector<int > > prices;
    
    int m, n;

    // cout<< "Enter m and n"<<endl;
    cin>> m >> n ;
    for(int i=0 ; i<m ; i++){
        // cout<<"Enter stock prices"<<endl;
        vector<int> row;
        int temp;
        for(int j=0; j<n; j++){
            cin>> temp;
            row.push_back(temp);
        }
        prices.push_back(row);
    }

        // if(n<2) return 0;
        // vector<vector<int> > v(n+1,vector<int>(2,-1));
        int maxProfit = 0;
     
    
          maxProfit_3b(prices,m,n);
}

void read4(){
auto start = chrono::steady_clock::now();
    vector<vector<int > > prices ;


   SubClass obj;
   SubClass ans;
    MaxProfit mp;
    int m, n, k;

    // cout<< "Enter k"<<endl;
    cin>> k;
    // cout<<"Enter m and n"<<endl;
    cin >> m >>n;
    for(int i=0 ; i<m ; i++){
        // cout<<"Enter stock prices"<<endl;
        vector<int> row;
        int temp;
        for(int j=0; j<n; j++){
            cin>> temp;
            row.push_back(temp);
        }
        prices.push_back(row);
    }
 ans =mp.maxprofit_4(prices, 0, k, false, 0, 0, obj.output);
//  cout<<ans.maxProfit<<endl;

 for(int i=0; i<ans.output.size(); i++){
    for(int j=0; j< ans.output[0].size(); j++){
        cout<<ans.output[i][j]+1<<" ";
    }
    cout<<"\n";
 }
 auto end = chrono::steady_clock::now();
    auto diff = end - start;
    //  cout << chrono::duration <double, micro> (diff).count() << " micros" << endl;

}
void read5(){
     vector<vector<int > > prices;
    
    int m, n, k;

    // cout<< "Enter k"<<endl;
    cin>> k;
    // cout<<"Enter m and n"<<endl;
    cin >> m >>n;
    for(int i=0 ; i<m ; i++){
        // cout<<"Enter stock prices"<<endl;
        vector<int> row;
        int temp;
        for(int j=0; j<n; j++){
            cin>> temp;
            row.push_back(temp);
        }
        prices.push_back(row);
    }

maxProfit_5(prices,n,k);
}
void read6a(){
      vector<vector<int > > prices;
    
    int m, n, k;

    //  cout<< "Enter k"<<endl;
    cin>> k;
    // cout<<"Enter m and n"<<endl;
    cin >> m >>n;
    for(int i=0 ; i<m ; i++){
        // cout<<"Enter stock prices"<<endl;
        vector<int> row;
        int temp;
        for(int j=0; j<n; j++){
            cin>> temp;
            row.push_back(temp);
        }
        prices.push_back(row);
    }

maxProfit_6a(prices,n,k);
}
void read6b(){
     vector<vector<int > > prices;
    
    int m, n, k;

    //  cout<< "Enter k"<<endl;
    cin>> k;
    // cout<<"Enter m and n"<<endl;
    cin >> m >>n;
    for(int i=0 ; i<m ; i++){
        // cout<<"Enter stock prices"<<endl;
        vector<int> row;
        int temp;
        for(int j=0; j<n; j++){
            cin>> temp;
            row.push_back(temp);
        }
        prices.push_back(row);
    }

maxProfit_6b(prices,n,k);
}
int main(int argc, char *argv[]) {
  string current_exec_name; 
// cout << "You have entered " << argc
//          << " arguments:" << "\n";

// if argc.count == 1 // error, exit 1
current_exec_name = argv[1];
if(current_exec_name == "1"){
    read1();
}
else if(current_exec_name =="2"){
    read2();
}
else if(current_exec_name =="3a"){
    read3a();
}
else if(current_exec_name =="3b"){
    read3b();
}
else if(current_exec_name =="4"){
    read4();
}
else if(current_exec_name =="5"){
    read5();
}
else if(current_exec_name =="6a"){
    read6a();
}
else if(current_exec_name =="6b"){
    read6b();
}
  
    // for (int i = 0; i < argc; ++i)
    //     cout << argv[i] << "\n";
  
    return 0; 
   
}