package graph;

import java.util.*;

public class Graph {

    private final int size;
    private final List<List<Edge>> adjList;
    private int maxWeight;
    private int minWeight;
    private int countEdges;

    public Graph(
            int size
    ) {
        this.size = size;
        this.maxWeight = -1;
        this.minWeight = Integer.MAX_VALUE;
        this.countEdges = 0;

        adjList = new ArrayList<>(size);

        for (int i = 0; i < size + 1; i++) {
            adjList.add(new ArrayList<>());
        }
    }

    public int getSize(

    ) {
        return size;
    }

    public int getCountEdges(

    ) {
        return countEdges;
    }

    public int getMaxWeight(

    ) {
        return maxWeight;
    }

    public int getMinWeight(

    ) {
        return minWeight;
    }

    public void addEdge(
            int source,
            int dest,
            int weight
    ) {
        Edge edge = new Edge(dest, weight);

        countEdges++;

        if (weight > maxWeight) {
            maxWeight = weight;
        }

        if (weight < minWeight) {
            minWeight = weight;
        }

        adjList.get(source).add(edge);
    }

    public void print(

    ) {
        System.out.println("Graph:");

        for (int i = 1; i <= size; i++) {
            System.out.print("Vertex " + i + ": ");
            for (Edge edge: adjList.get(i)) {
                System.out.print("(" + edge.getDest() + ", " + edge.getWeight() + ") ");
            }
            System.out.println();
        }

        System.out.println();
    }

    public String dijkstraTime(
            int source,
            boolean verbose
    ) {
        long start = System.nanoTime();
        this.dijkstra(source, verbose);
        double elapsedTime = (System.nanoTime() - start) / 1_000_000.0;
        return String.format("%.2f", elapsedTime);
    }


    public String dijkstraPath(
            int source,
            int dest,
            boolean verbose
    ) {
        int[] distances = this.dijkstra(source, verbose);
        return String.valueOf(distances[dest]);
    }

    public int[] dijkstra(
            int source,
            boolean verbose
    ) {
        if (verbose) {
            System.out.println("Source: " + source);
            System.out.println();
        }

        PriorityQueue<Vertex> heap = new PriorityQueue<>(new VertexComparator());

        int[] distances = new int[size + 1];
        boolean[] visited = new boolean[size + 1];

        Arrays.fill(distances, Integer.MAX_VALUE);

        heap.add(new Vertex(source, 0));
        distances[source] = 0;

        while (!heap.isEmpty()) {
            int id1 = heap.poll().getId();
            visited[id1] = true;

            for (Edge edge : adjList.get(id1)) {
                int id2 = edge.getDest();
                int weight = edge.getWeight();

                if (
                        !visited[id2]
                        && distances[id1] != Integer.MAX_VALUE
                        && distances[id1] + weight < distances[id2]
                ) {
                    distances[id2] = distances[id1] + weight;
                    heap.add(new Vertex(id2, distances[id2]));
                }
            }
        }

        if (verbose) {
            System.out.println("Distances:");

            for (int i = 1; i < size + 1; i++) {
                System.out.println("Vertex " + i + ": " + distances[i]);
            }

            System.out.println();
        }

        return distances;
    }

    public String dialTime(
            int source,
            boolean verbose
    ) {
        long start = System.nanoTime();
        this.dial(source, verbose);
        double elapsedTime = (System.nanoTime() - start) / 1_000_000.0;
        return String.format("%.2f", elapsedTime);
    }

    public String dialPath(
            int source,
            int dest,
            boolean verbose
    ) {
        int[] distances = this.dial(source, verbose);
        return String.valueOf(distances[dest]);
    }

    private int[] dial(int source, boolean verbose) {

        if (verbose) {
            System.out.println("Source: " + source);
            System.out.println();
        }

        int[] distances = new int[size + 1];
        boolean[] visited = new boolean[size + 1];

        Arrays.fill(distances, Integer.MAX_VALUE);

        int numVertices = 0;
        int bucketsNumber = maxWeight + 1;
        int nonEmptyBucket = 0;

        List<Queue<Integer>> buckets = new ArrayList<>(bucketsNumber);

        for (int i = 0; i < bucketsNumber; i++) {
            buckets.add(new ArrayDeque<>());
        }

        distances[source] = 0;
        buckets.get(0).add(source);
        numVertices++;

        while (numVertices > 0) {
            while (buckets.get(nonEmptyBucket).isEmpty()) {
                nonEmptyBucket++;
                if (nonEmptyBucket == bucketsNumber) {
                    nonEmptyBucket = 0;
                }
            }

            int v = buckets.get(nonEmptyBucket).poll();
            numVertices--;

            if (visited[v]) {
                continue;
            }

            visited[v] = true;

            for (Edge edge : adjList.get(v)) {
                int newDistance = distances[v] + edge.getWeight();
                int u = edge.getDest();

                if (distances[u] > newDistance) {
                    distances[u] = newDistance;
                    buckets.get(distances[u] % bucketsNumber).add(u);
                    numVertices++;
                }
            }
        }

        if (verbose) {
            System.out.println("Distances:");

            for (int i = 1; i < size + 1; i++) {
                System.out.println("Vertex " + i + ": " + distances[i]);
            }

            System.out.println();
        }

        return distances;
    }

    private long[] radixHeap(int source, boolean verbose) {

        if (verbose) {
            System.out.println("Source: " + source);
            System.out.println();
        }

        long[] distances = new long[size + 1];

        for (int i = 0; i < size + 1; i++) {
            distances[i] = Long.MAX_VALUE;
        }

        boolean[] visited = new boolean[size + 1];

        RadixHeap radixHeap = new RadixHeap();

        distances[source] = 0L;
        radixHeap.push(source, 0L);

        while (!radixHeap.isEmpty()) {
            int v = radixHeap.pop();

            if (visited[v]) {
                continue;
            }

            visited[v] = true;
            long distance = distances[v];

            for (Edge edge : adjList.get(v)) {
                long newDist = distance + edge.getWeight();

                if (distances[edge.getDest()] > newDist) {
                    distances[edge.getDest()] = newDist;
                    radixHeap.push(edge.getDest(), newDist);
                }
            }
        }

        if (verbose) {
            System.out.println("Distances:");

            for (int i = 1; i <= size; i++) {
                System.out.println("Vertex " + i + ": " + distances[i]);
            }

            System.out.println();
        }

        return distances;
    }

    public String radixHeapTime(
            int source,
            boolean verbose
    ) {
        long start = System.nanoTime();
        this.radixHeap(source, verbose);
        double elapsedTime = (System.nanoTime() - start) / 1_000_000.0;
        return String.format("%.2f", elapsedTime);
    }

    public String radixHeapPath(
            int source,
            int dest,
            boolean verbose
    ) {
        long[] distances = this.radixHeap(source, verbose);
        return String.valueOf(distances[dest]);
    }
}
