#!/bin/bash
if [ -z "$MATLAB" ]
then
	echo 'MATLAB env var is not set, point it to your matlab executable'
else
	$MATLAB -nodisplay -nosplash -nodesktop -r 'run ./generate_c; exit'
fi
