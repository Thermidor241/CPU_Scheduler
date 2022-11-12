#include<iostream>
#include<vector>

using namespace std;
double total_time = 0; //Total amount of time passed
double total_wait = 0.0;//wait times added up
double avg_wait;// Average wait time
double total_response;
double avg_turn;//Average turnaround time
double total_turn;//turnaround times added up
double CPU_U; //CPU Utilization
double avg_res; //Average response time
int idle_time = 0;
class process{
 private:
  int response; //response time of current program
  vector<int> IO_list; //list of io times
  vector<int> burst_list;//list of cpu burst times
  int burst_time; // The starting burst time
  int io_time;//The starting io time
  int cur_burst; //however much time is left in burst
  int cur_io;  //time left in io
  bool in_burst = false; //whether or not the process is in burst
  bool in_io = false; // whether or not the process is in io
  string procc_num;//The process number
  int wait_time = 0; //amount of time the process waited
  int final_turn = 0;//total turnaround
  int turn_time = 0;// amount of time the process was there
  bool done = false;// If the process is done
  bool started = false;//If the process has been read
 public:
     //setters
     void set_response(int res){
         response = res;
     }
     void set_IO_list(vector<int> il){
         IO_list = il;
     }
     void set_burst_list(vector<int> bl){
         burst_list = bl;
     }

     void set_done(){
     done = true;}

     void set_proc_name(string Pnum){
     procc_num = Pnum;}

     void set_started(){
     started = true;}

     void switch_stat(){              //Switches status of the process
        if (in_burst == true){
            in_burst = false;
            in_io = true;
        }
        else if(in_io == true){
            in_io = false;
        }
        else{
            in_burst = true;
        }}

     //Getters
     int get_response()
     {
        return response;}

    string get_Pnum()
    {
    return procc_num;}

     int get_burst_time(){
         burst_time = burst_list.front();
         cur_burst = burst_time;
     return burst_time;}

     int get_curburst(){
     return cur_burst;
     }

     int dec_curburst(){
     cur_burst--;
     return cur_burst;}


     int get_io_time(){
         io_time = IO_list.front();
         cur_io = io_time;
     return io_time;}

     int inc_turn(){
       turn_time++;
       return turn_time;}

     int get_cur_io(){
     return cur_io;
     }


     int dec_cur_io(){
     cur_io--;
     return cur_io;}

     bool get_io_stat(){// Check if process is in io
     return in_io;}

     bool get_b_stat(){
     return in_burst;}

     bool get_done(){  //Make sure process finished
     return done;}

     bool get_start(){  //Make sure process has started
     return started;}

     int get_turn(){  //Get turnaround time
     return turn_time;}

     vector<int> get_b_list(){ //Get burst list
     return burst_list;}

      vector<int> get_io_list(){ //Get io list
     return IO_list;}

     int get_wait(){
     return wait_time;}

     void inc_wait(){
     wait_time++;}

     int get_final_turn(){
     final_turn = wait_time + turn_time;
     return final_turn;}
      void erase_burst(){
            burst_list.erase(burst_list.begin());
            get_burst_time();
            }
      void erase_io(){
            IO_list.erase(IO_list.begin());
            get_io_time();
            }
};

//Statistic function temporary

void temp_statistic(vector<process> Proc, vector<process> Ready, int time){

    cout << "Here are the stats so far!\n";
    cout << "Current execution time: "<< time << endl;
    if (Ready.size() == 0){
            cout << "The ready queue is empty \n";}
    else{
     cout << "Current process bursting :\n" << Ready[0].get_Pnum() << "  Burst time left :" << Ready[0].get_curburst() << endl;
  if (Ready.size() > 0){
  cout << "----------Ready Queue-----------" << endl;
  for(int j = 0; j < Ready.size(); j++){
  cout <<" "<< Ready[j].get_Pnum()<< " time: " << Ready[j].get_curburst() << endl;}
  }
    }
    //iterate through processes for io time
    cout << "List of processes in io"<< endl;
    cout <<"----------------------------"<<endl;
    for(int i = 0; i < Proc.size(); i++){
        if (Proc[i].get_io_stat() == true){
            cout << Proc[i].get_Pnum() << " IO time left: "<< Proc[i].get_cur_io() << endl;
        }
    }
    cout << "Finished processes "<< endl;
    cout <<"----------------------"<<endl;
  //iterate to find finished processes
  for(int i = 0;i < Proc.size();i++){
    if (Proc[i].get_done()== true){
        cout << Proc[i].get_Pnum() <<endl;

    }
  }

}

//Final Calculation function
void Final_Stat(vector<process>P_list, int clock){
  total_time = clock;
  cout << "-----------------------"<<endl;
  cout <<"|--Tw--|--Ttr--|--Tr--|"<<endl;
    for(int i = 0; i < P_list.size(); i++){
        cout <<"| "<<P_list[i].get_wait()<<" | "<<P_list[i].get_turn() + P_list[i].get_wait()<<" | "<<P_list[i].get_response()<< " |" <<endl;
        total_turn += P_list[i].get_final_turn();
        total_wait += P_list[i].get_wait();
        total_response += P_list[i].get_response();

    }
    avg_wait = (total_wait/P_list.size());
    avg_turn = (total_turn/P_list.size());
    avg_res  =  (total_response/P_list.size());
    CPU_U = ((total_time - idle_time)/total_time) * 100;

    cout << "Average wait |"<< avg_wait<<endl;
    cout << "Average turnaround |"<<avg_turn<<endl;
    cout << "Average response time |"<<avg_res<<endl;
    cout << "total time |" << total_time<< endl;
    cout << "CPU Utilization |" <<CPU_U << "%" <<endl;

  }

