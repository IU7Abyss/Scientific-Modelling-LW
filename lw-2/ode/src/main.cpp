#include <iostream>
using std::cout;

#include <map>
using std::map;

#include <string>
using std::string;

#include <thread>
using std::thread;

#include <vector>
using std::vector;

#include "Model.h"
#include "datarw/datarw.h"


void
task1 (double t0,
       double t_end,
       double t_delta,
       double I0,
       double Uc_0,
       double Ck,
       double Lk,
       double Rk,
       double l_e,
       double R,
       double Tw,
       const std::map< double, std::vector<double> > &map_I_T0_n,
       const std::map<double, double> &map_T_Sigma,
       const std::string &filename)
{
    Model m1 = model_runge(t0, t_end, t_delta, I0, Uc_0, Ck, Lk, Rk, l_e, R, Tw, map_I_T0_n, map_T_Sigma);
    cout << "Runge 4 computaton compelted." << '\n';
    makeCSV(filename, "t,I,Uc,Rp", m1);
}

void
task2 (double t0,
       double t_end,
       double t_delta,
       double I0,
       double Uc_0,
       double Ck,
       double Lk,
       double Rk,
       double l_e,
       double R,
       double Tw,
       const std::map< double, std::vector<double> > &map_I_T0_n,
       const std::map<double, double> &map_T_Sigma,
       const std::string &filename)
{
    Model m2 = model_trapezium(t0, t_end, t_delta, I0, Uc_0, Ck, Lk, Rk, l_e, R, Tw, map_I_T0_n, map_T_Sigma);
    cout << "Trapezium computaton compelted." << '\n';
    makeCSV(filename, "t,I,Uc,Rp", m2);
}

int main(int argc, const char * argv[])
{
    if (argc < 6) {
        cout << "Error: Something wrong. input data, table1, table2, runge_out, trapezium_out" << '\n';
        return 1;
    }
    
    cout << "Loading the initial values from '" << argv[1] << "'..." << '\n';
    map<string, double> inputdata = read_inputdata(argv[1]);
    cout << "Loading '" << argv[1] << "' completed." << '\n';
    
    cout << "Loading table '| I | T0 | n |' from '" << argv[2] << "'..." << '\n';
    map< double, vector<double> > I_T0_n = read_I_T0_n(argv[2]);
    cout << "Loading '" << argv[2] << "' completed." << '\n';
    
    cout << "Loading table '| T | Sigma |' from '" << argv[3] << "'..." << '\n';
    map<double, double> T_Sigma = read_T_Sigma(argv[3]);
    cout << "Loading '" << argv[3] << "' completed." << '\n';
    
    double t0      = inputdata["t0"];
    double t_end   = inputdata["t_end"];
    double t_delta = inputdata["t_delta"];
    double I0      = inputdata["I0"];
    double Uc_0    = inputdata["Uc_0"];
    double Ck      = inputdata["Ck"];
    double Lk      = inputdata["Lk"];
    double Rk      = inputdata["Rk"];
    double l_e     = inputdata["l_e"];
    double Tw      = inputdata["Tw"];
    double R       = inputdata["R"];
    string runge4_out    = argv[4];
    string trapezium_out = argv[5];
    
    cout << "Computation..." << '\n';
    
    auto start_time = std::chrono::high_resolution_clock::now();
    
    thread t1(task1, t0, t_end, t_delta, I0, Uc_0, Ck, Lk, Rk, l_e, R, Tw, I_T0_n, T_Sigma, runge4_out);
    thread t2(task2, t0, t_end, t_delta, I0, Uc_0, Ck, Lk, Rk, l_e, R, Tw, I_T0_n, T_Sigma, trapezium_out);
    
    t1.join();
    t2.join();
    
    auto end_time = std::chrono::high_resolution_clock::now();
    
    cout << "Computation completed." << '\n';
    cout << "Time estimated (with writing data to files):" << '\n'
         << "\t in seconds:\t  " << std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count() << " s" << '\n'
         << "\t in milliseconds: " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << " ms" << '\n'
         << "\t in microseconds: " << std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count() << " µs" <<'\n';
    
    return 0;
}
