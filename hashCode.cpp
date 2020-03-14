#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

struct book{
    int id;
    int score;
};

struct library{
    int id;
    int numOfBooks, signupTime, maxBooks; // input direct
    int totalScorePossible;
    vector<int> booksAvailable;
    double order;
    int counter;
    vector<book> finalChosen;
    int dubs = 0;
};

vector<int> score;
vector<book> books;
vector<book> newBooks;

bool comp(library a, library b){
    return a.order > b.order;
}

bool comp2(book a, book b){
    return a.score > b.score;
}

bool comp3(int a, int b){
    if(books[a].score > books[b].score) return true;
    else return false;
}

int main(){
    int b,l,d;
    cin>>b>>l>>d;
    
    for(int i=0;i<b;i++){
        book x;
        x.id = i;
        cin>>x.score;
        score.push_back(x.score);
        books.push_back(x);
    }

    unordered_map<int, int> ifvis;

    newBooks = books;
    sort(newBooks.begin(), newBooks.end(), comp2);
    
    vector<library> libs;
    

    // input for library starts here
    for(int i=0;i<l;i++){
        library x;
        x.id = i;
        cin>>x.numOfBooks>>x.signupTime>>x.maxBooks;
        int sum=0;
        for(int j=0;j<x.numOfBooks;j++){
            int y;
            cin>>y;
            sum+=score[y];
            x.booksAvailable.push_back(y);
        }
        
        x.totalScorePossible = sum;
        x.order = ((double) x.totalScorePossible * (double)x.maxBooks / (double)x.signupTime) - x.dubs;
        
        sort(x.booksAvailable.begin(), x.booksAvailable.end(), comp3);
        
        libs.push_back(x);
    } // input ends here

    unordered_map<int,int> che;

    for (int i = 0; i < libs.size(); ++i) {
        int du = 0;

        for (int j = 0; j < libs[i].booksAvailable.size(); ++j) {
            if (che[libs[i].booksAvailable[j]] != 0) {
                du++;
            }else {
                che[libs[i].booksAvailable.size()] = 1;
            }
        }

        libs[i].dubs = du;
    }

    sort(libs.begin(), libs.end(), comp);

    vector<bool> visited(b, false);

    int finalAns=0;

    int daysConsumed = 0;
    int maxi;
    for(int i=0;i<libs.size();i++){
        daysConsumed += libs[i].signupTime;
        if(daysConsumed > d) break;
        int remDays = d - daysConsumed;
        int maxBooksShipped = min(libs[i].numOfBooks, remDays * libs[i].maxBooks);
        int j=0;
        int counter=0;
        for(;j<libs[i].booksAvailable.size() && counter <= maxBooksShipped;j++){
            if(!visited[libs[i].booksAvailable[j]]){
                finalAns += score[libs[i].booksAvailable[j]];
                counter++;
                // if(counter > maxBooksShipped){
                //     counter = maxBooksShipped;
                //     break;
                // }
                libs[i].finalChosen.push_back(books[libs[i].booksAvailable[j]]);
                visited[libs[i].booksAvailable[j]] = true;
            }
        }
        // libs[i].counter = counter;
        maxi = i;
    }
    // cout<<finalAns<<endl;

    cout << maxi + 1 << endl;

    for (int i = 0; i < maxi + 1; ++i) {
        cout << libs[i].id << " " << libs[i].finalChosen.size();
        cout << endl;
        for (int j = 0; j < libs[i].finalChosen.size(); ++j) {
            cout << libs[i].finalChosen[j].id << " ";
        }
        cout << endl;
 
    }cout << endl;



    return 0;
}