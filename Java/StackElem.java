package durnoga;

public class StackElem {

    private Object value;
    private StackElem next;

    public StackElem(Object value, StackElem next) {
        this.value = value;
        this.next = next;
    }

    public Object getValue() {

        return value;
    }

    public StackElem getNext() {

        return next;
    }
}
