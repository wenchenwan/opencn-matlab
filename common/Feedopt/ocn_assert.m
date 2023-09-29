function ocn_assert( condition, msg, fileName ) 
%#codegen
    if( StructTypeName.AssertDisable )
        % Fake Assert
        if( ~condition )
            fprintf( 2, "Assertion : " + "[" + fileName + "]" + msg + "\n");
        end
    else
        assert( condition, "[" + fileName + "]" + msg );
    end
end