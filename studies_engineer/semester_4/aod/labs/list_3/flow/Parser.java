package flow;

import java.util.ArrayList;
import java.util.List;

public class Parser {

    public static List<String> parse(
            String[] args
    ) {
        System.out.println("Programme summoned with options:");
        System.out.println(args[0] + " " + args[1]);
        System.out.println(args[2] + " " + args[3]);
        System.out.println(args[4] + " " + args[5]);
        System.out.println(args[6] + " " + args[7]);
        System.out.println();

        if (
                !(args.length == 8
                && (args[2].equals("-d") && args[3].endsWith(".gr"))
                && (((args[4].equals("-ss") && args[5].endsWith(".ss")) && (args[6].equals("-oss") && args[7].endsWith(".ss.res")))
                || ((args[4].equals("-p2p") && args[5].endsWith(".p2p")) && (args[6].equals("-op2p") && args[7].endsWith(".p2p.res")))))
        ) {
            System.out.println("Invalid command format. Usage: java -jar out/dijkstra.jar -a alg -d name1.gr -ss name2.ss -oss name3.oss");
            System.out.println("Or: java -jar out/dijkstra.jar -a alg -d name1.gr -p2p name2.p2p -op2p name3.op2p");
            return null;
        }

        List<String> options = new ArrayList<>();

        options.add(args[1]);
        options.add(args[3]);
        options.add(args[5]);
        options.add(args[7]);

        return options;
    }
}
