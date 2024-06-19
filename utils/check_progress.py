"""
Quick and dirty script to check the total decompilation progress.
Here's how this (basically) works:
- Check the list of functions (functions.c)
- Crawl the decompiled code directory and find all function definitions in the c files (and headers too, just as another statistic)
- Compare the two lists (by name, not by parameters or return type) and print the results
"""
import os
import re
from cxxheaderparser.simple import parse_string
import cxxheaderparser.errors
from pprint import pprint

def parse_filename(filename):
    with open(filename, "r") as f:
        data = f.read()
    try:
        return parse_string(data)
    except cxxheaderparser.errors.CxxParseError:
        print(f"Failed to parse {filename}")
        return None

def parse_namespace(namespace, namespace_name=None):
    res = []
    functions = namespace.functions
    for function in functions:
        res.append(function.name.format())
    classes = namespace.classes
    for class_ in classes:
        functions = class_.methods
        for function in functions:
            if namespace_name:
                res.append(namespace_name + "::" + class_.class_decl.typename.format().split("class ")[1] + "::" + function.name.format())
            else:
                res.append(class_.class_decl.typename.format().split("class ")[1] + "::" + function.name.format())
    namespaces = namespace.namespaces
    for name, namespace in namespaces.items():
        if not namespace_name:
            res += parse_namespace(namespace, name)
        else:
            res += parse_namespace(namespace, namespace_name + "::" + name)
    return res

def get_functions(filename) -> list:
    res = []
    print(f"Processing {filename}")
    parsed = parse_filename(filename)
    if not parsed:
        return res
    res = parse_namespace(parsed.namespace)
    return res

def get_decompiled_functions(directory) -> list:
    res = []
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(".c") or file.endswith(".cpp") or file.endswith(".h"):
                functions = get_functions(os.path.join(root, file))
                res += functions
    return res

def compare_to_functions_c(functions_c, decompiled_functions):
    with open(functions_c, "r") as f:
        data = f.read()
    missing = []
    i = 0
    for line in data.split("\n"):
        i += 1
        found = False
        for function in decompiled_functions:
            if function in line:
                found = True
                break
        if not found:
            missing.append(function)
    return missing, i
    
if __name__ == "__main__":
    print("Finding decompiled functions...")
    functions = get_decompiled_functions("echovr58/EchoArena")
    print("Finding functions.c functions...")
    missing, total = compare_to_functions_c("echovr58/wip/functions.c", functions)
    print()
    print("-------------------------------------------------------------------------------")
    print(f"Total function declarations (headers and source files): {len(functions)}")
    functions = set(functions)
    print(f"Unique functions: {len(functions)}")
    print(f"Total functions in functions.c: {total}")
    print(f"Total missing functions: {len(missing)}")
    print(f"     Grand percentage: ({len(functions)} / {total}) {len(functions) / total * 100:.5f}%")
    print("-------------------------------------------------------------------------------")