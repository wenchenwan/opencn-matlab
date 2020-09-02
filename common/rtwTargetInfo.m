function rtwTargetInfo(cm)

cm.registerTargetInfo(@loc_register_crl);

function this = loc_register_crl

this(1) = RTW.TflRegistry;
this(1).Name = 'rpi4';
this(1).TableList = {'rpi4crl'};
this(1).BaseTfl = 'Inlined ARM NEON Intrinsics';
this(1).TargetHWDeviceType = {'*'};
this(1).Description = '';
