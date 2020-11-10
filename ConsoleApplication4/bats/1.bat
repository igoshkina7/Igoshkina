@echo off

chcp 1251
 
FOR /L %%i IN (1 2 3) DO  (	
	\\C:\Users\igosh\source\repos\ConsoleApplication4\Debug\ConsoleApplication4.exe %%i.txt > \\C:\Users\igosh\source\repos\ConsoleApplication4\bats\%%i_log.txt
   
)
 
set /p research_string=Input research string:
set /p research_file=Input filename for research:

findstr %research_string% %research_file% 

pause