# syclinfo - a simple tool to query SYCL devices and platforms

`syclinfo` queries all SYCL devices and platforms for all available information. In that sense, it is the SYCL equivalent to the well-known `clinfo` for OpenCL. Like `clinfo`, `syclinfo` is particularly useful to quickly check the functionality of SYCL installations and devices.

## Installing
`syclinfo` has been tested with the SYCU and ComputeCpp SYCL implementations. For SYCU, the necessary compilation steps are:
```
$ mkdir <build directory>; cd <build directory>
$ cmake -DCMAKE_CXX_COMPILER=sycucc <source directory>
$ make
```
For ComputeCpp, the process is similar but slightly more involved. Apart from setting `-DCMAKE_CXX_COMPILER=compute++`, the include directories must be pointed to the ComputeCpp include directories and `libComputeCpp.so` must be linked against.
