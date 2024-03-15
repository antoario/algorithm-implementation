import java.util.*;

public class Graph<V, L> implements AbstractGraph<V, L> {
    private final boolean directed;
    private final boolean labelled;
    private final HashMap<V, HashSet<Integer>> nodesMap;
    private final HashMap<V, ArrayList<V>> neighboursMap;
    private final HashMap<Integer, Edge<V, L>> edgeHashMap;
    private int numNodes;
    private int numEdges;

    // Constructor
    public Graph(boolean directed, boolean labelled) {
        this.directed = directed;
        this.labelled = labelled;
        this.nodesMap = new HashMap<>();
        this.neighboursMap = new HashMap<>();
        this.edgeHashMap = new HashMap<>();
        this.numNodes = 0;
        this.numEdges = 0;
    }

    /**
     * It checks if the graph is directed.
     *
     * @return boolean value result of the check.
     */
    public boolean isDirected() {
        return directed;
    } // isDirected


    /**
     * It checks if the graph is labelled.
     *
     * @return boolean value result of the check.
     */
    public boolean isLabelled() {
        return labelled;
    } // isLabelled


    /**
     * It adds a new node in the graph.
     *
     * @param a: node to add.
     * @return boolean value, result of the operation.
     */
    public boolean addNode(V a) {
        if (containsNode(a)) return false;
        nodesMap.put(a, new HashSet<>());
        numNodes++;
        return true;
    } // addNode


    /**
     * It adds a new edge in the graph.
     *
     * @param a: first node.
     * @param b: second node.
     * @param l: label for the edge.
     * @return boolean value, result of the operation.
     */
    public boolean addEdge(V a, V b, L l) {
        if (containsEdge(a, b)) return false;

        Edge<V, L> edge = new Edge<>(a, b, l);
        int hash = Objects.hash(a, b);

        // Add the edge to the adjacency list of node 'a'
        HashSet<Integer> toAdd = nodesMap.get(a);
        toAdd.add(hash);
        edgeHashMap.put(hash, edge);
        numEdges++;

        // Update neighboursMap for node 'a'
        ArrayList<V> neighboursA = neighboursMap.computeIfAbsent(a, k -> new ArrayList<>());
        neighboursA.add(b);

        // If the graph is undirected, add the reverse edge and update the neighbour for 'b'
        if (!directed) {
            int hashB = Objects.hash(b, a);
            HashSet<Integer> toAddB = nodesMap.get(b);
            toAddB.add(hashB);
            Edge<V, L> edgeB = new Edge<>(b, a, l);
            edgeHashMap.put(Objects.hash(b, a), edgeB);

            ArrayList<V> neighboursB = neighboursMap.computeIfAbsent(b, k -> new ArrayList<>());
            neighboursB.add(a);
        }

        return true;
    } //addEdge


    /**
     * It checks if the graph contains a specific node passed as parameter.
     *
     * @param a: node to check.
     * @return boolean value indicating if the node is in the graph.
     */
    public boolean containsNode(V a) {
        return nodesMap.containsKey(a);
    } // containsNode


    /**
     * It checks if the graph contains a specific edge from 'a' to 'b'.
     *
     * @param a: first node.
     * @param b: second node.
     * @return boolean value indicating if the edge is in the graph.
     */
    public boolean containsEdge(V a, V b) {
        if (!directed)
            return edgeHashMap.containsKey(Objects.hash(a, b)) || edgeHashMap.containsKey(Objects.hash(b, a));
        return edgeHashMap.containsKey(Objects.hash(a, b));
    } // containsEdge


    /**
     * It removes a node from the graph and all edges associated with it.
     *
     * @param a: node to remove.
     * @return boolean value, result of the operation.
     */
    public boolean removeNode(V a) {

        if (!containsNode(a)) return false;

        ArrayList<Integer> edgesToRemove = new ArrayList<>(nodesMap.get(a));

        for (int edge : edgesToRemove) {
            removeEdge(a, edgeHashMap.get(edge).getEnd());
        }
        nodesMap.remove(a);
        numNodes--;
        return true;
    } // removeNode


    /**
     * It removes an edge from the graph.
     *
     * @param a: first node.
     * @param b: second node.
     * @return boolean value, result of the operation.
     */
    public boolean removeEdge(V a, V b) {
        if (!containsEdge(a, b)) return false;

        int hash = Objects.hash(a, b);
        edgeHashMap.remove(hash);
        HashSet<Integer> mapToRemove = nodesMap.get(a);
        mapToRemove.remove(hash);

        if (!directed) {
            int hashB = Objects.hash(b, a);
            mapToRemove = nodesMap.get(b);
            mapToRemove.remove(hashB);
            edgeHashMap.remove(hashB);
        }

        // Update the neighboursMap to remove the neighbour relationship
        if (neighboursMap.containsKey(a)) {
            neighboursMap.get(a).remove(b);
        }

        if (!directed && neighboursMap.containsKey(b)) {
            neighboursMap.get(b).remove(a);
        }

        numEdges--;
        return true;
    } // removeEdge


    /**
     * It returns the number of nodes present in the graph.
     *
     * @return int value that represents the number of nodes.
     */
    public int numNodes() {
        return numNodes;
    } // numNodes


    /**
     * It returns the number of edges present in the graph.
     *
     * @return int value that represents the number of edges.
     */
    public int numEdges() {
        return numEdges;
    } //numEdges


    /**
     * It retrieves graph nodes.
     *
     * @return graph nodes.
     */
    public Collection<V> getNodes() {
        return nodesMap.keySet();
    } // getNodes


    /**
     * It retrieves graph edges.
     *
     * @return graph edges.
     */
    public Collection<? extends AbstractEdge<V, L>> getEdges() {
        ArrayList<AbstractEdge<V, L>> edges = new ArrayList<>();
        edgeHashMap.forEach((key, value) -> {
            edges.add(value);
        });
        return edges;
    } // getEdges


    /**
     * It retrieves the nodes adjacent to a given node.
     *
     * @param a: node for which to search for neighbors.
     * @return node neighbors.
     */
    public Collection<V> getNeighbours(V a) {
        return neighboursMap.getOrDefault(a, new ArrayList<>());
    } // getNeighbours


    /**
     * It returns the label of an edge.
     *
     * @param a: first node.
     * @param b: second node.
     * @return label, if present.
     */
    public L getLabel(V a, V b) {
        if (!containsEdge(a, b)) return null;
        int hash = Objects.hash(a, b);
        if (edgeHashMap.containsKey(hash)) return edgeHashMap.get(hash).getLabel();
        return null;
    }

    /**
     * Retrieves the edges connected to a given node.
     *
     * @param a: node for which to retrieve connected edges.
     * @return a collection of edges connected to the specified node.
     */
    public Collection<Edge<V, L>> getEdges(V a) {
        Collection<Edge<V, L>> res = new ArrayList<>();
        nodesMap.get(a).forEach(val -> {
            res.add(edgeHashMap.get(val));
        });
        return res;
    }
}
