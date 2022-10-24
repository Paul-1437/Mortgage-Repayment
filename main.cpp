//Created by Paul-1437, avaliable on Github
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
int main(){
    int inital,repayment,bp=1000;
    bool repayment_change=0,lump_sum=0,interest_change=0;
    double intre_rate;
    
    /*input, the only thing you need to do
    1. input amount borrowed 输入贷款金额
    2. input interest p.a. 输入年利息
    3. input monthly repayment 输入月还款量
    4. input how many repayment changes will be (1=yes,0=no) 输入是还款是否变化
    5. input how many lump sum will be (1=yes,0=no) 输入是否有一次性还款
    6. input hou many intrrest changes will be (1=yes,0=no) 输入利息是否会改变
    input different varibles with space or enter (200 0.01 10 0 0 0, etc.)
    不同变量的输入以空格或换行为间隔
    if any input of 4-6 is yes, then you need to input two varibles for each:
    when to change and change to how much
    如果第4-6个输入中的任意一个为“是“，你需要输入两个变量：
    何时变化和变化后的值
    */
    cin>>inital>>intre_rate>>repayment;
    cin>>repayment_change>>lump_sum>>interest_change;
     
    intre_rate/=12; //monthly intrest cal 计算月利息
    
    int r_after_months=0,r_change_to=repayment;
    if (repayment_change){ //if monthly repayment needs to change 如果要改变月还款量
        cin>>r_after_months>>r_change_to;
        //input changed value and when to change 输入何时执行和改变后的值
        r_after_months--;
    }
    int l_after_months=0,l_change_to=0;
    if (lump_sum){ //if there's a lump sum 如果要执行一次性还款
        cin>>l_after_months>>l_change_to;
        //input lump sum value and when to change 输入何时执行和改变后的值
        l_after_months--;
    }
    int i_after_months=0,i_change_to=intre_rate;
    if (interest_change){ //if instest (p.a.) needs to change 如果要改变年利息
        cin>>i_after_months>>i_change_to;
        //input changed value and when to change 输入何时执行和改变后的值
        i_after_months--;
    }
    
    compound c[1000];
    //initialization 初始化
    c[0].rate_pt=intre_rate*inital;
    c[0].final_amount=inital+c[0].rate_pt-repayment;
    c[0].principal_rp=repayment-c[0].rate_pt;
    c[0].repayment=repayment;
    for (int i = 1; i < 1000; i++)
    {
        if(c[i-1].final_amount>0){ //When the repayment is going 当贷款还没还完
            c[i].rate_pt=c[i-1].final_amount*intre_rate;
            //interest cal 计算利息
            c[i].repayment=repayment;
            //apply replayment 代入月还款量到结构体中
            c[i].final_amount=c[i].rate_pt+c[i-1].final_amount-repayment;
            //balance cal 计算剩余金额
            c[i].principal_rp=repayment-c[i].rate_pt;
            if (lump_sum && l_after_months==i) {
                c[i].final_amount-=l_change_to;
                //apply lump sum 执行一次性还款
            }
            if (repayment_change && r_after_months==i) {
                repayment=r_change_to;
                //apply repayment change 更改月还款
            }
            if (interest_change && i_after_months==i) {
                intre_rate=i_change_to;
                //apply intrest change(p.a.) 更改年利息
            }
            if (c[i].final_amount<0) {  //When the repayment is done 当贷款还完时
                c[i].repayment+=c[i].final_amount;
                c[i].final_amount=0;
                c[i].principal_rp=c[i-1].final_amount;
                bp=i;
                break;
            }
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
    return 0;
}
