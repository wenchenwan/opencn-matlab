 classdef LibInfo
    properties( Constant = true )
         gsl = struct('cflags', find_libcflags('gsl'), 'lflags', find_liblflags('gsl'));
         clp = struct('cflags', find_libcflags('clp'), 'lflags', find_liblflags('clp'));
    end
 end