//FCFS Function

 void FCFS(vector<process> P_list){
     vector<process> R_Q; //Ready queue
     int num_done = 0; //Number of finished processes
     int clock = 0; //timer for scheduler


     //Copy the process list to the ready queue
    R_Q = P_list;

    //While not all of the processes are done

    while (num_done < P_list.size()){  //update to less than size
        //cout << clock << endl;
     //Look at ready queue
    if (R_Q.empty()){
        idle_time++;
    }
    else{
      for(int i = 0; i < P_list.size(); i++){
        if(P_list[i].get_Pnum() == R_Q[0].get_Pnum()){//If the process in the queue hasn't started then  set start bool to true and
        if (P_list[i].get_start() == false){
        P_list[i].set_started(); // Set the response time to the current time.
        P_list[i].set_response(clock);
        }

        if (P_list[i].get_b_stat() == false){
            P_list[i].switch_stat();} //switch burst status to true
        }
      }
    }


     //Look at process list and count
      for(int i = 0; i < P_list.size(); i++) //Iterating in process list
  {
    if (P_list[i].get_done() == false){  //If the process isnt done

        if(P_list[i].get_b_stat() == true)
        {      //If the process is currently bursting

            P_list[i].dec_curburst();       //Decrement the current burst time
            P_list[i].inc_turn();           //increment turnaround time
            if (P_list[i].get_curburst() == 0)
            { //If the burst time is zero
                R_Q.erase(R_Q.begin());         //Erase process from queue
                P_list[i].erase_burst();        //Erase burst time from list
                if (P_list[i].get_b_list().size() == 0){     //If the burst list is empty
                    P_list[i].set_done();  //Process is done
                    num_done++;
                }
                else
                {
                    P_list[i].switch_stat()  ;     //switch the io status to true
                    //cout << "hello "<< endl;

                }
                   temp_statistic(P_list, R_Q, clock);
            }
        }
        else if(P_list[i].get_io_stat() == true)
        {
            P_list[i].dec_cur_io();
            P_list[i].inc_turn();
            if (P_list[i].get_cur_io() == 0)
            {
                /*set io stat to false */
                P_list[i].switch_stat();
                //delete front io
                P_list[i].erase_io();
                R_Q.push_back(P_list[i]);
            }
        }
        else if ((P_list[i].get_io_stat() == false) && (P_list[i].get_b_stat() == false)){ //Not in io  or burst means that it is in the ready queue
            P_list[i].inc_wait();
            //cout << "No"<< endl; //Add to wait time
        }
    }
  }

        clock++;}//increment clock
        Final_Stat(P_list,clock);
 }


int main()
{
 vector <process> Proc_list;
 process P1,P2,P3,P4,P5,P6,P7,P8;
 //Setting up P1
 P1.set_burst_list({5,3,5,4,6,4,3,4});
 P1.set_IO_list({27,31,43,18,22,26,24});
 P1.get_burst_time();
 P1.get_io_time();
 P1.set_proc_name("P1");
 Proc_list.push_back(P1);


 //Setting up P2
 P2.set_burst_list({4,5,7,12,9,4,9,7,8});
 P2.set_IO_list({48,44,42,37,76,41,31,43});
 P2.get_burst_time();
 P2.get_io_time();
 P2.set_proc_name("P2");
 Proc_list.push_back(P2);

 //Setting up P3
 P3.set_burst_list({8,12,18,14,4,15,14,5,6});
 P3.set_IO_list({33,41,65,21,61,18,26,31});
 P3.get_burst_time();
 P3.get_io_time();
 P3.set_proc_name("P3");
 Proc_list.push_back(P3);

  //Setting up P4
 P4.set_burst_list({3,4,5,3,4,5,6,5,3});
 P4.set_IO_list({35,41,45,51,61,54,82,77});
 P4.get_burst_time();
 P4.get_io_time();
 P4.set_proc_name("P4");
 Proc_list.push_back(P4);

   //Setting up P5
 P5.set_burst_list({16,17,5,16,7,13,11,6,3,4});
 P5.set_IO_list({24,21,36,26,31,28,21,13,11});
 P5.get_burst_time();
 P5.get_io_time();
 P5.set_proc_name("P5");
 Proc_list.push_back(P5);

   //Setting up P6
 P6.set_burst_list({11,4,5,6,7,9,12,15,8});
 P6.set_IO_list({22,8,10,12,14,18,24,30});
 P6.get_burst_time();
 P6.get_io_time();
 P6.set_proc_name("P6");
 Proc_list.push_back(P6);

   //Setting up P7
 P7.set_burst_list({14,17,11,15,4,7,16,10});
 P7.set_IO_list({46,41,42,21,32,19,33});
 P7.get_burst_time();
 P7.get_io_time();
 P7.set_proc_name("P7");
 Proc_list.push_back(P7);

   //Setting up P8
 P8.set_burst_list({4,5,6,14,16,6});
 P8.set_IO_list({14,33,51,73,87});
 P8.get_burst_time();
 P8.get_io_time();
 P8.set_proc_name("P8");
 Proc_list.push_back(P8);






FCFS(Proc_list);
return 0;
}
