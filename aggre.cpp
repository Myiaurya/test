#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

#define NUMOFVAL 12
string ReplaceString
(
      string String1   // 置き換え対象
    , string String2   // 検索対象
    , string String3   // 置き換える内容
)
{
    string::size_type  Pos( String1.find( String2 ) );
 
    while( Pos != string::npos )
    {
        String1.replace( Pos, String2.length(), String3 );
        Pos = String1.find( String2, Pos + String3.length() );
    }
 
    return String1;
}

int main(int argc, char *argv[]) {
    
    int numofline = 0;
    ostringstream dirname;
    ifstream txt;
    string moji;
    double r1_step, r1_max, r1_min, r2_step, r2_max, r2_min, \
        game_step, game_max, game_min, day_step, day_max, day_min;
    ostringstream val_name;
    dirname << "./runcomp.sh";
    txt.open(dirname.str());
    getline(txt, moji);
    getline(txt, moji);
    for (int i = 0; i < 12; i++) {
        getline(txt, moji);
        val_name << moji << "\n";
    }
    //    val_name = ReplaceString(val_name.str(), "=", " ");
    string str = ReplaceString(val_name.str(), "=", " ");
    istringstream input_istring(str);
    input_istring >> moji >> r1_step >> moji >> r1_max >> moji >> r1_min \
                  >> moji >> r2_step >> moji >> r2_max >> moji >> r2_min \
                  >> moji >> game_step >> moji >> game_max >> moji >> game_min \
                  >> moji >> day_step >> moji >> day_max >> moji >> day_min;
    txt.close();
    dirname.str("");
    dirname << "./some_result_txt/trance_vg_r.txt";
    txt.open(dirname.str());
    getline(txt, moji);
    while (getline(txt, moji)) {
        numofline++;
    }
    txt.close();
    double *benefit_ = new double[numofline],\
        *fear_ = new double[numofline],\
        *serv_  = new double[numofline],\
        *ally_ = new double[numofline],\
        *infected_ = new double[numofline],\
        *game_ = new double[numofline],\
        *day_ = new double[numofline];

    txt.open(dirname.str());
    getline(txt, moji);
    for (int i = 0; i < numofline; i++) {
        txt >> benefit_[i] >> fear_[i] >> serv_[i]\
            >> ally_[i] >> infected_[i]\
            >> game_[i] >> day_[i];
    }
    txt.close();
    ofstream fout;
    ostringstream fileNN;
    //r1を変化させていくver　r2, game, day固定
    for (double i = game_min; i <= game_max; i += game_step) {
        for (double j = day_min; j <= day_max; j += day_step) {
            fileNN.str("");
            fileNN << "./final_result/G"<< i << "D" << j << ".txt";
            fout.open(fileNN.str());
            for (double k = r2_min; k <= r2_max; k += r2_step) {
                for (int ii = 0; ii < numofline; ii++) {
                    if (game_[ii] == i && day_[ii] == j && fear_[ii] == k) {
                        fout << benefit_[ii] << " " << fear_[ii] << " " << serv_[ii] << " " \
                             << ally_[ii] << " " << infected_[ii] << endl;
                    }
                }
                fout << endl;
            }
            
            fout.close();
        }
    }
    
    
}
