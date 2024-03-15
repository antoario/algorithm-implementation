import java.util.Comparator;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

public class PriorityQueueTests {
    private final Comparator<String> stringComparator = Comparator.naturalOrder();
    private final Comparator<Integer> integerComparator = Comparator.naturalOrder();
    private PriorityQueue<String> stringPriorityQueue;
    private PriorityQueue<Integer> integerPriorityQueue;

    @Before
    public void createPriorityQueue() {
        stringPriorityQueue = new PriorityQueue<>(stringComparator);
        integerPriorityQueue = new PriorityQueue<>(integerComparator);
    }

    @Test
    public void emptyTest() {
        assertTrue(stringPriorityQueue.empty());
    }

    @Test
    public void notEmptyTest() {
        stringPriorityQueue.push("Test");
        assertFalse(stringPriorityQueue.empty());
    }

    @Test(expected = IllegalStateException.class)
    public void testTopEmpty() {
       stringPriorityQueue.top();
    }

    @Test
    public void testTopMoreEl() {
        stringPriorityQueue.push("Test0");
        stringPriorityQueue.push("Test1");
        stringPriorityQueue.push("Test2");
        assertEquals("Test0", stringPriorityQueue.top());
    }

    @Test
    public void testPushWithEl() {
        stringPriorityQueue.push("Test0");
        stringPriorityQueue.push("Test1");
        assertFalse(stringPriorityQueue.push("Test0"));
    }

    @Test
    public void testPushWithoutEl() {
        stringPriorityQueue.push("Test0");
        stringPriorityQueue.push("Test1");
        assertTrue(stringPriorityQueue.push("Test3"));
    }

    @Test(expected = IllegalStateException.class)
    public void testPopEmpty() {
        stringPriorityQueue.pop();
    }

    @Test
    public void testPopMoreEl() {
        stringPriorityQueue.push("Test0");
        stringPriorityQueue.push("Test1");
        stringPriorityQueue.pop();
        assertEquals(1, stringPriorityQueue.getSize());
    }

    @Test
    public void testContainsEmpty() {
        assertFalse(stringPriorityQueue.contains("Test"));
    }

    @Test
    public void testContainsWithEl() {
        stringPriorityQueue.push("Test0");
        stringPriorityQueue.push("Test1");
        stringPriorityQueue.push("Test2");
        assertTrue(stringPriorityQueue.contains("Test1"));
    }

    @Test
    public void testContainsWithoutEl() {
        stringPriorityQueue.push("Test0");
        stringPriorityQueue.push("Test1");
        stringPriorityQueue.push("Test2");
        assertFalse(stringPriorityQueue.contains("Test5"));
    }

    @Test
    public void testRemoveWithEl() {
        stringPriorityQueue.push("Test0");
        stringPriorityQueue.push("Test1");
        stringPriorityQueue.push("Test2");
        stringPriorityQueue.remove("Test1");
        assertEquals(2, stringPriorityQueue.getSize());
    }

    @Test
    public void testAddInteger() {
        integerPriorityQueue.push(2);
        integerPriorityQueue.push(5);
        integerPriorityQueue.push(6);
        integerPriorityQueue.push(4);
        //ArrayList<Integer> equal = new ArrayList<>(Arrays.asList(2,4,5,6));
        //assertEquals(equal, integerPriorityQueue.heap());
    }

    @Test
    public void testRemoveWithoutEl() {
        assertFalse(stringPriorityQueue.remove("Test"));
    }

    @Test
    public void testChangePriority() {
        stringPriorityQueue.push("Test0");
        stringPriorityQueue.push("Test1");
        stringPriorityQueue.push("Test2");
        stringPriorityQueue.changePriority("Test0");
        assertEquals("Test0", stringPriorityQueue.top());
    }
 }
