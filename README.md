# ezh5-eigen: C++ interface for HDF5 with Eigen3 support
Theoretically simple and straightforward to use C++11 to HDF5 library.  
Based off of [mileschen360/ezh5](https://github.com/mileschen360/ezh5/)

## Features
* Reading/writing of basic data types (`int`,`double`,`std::complex<T>`,`std::string`)
* Reading/writing of Eigen vectors and matrices (e.g. `Eigen::VectorXd`, `Eigen::Matrix Xcd`)
* Appending of basic data types into vectors
* Appending of Eigen vectors into a "matrix"

## Interface
```c++
using namespace ezh5;
{
  File f ("universe.h5", H5F_ACC_TRUNC);  // create a file object called f
  //------------------------------------------------------------------------------
  // Set basic+Eigen datatypes 
  //------------------------------------------------------------------------------
  f["step"]=1;

  //vector support
  std::vector<double> v(4) = {1.5,2.5,3.5,4.5};
  f["myVector"]=v;

  //Eigen support
  Eigen::VectorXcd evc(10);
  evc.setRandom();
  f["evc"]=evc;

  Eigen::MatrixXd ev(2,5);
  ev<<1,2,3,4,5,6,7,8,9,10;
  f["ev"]=ev;
  //------------------------------------------------------------------------------
  // Append basic+Eigen datatypes
  //------------------------------------------------------------------------------
  
  //append by keeping the node around
  auto toKeep=f["vecOfInts"];
  toKeep.append(1);
  toKeep.append(2);
  toKeep.append(3);
  //alternative interface
  toKeep << 4;
  toKeep << 5 << 6;

  //append eigen vectors
  Eigen::VectorXd eigv(4);
  eigv << 1,2,3,4;
  auto eNode = f["evAppend"];
  eNode.append(eigv).append(eigv);
  eNode << eigv;
  eNode << eigv;

  //destructor closes file
}
{
  File g ("universe.h5", H5F_ACC_RDONLY);
  //------------------------------------------------------------------------------
  // Straightforward reading interface
  //------------------------------------------------------------------------------
  int step;
  g["step"] >> step;
  std::vector<double> v;
  g["v"] >> v;
  Eigen::MatrixXd ev;
  g["ev"] >> ev;
  Eigen::VectorXcd evc;
  g["evc"] >> evc;

  std::vector<int> test;
  g["vecOfInts"] >> test; //automatic vector
  
  //append vectors become matrices
  Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor> evMatrix;
  g["evAppend"] >> evMatrix;
}

```

## Installation Usage
Simply compile `ezh5.cc` along with your codebase and include `ezh5.h` in your files and you're good to go!  

Requires both [HDF5](https://www.hdfgroup.org/downloads/hdf5) and [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) to be installed

## Installing HDF5
### Mac
I suggest using [homebrew](https://brew.sh/) (preferred) 
```
brew install hdf5
```
or [MacPorts](https://www.macports.org/)
```
port install hdf5
```
### Linux
* Ubuntu: `apt-get install libhdf5-serial-dev hdf5-tools`
* Fedora: `dnf install hdf5-devel`

## Contributors
- [Ryan Levy](https://github.com/ryanlevy/) - major modifications and appending support
- [Xiongjie Yu](https://github.com/xyu40) - Original port and initial Eigen support
- [M. Chen](https://github.com/mileschen360) - Original open source base code and style of [ezh5](https://github.com/mileschen360/ezh5/)
## TODO
* Append Eigen Matrices (requires a bit of work when extracting the resulting matrix)
* Better documentation +/- Doxygen


