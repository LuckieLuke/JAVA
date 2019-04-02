package durnoga;

public class YetAnotherStack implements IStack {

    private Stack stack;

    public YetAnotherStack() {
        stack = new Stack();
    }


    @Override
    public void push(Object value) {
        stack.push(value);
    }

    @Override
    public Object pop() {
        return stack.pop();
    }

    @Override
    public boolean isEmpty() {
        return stack.isEmpty();
    }

    @Override
    public Object top() {
        return stack.top();
    }
}
