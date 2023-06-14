package graph;

public class RadixTuple {
    private long first;
    private int second;

    public RadixTuple(long first, int second) {
        this.first = first;
        this.second = second;
    }

    public long getFirst(

    ) {
        return first;
    }

    public int getSecond(

    ) {
        return second;
    }

    public void setFirst(
            long first
    ) {
        this.first = first;
    }

    public void setSecond(
            int second
    ) {
        this.second = second;
    }
}
