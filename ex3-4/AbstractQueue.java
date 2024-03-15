public interface AbstractQueue<E> {
    public boolean empty(); // Check if the queue is empty -- O(1)
    public boolean push(E e); // Add an element to the queue -- O(logN)
    public boolean contains(E e); // Check if an element is queued -- O(1)
    public E top(); // Access the element at the top of the queue -- O(1)
    public void pop(); // Remove the element at the top of the queue -- O(logN)
    public boolean remove(E e); // Remove an element if it's present in the queue -- O(logN)
}