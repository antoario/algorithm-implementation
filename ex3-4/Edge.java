public class Edge<V, L> implements AbstractEdge<V, L> {
    private final V startNode;
    private final V endNode;
    private final L label;

    // Constructor
    public Edge(V startNode, V endNode, L label) {
        this.startNode = startNode;
        this.endNode = endNode;
        this.label = label;
    }

    /**
     * It returns the starting edge node.
     *
     * @return starting edge node.
     */
    public V getStart() {
        return startNode;
    }

    /** 
     * It returns the ending edge node.
     *
     * @return ending edge node.
     */
    public V getEnd() {
        return endNode;
    }

    /**
     * It returns the edge label.
     *
     * @return edge label.
     */
    public L getLabel() {
        return label;
    }


    /**
     * It returns the entire edge as String.
     *
     * @return String that contains the edge.
     */
    @Override
    public String toString() {
        return "{Start: " + this.startNode + " end: " + this.endNode + " label: " + this.label + "}";
    }
}
