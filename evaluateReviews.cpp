// <Your Name> 
// <Partner uniqname (or "none")> 
// <Lab Section Number(s)> 
// <Date Submitted>

//------------------------------------------------------
// AUTOGRADER INFO -- IGNORE BUT DO NOT REMOVE 
// test_cases: true
// feedback('all')
// c269759b-5ea7-4702-bff4-ebc05443d45d
//------------------------------------------------------



// Add any #includes for C++ libraries here.
// We have already included iostream as an example.
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <functional>


// This #include adds all the function declarations (a.k.a. prototypes) from the
// reviews.h file, which means the compiler knows about them when it is compiling
// the main function below (e.g. it can verify the parameter types and return types
// of the function declarations match the way those functions are used in main() ).
// However, the #include does not add the actual code for the functions, which is
// in reviews.cpp. This means you need to compile with a g++ command including both
// .cpp source files. For this project, we will being using some features from C++11,
// which requires an additional flag. Compile with this command:
//     g++ --std=c++11 evaluateReviews.cpp reviews.cpp -o evaluateReviews
#include "reviews.h"

using namespace std;

const double SCORE_LIMIT_TRUTHFUL = 3;
const double SCORE_LIMIT_DECEPTIVE = -3;


int main(){
    ifstream KeywordWeight ("keywordWeights.txt");
    if (! KeywordWeight.is_open()){
        cout << "Error: keywordWeights.txt could not be opened.";
        return 1;
    }
    vector<string> keywords;
    vector<double> weights;
    readKeywordWeights(KeywordWeight, keywords, weights);

   struct reviews {
        int reviewnumber;
        double reviewScore;
        string category;
    };
   vector <reviews> Indreview;
    int NumofTruth = 0;
   int NumofDecep = 0;
   int NumofUncat = 0;
    int i = 0;

   for(i; i<= 99; i++){
    
       string filename = makeReviewFilename(i);
       ifstream hotelreview (filename);
        vector<string> reviewWords;
        readReview(hotelreview, reviewWords);
        if(reviewWords.at(i).empty()){
            break;
        }
        Indreview.at(i).reviewScore = reviewScore(reviewWords,keywords, weights);
        if(Indreview.at(i).reviewScore > SCORE_LIMIT_TRUTHFUL){
            Indreview.at(i).category = "truthful";
        }
        if(Indreview.at(i).reviewScore < SCORE_LIMIT_DECEPTIVE){
            Indreview.at(i).category = "deceptive";
        }
        else{
            Indreview.at(i).category = "uncategorized";
        }
        Indreview.at(i).reviewnumber = i;
        
   }
   int index_of_max = 0;
   for (int j = 0; j < Indreview.size(); ++j){
     if(Indreview.at(j).reviewScore > Indreview.at(index_of_max).reviewScore){
        index_of_max = j;
     }
   }
   int index_of_min = 0;
   for (int j = 0; j < Indreview.size(); ++j){
     if(Indreview.at(j).reviewScore > Indreview.at(index_of_min).reviewScore){
        index_of_min = j;
     }
   }
    int totalnumreviewed = i + 1;
    for(size_t j = 0; j <Indreview.size(); ++j) {
        if(Indreview.at(j).category == "truthful"){

        
        NumofTruth += 1;
        }
        if(Indreview.at(j).category == "deceptive"){
            NumofDecep += 1;
        }
        else {
            NumofUncat += 1;
        }
    }
    ofstream file ("report.txt");
    cout << "review score category" << endl;
    for(size_t j = 0; j < Indreview.size(); ++j){
        cout << Indreview.at(j).reviewnumber << " "<< Indreview.at(j).reviewScore << " " << Indreview.at(j).category << endl;
    }
 cout << "/n" ;
 cout << "Number of reviews: " << totalnumreviewed << endl;
 cout << "Number of truthful reviews: " << NumofTruth << endl;
 cout << "Number of deceptive reviews: " << NumofDecep << endl;
 cout << "Number of uncategorized reviews: " << NumofUncat << endl;
 cout << "/n" ;
 cout << "review with highest score: " << index_of_max << endl;
 cout << "review with lowest score: " << index_of_min << endl;
    // TODO: implement the main program

}
