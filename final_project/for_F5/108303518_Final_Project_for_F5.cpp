#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <cctype>

using namespace std; //可以不用打std

bool string_compare(char &st1,char &st2){ // AaBb
    if((isupper(st1) && isupper(st2)) || (islower(st1) && islower(st2))){
        if(st1 > st2) return 0; // 換
        if(st2 > st1) return 1; // 不換
    }
    else{
        if(isupper(st1) && islower(st2)){
            if(st1 + 32 <= st2) return 1; // A:65,a:97
            else return 0;
        }
        else{
            if(st2 + 32 <= st1) return 0;
            else return 1;
        }
    }
}

bool vector_string_compare(string &st1,string &st2){ // AaBb
    if((isupper(st1[0]) && isupper(st2[0])) || (islower(st1[0]) && islower(st2[0]))){
        if(st1 > st2) return 0; // 換
        if(st2 > st1) return 1; // 不換
    }
    else{
        if(isupper(st1[0]) && islower(st2[0])){
            if(st1[0] + 32 <= st2[0]) return 1; // A:65,a:97
            else return 0;
        }
        else{
            if(st2[0] + 32 <= st1[0]) return 0;
            else return 1;
        }
    }
}

string string_intersection(std::vector<string> S){ // 取交集 abc、abd = ab
    string temp;
    int counter = 0;
    for(int i = 0;i<S[0].length();i++){
        counter = 0;
        for(int j=0;j<S.size();j++){
            if(S[j].find(S[0][i]) != string::npos){
                counter += 1;
            }
        }
        if(counter == S.size()){
            temp += S[0][i];
        }
    }
    return temp;
}

string string_union(std::vector<string> S,string co){ // 取聯集 (abc+abd,ab) = c+d
    string temp;
    int counter = 0;
    size_t space = 0;

    for(int i=0;i<S.size();i++){
        if(temp.length() > 0){
            temp += "+";
        }
        temp += S[i];
    }

    cout << temp << endl;

    for(int i=0;i<co.length();i++){
        while((space = temp.find(co[i])) != string::npos){
            temp.erase(space,1);
        }
    }

    if(temp[temp.length() - 1] == '+'){ // 最後一個字元為"+"
        temp.erase(temp.length() - 1);
    }

    if(temp[0] == '+'){ // 第一個字元為"+"
        temp.erase(0);
    }

    return temp;
}

string variable_count(string B_F_split){ //刪除重複的 // abc+abd = abcd
    string temp;

    for(int i=0;i<B_F_split.length();i++){
        if(temp.find(B_F_split[i]) == string::npos && B_F_split[i] != '+'){ // string取出是char
            temp += B_F_split[i];
        }
    }

    cout << "variable: ";
    std::sort(temp.begin(), temp.end(),string_compare); // string排序
    cout << temp << endl;
    return temp;
}

bool vector_find(std::vector<string> function_and,string temp){
    for(int i=0;i<function_and.size();i++){
        if(function_and[i] == temp){
            return 1;
        }
    }
    return 0;
}

void vector_show(std::vector<string> show_vector){
    for (int i=0;i<show_vector.size();i++){
        cout << show_vector[i] << " ";
    }
    cout << endl;
}

std::vector<string> Boolean_function_split(string B_F_split){
    string temp;
    vector<string> B_F_S;
    size_t plus = 0;

    while((plus = B_F_split.find("+")) != string::npos){
        temp = B_F_split.substr(0,plus);
        B_F_S.push_back(temp);
        B_F_split = B_F_split.substr(plus+1);
    }

    B_F_S.push_back(B_F_split); // 最後一項

    std::sort(B_F_S.begin(), B_F_S.end(),vector_string_compare); // B_F_S排序

    // 顯示vetor
    cout << "B_F_S: ";
    vector_show(B_F_S);

    return B_F_S;
}

