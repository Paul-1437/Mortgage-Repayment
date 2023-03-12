/*
Created by Paul-1437. Avaliable on github.
This is a project for calculating mortgage repayment(personal loans). This code is the advanced version. The way to input varibles might be difficult for people who have coding experience. If you found it too hard, try basic.cpp. IDE is required to run the code.
这是一个计算个人贷款的微型工程，此文件是是高级版程序，复杂的输入程序可能会使没有接触过编程的小伙伴觉得困难。如有不适请移步至basic.cpp。你需要IDE以运行该程序

input different varibles with space or enter (200 0.01 10 0 0 0, etc.)
不同变量的输入以空格或换行为间隔

*/
#include <iostream>
#include <cstdio>
using namespace std;
struct compound
{
    double rate_pt;
    double final_amount;
    double principal_rp;
    int repayment;
};
struct repay_c{
    int after_months;
    int change_to;
};
struct interest_c{
    int after_months;
    double change_to;
};
struct lump{
    int after_months;
    int change_to;
};
int main(){
    int inital,repayment;
    int repayment_change=0,lump_sum=0,interest_change=0;
    repay_c r[50];
    interest_c in[50];
    lump l[50];
    double intre_rate,bp=1000;
    cout<<"Input amount borrowed"<<endl;
    cin>>inital;
    cout<<"input interest rate p.a."<<endl;
    cin>>intre_rate;
    cout<<"input monthly repayment"<<endl;
    cin>>repayment;
    cout<<"input how many repayment changes (0=no changes)"<<endl;
    cin>>repayment_change;
    cout<<"input how many lump sum (0=no changes)"<<endl;
    cin>>lump_sum;
    cout<<"input how many interest changes (0=no changes)"<<endl;
    cin>>interest_change;
     
    intre_rate/=12; //monthly intrest cal 计算月利息
    for (int i=0; i<repayment_change; i++){
    //if monthly repayment needs to change 如果要改变月还款量
        cout<<"input changed value"<<endl;
        cin>>r[i].after_months;
        cout<<"input which month"<<endl;
        cin>>r[i].change_to;
        //input changed value and which month to change 输入何时执行和改变后的值
    }
    for (int i=0; i<lump_sum; i++){ //if there's a lump sum 如果要执行一次性还款
        cout<<"input lump sum value"<<endl;
        cin>>l[i].after_months;
        cout<<"input which month"<<endl;
        cin>>l[i].change_to;
        //input lump sum value and which month to change 输入何时执行和改变后的值
    }
    for (int i=0; i<interest_change; i++){ //if instest (p.a.) needs to change 如果要改变年利息
        cout<<"input changed intest"<<endl;
        cin>>in[i].after_months;
        cout<<"input which month"<<endl;
        cin>>in[i].change_to;
        in[i].change_to/=12;
        //input changed value and which month to change 输入何时执行和改变后的值
    }
    compound c[1000];
    //initialization 初始化
    c[0].rate_pt=intre_rate*inital;
    c[0].final_amount=inital+c[0].rate_pt-repayment;
    c[0].principal_rp=repayment-c[0].rate_pt;
    c[0].repayment=repayment;
    for (int i = 1; i < 1000; i++)
    {
        for (int j=0; j<=repayment_change; j++){
            if (r[j].after_months==i) {
                repayment=r[j].change_to;
                //apply repayment change 更改月还款
            }
        }
        for (int j=0; j<=interest_change; j++) {
            if (in[j].after_months==i) {
                intre_rate=in[j].change_to;
                //apply intrest change(p.a.) 更改年利息
            }
        }
        
        c[i].rate_pt=c[i-1].final_amount*intre_rate;
        //interest cal 计算利息
        c[i].repayment=repayment;
        //apply replayment 代入月还款量到结构体中
        c[i].final_amount=c[i].rate_pt+c[i-1].final_amount-repayment;
        //balance cal 计算剩余金额
        c[i].principal_rp=repayment-c[i].rate_pt;
        for (int j=0; j<=lump_sum; j++) {
            if (l[j].after_months==i) {
                c[i].final_amount-=l[j].change_to;
                //apply lump sum 执行一次性还款
            }
        }
        if (c[i].final_amount<0) {  //When the repayment is done 当贷款还完时
            c[i].repayment+=c[i].final_amount;
            c[i].final_amount=0;
            c[i].principal_rp=c[i-1].final_amount;
            bp=i;
            break;
        }
}
    //output
    printf("Month\tInterest\t Repayment\t  Principal\t\tFinal amount\n");
    for (int i=0; i<=bp; i++) {
        cout<<i+1<<"\t\t";
        printf("%.2f\t\t ",c[i].rate_pt);
        printf("%d\t\t  ",c[i].repayment);
        printf("%.2f\t\t",c[i].principal_rp);
        printf("%.2f",c[i].final_amount);
        cout<<endl;
    }
    cout<<"Months to repay: "<<++bp<<endl;
    bp/=12;
    printf("Years to repay: %.6f\n", bp);
    return 0;
}
