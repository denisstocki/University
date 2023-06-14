package graph;

public class Vertex {

    private int id;
    private int distance;

    public Vertex(
            int id,
            int distance
    ) {
        this.id  = id;
        this.distance = distance;
    }

    public int getId(

    ) {
        return id;
    }

    public int getDistance(

    ) {
        return distance;
    }
}
