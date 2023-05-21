import matplotlib.pyplot as plt

files = ['av_case.txt', 'worst_case.txt']

names = ['av_comps.jpg', 'max_comps.jpg', 'av_heights.jpg', 'max_heights.jpg', 'av_reads.jpg', 'max_reads.jpg', 'av_assignments.jpg', 'max_assignments.jpg']

titles = ['Average Comparisons', 'Max Comparisons', 'Average Heights', 'Max Heights', 'Average Reads', 'Max Reads', 'Average Assignments', 'Max Assignments']

colors = ['red', 'blue', 'green']

paths = ['../ex_2/', '../ex_4/', '../ex_6/']

labels = ['Binary Tree', 'Red Black Tree', 'Splay Tree']

for i, title in enumerate(titles):
    plt.figure()
    plt.title(titles[i])
    for k, path in enumerate(paths):
        data = []
        with open(path + files[i % 2], 'r') as f:
            for line in f:
                values = line.strip().split(', ')
                n = float(values[0])
                value = float(values[i + 1])
                data.append((n, value))
        xs, ys = zip(*data)
        plt.plot(xs, ys, color=colors[k], label=f'{labels[k]}')
    plt.legend()
    plt.savefig(f'../charts/{names[i]}')
    plt.close()