

% clear; clc;
% cfg = coder.config('mex');
% cfg.GenCodeOnly = false;
% cfg.FilePartitionMethod = 'MapMFileTOCFile';
% cfg.PreserveArrayDimensions = true;
% cfg.GenerateReport = false;
% cfg.TargetLang = 'C++';
% cfg.HardwareImplementation.ProdHWDeviceType = 'Generic->MATLAB Host Computer';
% 
% 
% codegen('-config', cfg, '-d', 'gen_mex/queue', ...
%     'queue_init', '-args', {int32(1), int32(8)}, ...
%     'queue_push', '-args', {int32(1), int32(8)}, ...
%     '-o', 'queue_mex');

clear; clc;
% spmd
mex mex/queue/queue_new.cpp -output queue_new_mex
mex mex/queue/queue_delete.cpp -output queue_delete_mex
mex mex/queue/queue_push.cpp -output queue_push_mex
mex mex/queue/queue_get.cpp -output queue_get_mex
mex mex/queue/queue_set.cpp -output queue_set_mex
mex mex/queue/queue_pop.cpp -output queue_pop_mex
mex mex/queue/queue_size.cpp -output queue_size_mex
mex mex/queue/queue_get_all.cpp -output queue_get_all_mex
% end