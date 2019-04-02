package durnoga;

import java.util.Arrays;

public class ArrayStack implements IStack {

    private Object[] tab;
    private int index;

    public ArrayStack() {
        tab = new Object[1];
        index = 0;
    }

    public void push(Object value) {
        if(index == tab.length) {
            tab = Arrays.copyOf(tab, 2 * tab.length);
        }
        tab[index] = value;
        index++;
    }

    public Object pop() {
        if(isEmpty()) {
            System.err.println("Zdejmuje z pustego stosu");
            return null;
        }
        return tab[--index];
    }

    public boolean isEmpty() {
        return index == 0;
    }

    public Object top() {
        return tab[index-1];
    }

    @Override
    public String toString() {
        return Arrays.toString(Arrays.copyOf(tab, index));
    }
}
