#include <iostream>
#include <string>

using namespace std;

struct student{
    string name;
    int old;
    string birth;
    string state;
};

void changeName(struct student* st, string newname){
    st->name = newname;
}

int main(){
    int N,K;
    cin >> N >> K;
    student *roster[N];
    for(int i = 0; i < N; i++){
        student *st = new student;
        cin >> st->name >> st->old >> st->birth >> st->state;
        roster[i] = st;
    }

    for(int i = 0; i < K; i++){
        int a;
        string nn;
        cin >> a >> nn;
        a--;
        changeName(roster[a],nn);
    }

    
    for(int i = 0; i < N; i++){
        cout << roster[i]->name << " " << roster[i]->old << " " << roster[i]->birth << " " << roster[i]->state << endl;
    }
}
