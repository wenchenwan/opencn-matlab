%#codegen
% export_kinematics : Export the kinematics class using several entry
% functions. This necessary to export all the functions of a matlab class.
%
% Inputs :
%   cfg         : The configuration structure.
%   Rvec        : Input vector with specific size for the code generation
%   RMatrix     : Input matrix with specific size for the code generation
%
% Outputs : 
%   kin         : The kinematics instance.
%   vec         : The dummy vec
%   params      : Vector parameters of the kinematics
%   type        : Type of the kinematics
%   resVec      : The resulting vector
%   resMatrix   : The resulting matrix
%
function [ kin, vec, params, type, resVec, resMatrix ] = export_kinematics( cfg, Rvec, RMatrix )
    vec     = [];
    kin     = kinematics_init( cfg.kin_type, cfg.kin_params );
    kin     = kinematics_set_parameters( kin, cfg.kin_params );
    kin     = kinematics_set_type( kin, cfg.kin_type );
    kin     = kinematics_set_machine_offset( kin, zeros( 3, 1) );
    kin     = kinematics_set_piece_offset( kin, zeros( 3, 1) );
    kin     = kinematics_set_tool_offset( kin, zeros( 3, 1) );
    kin     = kinematics_set_tool_length( kin, 0 );
    params  = kinematics_get_params( kin );
    type    = kinematics_get_type( kin );
    
    % Forward kinematics (piece frame)
    resVec        = kinematics_r_relative( kin, Rvec );
    resMatrix     = kinematics_r_relative( kin, RMatrix );
    % Inverse kinematics (joint frame)
    resVec        = resVec + kinematics_r_joint( kin, Rvec );
    resMatrix     = resMatrix + kinematics_r_joint( kin, RMatrix );
    % Speed on piece frame
    resVec        = resVec + kinematics_v_relative( kin, Rvec, Rvec );
    resMatrix     = resMatrix + kinematics_v_relative( kin, RMatrix, RMatrix );
    % Speed on joint frame
    resVec        = resVec + kinematics_v_joint( kin, Rvec, Rvec );
    resMatrix     = resMatrix + kinematics_v_joint( kin, RMatrix, RMatrix );
    % Acceleration on piece frame
    resVec        = resVec + kinematics_a_relative( kin, Rvec, Rvec, Rvec );
    resMatrix     = resMatrix + kinematics_a_relative( kin, RMatrix, RMatrix, RMatrix );
    % Acceleration on joint frame
    resVec        = resVec + kinematics_a_joint( kin, Rvec, Rvec, Rvec );
    resMatrix     = resMatrix + kinematics_a_joint( kin, RMatrix, RMatrix, RMatrix );
    % Jerk on piece frame
    resVec        = resVec + kinematics_j_relative( kin, Rvec, Rvec, Rvec, Rvec );
    resMatrix     = resMatrix + kinematics_j_relative( kin, RMatrix, RMatrix, RMatrix, RMatrix );
    % Jerk on joint frame
    resVec        = resVec + kinematics_j_joint( kin, Rvec, Rvec, Rvec, Rvec );
    resMatrix     = resMatrix + kinematics_j_joint( kin, RMatrix, RMatrix, RMatrix, RMatrix );

    % Complete transformation (Piece frame)
    [ piece, v_piece, a_piece, j_piece ] = kinematics_relative( kin, Rvec, Rvec, Rvec, Rvec );
    resVec        = resVec + piece + v_piece + a_piece + j_piece;

    [ pieceM, v_pieceM, a_pieceM, j_pieceM ] = kinematics_relative( kin, Rvec, Rvec, Rvec, Rvec );
    resMatrix     = resMatrix + pieceM + v_pieceM + a_pieceM + j_pieceM;

    % Complete transformation (Joint frame)
    [ joint, v_joint, a_joint, j_joint ] = kinematics_joint( kin, Rvec, Rvec, Rvec, Rvec );
    resVec        = resVec + joint + v_joint + a_joint + j_joint;

    [ jointM, v_jointM, a_jointM, j_jointM ] = kinematics_joint( kin, Rvec, Rvec, Rvec, Rvec );
    resMatrix     = resMatrix + jointM + v_jointM + a_jointM + j_jointM;
end


function [ kin ] = kinematics_set_parameters( kin, params )
    kin = kin.set_params( params );
end

function [ kin ] = kinematics_init( type, params )
    kin = Kinematics( type, params );
end

function [ kin ] = kinematics_set_type( kin, type )
    kin = kin.set_type( type );
end

function [ kin ] = kinematics_set_machine_offset( kin, offset )
    kin = kin.set_machine_offset( offset );
end

function [ kin ] = kinematics_set_tool_offset( kin, offset )
    kin = kin.set_tool_offset( offset );
end

function [ kin ] = kinematics_set_piece_offset( kin, offset )
    kin = kin.set_piece_offset( offset );
end

function [ kin ] = kinematics_set_tool_length( kin , tool_length )
    kin = kin.set_piece_offset( tool_length );
end

function [ params ] = kinematics_get_params( kin )
    params = kin.get_params();
end

function [ type ] = kinematics_get_type( kin )
    type = kin.get_type();
end

function [ piece ] = kinematics_r_relative( kin, joint )
    piece = kin.r_relative( joint );
end

function [ joint ] = kinematics_r_joint( kin, piece )
    joint = kin.r_joint( piece );
end

function [ v_piece ] = kinematics_v_relative( kin, joint, v_joint )
    v_piece = kin.v_relative( joint, v_joint );
end

function [ v_joint ] = kinematics_v_joint( kin, piece, v_piece )
    v_joint = kin.v_joint( piece, v_piece );
end

function [ a_piece ] = kinematics_a_relative( kin, joint, v_joint, a_joint )
    a_piece = kin.a_relative( joint, v_joint, a_joint );
end

function [ a_joint ] = kinematics_a_joint( kin, piece, v_piece, a_piece )
    a_joint = kin.a_joint( piece, v_piece, a_piece );
end

function [ j_piece ] = kinematics_j_relative( kin, joint, v_joint, a_joint, j_joint )
    j_piece = kin.j_relative( joint, v_joint, a_joint, j_joint );
end

function [ j_joint ] = kinematics_j_joint( kin, piece, v_piece, a_piece, j_piece )
   j_joint = kin.j_joint( piece, v_piece, a_piece, j_piece );
end

function [ piece, v_piece, a_piece, j_piece ] = kinematics_relative( kin, joint, v_joint, a_joint, j_joint )
    [ piece, v_piece, a_piece, j_piece ] = kin.relative( joint, v_joint, a_joint, j_joint );
end

function [ joint, v_joint, a_joint, j_joint ] = kinematics_joint( kin, piece, v_piece, a_piece, j_piece )
    [ joint, v_joint, a_joint, j_joint ] = kin.joint( piece, v_piece, a_piece, j_piece );
end
