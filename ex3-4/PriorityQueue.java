import java.util.Comparator;
import java.util.ArrayList;
import java.util.HashMap;

/**
 * It implements a priority queue.
 * @param <E>: type of the array elements.
 */
public class PriorityQueue<E> implements AbstractQueue<E> {
    private final Comparator<E> comparator;
    private final ArrayList<E> heap;
    private final HashMap<E, Integer> map;

    /**
     * It creates an empty array and a hash map.
     * @param comparator: a comparator implementing the precedence relation between elements.
     */
    public PriorityQueue(Comparator<E> comparator) {
        if(comparator == null) throw new IllegalStateException("Comparator can't be null!");
        this.comparator = comparator;
        this.heap = new ArrayList<>();
        this.map = new HashMap<>();
    } // PriorityQueue


    /**
     * Check if the queue si empty and it returns a boolean value, result of the check.
     */
    @Override
    public boolean empty() {
        return heap.isEmpty();
    } // empty


    /**
     * It accesses the item at the top of the queue and it returns it.
     */
    @Override
    public E top() {
        if(empty()) throw new IllegalStateException("Queue is empty!");
        return heap.get(0);
    } // top


    /**
     * It adds an item to the queue and it returns a boolean value, result of the operation.
     * @param e: element to add to the queue.
     */
    @Override
    public boolean push(E e) {
        if (map.containsKey(e)) return false;
        heap.add(e);
        map.put(e, getChildIndex());

        if (comparator.compare(heap.get(getChildIndex()), heap.get(getParentIndex(getChildIndex()))) < 0) {
            fixHeapUp(getChildIndex());
        }
        return true;
    } // push


    /**
     *  It removes the item at the top of the queue.
     */
    @Override
    public void pop() {
        if (empty()) throw new IllegalStateException("Queue is empty!");
        E lastElement = heap.remove(getChildIndex());
        map.remove(lastElement);

        if (!heap.isEmpty()) {
            heap.set(0, lastElement);
            map.put(lastElement, 0);
            fixHeapDown(0);
        }
    } // pop


    /**
     * It checks if an element is queued and it returns a boolean value, result of the check.
     * @param e: element to found.
     */
    @Override
    public boolean contains(E e) {
        return map.containsKey(e);
    } // contains


    /**
     * It removes an element if it's present in the queue and it returns a boolean value, result of the operation.
     * @param e: element to remove.
     */
    @Override
    public boolean remove(E e) {
        if (!map.containsKey(e)) return false;
        int index = map.get(e);
        E lastElement = heap.remove(getChildIndex());
        map.remove(e);

        if (index != heap.size() && !heap.isEmpty()) {
            heap.set(index, lastElement);
            map.put(lastElement, index);
            fixHeapUp(index);
            fixHeapDown(index);
        }
        return true;
    } // remove


    /**
     * It changes the priority of an element.
     * @param e: element on which to change the priority.
     */
    public void changePriority(E e) {
        remove(e);
        push(e);
    } // changePriority


    /**
     * It restores the priority of the queue after adding an element.
     * @param childIndex: child index to be compared with the parent.
     */
    private void fixHeapUp(int childIndex) {
        while (childIndex > 0) {
            int parentIndex = getParentIndex(childIndex);

            if (comparator.compare(heap.get(childIndex), heap.get(parentIndex)) < 0) {
                swapElements(childIndex, parentIndex);
                childIndex = parentIndex;
            } else {
                break;
            }
        } // while
    } // fixHeapUp


    /**
     * It restores the priority of the queue after removing an element.
     * @param parentIndex: parent index to be compared with children.
     */
    private void fixHeapDown(int parentIndex) {
        int leftChildIndex = 2 * parentIndex + 1;

        while (leftChildIndex < heap.size()) {
            int smallestChildIndex = leftChildIndex;
            int rightChildIndex = leftChildIndex + 1;

            if (rightChildIndex < heap.size() && comparator.compare(heap.get(rightChildIndex), heap.get(leftChildIndex)) < 0) {
                smallestChildIndex = rightChildIndex;
            }

            if (comparator.compare(heap.get(parentIndex), heap.get(smallestChildIndex)) > 0) {
                swapElements(parentIndex, smallestChildIndex);
                parentIndex = smallestChildIndex;
                leftChildIndex = 2 * parentIndex + 1;
            } else {
                break;
            }
        } // while
    } // fixHeapDown


    /**
     * It swaps elements in the heap and update indexes in the hashmap.
     * @param index1: first element index to swap.
     * @param index2: second element index to swap.
     */
    private void swapElements(int index1, int index2) {
        E element1 = heap.get(index1);
        E element2 = heap.get(index2);

        heap.set(index1, element2);
        heap.set(index2, element1);
        map.put(element1, index2);
        map.put(element2, index1);
    } // swapElements


    /**
     * It calculates the child index and it returns it.
     */
    private int getChildIndex() {
        return heap.size() - 1;
    } // getChildIndex


    /**
     * It calculates the parent index and it returns it.
     * @param childIndex: child index useful to trace back to the parent.
     */
    private int getParentIndex(int childIndex) {
        return (childIndex - 1) / 2;
    } // getParentIndex


    /**
     * It returns heap size(useful for testing).
     */
    public int getSize() {
        return heap.size();
    } // getSize

    @Override
    public String toString(){
        return heap.toString();
    }
}
