#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <queue>


using namespace std;

//this class holds the information for a given job
class Job
{
public:
  char name;
  int startTime;
  int duration;
  int remaining;
  int waiting;
  int place;

  //constructor
  Job(char n, int s, int d, int p)
  {
    name = n;
    startTime = s;
    duration = d;
    remaining = d;
    waiting = 0;
    place = p;
  }

  //sets the intial remaining time and the intial waiting time to 0
  void setRemaining()
  {
    remaining = duration;
    waiting = 0;
  }
  
  //calculates the highest response time ratio
  double calculateRatio()
  {
    return ((waiting + duration) / duration);
  }
};

vector<Job> jobs;

//serves whichever jobs arrives first
void FCFS()
{
  cout << "FCFS" << endl << endl;
  
  for(int x=0; x<jobs.size(); x++)
    {
      cout << jobs.at(x).name << " ";
      jobs.at(x).setRemaining();
    }
  cout << endl;
  //goes through all jobs and runs them starting with the one that arrives first 
  for(int x=0; x<jobs.size(); x++)
    {
      for(int y=0; y<jobs.at(x).duration; y++)
	{
	  for(int y=0; y<jobs.at(x).place; y++)
	    cout << "  ";
	  cout << "X" << endl;
	}
    }
  cout << endl << endl;
}

//serves each job in a circle with one unit each
void RR()
{  
  queue<Job> ready, j;

  int timeLeft = 0;
  int time = 0;
  cout << "RR" << endl << endl;
  for(int x=0; x<jobs.size(); x++)
    {
      cout << jobs.at(x).name << " ";
      timeLeft += jobs.at(x).duration;
      jobs.at(x).setRemaining();
      j.push(jobs.at(x));
    }
  cout << endl;
  //puts jobs ready to run in the ready queue
  while(j.front().startTime <= time && !j.empty())
    {
      ready.push(j.front());
      j.pop();
    }

  while(timeLeft > 0)
    {
      if(!ready.empty())
	{
	  for(int y=0; y<ready.front().place; y++)
	    cout << "  ";
	  cout << "X" << endl;
	  timeLeft--;
	  time++;
	  ready.front().remaining--;
	  //puts jobs ready to run in the ready queue
	  while(j.front().startTime <= time && !j.empty())
	    {
	      ready.push(j.front());
	      j.pop();
	    }
	  //puts the jobs that just ran in the ready queue
	  if(ready.front().remaining > 0)
	    ready.push(ready.front());
	  ready.pop();
	}
    }
  cout << endl << endl;
}

//serves the shortest process next
void SPN()
{
  cout << "SPN" << endl << endl;
  
  int timeLeft = 0;
  int time = 0;
  for(int x=0; x<jobs.size(); x++)
    {
      cout << jobs.at(x).name << " ";
      timeLeft += jobs.at(x).duration;
      jobs.at(x).setRemaining();
    }
  cout << endl;
  int min = -1;
  //while there is still time left continue to run choosing the shortest process to run 
  while(timeLeft > 0)
    {
      for(int x=0; x<jobs.size(); x++)
	{  
	  if(jobs.at(x).remaining > 0 && jobs.at(x).startTime <= time)
	    {
	      min = x;
	      break;
	    }
	}
      for(int x=0; x<jobs.size(); x++)
	{
	  if(jobs.at(x).duration < jobs.at(min).duration && jobs.at(x).startTime <= time && jobs.at(x).remaining > 0)
	      min = x;
	}
      //runs an entire job
      while(jobs.at(min).remaining > 0)
	{
	  for(int y=0; y<min; y++)
	    cout << "  ";
	   cout << "X" << endl;
	   time++;
	   timeLeft--;
	   jobs.at(min).remaining--;  
	}
    }
  cout << endl << endl;
}

//serves the process with the shortest remaining time
void SRT()
{
  cout << "SRT" << endl << endl;

    int timeLeft = 0;
  int time = 0;
  for(int x=0; x<jobs.size(); x++)
    {
      cout << jobs.at(x).name << " ";
      timeLeft += jobs.at(x).duration;
      jobs.at(x).setRemaining();
    }
  cout << endl;
  int min = -1;
  //while there is time left choosing the job with the shortest remaining time preempting if a new job arrives with shorter time
  while(timeLeft > 0)
    {
      for(int x=0; x<jobs.size(); x++)
	{  
	  if(jobs.at(x).remaining > 0 && jobs.at(x).startTime <= time)
	    {
	      min = x;
	      break;
	    }
	}
      
      //finds the new shortest remaining time process
      for(int x=0; x<jobs.size(); x++)
	{
	  if(jobs.at(x).remaining < jobs.at(min).remaining && jobs.at(x).startTime <= time && jobs.at(x).remaining > 0)
	      min = x;
	}
      for(int y=0; y<min; y++)
	cout << "  ";
      cout << "X" << endl;
      time++;
      timeLeft--;
      jobs.at(min).remaining--;  
    }
  cout << endl << endl;
}

