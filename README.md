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
```

3. Run the provided basic example to see if everything has been correctly installed

```shell
>> run basic_example.m
```

## C/C++ files :

1. Open Matlab at the root of the opencn folder. 

The folder generate contains all the files envolves in code generation. 
The file generate/generate.c can be modified to selecte which architecture will be used during the code generation. 
Run the following commands in the Matlab prompt to start the code generation. 

```shell
>> run generate_c.m
```
**Note** : You can change the configuration of generated code in the file generate/generate_c_config.m

## Files organisation :

```
common/
├── Bugs
├── dev
├── fake_headers
├── Feedopt
├── generate
├── gen_mex
├── kinematics
├── mex
├── ngc_test
├── old
├── src
├── Tests
├── types
├── utils
└── Validate_OpenCN
```

| Directory        | Content                                                               |
|------------------|-----------------------------------------------------------------------|
| Bugs             | Relevant files and data related to reported bugs ( see issues on Gitlab )                         |
| dev              | Untracked folder for developpment and quick test only                 |
| fake_headers     | Hand written header files used to be compliant with the machine kernel       |
| Feedopt          | Functions used in the feedrate planning algorithms                    |
| generate         | Files related to the C/C++ code generation and Mexing                 |
| gen_mex          | Generated mex functions and code                                      |
| kinematics       | Kinematics functions and tests                                        |
| mex              | C/C++ wrappers for mexing external code                               |
| ngc_test         | Set of RS274 G codes used for the tests                                |
| old              | Old version of algorithms and tests                                   |
| src              | Custom C/C++ functions                                                |
| Tests            | Tests files                                                           |
| types            | Types used to represent the curves                                    |
| utils            | Functions used for debugging and analyse the result of the algorithms |
| Validates_OpenCN | Validation of the algorithms against a set of G codes                 |




# 2. Complements
- C/C++ code generation has been tested and validated using the release 5.3 of Matlab Coder
- The code has been tested with Matlab 2021b
- The path planning algorithms are described in details in [chapter 5](https://mecatronyx.gitlab.io/opencnc/opencn/CNC_Path_Planning_Algorithms/CNC_Path_Planning_Algorithms.html) of the documentation.

- A guide for the utilisation of the Matlab coder in *opencn-matlab* is provided in [chapter 4.3](https://mecatronyx.gitlab.io/opencnc/opencn/components/feedopt.html) of the documentation.

# 3. Acknowledgements
| **Matlab function(s)** | **Functionality**                           | **Citation**                                                                                                                                                                                                                             |
|------------------------|---------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| lgwt.m                 | Legendre-Gauss Quadrature Weights and Nodes | Greg von Winckel (2022). [Legendre-Gauss Quadrature Weights and Nodes](https://www.mathworks.com/matlabcentral/fileexchange/4540-legendre-gauss-quadrature-weights-and-node), MATLAB Central File Exchange. Retrieved February 11, 2022. |
