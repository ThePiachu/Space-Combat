@echo off
del D:\1\list.txt
for /R D:\1\ %%A in (*) do echo %%A >> D:\1\list.txt