package graph;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class RadixHeap {

    private static final int maxWeight = Long.SIZE;
    private static final int bucketsNumber = maxWeight + 1;
    private int size;
    private List<List<RadixTuple>> buckets;
    private long[] minDistances;
    private long minKey;

    public RadixHeap() {
        size = 0;
        minKey = Long.MAX_VALUE;

        buckets = new ArrayList<>(bucketsNumber);
        minDistances = new long[bucketsNumber];

        for (int i = 0; i < bucketsNumber; i++) {
            buckets.add(new ArrayList<>());
        }

        Arrays.fill(minDistances, Long.MAX_VALUE);
    }

    public boolean isEmpty() {
        return size == 0;
    }

    public void push(int v, long d) {
        int bucketIndex;
        if (d == minKey) {
            bucketIndex = 0;
        } else {
            bucketIndex = maxWeight - Long.numberOfLeadingZeros(d ^ minKey);
        }

        buckets.get(bucketIndex).add(new RadixTuple(d, v));
        size++;

        if (d < minDistances[bucketIndex]) {
            minDistances[bucketIndex] = d;
        }
    }

    public void pullNodes() {
        if (!buckets.get(0).isEmpty()) {
            return;
        }

        int bucketIndex = 1;
        while (buckets.get(bucketIndex).isEmpty()) {
            bucketIndex++;
        }

        minKey = minDistances[bucketIndex];

        for (RadixTuple node : buckets.get(bucketIndex)) {
            int newBucketIndex;
            if (node.getFirst() == minKey) {
                newBucketIndex = 0;
            } else {
                newBucketIndex = maxWeight - Long.numberOfLeadingZeros(node.getFirst() ^ minKey);
            }

            buckets.get(newBucketIndex).add(node);

            if (node.getFirst() < minDistances[newBucketIndex]) {
                minDistances[newBucketIndex] = node.getFirst();
            }
        }

        buckets.get(bucketIndex).clear();
        minDistances[bucketIndex] = Long.MAX_VALUE;
    }

    public int pop() {
        pullNodes();

        RadixTuple node = buckets.get(0).get(buckets.get(0).size() - 1);
        buckets.get(0).remove(buckets.get(0).size() - 1);
        size--;

        return node.getSecond();
    }
}
