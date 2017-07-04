 %% move cursor to beginning of the line
	io:format("\e[H").
	
	%% clear the console 
	io:format("\e[J").
	
	%% both
	io:format("\e[H\e[J").
