import re
import sys

def find_functions_referencing_string(file_path, search_string):
    with open(file_path, 'r') as file:
        content = file.read()
    functions = re.split(r'//----- \(.*\) ----------------------------------------------------', content)
    matching_functions = [func for func in functions if search_string in func]
    return matching_functions

file_path = 'echovr58/orig/bin/win7/EchoArena.exe.c'
out_path = 'echovr58/EchoArena/funcs_referencing_string.c'
search_string = sys.argv[1]
matching_functions = find_functions_referencing_string(file_path, search_string)

with open(out_path, 'w') as file:
    for func in matching_functions:
        file.write(func + '\n\n\n')