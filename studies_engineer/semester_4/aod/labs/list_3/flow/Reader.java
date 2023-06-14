package flow;

import graph.Graph;
import graph.RadixTuple;
import graph.Tuple;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Reader {

    public static Graph readGraph(
        String name
    ) {
        File file = new File(name);

        try {
            Scanner scanner = new Scanner(file);
            Graph graph = null;

            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();

                if (line.startsWith("p sp")) {
                    String[] parts = line.split(" ");
                    graph = new Graph(Integer.parseInt(parts[2]));
                } else if (line.startsWith("a")) {
                    String[] parts = line.split(" ");

                    assert graph != null;

                    graph.addEdge(
                        Integer.parseInt(parts[1]),
                        Integer.parseInt(parts[2]),
                        Integer.parseInt(parts[3])
                    );
                }
            }

            return graph;
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    public static int[] readSources(
            String name
    ) {
        File file = new File(name);

        try {
            Scanner scanner = new Scanner(file);
            int[] sources = null;
            int counter = 0;

            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();

                if (line.startsWith("p aux sp ss")) {
                    String[] parts = line.split(" ");
                    sources = new int[Integer.parseInt(parts[4])];
                } else if (line.startsWith("s")) {
                    String[] parts = line.split(" ");

                    assert sources != null;

                    sources[counter++] = Integer.parseInt(parts[1]);
                }
            }

            return sources;
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    public static Tuple[] readPairs(
            String name
    ) {
        File file = new File(name);

        try {
            Scanner scanner = new Scanner(file);
            Tuple[] sources = null;
            int counter = 0;

            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();

                if (line.startsWith("p aux sp p2p")) {
                    String[] parts = line.split(" ");
                    sources = new Tuple[Integer.parseInt(parts[4])];
                } else if (line.startsWith("q")) {
                    String[] parts = line.split(" ");

                    assert sources != null;

                    sources[counter++] = new Tuple(
                            Integer.parseInt(parts[1]),
                            Integer.parseInt(parts[2])
                    );
                }
            }

            return sources;
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }

    public List<String> readSS(
        String name
    ) {
        return null;
    }

    public List<String> readP2P(
        String name
    ) {
        return null;
    }
}
