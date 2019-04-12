#include <Eigen/Dense>
#include "../ezh5.h"
#include <complex>
#include <vector>
using namespace std;
const std::complex<double> CONE(0,1);
int main(){
  {
    //put inside brackets so the deconstructor is called
    ezh5::File f ("universe.h5", H5F_ACC_TRUNC);  // create a file object called f

    //set basic data types
    f["i"]=1;
    f["d"]=5.2;
    f["c"]=1.0+5.1*CONE;
    f["ch"]='t';

    //vector support
    std::vector<double> v(10);
    double x=0.0;
    for(auto &vi : v){
      vi=x;
      x+=2.5;
    }
    f["v"]=v;

    //Eigen support
    Eigen::MatrixXd ev(2,5);
    ev<<1,2,3,4,5,6,7,8,9,10;
    std::cerr<<"ev:\n"<<ev<<std::endl;
    f["ev"]=ev;
    Eigen::VectorXcd evc(10);
    evc.setRandom();
    f["evc"]=evc;
    Eigen::MatrixXd mxd(5,5);
    mxd.setRandom();
    f["mxd"]=mxd;
    
    Eigen::MatrixXcd mxcd(5,5);
    mxcd.setRandom();
    f["mxcd"]=mxcd;
    
    // append support
    //std::cerr<<"pre test"<<std::endl;
    auto toKeep=f["test"];
    toKeep.append(1);
    //std::cerr<<"appended"<<std::endl;
    toKeep << 2;
    toKeep << 3;
    toKeep << 4;
    toKeep <<5 <<5;
    
    //append vectors
    std::vector<int> v1 = {1,2,3};
    auto vNode = f["vtest"];
    vNode.append(v1);
    std::vector<int> v2 = {4,5,6};
    std::vector<int> v3 = {7,8,9};
    vNode << v2 << v3;
    vNode << v1;

    //append eigen vectors
    Eigen::VectorXd eigv(4);
    eigv << 1,2,3,4;
    auto eNode = f["evtest"];
    eNode.append(eigv).append(eigv);
    eNode << eigv;
    eNode << eigv;

    //allow overwriting of data
    for(int i=0;i<10000;i++)
      f["abc"+to_string(i)]=1.0;

    for(int i=0;i<10000;i++)
      f["abc"+to_string(i)]=2.0;

  }
  std::cerr<<"written"<<std::endl;

  {
    std::cerr<<"Reading in"<<std::endl;

    ezh5::File g ("universe.h5", H5F_ACC_RDONLY);  // create a file object called f
    //read in data we wrote above
    int i;
    g["i"] >> i;
    double d;
    g["d"] >> d;
    std::complex<double> c;
    g["c"] >> c;
    char name;
    g["ch"] >> name;
    std::vector<double> v;
    g["v"] >> v;
    Eigen::MatrixXd ev;
    g["ev"] >> ev;
    Eigen::VectorXcd evc;
    g["evc"] >> evc;
    Eigen::MatrixXd mxd;
    g["mxd"] >> mxd;
    Eigen::MatrixXcd mxcd;
    g["mxcd"] >> mxcd;

    std::vector<int> test;
    g["test"] >> test;

    Eigen::Matrix<int,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> vtest;
    g["vtest"] >> vtest;

    Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> evtest;
    g["evtest"] >> evtest;

    std::cout<<"i: " <<i<<std::endl;
    std::cout<<"d: " <<d<<std::endl;
    std::cout<<"c: " <<c<<std::endl;
    std::cout<<"ch: "<<name<<std::endl;
    std::cout<<"v: ";
    for(auto x: v)
      std::cout<<x<<" ";
    std::cout<<std::endl;
    std::cout<<"ev:\n"  <<ev<<std::endl;  
    std::cout<<"evc: "  <<evc.transpose()<<std::endl;
    std::cout<<"mxd:\n" <<mxd<<std::endl;
    std::cout<<"mxcd:\n"<<mxcd<<std::endl;
    g["mxd"] >> mxcd;
    std::cout<<"mxcd:\n"  <<mxcd<<std::endl;
    std::cout<<std::endl<<"test: ";
    for(auto x: test)
      std::cout<<x<<" ";
    std::cout<<std::endl;

    std::cout<<std::endl<<"vtest:\n"<<vtest<<std::endl;
    std::cout<<std::endl<<"evtest:\n"<<evtest<<std::endl;
  }
    return 0;
}
