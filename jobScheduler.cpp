#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
#include<map>
#include<unordered_map>

using namespace std;

class Job{
    string jobName;
    int duration;
    int priority;
    int deadline;
    int userType;

    public:
    Job(){

    }
    Job(string jobName, int duration, int priority, int deadline, int userType){
        this->jobName = jobName;
        this->duration = duration;
        this->priority = priority;
        this->deadline = deadline;
        this->userType = userType;
    }

    //getter and setter for each attribute

    string getJobName(){
        return this->jobName;
    }

    void setJobName(string jobName){
        this->jobName = jobName;
    }

    int getDuration(){
        return this->duration;
    }

    void setDuration(int duration){
        this->duration = duration;
    }

    int getPriority(){
        return this->priority;
    }

    void setPriority(int priority){
        this->priority = priority;
    }

    int getDeadline(){
        return this->deadline;
    }

    void setDeadline(int deadline){
        this->deadline = deadline;
    }

    int getUserType(){
        return this->userType;
    }

    void setUserType(int userType){
        this->userType = userType;
    }

    string toString(){
        stringstream ss;
        ss<<"Input [jobName=" << this->jobName<<  ", duration=" << this->duration<< ", priority=" <<this->priority<<
        ", deadline=" <<this->deadline<< ", userType=" <<this->userType<< "]";

        return ss.str();
    }

};

class EDF{
    vector<string> jobNames;
    int deadline;
    public: 
    EDF(){ }

    int getDeadline(){
        return this->deadline;
    }

    void setDeadline(int deadline){
        this->deadline=deadline;
    }

    vector<string> getJobNames(){
        return this->jobNames;
    }

    void setJobNames(vector<string> jobName){
        this->jobNames =  jobName;
    }

};


class JobScheduler{
    public:

    /*void shortestJobFirst(int threadNo, vector<Job> job);
    void firstComeFirstServe(int threadNo, vector<Job> job);
    void fixedPriorityScheduling(int threadNo, vector<Job> job);
    void earliestDeadlineFirst(int threadNo, vector<Job> job);
    map<int, vector<string>> assignThreadsToJobs(vector<Job> jobs);
    void displayScheduleJobs(map<int, vector<string>> threads);
    */


    static bool cmp1(Job j1, Job j2){
        if(j1.getDuration() == j2.getDuration()){
            return j1.getPriority() < j2.getPriority();
        }
        else{
            return j1.getDuration() < j2.getDuration();
        }
    }

    static bool cmp2(Job j1, Job j2){
        if(j1.getPriority() == j2.getPriority()){
            if(j1.getUserType() == j2.getUserType()){
                return j1.getDuration() > j2.getDuration();
            }
            else{
                return j1.getUserType() < j2.getUserType();
            }
        }
        else{
            return j1.getPriority() < j2.getPriority();
        }
    }

    static bool cmp3(Job j1, Job j2){
        if(j1.getDeadline() == j2.getDeadline()){
            if(j1.getPriority() == j2.getPriority()){
                return j1.getDuration() < j2.getDuration();
            }
            else{
                return j1.getPriority() < j2.getPriority();
            }
        }
        else{
            return j1.getDeadline() < j2.getDeadline();
        }
    }

    map<int, vector<string>> assignThreadsToJobs(int threadNo, vector<Job> jobs){
        int threadCnt = 0;
        map<int, vector<string>> res;

        for(Job job : jobs){
            if(res.find(threadCnt % threadNo) == res.end()){
                vector<string> t;
                t.push_back(job.getJobName());
                res[threadCnt % threadNo] = t;
            }
            else{
                res[threadCnt % threadNo].push_back(job.getJobName());
            }
            threadCnt++;
        }
        return res;
    }

    map<int, EDF> assignThreadsToJobsForEdf(int threadNo, vector<Job> jobs){
        int threadCnt = 0;
        map<int, EDF> res;
        
        EDF edf;
        for(Job job : jobs){
            if(res.find(threadCnt % threadNo) == res.end()){
                edf = EDF();
                vector<string> t;
                t.push_back(job.getJobName());
                edf.setJobNames(t);
                //edf.getJobNames().push_back(job.getJobName());
                edf.setDeadline(job.getDuration());
                res[threadCnt % threadNo] = edf;
            }
            else{
                //EDF edf;
                //edf  = res[threadCnt % threadNo];
                if( (res[threadCnt % threadNo].getDeadline()+job.getDuration()) <=  job.getDeadline()){
                    vector<string> t;
                    t=res[threadCnt % threadNo].getJobNames();
                    t.push_back(job.getJobName());
                    res[threadCnt % threadNo].setJobNames(t);
                    //edf.getJobNames().push_back(job.getJobName());
                    res[threadCnt % threadNo].setDeadline(res[threadCnt % threadNo].getDeadline()+job.getDuration());
                    cout<<"hi"<<endl;
                }
            }
            threadCnt++;
        }
        return res;
    }

    void displayScheduleJobsForEdf(map<int, EDF> threads){
        for(auto i : threads){
            cout<<"Thread: "<<i.first<<" - ";
            for(string s: i.second.getJobNames()){
                cout<<s<<", ";
            }cout<<endl;
        }cout<<endl;
    }

    void displayScheduleJobs(map<int, vector<string>> threads){
        for(auto i : threads){
            cout<<"Thread: "<<i.first<<" - ";
            for(string s: i.second){
                cout<<s<<", ";
            }cout<<endl;
        }cout<<endl;
    }

    void shortestJobFirst(int threadNo, vector<Job> job){
        vector<Job> jobs = job;

        sort(jobs.begin(), jobs.end(), cmp1);

        map<int, vector<string>> threads = assignThreadsToJobs(threadNo, jobs);

        displayScheduleJobs(threads);
    }

    void firstComeFirstServe(int threadNo, vector<Job> job){
        map<int, vector<string>> threads = assignThreadsToJobs(threadNo, job);

        displayScheduleJobs(threads);
    }

    void fixedPriorityScheduling(int threadNo, vector<Job> job){
        vector<Job> jobs = job;

        sort(jobs.begin(), jobs.end(), cmp2);

        map<int, vector<string>> threads = assignThreadsToJobs(threadNo, jobs);

        displayScheduleJobs(threads);
    }

    void earliestDeadlineFirst(int threadNo, vector<Job> job){
        vector<Job> jobs = job;

        sort(jobs.begin(), jobs.end(), cmp3);

        map<int, EDF> threads = assignThreadsToJobsForEdf(threadNo, jobs);

        displayScheduleJobsForEdf(threads);
    }
};



int main(){
    JobScheduler js;
    Job j1("J1", 10, 0, 10, 0);
    Job j2("J2", 20, 0, 40, 1);
    Job j3("J3", 15, 2, 40, 0);
    Job j4("J4", 30, 1, 40, 2);
    Job j5("J5", 10, 2, 30, 2);
    vector<Job> jobs;
    jobs.push_back(j1);
    jobs.push_back(j2);
    jobs.push_back(j3);
    jobs.push_back(j4);
    jobs.push_back(j5);

    js.shortestJobFirst(2, jobs);
    js.firstComeFirstServe(2, jobs);
    js.fixedPriorityScheduling(2, jobs);
    js.earliestDeadlineFirst(2, jobs);
    return 0;
}