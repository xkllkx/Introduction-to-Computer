#include <iostream>
#include <iomanip>
#include <string>

using namespace std; //可以不用打std

bool int_check(string const &str){
    char* p;
    strtol(str.c_str(), &p, 10);
    return *p == 0;
}

int main(){
    int baseline,age,day;
    float slope,beta,Antibody,alpha_age;
    string mode,brand,pre_infection,age_s,day_s;
    
    int mode1 = 0,mode2 = 0,mode3 = 0;

    while(mode != "0"){
        cout << "***Antibody Calculator***\n";
        cout << "Enter 1 to input body data\n";
        cout << "Enter 2 to input vaccine data\n";
        cout << "Enter 3 to input prior infection\n";
        cout << "Enter R to calculate antibody\n";
        cout << "Enter 0 to exit system\n";

        cin >> mode;

        while(mode != "0" && mode != "1" && mode != "2" && mode != "3" && mode != "R"){ //string 用""，char用''
            cout << "Invalid input! Please enter again.\n";
            cin >> mode;
        }

        if (mode == "1"){  //字元要用單引號 //只有if-else
            //初始化
            age = 0;
            age_s = "";

            cout << "Enter your age:";
            cin >> age_s;

            // cout << age_s;

            //防呆
            while(1){
                try{
                    if (int_check(age_s)){
                        age = stoi(age_s);
                    }
                    // cout << age << endl;
                }catch (std::exception &e) {
                    cout << "Invalid input! Please enter again.\n";
                    cin >> age_s;
                    continue;
                }

                if (age >= 1 && age <= 120){
                    break;
                }
                else{
                    cout << "Invalid input! Please enter again.\n";
                    cin >> age_s;
                }
            }

            cout << "\n";
            mode1 = 1;
        }
        else if (mode == "2"){
            //初始化
            day = 0;
            day_s = "";
            brand = "";

            cout << "Enter how many days pass by since you were vaccinated:";
            cin >> day_s;

            //防呆
            while(1){
                try{
                    if (int_check(day_s)){
                        day = stoi(day_s);
                    }
                    // cout << age << endl;
                }catch (std::exception &e) {
                    cout << "Invalid input! Please enter again.\n";
                    cin >> day_s;
                    continue;
                }

                if (day > 0){
                    break;
                }
                else{
                    cout << "Invalid input! Please enter again.\n";
                    cin >> day_s;
                }
            }

            cout << "Enter the brand(A/B/M):";
            cin >> brand;

            //防呆
            while(brand != "A" && brand != "B" && brand != "M"){
                // cout << "brand error,please choose A/B/M.\n";
                cout << "Invalid input! Please enter again.\n";
                cin >> brand;
            }

            cout << "\n";
            mode2 = 1;
        }
        else if (mode == "3"){
            //初始化
            pre_infection = "";

            cout << "Did you have a prior infection(y/n):";
            cin >> pre_infection;

            //防呆
            while(pre_infection != "y" && pre_infection != "n"){
                // cout << "prior infection error,please choose y/n.\n";
                cout << "Invalid input! Please enter again.\n";
                cin >> pre_infection;
            }

            cout << "\n";
            mode3 = 1;
        }
        else if (mode == "R"){

            // cout << age << endl;
            // cout << day << endl;
            // cout << brand << endl;
            // cout << pre_infection << endl;

            if (mode1 && mode2 && mode3){
                //資料前處理
                //body data
                if (age >= 1 && age <= 40){
                    alpha_age = 0.05;
                    slope = -2;
                }
                else if (age >= 41 && age <= 80){
                    alpha_age = 0;
                    slope = -3;
                }
                else{
                    alpha_age = -0.05;
                    slope = -3.5;
                }

                // cout << alpha_age << endl;
                // cout << slope << endl;

                //vaccine data
                if (brand == "A"){
                    baseline = 300;
                }
                else if (brand == "B"){
                    baseline = 800;
                }
                else{
                    baseline = 900;
                }

                // cout << baseline << endl;

                //Prior infection
                if (pre_infection == "y"){
                    beta = 0.5;
                }
                else{
                    beta = 1;
                }

                // cout << beta << endl;

                if (day <= 14){
                    Antibody = baseline * (1 + alpha_age) * day/14;
                }
                else{
                    Antibody = (baseline * (1 + alpha_age)) + (slope * (day - 14) * beta);
                }

                //判斷
                if (Antibody >= 50.){
                    cout << "Your antibody is " << setprecision(2) << fixed << Antibody << endl;
                    cout << "You are safe!\n";
                    cout << "\n";
                }
                else if (Antibody >= 0. && Antibody < 50.){
                    cout << "Your antibody is " << setprecision(2) << fixed << Antibody << endl;
                    cout << "Watch out! Antibody is low.\n";
                    cout << "\n";
                }
                else{
                    cout << "Your antibody is 0.00\n";
                    cout << "Watch out! Antibody is low.\n";
                    cout << "\n";
                }
            }
            else{
                cout << "Data is not enough.\n";
                cout << "\n";
            }
        }
        else if (mode == "0"){
            cout << "\n\n";
            cout << "bye~";
            return 0;
        }
        else{
            continue;
        }
    }
}
