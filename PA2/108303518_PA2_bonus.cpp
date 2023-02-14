#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std; //可以不用打std

//全域變數
int ring_num = 0;
string initial_state = "",initial_state_r="",initial_state_s="",initial_state_f="";

void state_set(){
    string th,state;
    int ring = 1;

    while (ring <= ring_num){
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
        ring += 1;
    }
}

int str2dec(){
    int ring = 0,state_num=0;
    while(ring < ring_num){
        state_num = state_num + (initial_state_f[ring_num - ring - 1]-'0')*pow(2,ring);
        ring += 1;
    }
    return state_num;
}

void R_rule_try(){
    if (initial_state_r != ""){
        if (initial_state_r[ring_num-1] == '0'){
            initial_state_r[ring_num-1] = '1';
        }
        else{
            initial_state_r[ring_num-1] = '0';
        }
    }
    cout << "If run R-rule once, the rings state of " << ring_num <<
    "-Linked Ring is: " << initial_state_r << endl;
}

void S_rule_try(){
    int ring = ring_num;

    if (initial_state_s.find('1') != string::npos){
        while (initial_state_s[ring] != '1'){
            ring -= 1;
        }

        if (initial_state_s[ring-1] == '0'){
            initial_state_s[ring-1] = '1';
        }
        else{
            initial_state_s[ring-1] = '0';
        }
    }
    cout << "If run S-rule once, the rings state of " << ring_num <<
    "-Linked Ring is: " << initial_state_s << endl;
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

void Finite_Automation(){
    int inv=0,ring=0;
    while (ring < ring_num){
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
    }
}

void Inputrings(){
    cout << "Welcome to play X-Linked Ring!" << endl;
    cout << "How many X-Linked Ring do you want to solve?" << endl;
    cin >> ring_num;

    cout << "\nWhat the " << ring_num << "-Linked Ring look like?" << endl;
    cout << "Please enter the rings state from inside to outside." << endl;
    cout << "If the ring is on the sword, please input 1. Otherwise, please enter 0." << endl; //由內到外

    state_set();

    initial_state_r = initial_state;
    initial_state_s = initial_state;

    //環的狀態：1 0 1 0
    //字串編號：0 1 2 3
    //環的編號：1 2 3 4

    cout << "\nThe rings state of " << ring_num << "-Linked Ring is: " << initial_state << endl;
}

void R_rule(){
    string th,motion;

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

    if (initial_state[ring_num-1] == '1'){
        motion = "down";
        initial_state[ring_num-1] = '0';
    }
    else{
        motion = "on";
        initial_state[ring_num-1] = '1';
    }
    cout << "!! Turn the " << ring_num << th << " ring " << motion << " !!" << endl;
}

void S_rule(){
    int ring = ring_num;
    string th,motion;

    while (initial_state[ring] != '1'){
        ring -= 1;
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

    if (initial_state[ring-1] == '0'){
        motion = "on";
        initial_state[ring-1] = '1';
    }
    else{
        motion = "down";
        initial_state[ring-1] = '0';
    }

    cout << "!! Turn the " << ring << th << " ring " << motion << " !!" << endl;
}

void Outputrings(){
    cout << "The rings state of " << ring_num << "-Linked Ring is: " << initial_state << endl;
}

int SolveRings(){
    int R_S_switch = 0 , R_S_switch_num = 0,state_num = 0;

    cout << "\nLet's start to solve the " << ring_num << "-Linked Ring." << endl;

    Finite_Automation();
    state_num = str2dec();

    if (state_num % 2 == 1){ //R
        cout << "Start with R-rule !!" << endl;
        R_S_switch = 1;
    }
    else{ //S
        cout << "Start with S-rule !!" << endl;
        R_S_switch = 0;
    }

    while(1){
        if (initial_state.find('1') == string::npos){
            return R_S_switch_num;
        }

        if (R_S_switch == 1){ //R_rule
            R_rule();

            R_S_switch = 0;
            R_S_switch_num += 1;
        }
        else{ //S_rule
            S_rule();

            R_S_switch = 1;
            R_S_switch_num += 1;
        }
        Outputrings();
    }
}

int main(){

    Inputrings();

    R_rule_try();
    S_rule_try();

    int R_S_switch_num = 0;

    R_S_switch_num = SolveRings();

    cout << "\nThe " << ring_num << "-Linked Ring is solved in " << R_S_switch_num << " steps." << endl;
    cout << "Thanks for using!! Goodbye ~"<< endl;
}
