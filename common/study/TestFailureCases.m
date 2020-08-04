function TestFailureCases


load failure_cases/smooth_helix_line2.mat


PlotCurvStructs([CurvStruct1, CurvStruct2])
CalcTransition(CurvStruct1, CurvStruct2, CutOff)


end