bool cube_free_detect(string F_div_co){
    cout << "---cube_free_detect---" << endl;
    vector<string> B_F_S = Boolean_function_split(F_div_co);
    string variable_total = variable_count(F_div_co);
    int counter = 0,counter_unit = 0;

    // 判斷最大元素長度
    for(int j=0;j<B_F_S.size();j++){
        counter_unit = max(counter_unit,(int)B_F_S[j].length());
    }

    if(counter_unit == 1){ // 判斷元素皆為1直接cube free
        return 1; // cube_free
    }

    for(int i=0;i<variable_total.length();i++){
        // 數cube有沒有這個元素
        for(int j=0;j<B_F_S.size();j++){
            if(B_F_S[j].find(variable_total[i]) != string::npos)
                counter += 1;
        }

        if(counter == B_F_S.size()){
            return 0; // not cube_free
        }
        counter = 0;
    }
    return 1;
}

string Kernel_mul(std::vector<string> &Kernel){
    vector<vector<string>> Kernel_unit;
    vector<string> B_F_S,mul_temp_list,mul;
    string mul_temp,mul_final;

    for(int i=0;i<Kernel.size();i++){
        B_F_S = Boolean_function_split(Kernel[i]);
        Kernel_unit.push_back(B_F_S);

        B_F_S.clear();
        vector <string>().swap(B_F_S);
    }

    for(int i=0;i<Kernel_unit.size();i++){
        for(int j=0;j<Kernel_unit[i].size();j++){
            cout << Kernel_unit[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    // 第一個Kernel
    mul_temp_list.assign(Kernel_unit[0].begin(), Kernel_unit[0].end());

    for(int i=1;i<Kernel_unit.size();i++){
        for(int j=0;j<mul_temp_list.size();j++){
            cout << "mul1:" << mul_temp_list[j] << endl;
            for(int k=0;k<Kernel_unit[i].size();k++){
                cout << "mul2:" << Kernel_unit[i][k] << endl;

                set_union(mul_temp_list[j].begin(),mul_temp_list[j].end(),Kernel_unit[i][k].begin(),Kernel_unit[i][k].end(),back_inserter(mul_temp));
                std::sort(mul_temp.begin(), mul_temp.end(),string_compare); // string排序

                // 重複不放進mul
                if(!vector_find(mul,mul_temp)){
                    mul.push_back(mul_temp);
                    cout << "get:" << mul_temp << endl;
                    cout << "----------" << endl;
                }
                mul_temp.clear();
            }
        }
        mul_temp_list.assign(mul.begin(), mul.end());

        if(i < Kernel_unit.size() - 1){
            mul.clear();
            vector <string>().swap(mul);
        }
    }

    std::sort(mul.begin(), mul.end(),vector_string_compare); // mul排序

    // 顯示mul
    cout << "mul: ";
    for(int i=0;i<mul.size();i++){
        cout << mul[i] << " ";

        mul_final += mul[i];
        if(i < mul.size()-1){
            mul_final += "+";
        }
    }
    cout << endl;

    cout << "mul_final: " << mul_final << endl;
    return mul_final;
}

// Kernel Algorithm
void FindKernels(string B_F_split,std::vector<string> &Kernel){ // F: input Boolean function
    string variable_total = variable_count(B_F_split);

    vector<string> B_F_S = Boolean_function_split(B_F_split);

    vector<string> S;
    string co,F_div_co;

    for(int i=0;i<variable_total.length()+1;i++){
        S.clear();
        vector <string>().swap(S);
        
        // 數cube有沒有這個元素
        if(i==0){ // 掃1
            cout << "1: ";
            S.assign(B_F_S.begin(), B_F_S.end()); // 複製BFS
        }
        else{
            cout << variable_total[i-1] << ": "; // 因為先掃1所以i-1
            for(int j=0;j<B_F_S.size();j++){
                if(B_F_S[j].find(variable_total[i-1]) != string::npos){
                    S.push_back(B_F_S[j]);
                    cout << B_F_S[j] << " "; // 顯示S
                }
            }
            cout << endl;
        }

        if(S.size() > 1){ // there are at least 2 cubes in F that have variable x
            co = string_intersection(S); // S取交集
            cout << "co: " << co << endl; // 顯示co

            F_div_co = string_union(S,co); // K = K U FindKernels(F/co);
            cout << "F_div_co: " << F_div_co << endl; // 顯示F_div_co

            if(!cube_free_detect(F_div_co)){ // not cube_free
                cout << "**********" << endl;
                FindKernels(F_div_co,Kernel);
            }
            else{ // cube_free

                // 重複不放進K
                if(!vector_find(Kernel,F_div_co)){
                    Kernel.push_back(F_div_co);
                    cout << "get:" << F_div_co << endl;
                }
                else{
                    cout << F_div_co << " repeat" << endl;
                }
            }
        }

        cout << "----------" << endl;
    }
}

void FindKernels_2(string B_F_split,std::vector<string> &Kernel,bool &no_kernel){ // F: input Boolean function
    string variable_total = variable_count(B_F_split);
    vector<string> B_F_S = Boolean_function_split(B_F_split);

    vector<string> S;
    string co,F_div_co,unit,qoute_temp;

    vector<string> qoute[variable_total.length()];
    int qoute_flag = 0,quote_counter = 0;

    vector<string> temp;

    for(int i=0;i<variable_total.length();i++){
        S.clear();
        vector <string>().swap(S);
        
        // 數cube有沒有這個元素
        cout << variable_total[i] << ": ";
        for(int j=0;j<B_F_S.size();j++){
            if(B_F_S[j].find(variable_total[i]) != string::npos){
                S.push_back(B_F_S[j]);
                cout << B_F_S[j] << " "; // 顯示S
            }
        }
        cout << endl;

        if(S.size() > 1){ // there are at least 2 cubes in F that have variable x
            co = string_intersection(S); // S取交集
            cout << "co: " << co << endl; // 顯示co
            no_kernel = 1;

            F_div_co = string_union(S,co); // FindKernels(F/co);
            cout << "F_div_co: " << F_div_co << endl; // 顯示F_div_co

            qoute_flag = 0;
            for(int j=0;j<quote_counter;j++){
                if(qoute[j][1] == F_div_co){
                    if(co != qoute[j][0]){
                        qoute_temp = qoute[j][0] + "+" + variable_total[i];
                        qoute[j][0] = qoute_temp;
                    }

                    qoute_flag = 1;
                    break;
                }
            }

            if(qoute_flag == 0){
                qoute[quote_counter].push_back(co);
                qoute[quote_counter].push_back(F_div_co);
                
                quote_counter += 1;
            }

            // 顯示qoute
            cout << "qoute: " << endl;
            for(int i=0;i<quote_counter;i++){
                for(int j=0;j<qoute[i].size();j++){
                    cout << qoute[i][j] << " ";
                }
                cout << endl;
            }
            cout << endl;

            FindKernels_2(F_div_co,temp,no_kernel);

            // cout << "temp:";
            // vector_show(temp);

            if(temp.size() > 0){
                qoute[i].pop_back(); // 刪除no cubefree項

                qoute[i].insert(qoute[i].end(),temp.begin(),temp.end()); // 將temp存入qoute[i]

                temp.clear();
                vector <string>().swap(temp);
            }
        }
        cout << "----------" << endl;
    }

    // 二維vector轉一維vector
    for(int i=0;i<quote_counter;i++){
        for(int j=0;j<qoute[i].size();j++){
            if(!vector_find(Kernel,qoute[i][j]) && qoute[i][j].find("+") != string::npos){ // 去掉單項與連乘項
                cout << qoute[i][j] << " ";
                Kernel.push_back(qoute[i][j]);
            }
        }
    }
    cout << endl;

    std::sort(Kernel.begin(), Kernel.end(),vector_string_compare); // Kernel排序

    // 顯示Kernel
    cout << "Kernel: ";
    vector_show(Kernel);
}

void function_intersection(std::vector<vector<string>> &function_CAL_split,std::vector<string> &function_and){ // 方程式取交集
    vector<string> K1_unit;
    vector<string> K2_unit;
    vector<string> K1_K2_temp;
    vector<string> function_and_temp,function_and_temp1;

    string temp;

    function_and_temp.assign(function_CAL_split[0].begin(),function_CAL_split[0].end());

    for(int n=1;n<function_CAL_split.size();n++){
        for(int i=0;i<function_and_temp.size();i++){
            K1_unit.clear();
            vector <string>().swap(K1_unit);
            K1_unit = Boolean_function_split(function_and_temp[i]);

            for(int j=0;j<function_CAL_split[n].size();j++){
                cout << "K1: " << function_and_temp[i] << endl;
                cout << "K2: " << function_CAL_split[n][j] << endl;

                K2_unit.clear();
                vector <string>().swap(K2_unit);
                K2_unit = Boolean_function_split(function_CAL_split[n][j]);

                K1_K2_temp.clear();
                vector <string>().swap(K1_K2_temp);

                for(int k=0;k<K1_unit.size();k++){
                    for(int p=0;p<K2_unit.size();p++){
                        if(K1_unit[k] == K2_unit[p]){
                            K1_K2_temp.push_back(K1_unit[k]);
                            cout << K1_unit[k] << endl;
                        }
                    }
                }
                
                // 單項重複項不採計
                if(K1_K2_temp.size() > 1){
                    for(int k=0;k<K1_K2_temp.size();k++){
                        temp += K1_K2_temp[k];
                        if(k < K1_K2_temp.size()-1){
                            temp += "+"; // 元素合併 + "+"
                        }
                    }

                    // 重複不放進function_and
                    if(!vector_find(function_and_temp1,temp)){
                        function_and_temp1.push_back(temp);
                        cout << temp << endl;
                    }
                    else{
                        cout << temp << " repeat" << endl;
                    }
                }

                temp.clear();

                cout << "----------" << endl;

                cout << "K1_and_K2: ";
                for(int k=0;k<function_and_temp1.size();k++){
                    cout << function_and_temp1[k] << " ";
                }
                cout << endl;
                cout << "----------" << endl;
            }
        }

        if(n < function_CAL_split.size() - 1){
            function_and_temp.clear();
            vector <string>().swap(function_and_temp);

            for(int i=0;i<function_and_temp1.size();i++){
                FindKernels(function_and_temp1[i],function_and_temp);

                cout << "function_and_temp: ";
                vector_show(function_and_temp);
            }

            function_and_temp1.clear();
            vector <string>().swap(function_and_temp1);
        }
    }
    
    function_and.assign(function_and_temp1.begin(),function_and_temp1.end());
}

int main(){
    vector<string> B_F_name;
    vector<string> B_F_split;
    vector<string> CAL;

    clock_t start, end;
    string input_temp;
    size_t space = 0;

    bool no_kernel = 0;

    start = clock();

    // input讀檔 ------------------------------------------------------------
    string filename = "testcase2_example";

    ifstream inClientFile(filename, ios::in);
    if (!inClientFile){
		cerr << "file could not be opened" << endl;
		exit(EXIT_FAILURE);
	}

    while (getline(inClientFile, input_temp)){
        cout << input_temp << endl;
        if((space = input_temp.find("=")) != string::npos){
            B_F_split.push_back(input_temp.substr(space+1)); // 把F1=截掉
            B_F_name.push_back(input_temp.substr(0,space)); // 剩餘方程式部分
        }
        else{
            CAL.push_back(input_temp);
        }
    }

    cout << endl;

    // 顯示B_F_name
    cout << "B_F_name: ";
    vector_show(B_F_name);
    
    // 顯示B_F_split
    cout << "B_F_split: ";
    vector_show(B_F_split);

    // 顯示CAL(計算方程式)
    cout << "CAL: " << endl;
    vector_show(CAL);

    inClientFile.close();

    cout << endl;

    vector<string> Kernel[B_F_name.size()];

    // output寫檔 ------------------------------------------------------------

    string mul_final,new_B_F;
    vector<string> B_F_S;

    // output寫入
    ofstream outClientFile(filename + ".out", ios::out);
	if (!outClientFile){
		cerr << "file could not be opened" << endl;
		exit(EXIT_FAILURE);
	}

    for(int i=0;i<B_F_name.size();i++){
        cout << B_F_name[i] << endl;
        FindKernels_2(B_F_split[i],Kernel[i],no_kernel);

        // 合併B_F_S
        B_F_S = Boolean_function_split(B_F_split[i]);
        for(int j=0;j<B_F_S.size();j++){
            new_B_F += B_F_S[j];
            if(j < B_F_S.size()-1){
                new_B_F += "+";
            }
        }

        // 清掉上次結果
        B_F_S.clear();
        vector <string>().swap(B_F_S);

        // 最後掃1
        if(Kernel[i].size() > 0){
            mul_final = Kernel_mul(Kernel[i]); // 不能先放再mul

            cout << "new_B_F:" << new_B_F << endl;
            Kernel[i].push_back(new_B_F); // 先放再刪

            cout << cube_free_detect(new_B_F) << endl;

            if(cube_free_detect(new_B_F)){ // 沒有共同元素，判定kernel相乘不為本身
                if(new_B_F == mul_final){
                    Kernel[i].pop_back();
                }
                // Kernel[i].pop_back();
            }
            else{ // 有共同元素
                Kernel[i].pop_back();
            }

            mul_final.clear();
        }
        else{ // 沒有kernel
            if(!no_kernel){
                cout << "new_B_F:" << new_B_F << endl;
                Kernel[i].push_back(new_B_F);
            }
            else{
                Kernel[i].push_back("none");
            }
        }

        no_kernel = 0;
        new_B_F.clear();

        if(CAL.size() == 0)
            outClientFile << B_F_name[i] << endl;
        for (int j=0;j<Kernel[i].size();j++){
            if(j<Kernel[i].size()-1){
                if(CAL.size() == 0)
                    outClientFile << Kernel[i][j] << " ";
                cout << Kernel[i][j] << " ";
            }
            else{
                if(CAL.size() == 0)
                    outClientFile << Kernel[i][j];
                cout << Kernel[i][j];
            }
        }

        if(CAL.size() == 0)
            outClientFile << endl;
        cout << endl << endl;
    }

    cout << "^^^^^^^^^^" << endl;

    // 顯示最後Kernel
    for (int i=0;i<B_F_name.size();i++){
        cout << B_F_name[i] << ": ";
        for (int j=0;j<Kernel[i].size();j++){
            cout << Kernel[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    vector<string> CAL_split;
    string CAL_temp,function_temp;
    vector<string> function_and;

    vector<vector<string>> function_CAL_split;

    // CAL計算方程式 ------------------------------------------------------------

    // F1 and F2
    for(int i=0;i<CAL.size();i++){
        CAL_split.clear();
        vector <string>().swap(CAL_split);
        function_and.clear();
        vector <string>().swap(function_and);
        function_CAL_split.clear();
        vector<vector<string>>().swap(function_CAL_split);

        CAL_temp = CAL[i];
        cout << CAL_temp << endl; // F1 and F2
        outClientFile << CAL_temp << endl;

        while((space = CAL_temp.find(" ")) != string::npos){
            // cout << CAL_temp << endl;
            if((function_temp = CAL_temp.substr(0,space)) != "and"){
                CAL_split.push_back(function_temp);
            }
            CAL_temp.erase(0, space + 1); // 空格長度
        }
        CAL_split.push_back(CAL_temp); // 最後一項

        for(int j=0;j<CAL_split.size();j++){
            for(int k=0;k<B_F_name.size();k++){
                if(CAL_split[j] == B_F_name[k]){
                    function_CAL_split.push_back(Kernel[k]);
                    break;
                }
            }
        }

        // 顯示CAL_split
        cout << "CAL_split: ";
        vector_show(CAL_split);

        // 顯示function_CAL_split
        cout << "function_CAL_split: " << endl;
        for (int j=0;j<function_CAL_split.size();j++){
            for(int k=0;k<function_CAL_split[j].size();k++){
                cout << function_CAL_split[j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;

        function_intersection(function_CAL_split,function_and);
        
        if(function_and.size() > 0){
            for(int j=0;j<function_and.size();j++){
                outClientFile << function_and[j];
                if(j < function_and.size()-1){
                    outClientFile << " ";
                }
            }
            outClientFile << endl;
        }
        else{
            outClientFile << "none" << endl;
        }
    }

    outClientFile.close();

    end = clock();
    cout << "execution_time:" << ((double) (end - start)) / CLOCKS_PER_SEC << endl;
}