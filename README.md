# Installation :
**************
This installation procedure is required by any developers interested either in modifying the provided trajectory planning algorithms implemented with Matlab or in the customization of the generated C/C++ code.

**Note** : To use directly a functional application of opencn please look at the [User guide] (https://mecatronyx.gitlab.io/opencnc/opencn/user_guide.html#)

## Minimum requirements :

- A linux environment
- A basic installation of Matlab
- The Matlab toolboxes :
	- Matlab coder
	- Embedded Coder
  
## External libraries

1. Open a terminal.
2. Install the libraries of the linear programming solver COIN-OR LP (CLP). 

```shell
$ sudo apt install coinor-clp coinor-libclp-dev 
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

2. Open Maltab at the root of the opencn folder and run the following commands in the Matlab prompt

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