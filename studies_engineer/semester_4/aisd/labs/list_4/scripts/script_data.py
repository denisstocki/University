import subprocess
from statistics import mean

gens_arr = [
    "./../gens/rand_arr",
    "./../gens/inc_arr"
]

name_out = [
    "av_case.txt",
    "worst_case.txt"
]

path_arr = [
    "./../ex_1/", 
    "./../ex_3/", 
    "./../ex_5/"
]

path_out_arr = [
    "./../ex_2/", 
    "./../ex_4/", 
    "./../ex_6/"
]

def run_program(n, path, gen):
    process1 = subprocess.Popen([gen, str(n)], stdout=subprocess.PIPE)
    output1, _ = process1.communicate()
    process2 = subprocess.Popen([path + "ex"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    output2, _ = process2.communicate(input=output1)
    return output2.decode().strip().split("\n")

def save_results(filename, results):
    with open(filename, "w") as file:
        for result in results:
            file.write(result + "\n")

def calculate_statistics(data):
    for line in data:
        if line.startswith("COMPARISONS:"):
            comparisons = (int(line.split(":")[1].strip()))
        elif line.startswith("HEIGHT:"):
            heights = (int(line.split(":")[1].strip()))
        elif line.startswith("READS:"):
            reads = (int(line.split(":")[1].strip()))
        elif line.startswith("ASSIGNMENTS:"):
            assignments = (int(line.split(":")[1].strip()))
    
    return comparisons, heights, reads, assignments

for i in range(len(path_arr)):
    for j in range(len(gens_arr)):

        results = []

        if gens_arr[j] == "./../gens/inc_arr":
            start = 1000
            end = 10001
            inc = 1000
        else:
            start = 10000
            end = 100001
            inc = 10000

        for n in range(start, end, inc):
            comparisons_list = []
            heights_list = []
            reads_list = []
            assignments_list = []
    
            for _ in range(20):
                output = run_program(n, path_arr[i], gens_arr[j])
                comparisons, heights, reads, assignments = calculate_statistics(output)
                comparisons_list.append(comparisons)
                heights_list.append(heights)
                reads_list.append(reads)
                assignments_list.append(assignments)                
    
            avg_comparisons = mean(comparisons_list)
            max_comparisons = max(comparisons_list)
            avg_heights = mean(heights_list)
            max_heights = max(heights_list)
            avg_reads = mean(reads_list)
            max_reads = max(reads_list)
            avg_assignments = mean(assignments_list)
            max_assignments = max(assignments_list)

            results.append(f"{n}, {avg_comparisons}, {max_comparisons}, {avg_heights}, {max_heights}, {avg_reads}, {max_reads}, {avg_assignments}, {max_assignments}")

        save_results(path_out_arr[i] + name_out[j], results)
