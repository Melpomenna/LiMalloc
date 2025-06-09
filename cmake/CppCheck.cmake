
function(UseCppCheck target)
	 find_program(CPPCHECK_COMMAND cppcheck) 
	 if (CPPCHECK_COMMAND) 
		 message("cppcheck founded!\n") 
		 set_target_properties(${target} PROPERTIES C_CPPCHECK "${CPPCHECK_COMMAND};-q;-j4;--enable=information,performance,portability,warning;--error-exitcode=1;}") 
	endif() 
endfunction()
