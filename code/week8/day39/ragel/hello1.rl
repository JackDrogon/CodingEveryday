#include <stdio.h>
#include <string.h>

%%{
	machine foo;
	main :=
		      ('foo' | 'bar')
		      0 @{res = 1;};
}%%

%% write data;
