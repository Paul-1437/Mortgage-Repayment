/*Created by Paul-1437, avaliable on Github
input, the only thing you need to do
1. input amount borrowed 输入贷款金额
2. input interest p.a. 输入年利息
3. input monthly repayment 输入月还款量
 input different varibles with space or enter
 不同变量的输入以空格或换行为间隔
输入样例 input sample: 20000 0.01 1000
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
int main(){
    int inital,repayment,bp=1000;
    double intre_rate;
    cin>>inital>>intre_rate>>repayment;
    intre_rate/=12; //monthly intrest cal 计算月利息
    
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
