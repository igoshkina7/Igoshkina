\\C:\Users\igosh\source\repos\ConsoleApplication4\Debug\ConsoleApplication4.exe 1.txt 2.txt 3.txt > \\C:\Users\igosh\OneDrive\Рабочий стол\full_log.txt


@echo off

chcp 1251
 
\\C:\Users\igosh\source\repos\ConsoleApplication4\Debug\ConsoleApplication4.exe 1.txt 2.txt 3.txt > \\C:\Users\igosh\source\repos\ConsoleApplication4\bats\full_log.txt

set /p research_string=Input research string:
set /p research_file=Input filename for research:

findstr %research_string% %research_file% 

pause