#include <stdio.h>
#include <iostream>
#include <stdlib.h> 
#include <queue>
#include <stack>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <math.h>

using namespace std;


const int order_num = 40;

vector< vector<int> > od_map (order_num+1, vector<int>(order_num+1, -1)) ;

const double  T     =   10000   ; //初始温度  
const double  EPS   =   1e-8   ; //终止温度  
const double  DELTA =   0.98   ; //温度衰减率  
#define LIMIT 300   //概率选择上限  
#define OLOOP 1000    //外循环次数  
#define ILOOP 300   //内循环次数  

int init_od(void)
{
    for(int i =1; i< order_num+1; i++)
    {
        for (int j=i; j< order_num + 1; j++)
        {
            // 真实路径距离
            od_map[i][j] = ((i+5)*(j+7)- 3 )%30;
            od_map[j][i] = od_map[i][j];

            if (i == 0 || j == 0 || i==j)
                od_map[i][j] = -1;
        }
        
    }
 

    return 0;
}


int print_od(void)
{
 
    for(int i =0; i<order_num + 1; i++)
    {
        for (int j=0; j<order_num + 1; j++)
        {
            printf("%d ",od_map[i][j]);
        }
         printf("\n");
    }
    printf("\n");
    return 0;
}




int gen_new_path(vector<int> &cur_result ,   vector<int>& new_result )
{
    new_result = cur_result;
    while (1)
    {
        int l = (int)(rand() % order_num );
        int r = (int)(rand() % order_num );

        if (l == r)
            continue;

        new_result[l] = cur_result[r];
        new_result[r] = cur_result[l];
        break;
    }
    return 0;
}

int cal_dis(vector<int> &cur_result)
{
    int total_dis = 0;

    for (int i=0; i<cur_result.size() -1; i++  )
    {
        total_dis += od_map[cur_result[i]][cur_result[i+1]];
    }
    return total_dis;
}



int judge( int s_new, int s_old, double t )
{
    if (s_new <  s_old )
        return 1;

    double d = exp(-( (s_new - s_old) / t) );
    double rand = 0.001;
    if(d > rand)
        return 1;
    else
        return 0;    
}


int main(void)
{
    init_od();
    print_od();

    vector<int> myints;
    for (int i=1; i<=order_num; i++)
        myints.push_back(i);


    vector<int> cur_result(myints.begin(),  myints.end() );
    int cur_cost = cal_dis(cur_result);  

    int offset = 0;

    vector<int> next_result;

    double t_current  =  T;

    while( t_current > EPS)
    {
        gen_new_path(cur_result, next_result)  ;
        int new_cost = cal_dis(next_result); 


        if ( 1 ==  judge( new_cost, cur_cost,  t_current  )  ) 
        {
            cur_cost = new_cost;
            cur_result = next_result;
            //printf("%d loop  cost= %d\n", offset, cur_cost);
        }

        t_current = t_current * DELTA;

        offset++;

        if (offset%10 == 0)
            printf("%d loop  t_current=%f  cost= %d\n", offset, t_current, cur_cost);
    }

    return 0;
}

