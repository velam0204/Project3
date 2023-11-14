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

   //struct reviews {
    //    int reviewnumber;
    //   double reviewScore;
    //    string category;
    //};
   //vector <reviews> Indreview;
    int NumofTruth = 0;
    int NumofDecep = 0;
    int NumofUncat = 0;
    string category;
    int i = 0;
    double maxtemreviewscore = 0;
    double mintemreviewscore = 0;
    int index_of_max = 0;
    int index_of_min = 0;
    ofstream file ("report.txt");
    file << "review score category" << endl;
    double score;


   for(i; i<= 99; i++){
    
       string filename = makeReviewFilename(i);
       ifstream hotelreview (filename);
       if (! hotelreview.is_open()){
        break;   
        }
        vector<string> reviewWords;
        readReview(hotelreview, reviewWords);
        score = reviewScore(reviewWords,keywords, weights);


        if (score > SCORE_LIMIT_TRUTHFUL){
            category = "truthful";
            NumofTruth += 1;
        }
        if (score < SCORE_LIMIT_DECEPTIVE){
            category = "deceptive";
            NumofDecep +=1;
        }
        else if (score <= SCORE_LIMIT_TRUTHFUL && score >= SCORE_LIMIT_DECEPTIVE){
            category = "uncategorized";
            NumofUncat +=1;
        }

        if (score > maxtemreviewscore){
            maxtemreviewscore = score;
            index_of_max = i;
        }
        if (score < mintemreviewscore){
            mintemreviewscore = score;
            index_of_min = i;
        }


        file << i << " " << score << " " << category << endl;




        //if(reviewWords.at(i).empty()){
        //    break;
        //}
        //Indreview.at(i).reviewScore = reviewScore();
        //if(Indreview.at(i).reviewScore > SCORE_LIMIT_TRUTHFUL){
        //    Indreview.at(i).category = "truthful";
        //}
        //if(Indreview.at(i).reviewScore < SCORE_LIMIT_DECEPTIVE){
        //    Indreview.at(i).category = "deceptive";
        //}
        //else{
        //    Indreview.at(i).category = "uncategorized";
        //}
        //Indreview.at(i).reviewnumber = i;
        //Indreview.push_back(review);
        
   }
    file << "" << endl;
    file << "Number of reviews: " << i << endl;
    file << "Number of truthful reviews: " << NumofTruth << endl;
    file << "Number of deceptive reviews: " << NumofDecep << endl;
    file << "Number of uncategorized reviews: " << NumofUncat << endl << endl;
    file << "review with highest score: " << index_of_max << endl;
    file << "review with lowest score: " << index_of_min << endl;
    file.close();

 
    // TODO: implement the main program

}
