#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

using namespace std; //可以不用打std

bool int_check(string const &str){
    char* p;
    strtol(str.c_str(), &p, 10);
    return *p == 0;
}

bool time_check(string date){
    bool leapyear;
    int year,month,day;

    if (date.length() != 8) return false;

    // cout << date.length() << endl;

    string year_s = date.substr(0,4);
    string month_s = date.substr(4,2);
    string day_s = date.substr(6,2);

    year = stoi(year_s);
    month = stoi(month_s);
    day = stoi(day_s);

    if(((year%4 == 0) && (year%100 != 0)) || (year%400 == 0)) leapyear = true;
    else leapyear = false;

    if(year < 2019 || year > 2022 || month <= 0 || month > 12 || day <= 0 || day > 31) return false;

    if((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day < 32)) return true;
    else{
        if (month != 2 && day < 31) return true;
        else{
            if(leapyear){
                if(day < 30) return true;
                else return false;
            }
            else {
                if(day < 29) return true;
                else return false;
            }
        }
    }
}

int time_cal(string date_v,string date_c){
    int year_v,month_v,day_v;
    int year_c,month_c,day_c;
    int gap;

    //(yyyymmdd): 20220830

    string year_s = date_v.substr(0,4);
    string month_s = date_v.substr(4,2);
    string day_s = date_v.substr(6,2);

    year_v = stoi(year_s);
    month_v = stoi(month_s);
    day_v = stoi(day_s);

    // cout << year_s << endl;
    // cout << month_s << endl;
    // cout << day_s << endl;

    year_s = date_c.substr(0,4);
    month_s = date_c.substr(4,2);
    day_s = date_c.substr(6,2);

    year_c = stoi(year_s);
    month_c = stoi(month_s);
    day_c = stoi(day_s);

    // cout << year_v << endl;
    // cout << month_v << endl;
    // cout << day_v << endl;

    // cout << year_c << endl;
    // cout << month_c << endl;
    // cout << day_c << endl;

    struct tm d_v = {0};
    struct tm d_c = {0};

    d_v.tm_year = year_v - 1900;
    d_v.tm_mon = month_v;
    d_v.tm_mday = day_v;

    d_c.tm_year = year_c - 1900;
    d_c.tm_mon = month_c;
    d_c.tm_mday = day_c;

    gap = difftime(mktime(&d_c), mktime(&d_v))/86400 + 1; //轉換成time結構，並利用difftime計算時間，+1是因為要包括注射當天

    // cout << gap << endl;

    return gap;
}

int main()
{
    int baseline,age,day;
    float slope,beta,Antibody,alpha_age;
    string mode,brand,pre_infection,age_s;

    string date_v,date_c;
    int year_v,month_v,day_v;

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
            date_v = "";
            brand = "";

            cout << "Enter the date you were vaccinated(yyyymmdd):";
            cin >> date_v;

            //防呆
            while(!time_check(date_v)){
                 //cout << "date error,The range of the date is [20190101-20221231]..\n";
                cout << "Invalid input! Please enter again.\n";
                cin >> date_v;
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
            //初始化
            date_c = "";

            // cout << age << endl;
            // cout << day << endl;
            // cout << brand << endl;
            // cout << pre_infection << endl;

            if (mode1 && mode2 && mode3){

                //-----------------------------
                //現在日期
                cout << "Enter the date today (yyyymmdd):";
                cin >> date_c;

                //防呆
                while(!time_check(date_c)){
                    //cout << "date error,The range of the date is [20190101-20221231]..\n";
                    cout << "Invalid input! Please enter again.\n";
                    cin >> date_c;
                }

                day = time_cal(date_v,date_c);
                // cout << day << endl;
                //-----------------------------

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
