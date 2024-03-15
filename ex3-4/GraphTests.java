import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;

public class GraphTests {
    private Graph<String, Integer> graph;

    @Before
    public void createGraph() {
        graph = new Graph<>(true, true);
    }

    @Test
    public void testIsDirected() {
        assertTrue(graph.isDirected());
        //assertFalse(graph.isDirected());  // if undirected
    }

    @Test
    public void testIsLabelled() {
        assertTrue(graph.isLabelled());
        //assertFalse(graph.isLabelled()); // if unlabelled
    }

    @Test
    public void testAddContainsNodes() {
        graph.addNode("A");
        graph.addNode("B");
        assertTrue(graph.containsNode("A"));
        assertTrue(graph.containsNode("B"));
    }

    @Test
    public void testAddContainsEdge() {
        graph.addNode("A");
        graph.addNode("B");
        graph.addEdge("A", "B", 1);
        assertTrue(graph.containsEdge("A", "B"));
        //assertTrue(graph.containsEdge("B", "A"));
    }

    @Test
    public void testRemoveContainsNode() {
        graph.addNode("A");
        graph.removeNode(("A"));
        assertFalse(graph.containsNode("A"));
    }

    @Test
    public void testRemoveContainsEdge() {
        graph.addNode("A");
        graph.addNode("B");
        graph.addEdge("A", "B", 1);
        graph.removeEdge("A", "B");
        graph.removeEdge("B", "A"); // if undirected
        assertFalse(graph.containsEdge("A", "B"));
    }

    @Test
    public void testNumNodes() {
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.removeNode("B");
        assertEquals(2, graph.numNodes());
    }

    @Test
    public void testNumEdges() {
        graph.addNode("A");
        graph.addNode("B");
        graph.addNode("C");
        graph.addEdge("A", "B", 1);
        graph.addEdge("B", "C", 2);
        graph.removeEdge("A", "B");
        assertEquals(1, graph.numEdges());
    }

    @Test
    public void testGetNodes() {
        graph.addNode("A");
        graph.addNode("B");
        HashMap<String, Integer> nodes = new HashMap<>();
        nodes.put("A",1);
        nodes.put("B",2);
        assertEquals(nodes.keySet(), graph.getNodes());
    }

    @Test
    public void testGetEdges() {
        graph.addNode("A");
        graph.addNode("B");
        graph.addEdge("A", "B", 1);
        Edge<String, Integer> edge1 = new Edge<>("A", "B", 1);
        Collection<? extends AbstractEdge<String, Integer>> allEdges = graph.getEdges();
        for (AbstractEdge<String, Integer> element : allEdges) {
                assertEquals(element.getStart(), edge1.getStart());
                assertEquals(element.getEnd(), edge1.getEnd());
                assertEquals(element.getLabel(), edge1.getLabel());
        }
    }

    @Test
    public void testGetHeighbours() {
        graph.addNode("A");
        graph.addNode("B");
        graph.addEdge("A", "B", 1);
        ArrayList<String> neighbours = new ArrayList<>();
        neighbours.add("B");
        assertEquals(neighbours, graph.getNeighbours("A"));
    }

    @Test
    public void testGetLabel() {
        graph.addNode("A");
        graph.addNode("B");
        graph.addEdge("A", "B", 1);
        assertEquals(1, (int) graph.getLabel("A", "B"));
    }
}
