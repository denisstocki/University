package control;

import flow.Parser;
import flow.Reader;
import graph.Graph;
import graph.RadixTuple;
import graph.Tuple;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.List;
import java.util.Scanner;
import java.util.function.BiConsumer;
import java.util.function.BiFunction;

public class Main {

    public static void main(String[] args) {
        System.out.println();

        List<String> options = Parser.parse(args);
        boolean verbose = false;

        if (options == null) return;

        Graph graph = Reader.readGraph(options.get(1));

        if (options.get(2).endsWith(".ss")) {
            int[] sources = Reader.readSources(options.get(2));

            BiFunction<Graph, Integer, String> functionToInvoke = null;

            switch (options.get(0)) {
                case "dijkstra":
                    functionToInvoke = (g, source) -> g.dijkstraTime(source, verbose);
                    break;
                case "diala":
                    functionToInvoke = (g, source) -> g.dialTime(source, verbose);
                    break;
                case "radix":
                    functionToInvoke = (g, source) -> g.radixHeapTime(source, verbose);
                    break;
            }

            if (functionToInvoke != null) {
                try (PrintWriter writer = new PrintWriter(options.get(3))) {
                    writer.println("p res sp ss " + options.get(0));
                    writer.println("f " + options.get(1) + " " + options.get(2));
                    writer.println("g " + graph.getSize() + " " + graph.getCountEdges() + " " + graph.getMinWeight() + " " + graph.getMaxWeight());
                    for (int source : sources) {
                        writer.println("t " + functionToInvoke.apply(graph, source));
                    }
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
            }
        } else if (options.get(2).endsWith(".p2p")){
            Tuple[] pairs = Reader.readPairs(options.get(2));

            BiFunction<Graph, Tuple, String> functionToInvoke = null;

            switch (options.get(0)) {
                case "dijkstra":
                    functionToInvoke = (g, tuple) -> g.dijkstraPath(tuple.getFirst(), tuple.getSecond(), verbose);
                    break;
                case "diala":
                    functionToInvoke = (g, tuple) -> g.dialPath(tuple.getFirst(), tuple.getSecond(), verbose);
                    break;
                case "radix":
                    functionToInvoke = (g, tuple) -> g.radixHeapPath(tuple.getFirst(), tuple.getSecond(), verbose);
                    break;
            }

            if (functionToInvoke != null) {
                try (PrintWriter writer = new PrintWriter(options.get(3))) {
                    writer.println("p res sp p2p " + options.get(0));
                    writer.println("f " + options.get(1) + " " + options.get(2));
                    writer.println("g " + graph.getSize() + " " + graph.getCountEdges() + " " + graph.getMinWeight() + " " + graph.getMaxWeight());
                    for (Tuple tuple : pairs) {
                        writer.println("d " + tuple.getFirst() + " " + tuple.getSecond() + " " + functionToInvoke.apply(graph, tuple));
                    }
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}