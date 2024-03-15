import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;

public class Prim {
    public static <V, L extends Number> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(Graph<V, L> graph) {
        HashSet<V> visitedNodes = new HashSet<>();
        PriorityQueue<Edge<V, L>> edgePriorityQueue = new PriorityQueue<>(Comparator.comparing(edge -> edge.getLabel().floatValue()));
        ArrayList<Edge<V, L>> resultEdges = new ArrayList<>();

        Set<V> allNodes = new HashSet<>(graph.getNodes());

        while (!allNodes.isEmpty()) {
            V start = allNodes.iterator().next();
            visitedNodes.add(start);
            graph.getEdges(start).forEach(edgePriorityQueue::push);

            while (!edgePriorityQueue.empty()) {
                Edge<V, L> smallestEdge = edgePriorityQueue.top();
                edgePriorityQueue.remove(smallestEdge);

                if (!visitedNodes.contains(smallestEdge.getEnd())) {
                    resultEdges.add(smallestEdge);
                    visitedNodes.add(smallestEdge.getEnd());
                    graph.getEdges(smallestEdge.getEnd()).forEach(edgePriorityQueue::push);
                }
            } // while

            allNodes.removeAll(visitedNodes);
        }

        return resultEdges;
    } // Prim

    public static void main(String[] args) {
        Graph<String, Float> graph = new Graph<>(false, false);

        // Check if there's textFilePath as argument.
        if (args.length < 1) {
            System.err.println("Usage: java Main <textFilePath> not found.");
            System.exit(1);
        }

        String filePath = args[0];
        String line;
        try (BufferedReader br = new BufferedReader(new FileReader(filePath))) {
            while ((line = br.readLine()) != null) {
                // Use comma as separator.
                String[] columns = line.split(",");


                graph.addNode(columns[0]);
                graph.addNode(columns[1]);
                graph.addEdge(columns[0], columns[1], Float.parseFloat(columns[2]));
            } // while
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Calculate the minimum spanning forest.
        Collection<AbstractEdge<String, Float>> minForest = (Collection<AbstractEdge<String, Float>>) minimumSpanningForest(graph);

        // Calculate num nodes.
        HashSet<String> nodes = new HashSet<>();
        minForest.forEach(edge -> {
            nodes.add(edge.getEnd());
            nodes.add(edge.getStart());
        });

        System.out.println("Num Edges: " + minForest.size());
        System.out.println("Num Node: " + nodes.size());

        // Calculate the distance.
        float totalDistance = 0.0f;
        for (AbstractEdge<?, Float> edge : minForest) {
            if (edge != null) {
                totalDistance += edge.getLabel();
            }
        } // for
        System.out.println("Distance in km: " + totalDistance / 1000);
    }
}
