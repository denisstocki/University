import sys
import os
import matplotlib.pyplot as plt
from statistics import mean

def parse_file(file_path):
    data = {}
    with open(file_path, 'r') as file:
        lines = file.readlines()
        algorithm = lines[0].strip().split()[4]
        data['algorithm'] = algorithm
        data['vertices'] = int(lines[2].strip().split()[1])
        data['edges'] = int(lines[2].strip().split()[2])
        data['max_cost'] = int(lines[2].strip().split()[4])
        data['vertices_x_max_cost'] = data['vertices'] * data['max_cost']
        data['times'] = [float(line.strip().split()[1]) for line in lines[3:]]
    return data

def generate_charts(data_folder):
    algorithm_prefixes = ['dijkstra', 'diala', 'radix']
    x_prefixes = ['vertices', 'edges', 'max_cost', 'vertices_x_max_cost']

    for prefix in x_prefixes:
        # Wykres względem liczby wierzchołków
        x_values_dijkstra = []
        y_values_dijkstra = []

        # Wykres względem liczby krawędzi
        x_values_diala = []
        y_values_diala = []

        # Wykres względem maksymalnego kosztu
        x_values_radix = []
        y_values_radix = []

        for file_name in os.listdir(data_folder):
            if file_name.endswith('.ss.res'):
                file_path = os.path.join(data_folder, file_name)
                data = parse_file(file_path)
                algorithm = data['algorithm']
                value = data[prefix]
                times = data['times']
                avg_time = sum(times) / len(times)

                if file_name.startswith('dijkstra'):
                    x_values_dijkstra.append(value)
                    y_values_dijkstra.append(avg_time)
                elif file_name.startswith('diala'):
                    x_values_diala.append(value)
                    y_values_diala.append(avg_time)
                else:
                    x_values_radix.append(value)
                    y_values_radix.append(avg_time)

        # Posortuj punkty względem wartości x_values dla każdego wykresu
        sorted_points_dijkstra = sorted(zip(x_values_dijkstra, y_values_dijkstra))
        x_values_dijkstra, y_values_dijkstra = zip(*sorted_points_dijkstra)

        sorted_points_diala = sorted(zip(x_values_diala, y_values_diala))
        x_values_diala, y_values_diala = zip(*sorted_points_diala)

        sorted_points_radix = sorted(zip(x_values_radix, y_values_radix))
        x_values_radix, y_values_radix = zip(*sorted_points_radix)

        # Wykres względem liczby wierzchołków
        plt.plot(x_values_dijkstra, y_values_dijkstra, marker='o', label='dijkstra')

        # Wykres względem liczby krawędzi
        plt.plot(x_values_diala, y_values_diala, marker='o', label='diala')

        # Wykres względem maksymalnego kosztu
        plt.plot(x_values_radix, y_values_radix, marker='o', label='radix')
        plt.xlabel('Number of ' + prefix)
        plt.ylabel('Average Time')
        plt.title('Average Time of Algorithms - ' + prefix)
        plt.legend()

        chart_folder = os.path.join(os.getcwd(), 'charts')
        if not os.path.exists(chart_folder):
            os.makedirs(chart_folder)
        chart_name = f'{prefix}_chart.png'
        path = os.path.join(chart_folder, data_folder)
        if not os.path.exists(path):
            os.makedirs(path)
        chart_path = os.path.join(path, chart_name)

        # Zapisywanie wykresu do pliku
        plt.savefig(chart_path)
        plt.close()

        print(f'Chart saved: {chart_path}')




if __name__ == "__main__":
    if len(sys.argv) > 1:
        data_folder = sys.argv[1]
        print(data_folder)
        generate_charts(data_folder)
    else:
        print("Please provide the data folder path.")
