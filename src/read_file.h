#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ProcessParams
{
public:
	ProcessParams(int c, int d, int p) { 
		creation_time = c;
		duration = d;
		priority = p;
	}

	friend ostream &operator<<(ostream& os, const ProcessParams& p) {
		os << "Creation time = " << p.creation_time << " duration = " << p.duration << " priority = " << p.priority << endl;
		return os;
	}

    unsigned int get_creation_time() const {
        return creation_time;
    }

    unsigned int get_duration() const {
        return duration;
    }

    unsigned int get_priority() const {
        return priority;
    }


private:
	unsigned int creation_time;
	unsigned int duration; //seconds
	unsigned int priority;
};

class File
{

public:
	File(char* file_name) {
		myfile.open(file_name);
		if (!myfile.is_open()) {
			cout << "Erro ao abrir o arquivo!\n";
		}
	}
	
	void read_file() {
	
		int a, b, c;
		
		if (!myfile.is_open()) {
			cout << "Arquivo não está aberto!" << endl;
		}
		
		while (myfile >> a >> b >> c) {
			ProcessParams *p = new ProcessParams(abs(a), abs(b), abs(c));
			processes.push_back(p);
		}

		// cout << "Quantidade de processos lidos do arquivo: " << processes.size() << endl;
	}

	void print_processes_params() {
		vector<ProcessParams *>::iterator iter = processes.begin();

		for(; iter < processes.end(); iter++) {
			ProcessParams *p = *iter;
			cout << *p;
		}
	}

    vector<ProcessParams *> get_processes_params() {
        return processes;
    }

	~File() {
		for(size_t i = 0; i < processes.size() ; i++) {
			ProcessParams *p = processes[i];
			delete p;
		}
	}

private:
	ifstream myfile; 
	vector<ProcessParams *> processes;
};