//highest response ratio next
void HRRN()
{
  cout << "HRRN" << endl << endl;

  int timeLeft = 0;
  int time = 0;
  for(int x=0; x<jobs.size(); x++)
    {
      cout << jobs.at(x).name << " ";
      timeLeft += jobs.at(x).duration;
      jobs.at(x).setRemaining();
    }
  cout << endl;
  int max = -1;
  //while there is time left, check which process has the highest response time ratio and run that process next
  while(timeLeft > 0)
    {
      for(int x=0; x<jobs.size(); x++)
	{  
	  if(jobs.at(x).remaining > 0 && jobs.at(x).startTime <= time)
	    {
	      max = x;
	      break;
	    }
	}
      for(int x=0; x<jobs.size(); x++)
	{
	  if(jobs.at(x).calculateRatio() > jobs.at(max).calculateRatio() && jobs.at(x).startTime <= time && jobs.at(x).remaining > 0)
	      max = x;
	}
      //runs entire job
      while(jobs.at(max).remaining > 0)
	{
	  for(int y=0; y<max; y++)
	    cout << "  ";
	   cout << "X" << endl;
	   time++;
	   timeLeft--;
	   jobs.at(max).remaining--;
	   for(int x=0; x<jobs.size(); x++)
	     {
	       if(jobs.at(x).startTime <= time && jobs.at(x).remaining > 0)
		 jobs.at(x).waiting++;
	     }  
	}
    }
  cout << endl << endl;
}

//creates 3 queues and serves customers from these queues
void FB()
{
  cout << "FB" << endl << endl;
  
  int timeLeft = 0;
  int time = 0;
  queue<Job> q1, q2, q3, j;
  for(int x=0; x<jobs.size(); x++)
    {
      cout << jobs.at(x).name << " ";
      timeLeft += jobs.at(x).duration;
      jobs.at(x).setRemaining();
      j.push(jobs.at(x));
    }
  cout << endl;

  Job current('0', 0, 0, 0);
  int qPlace;
  while(timeLeft > 0)
    {
      //puts new jobs in queue
      while(j.front().startTime <= time && !j.empty())
	{
	  q1.push(j.front());
	  j.pop();
	}

      //if the job ran last still has time left place back in queue
      if(current.remaining > 0)
	{
	  //if at least one queue has something in it, move current to the next queue
	  if(!q1.empty() || !q2.empty() || !q3.empty())
	    {
	      qPlace++;
	    }
	  switch(qPlace)
	    {
	    case 1: q1.push(current); break;
	    case 2: q2.push(current); break;
	    default: q3.push(current); break;
	    }
	}
      
      //if there is soemthing in q1, current is the first job
      if(!q1.empty())
	{
	  current = q1.front();
	  qPlace = 1;
	  q1.pop();
	}

      //if there is nothing in q1 and something in q2, current is first job 
      else if(q1.empty() && !q2.empty())
	{
	  current = q2.front();
	  qPlace = 2;
	  q2.pop();
	}

      //if there is nothing in q1, q2, current is the first job
      else if(q1.empty() && q2.empty() && !q3.empty())
	{
	  current = q3.front();
	  qPlace = 3;
	  q3.pop();
	}

      for(int y=0; y<current.place; y++)
      	cout << "  ";
      cout << "X" << endl;
      time++;
      timeLeft--;
      current.remaining--;

      
    }


}

//runs all six algorithms
void ALL()
{
  cout << "ALL" << endl << endl << endl;
  FCFS();
  RR();
  SPN();
  SRT();
  HRRN();
  FB();
}

//reads from the input file
void readFile(string filename)
{
  char name;
  int start, duration, count = 0;
  string dump;
  ifstream inFile;
  inFile.open(filename.c_str());

  if(!inFile)
    {
      cerr << "Error: cannot open file " << filename << endl;
      exit(1);
    }

  while(inFile >> name >> start >> duration)
    {
      getline(inFile, dump);
      Job j(name, start, duration, count);
      jobs.push_back(j);
      count++;
    }

  inFile.close();
}

int main(int argc, char* argv[])
{
  readFile(argv[1]);

  string task = argv[2];
  if(task.compare("FCFS") == 0)
     FCFS();
  else if(task.compare("RR") == 0)
     RR();
  else if(task.compare("SPN") == 0)
     SPN();
  else if(task.compare("SRT") == 0)
     SRT();
  else if(task.compare("HRRN") == 0)
    HRRN();
  else if(task.compare("FB") == 0)
    FB();
  else if(task.compare("ALL") == 0)
    ALL();
  else
    cout << "Invalid choice of algorithms" << endl;





  return 0;
}
