import os
import re
from cxxheaderparser.simple import parse_string
import cxxheaderparser.errors
import matplotlib.pyplot as plt
import matplotlib.dates as mdates
import subprocess
import json
from datetime import datetime

def get_git_revision_short_hash() -> str:
    return subprocess.check_output(['git', 'rev-parse', '--short', 'HEAD']).decode('ascii').strip()

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
        if line.startswith("//"):
            continue
        i += 1
        found = False
        for function in decompiled_functions:
            if function in line:
                found = True
                break
        if not found:
            missing.append(function)
    return missing, i

def create_graphs(data, functions, missing, total, folder_path):
    ### Graph 1: total decompiled functions vs total functions in functions.c (bar)
    fig, ax = plt.subplots()
    ax.set_title("# of decompiled functions vs total # of functions in the executable")
    ax.bar(["Decompiled", "functions.c"], [len(functions), total])
    plt.savefig(os.path.join(folder_path, "graph1.png"))
    plt.close()
    ### Graph 2: decompiled and missing functions (pie)
    fig, ax = plt.subplots()
    ax.set_title("Decompiled functions vs missing functions")
    ax.pie([len(functions), len(missing)], labels=["Decompiled", "Missing"], autopct="%1.3f%%")
    plt.savefig(os.path.join(folder_path, "graph2.png"))
    plt.close()
    ### Graph 3: line graph of progress over time
    echovr58_data = data["v1.58"]
    timestamps = []
    total_decompiled = []
    commit_labels = []
    for commit, info in echovr58_data.items():
        timestamp = datetime.strptime(info["timestamp"], "%Y-%m-%dT%H:%M:%S.%f")
        timestamps.append((timestamp, info["percentage"], commit))
    timestamps.sort(key=lambda x: x[0])
    sorted_timestamps, sorted_decompiled, sorted_commits = zip(*timestamps)
    fig, ax = plt.subplots()
    ax.plot(sorted_timestamps, sorted_decompiled, marker='o', linestyle='-', color='b')
    for i, (commit, timestamp, decompiled) in enumerate(zip(sorted_commits, sorted_timestamps, sorted_decompiled)):
        ax.annotate(commit, (timestamp, decompiled), textcoords="offset points", xytext=(0,10), ha='center')
    ax.xaxis.set_major_locator(mdates.YearLocator())
    ax.xaxis.set_major_formatter(mdates.DateFormatter('%Y-%m-%d'))
    plt.gcf().autofmt_xdate()
    ax.set_xlabel('Time')
    ax.set_ylabel('Total Decompiled (%)')
    ax.set_title('Decompilation progress over time')
    plt.legend(['Total Decompiled'])
    plt.savefig(os.path.join(folder_path, "graph3.png"))
    print("Graphs created.")

def write_data(data, functions, missing, total, path):
    git_commit = get_git_revision_short_hash()
    data["v1.58"][git_commit] = {
        "timestamp": datetime.now().isoformat(),
        "total_decompiled": len(functions),
        "functions_c_total": total,
        "missing": len(missing),
        "percentage": len(functions) / total * 100
    }
    with open(path, "w") as f:
        f.write(json.dumps(data, indent=4))
    print("Data written to data.json.")

def print_progress(functions, missing, total):
    print()
    print("                         v1.58 Decompilation Progress")
    print("-------------------------------------------------------------------------------")
    print(f"Total function declarations (headers and source files): {len(functions)}")
    functions = set(functions)
    print(f"Unique functions: {len(functions)}")
    print(f"Total functions in functions.c: {total}")
    print(f"Total missing functions: {len(missing)}")
    print(f"               Grand percentage: ({len(functions)} / {total}) {len(functions) / total * 100:.5f}%")
    print("-------------------------------------------------------------------------------")
    print()

if __name__ == "__main__":
    print(" --- v1.58 ---")
    print("Finding decompiled functions...")
    functions = get_decompiled_functions("echovr58/EchoArena")
    print("Finding functions.c functions...")
    missing, total = compare_to_functions_c("echovr58/wip/functions.c", functions)
    print_progress(functions, missing, total)
    use_path_workaround = False
    try:
        f = open("docs/graphs/data.json", "r")
    except FileNotFoundError:
        use_path_workaround = True
        f = open("../docs/graphs/data.json", "r")
    path = "docs/graphs/data.json" if not use_path_workaround else "../docs/graphs/data.json"
    folder_path = "docs/graphs" if not use_path_workaround else "../docs/graphs"
    data = json.loads(f.read())
    f.close()
    write_data(data, functions, missing, total, path)
    create_graphs(data, functions, missing, total, folder_path)