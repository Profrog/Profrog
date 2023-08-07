#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int convert_ti(string alpa, string beta)
{
    return stoi(alpa.substr(0, 2)) * 60 + stoi(alpa.substr(3, 2)) + stoi(beta);
}


bool compare0(vector<string> alpa, vector<string> beta)
{
    return convert_ti(alpa[1], "0") <= convert_ti(beta[1], "0");
}


vector<string> solution(vector<vector<string>> plans) {
    vector<string> answer;
    vector<vector<string>> answer2;
  
    sort(plans.begin(), plans.end(), compare0);
    plans.push_back({ "end","24:00","130" });
    int current_time = 0;
   

    for (auto i = 0; i < plans.size() - 1; ++i)
    {
        int remain_time = convert_ti(plans[i][1], "0") - current_time;
        while (remain_time && answer2.size()) //잔여시간이 있을 때 task로 때움
        {
            int tim = stoi(answer2.back()[2]) - remain_time;

            if (tim <= 0) //잔여시간이 더 큼
            {
                remain_time -= stoi(answer2.back()[2]);
                answer.push_back(answer2.back()[0]);
                answer2.pop_back();
            }

            else //task time이 더 큼
            {
                answer2.back()[2] = to_string(tim);
                remain_time = 0;
            }


        }

        current_time = convert_ti(plans[i][1], "0"); //작업 시작시간과 현재 시간사이의 간격 채움

        int tim_2 = convert_ti(plans[i + 1][1], "0") - convert_ti(plans[i][1], "0");
        int task_2 = stoi(plans[i][2]);


        if (task_2 <= tim_2) //일할 시간이 여유시간 보다 짧음
        {
            answer.push_back(plans[i][0]);
            current_time = convert_ti(plans[i][1], plans[i][2]);
        }

        else
        {
            answer2.push_back(plans[i]);  
        }
    }

    while (answer2.size())
    {
        answer.push_back(answer2.back()[0]);
        answer2.pop_back();
    }


    return answer;
}
