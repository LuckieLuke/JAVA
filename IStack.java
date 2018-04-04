package durnoga;

public interface IStack {
    void push(Object value);

    Object pop();

    boolean isEmpty();

    Object top();
}
