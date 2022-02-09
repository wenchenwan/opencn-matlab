# 1.Installation :
This installation procedure is required by any developers interested either in modifying the provided trajectory planning algorithms implemented with Matlab or in generating custom C/C++ code.

**Note** : To use directly the release of openCN please have a look at the [User guide](https://mecatronyx.gitlab.io/opencnc/opencn/user_guide.html#)

## Minimum requirements :

- A linux environment
- A basic installation of Matlab
- The Matlab toolboxes :
	- Matlab coder
	- Embedded Coder
  
## External libraries

1. Open a terminal.
2. Install the libraries for the linear programming solver COIN-OR LP (CLP). 

```shell
$ sudo apt install coinor-libclp1 coinor-clp coinor-libclp-dev 
```

3. Install the libraries of the GSL - GNU Scientific Library

```shell
$ sudo apt install libgsl23 libgsl-dev
```

## Mex files :

1. Open a terminal and clone the opencn repository 

```shell
$ git clone git@gitlab.com:mecatronyx/opencnc/opencn.git
$ git submodule init
$ git submodule update
```

2. Open Matlab at the root of the opencn folder and run the following commands in the Matlab prompt

```shell
>> cd opencn/agency/usr/matlab/common
>> run startup.m
>> run generate_mex.m
>> run mex_queue.m
```

3. Run the provided basic example to see if everything has been correctly installed

```shell
>> run basic_example.m
```

# 2. Complements
- C/C++ code generation has been tested and validated using the release 5.3 of Matlab Coder
- The code has been tested with Matlab 2021b
- The path planning algorithms are described in details in [chapter 5](https://mecatronyx.gitlab.io/opencnc/opencn/CNC_Path_Planning_Algorithms/CNC_Path_Planning_Algorithms.html) of the documentation.

- A guide for the utilisation of the Matlab coder in *opencn-matlab* is provided in [chapter 4.3](https://mecatronyx.gitlab.io/opencnc/opencn/components/feedopt.html) of the documentation.
