#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std; //可以不用打std

//全域變數
int ring_num = 0; //環的數量
string initial_state = ""; //環的狀態

void state_set(int ring){
    string th,state;
    if (ring <= ring_num){
        switch(ring){
            case 1:
                th = "st";
                break;
            case 2:
                th = "nd";
                break;
            case 3:
                th = "rd";
                break;
            default:
                th = "th";
                break;
        }

        cout << "What the state of " << ring << th << " rings?" << endl;
        cin >> state;

        initial_state = initial_state + state;
        // cout << initial_state << endl;

        ring += 1;
        return state_set(ring);
    }
}

int str2dec(int ring,int state_num,string initial_state_f){
    if (ring < ring_num){
        state_num = state_num + (initial_state_f[ring_num - ring - 1]-'0')*pow(2,ring);
        
        ring += 1;
        return str2dec(ring,state_num,initial_state_f);
    }
    else{
        return state_num;
    }
}

void R_rule_try(string initial_state_r){
    if (initial_state_r != ""){
        if (initial_state_r[ring_num-1] == '0'){
            initial_state_r[ring_num-1] = '1';
        }
        else{
            initial_state_r[ring_num-1] = '0';
        }
    }
    cout << "If run R-rule once, the rings state of " << ring_num << "-Linked Ring is: " << initial_state_r << endl;
}

void S_rule_try(string initial_state_s,int ring){
    if (initial_state_s.find('1') != string::npos){
        if (initial_state_s[ring] == '1'){
            if (initial_state_s[ring-1] == '0'){
                initial_state_s[ring-1] = '1';
            }
            else{
                initial_state_s[ring-1] = '0';
            }
        }
        else{
            ring -= 1;
            return S_rule_try(initial_state_s,ring);
        }
    }
    cout << "If run S-rule once, the rings state of " << ring_num << "-Linked Ring is: " << initial_state_s << endl;
}

char inverter(char i){
    if (i == '1'){
        return '0';
    }
    else{
        return '1';
    }
}

int inverter(int i){
    if (i == 1){
        return 0;
    }
    else{
        return 1;
    }
}

string Finite_Automation(int ring,int inv,string initial_state_f){
    if (ring < ring_num){
        if (inv){
            initial_state_f += inverter(initial_state[ring]);
        }
        else{
            initial_state_f += initial_state[ring];
        }

        if (initial_state[ring] == '1'){
            inv = inverter(inv);
        }
        else{
            inv = inv;
        }

        ring += 1;
        return Finite_Automation(ring,inv,initial_state_f);
    }
    else{
        return initial_state_f;
    }
}

int R_S_rule(int R_S_switch,int R_S_switch_num,int ring){
    string motion,th;
    if (initial_state.find('1') == string::npos){
        return R_S_switch_num;
    }

    if (R_S_switch == 1){ //R_rule
        if (initial_state[ring_num-1] == '1'){
            motion = "down";
            initial_state[ring_num-1] = '0';
        }
        else{
            motion = "on";
            initial_state[ring_num-1] = '1';
        }

        switch(ring_num){
            case 1:
                th = "st";
                break;
            case 2:
                th = "nd";
                break;
            case 3:
                th = "rd";
                break;
            default:
                th = "th";
                break;
        }

        cout << "!! Turn the " << ring_num << th << " ring " <<
        motion << " !!" << endl;
        cout << "The rings state of " << ring_num <<
        "-Linked Ring is: " << initial_state << endl;
        R_S_switch_num += 1;
        return R_S_rule(0,R_S_switch_num,ring_num-1);
    }
    else{ //S_rule
        if (initial_state[ring] == '1'){
            if (initial_state[ring-1] == '0'){
                motion = "on";
                initial_state[ring-1] = '1';
            }
            else{
                motion = "down";
                initial_state[ring-1] = '0';
            }

            switch(ring){
                case 1:
                    th = "st";
                    break;
                case 2:
                    th = "nd";
                    break;
                case 3:
                    th = "rd";
                    break;
                default:
                    th = "th";
                    break;
            }

            cout << "!! Turn the " << ring << th << " ring " <<
            motion << " !!" << endl;
            cout << "The rings state of " << ring_num <<
            "-Linked Ring is: " << initial_state << endl;
            R_S_switch_num += 1;
            return R_S_rule(1,R_S_switch_num,ring_num-1);
        }
        else{
            ring -= 1;
            return R_S_rule(0,R_S_switch_num,ring);
        }
    }
}



int main(){
    int state_num=0,R_S_switch_num=0; //state_num：環的狀態轉十進制,R_S_switch_num：操作次數
    string initial_state_r="",initial_state_s="",initial_state_f=""; 
    //initial_state_r：試跑R_rule所用的變數
    //initial_state_s：試跑S_rule所用的變數
    //initial_state_f：操作Finite_Automation所用之變數
    //分開是為了避免混淆

    cout << "Welcome to play X-Linked Ring!" << endl;
    cout << "How many X-Linked Ring do you want to solve?" << endl;
    cin >> ring_num;

    cout << "\nWhat the " << ring_num << "-Linked Ring look like?" << endl;
    cout << "Please enter the rings state from inside to outside." << endl;
    cout << "If the ring is on the sword, please input 1. Otherwise, please enter 0." << endl; //由內到外

    state_set(1);

    initial_state_r = initial_state;
    initial_state_s = initial_state;

    //環的狀態：1 0 1 0
    //字串編號：0 1 2 3
    //環的編號：1 2 3 4

    cout << "\nThe rings state of " << ring_num << "-Linked Ring is: " << initial_state << endl;

    R_rule_try(initial_state_r);
    S_rule_try(initial_state_s,ring_num);

    cout << "\nLet's start to solve the " << ring_num << "-Linked Ring." << endl;

    initial_state_f = Finite_Automation(0,0,initial_state_f);
    state_num = str2dec(0,state_num,initial_state_f);

    if (state_num % 2 == 1){ //R
        cout << "Start with R-rule !!" << endl;
        R_S_switch_num = R_S_rule(1,R_S_switch_num,ring_num-1);
    }
    else{ //S
        cout << "Start with S-rule !!" << endl;
        R_S_switch_num = R_S_rule(0,R_S_switch_num,ring_num-1);
    }

    cout << "\nThe " << ring_num << "-Linked Ring is solved in " <<
    R_S_switch_num << " steps." << endl;
    cout << "Thanks for using!! Goodbye ~"<< endl;
}
