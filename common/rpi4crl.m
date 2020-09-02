function hLib = rpi4crl


hLib = RTW.TflTable;
%---------- entry: sqrt ----------- 
hEnt = createCRLEntry(hLib, ...
    'double y1 = sqrt( double u1 )', ...
    'double y1 = __ocn_sqrt( double u1 )');
hEnt.setTflCFunctionEntryParameters( ...
          'Priority', 100, ...
          'ImplementationHeaderFile', 'crl.h');



hLib.addEntry( hEnt ); 

