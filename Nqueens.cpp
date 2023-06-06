#include <iostream>
#include <string>
#include<stack>
#include<cstdlib>

using namespace std;

// functions

// printQueens serves to print the indexs of the queens starting from the bottem to the top of the board
// It achieves this by printing the stack recursively backwards but printing the rows in a linear fashion
void printQueens(stack<int> q, int n){
    if(q.empty()){
        return;
    }
    int x = q.top();
    q.pop();
    n = n - 1;

    printQueens(q,n);
    cout << "[" << n + 1 << "," << x << "]";
    
    q.push(x);
}

// printRow serves to print the board of the top of the stack's row.
// it achieves this by printing a "." if its not the number of the top of stack and print "x" if it is, creating a chess row with a x for the queen piece
void printRow(stack<int> q,int n){
        int sum = n;
        for(int i = 1; i < sum + 1; i++){
            if(i == q.top()){
                cout << " x";
                
            }
            else{
                cout << " .";
            }
            
        }   
}

// printBoard serves to print the whole chessboard
// it acheives this by constanly printing the chess board row with printRow and popping off the top of the stack until there are no elements in the stack
void printBoard(stack<int> q, int n){
    for(int o = 0; o < n; o++){
        printRow(q,n);
        q.pop();
        cout << "\n";
    }
}

// copyStack serves to copy values from one stack to another
// it achieves this by taking the values at one stack and making it equal to the other
// note: important function for the n queens program as we will use this to check the queens before by checking the copied stack and not the real one
void copyStack(stack<int> & stack1, stack<int> & stack2){
    stack2 = stack1;
}

// isValid serves to check if the most recent element/queen pushed into the stack is a valid location for a queen on our chessboard and returning a bool
// it achieves this by doing 4 things:
// 1. Checking to see if its the only item in the stack as that means there are no queens for it to conflict with
// 2. Making sure that its column doesnt surpass the the amount allowed by our N x N chessboard
// 3. Making sure that any other queen in the rows before are not in its diagonals
// 4. Making sure its not in the same column as any other queen before
bool isValid(stack<int>  q, int n){
    // Makes queen size equal to size and check if its one, return true if so because its the first queen placed so no conflicts
    int size = q.size();
    if(q.size() == 1){
        return true;
    }
    // Checks to see if the column number is higher that the length of the chessboard and returns false if so because its not a valid position
    if(q.top() > n){
        return false;
    }
    
    stack<int> qcopy; 
    copyStack(q,qcopy); // Makes a copy of our queen stack so we can view elements before by popping within a for loop
    for(int i = 0; i < size - 1; i ++){
        qcopy.pop();
        if(qcopy.top() == q.top()){ // checks if the elements below our recently pushed in queen are the same as that would mean they have the same column
            return false;
        }
        if(qcopy.top() == q.top() + 1 + i or qcopy.top() == q.top() - 1 - i ){ // checks if the element below is one more or one less and increases by one as it goes down as thats how diagonols work
            return false;
        }
    }
    // if all of these statement dont return false then the queen is in a valid postition for our chessboard/stack at the time
        return true; 
}

// main serves to house the algorithm 
int main(){
    // Makes a new stack and asks the user for our N which cant exceed 15 for the algorithms sake
    stack<int> q;
    int n;
    bool ask = true;
    while(ask){
    cout << "\nPlease enter n, which will be our N x N Chessboard and amount of queens ";
        cin >> n;
        if(n < 16){
            ask = false;
        }
        if(n > 15){
            cout << "Please input something 15 or less for algorithm's sake";
        }
        cout << "\n";
    }

   
    // keep track at where we are in rows so we can stop
     int filled = 0;
    
    while(filled != n){ // while the chessboard isn't filled with queens
        q.push(1); // pushes queen into the first column with the row index because where it at in the stack
        bool Valid = isValid(q,n); // checks if its a valid position
        
        // if its valid we will fill the row
        if(Valid == true){
            filled = filled + 1;
        }
        if(Valid == false){
            bool keepGoing = true;
            
            int counter = (n - q.top()) + 1;
            while(keepGoing){
                // if false location we will shift the queen across until one index over the size of the board
                // we do this because if the queen was valid in the last slot but has to be popped do to the other queen's locations above not working, then
                // it would go over the index and the if statement(line 140) below would pop it
                for(int i = 0; i < counter; i++){ // this for loop shifts the queen over until its a valid location or just goes out of bounds
                    int k = q.top() + 1;
                    q.pop();
                    q.push(k);
                    bool Valid2 = isValid(q,n);
                    if(Valid2 == true){
                        filled = filled + 1;
                        keepGoing = false;
                        break;
                    }
                }
                // this if statement pops if the queen cant find a valid location or was valid but due to the queens above has to be popped
                if(q.top() > n){
                    q.pop();
                    filled = filled - 1;
                    keepGoing = true;
                } 
            }
        }
    }
    // Prints the Queen locations and the Board
    cout << "The Queens Locations are, ";
    printQueens(q,n);
    cout << "\n";
    printBoard(q,n);   
        
    return 0; // end
}


